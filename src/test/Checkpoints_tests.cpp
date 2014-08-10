// Copyright (c) 2011-2013 The Bitcoin Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

//
// Unit tests for block-chain checkpoints
//

#include "checkpoints.h"

#include "uint256.h"

#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(Checkpoints_tests)

BOOST_AUTO_TEST_CASE(sanity)
{
    uint256 p9646 = uint256("0x0000000000000b0f1372211861f226a3ec06a27d0a5bf36e4244a982da077e8f");
    uint256 p141845 = uint256("0x00000000000000f62d14d55c2bc3ec0ba94e4f2b3868bbe7be9cb5b681fcc0fb");
    BOOST_CHECK(Checkpoints::CheckBlock(9646, p9646));
    BOOST_CHECK(Checkpoints::CheckBlock(141845, p141845));

    
    // Wrong hashes at checkpoints should fail:
    BOOST_CHECK(!Checkpoints::CheckBlock(9646, p141845));
    BOOST_CHECK(!Checkpoints::CheckBlock(141845, p9646));

    // ... but any hash not at a checkpoint should succeed:
    BOOST_CHECK(Checkpoints::CheckBlock(9646+1, p141845));
    BOOST_CHECK(Checkpoints::CheckBlock(141845+1, p9646));

    BOOST_CHECK(Checkpoints::GetTotalBlocksEstimate() >= 141845);
}    

BOOST_AUTO_TEST_SUITE_END()
