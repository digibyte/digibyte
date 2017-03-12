// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CONSENSUS_CONSENSUS_H
#define BITCOIN_CONSENSUS_CONSENSUS_H

#include <stdint.h>

/** The maximum allowed size for a serialized block, in bytes (only for buffer size limits) */
static const unsigned int MAX_BLOCK_SERIALIZED_SIZE = 4000000;
/** The maximum allowed weight for a block, see BIP 141 (network rule) */
static const unsigned int MAX_BLOCK_WEIGHT = 4000000;
/** The maximum allowed size for a block excluding witness data, in bytes (network rule) */
static const unsigned int MAX_BLOCK_SIZE = 1000000;

const int64_t nDiffChangeTarget = 67200; // Patch effective @ block 67200//for testing
const int64_t multiAlgoDiffChangeTarget = 145000; // block 145000 where multi-algo work weighting starts 145000//for testing
const int64_t alwaysUpdateDiffChangeTarget = 400000; // block 400000 after which all difficulties are updated on every block//for testing
const int64_t workComputationChangeTarget = 1430000; //digispeed
const int64_t workComputationChangeTarget2 = workComputationChangeTarget+2*365*24*3600/15;//2 years,
const int64_t workComputationChangeTarget4 = workComputationChangeTarget2+2*365*24*3600/15;//4 years,
const int64_t workComputationChangeTarget6 = workComputationChangeTarget4+2*365*24*3600/15;//6 years,
const int64_t workComputationChangeTarget8 = workComputationChangeTarget6+2*365*24*3600/15;//8 years,
const int64_t workComputationChangeTarget10 = workComputationChangeTarget8+2*365*24*3600/15;//10 years,
const int64_t workComputationChangeTarget12 = workComputationChangeTarget10+2*365*24*3600/15;//12 years,
const int64_t workComputationChangeTarget14 = workComputationChangeTarget12+2*365*24*3600/15;//14 years,
const int64_t workComputationChangeTarget16 = workComputationChangeTarget14+2*365*24*3600/15;//16 years,
const int64_t workComputationChangeTarget18 = workComputationChangeTarget16+2*365*24*3600/15;//18 years,
const int64_t workComputationChangeTarget20 = workComputationChangeTarget18+2*365*24*3600/15;//20 years,

static const int64_t patchBlockRewardDuration = 10080; // 10080 blocks main net change
static const int64_t patchBlockRewardDuration2 = 80160; // 80160 blocks main net change

const int64_t nTargetTimespan =  0.10 * 24 * 60 * 60; // 2.4 hours
const int64_t nTargetSpacing = 60; // 60 seconds
const int64_t nInterval = nTargetTimespan / nTargetSpacing;
const int64_t nTargetTimespanRe = 1*60; // 60 Seconds
const int64_t nTargetSpacingRe = 1*60; // 60 seconds
const int64_t nIntervalRe = nTargetTimespanRe / nTargetSpacingRe; // 1 block

static const unsigned int MAX_BLOCK_BASE_SIZE = 2000000;


/** The maximum allowed number of signature check operations in a block (network rule) */
static const int64_t MAX_BLOCK_SIGOPS_COST = 80000;
/** Coinbase transaction outputs can only be spent after this number of new blocks (network rule) */
static const int COINBASE_MATURITY = 8;
static const int COINBASE_MATURITY_2 = 100;
/** Flags for nSequence and nLockTime locks */
enum {
    /* Interpret sequence numbers as relative lock-time constraints. */
    LOCKTIME_VERIFY_SEQUENCE = (1 << 0),

    /* Use GetMedianTimePast() instead of nTime for end point timestamp. */
    LOCKTIME_MEDIAN_TIME_PAST = (1 << 1),
};

#endif // BITCOIN_CONSENSUS_CONSENSUS_H
