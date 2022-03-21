// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2020 The Bitcoin Core developers
// Copyright (c) 2014-2020 The DigiByte Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DIGIBYTE_CONSENSUS_PARAMS_H
#define DIGIBYTE_CONSENSUS_PARAMS_H

#include <uint256.h>
#include <limits>
#include <map>

namespace Consensus {

/**
 * A buried deployment is one where the height of the activation has been hardcoded into
 * the client implementation long after the consensus change has activated. See BIP 90.
 */
enum BuriedDeployment : int16_t {
    // buried deployments get negative values to avoid overlap with DeploymentPos
    DEPLOYMENT_HEIGHTINCB = std::numeric_limits<int16_t>::min(),
    DEPLOYMENT_CLTV,
    DEPLOYMENT_DERSIG,
    DEPLOYMENT_CSV, // Deployment of BIP68, BIP112, and BIP113.
    DEPLOYMENT_SEGWIT, // Deployment of BIP141, BIP143, and BIP147.
    DEPLOYMENT_NVERSIONBIPS, // Deployment of BIP34, BIP65, and BIP66.
    DEPLOYMENT_RESERVEALGO,  // Reservation of version bits for future algos
    DEPLOYMENT_ODO, // Odo hard fork
    //DEPLOYMENT_EQUIHASH, // Equihash algo swap
    //DEPLOYMENT_ETHASH, // Ethash algo swap
};
constexpr bool ValidDeployment(BuriedDeployment dep) { return dep <= DEPLOYMENT_ODO; }

enum DeploymentPos : uint16_t {
    DEPLOYMENT_TESTDUMMY,
    DEPLOYMENT_TAPROOT, // Deployment of Schnorr/Taproot (BIPs 340-342)
    // NOTE: Also add new deployments to VersionBitsDeploymentInfo in deploymentinfo.cpp
    MAX_VERSION_BITS_DEPLOYMENTS
};
constexpr bool ValidDeployment(DeploymentPos dep) { return DEPLOYMENT_TESTDUMMY <= dep && dep <= DEPLOYMENT_TAPROOT; }

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
    /** If lock in occurs, delay activation until at least this block
     *  height.  Note that activation will only occur on a retarget
     *  boundary.
     */
    int min_activation_height{0};

    /** Constant for nTimeout very far in the future. */
    static constexpr int64_t NO_TIMEOUT = std::numeric_limits<int64_t>::max();

    /** Special value for nStartTime indicating that the deployment is always active.
     *  This is useful for testing, as it means tests don't need to deal with the activation
     *  process (which takes at least 3 BIP9 intervals). Only tests that specifically test the
     *  behaviour during activation cannot use this. */
    static constexpr int64_t ALWAYS_ACTIVE = -1;

    /** Special value for nStartTime indicating that the deployment is never active.
     *  This is useful for integrating the code changes for a new feature
     *  prior to deploying it on some or all networks. */
    static constexpr int64_t NEVER_ACTIVE = -2;
};

/**
 * Parameters that influence chain consensus.
 */
struct Params {
    uint256 hashGenesisBlock;
    int nSubsidyHalvingInterval;
    /* Block hash that is excepted from BIP16 enforcement */
    uint256 BIP16Exception;
    /** Block height and hash at which BIP34 becomes active */
    int BIP34Height;
    uint256 BIP34Hash;
    /** Block height at which BIP65 becomes active */
    int BIP65Height;
    /** Block height at which BIP66 becomes active */
    int BIP66Height;
    /** Block height at which CSV (BIP68, BIP112 and BIP113) becomes active */
    int CSVHeight;
    /** Block height at which Segwit (BIP141, BIP143 and BIP147) becomes active.
     * Note that segwit v0 script rules are enforced on all blocks except the
     * BIP 16 exception blocks. */
    int SegwitHeight;
    /**
     * Block height at which version bits were set to resolved
     * to support future algo changes */
    int ReserveAlgoBitsHeight;
    /**
     * Block height at which Odocrypt got activated */
    int OdoHeight;

    /** Don't warn about unknown BIP 9 activations below this height.
     * This prevents us from warning about the CSV and segwit activations. */
    int MinBIP9WarningHeight;
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
    std::map<int, uint256> initialTarget;
    bool fPowAllowMinDifficultyBlocks;
    bool fEasyPow;
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
	int64_t algoSwapChangeTarget;

    uint32_t nOdoShapechangeInterval;

    /** The best chain should have at least this much work */
    uint256 nMinimumChainWork;
    /** By default assume that the signatures in ancestors of this block are valid */
    uint256 defaultAssumeValid;

    /**
     * If true, witness commitments contain a payload equal to a DigiByte Script solution
     * to the signet challenge. See BIP325.
     */
    bool signet_blocks{false};
    std::vector<uint8_t> signet_challenge;

    bool EnableRBF() const { return fRbfEnabled; }

    int DeploymentHeight(BuriedDeployment dep) const
    {
        switch (dep) {
        case DEPLOYMENT_HEIGHTINCB:
            return BIP34Height;
        case DEPLOYMENT_CLTV:
            return BIP65Height;
        case DEPLOYMENT_DERSIG:
            return BIP66Height;
        case DEPLOYMENT_CSV:
            return CSVHeight;
        case DEPLOYMENT_SEGWIT:
            return SegwitHeight;
        case DEPLOYMENT_NVERSIONBIPS:
            // In DigiByte DEPLOYMENT_CSV and DEPLOYMENT_NVERSIONBIPS
            // got activated simultaneously
            return CSVHeight;
        case DEPLOYMENT_RESERVEALGO:
            return ReserveAlgoBitsHeight;
        case DEPLOYMENT_ODO:
            return OdoHeight;
        } // no default case, so the compiler can warn about missing cases
        return std::numeric_limits<int>::max();
    }
};

} // namespace Consensus

#endif // DIGIBYTE_CONSENSUS_PARAMS_H
