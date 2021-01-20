<<<<<<< HEAD
// Copyright (c) 2009-2019 The Bitcoin Core developers
// Copyright (c) 2014-2019 The DigiByte Core developers
=======
// Copyright (c) 2016-2020 The DigiByte Core developers
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <compat/byteswap.h>
<<<<<<< HEAD
#include <test/test_digibyte.h>
=======
#include <test/util/setup_common.h>
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25

#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE(bswap_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(bswap_tests)
{
<<<<<<< HEAD
	// Sibling in digibyte/src/qt/test/compattests.cpp
	uint16_t u1 = 0x1234;
	uint32_t u2 = 0x56789abc;
	uint64_t u3 = 0xdef0123456789abc;
	uint16_t e1 = 0x3412;
	uint32_t e2 = 0xbc9a7856;
	uint64_t e3 = 0xbc9a78563412f0de;
	BOOST_CHECK(bswap_16(u1) == e1);
	BOOST_CHECK(bswap_32(u2) == e2);
	BOOST_CHECK(bswap_64(u3) == e3);
=======
    // Sibling in digibyte/src/qt/test/compattests.cpp
    uint16_t u1 = 0x1234;
    uint32_t u2 = 0x56789abc;
    uint64_t u3 = 0xdef0123456789abc;
    uint16_t e1 = 0x3412;
    uint32_t e2 = 0xbc9a7856;
    uint64_t e3 = 0xbc9a78563412f0de;
    BOOST_CHECK(bswap_16(u1) == e1);
    BOOST_CHECK(bswap_32(u2) == e2);
    BOOST_CHECK(bswap_64(u3) == e3);
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25
}

BOOST_AUTO_TEST_SUITE_END()
