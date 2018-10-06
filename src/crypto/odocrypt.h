// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The DigiByte developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef ODO_CRYPT
#define ODO_CRYPT

#include <stdint.h>

class OdoCrypt
{
public:
    const static int DIGEST_SIZE = 81;
    const static int ROUNDS = 96;
    const static int ROUNDKEY_BITS = 8;
    const static int SBOX_WIDTH = 6;
    const static int DIGEST_BITS = 8*DIGEST_SIZE;
    const static int SBOX_VALUES = 1 << SBOX_WIDTH;
    const static int STATE_SIZE = DIGEST_BITS / SBOX_WIDTH;

    OdoCrypt(uint32_t key);

    void Encrypt(char cipher[DIGEST_SIZE], const char plain[DIGEST_SIZE]) const;

    // Encrypt 64 messages simultaneously
    void EncryptBitsliced(char cipher[64][DIGEST_SIZE], const char plain[64][DIGEST_SIZE]) const;

    // test-only, proves that this really is a permutation function
    void Decrypt(char plain[DIGEST_SIZE], const char cipher[DIGEST_SIZE]) const;

private:
    uint8_t Sbox[STATE_SIZE][SBOX_VALUES];
    uint8_t InvSbox[STATE_SIZE][SBOX_VALUES];
    int Pbox[SBOX_WIDTH][STATE_SIZE];
    int InvPbox[SBOX_WIDTH][STATE_SIZE];
    uint8_t RoundKey[ROUNDS];

    // Pack/unpack bytes into internal state
    static void Unpack(uint8_t state[STATE_SIZE], const char bytes[DIGEST_SIZE]);
    static void Pack(const uint8_t state[STATE_SIZE], char bytes[DIGEST_SIZE]);

    // Apply the appropriate S-boxes or P-boxes to the state
    static void ApplySbox(uint8_t state[STATE_SIZE], const uint8_t sbox[STATE_SIZE][SBOX_VALUES]);
    static void ApplyPbox(uint8_t state[STATE_SIZE], const int pbox[SBOX_WIDTH][STATE_SIZE]);

    // Apply round key. Involution.
    static void ApplyRoundKey(uint8_t state[STATE_SIZE], int roundKey);

    // Bitsliced versions of the above
    static void UnpackBitsliced(uint64_t state[DIGEST_BITS], const char bytes[64][DIGEST_SIZE]);
    static void PackBitsliced(uint64_t state[DIGEST_BITS], char bytes[64][DIGEST_SIZE]);
    static void ApplySboxBitsliced(uint64_t state[SBOX_WIDTH], const uint8_t sbox[SBOX_VALUES]);
    static void ApplyPboxBitsliced(uint64_t state[DIGEST_BITS], const int pbox[SBOX_WIDTH][STATE_SIZE]);
    static void ApplyRoundKeyBitsliced(uint64_t state[DIGEST_BITS], int roundKey);
};

#endif
