
@@ -7,28 +7,35 @@.>bitcoin-digibyte
#define HASH_ODO

#include "uint256.h"
#include "scrypt.h"
#include "odocrypt.h"

extern "C" {
    #include "KeccakP-800-SnP.h"
}
#include "odo_sha256_param_gen.h"
#include "sha256.h"

template<typename T1>
inline uint256 HashOdo(const T1 pbegin, const T1 pend, uint32_t key)
{
    char cipher[KeccakP800_stateSizeInBytes] = {};
    char cipher[OdoCrypt::DIGEST_SIZE] = {};
    uint256 hash;

    size_t len = (pend - pbegin) * sizeof(pbegin[0]);
    assert(len <= OdoCrypt::DIGEST_SIZE);
    assert(OdoCrypt::DIGEST_SIZE < KeccakP800_stateSizeInBytes);
    memcpy(cipher, static_cast<const void*>(&pbegin[0]), len);
    cipher[len] = 1;

    OdoCrypt(key).Encrypt(cipher, cipher);
    KeccakP800_Permute_12rounds(cipher);
    memcpy(&hash, cipher, hash.size());

    ODO_SHA256_PARAM_GEN param(key);
    CSHA256 sha256(param.sha256_initial_hash_value, param.k256);

    uint8_t ucipher[OdoCrypt::DIGEST_SIZE] = {};
    for(size_t i = 0; i < OdoCrypt::DIGEST_SIZE; i++){
        ucipher[i] = cipher[i];
    }
    sha256.Write(ucipher, (size_t)(OdoCrypt::DIGEST_SIZE));

    uint8_t sha256_out[CSHA256::OUTPUT_SIZE];
    sha256.Finalize(sha256_out);

    memcpy(hash, sha256_out, hash.size());

    return hash;
