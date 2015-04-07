// Copyright (c) 2011-2014 The Bitcoin Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "main.h"
#include "miner.h"
#include "uint256.h"
#include "util.h"

#include <boost/test/unit_test.hpp>
// miners obey an exponential distribution
#include <boost/random/exponential_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/function.hpp>

static boost::mt19937 prng;

int VersionForAlgo(int algo)
{
    switch (algo)
    {
        case ALGO_SCRYPT:
            return BLOCK_VERSION_DEFAULT;
        case ALGO_SHA256D:
            return BLOCK_VERSION_DEFAULT | BLOCK_VERSION_SHA256D;
        case ALGO_GROESTL:
            return BLOCK_VERSION_DEFAULT | BLOCK_VERSION_GROESTL;
        case ALGO_SKEIN:
            return BLOCK_VERSION_DEFAULT | BLOCK_VERSION_SKEIN;
        case ALGO_QUBIT:
            return BLOCK_VERSION_DEFAULT | BLOCK_VERSION_QUBIT;
    }
    assert(false);
    return 0;
}

double BitsToDifficulty(int nBits)
{
    CBigNum target;
    target.SetCompact(nBits);
    // approximate
    return pow(2, 256-32)/target.getuint256().getdouble();
}

void SimulateNextBlock(CBlockIndex*& tip, double* hashRates)
{
    double recTime = 1e9;
    CBlockIndex* newTip = new CBlockIndex;
    newTip->pprev = tip;
    newTip->nHeight = tip->nHeight+1;
    for (int i=0; i<NUM_ALGOS; i++)
    {
        if (hashRates[i] == 0) continue;
        CBigNum target;
        unsigned int nBits = GetNextWorkRequired(tip, NULL, i, false);
        target.SetCompact(nBits);
        double dtarget = target.getuint256().getdouble()/pow(2,256);
        double mean = 1/(hashRates[i]*dtarget);
        boost::exponential_distribution<double> distr(1/mean);
        double received = distr(prng);
        if (received < recTime)
        {
            recTime = received;
            newTip->nVersion = VersionForAlgo(i);
            newTip->nTime = tip->nTime + received;
            newTip->nBits=nBits;
        }
    }
    assert(recTime < 1e9);
    tip = newTip;
    return;
}

void SimulationSetup(CBlockIndex*& tip, double* hashRates, int height)
{
    assert(tip==NULL);
    // give it a perfect setup
    for(int h=0, c=20*NUM_ALGOS-1; h<20; h++)
    for(int i=0; i<NUM_ALGOS; i++, c--)
    {
        CBlockIndex* newTip = new CBlockIndex;
        newTip->pprev = tip;
        newTip->nHeight = height - c;
        newTip->nTime = newTip->nHeight * 30;
        newTip->nVersion = VersionForAlgo(i);
        double dtarget = pow(2, 256)/hashRates[i] / 150;
        // no base_uint::setdouble()? no problem
        uint256 target;
        for(int b=255; b>=0; b--)
        {
            uint256 newTarget = target + (uint256(1)<<b);
            if (newTarget.getdouble() < dtarget)
                target = newTarget;
        }
        newTip->nBits = CBigNum(target).GetCompact();
        tip = newTip;
    }
}

double ConstantRate(const CBlockIndex* pBlock)
{
    return pow(2,32);
}

double MultipoolRate(const CBlockIndex* pBlock)
{
    if (!pBlock || pBlock->nHeight < 400500)
        return pow(2,32);
    if (pBlock->nHeight < 401000)
        return 10*pow(2,32);
    return pow(2,32);
}

void RunSimulation(boost::function<double(const CBlockIndex*)>* hashRate, int startHeight, int iterations)
{
    CBlockIndex* tip = NULL;
    double rate[5];
    for(int i=0; i<5; i++)
        rate[i]=hashRate[i](tip);
    SimulationSetup(tip, rate, startHeight);
    printf("begin simulation:\n");
    for(int it=0; it<iterations; it++)
    {
        for(int i=0; i<5; i++)
            rate[i]=hashRate[i](tip);
        SimulateNextBlock(tip, rate);

        double diffsum=0;
        for(int i=0; i<5; i++)
            diffsum+=BitsToDifficulty(GetNextWorkRequired(tip, NULL, i, false));
        
        printf("height %d algo %7s time %3d diff %8.3f, avg next diff %7.3f\n", 
            tip->nHeight,
            GetAlgoName(GetAlgo(tip->nVersion)).c_str(), 
            tip->nTime - tip->pprev->nTime, 
            BitsToDifficulty(tip->nBits), diffsum/5);
    }
}

BOOST_AUTO_TEST_SUITE(difficulty_simulation)

// constant hashrate test
BOOST_AUTO_TEST_CASE(constant_rate)
{
    boost::function<double(const CBlockIndex*)> hashRate[5] = {
        ConstantRate,
        ConstantRate,
        ConstantRate,
        ConstantRate,
        ConstantRate,
    };
    RunSimulation(hashRate, 400000, 1000);
}

// a multipool hops on sha at block 500, then off at block 1000
BOOST_AUTO_TEST_CASE(multipool)
{
    boost::function<double(const CBlockIndex*)> hashRate[5] = {
        MultipoolRate,
        ConstantRate,
        ConstantRate,
        ConstantRate,
        ConstantRate,
    };
    RunSimulation(hashRate, 400000, 1500);
}

BOOST_AUTO_TEST_SUITE_END()
