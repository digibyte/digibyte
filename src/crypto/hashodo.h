// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The DigiByte developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HASH_ODO
#define HASH_ODO

#include "uint256.h"
#include "odocrypt.h"
extern "C" {
#include "KeccakP-800-SnP.h"
}

template<typename T1>
inline uint256 HashOdo(const T1 pbegin, const T1 pend, uint32_t key)
{
    char cipher[KeccakP800_stateSizeInBytes] = {};
    uint256 hash;

    size_t len = (pend - pbegin) * sizeof(pbegin[0]);
    assert(len <= OdoCrypt::DIGEST_SIZE);
    assert(OdoCrypt::DIGEST_SIZE < KeccakP800_stateSizeInBytes);
    memcpy(cipher, static_cast<const void*>(&pbegin[0]), len);
    cipher[len] = 1;

    OdoCrypt(key).Encrypt(cipher, cipher);
    KeccakP800_Permute_12rounds(cipher);
    memcpy(hash.data(), cipher, hash.size());

    return hash;
}

#endif
