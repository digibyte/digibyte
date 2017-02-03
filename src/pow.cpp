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

unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params& params, int algo)
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
