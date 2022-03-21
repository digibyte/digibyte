// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2020 The Bitcoin Core developers
// Copyright (c) 2014-2020 The DigiByte Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <pow.h>
#include <logging.h>
#include <arith_uint256.h>
#include <chain.h>
#include <primitives/block.h>
#include <uint256.h>
#include <chainparams.h>

inline unsigned int PowLimit(const Consensus::Params& params)
{
    return UintToArith256(params.powLimit).GetCompact();
}

unsigned int InitialDifficulty(const Consensus::Params& params, int algo)
{
    const auto& it = params.initialTarget.find(algo);
    if (it == params.initialTarget.end())
        return PowLimit(params);
    return UintToArith256(it->second).GetCompact();
}

unsigned int GetNextWorkRequiredV1(const CBlockIndex* pindexLast, const Consensus::Params& params, int algo)
{
    int nHeight = pindexLast->nHeight + 1;
    bool fNewDifficultyProtocol = (nHeight >= params.nDiffChangeTarget);
    int blockstogoback = 0;

    //set default to pre-v2.0 values
    int64_t retargetTimespan = params.nTargetTimespan;
    //int64_t retargetSpacing = nTargetSpacing;
    int64_t retargetInterval = params.nInterval;

    //if v2.0 changes are in effect for block num, alter retarget values
    if(fNewDifficultyProtocol && !params.fPowAllowMinDifficultyBlocks) {
        LogPrintf("GetNextWorkRequired nActualTimespan Limiting\n");
        retargetTimespan = params.nTargetTimespanRe;
        //retargetSpacing = nTargetSpacingRe;
        retargetInterval = params.nIntervalRe;
    }

    // Only change once per interval
    if ((pindexLast->nHeight+1) % retargetInterval != 0)
    {
        return pindexLast->nBits;
    }

    // DigiByte: This fixes an issue where a 51% attack can change difficulty at will.
    // Go back the full period unless it's the first retarget after genesis. Code courtesy of Art Forz
    blockstogoback = retargetInterval-1;
    if ((pindexLast->nHeight+1) != retargetInterval)
        blockstogoback = retargetInterval;

    // Go back by what we want to be 14 days worth of blocks
    const CBlockIndex* pindexFirst = pindexLast;
    for (int i = 0; pindexFirst && i < blockstogoback; i++)
        pindexFirst = pindexFirst->pprev;
    assert(pindexFirst);

    // Limit adjustment step
    int64_t nActualTimespan = pindexLast->GetBlockTime() - pindexFirst->GetBlockTime();

    // thanks to RealSolid & WDC for this code
    if(fNewDifficultyProtocol && !params.fPowAllowMinDifficultyBlocks) {
        if (nActualTimespan < (retargetTimespan - (retargetTimespan/4)) ) nActualTimespan = (retargetTimespan - (retargetTimespan/4));
        if (nActualTimespan > (retargetTimespan + (retargetTimespan/2)) ) nActualTimespan = (retargetTimespan + (retargetTimespan/2));
    }
    else {
        if (nActualTimespan < retargetTimespan/4) nActualTimespan = retargetTimespan/4;
        if (nActualTimespan > retargetTimespan*4) nActualTimespan = retargetTimespan*4;
    }

    arith_uint256 bnNew;
    arith_uint256 bnBefore;
    bnNew.SetCompact(pindexLast->nBits);
    bnBefore=bnNew;
    bnNew *= nActualTimespan;
    bnNew /= retargetTimespan;

    if (bnNew > UintToArith256(params.powLimit))
        bnNew = UintToArith256(params.powLimit);

    // debug print
    LogPrintf("nTargetTimespan = %d    nActualTimespan = %d\n", retargetTimespan, nActualTimespan);
    LogPrintf("Before: %08x  %s\n", pindexLast->nBits, ArithToUint256(bnBefore).ToString());
    LogPrintf("After:  %08x  %s\n", bnNew.GetCompact(), ArithToUint256(bnNew).ToString());

    return bnNew.GetCompact();
}

unsigned int GetNextWorkRequiredV2(const CBlockIndex* pindexLast, const Consensus::Params& params, int algo)
{
    LogPrintf("Height (Before): %s\n", pindexLast->nHeight);

    // find previous block with same algo
    const CBlockIndex* pindexPrev = GetLastBlockIndexForAlgo(pindexLast, params, algo);

    // find first block in averaging interval
    // Go back by what we want to be nAveragingInterval blocks
    const CBlockIndex* pindexFirst = pindexPrev;
    for (int i = 0; pindexFirst && i < params.nAveragingInterval - 1; i++)
    {
        pindexFirst = pindexFirst->pprev;
        pindexFirst = GetLastBlockIndexForAlgo(pindexFirst, params, algo);
    }

    if (pindexFirst == nullptr)
    {
        LogPrintf("Use default POW Limit\n");
        return InitialDifficulty(params, algo);
    }

    // Limit adjustment step
    int64_t nActualTimespan = pindexPrev->GetBlockTime() - pindexFirst->GetBlockTime();
    if (nActualTimespan < params.nMinActualTimespan)
        nActualTimespan = params.nMinActualTimespan;
    if (nActualTimespan > params.nMaxActualTimespan)
        nActualTimespan = params.nMaxActualTimespan;

    // Retarget

    arith_uint256 bnNew;
    bnNew.SetCompact(pindexPrev->nBits);
    bnNew *= nActualTimespan;
    bnNew /= params.nAveragingTargetTimespan;

    if (bnNew > UintToArith256(params.powLimit))
    {
        bnNew = UintToArith256(params.powLimit);
    }

    return bnNew.GetCompact();    
}

unsigned int GetNextWorkRequiredV3(const CBlockIndex* pindexLast, const Consensus::Params& params, int algo)
{
    // find first block in averaging interval
    // Go back by what we want to be nAveragingInterval blocks per algo
    const CBlockIndex* pindexFirst = pindexLast;
    for (int i = 0; pindexFirst && i < NUM_ALGOS*params.nAveragingInterval; i++)
    {
        pindexFirst = pindexFirst->pprev;
    }
    const CBlockIndex* pindexPrevAlgo = GetLastBlockIndexForAlgo(pindexLast, params, algo);
    if (pindexPrevAlgo == nullptr || pindexFirst == nullptr)
        return InitialDifficulty(params, algo); // not enough blocks available

    // Limit adjustment step
    // Use medians to prevent time-warp attacks
    int64_t nActualTimespan = pindexLast->GetMedianTimePast() - pindexFirst->GetMedianTimePast();
    nActualTimespan = params.nAveragingTargetTimespan + (nActualTimespan - params.nAveragingTargetTimespan)/6;
    if (nActualTimespan < params.nMinActualTimespanV3)
        nActualTimespan = params.nMinActualTimespanV3;
    if (nActualTimespan > params.nMaxActualTimespanV3)
        nActualTimespan = params.nMaxActualTimespanV3;

    // Global retarget
    arith_uint256 bnNew;
    bnNew.SetCompact(pindexPrevAlgo->nBits);
    bnNew *= nActualTimespan;
    bnNew /= params.nAveragingTargetTimespan;

    // Per-algo retarget
    int nAdjustments = pindexPrevAlgo->nHeight - pindexLast->nHeight + NUM_ALGOS - 1;
    if (nAdjustments > 0)
    {
        for (int i = 0; i < nAdjustments; i++)
        {
            bnNew *= 100;
            bnNew /= 100 + params.nLocalDifficultyAdjustment;
        }
    }
    if (nAdjustments < 0)
    {
        for (int i = 0; i < -nAdjustments; i++)
        {
            bnNew *= 100 + params.nLocalDifficultyAdjustment;
            bnNew /= 100;
        }
    }

    if (bnNew > UintToArith256(params.powLimit))
        bnNew = UintToArith256(params.powLimit);

    return bnNew.GetCompact();
}

unsigned int GetNextWorkRequiredV4(const CBlockIndex* pindexLast, const Consensus::Params& params, int algo)
{
    // find first block in averaging interval
    // Go back by what we want to be nAveragingInterval blocks per algo
    const CBlockIndex* pindexFirst = pindexLast;
    for (int i = 0; pindexFirst && i < NUM_ALGOS*params.nAveragingInterval; i++)
    {
        pindexFirst = pindexFirst->pprev;
    }

    const CBlockIndex* pindexPrevAlgo = GetLastBlockIndexForAlgo(pindexLast, params, algo);
    if (pindexPrevAlgo == nullptr || pindexFirst == nullptr)
    {
        return InitialDifficulty(params, algo);
    }

    // Limit adjustment step
    // Use medians to prevent time-warp attacks
    int64_t nActualTimespan = pindexLast-> GetMedianTimePast() - pindexFirst->GetMedianTimePast();
    nActualTimespan = params.nAveragingTargetTimespanV4 + (nActualTimespan - params.nAveragingTargetTimespanV4)/4;

    if (nActualTimespan < params.nMinActualTimespanV4)
        nActualTimespan = params.nMinActualTimespanV4;
    if (nActualTimespan > params.nMaxActualTimespanV4)
        nActualTimespan = params.nMaxActualTimespanV4;

    //Global retarget
    arith_uint256 bnNew;
    bnNew.SetCompact(pindexPrevAlgo->nBits);

    bnNew *= nActualTimespan;
    bnNew /= params.nAveragingTargetTimespanV4;

    //Per-algo retarget
    int nAdjustments = pindexPrevAlgo->nHeight + NUM_ALGOS - 1 - pindexLast->nHeight;
    if (nAdjustments > 0)
    {
        for (int i = 0; i < nAdjustments; i++)
        {
            bnNew *= 100;
            bnNew /= (100 + params.nLocalTargetAdjustment);
        }
    }
    else if (nAdjustments < 0)//make it easier
    {
        for (int i = 0; i < -nAdjustments; i++)
        {
            bnNew *= (100 + params.nLocalTargetAdjustment);
            bnNew /= 100;
        }
    }

    if (bnNew > UintToArith256(params.powLimit))
    {
        bnNew = UintToArith256(params.powLimit);
    }

    return bnNew.GetCompact();
}

unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params& params, int algo)
{
    // Genesis block
    if (pindexLast == nullptr)
        return InitialDifficulty(params, algo);

    if (params.fPowAllowMinDifficultyBlocks)
    {
        // Special difficulty rule for regtest:
        // Always allow min difficulty blocks if fEasyPow is set
        if (params.fEasyPow) {
            return PowLimit(params);
        }

        // Special difficulty rule for testnet:
        // If the new block's timestamp is more than 2 minutes
        // then allow mining of a min-difficulty block.
        if (pblock->nTime > pindexLast->nTime + params.nTargetSpacing*2)
            return PowLimit(params);
    }

    if (pindexLast->nHeight < params.multiAlgoDiffChangeTarget)
        return GetNextWorkRequiredV1(pindexLast, params, algo);
    else if (pindexLast->nHeight < params.alwaysUpdateDiffChangeTarget){
        return GetNextWorkRequiredV2(pindexLast, params, algo);
    } else if(pindexLast->nHeight < params.workComputationChangeTarget)
        return GetNextWorkRequiredV3(pindexLast, params, algo);
    else
        return GetNextWorkRequiredV4(pindexLast, params, algo);
}

unsigned int CalculateNextWorkRequired(const CBlockIndex* pindexLast, int64_t nFirstBlockTime, const Consensus::Params& params)
{
    if (params.fPowNoRetargeting)
        return pindexLast->nBits;

    // Limit adjustment step
    int64_t nActualTimespan = pindexLast->GetBlockTime() - nFirstBlockTime;
    if (nActualTimespan < params.nPowTargetTimespan/4)
        nActualTimespan = params.nPowTargetTimespan/4;
    if (nActualTimespan > params.nPowTargetTimespan*4)
        nActualTimespan = params.nPowTargetTimespan*4;

    // Retarget
    const arith_uint256 bnPowLimit = UintToArith256(params.powLimit);
    arith_uint256 bnNew;
    bnNew.SetCompact(pindexLast->nBits);
    bnNew *= nActualTimespan;
    bnNew /= params.nPowTargetTimespan;

    if (bnNew > bnPowLimit)
        bnNew = bnPowLimit;

    return bnNew.GetCompact();
}

bool CheckProofOfWork(uint256 hash, unsigned int nBits, const Consensus::Params& params)
{
    bool fNegative;
    bool fOverflow;
    arith_uint256 bnTarget;

    bnTarget.SetCompact(nBits, &fNegative, &fOverflow);

    // Check range
    if (fNegative || bnTarget == 0 || fOverflow || bnTarget > UintToArith256(params.powLimit))
        return false;

    // Check proof of work matches claimed amount
    if (UintToArith256(hash) > bnTarget)
        return false;

    return true;
}

const CBlockIndex* GetLastBlockIndexForAlgo(const CBlockIndex* pindex, const Consensus::Params& params, int algo)
{
    for (; pindex; pindex = pindex->pprev)
    {
        if (pindex->GetAlgo() != algo)
            continue;
        // ignore special min-difficulty testnet blocks
        if (params.fPowAllowMinDifficultyBlocks &&
            pindex->pprev &&
            pindex->nTime > pindex->pprev->nTime + params.nTargetSpacing*2)
        {
            continue;
        }
        return pindex;
    }
    return nullptr;
}

uint256 GetPoWAlgoHash(const CBlockHeader& block)
{
    return block.GetPoWAlgoHash(Params().GetConsensus());
}
