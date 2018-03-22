// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The DigiByte Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DIGIBYTE_PRIMITIVES_BLOCK_H
#define DIGIBYTE_PRIMITIVES_BLOCK_H

#include <primitives/transaction.h>
#include <serialize.h>
#include <uint256.h>
#include <util.h>

enum { 
    ALGO_SHA256D  = 0,
    ALGO_SCRYPT   = 1,
    ALGO_GROESTL  = 2,
    ALGO_SKEIN    = 3,
    ALGO_QUBIT    = 4,
    //ALGO_EQUIHASH = 5,
    //ALGO_ETHASH   = 6,
    NUM_ALGOS_IMPL };

const int NUM_ALGOS = 5;

enum {
    // primary version
    BLOCK_VERSION_DEFAULT        = 2, 

    // algo
    BLOCK_VERSION_ALGO           = (7 << 9),
    BLOCK_VERSION_SCRYPT         = (1 << 9),
    BLOCK_VERSION_SHA256D        = (1 << 9),
    BLOCK_VERSION_GROESTL        = (2 << 9),
    BLOCK_VERSION_SKEIN          = (3 << 9),
    BLOCK_VERSION_QUBIT          = (4 << 9),
    //BLOCK_VERSION_EQUIHASH       = (5 << 9),
    //BLOCK_VERSION_ETHASH         = (6 << 9),
};

std::string GetAlgoName(int Algo);


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

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action) {
        READWRITE(this->nVersion);
        READWRITE(hashPrevBlock);
        READWRITE(hashMerkleRoot);
        READWRITE(nTime);
        READWRITE(nBits);
        READWRITE(nNonce);
    }

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
        switch(algo)
        {
            case ALGO_SHA256D:
                nVersion |= BLOCK_VERSION_SHA256D;
                break;
            case ALGO_SCRYPT:
                nVersion |= BLOCK_VERSION_SCRYPT;
                break;
            case ALGO_GROESTL:
                nVersion |= BLOCK_VERSION_GROESTL;
                break;
            case ALGO_SKEIN:
                nVersion |= BLOCK_VERSION_SKEIN;
                break;
            case ALGO_QUBIT:
                nVersion |= BLOCK_VERSION_QUBIT;
                break;
            //case ALGO_EQUIHASH:
                //nVersion |= BLOCK_VERSION_EQUIHASH;
                //break;
            //case ALGO_ETHASH:
                //nVersion |= BLOCK_VERSION_ETHASH;
                //break;
            default:
                break;
        }
    }
    
    int GetAlgo() const;

    uint256 GetHash() const;

    uint256 GetPoWAlgoHash(int algo) const;

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

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action) {
        READWRITE(*static_cast<CBlockHeader*>(this));
        READWRITE(vtx);
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

    std::string ToString() const;
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

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action) {
        int nVersion = s.GetVersion();
        if (!(s.GetType() & SER_GETHASH))
            READWRITE(nVersion);
        READWRITE(vHave);
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
