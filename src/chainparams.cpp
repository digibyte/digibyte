// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

//
// Main network
//

unsigned int pnSeed[] =
{
//            0x797DFAD8, 0xA0E6D04A, 0xCACC704A, 0xDC20042E, 0x586D1BC6,
//           0x2124CC36, 0x8CB829C6, 0xB65E4C90, 0xBC32555F, 0x46F09FA2,
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        pchMessageStart[0] = 0xfc;
        pchMessageStart[1] = 0xc1;
        pchMessageStart[2] = 0xb7;
        pchMessageStart[3] = 0xdc;
        vAlertPubKey = ParseHex("04F04441C4757F356290A37C313C3772C5BC5003E898EB2E0CF365795543A7BF690C8BBBFA32EE3A3325477CE2000B7D0453EFBB203329D0F9DF34D5927D022BC9");
        nDefaultPort = 11024;
        nRPCPort = 11022;
        bnProofOfWorkLimit[ALGO_SHA256D] = CBigNum(~uint256(0) >> 20);
        bnProofOfWorkLimit[ALGO_SCRYPT]  = CBigNum(~uint256(0) >> 20);
        bnProofOfWorkLimit[ALGO_GROESTL] = CBigNum(~uint256(0) >> 20);
        bnProofOfWorkLimit[ALGO_SKEIN]   = CBigNum(~uint256(0) >> 20);
        bnProofOfWorkLimit[ALGO_QUBIT]   = CBigNum(~uint256(0) >> 20);
        

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
  
 const char* pszTimestamp = "USA Today: 10/Jan/2014, Target: Data stolen from up to 110M customers";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CBigNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 8000;
        txNew.vout[0].scriptPubKey = CScript() << 0x0 << OP_CHECKSIG;          
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        //genesis.nVersion = 1;
       
	genesis.nTime    = 1392796564;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 961533; 
        //// debug print
        hashGenesisBlock = genesis.GetHash();
        //while (hashGenesisBlock > bnProofOfWorkLimit[ALGO_SHA256D].getuint256()){
        //    if (++genesis.nNonce==0) break;
        //    hashGenesisBlock = genesis.GetHash();
        //}

        //printf("MAIN: %s\n", hashGenesisBlock.ToString().c_str());
        //printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        //printf("%x\n", bnProofOfWorkLimit[ALGO_SCRYPT].GetCompact());
        //genesis.print();
        assert(hashGenesisBlock == uint256("0xb5dca8039e300198e5fe7cd23bdd1728e2a444af34c447dbd0916fa3430a68c2"));
        //assert(hashGenesisBlock == uint256("0x7497ea1b465eb39f1c8f507bc877078fe016d6fcb6dfad3a64c98dcc6e1e8496"));
        assert(genesis.hashMerkleRoot == uint256("0x72ddd9496b004221ed0557358846d9248ecd4c440ebd28ed901efc18757d0fad"));

        //vSeeds.push_back(CDNSSeedData("digibyte.co seed #1", "seed1.digibyte.co"));
        //vSeeds.push_back(CDNSSeedData("hashdragon.com seed #2", "seed2.hashdragon.com"));

        base58Prefixes[PUBKEY_ADDRESS] = 127;
        base58Prefixes[SCRIPT_ADDRESS] = 5;
        base58Prefixes[SECRET_KEY] =     128;

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' 
            const int64 nTwoDays = 2 * 24 * 60 * 60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nTwoDays) - nTwoDays;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        pchMessageStart[0] = 0xfc;
        pchMessageStart[1] = 0xc1;
        pchMessageStart[2] = 0xb7;
        pchMessageStart[3] = 0xdc;
        vAlertPubKey = ParseHex("b5dca8039e300198e5fe7cd23bdd1728e2a444af34c447dbd0916fa3430a68c2");
        nDefaultPort = 12025;
        nRPCPort = 14023;
        strDataDir = "testnet3";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1392796564;
        genesis.nNonce = 961533;
        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0xb5dca8039e300198e5fe7cd23bdd1728e2a444af34c447dbd0916fa3430a68c2"));
        //while (hashGenesisBlock > bnProofOfWorkLimit[ALGO_SHA256D].getuint256()){
        //    if (++genesis.nNonce==0) break;
        //   hashGenesisBlock = genesis.GetHash();
        //}

        //printf("TEST: %s\n", hashGenesisBlock.ToString().c_str());
        //printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        //genesis.print();
        
        //assert(hashGenesisBlock == uint256("0x0000017ce2a79c8bddafbbe47c004aa92b20678c354b34085f62b762084b9788"));

        base58Prefixes[PUBKEY_ADDRESS] = 111;
        base58Prefixes[SCRIPT_ADDRESS] = 196;
        base58Prefixes[SECRET_KEY]     = 239;

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xb3;
        pchMessageStart[2] = 0xb2;
        pchMessageStart[3] = 0xdb;
        //nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit[ALGO_SHA256D] = CBigNum(~uint256(0) >> 1);
        bnProofOfWorkLimit[ALGO_SCRYPT]  = CBigNum(~uint256(0) >> 1);
        bnProofOfWorkLimit[ALGO_GROESTL] = CBigNum(~uint256(0) >> 1);
        bnProofOfWorkLimit[ALGO_SKEIN]   = CBigNum(~uint256(0) >> 1);
        bnProofOfWorkLimit[ALGO_QUBIT]   = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1392796564;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 961533;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
        //assert(hashGenesisBlock == uint256("0x0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
