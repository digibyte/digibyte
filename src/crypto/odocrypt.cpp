// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The DigiByte developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "odocrypt.h"

#include <algorithm>

struct OdoRandom
{
    // LCG parameters from Knuth
    const static uint64_t BASE_MULTIPLICAND = 6364136223846793005ull;
    const static uint64_t BASE_ADDEND = 1442695040888963407ull;

    OdoRandom(uint32_t seed):
        current(seed),
        multiplicand(1),
        addend(0)
    {}

    // For a standard LCG, every seed produces the same sequence, but from a different
    // starting point.  This generator gives the 1st, 3rd, 6th, 10th, etc output from
    // a standard LCG.  This ensures that every seed produces a unique sequence.
    inline int Next(int N)
    {
        addend += multiplicand * BASE_ADDEND;
        multiplicand *= BASE_MULTIPLICAND;
        current = current * multiplicand + addend;
        return ((current >> 32) * N) >> 32;
    }

    template<class T>
    void Shuffle(T first, int N)
    {
        for (int i = 1; i < N; i++)
            std::swap(first[i], first[Next(i+1)]);
    }

    uint64_t current;
    uint64_t multiplicand;
    uint64_t addend;
};

template<class T>
void InvertMapping(T res[], const T mapping[], size_t size)
{
    for (size_t i = 0; i < size; i++)
        res[mapping[i]] = i;
}

OdoCrypt::OdoCrypt(uint32_t key)
{
    OdoRandom r(key);

    // Randomize each s-box
    for (int i = 0; i < STATE_SIZE; i++)
    {
        for (int j = 0; j < SBOX_VALUES; j++)
            Sbox[i][j] = j;
        r.Shuffle(Sbox[i], SBOX_VALUES);
        InvertMapping(InvSbox[i], Sbox[i], SBOX_VALUES);
    }

    // Randomize each p-box
    for (int i = 0; i < SBOX_WIDTH; i++)
    {
        int cycle[STATE_SIZE];
        for (int j = 0; j < STATE_SIZE; j++)
            cycle[j] = j;
        r.Shuffle(cycle, STATE_SIZE);
        for (int j = 1; j < STATE_SIZE; j++)
            Pbox[i][cycle[j-1]] = cycle[j];
        Pbox[i][cycle[STATE_SIZE-1]] = cycle[0];
        InvertMapping(InvPbox[i], Pbox[i], STATE_SIZE);
    }
    // Randomize each round key
    for (int i = 0; i < ROUNDS; i++)
        RoundKey[i] = r.Next(1 << ROUNDKEY_BITS);
}

void OdoCrypt::Encrypt(char cipher[DIGEST_SIZE], const char plain[DIGEST_SIZE]) const
{
    uint8_t state[STATE_SIZE];
    Unpack(state, plain);
    for (int round = 0; round < ROUNDS; round++)
    {
        ApplySbox(state, Sbox);
        ApplyPbox(state, Pbox);
        ApplyRoundKey(state, RoundKey[round]);
    }
    Pack(state, cipher);
}

void OdoCrypt::EncryptBitsliced(char cipher[64][DIGEST_SIZE], const char plain[64][DIGEST_SIZE]) const
{
    uint64_t state[DIGEST_BITS];
    UnpackBitsliced(state, plain);
    for (int round = 0; round < ROUNDS; round++)
    {
        for (int i = 0; i < STATE_SIZE; i++)
            ApplySboxBitsliced(state + SBOX_WIDTH*i, Sbox[i]);
        ApplyPboxBitsliced(state, Pbox);
        ApplyRoundKeyBitsliced(state, RoundKey[round]);
    }
    PackBitsliced(state, cipher);
}

void OdoCrypt::Decrypt(char plain[DIGEST_SIZE], const char cipher[DIGEST_SIZE]) const
{
    uint8_t state[STATE_SIZE];
    Unpack(state, cipher);
    for (int round = ROUNDS-1; round >= 0; round--)
    {
        ApplyRoundKey(state, RoundKey[round]);
        ApplyPbox(state, InvPbox);
        ApplySbox(state, InvSbox);
    }
    Pack(state, plain);
}

void OdoCrypt::Unpack(uint8_t state[STATE_SIZE], const char bytes[DIGEST_SIZE])
{
    std::fill(state, state+STATE_SIZE, 0);
    unsigned int pos = 0;
    for (int i = 0; i < STATE_SIZE; i++)
    {
        for (int j = 0; j < SBOX_WIDTH; j++)
        {
            uint8_t bit = (bytes[pos / 8] >> (pos % 8)) & 1;
            state[i] |= bit << j;
            pos++;
        }
    }
}

void OdoCrypt::Pack(const uint8_t state[STATE_SIZE], char bytes[DIGEST_SIZE])
{
    std::fill(bytes, bytes+DIGEST_SIZE, 0);
    unsigned int pos = 0;
    for (int i = 0; i < STATE_SIZE; i++)
    {
        for (int j = 0; j < SBOX_WIDTH; j++)
        {
            uint8_t bit = (state[i] >> j) & 1;
            bytes[pos / 8] |= bit << (pos % 8);
            pos++;
        }
    }
}

void OdoCrypt::ApplySbox(uint8_t state[STATE_SIZE], const uint8_t sbox[STATE_SIZE][SBOX_VALUES])
{
    for (int i = 0; i < STATE_SIZE; i++)
        state[i] = sbox[i][state[i]];
}

void OdoCrypt::ApplyPbox(uint8_t state[STATE_SIZE], const int pbox[SBOX_WIDTH][STATE_SIZE])
{
    uint8_t next[STATE_SIZE] = {};
    for (int i = 0; i < SBOX_WIDTH; i++)
    for (int j = 0; j < STATE_SIZE; j++)
    {
        next[pbox[i][j]] |= state[j] & (1<<i);
    }
    std::copy(next, next+STATE_SIZE, state);
}

void OdoCrypt::ApplyRoundKey(uint8_t state[STATE_SIZE], int roundKey)
{
    for (int i = 0; i < ROUNDKEY_BITS; i++)
        state[i] ^= (roundKey >> i) & 1;
}

void OdoCrypt::UnpackBitsliced(uint64_t state[DIGEST_BITS], const char bytes[64][DIGEST_SIZE])
{
    std::fill(state, state+DIGEST_BITS, 0);
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < DIGEST_SIZE; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                uint64_t bit = (bytes[i][j] >> k) & 1;
                state[8*j+k] |= bit << i;
            }
        }
    }
}

void OdoCrypt::PackBitsliced(uint64_t state[DIGEST_BITS], char bytes[64][DIGEST_SIZE])
{
    for (int i = 0; i < 64; i++)
        std::fill(bytes[i], bytes[i]+DIGEST_SIZE, 0);
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < DIGEST_SIZE; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                uint8_t bit = (state[8*j+k] >> i) & 1;
                bytes[i][j] |= bit << k;
            }
        }
    }
}

#define UNROLLED 1
void OdoCrypt::ApplySboxBitsliced(uint64_t state[SBOX_WIDTH], const uint8_t sbox[SBOX_VALUES])
{
    uint64_t data[SBOX_VALUES];

    // demux
    if (!UNROLLED)
    {
        data[0] = -1;
        for (int i = 0; i < SBOX_WIDTH; i++)
        {
            int shift = 1 << i;
            for (int j = 0; j < shift; j++)
            {
                data[j+shift] = data[j] & state[i];
                data[j] &= ~state[i];
            }
        }
    }
    else
    {
        uint64_t lo[8] = {
            ~state[0] & ~state[1] & ~state[2],
             state[0] & ~state[1] & ~state[2],
            ~state[0] &  state[1] & ~state[2],
             state[0] &  state[1] & ~state[2],
            ~state[0] & ~state[1] &  state[2],
             state[0] & ~state[1] &  state[2],
            ~state[0] &  state[1] &  state[2],
             state[0] &  state[1] &  state[2],
        };
        uint64_t hi[8] = {
            ~state[3] & ~state[4] & ~state[5],
             state[3] & ~state[4] & ~state[5],
            ~state[3] &  state[4] & ~state[5],
             state[3] &  state[4] & ~state[5],
            ~state[3] & ~state[4] &  state[5],
             state[3] & ~state[4] &  state[5],
            ~state[3] &  state[4] &  state[5],
             state[3] &  state[4] &  state[5],
        };
        data[0] = lo[0] & hi[0];
        data[1] = lo[1] & hi[0];
        data[2] = lo[2] & hi[0];
        data[3] = lo[3] & hi[0];
        data[4] = lo[4] & hi[0];
        data[5] = lo[5] & hi[0];
        data[6] = lo[6] & hi[0];
        data[7] = lo[7] & hi[0];
        data[8] = lo[0] & hi[1];
        data[9] = lo[1] & hi[1];
        data[10] = lo[2] & hi[1];
        data[11] = lo[3] & hi[1];
        data[12] = lo[4] & hi[1];
        data[13] = lo[5] & hi[1];
        data[14] = lo[6] & hi[1];
        data[15] = lo[7] & hi[1];
        data[16] = lo[0] & hi[2];
        data[17] = lo[1] & hi[2];
        data[18] = lo[2] & hi[2];
        data[19] = lo[3] & hi[2];
        data[20] = lo[4] & hi[2];
        data[21] = lo[5] & hi[2];
        data[22] = lo[6] & hi[2];
        data[23] = lo[7] & hi[2];
        data[24] = lo[0] & hi[3];
        data[25] = lo[1] & hi[3];
        data[26] = lo[2] & hi[3];
        data[27] = lo[3] & hi[3];
        data[28] = lo[4] & hi[3];
        data[29] = lo[5] & hi[3];
        data[30] = lo[6] & hi[3];
        data[31] = lo[7] & hi[3];
        data[32] = lo[0] & hi[4];
        data[33] = lo[1] & hi[4];
        data[34] = lo[2] & hi[4];
        data[35] = lo[3] & hi[4];
        data[36] = lo[4] & hi[4];
        data[37] = lo[5] & hi[4];
        data[38] = lo[6] & hi[4];
        data[39] = lo[7] & hi[4];
        data[40] = lo[0] & hi[5];
        data[41] = lo[1] & hi[5];
        data[42] = lo[2] & hi[5];
        data[43] = lo[3] & hi[5];
        data[44] = lo[4] & hi[5];
        data[45] = lo[5] & hi[5];
        data[46] = lo[6] & hi[5];
        data[47] = lo[7] & hi[5];
        data[48] = lo[0] & hi[6];
        data[49] = lo[1] & hi[6];
        data[50] = lo[2] & hi[6];
        data[51] = lo[3] & hi[6];
        data[52] = lo[4] & hi[6];
        data[53] = lo[5] & hi[6];
        data[54] = lo[6] & hi[6];
        data[55] = lo[7] & hi[6];
        data[56] = lo[0] & hi[7];
        data[57] = lo[1] & hi[7];
        data[58] = lo[2] & hi[7];
        data[59] = lo[3] & hi[7];
        data[60] = lo[4] & hi[7];
        data[61] = lo[5] & hi[7];
        data[62] = lo[6] & hi[7];
        data[63] = lo[7] & hi[7];
    }

    // permute
    uint64_t permuted[SBOX_VALUES];
    for (int i = 0; i < SBOX_VALUES; i++)
        permuted[sbox[i]] = data[i];

    // mux
    if (!UNROLLED)
    {
        for (int i = SBOX_WIDTH-1; i >= 0; i--)
        {
            state[i] = 0;
            int shift = 1 << i;
            for (int j = 0; j < shift; j++)
            {
                state[i] |= permuted[j+shift];
                permuted[j] |= permuted[j+shift];
            }
        }
    }
    else
    {
        uint64_t lo[8] = {
            0,
            permuted[1] | permuted[ 9] | permuted[17] | permuted[25] | permuted[33] | permuted[41] | permuted[49] | permuted[57],
            permuted[2] | permuted[10] | permuted[18] | permuted[26] | permuted[34] | permuted[42] | permuted[50] | permuted[58],
            permuted[3] | permuted[11] | permuted[19] | permuted[27] | permuted[35] | permuted[43] | permuted[51] | permuted[59],
            permuted[4] | permuted[12] | permuted[20] | permuted[28] | permuted[36] | permuted[44] | permuted[52] | permuted[60],
            permuted[5] | permuted[13] | permuted[21] | permuted[29] | permuted[37] | permuted[45] | permuted[53] | permuted[61],
            permuted[6] | permuted[14] | permuted[22] | permuted[30] | permuted[38] | permuted[46] | permuted[54] | permuted[62],
            permuted[7] | permuted[15] | permuted[23] | permuted[31] | permuted[39] | permuted[47] | permuted[55] | permuted[63],
        };
        uint64_t hi[8] = {
            0,
            permuted[ 8] | permuted[ 9] | permuted[10] | permuted[11] | permuted[12] | permuted[13] | permuted[14] | permuted[15],
            permuted[16] | permuted[17] | permuted[18] | permuted[19] | permuted[20] | permuted[21] | permuted[22] | permuted[23],
            permuted[24] | permuted[25] | permuted[26] | permuted[27] | permuted[28] | permuted[29] | permuted[30] | permuted[31],
            permuted[32] | permuted[33] | permuted[34] | permuted[35] | permuted[36] | permuted[37] | permuted[38] | permuted[39],
            permuted[40] | permuted[41] | permuted[42] | permuted[43] | permuted[44] | permuted[45] | permuted[46] | permuted[47],
            permuted[48] | permuted[49] | permuted[50] | permuted[51] | permuted[52] | permuted[53] | permuted[54] | permuted[55],
            permuted[56] | permuted[57] | permuted[58] | permuted[59] | permuted[60] | permuted[61] | permuted[62] | permuted[63],
        };
        state[0] = lo[1] | lo[3] | lo[5] | lo[7];
        state[1] = lo[2] | lo[3] | lo[6] | lo[7];
        state[2] = lo[4] | lo[5] | lo[6] | lo[7];
        state[3] = hi[1] | hi[3] | hi[5] | hi[7];
        state[4] = hi[2] | hi[3] | hi[6] | hi[7];
        state[5] = hi[4] | hi[5] | hi[6] | hi[7];
    }
}

void OdoCrypt::ApplyPboxBitsliced(uint64_t state[DIGEST_BITS], const int pbox[SBOX_WIDTH][STATE_SIZE])
{
    uint64_t nextState[DIGEST_BITS];
    for (int i = 0; i < SBOX_WIDTH; i++)
    {
        for (int j = 0; j < STATE_SIZE; j++)
        {
            nextState[SBOX_WIDTH*pbox[i][j] + i] = state[SBOX_WIDTH*j + i];
        }
    }
    std::copy(nextState, nextState + DIGEST_BITS, state);
}

void OdoCrypt::ApplyRoundKeyBitsliced(uint64_t state[DIGEST_BITS], int roundKey)
{
    for (int i = 0; i < ROUNDKEY_BITS; i++)
        state[SBOX_WIDTH*i] ^= -(uint64_t)((roundKey >> i) & 1);
}

