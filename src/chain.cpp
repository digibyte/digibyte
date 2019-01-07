// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The DigiByte Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chain.h>
#include <chainparams.h>

#include <txdb.h>
extern std::unique_ptr<CBlockTreeDB> pblocktree;

/* Low Memory Mode */
CBlockIndexRawPtr CBlockIndexProxy::loadFromDB(const uint256* hash) {
    std::unique_ptr<CDBIterator> pcursor(pblocktree->NewIterator());
    pcursor->Seek(std::make_pair('b', *hash));
    
    if (pcursor->Valid()) {
        std::pair<char, uint256> key;
        if (pcursor->GetKey(key) && key.first == 'b') {
            CDiskBlockIndex diskindex;
            if (pcursor->GetValue(diskindex)) {
                // Construct block index object

                CBlockIndexRawPtr pindexNew(new CBlockIndex());

                uint256 block_hash(diskindex.GetBlockHash());
                pindexNew->phashBlock     = &block_hash;

                pindexNew->pprev          = diskindex.hashPrev;
                pindexNew->nHeight        = diskindex.nHeight;
                pindexNew->nFile          = diskindex.nFile;
                pindexNew->nDataPos       = diskindex.nDataPos;
                pindexNew->nUndoPos       = diskindex.nUndoPos;
                pindexNew->nVersion       = diskindex.nVersion;
                pindexNew->hashMerkleRoot = diskindex.hashMerkleRoot;
                pindexNew->nTime          = diskindex.nTime;
                pindexNew->nBits          = diskindex.nBits;
                pindexNew->nNonce         = diskindex.nNonce;
                pindexNew->nStatus        = diskindex.nStatus;
                pindexNew->nTx            = diskindex.nTx;

                return pindexNew;
            }
        }
    }

    return nullptr;
}

// void CBlockIndexProxy::operator=(const CBlockIndexRawPtr newVal) {
//     resetPtr();
//     if (newVal) {
//         val = new uint256(*newVal->phashBlock);
//     }
// }

void CBlockIndexProxy::operator=(const uint256& hash) {
    resetPtr();
    val = new uint256(hash);
}

void CBlockIndexProxy::resetPtr() {
    if (val) {
        delete val;
        val = nullptr;
    }
}

/**
 * CChain implementation
 */
void CChain::SetTip(CBlockIndexConstPtr pindex) {
    if (pindex == nullptr) {
        vChain.clear();
        return;
    }
    vChain.resize(pindex->nHeight + 1);
    while (pindex && vChain[pindex->nHeight] != pindex) {
        vChain[pindex->nHeight] = pindex;
        pindex = pindex->pprev;
    }
}

CBlockLocator CChain::GetLocator(CBlockIndexConstPtr pindex) const {
    int nStep = 1;
    std::vector<uint256> vHave;
    vHave.reserve(32);

    if (!pindex)
        pindex = Tip();
    while (pindex) {
        vHave.push_back(pindex->GetBlockHash());
        // Stop when we have added the genesis block.
        if (pindex->nHeight == 0)
            break;
        // Exponentially larger steps back, plus the genesis block.
        int nHeight = std::max(pindex->nHeight - nStep, 0);
        if (Contains(pindex)) {
            // Use O(1) CChain index if possible.
            pindex = (*this)[nHeight];
        } else {
            // Otherwise, use O(log n) skiplist.
            pindex = pindex->GetAncestor(nHeight);
        }
        if (vHave.size() > 10)
            nStep *= 2;
    }

    return CBlockLocator(vHave);
}

const CBlockIndexPtr CChain::FindFork(CBlockIndexConstPtr pindex) const {
    if (pindex == nullptr) {
        return nullptr;
    }
    if (pindex->nHeight > Height())
        pindex = pindex->GetAncestor(Height());
    while (pindex && !Contains(pindex))
        pindex = pindex->pprev;
    return pindex;
}

CBlockIndexPtr CChain::FindEarliestAtLeast(int64_t nTime) const
{
    std::vector<CBlockIndexPtr>::const_iterator lower = std::lower_bound(vChain.begin(), vChain.end(), nTime,
        [](CBlockIndexPtr pBlock, const int64_t& time) -> bool { return pBlock->GetBlockTimeMax() < time; });
    return (lower == vChain.end() ? nullptr : *lower);
}

/** Turn the lowest '1' bit in the binary representation of a number into a '0'. */
int static inline InvertLowestOne(int n) { return n & (n - 1); }

/** Compute what height to jump back to with the CBlockIndex::pskip pointer. */
int static inline GetSkipHeight(int height) {
    if (height < 2)
        return 0;

    // Determine which height to jump back to. Any number strictly lower than height is acceptable,
    // but the following expression seems to perform well in simulations (max 110 steps to go back
    // up to 2**18 blocks).
    return (height & 1) ? InvertLowestOne(InvertLowestOne(height - 1)) + 1 : InvertLowestOne(height);
}

CBlockIndexConstPtr CBlockIndex::GetAncestor(int height) const
{
    if (height > nHeight || height < 0) {
        return nullptr;
    }

    CBlockIndexConstPtr pindexWalk = this;
    int heightWalk = nHeight;
    while (heightWalk > height) {
        int heightSkip = GetSkipHeight(heightWalk);
        int heightSkipPrev = GetSkipHeight(heightWalk - 1);
        if (pindexWalk->pskip != nullptr &&
            (heightSkip == height ||
             (heightSkip > height && !(heightSkipPrev < heightSkip - 2 &&
                                       heightSkipPrev >= height)))) {
            // Only follow pskip if pprev->pskip isn't better than pskip->pprev.
            pindexWalk = pindexWalk->pskip;
            heightWalk = heightSkip;
        } else {
            assert(pindexWalk->pprev);
            pindexWalk = pindexWalk->pprev;
            heightWalk--;
        }
    }
    return pindexWalk;
}

CBlockIndexPtr CBlockIndex::GetAncestor(int height)
{
    #if MEMORY_MAPPING
        return static_cast<const CBlockIndex*>(this)->GetAncestor(height);
    #else
        return const_cast<CBlockIndexPtr>(static_cast<CBlockIndexConstPtr>(this)->GetAncestor(height));
    #endif
}

void CBlockIndex::BuildSkip()
{
    if (pprev)
        pskip = pprev->GetAncestor(GetSkipHeight(nHeight));
}

int GetAlgoWorkFactor(int nHeight, int algo) 
{
    if (nHeight < Params().GetConsensus().multiAlgoDiffChangeTarget)
    {
        return 1;
    }

    switch (algo)
    {
        case ALGO_SHA256D:
            return 1; 
        // work factor = absolute work ratio * optimisation factor
        case ALGO_SCRYPT:
            return 1024 * 4;
        case ALGO_GROESTL:
            return 64 * 8;
        case ALGO_SKEIN:
            return 4 * 6;
        case ALGO_QUBIT:
            return 128 * 8;
        default:
            return 1;
    }
}

arith_uint256 GetBlockProofBase(CBlockIndexConstPtr block)
{
    arith_uint256 bnTarget;
    bool fNegative;
    bool fOverflow;
    bnTarget.SetCompact(block->nBits, &fNegative, &fOverflow);
    if (fNegative || fOverflow || bnTarget == 0)
        return 0;
    // We need to compute 2**256 / (bnTarget+1), but we can't represent 2**256
    // as it's too large for a arith_uint256. However, as 2**256 is at least as large
    // as bnTarget+1, it is equal to ((2**256 - bnTarget - 1) / (bnTarget+1)) + 1,
    // or ~bnTarget / (nTarget+1) + 1.
    return (~bnTarget / (bnTarget + 1)) + 1;
}

// DGB 6.14.1 GetBlock Proof
arith_uint256 GetBlockProof(CBlockIndexConstPtr block)
{
    CBlockHeader header = block->GetBlockHeader();
    int nHeight = block->nHeight;
    const Consensus::Params& params = Params().GetConsensus();

    if (nHeight < params.workComputationChangeTarget)
    {
        arith_uint256 bnBlockWork = GetBlockProofBase(block);
        uint32_t nAlgoWork = GetAlgoWorkFactor(nHeight, header.GetAlgo());
        return bnBlockWork * nAlgoWork;
    }
    else
    {
        // Compute the geometric mean of the block targets for each individual algorithm.
        arith_uint256 bnAvgTarget(1);

        for (int i = 0; i < NUM_ALGOS; i++)
        {
            unsigned int nBits = GetNextWorkRequired(block->pprev, &header, params, i);
            arith_uint256 bnTarget;
            bool fNegative;
            bool fOverflow;
            bnTarget.SetCompact(nBits, &fNegative, &fOverflow);
            if (fNegative || fOverflow || bnTarget == 0)
                return 0;
            // Instead of multiplying them all together and then taking the
            // nth root at the end, take the roots individually then multiply so
            // that all intermediate values fit in 256-bit integers.
            bnAvgTarget *= bnTarget.ApproxNthRoot(NUM_ALGOS);
        }
        // see comment in GetProofBase
        arith_uint256 bnRes = (~bnAvgTarget / (bnAvgTarget + 1)) + 1;
        // Scale to roughly match the old work calculation
        bnRes <<= 7;

        return bnRes;
    }
}

int64_t GetBlockProofEquivalentTime(CBlockIndexConstPtr to, CBlockIndexConstPtr from, CBlockIndexConstPtr tip, const Consensus::Params& params)
{
    arith_uint256 r;
    int sign = 1;
    if (to->nChainWork > from->nChainWork) {
        r = to->nChainWork - from->nChainWork;
    } else {
        r = from->nChainWork - to->nChainWork;
        sign = -1;
    }
    r = r * arith_uint256(params.nPowTargetSpacing) / GetBlockProof(tip);
    if (r.bits() > 63) {
        return sign * std::numeric_limits<int64_t>::max();
    }
    return sign * r.GetLow64();
}

/** Find the last common ancestor two blocks have.
 *  Both pa and pb must be non-nullptr. */
CBlockIndexConstPtr LastCommonAncestor(CBlockIndexConstPtr pa, CBlockIndexConstPtr pb) {
    if (pa->nHeight > pb->nHeight) {
        pa = pa->GetAncestor(pb->nHeight);
    } else if (pb->nHeight > pa->nHeight) {
        pb = pb->GetAncestor(pa->nHeight);
    }

    while (pa != pb && pa && pb) {
        pa = pa->pprev;
        pb = pb->pprev;
    }

    // Eventually all chain branches meet at the genesis block.
    assert(pa == pb);
    return pa;
}
