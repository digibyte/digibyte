// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The DigiByte Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DIGIBYTE_CONSENSUS_PARAMS_H
#define DIGIBYTE_CONSENSUS_PARAMS_H

#include "uint256.h"
#include <map>
#include <string>

namespace Consensus {

enum DeploymentPos
{
    DEPLOYMENT_TESTDUMMY,
    DEPLOYMENT_CSV, // Deployment of BIP68, BIP112, and BIP113.
    DEPLOYMENT_SEGWIT, // Deployment of BIP141, BIP143, and BIP147.
    DEPLOYMENT_NVERSIONBIPS, // Deployment of BIP34, BIP65, and BIP66.
    //DEPLOYMENT_EQUIHASH, // Equihash algo swap
    //DEPLOYMENT_ETHASH, // Ethash algo swap
    // NOTE: Also add new deployments to VersionBitsDeploymentInfo in versionbits.cpp
    MAX_VERSION_BITS_DEPLOYMENTS
};

/**
 * Struct for each individual consensus rule change using BIP9.
 */
struct BIP9Deployment {
    /** Bit position to select the particular bit in nVersion. */
    int bit;
    /** Start MedianTime for version bits miner confirmation. Can be a date in the past */
    int64_t nStartTime;
    /** Timeout/expiry MedianTime for the deployment attempt. */
    int64_t nTimeout;
};

/**
 * Parameters that influence chain consensus.
 */
struct Params {
    uint256 hashGenesisBlock;
    int nSubsidyHalvingInterval;
    
    /**
     * Minimum blocks including miner confirmation of the total of 2016 blocks in a retargeting period,
     * (nPowTargetTimespan / nPowTargetSpacing) which is also used for BIP9 deployments.
     * Examples: 1916 for 95%, 1512 for testchains.
     */
    uint32_t nRuleChangeActivationThreshold;
    uint32_t nMinerConfirmationWindow;
    BIP9Deployment vDeployments[MAX_VERSION_BITS_DEPLOYMENTS];
    /** Proof of work parameters */
    uint256 powLimit;
    bool fPowAllowMinDifficultyBlocks;
    bool fPowNoRetargeting;
    bool fRbfEnabled;
    int64_t nPowTargetSpacing;
    int64_t nPowTargetTimespan;
    int64_t DifficultyAdjustmentInterval() const { return nPowTargetTimespan / nPowTargetSpacing; }

    int64_t nTargetTimespan;
    int64_t nTargetSpacing;
    int64_t nInterval;
    int64_t nDiffChangeTarget;
    int64_t nTargetTimespanRe;
    int64_t nTargetSpacingRe;
    int64_t nIntervalRe;
    int64_t patchBlockRewardDuration;
    int64_t patchBlockRewardDuration2;

	int64_t nAveragingInterval;
    int64_t multiAlgoTargetSpacing;
	int64_t multiAlgoTargetSpacingV4;
    int64_t nAveragingTargetTimespan;
	int64_t nAveragingTargetTimespanV4;

	int64_t nMaxAdjustDown;
	int64_t nMaxAdjustUp;
	int64_t nMaxAdjustDownV3;
	int64_t nMaxAdjustUpV3;
	int64_t nMaxAdjustDownV4;
	int64_t nMaxAdjustUpV4;

	int64_t nMinActualTimespan;
	int64_t nMaxActualTimespan;
	int64_t nMinActualTimespanV3;
	int64_t nMaxActualTimespanV3;
	int64_t nMinActualTimespanV4;
	int64_t nMaxActualTimespanV4;

	int64_t nLocalTargetAdjustment;
	int64_t nLocalDifficultyAdjustment;

	int64_t multiAlgoDiffChangeTarget;
	int64_t alwaysUpdateDiffChangeTarget;
	int64_t workComputationChangeTarget;


    uint256 nMinimumChainWork;
    uint256 defaultAssumeValid;
    bool EnableRBF() const { return fRbfEnabled; }
};
} // namespace Consensus

#endif // DIGIBYTE_CONSENSUS_PARAMS_H
