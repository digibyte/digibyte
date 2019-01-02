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

    template<class T, size_t sz>
    void Permutation(T (&arr)[sz])
    {
        for (size_t i = 0; i < sz; i++)
            arr[i] = i;
        Shuffle(arr, sz);
    }

    uint64_t current;
    uint64_t multiplicand;
    uint64_t addend;
};

void RandomizePbox(OdoRandom& r, uint64_t pbox[OdoCrypt::STATE_SIZE][OdoCrypt::STATE_SIZE])
{
    for (int i = 0; i < OdoCrypt::STATE_SIZE; i++)
    for (int j = 0; j < OdoCrypt::STATE_SIZE; j++)
        pbox[i][j] = 0;
    for (int i = 0; i < OdoCrypt::WORD_BITS; i++)
    {
        int cycle[OdoCrypt::STATE_SIZE + 1];
        for (size_t j = 0; j < OdoCrypt::STATE_SIZE; j++)
            cycle[j] = j;
        r.Shuffle(cycle, OdoCrypt::STATE_SIZE);
        cycle[OdoCrypt::STATE_SIZE] = cycle[0];
        for (size_t j = 0; j < OdoCrypt::STATE_SIZE; j++)
            pbox[cycle[j]][cycle[j+1]] |= (uint64_t)1 << i;
    }
}

OdoCrypt::OdoCrypt(uint32_t key)
{
    OdoRandom r(key);

    // Randomize each s-box
    for (int i = 0; i < SMALL_SBOX_COUNT; i++)
    {
        r.Permutation(Sbox1[i]);
    }
    for (int i = 0; i < LARGE_SBOX_COUNT; i++)
    {
        r.Permutation(Sbox2[i]);
    }

    // Randomize each p-box
    RandomizePbox(r, Pbox1);
    RandomizePbox(r, Pbox2);

    // Randomize rotations
    // Rotations must be distinct, non-zero, and have odd sum
    {
        int bits[WORD_BITS-1];
        r.Permutation(bits);
        int sum = 0;
        for (int j = 0; j < ROTATION_COUNT-1; j++)
        {
            Rotations[j] = bits[j] + 1;
            sum += Rotations[j];
        }
        for (int j = ROTATION_COUNT-1; ; j++)
        {
            if ((bits[j] + 1 + sum) % 2)
            {
                Rotations[ROTATION_COUNT-1] = bits[j] + 1;
                break;
            }
        }
    }

    // Randomize each round key
    for (int i = 0; i < ROUNDS; i++)
        RoundKey[i] = r.Next(1 << STATE_SIZE);
}

void OdoCrypt::Encrypt(char cipher[DIGEST_SIZE], const char plain[DIGEST_SIZE]) const
{
    uint64_t state[STATE_SIZE];
    Unpack(state, plain);
    PreMix(state);
    for (int round = 0; round < ROUNDS; round++)
    {
        ApplyPbox(state, Pbox1);
        ApplySboxes(state, Sbox1, Sbox2);
        ApplyPbox(state, Pbox2);
        ApplyRotations(state, Rotations);
        ApplyRoundKey(state, RoundKey[round]);
    }
    Pack(state, cipher);
}

template<class T, size_t sz1, size_t sz2>
void InvertMapping(T (&res)[sz1][sz2], const T (&mapping)[sz1][sz2])
{
    for (size_t i = 0; i < sz1; i++)
    for (size_t j = 0; j < sz2; j++)
        res[i][mapping[i][j]] = j;
}

template<class T, size_t sz>
void Transpose(T (&res)[sz][sz], const T (&orig)[sz][sz])
{
    for (size_t i = 0; i < sz; i++)
    for (size_t j = 0; j < sz; j++)
        res[i][j] = orig[j][i];
}

void OdoCrypt::Decrypt(char plain[DIGEST_SIZE], const char cipher[DIGEST_SIZE]) const
{
    uint8_t invSbox1[SMALL_SBOX_COUNT][1 << SMALL_SBOX_WIDTH];
    uint16_t invSbox2[LARGE_SBOX_COUNT][1 << LARGE_SBOX_WIDTH];
    uint64_t invPbox1[STATE_SIZE][STATE_SIZE];
    uint64_t invPbox2[STATE_SIZE][STATE_SIZE];

    InvertMapping(invSbox1, Sbox1);
    InvertMapping(invSbox2, Sbox2);
    Transpose(invPbox1, Pbox1);
    Transpose(invPbox2, Pbox2);

    uint64_t state[STATE_SIZE];
    Unpack(state, cipher);
    for (int round = ROUNDS-1; round >= 0; round--)
    {
        ApplyRoundKey(state, RoundKey[round]);
        // LCM(STATE_SIZE, WORD_BITS)-1 is enough iterations, but this will do.
        for (int i = 0; i < STATE_SIZE*WORD_BITS-1; i++)
            ApplyRotations(state, Rotations);
        ApplyPbox(state, invPbox2);
        ApplySboxes(state, invSbox1, invSbox2);
        ApplyPbox(state, invPbox1);
    }
    PreMix(state);
    Pack(state, plain);
}

void OdoCrypt::Unpack(uint64_t state[STATE_SIZE], const char bytes[DIGEST_SIZE])
{
    std::fill(state, state+STATE_SIZE, 0);
    for (int i = 0; i < STATE_SIZE; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            state[i] |= (uint64_t)(uint8_t)bytes[8*i + j] << (8*j);
        }
    }
}

void OdoCrypt::Pack(const uint64_t state[STATE_SIZE], char bytes[DIGEST_SIZE])
{
    std::fill(bytes, bytes+DIGEST_SIZE, 0);
    for (int i = 0; i < STATE_SIZE; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            bytes[8*i + j] = (state[i] >> (8*j)) & 0xff;
        }
    }
}

void OdoCrypt::PreMix(uint64_t state[STATE_SIZE])
{
    uint64_t total = 0;
    for (int i = 0; i < STATE_SIZE; i++)
        total ^= state[i];
    total ^= total >> 32;
    for (int i = 0; i < STATE_SIZE; i++)
        state[i] ^= total;
}

void OdoCrypt::ApplySboxes(
    uint64_t state[STATE_SIZE],
    const uint8_t sbox1[SMALL_SBOX_COUNT][1 << SMALL_SBOX_WIDTH],
    const uint16_t sbox2[LARGE_SBOX_COUNT][1 << LARGE_SBOX_WIDTH])
{
    const static uint64_t MASK1 = (1 << SMALL_SBOX_WIDTH) - 1;
    const static uint64_t MASK2 = (1 << LARGE_SBOX_WIDTH) - 1;

    int smallSboxIndex = 0;
    for (int i = 0; i < STATE_SIZE; i++)
    {
        uint64_t next = 0;
        int pos = 0;
        int largeSboxIndex = i;
        for (int j = 0; j < SMALL_SBOX_COUNT / STATE_SIZE; j++)
        {
            next |= (uint64_t)sbox1[smallSboxIndex][(state[i] >> pos) & MASK1] << pos;
            pos += SMALL_SBOX_WIDTH;
            next |= (uint64_t)sbox2[largeSboxIndex][(state[i] >> pos) & MASK2] << pos;
            pos += LARGE_SBOX_WIDTH;
            smallSboxIndex++;
        }
        state[i] = next;
    }
}

void OdoCrypt::ApplyPbox(uint64_t state[STATE_SIZE], const uint64_t pbox[STATE_SIZE][STATE_SIZE])
{
    uint64_t next[STATE_SIZE] = {};
    for (int i = 0; i < STATE_SIZE; i++)
    for (int j = 0; j < STATE_SIZE; j++)
    {
        next[j] |= state[i] & pbox[i][j];
    }
    std::copy(next, next+STATE_SIZE, state);
}

inline uint64_t Rot(uint64_t x, int r)
{
    return r == 0 ? x : (x << r) ^ (x >> (64-r));
}

void OdoCrypt::ApplyRotations(uint64_t state[STATE_SIZE], const int rotations[ROTATION_COUNT])
{
    uint64_t next[STATE_SIZE];
    std::rotate_copy(state, state+1, state+STATE_SIZE, next);
    for (int i = 0; i < STATE_SIZE; i++)
    for (int j = 0; j < ROTATION_COUNT; j++)
    {
            next[i] ^= Rot(state[i], rotations[j]);
    }
    std::copy(next, next+STATE_SIZE, state);
}

void OdoCrypt::ApplyRoundKey(uint64_t state[STATE_SIZE], int roundKey)
{
    for (int i = 0; i < STATE_SIZE; i++)
        state[i] ^= (roundKey >> i) & 1;
}
