// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2020 The Bitcoin Core developers
// Copyright (c) 2014-2020 The DigiByte Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DIGIBYTE_PRIMITIVES_BLOCK_H
#define DIGIBYTE_PRIMITIVES_BLOCK_H

#include <primitives/transaction.h>
#include <serialize.h>
#include <uint256.h>

namespace Consensus { struct Params; }

enum { 
    ALGO_UNKNOWN = -1,
    ALGO_SHA256D  = 0,
    ALGO_SCRYPT   = 1,
    ALGO_GROESTL  = 2,
    ALGO_SKEIN    = 3,
    ALGO_QUBIT    = 4,
    //ALGO_EQUIHASH = 5,
    //ALGO_ETHASH   = 6,
    ALGO_ODO      = 7,
    NUM_ALGOS_IMPL };

const int NUM_ALGOS = 5;

enum {
    // primary version
    BLOCK_VERSION_DEFAULT        = 2, 

    // algo
    BLOCK_VERSION_ALGO           = (15 << 8),
    BLOCK_VERSION_SCRYPT         = (0 << 8),
    BLOCK_VERSION_SHA256D        = (2 << 8),
    BLOCK_VERSION_GROESTL        = (4 << 8),
    BLOCK_VERSION_SKEIN          = (6 << 8),
    BLOCK_VERSION_QUBIT          = (8 << 8),
    //BLOCK_VERSION_EQUIHASH       = (10 << 8),
    //BLOCK_VERSION_ETHASH         = (12 << 8),
    BLOCK_VERSION_ODO            = (14 << 8),
};

std::string GetAlgoName(int Algo);

int GetAlgoByName(std::string strAlgo, int fallback);

inline int GetVersionForAlgo(int algo)
{
    switch(algo)
    {
        case ALGO_SHA256D:
            return BLOCK_VERSION_SHA256D;
        case ALGO_SCRYPT:
            return BLOCK_VERSION_SCRYPT;
        case ALGO_GROESTL:
            return BLOCK_VERSION_GROESTL;
        case ALGO_SKEIN:
            return BLOCK_VERSION_SKEIN;
        case ALGO_QUBIT:
            return BLOCK_VERSION_QUBIT;
        //case ALGO_EQUIHASH:
            //return BLOCK_VERSION_EQUIHASH;
        //case ALGO_ETHASH:
            //return BLOCK_VERSION_ETHASH;
        case ALGO_ODO:
            return BLOCK_VERSION_ODO;
        default:
            assert(false);
            return 0;
    }
}

uint32_t OdoKey(const Consensus::Params& params, uint32_t nTime);

/** Nodes collect new transactions into a block, hash them into a hash tree,
 * and scan through nonce values to make the block's hash satisfy proof-of-work
 * requirements.  When they solve the proof-of-work, they broadcast the block
 * to everyone and the block is added to the block chain.  The first transaction
 * in the block is a special one that creates a new coin owned by the creator
 * of the block.
 */
class CBlockHeader
{
public:
    // header
    int32_t nVersion;
    uint256 hashPrevBlock;
    uint256 hashMerkleRoot;
    uint32_t nTime;
    uint32_t nBits;
    uint32_t nNonce;

    CBlockHeader()
    {
        SetNull();
    }

    SERIALIZE_METHODS(CBlockHeader, obj) { READWRITE(obj.nVersion, obj.hashPrevBlock, obj.hashMerkleRoot, obj.nTime, obj.nBits, obj.nNonce); }

    void SetNull()
    {
        nVersion = 0;
        hashPrevBlock.SetNull();
        hashMerkleRoot.SetNull();
        nTime = 0;
        nBits = 0;
        nNonce = 0;
    }

    bool IsNull() const
    {
        return (nBits == 0);
    }

    // Set Algo to use
    inline void SetAlgo(int algo)
    {
        nVersion |= GetVersionForAlgo(algo);
    }
    
    int GetAlgo() const;

    uint256 GetHash() const;

    uint256 GetPoWAlgoHash(const Consensus::Params& params) const;

    int64_t GetBlockTime() const
    {
        return (int64_t)nTime;
    }
};


class CBlock : public CBlockHeader
{
public:
    // network and disk
    std::vector<CTransactionRef> vtx;

    // memory only
    mutable bool fChecked;

    CBlock()
    {
        SetNull();
    }

    CBlock(const CBlockHeader &header)
    {
        SetNull();
        *(static_cast<CBlockHeader*>(this)) = header;
    }

    SERIALIZE_METHODS(CBlock, obj)
    {
        READWRITEAS(CBlockHeader, obj);
        READWRITE(obj.vtx);
    }

    void SetNull()
    {
        CBlockHeader::SetNull();
        vtx.clear();
        fChecked = false;
    }

    CBlockHeader GetBlockHeader() const
    {
        CBlockHeader block;
        block.nVersion       = nVersion;
        block.hashPrevBlock  = hashPrevBlock;
        block.hashMerkleRoot = hashMerkleRoot;
        block.nTime          = nTime;
        block.nBits          = nBits;
        block.nNonce         = nNonce;
        return block;
    }

    std::string ToString(const Consensus::Params& params) const;
};

/** Describes a place in the block chain to another node such that if the
 * other node doesn't have the same branch, it can find a recent common trunk.
 * The further back it is, the further before the fork it may be.
 */
struct CBlockLocator
{
    std::vector<uint256> vHave;

    CBlockLocator() {}

    explicit CBlockLocator(const std::vector<uint256>& vHaveIn) : vHave(vHaveIn) {}

    SERIALIZE_METHODS(CBlockLocator, obj)
    {
        int nVersion = s.GetVersion();
        if (!(s.GetType() & SER_GETHASH))
            READWRITE(nVersion);
        READWRITE(obj.vHave);
    }

    void SetNull()
    {
        vHave.clear();
    }

    bool IsNull() const
    {
        return vHave.empty();
    }
};

#endif // DIGIBYTE_PRIMITIVES_BLOCK_H
