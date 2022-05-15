// Copyright (c) 2014-2020 The DigiByte Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <net.h>
#include <signet.h>
#include <uint256.h>
#include <validation.h>

#include <test/util/setup_common.h>

#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE(validation_tests, TestingSetup)

#define END_OF_SUPPLY_CURVE 110579600

// Set OUTPUT_SUPPLY_SAMPLES_ENABLED to 1 to output
// sampled Supply-curve data points (SAMPLE_INTERVAL)
#ifndef OUTPUT_SUPPLY_SAMPLES_ENABLED
    #define OUTPUT_SUPPLY_SAMPLES_ENABLED 0
#endif

#ifndef SAMPLE_INTERVAL
    #define SAMPLE_INTERVAL 100
#endif

#ifndef WHOLE_COIN
    #define WHOLE_COIN false
#endif

#define CALC_COIN(amount) (WHOLE_COIN ? (amount / COIN) : (amount))

#if OUTPUT_SUPPLY_SAMPLES_ENABLED 
    #define DEBUG(x,y) if (x % SAMPLE_INTERVAL == 0) { \
        std::cerr << x << ';' << CALC_COIN(y) << std::endl; \
    }
#else
    #define DEBUG(x,y) (void) (x)
#endif

#ifndef BLOCK_TIME_SECONDS
    #define BLOCK_TIME_SECONDS 15
#endif

#ifndef SECONDS_PER_MONTH
    #define SECONDS_PER_MONTH (60 * 60 * 24 * 365 / 12)
#endif    

#ifndef ENABLE_TESTNET_SUBSIDY_TESTS
    #define ENABLE_TESTNET_SUBSIDY_TESTS 0
#endif

static void TestBlockSubsidy(const Consensus::Params& consensusParams, int nMaxBlocks, CAmount* nSumOut)
{
    CAmount nSum = 0;
    CAmount nInitialSubsidy = 72000 * COIN;

    CAmount nPreviousSubsidy = nInitialSubsidy * 2; // for height == 0
    BOOST_CHECK_EQUAL(nPreviousSubsidy, nInitialSubsidy * 2);

    /* Before first hard fork */

    // 72000 reward for the first 1440 blocks
    for (int nBlocks = 0; nBlocks < 1440 && nBlocks < consensusParams.nDiffChangeTarget; ++nBlocks)
    {
        int nHeight = nBlocks;
        CAmount nSubsidy = GetBlockSubsidy(nHeight, consensusParams);
        BOOST_CHECK_EQUAL(nSubsidy, nInitialSubsidy);

        nSum += nSubsidy;
        DEBUG(nBlocks, nSubsidy);
    }

    // 16000 rewards until block height 5760
    for (int nBlocks = 1440; nBlocks < 5760 && nBlocks < consensusParams.nDiffChangeTarget; ++nBlocks)
    {
        int nHeight = nBlocks;
        CAmount nSubsidy = GetBlockSubsidy(nHeight, consensusParams);
        BOOST_CHECK_EQUAL(nSubsidy, 16000 * COIN);

        nSum += nSubsidy;
        DEBUG(nBlocks, nSubsidy);
    }

    // 8000 mining rewards until block height 67,200
    for (int nBlocks = 5760; nBlocks < consensusParams.nDiffChangeTarget; ++nBlocks)
    {
        int nHeight = nBlocks;
        CAmount nSubsidy = GetBlockSubsidy(nHeight, consensusParams);
        BOOST_CHECK_EQUAL(nSubsidy, 8000 * COIN);  

        nSum += nSubsidy;
        DEBUG(nBlocks, nSubsidy);
    }

    // Dynamic mining rewards from block height 67,200 to block height 400,000 
    for (int nBlocks = consensusParams.nDiffChangeTarget; nBlocks < consensusParams.alwaysUpdateDiffChangeTarget; ++nBlocks)
    {
        int nHeight = nBlocks;
        CAmount nSubsidy = GetBlockSubsidy(nHeight, consensusParams);

        CAmount nExpectedSubsidy = 8000 * COIN;
        int nHeightWithinFork = (nHeight - consensusParams.nDiffChangeTarget);

        for (int i = 0; i < (nHeightWithinFork / consensusParams.patchBlockRewardDuration) + 1; ++i) {
            nExpectedSubsidy -= nExpectedSubsidy / 200; // dec by 0.5%
        }

        BOOST_CHECK_EQUAL(nSubsidy, nExpectedSubsidy);

        nSum += nSubsidy;
        DEBUG(nBlocks, nSubsidy);
    }

    // Updated dynamic mining rewards from block height 400,000 to block height 1,430,000
    for (int nBlocks = consensusParams.alwaysUpdateDiffChangeTarget; nBlocks < consensusParams.workComputationChangeTarget; ++nBlocks)
    {
        int nHeight = nBlocks;
        CAmount nSubsidy = GetBlockSubsidy(nHeight, consensusParams);

        CAmount nExpectedSubsidy = 2459 * COIN;
        int nHeightWithinFork = (nHeight - consensusParams.alwaysUpdateDiffChangeTarget);

        for (int i = 0; i < (nHeightWithinFork / consensusParams.patchBlockRewardDuration2) + 1; ++i) {
            nExpectedSubsidy -= nExpectedSubsidy / 100; // dec by 1% per month
        }

        BOOST_CHECK_EQUAL(nSubsidy, nExpectedSubsidy);

        nSum += nSubsidy;
        DEBUG(nBlocks, nSubsidy);
    }

    {
        // Updated dynamic mining rewards from block height 1,430,000 to max block height.
        // Intended blockheight: 41.6 million
        // Actual blockheight: 110.5 million
        CAmount nExpectedSubsidyStart = 2157 * COIN / 2;
        CAmount nExpectedSubsidy = nExpectedSubsidyStart;
        int nMonthsConsidered = 0;

        for (int nBlocks = consensusParams.workComputationChangeTarget; nBlocks < nMaxBlocks; ++nBlocks) {
            int nHeight = nBlocks;
            CAmount nSubsidy = GetBlockSubsidy(nHeight, consensusParams);

            int nHeightWithinFork = (nHeight - consensusParams.workComputationChangeTarget);
            int nMonths = nHeightWithinFork * BLOCK_TIME_SECONDS / SECONDS_PER_MONTH;

            if (nMonthsConsidered < nMonths) {
                // Calculate new subsidy for number of months `nMonths`.
                // This is a major optimization in order to reduce the
                // number of inner loops

                // Recalculate subsidy
                for (int i = nMonthsConsidered; i < nMonths; ++i) {
                    // Decay factor: 98884/100000
                    nExpectedSubsidy *= 98884; 
                    nExpectedSubsidy /= 100000; 
                    ++nMonthsConsidered;
                }
            }

            if (nExpectedSubsidy < COIN) { // ToDo: Alter consensus
                nExpectedSubsidy = COIN;
            }

            BOOST_CHECK_EQUAL(nSubsidy, nExpectedSubsidy);

            nSum += nSubsidy;
            DEBUG(nBlocks, nSubsidy);
        }
    }

    CAmount nSubsidy = GetBlockSubsidy(nMaxBlocks, consensusParams);
    CAmount nExpectedSubsidy = 1 * COIN;

    BOOST_CHECK_EQUAL(nSubsidy, nExpectedSubsidy);

    if (nSumOut != NULL) {
        *nSumOut = nSum;
    }
}

BOOST_AUTO_TEST_CASE(block_subsidy_test)
{
    CAmount sum;
    const auto chainParams = CreateChainParams(*m_node.args, CBaseChainParams::MAIN);
    const auto testChainParams = CreateChainParams(*m_node.args, CBaseChainParams::TESTNET);
    TestBlockSubsidy(chainParams->GetConsensus(), END_OF_SUPPLY_CURVE, &sum); // Mainnet

    CAmount nExpectedTotalSupply = 2239167398214795680ULL;
    BOOST_CHECK_EQUAL(sum, nExpectedTotalSupply);

#if OUTPUT_SUPPLY_SAMPLES_ENABLED
    // Output the accumulated supply until END_OF_SUPPLY_CURVE
    std::cout << "(mainnet): MAXIMUM SUPPLY: " << sum << " dgbSATS (" << (sum / COIN) << " DGB)";
#elif ENABLE_TESTNET_SUBSIDY_TESTS != 0
    // Only perform test on TESTNET too if requested so.
    TestBlockSubsidy(testChainParams->GetConsensus(), END_OF_SUPPLY_CURVE, NULL); // Testnet
#endif
}

BOOST_AUTO_TEST_CASE(signet_parse_tests)
{
    ArgsManager signet_argsman;
    signet_argsman.ForceSetArg("-signetchallenge", "51"); // set challenge to OP_TRUE
    const auto signet_params = CreateChainParams(signet_argsman, CBaseChainParams::SIGNET);
    CBlock block;
    BOOST_CHECK(signet_params->GetConsensus().signet_challenge == std::vector<uint8_t>{OP_TRUE});
    CScript challenge{OP_TRUE};

    // empty block is invalid
    BOOST_CHECK(!SignetTxs::Create(block, challenge));
    BOOST_CHECK(!CheckSignetBlockSolution(block, signet_params->GetConsensus()));

    // no witness commitment
    CMutableTransaction cb;
    cb.vout.emplace_back(0, CScript{});
    block.vtx.push_back(MakeTransactionRef(cb));
    block.vtx.push_back(MakeTransactionRef(cb)); // Add dummy tx to exercise merkle root code
    BOOST_CHECK(!SignetTxs::Create(block, challenge));
    BOOST_CHECK(!CheckSignetBlockSolution(block, signet_params->GetConsensus()));

    // no header is treated valid
    std::vector<uint8_t> witness_commitment_section_141{0xaa, 0x21, 0xa9, 0xed};
    for (int i = 0; i < 32; ++i) {
        witness_commitment_section_141.push_back(0xff);
    }
    cb.vout.at(0).scriptPubKey = CScript{} << OP_RETURN << witness_commitment_section_141;
    block.vtx.at(0) = MakeTransactionRef(cb);
    BOOST_CHECK(SignetTxs::Create(block, challenge));
    BOOST_CHECK(CheckSignetBlockSolution(block, signet_params->GetConsensus()));

    // no data after header, valid
    std::vector<uint8_t> witness_commitment_section_325{0xec, 0xc7, 0xda, 0xa2};
    cb.vout.at(0).scriptPubKey = CScript{} << OP_RETURN << witness_commitment_section_141 << witness_commitment_section_325;
    block.vtx.at(0) = MakeTransactionRef(cb);
    BOOST_CHECK(SignetTxs::Create(block, challenge));
    BOOST_CHECK(CheckSignetBlockSolution(block, signet_params->GetConsensus()));

    // Premature end of data, invalid
    witness_commitment_section_325.push_back(0x01);
    witness_commitment_section_325.push_back(0x51);
    cb.vout.at(0).scriptPubKey = CScript{} << OP_RETURN << witness_commitment_section_141 << witness_commitment_section_325;
    block.vtx.at(0) = MakeTransactionRef(cb);
    BOOST_CHECK(!SignetTxs::Create(block, challenge));
    BOOST_CHECK(!CheckSignetBlockSolution(block, signet_params->GetConsensus()));

    // has data, valid
    witness_commitment_section_325.push_back(0x00);
    cb.vout.at(0).scriptPubKey = CScript{} << OP_RETURN << witness_commitment_section_141 << witness_commitment_section_325;
    block.vtx.at(0) = MakeTransactionRef(cb);
    BOOST_CHECK(SignetTxs::Create(block, challenge));
    BOOST_CHECK(CheckSignetBlockSolution(block, signet_params->GetConsensus()));

    // Extraneous data, invalid
    witness_commitment_section_325.push_back(0x00);
    cb.vout.at(0).scriptPubKey = CScript{} << OP_RETURN << witness_commitment_section_141 << witness_commitment_section_325;
    block.vtx.at(0) = MakeTransactionRef(cb);
    BOOST_CHECK(!SignetTxs::Create(block, challenge));
    BOOST_CHECK(!CheckSignetBlockSolution(block, signet_params->GetConsensus()));
}

//! Test retrieval of valid assumeutxo values.
BOOST_AUTO_TEST_CASE(test_assumeutxo)
{
    const auto params = CreateChainParams(*m_node.args, CBaseChainParams::REGTEST);

    // These heights don't have assumeutxo configurations associated, per the contents
    // of chainparams.cpp.
    std::vector<int> bad_heights{0, 100, 111, 115, 209, 211};

    for (auto empty : bad_heights) {
        const auto out = ExpectedAssumeutxo(empty, *params);
        BOOST_CHECK(!out);
    }

    const auto out110 = *ExpectedAssumeutxo(110, *params);
    BOOST_CHECK_EQUAL(out110.hash_serialized.ToString(), "58c8c65a67deee7f6cca0d5a08254b73198f13201485cb6a39dba03e5f41ee65");
    BOOST_CHECK_EQUAL(out110.nChainTx, 110U);

    const auto out210 = *ExpectedAssumeutxo(200, *params);
    BOOST_CHECK_EQUAL(out210.hash_serialized.ToString(), "51c8d11d8b5c1de51543c579736e786aa2736206d1e11e627568029ce092cf62");
    BOOST_CHECK_EQUAL(out210.nChainTx, 200U);
}

BOOST_AUTO_TEST_SUITE_END()
