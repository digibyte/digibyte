// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The DigiByte developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef HASH_ODO
#define HASH_ODO

#include "uint256.h"
#include "odocrypt.h"
#include "sph_keccak.h"

template<typename T1>
inline uint256 HashOdo(const T1 pbegin, const T1 pend, uint32_t key)

{
    char cipher[OdoCrypt::DIGEST_SIZE] = {};
    sph_keccak256_context ctx_keccak;
    uint256 hash;

    size_t len = (pend - pbegin) * sizeof(pbegin[0]);
    assert(len <= OdoCrypt::DIGEST_SIZE);
    memcpy(cipher, static_cast<const void*>(&pbegin[0]), len);
    OdoCrypt(key).Encrypt(cipher, cipher);

    sph_keccak256_init(&ctx_keccak);
    sph_keccak256 (&ctx_keccak, static_cast<const void*>(cipher), OdoCrypt::DIGEST_SIZE);
    sph_keccak256_close(&ctx_keccak, static_cast<void*>(&hash));

    return hash;
}

#endif
