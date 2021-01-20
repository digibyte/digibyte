<<<<<<< HEAD
// Copyright (c) 2009-2019 The Bitcoin Core developers
// Copyright (c) 2014-2019 The DigiByte Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <utilstrencodings.h>
#include <test/test_digibyte.h>
=======
// Copyright (c) 2012-2020 The DigiByte Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <test/util/setup_common.h>
#include <util/strencodings.h>
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25

#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE(base32_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(base32_testvectors)
{
    static const std::string vstrIn[]  = {"","f","fo","foo","foob","fooba","foobar"};
    static const std::string vstrOut[] = {"","my======","mzxq====","mzxw6===","mzxw6yq=","mzxw6ytb","mzxw6ytboi======"};
    static const std::string vstrOutNoPadding[] = {"","my","mzxq","mzxw6","mzxw6yq","mzxw6ytb","mzxw6ytboi"};
    for (unsigned int i=0; i<sizeof(vstrIn)/sizeof(vstrIn[0]); i++)
    {
        std::string strEnc = EncodeBase32(vstrIn[i]);
        BOOST_CHECK_EQUAL(strEnc, vstrOut[i]);
        strEnc = EncodeBase32(vstrIn[i], false);
        BOOST_CHECK_EQUAL(strEnc, vstrOutNoPadding[i]);
        std::string strDec = DecodeBase32(vstrOut[i]);
        BOOST_CHECK_EQUAL(strDec, vstrIn[i]);
    }

    // Decoding strings with embedded NUL characters should fail
    bool failure;
    (void)DecodeBase32(std::string("invalid", 7), &failure);
    BOOST_CHECK_EQUAL(failure, true);
    (void)DecodeBase32(std::string("AWSX3VPP", 8), &failure);
    BOOST_CHECK_EQUAL(failure, false);
    (void)DecodeBase32(std::string("AWSX3VPP\0invalid", 16), &failure);
    BOOST_CHECK_EQUAL(failure, true);
    (void)DecodeBase32(std::string("AWSX3VPPinvalid", 15), &failure);
    BOOST_CHECK_EQUAL(failure, true);
}

BOOST_AUTO_TEST_SUITE_END()
