// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2020 The DigiByte Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "arith_uint256.h"
#include <chainparams.h>

#include <chainparamsseeds.h>
#include <consensus/merkle.h>
#include <hash.h> // for signet block challenge hash
#include <tinyformat.h>
#include <util/system.h>
#include <util/strencodings.h>
#include <versionbitsinfo.h>

#include <assert.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = 8000;
    txNew.vout[0].scriptPubKey = CScript() << 0x0 << OP_CHECKSIG;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "USA Today: 10/Jan/2014, Target: Data stolen from up to 110M customers";
    const CScript genesisOutputScript = CScript() << 0x0 << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = CBaseChainParams::MAIN;
        consensus.signet_blocks = false;
        consensus.signet_challenge.clear();
        //consensus.nSubsidyHalvingInterval = 210000;
        consensus.BIP16Exception = uint256S("0x0");
        consensus.BIP34Height = 4394880;
        consensus.BIP34Hash = uint256S("0xadd8ca420f557f62377ec2be6e6f47b96cf2e68160d58aeb7b73433de834cca0");
        consensus.BIP65Height = 4394880; // 
        consensus.BIP66Height = 4394880; // 
        consensus.CSVHeight = 419328; // 000000000000000004a1b34462cb8aeebd5799177f7a29cf28f2d1961716b5b5
        consensus.SegwitHeight = 481824; // 0000000000000000001c8018d9cb3b742ef25114f27563e3fc4a1902167f9893
        consensus.MinBIP9WarningHeight = 483840; // segwit activation height + miner confirmation window
        consensus.powLimit = ArithToUint256(~arith_uint256(0) >> 20);
        consensus.initialTarget[ALGO_ODO] = ArithToUint256(~arith_uint256(0) >> 40); // 256 difficulty
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 60 / 4;

        /** Current DigiByte 2017 Difficulty Adjustment Code & Block Target. See explanation here: 
        https://github.com/digibyte/digibyte-old/pull/36 
        https://github.com/digibyte/digibyte-old/pull/15

        Difficulty is updated for every algorithm on every block, not just the algorithm that was solved. 
        In particular, the difficulty of one algorithm may decrease when a different algorithm is solved. 

        An attacker with 90% of the SHA256D hashrate and 33% of each of the other 4 algorithms would 
        have insufficient hashpower to mount a 51% attack.

        - MultiAlgo POW (Scrypt, SHA256D, Qubit, Skein and Groestl) algorithms
        - 15 Second Block Target (1.5 min per Algo)
        - ~21 billion total coins in 21 years
        - 8000 coins per block, reduces by 0.5% every 10,080 blocks starting 2/28/14 1% monthly reduction
        - Difficulty retarget every 1 block per algo (1.5 Min)
        **/

        consensus.nTargetTimespan =  0.10 * 24 * 60 * 60; // 2.4 hours
        consensus.nTargetSpacing = 60; // 60 seconds
        consensus.nInterval = consensus.nTargetTimespan / consensus.nTargetSpacing;
        consensus.nDiffChangeTarget = 67200; // DigiShield Hard Fork Block BIP34Height 67,200

        // Old 1% monthly DGB Reward before 15 secon block change
        consensus.patchBlockRewardDuration = 10080; //10080; - No longer used
        //4 blocks per min, x60 minutes x 24hours x 14 days = 80,160 blocks for 0.5% reduction in DGB reward supply - No longer used
        consensus.patchBlockRewardDuration2 = 80160; //80160;
        consensus.nTargetTimespanRe = 1*60; // 60 Seconds
        consensus.nTargetSpacingRe = 1*60; // 60 seconds
        consensus.nIntervalRe = consensus.nTargetTimespanRe / consensus.nTargetSpacingRe; // 1 block

        consensus.nAveragingInterval = 10; // 10 blocks
        consensus.multiAlgoTargetSpacing = 30*5; // NUM_ALGOS * 30 seconds
        consensus.multiAlgoTargetSpacingV4 = 15*5; // NUM_ALGOS * 15 seconds
        consensus.nAveragingTargetTimespan = consensus.nAveragingInterval * consensus.multiAlgoTargetSpacing; // 10* NUM_ALGOS * 30
        consensus.nAveragingTargetTimespanV4 = consensus.nAveragingInterval * consensus.multiAlgoTargetSpacingV4; // 10 * NUM_ALGOS * 15

        consensus.nMaxAdjustDown = 40; // 40% adjustment down
        consensus.nMaxAdjustUp = 20; // 20% adjustment up
        consensus.nMaxAdjustDownV3 = 16; // 16% adjustment down
        consensus.nMaxAdjustUpV3 = 8; // 8% adjustment up
        consensus.nMaxAdjustDownV4 = 16;
        consensus.nMaxAdjustUpV4 = 8;

        consensus.nMinActualTimespan = consensus.nAveragingTargetTimespan * (100 - consensus.nMaxAdjustUp) / 100;
        consensus.nMaxActualTimespan = consensus.nAveragingTargetTimespan * (100 + consensus.nMaxAdjustDown) / 100;
        consensus.nMinActualTimespanV3 = consensus.nAveragingTargetTimespan * (100 - consensus.nMaxAdjustUpV3) / 100;
        consensus.nMaxActualTimespanV3 = consensus.nAveragingTargetTimespan * (100 + consensus.nMaxAdjustDownV3) / 100;
        consensus.nMinActualTimespanV4 = consensus.nAveragingTargetTimespanV4 * (100 - consensus.nMaxAdjustUpV4) / 100;
        consensus.nMaxActualTimespanV4 = consensus.nAveragingTargetTimespanV4 * (100 + consensus.nMaxAdjustDownV4) / 100;

        consensus.nLocalTargetAdjustment = 4; //target adjustment per algo
        consensus.nLocalDifficultyAdjustment = 4; //difficulty adjustment per algo


        // DigiByte Hard Fork Block Heights
        consensus.multiAlgoDiffChangeTarget = 145000; // Block 145,000 MultiAlgo Hard Fork
        consensus.alwaysUpdateDiffChangeTarget = 400000; // Block 400,000 MultiShield Hard Fork
        consensus.workComputationChangeTarget = 1430000; // Block 1,430,000 DigiSpeed Hard Fork
        consensus.algoSwapChangeTarget = 9100000; // Block 9,100,000 Odo PoW Hard Fork

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 28224; // 28224 - 70% of 40320
        consensus.nMinerConfirmationWindow = 40320; // nPowTargetTimespan / nPowTargetSpacing 40320 main net - 1 week
        consensus.fRbfEnabled = false;

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 27; //Add VERSIONBITS_NUM_BITS_TO_SKIP (12)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 12; //Add VERSIONBITS_NUM_BITS_TO_SKIP (12)
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1489997089; // March 24th, 2017 1490355345
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1521891345; // March 24th, 2018

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 13; //Add VERSIONBITS_NUM_BITS_TO_SKIP (12)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1490355345; // March 24th, 2017 1490355345
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1521891345; // March 24th, 2018

        // Deployment of BIP65, BIP66, and BIP34.
        consensus.vDeployments[Consensus::DEPLOYMENT_NVERSIONBIPS].bit = 14; //Add VERSIONBITS_NUM_BITS_TO_SKIP (12)
        consensus.vDeployments[Consensus::DEPLOYMENT_NVERSIONBIPS].nStartTime = 1489997089; // March 24th, 2017 1490355345
        consensus.vDeployments[Consensus::DEPLOYMENT_NVERSIONBIPS].nTimeout = 1521891345;    // March 24th, 2018

        // Reservation of version bits for future algos
        consensus.vDeployments[Consensus::DEPLOYMENT_RESERVEALGO].bit = 12;
        consensus.vDeployments[Consensus::DEPLOYMENT_RESERVEALGO].nStartTime = 1542672000; // 20 Nov, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_RESERVEALGO].nTimeout = 1574208000;   // 20 Nov, 2019

        // Deployment of Odo proof-of-work hardfork
        consensus.vDeployments[Consensus::DEPLOYMENT_ODO].bit = 6;
        consensus.vDeployments[Consensus::DEPLOYMENT_ODO].nStartTime = 1556668800; // 1 May, 2019
        consensus.vDeployments[Consensus::DEPLOYMENT_ODO].nTimeout = 1588291200;    // 1 May, 2020
        
        consensus.nOdoShapechangeInterval = 10*24*60*60; // 10 days    

        // Deployment of ProgPOW algo softfork
        //consensus.vDeployments[Consensus::DEPLOYMENT_PROGPOW].bit = 3;
        //consensus.vDeployments[Consensus::DEPLOYMENT_PROGPOW].nStartTime = 1489997089; // July, 2017 
        //consensus.vDeployments[Consensus::DEPLOYMENT_PROGPOW].nTimeout = 1521891345;    // July, 2018

        // Deployment of RandomX algo softfork
        //consensus.vDeployments[Consensus::DEPLOYMENT_RANDOMX].bit = 4;
        //consensus.vDeployments[Consensus::DEPLOYMENT_RANDOMX].nStartTime = 1489997089; // October, 2017 
        //consensus.vDeployments[Consensus::DEPLOYMENT_RANDOMX].nTimeout = 1521891345;    // October, 2018

        // Deployment of Taproot (BIPs 340-342)
        //consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].bit = 2;
        //consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nStartTime = 1199145601; // January 1, 2008
        //consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nTimeout = 1230767999; // December 31, 2008

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x6495a84f8f83981a435a6cbf9e6dd4bf0f38618c8325213ca6ef6add40c0ddd8"); // Block 6,000,000

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0xb6;
        pchMessageStart[3] = 0xda;
        nDefaultPort = 12024;
        nPruneAfterHeight = 100000;
        m_assumed_blockchain_size = 350;
        m_assumed_chain_state_size = 6;

        genesis = CreateGenesisBlock(1389388394, 2447652, 0x1e0ffff0, 1, 8000);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x7497ea1b465eb39f1c8f507bc877078fe016d6fcb6dfad3a64c98dcc6e1e8496"));
        assert(genesis.hashMerkleRoot == uint256S("0x72ddd9496b004221ed0557358846d9248ecd4c440ebd28ed901efc18757d0fad"));

        // Note that of those with the service bits flag, most only support a subset of possible options
        vSeeds.emplace_back("seed1.digibyte.io");
        vSeeds.emplace_back("seed2.digibyte.io");
        vSeeds.emplace_back("seed3.digibyte.io");
        vSeeds.emplace_back("seed.digibyte.io");
        vSeeds.emplace_back("digihash.co");
        vSeeds.emplace_back("digiexplorer.info");
        vSeeds.emplace_back("seed.digibyteprojects.com");



        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,30);
        base58Prefixes[SCRIPT_ADDRESS_OLD] = std::vector<unsigned char>(1,5);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,63);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,128);
        base58Prefixes[SECRET_KEY_OLD] = std::vector<unsigned char>(1,158);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};

        bech32_hrp = "dgb";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        m_is_test_chain = false;
        m_is_mockable_chain = false;

        checkpointData = (CCheckpointData) {
         {
            {     0, uint256S("0x7497ea1b465eb39f1c8f507bc877078fe016d6fcb6dfad3a64c98dcc6e1e8496")},
            {  5000, uint256S("0x95753d284404118788a799ac754a3fdb5d817f5bd73a78697dfe40985c085596")},
            { 10000, uint256S("0x12f90b8744f3b965e107ad9fd8b33ba6d95a91882fbc4b5f8588d70d494bed88")},
            { 12000, uint256S("0xa1266acba91dc3d5737d9e8c6e21b7a91901f7f4c48082ce3d84dd394a13e415")},
            { 14300, uint256S("0x24f665d71b0c6c88f6f72a863e9f1ba8e835cc52d13ad895dc5426021c7d2c48")},
            { 30000, uint256S("0x17c69ef6b403571b1bd333c91fbe116e451ba8281be12aa6bafb0486764bb315")},
            { 60000, uint256S("0x57b2c612b60462a3d6c388c8b30a68cb6f7e2034eea962b12b7ef506454fa2c1")},
            { 110000, uint256S("0xab2da24656493015f2fd288994661e1cc657d90aa34c755514af044aaaf1569d")},
            { 141100, uint256S("0x145c2cb5239a4e019c730ce8468d927a3955529c2bae077850783da97ddbca05")},
            { 141656, uint256S("0x683d27720429f28bcfa22d8385b7a06f307c8fd918d49215148fbd41a0dda595")},
            { 245000, uint256S("0x852c475c605e1f20bbe60219c811abaeef08bf0d4ff87eef59200fd7a7567fa7")},
            { 302000, uint256S("0xfb6d14ac5e0208f00d941db1fcbfe050f093cfd0c05ed151c809e4428bc14286")},
            { 331000, uint256S("0xbd1a1d002750e1648746eb29c78d30fa1043c8b6f89d82924c4488be06fa3d19")},
            { 360000, uint256S("0x8fee7e3f6c38dccd3047a3e4667c63406f835c2890024030a2ab2dc6dba7c912")},
            { 400100, uint256S("0x82325a97cd97ac14b0a57408f881b1a9fc40174f8430a4580429499ac5d153c8")},
            { 521000, uint256S("0xd23fd1e1f994c0586d761b71bb3530e9ab45bd0fabda3a5a2e394f3dc4d9bb04")},
            { 1380000, uint256S("0x00000000000001969b1e5836dd8bf6a001d96f4a16d336e09405b62b29feead6")},
            { 1435000, uint256S("0xf78cc9c2791c8a23720e2efcdaf46584046ee5db8f050e21a3a15a13f5c68da0")},
            { 4255555, uint256S("0x23f72e760542bf021ec76d04231ad7cf80142069a79ba702028e074b726f86ef")},
            { 6000000, uint256S("0x6495a84f8f83981a435a6cbf9e6dd4bf0f38618c8325213ca6ef6add40c0ddd8")},
         }
        };

        chainTxData = ChainTxData{
            // Data from RPC: getchaintxstats 4096 0000000000000000000b9d2ec5a352ecba0592946514a92f14319dc2b367fc72
            /* nTime    */ 1416891634,
            /* nTxCount */ 1046018,
            /* dTxRate  */ 0.1,
        };
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = CBaseChainParams::TESTNET;
        consensus.signet_blocks = false;
        consensus.signet_challenge.clear();
        consensus.nSubsidyHalvingInterval = 210000;
        consensus.BIP16Exception = uint256S("0x00000000dd30457c001f4095d208cc1296b0eed002427aa599874af7a432b105");
        consensus.BIP34Height = 21111;
        consensus.BIP34Hash = uint256S("0x0000000023b3a96d3484e5abb3755c413e7d41500f8e2a5c3f0dd01299cd8ef8");
        consensus.BIP65Height = 581885; // 00000000007f6655f22f98e72ed80d8b06dc761d5da09df0fa1dc4be4f861eb6
        consensus.BIP66Height = 330776; // 000000002104c8c45e99a8853285a3b592602a3ccde2b832481da85e9e4ba182
        consensus.CSVHeight = 770112; // 00000000025e930139bac5c6c31a403776da130831ab85be56578f3fa75369bb
        consensus.SegwitHeight = 834624; // 00000000002b980fcd729daaa248fd9316a5200e9b367f4ff2c42453e84201ca
        consensus.MinBIP9WarningHeight = 836640; // segwit activation height + miner confirmation window
        consensus.powLimit = uint256S("00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.initialTarget[ALGO_ODO] = ArithToUint256(~arith_uint256(0) >> 36); // 16 difficulty      
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 60 / 4;

        /** Current DigiByte 2017 Difficulty Adjustment Code & Block Target. See explanation here: 
        https://github.com/digibyte/digibyte-old/pull/36 
        https://github.com/digibyte/digibyte-old/pull/15

        Difficulty is updated for every algorithm on every block, not just the algorithm that was solved. 
        In particular, the difficulty of one algorithm may decrease when a different algorithm is solved. 

        An attacker with 90% of the SHA256D hashrate and 33% of each of the other 4 algorithms would 
        have insufficient hashpower to mount a 51% attack.

        - MultiAlgo POW (Scrypt, SHA256D, Qubit, Skein and Groestl) algorithms
        - 15 Second Block Target (1.5 min per Algo)
        - ~21 billion total coins in 21 years
        - 8000 coins per block, reduces by 0.5% every 10,080 blocks starting 2/28/14 1% monthly reduction
        - Difficulty retarget every 1 block per algo (1.5 Min)
        **/

        consensus.nTargetTimespan =  0.10 * 24 * 60 * 60; // 2.4 hours
        consensus.nTargetSpacing = 60; // 60 seconds
        consensus.nInterval = consensus.nTargetTimespan / consensus.nTargetSpacing;
        consensus.nDiffChangeTarget = 67; // DigiShield Hard Fork Block BIP34Height 67,200

        // Old 1% monthly DGB Reward before 15 secon block change
        consensus.patchBlockRewardDuration = 10; //10080; - No longer used
        //4 blocks per min, x60 minutes x 24hours x 14 days = 80,160 blocks for 0.5% reduction in DGB reward supply - No longer used
        consensus.patchBlockRewardDuration2 = 80; //80160;
        consensus.nTargetTimespanRe = 1*60; // 60 Seconds
        consensus.nTargetSpacingRe = 1*60; // 60 seconds
        consensus.nIntervalRe = consensus.nTargetTimespanRe / consensus.nTargetSpacingRe; // 1 block

        consensus.nAveragingInterval = 10; // 10 blocks
        consensus.multiAlgoTargetSpacing = 30*5; // NUM_ALGOS * 30 seconds
        consensus.multiAlgoTargetSpacingV4 = 15*5; // NUM_ALGOS * 15 seconds
        consensus.nAveragingTargetTimespan = consensus.nAveragingInterval * consensus.multiAlgoTargetSpacing; // 10* NUM_ALGOS * 30
        consensus.nAveragingTargetTimespanV4 = consensus.nAveragingInterval * consensus.multiAlgoTargetSpacingV4; // 10 * NUM_ALGOS * 15

        consensus.nMaxAdjustDown = 40; // 40% adjustment down
        consensus.nMaxAdjustUp = 20; // 20% adjustment up
        consensus.nMaxAdjustDownV3 = 16; // 16% adjustment down
        consensus.nMaxAdjustUpV3 = 8; // 8% adjustment up
        consensus.nMaxAdjustDownV4 = 16;
        consensus.nMaxAdjustUpV4 = 8;

        consensus.nMinActualTimespan = consensus.nAveragingTargetTimespan * (100 - consensus.nMaxAdjustUp) / 100;
        consensus.nMaxActualTimespan = consensus.nAveragingTargetTimespan * (100 + consensus.nMaxAdjustDown) / 100;
        consensus.nMinActualTimespanV3 = consensus.nAveragingTargetTimespan * (100 - consensus.nMaxAdjustUpV3) / 100;
        consensus.nMaxActualTimespanV3 = consensus.nAveragingTargetTimespan * (100 + consensus.nMaxAdjustDownV3) / 100;
        consensus.nMinActualTimespanV4 = consensus.nAveragingTargetTimespanV4 * (100 - consensus.nMaxAdjustUpV4) / 100;
        consensus.nMaxActualTimespanV4 = consensus.nAveragingTargetTimespanV4 * (100 + consensus.nMaxAdjustDownV4) / 100;

        consensus.nLocalTargetAdjustment = 4; //target adjustment per algo
        consensus.nLocalDifficultyAdjustment = 4; //difficulty adjustment per algo


        // DigiByte Hard Fork Block Heights
        consensus.multiAlgoDiffChangeTarget = 100; // Block 145,000 MultiAlgo Hard Fork
        consensus.alwaysUpdateDiffChangeTarget = 400; // Block 400,000 MultiShield Hard Fork
        consensus.workComputationChangeTarget = 1430; // Block 1,430,000 DigiSpeed Hard Fork
        consensus.algoSwapChangeTarget = 20000; // Block 9,000,000 Odo PoW Hard Fork

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 4032; // 4032 - 70% of 5760
        consensus.nMinerConfirmationWindow = 5760; // 1 day of blocks on testnet
        consensus.fRbfEnabled = false;

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 27; //Add VERSIONBITS_NUM_BITS_TO_SKIP (12)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 12; //Add VERSIONBITS_NUM_BITS_TO_SKIP (12)
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 13; //Add VERSIONBITS_NUM_BITS_TO_SKIP (12)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // Deployment of BIP65, BIP66, and BIP34.
        consensus.vDeployments[Consensus::DEPLOYMENT_NVERSIONBIPS].bit = 14; //Add VERSIONBITS_NUM_BITS_TO_SKIP (12)
        consensus.vDeployments[Consensus::DEPLOYMENT_NVERSIONBIPS].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_NVERSIONBIPS].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // Reservation of version bits for future algos
        consensus.vDeployments[Consensus::DEPLOYMENT_RESERVEALGO].bit = 12;
        consensus.vDeployments[Consensus::DEPLOYMENT_RESERVEALGO].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_RESERVEALGO].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // Deployment of Odo proof-of-work hardfork
        consensus.vDeployments[Consensus::DEPLOYMENT_ODO].bit = 6;
        consensus.vDeployments[Consensus::DEPLOYMENT_ODO].nStartTime = 1551398400; // 1 Mar, 2019
        consensus.vDeployments[Consensus::DEPLOYMENT_ODO].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        consensus.nOdoShapechangeInterval = 1*24*60*60; // 1 day

        // Deployment of Taproot (BIPs 340-342)
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].bit = 2;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nTimeout = 1230767999; // December 31, 2008

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00"); //1079274

        pchMessageStart[0] = 0xfd;
        pchMessageStart[1] = 0xc8;
        pchMessageStart[2] = 0xbd;
        pchMessageStart[3] = 0xdd;
        nDefaultPort = 12026;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 40;
        m_assumed_chain_state_size = 2;

        genesis = CreateGenesisBlock(1516939474, 2411473, 0x1e0ffff0, 1, 8000 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x308ea0711d5763be2995670dd9ca9872753561285a84da1d58be58acaa822252"));
        assert(genesis.hashMerkleRoot == uint256S("0x72ddd9496b004221ed0557358846d9248ecd4c440ebd28ed901efc18757d0fad"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back("seed1.digibyte.io");
        vSeeds.emplace_back("seed2.digibyte.io");
        vSeeds.emplace_back("seed3.digibyte.io");
        vSeeds.emplace_back("testnet-seed.digibyteprojects.com");
        vSeeds.emplace_back("testnet-1.us.digibyteservers.io");

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,126);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,140);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,254);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "dgbt";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        m_is_test_chain = true;
        m_is_mockable_chain = false;

        checkpointData = {
            {
                {     0, uint256S("0x308ea0711d5763be2995670dd9ca9872753561285a84da1d58be58acaa822252")},
            }
        };

        chainTxData = ChainTxData{
            // Data from RPC: getchaintxstats 4096 000000000000006433d1efec504c53ca332b64963c425395515b01977bd7b3b0
            /* nTime    */ 1603359686,
            /* nTxCount */ 58090238,
            /* dTxRate  */ 0.1232886622799463,
        };
    }
};

/**
 * Signet
 */
class SigNetParams : public CChainParams {
public:
    explicit SigNetParams(const ArgsManager& args) {
        std::vector<uint8_t> bin;
        vSeeds.clear();

        if (!args.IsArgSet("-signetchallenge")) {
            bin = ParseHex("512103ad5e0edad18cb1f0fc0d28a3d4f1f3e445640337489abb10404f2d1e086be430210359ef5021964fe22d6f8e05b2463c9540ce96883fe3b278760f048f5189f2e6c452ae");
            vSeeds.emplace_back("178.128.221.177");
            vSeeds.emplace_back("2a01:7c8:d005:390::5");
            vSeeds.emplace_back("v7ajjeirttkbnt32wpy3c6w3emwnfr3fkla7hpxcfokr3ysd3kqtzmqd.onion:38333");

            consensus.nMinimumChainWork = uint256S("0x00000000000000000000000000000000000000000000000000000019fd16269a");
            consensus.defaultAssumeValid = uint256S("0x0000002a1de0f46379358c1fd09906f7ac59adf3712323ed90eb59e4c183c020"); // 9434
            m_assumed_blockchain_size = 1;
            m_assumed_chain_state_size = 0;
            chainTxData = ChainTxData{
                // Data from RPC: getchaintxstats 4096 0000002a1de0f46379358c1fd09906f7ac59adf3712323ed90eb59e4c183c020
                /* nTime    */ 1603986000,
                /* nTxCount */ 9582,
                /* dTxRate  */ 0.00159272030651341,
            };
        } else {
            const auto signet_challenge = args.GetArgs("-signetchallenge");
            if (signet_challenge.size() != 1) {
                throw std::runtime_error(strprintf("%s: -signetchallenge cannot be multiple values.", __func__));
            }
            bin = ParseHex(signet_challenge[0]);

            consensus.nMinimumChainWork = uint256{};
            consensus.defaultAssumeValid = uint256{};
            m_assumed_blockchain_size = 0;
            m_assumed_chain_state_size = 0;
            chainTxData = ChainTxData{
                0,
                0,
                0,
            };
            LogPrintf("Signet with challenge %s\n", signet_challenge[0]);
        }

        if (args.IsArgSet("-signetseednode")) {
            vSeeds = args.GetArgs("-signetseednode");
        }

        strNetworkID = CBaseChainParams::SIGNET;
        consensus.signet_blocks = true;
        consensus.signet_challenge.assign(bin.begin(), bin.end());
        consensus.nSubsidyHalvingInterval = 210000;
        consensus.BIP16Exception = uint256{};
        consensus.BIP34Height = 1;
        consensus.BIP34Hash = uint256{};
        consensus.BIP65Height = 1;
        consensus.BIP66Height = 1;
        consensus.CSVHeight = 1;
        consensus.SegwitHeight = 1;
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 10 * 60;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.MinBIP9WarningHeight = 0;
        consensus.powLimit = uint256S("00000377ae000000000000000000000000000000000000000000000000000000");
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Activation of Taproot (BIPs 340-342)
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].bit = 2;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // message start is defined as the first 4 bytes of the sha256d of the block script
        CHashWriter h(SER_DISK, 0);
        h << consensus.signet_challenge;
        uint256 hash = h.GetHash();
        memcpy(pchMessageStart, hash.begin(), 4);

        nDefaultPort = 38333;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1598918400, 52613770, 0x1e0377ae, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000008819873e925422c1ff0f99f7cc9bbb232af63a077a480a3633bee1ef6"));
        assert(genesis.hashMerkleRoot == uint256S("0x4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b"));

        vFixedSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "tb";

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        m_is_test_chain = true;
        m_is_mockable_chain = false;
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 60 / 4;
        consensus.nTargetTimespan =  0.10 * 24 * 60 * 60; // 2.4 hours
        consensus.nTargetSpacing = 60; // 60 seconds
        consensus.nInterval = consensus.nTargetTimespan / consensus.nTargetSpacing;
        consensus.nDiffChangeTarget = 67; // DigiShield Hard Fork Block BIP34Height 67,200

        // Old 1% monthly DGB Reward before 15 secon block change
        consensus.patchBlockRewardDuration = 10; //10080; - No longer used
        //4 blocks per min, x60 minutes x 24hours x 14 days = 80,160 blocks for 0.5% reduction in DGB reward supply - No longer used
        consensus.patchBlockRewardDuration2 = 80; //80;
        consensus.nTargetTimespanRe = 1*60; // 60 Seconds
        consensus.nTargetSpacingRe = 1*60; // 60 seconds
        consensus.nIntervalRe = consensus.nTargetTimespanRe / consensus.nTargetSpacingRe; // 1 block

        consensus.nAveragingInterval = 10; // 10 blocks
        consensus.multiAlgoTargetSpacing = 30*5; // NUM_ALGOS * 30 seconds
        consensus.multiAlgoTargetSpacingV4 = 15*5; // NUM_ALGOS * 15 seconds
        consensus.nAveragingTargetTimespan = consensus.nAveragingInterval * consensus.multiAlgoTargetSpacing; // 10* NUM_ALGOS * 30
        consensus.nAveragingTargetTimespanV4 = consensus.nAveragingInterval * consensus.multiAlgoTargetSpacingV4; // 10 * NUM_ALGOS * 15

        consensus.nMaxAdjustDown = 40; // 40% adjustment down
        consensus.nMaxAdjustUp = 20; // 20% adjustment up
        consensus.nMaxAdjustDownV3 = 16; // 16% adjustment down
        consensus.nMaxAdjustUpV3 = 8; // 8% adjustment up
        consensus.nMaxAdjustDownV4 = 16;
        consensus.nMaxAdjustUpV4 = 8;

        consensus.nMinActualTimespan = consensus.nAveragingTargetTimespan * (100 - consensus.nMaxAdjustUp) / 100;
        consensus.nMaxActualTimespan = consensus.nAveragingTargetTimespan * (100 + consensus.nMaxAdjustDown) / 100;
        consensus.nMinActualTimespanV3 = consensus.nAveragingTargetTimespan * (100 - consensus.nMaxAdjustUpV3) / 100;
        consensus.nMaxActualTimespanV3 = consensus.nAveragingTargetTimespan * (100 + consensus.nMaxAdjustDownV3) / 100;
        consensus.nMinActualTimespanV4 = consensus.nAveragingTargetTimespanV4 * (100 - consensus.nMaxAdjustUpV4) / 100;
        consensus.nMaxActualTimespanV4 = consensus.nAveragingTargetTimespanV4 * (100 + consensus.nMaxAdjustDownV4) / 100;

        consensus.nLocalTargetAdjustment = 4; //target adjustment per algo
        consensus.nLocalDifficultyAdjustment = 4; //difficulty adjustment per algo


        // DigiByte Hard Fork Block Heights
        consensus.multiAlgoDiffChangeTarget = 145; // Block 145,000 MultiAlgo Hard Fork
        consensus.alwaysUpdateDiffChangeTarget = 400; // Block 400,000 MultiShield Hard Fork
        consensus.workComputationChangeTarget = 1430; // Block 1,430,000 DigiSpeed Hard Fork
        consensus.algoSwapChangeTarget = 2000; // Block 9,000,000 Odo PoW Hard Fork

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].bit = 2;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_TAPROOT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        consensus.nMinimumChainWork = uint256{};
        consensus.defaultAssumeValid = uint256{};

        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nDefaultPort = 18444;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 0;
        m_assumed_chain_state_size = 0;

        UpdateActivationParametersFromArgs(args);

        genesis = CreateGenesisBlock(1519460922, 4, 0x207fffff, 1, 8000 * COIN);      
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x4598a0f2b823aaf9e77ee6d5e46f1edb824191dcd48b08437b7cec17e6ae6e26"));
        assert(genesis.hashMerkleRoot == uint256S("0x72ddd9496b004221ed0557358846d9248ecd4c440ebd28ed901efc18757d0fad"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = true;
        m_is_test_chain = true;
        m_is_mockable_chain = true;

        checkpointData = {
            {
                {0, uint256S("4598a0f2b823aaf9e77ee6d5e46f1edb824191dcd48b08437b7cec17e6ae6e26")},
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,126);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,140);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,254);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "dgbrt";
    }

    /**
     * Allows modifying the Version Bits regtest parameters.
     */
    void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
    void UpdateActivationParametersFromArgs(const ArgsManager& args);
};

void CRegTestParams::UpdateActivationParametersFromArgs(const ArgsManager& args)
{
    if (args.IsArgSet("-segwitheight")) {
        int64_t height = args.GetArg("-segwitheight", consensus.SegwitHeight);
        if (height < -1 || height >= std::numeric_limits<int>::max()) {
            throw std::runtime_error(strprintf("Activation height %ld for segwit is out of valid range. Use -1 to disable segwit.", height));
        } else if (height == -1) {
            LogPrintf("Segwit disabled for testing\n");
            height = std::numeric_limits<int>::max();
        }
        consensus.SegwitHeight = static_cast<int>(height);
    }

    if (!args.IsArgSet("-vbparams")) return;

    for (const std::string& strDeployment : args.GetArgs("-vbparams")) {
        std::vector<std::string> vDeploymentParams;
        boost::split(vDeploymentParams, strDeployment, boost::is_any_of(":"));
        if (vDeploymentParams.size() != 3) {
            throw std::runtime_error("Version bits parameters malformed, expecting deployment:start:end");
        }
        int64_t nStartTime, nTimeout;
        if (!ParseInt64(vDeploymentParams[1], &nStartTime)) {
            throw std::runtime_error(strprintf("Invalid nStartTime (%s)", vDeploymentParams[1]));
        }
        if (!ParseInt64(vDeploymentParams[2], &nTimeout)) {
            throw std::runtime_error(strprintf("Invalid nTimeout (%s)", vDeploymentParams[2]));
        }
        bool found = false;
        for (int j=0; j < (int)Consensus::MAX_VERSION_BITS_DEPLOYMENTS; ++j) {
            if (vDeploymentParams[0] == VersionBitsDeploymentInfo[j].name) {
                UpdateVersionBitsParameters(Consensus::DeploymentPos(j), nStartTime, nTimeout);
                found = true;
                LogPrintf("Setting version bits activation parameters for %s to start=%ld, timeout=%ld\n", vDeploymentParams[0], nStartTime, nTimeout);
                break;
            }
        }
        if (!found) {
            throw std::runtime_error(strprintf("Invalid deployment (%s)", vDeploymentParams[0]));
        }
    }
}

static std::unique_ptr<const CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<const CChainParams> CreateChainParams(const ArgsManager& args, const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN) {
        return std::unique_ptr<CChainParams>(new CMainParams());
    } else if (chain == CBaseChainParams::TESTNET) {
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    } else if (chain == CBaseChainParams::SIGNET) {
        return std::unique_ptr<CChainParams>(new SigNetParams(args));
    } else if (chain == CBaseChainParams::REGTEST) {
        return std::unique_ptr<CChainParams>(new CRegTestParams(args));
    }
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(gArgs, network);
}
