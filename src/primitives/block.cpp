// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The DigiByte Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <primitives/block.h>
#include <utilstrencodings.h>
#include <crypto/common.h>
#include <crypto/hashgroestl.h>
#include <crypto/hashodo.h>
#include <crypto/hashqubit.h>
#include <crypto/hashskein.h>
#include <crypto/scrypt.h>
#include <consensus/consensus.h>
#include <chainparams.h>
#include <util.h>
#include <hash.h>
#include <tinyformat.h>
#include <utilstrencodings.h>
#include <crypto/common.h>
#include <arith_uint256.h>

#include <unordered_map>

uint256 CBlockHeader::GetHash() const
{
    return SerializeHash(*this);
}

struct HeaderHash
{
    size_t operator() (const CBlockHeader& header) const
    {
        return header.nTime;
    }
};

struct HeaderEqual
{
    bool operator() (const CBlockHeader& lhs, const CBlockHeader& rhs) const
    {
        return
                lhs.nVersion == rhs.nVersion &&
                lhs.hashPrevBlock == rhs.hashPrevBlock &&
                lhs.hashMerkleRoot == rhs.hashMerkleRoot &&
                lhs.nTime == rhs.nTime &&
                lhs.nBits == rhs.nBits &&
                lhs.nNonce == rhs.nNonce;
    }
};

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
        // In version 6 and below, this version mask is unused.  However, nodes
        // running version 6 will happily accept a block with this version mask,
        // and just treat it like a normal SCRYPT block.  For this reason, if we
        // were to simply return ALGO_ODO here, it would be possible for a
        // malicious miner to cause a chain-split before the hard fork by
        // submitting such a block with a valid SCRYPT proof-of-work.
        //
        // This would be an easily solved problem if we had access to the block
        // height here, but we don't.  The best alternative I could come up with
        // is to check the proof-of-work here.  If its proof-of-work is valid
        // as a SCRYPT block, but not as an ODO block, return ALGO_SCRYPT,
        // otherwise return ALGO_ODO.  It's technically possible for a malicious
        // miner to cause a similar chain-split by mining a block where both
        // proof-of-works are valid, but at current mining difficulties this
        // would require around 2^96 hashes.
        //
        // This entire code block can be removed once a post hard-fork block has
        // been checkpointed.
        {
            // GetAlgo() will be called hundreds of times on the same block, so
            // it is absolutely necessary to make sure it remains fast.
            static std::mutex mutex;
            static std::unordered_map<CBlockHeader, int, HeaderHash, HeaderEqual> cache;

            {
                std::unique_lock<std::mutex> guard(mutex);
                auto it = cache.find(*this);
                if (it != cache.end())
                    return it->second;
            }

            arith_uint256 bnTarget;
            bnTarget.SetCompact(nBits);

            int result = ALGO_ODO;
            if (UintToArith256(GetPoWAlgoHash(ALGO_ODO)) > bnTarget &&
                UintToArith256(GetPoWAlgoHash(ALGO_SCRYPT)) <= bnTarget)
            {
                result = ALGO_SCRYPT;
            }

            {
                std::unique_lock<std::mutex> guard(mutex);
                cache.insert(std::make_pair(*this, result));
                return result;
            }
        }
            return ALGO_ODO;
    }
    // We can't yet return ALGO_UNKNOWN here for the same reasons as the above
    // comment.  After the hard-fork block height, such blocks will be rejected
    // in ContextualCheckBlockHeader.  Once a post hard-fork block has been
    // checkpointed, this code can then be replaced by "return ALGO_UNKNOWN".
    return ALGO_SCRYPT;
}

uint32_t OdoKey(const Consensus::Params& params, uint32_t nTime)
{
    uint32_t nShapechangeInterval = params.nOdoShapechangeInterval;
    return nTime - nTime % nShapechangeInterval;

}

uint256 CBlockHeader::GetPoWAlgoHash(int algo) const
{
    // This assert can be added back after the weird stuff in GetAlgo() is
    // removed
    //assert(algo == GetAlgo()); // why is this even an argument?
    switch (algo)
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
            uint32_t key = OdoKey(Params().GetConsensus(), nTime);
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

std::string CBlock::ToString() const
{
    std::stringstream s;
    s << strprintf("CBlock(hash=%s, ver=0x%08x, pow_algo=%d, pow_hash=%s, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%u, nBits=%08x, nNonce=%u, vtx=%u)\n",
        GetHash().ToString(),
        nVersion,
        GetAlgo(),
        GetPoWAlgoHash(GetAlgo()).ToString(),
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

int64_t GetBlockWeight(const CBlock& block)
{
    // This implements the weight = (stripped_size * 4) + witness_size formula,
    // using only serialization with and without witness data. As witness_size
    // is equal to total_size - stripped_size, this formula is identical to:
    // weight = (stripped_size * 3) + total_size.
    return ::GetSerializeSize(block, SER_NETWORK, PROTOCOL_VERSION | SERIALIZE_TRANSACTION_NO_WITNESS) * (WITNESS_SCALE_FACTOR - 1) + ::GetSerializeSize(block, SER_NETWORK, PROTOCOL_VERSION);
}
