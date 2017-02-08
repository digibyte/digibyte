// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "pow.h"

#include "arith_uint256.h"
#include "chain.h"
#include "primitives/block.h"
#include "uint256.h"

#include "util.h" //just for logs

unsigned int GetNextWorkRequiredV1(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params& params, int algo)
{
	// Find some place to put these
    int64_t nTargetTimespan =  0.10 * 24 * 60 * 60; // 2.4 hours
    int64_t nTargetSpacing = 60; // 60 seconds
    int64_t nInterval = nTargetTimespan / nTargetSpacing;
    int64_t nDiffChangeTarget = 67200;
    int64_t nTargetTimespanRe = 1*60; // 60 Seconds
    int64_t nTargetSpacingRe = 1*60; // 60 seconds
    int64_t nIntervalRe = nTargetTimespanRe / nTargetSpacingRe; // 1 block

    unsigned int nProofOfWorkLimit = UintToArith256(params.powLimit).GetCompact();
	int nHeight = pindexLast->nHeight + 1;
	bool fNewDifficultyProtocol = (nHeight >= nDiffChangeTarget);
	int blockstogoback = 0;

	//set default to pre-v2.0 values
	int64_t retargetTimespan = nTargetTimespan;
	//int64_t retargetSpacing = nTargetSpacing;
	int64_t retargetInterval = nInterval;

	// Genesis block
	if (pindexLast == NULL)
		return nProofOfWorkLimit;

	//if v2.0 changes are in effect for block num, alter retarget values
	if(fNewDifficultyProtocol) {
		LogPrintf("GetNextWorkRequired nActualTimespan Limiting\n");
		retargetTimespan = nTargetTimespanRe;
		//retargetSpacing = nTargetSpacingRe;
		retargetInterval = nIntervalRe;
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
	LogPrintf("nActualTimespan = %d  before bounds\n", nActualTimespan);

	// thanks to RealSolid & WDC for this code
	if(fNewDifficultyProtocol) {
		LogPrintf("GetNextWorkRequired nActualTimespan Limiting\n");
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
	LogPrintf("GetNextWorkRequired RETARGET\n");
	LogPrintf("nTargetTimespan = %d    nActualTimespan = %d\n", nTargetTimespan, nActualTimespan);
	LogPrintf("Before: %08x  %s\n", pindexLast->nBits, ArithToUint256(bnBefore).ToString());
	LogPrintf("After:  %08x  %s\n", bnNew.GetCompact(), ArithToUint256(bnNew).ToString());

	return bnNew.GetCompact();
}

unsigned int GetNextWorkRequiredV2(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params& params, int algo)
{

	// Find some place to put these
	static const int64_t nAveragingInterval = 10; // 10 blocks
	static const int64_t multiAlgoTargetSpacing = 30*5; // NUM_ALGOS * 30 seconds
	static const int64_t nAveragingTargetTimespan = nAveragingInterval * multiAlgoTargetSpacing; // 10* NUM_ALGOS * 30
	static const int64_t nMaxAdjustDown = 40; // 40% adjustment down
	static const int64_t nMaxAdjustUp = 20; // 20% adjustment up
	static const int64_t nMinActualTimespan = nAveragingTargetTimespan * (100 - nMaxAdjustUp) / 100;
	static const int64_t nMaxActualTimespan = nAveragingTargetTimespan * (100 + nMaxAdjustDown) / 100;

	unsigned int nProofOfWorkLimit = UintToArith256(params.powLimit).GetCompact();

	if (pindexLast == NULL)
		return nProofOfWorkLimit;

	LogPrintf("GetNextWorkRequired RETARGET\n");
	LogPrintf("Height (Before): %s\n", pindexLast->nHeight);

	// find previous block with same algo
	const CBlockIndex* pindexPrev = GetLastBlockIndexForAlgo(pindexLast, algo);

	// find first block in averaging interval
	// Go back by what we want to be nAveragingInterval blocks
	const CBlockIndex* pindexFirst = pindexPrev;
	for (int i = 0; pindexFirst && i < nAveragingInterval - 1; i++)
	{
		pindexFirst = pindexFirst->pprev;
		pindexFirst = GetLastBlockIndexForAlgo(pindexFirst, algo);
	}

	if (pindexFirst == NULL)
	{
		LogPrintf("Use default POW Limit\n");
		return nProofOfWorkLimit;
	}

	// Limit adjustment step
	int64_t nActualTimespan = pindexPrev->GetBlockTime() - pindexFirst->GetBlockTime();
	LogPrintf("nActualTimespan = %d before bounds\n", nActualTimespan);
	if (nActualTimespan < nMinActualTimespan)
		nActualTimespan = nMinActualTimespan;
	if (nActualTimespan > nMaxActualTimespan)
		nActualTimespan = nMaxActualTimespan;

	// Retarget

	arith_uint256 bnNew;
	bnNew.SetCompact(pindexPrev->nBits);
	bnNew *= nActualTimespan;
	bnNew /= nAveragingTargetTimespan;

	if (bnNew > UintToArith256(params.powLimit))
	{
		bnNew = UintToArith256(params.powLimit);
	}

	return bnNew.GetCompact();	
}

unsigned int GetNextWorkRequiredV3(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params& params, int algo)
{
	// Find some place to put these
	static const int64_t nAveragingInterval = 10; // 10 blocks
	static const int64_t multiAlgoTargetSpacing = 30*5; // NUM_ALGOS * 30 seconds
	static const int64_t nAveragingTargetTimespan = nAveragingInterval * multiAlgoTargetSpacing; // 10* NUM_ALGOS * 30
	static const int64_t nMaxAdjustDownV3 = 16; // 16% adjustment down
	static const int64_t nMaxAdjustUpV3 = 8; // 8% adjustment up
	static const int64_t nMinActualTimespanV3 = nAveragingTargetTimespan * (100 - nMaxAdjustUpV3) / 100;
	static const int64_t nMaxActualTimespanV3 = nAveragingTargetTimespan * (100 + nMaxAdjustDownV3) / 100;
	static const int64_t nLocalDifficultyAdjustment = 4; //difficulty adjustment per algo

	unsigned int nProofOfWorkLimit = UintToArith256(params.powLimit).GetCompact();

	// Genesis block
	if (pindexLast == NULL)
		return nProofOfWorkLimit;

	// find first block in averaging interval
	// Go back by what we want to be nAveragingInterval blocks per algo
	const CBlockIndex* pindexFirst = pindexLast;
	for (int i = 0; pindexFirst && i < NUM_ALGOS*nAveragingInterval; i++)
	{
		pindexFirst = pindexFirst->pprev;
	}
	const CBlockIndex* pindexPrevAlgo = GetLastBlockIndexForAlgo(pindexLast, algo);
	if (pindexPrevAlgo == NULL || pindexFirst == NULL)
		return nProofOfWorkLimit; // not enough blocks available

	// Limit adjustment step
	// Use medians to prevent time-warp attacks
	int64_t nActualTimespan = pindexLast->GetMedianTimePast() - pindexFirst->GetMedianTimePast();
	nActualTimespan = nAveragingTargetTimespan + (nActualTimespan - nAveragingTargetTimespan)/6;
	LogPrintf("  nActualTimespan = %d before bounds\n", nActualTimespan);
	if (nActualTimespan < nMinActualTimespanV3)
		nActualTimespan = nMinActualTimespanV3;
	if (nActualTimespan > nMaxActualTimespanV3)
		nActualTimespan = nMaxActualTimespanV3;

	// Global retarget
	arith_uint256 bnNew;
	bnNew.SetCompact(pindexPrevAlgo->nBits);
	bnNew *= nActualTimespan;
	bnNew /= nAveragingTargetTimespan;

	// Per-algo retarget
	int nAdjustments = pindexPrevAlgo->nHeight - pindexLast->nHeight + NUM_ALGOS - 1;
	if (nAdjustments > 0)
	{
		for (int i = 0; i < nAdjustments; i++)
		{
			bnNew *= 100;
			bnNew /= 100 + nLocalDifficultyAdjustment;
		}
	}
	if (nAdjustments < 0)
	{
		for (int i = 0; i < -nAdjustments; i++)
		{
			bnNew *= 100 + nLocalDifficultyAdjustment;
			bnNew /= 100;
		}
	}

	if (bnNew > UintToArith256(params.powLimit))
		bnNew = UintToArith256(params.powLimit);

	return bnNew.GetCompact();
}

unsigned int GetNextWorkRequiredV4(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params& params, int algo)
{
	// Find some place to put these
	static const int64_t nAveragingInterval = 10; // 10 blocks
	static const int64_t multiAlgoTargetSpacingV4 = 15*5; // NUM_ALGOS * 15 seconds
	static const int64_t nAveragingTargetTimespanV4 = nAveragingInterval * multiAlgoTargetSpacingV4; // 10 * NUM_ALGOS * 15
	static const int64_t nMaxAdjustDownV4 = 16;
	static const int64_t nMaxAdjustUpV4 = 8;
	static const int64_t nMinActualTimespanV4 = nAveragingTargetTimespanV4 * (100 - nMaxAdjustUpV4) / 100;
	static const int64_t nMaxActualTimespanV4 = nAveragingTargetTimespanV4 * (100 + nMaxAdjustDownV4) / 100;
	static const int64_t nLocalTargetAdjustment = 4; //target adjustment per algo

	unsigned int nProofOfWorkLimit = UintToArith256(params.powLimit).GetCompact();

	// Genesis block
	if (pindexLast == NULL)
		return nProofOfWorkLimit;

	// find first block in averaging interval
	// Go back by what we want to be nAveragingInterval blocks per algo
	const CBlockIndex* pindexFirst = pindexLast;
	for (int i = 0; pindexFirst && i < NUM_ALGOS*nAveragingInterval; i++)
	{
		pindexFirst = pindexFirst->pprev;
	}

	const CBlockIndex* pindexPrevAlgo = GetLastBlockIndexForAlgo(pindexLast, algo);
	if (pindexPrevAlgo == NULL || pindexFirst == NULL)
	{
		return nProofOfWorkLimit;
	}

	// Limit adjustment step
	// Use medians to prevent time-warp attacks
	int64_t nActualTimespan = pindexLast-> GetMedianTimePast() - pindexFirst->GetMedianTimePast();
	nActualTimespan = nAveragingTargetTimespanV4 + (nActualTimespan - nAveragingTargetTimespanV4)/4;

	if (nActualTimespan < nMinActualTimespanV4)
		nActualTimespan = nMinActualTimespanV4;
	if (nActualTimespan > nMaxActualTimespanV4)
		nActualTimespan = nMaxActualTimespanV4;

	//Global retarget
	arith_uint256 bnNew;
	bnNew.SetCompact(pindexPrevAlgo->nBits);

	bnNew *= nActualTimespan;
	bnNew /= nAveragingTargetTimespanV4;

	//Per-algo retarget
	int nAdjustments = pindexPrevAlgo->nHeight + NUM_ALGOS - 1 - pindexLast->nHeight;
	if (nAdjustments > 0)
	{
		for (int i = 0; i < nAdjustments; i++)
		{
			bnNew *= 100;
			bnNew /= (100 + nLocalTargetAdjustment);
		}
	}
	else if (nAdjustments < 0)//make it easier
	{
		for (int i = 0; i < -nAdjustments; i++)
		{
			bnNew *= (100 + nLocalTargetAdjustment);
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
	const int64_t multiAlgoDiffChangeTarget = 145000;
	const int64_t alwaysUpdateDiffChangeTarget = 400000;
	const int64_t workComputationChangeTarget = 1430000; 

	if (pindexLast->nHeight < multiAlgoDiffChangeTarget)
		return GetNextWorkRequiredV1(pindexLast, pblock, params, algo);
	else if (pindexLast->nHeight < alwaysUpdateDiffChangeTarget){
		LogPrintf("algo is %i", algo);
		return GetNextWorkRequiredV2(pindexLast, pblock, params, algo);
	} else if(pindexLast->nHeight < workComputationChangeTarget)
		return GetNextWorkRequiredV3(pindexLast, pblock, params, algo);
	else
		return GetNextWorkRequiredV4(pindexLast, pblock, params, algo);
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

const CBlockIndex* GetLastBlockIndexForAlgo(const CBlockIndex* pindex, int algo)
{
	for (;;)
	{
		if (!pindex)
			return NULL;
		if (pindex->GetAlgo() == algo)
			return pindex;
		pindex = pindex->pprev;
	}
	return NULL;
}