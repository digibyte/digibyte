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
<<<<<<< HEAD
    uint256 p11111 = uint256("0x0000000069e244f73d78e8fd29ba2fd2ed618bd6fa2ee92559f542fdb26e7c1d");
    uint256 p134444 = uint256("0x00000000000005b12ffd4cd315cd34ffd4a594f430ac814c91184a0d42d2b0fe");
    BOOST_CHECK(Checkpoints::CheckBlock(11111, p11111));
    BOOST_CHECK(Checkpoints::CheckBlock(134444, p134444));

    
    // Wrong hashes at checkpoints should fail:
    BOOST_CHECK(!Checkpoints::CheckBlock(11111, p134444));
    BOOST_CHECK(!Checkpoints::CheckBlock(134444, p11111));

    // ... but any hash not at a checkpoint should succeed:
    BOOST_CHECK(Checkpoints::CheckBlock(11111+1, p134444));
    BOOST_CHECK(Checkpoints::CheckBlock(134444+1, p11111));

    BOOST_CHECK(Checkpoints::GetTotalBlocksEstimate() >= 134444);
=======
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
>>>>>>> mryiad/master
}    

BOOST_AUTO_TEST_SUITE_END()
