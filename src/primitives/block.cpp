// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2020 The Bitcoin Core developers
// Copyright (c) 2014-2020 The DigiByte Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <primitives/block.h>
#include <crypto/common.h>
#include <crypto/hashgroestl.h>
#include <crypto/hashodo.h>
#include <crypto/hashqubit.h>
#include <crypto/hashskein.h>
#include <crypto/scrypt.h>
#include <consensus/consensus.h>
#include <chainparams.h>
#include <hash.h>
#include <tinyformat.h>
#include <arith_uint256.h>

uint256 CBlockHeader::GetHash() const
{
    return SerializeHash(*this);
}

int CBlockHeader::GetAlgo() const
{
    switch (nVersion & BLOCK_VERSION_ALGO)
    {
        case BLOCK_VERSION_SCRYPT:
            return ALGO_SCRYPT;
        case BLOCK_VERSION_SHA256D:
            return ALGO_SHA256D;
        case BLOCK_VERSION_GROESTL:
            return ALGO_GROESTL;
        case BLOCK_VERSION_SKEIN:
            return ALGO_SKEIN;
        case BLOCK_VERSION_QUBIT:
            return ALGO_QUBIT;
        //case BLOCK_VERSION_EQUIHASH:
            //return ALGO_EQUIHASH;
        //case BLOCK_VERSION_ETHASH:
            //return ALGO_ETHASH;
        case BLOCK_VERSION_ODO:
            return ALGO_ODO;
    }
    return ALGO_UNKNOWN;
}

uint32_t OdoKey(const Consensus::Params& params, uint32_t nTime)
{
    uint32_t nShapechangeInterval = params.nOdoShapechangeInterval;
    return nTime - nTime % nShapechangeInterval;

}

uint256 CBlockHeader::GetPoWAlgoHash(const Consensus::Params& params) const
{
    switch (GetAlgo())
    {
        case ALGO_SHA256D:
            return GetHash();
        case ALGO_SCRYPT:
        {
            uint256 thash;
            scrypt_1024_1_1_256(BEGIN(nVersion), BEGIN(thash));
            return thash;
        }
        case ALGO_GROESTL:
            return HashGroestl(BEGIN(nVersion), END(nNonce));
        case ALGO_SKEIN:
            return HashSkein(BEGIN(nVersion), END(nNonce));
        case ALGO_QUBIT:
            return HashQubit(BEGIN(nVersion), END(nNonce));
        //case ALGO_EQUIHASH:
            //return HashEquihash(BEGIN(nVersion), END(nNonce));
        //case ALGO_ETHASH:
            //return HashEthash(BEGIN(nVersion), END(nNonce));
        case ALGO_ODO:
        {
            uint32_t key = OdoKey(params, nTime);
            return HashOdo(BEGIN(nVersion), END(nNonce), key);
        }
        case ALGO_UNKNOWN:
            // This block will be rejected anyway, but returning an always-invalid
            // PoW hash will allow it to be rejected sooner.
            return ArithToUint256(~arith_uint256(0));
    }
    assert(false);
    return GetHash();
}

std::string CBlock::ToString(const Consensus::Params& params) const
{
    std::stringstream s;
    s << strprintf("CBlock(hash=%s, ver=0x%08x, pow_algo=%d, pow_hash=%s, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%u, nBits=%08x, nNonce=%u, vtx=%u)\n",
        GetHash().ToString(),
        nVersion,
        GetAlgo(),
        GetPoWAlgoHash(params).ToString(),
        hashPrevBlock.ToString(),
        hashMerkleRoot.ToString(),
        nTime, nBits, nNonce,
        vtx.size());
    for (const auto& tx : vtx) {
        s << "  " << tx->ToString() << "\n";
    }
    return s.str();
}

std::string GetAlgoName(int Algo)
{
    switch (Algo)
    {
        case ALGO_SHA256D:
            return std::string("sha256d");
        case ALGO_SCRYPT:
            return std::string("scrypt");
        case ALGO_GROESTL:
            return std::string("groestl");
        case ALGO_SKEIN:
            return std::string("skein");
        case ALGO_QUBIT:
            return std::string("qubit");
        //case ALGO_EQUIHASH:
            //return std::string("equihash");
        //case ALGO_ETHASH:
            //return std::string("ethash");
        case ALGO_ODO:
            return std::string("odo");
    }
    return std::string("unknown");
}

int GetAlgoByName(std::string strAlgo, int fallback)
{
    transform(strAlgo.begin(),strAlgo.end(),strAlgo.begin(),::tolower);
    if (strAlgo == "sha" || strAlgo == "sha256" || strAlgo == "sha256d")
        return ALGO_SHA256D;
    else if (strAlgo == "scrypt")
        return ALGO_SCRYPT;
    else if (strAlgo == "groestl" || strAlgo == "groestlsha2")
        return ALGO_GROESTL;
    else if (strAlgo == "skein" || strAlgo == "skeinsha2")
        return ALGO_SKEIN;
    else if (strAlgo == "q2c" || strAlgo == "qubit")
        return ALGO_QUBIT;
    //else if (strAlgo == "equihash")
        //return ALGO_EQUIHASH;
    //else if (strAlgo == "ethash")
        //return ALGO_ETHASH;
    else if (strAlgo == "odo" || strAlgo == "odosha3")
        return ALGO_ODO;
    else
        return fallback;
}
