// Copyright (c) 2009-2019 The Bitcoin Core developers
// Copyright (c) 2014-2019 The DigiByte Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <key.h>

#include <key_io.h>
#include <script/script.h>
#include <uint256.h>
#include <util.h>
#include <utilstrencodings.h>
#include <test/test_digibyte.h>

#include <string>
#include <vector>

#include <boost/test/unit_test.hpp>
static const std::string strSecret1 = "5HwoXVkHoRM8sL2KmNRS217n1g8mPPBomrY7yehCuXC1115WWsh";
static const std::string strSecret2 = "5J5KUK3VXP8HUefNVYPxwxVRokScZdWXpu1Tj8LfaAXMqHzMmbk";
static const std::string strSecret1C = "KwntMbt59tTsj8xqpqYqRRWufyjGunvhSyeMo3NTYpFYzZbXJ5Hp"; 
static const std::string strSecret2C = "KxN4XYdzu6f9j3EMryaMwZvUVLk3y29M4QZ2xwPoFP2zwka1aWxU";
static const std::string addr1 = "DS1P3gwq6MFtatWprr2e2J32xGPd89n75C";
static const std::string addr2 = "DMQ3t1L7BmTwL5wpZ9mek1KUaCRLJSXJWV";
static const std::string addr1C = "DU9umLs2Ze8eNRo69wbSj5HeufphJawFPh"; 
static const std::string addr2C = "DCiLe5VAcdLpGXURTDsaoryMWdMVBP9NoN";

static const std::string strAddressBad = "1HV9Lc3sNHZxwj4Zk6fB38tEmBryq2cBiF";

BOOST_FIXTURE_TEST_SUITE(key_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(key_test1)
{
    CKey key1  = DecodeSecret(strSecret1);
    BOOST_CHECK(key1.IsValid() && !key1.IsCompressed());
    CKey key2  = DecodeSecret(strSecret2);
    BOOST_CHECK(key2.IsValid() && !key2.IsCompressed());
    CKey key1C = DecodeSecret(strSecret1C);
    BOOST_CHECK(key1C.IsValid() && key1C.IsCompressed());
    CKey key2C = DecodeSecret(strSecret2C);
    BOOST_CHECK(key2C.IsValid() && key2C.IsCompressed());
    CKey bad_key = DecodeSecret(strAddressBad);
    BOOST_CHECK(!bad_key.IsValid());

    CPubKey pubkey1  = key1. GetPubKey();
    CPubKey pubkey2  = key2. GetPubKey();
    CPubKey pubkey1C = key1C.GetPubKey();
    CPubKey pubkey2C = key2C.GetPubKey();

    BOOST_CHECK(key1.VerifyPubKey(pubkey1));
    BOOST_CHECK(!key1.VerifyPubKey(pubkey1C));
    BOOST_CHECK(!key1.VerifyPubKey(pubkey2));
    BOOST_CHECK(!key1.VerifyPubKey(pubkey2C));

    BOOST_CHECK(!key1C.VerifyPubKey(pubkey1));
    BOOST_CHECK(key1C.VerifyPubKey(pubkey1C));
    BOOST_CHECK(!key1C.VerifyPubKey(pubkey2));
    BOOST_CHECK(!key1C.VerifyPubKey(pubkey2C));

    BOOST_CHECK(!key2.VerifyPubKey(pubkey1));
    BOOST_CHECK(!key2.VerifyPubKey(pubkey1C));
    BOOST_CHECK(key2.VerifyPubKey(pubkey2));
    BOOST_CHECK(!key2.VerifyPubKey(pubkey2C));

    BOOST_CHECK(!key2C.VerifyPubKey(pubkey1));
    BOOST_CHECK(!key2C.VerifyPubKey(pubkey1C));
    BOOST_CHECK(!key2C.VerifyPubKey(pubkey2));
    BOOST_CHECK(key2C.VerifyPubKey(pubkey2C));

    BOOST_CHECK(DecodeDestination(addr1)  == CTxDestination(pubkey1.GetID()));
    BOOST_CHECK(DecodeDestination(addr2)  == CTxDestination(pubkey2.GetID()));
    BOOST_CHECK(DecodeDestination(addr1C) == CTxDestination(pubkey1C.GetID()));
    BOOST_CHECK(DecodeDestination(addr2C) == CTxDestination(pubkey2C.GetID()));

    for (int n=0; n<16; n++)
    {
        std::string strMsg = strprintf("Very secret message %i: 11", n);
        uint256 hashMsg = Hash(strMsg.begin(), strMsg.end());

        // normal signatures

        std::vector<unsigned char> sign1, sign2, sign1C, sign2C;

        BOOST_CHECK(key1.Sign (hashMsg, sign1));
        BOOST_CHECK(key2.Sign (hashMsg, sign2));
        BOOST_CHECK(key1C.Sign(hashMsg, sign1C));
        BOOST_CHECK(key2C.Sign(hashMsg, sign2C));

        BOOST_CHECK( pubkey1.Verify(hashMsg, sign1));
        BOOST_CHECK(!pubkey1.Verify(hashMsg, sign2));
        BOOST_CHECK( pubkey1.Verify(hashMsg, sign1C));
        BOOST_CHECK(!pubkey1.Verify(hashMsg, sign2C));

        BOOST_CHECK(!pubkey2.Verify(hashMsg, sign1));
        BOOST_CHECK( pubkey2.Verify(hashMsg, sign2));
        BOOST_CHECK(!pubkey2.Verify(hashMsg, sign1C));
        BOOST_CHECK( pubkey2.Verify(hashMsg, sign2C));

        BOOST_CHECK( pubkey1C.Verify(hashMsg, sign1));
        BOOST_CHECK(!pubkey1C.Verify(hashMsg, sign2));
        BOOST_CHECK( pubkey1C.Verify(hashMsg, sign1C));
        BOOST_CHECK(!pubkey1C.Verify(hashMsg, sign2C));

        BOOST_CHECK(!pubkey2C.Verify(hashMsg, sign1));
        BOOST_CHECK( pubkey2C.Verify(hashMsg, sign2));
        BOOST_CHECK(!pubkey2C.Verify(hashMsg, sign1C));
        BOOST_CHECK( pubkey2C.Verify(hashMsg, sign2C));

        // compact signatures (with key recovery)

        std::vector<unsigned char> csign1, csign2, csign1C, csign2C;

        BOOST_CHECK(key1.SignCompact (hashMsg, csign1));
        BOOST_CHECK(key2.SignCompact (hashMsg, csign2));
        BOOST_CHECK(key1C.SignCompact(hashMsg, csign1C));
        BOOST_CHECK(key2C.SignCompact(hashMsg, csign2C));

        CPubKey rkey1, rkey2, rkey1C, rkey2C;

        BOOST_CHECK(rkey1.RecoverCompact (hashMsg, csign1));
        BOOST_CHECK(rkey2.RecoverCompact (hashMsg, csign2));
        BOOST_CHECK(rkey1C.RecoverCompact(hashMsg, csign1C));
        BOOST_CHECK(rkey2C.RecoverCompact(hashMsg, csign2C));

        BOOST_CHECK(rkey1  == pubkey1);
        BOOST_CHECK(rkey2  == pubkey2);
        BOOST_CHECK(rkey1C == pubkey1C);
        BOOST_CHECK(rkey2C == pubkey2C);
    }

    // test deterministic signing

    std::vector<unsigned char> detsig, detsigc;
    std::string strMsg = "Very deterministic message";
    uint256 hashMsg = Hash(strMsg.begin(), strMsg.end());
    BOOST_CHECK(key1.Sign(hashMsg, detsig));
    BOOST_CHECK(key1C.Sign(hashMsg, detsigc));
    BOOST_CHECK(detsig == detsigc);
    BOOST_CHECK(detsig == ParseHex("3044022064b7d73eee352ebd0a9eea03b56141bb80ac71885506ca38cae731000a704b50022047ff0729ca4e6ffd41b7b4928cfa05ab1148dc4ecb7030bec53f7009a86d6ad2"));
    BOOST_CHECK(key2.Sign(hashMsg, detsig));
    BOOST_CHECK(key2C.Sign(hashMsg, detsigc));
    BOOST_CHECK(detsig == detsigc);
    BOOST_CHECK(detsig == ParseHex("30440220056e087458d463ac8197b2036c4cf2fd88f6f19318d313c47d299682b5e9b55e022063e9cb599949c38a1762c18c5440e382779d63df12702ab93efebd510f28f3fc"));
    BOOST_CHECK(key1.SignCompact(hashMsg, detsig));
    BOOST_CHECK(key1C.SignCompact(hashMsg, detsigc));
    BOOST_CHECK(detsig == ParseHex("1c64b7d73eee352ebd0a9eea03b56141bb80ac71885506ca38cae731000a704b5047ff0729ca4e6ffd41b7b4928cfa05ab1148dc4ecb7030bec53f7009a86d6ad2"));
    BOOST_CHECK(detsigc == ParseHex("2064b7d73eee352ebd0a9eea03b56141bb80ac71885506ca38cae731000a704b5047ff0729ca4e6ffd41b7b4928cfa05ab1148dc4ecb7030bec53f7009a86d6ad2"));
    BOOST_CHECK(key2.SignCompact(hashMsg, detsig));
    BOOST_CHECK(key2C.SignCompact(hashMsg, detsigc));
    BOOST_CHECK(detsig == ParseHex("1b056e087458d463ac8197b2036c4cf2fd88f6f19318d313c47d299682b5e9b55e63e9cb599949c38a1762c18c5440e382779d63df12702ab93efebd510f28f3fc"));
    BOOST_CHECK(detsigc == ParseHex("1f056e087458d463ac8197b2036c4cf2fd88f6f19318d313c47d299682b5e9b55e63e9cb599949c38a1762c18c5440e382779d63df12702ab93efebd510f28f3fc"));
}

BOOST_AUTO_TEST_CASE(key_signature_tests)
{
    // When entropy is specified, we should see at least one high R signature within 20 signatures
    CKey key = DecodeSecret(strSecret1);
    std::string msg = "A message to be signed";
    uint256 msg_hash = Hash(msg.begin(), msg.end());
    std::vector<unsigned char> sig;
    bool found = false;

    for (int i = 1; i <=20; ++i) {
        sig.clear();
        key.Sign(msg_hash, sig, false, i);
        found = sig[3] == 0x21 && sig[4] == 0x00;
        if (found) {
            break;
        }
    }
    BOOST_CHECK(found);

    // When entropy is not specified, we should always see low R signatures that are less than 70 bytes in 256 tries
    // We should see at least one signature that is less than 70 bytes.
    found = true;
    bool found_small = false;
    for (int i = 0; i < 256; ++i) {
        sig.clear();
        std::string msg = "A message to be signed" + std::to_string(i);
        msg_hash = Hash(msg.begin(), msg.end());
        key.Sign(msg_hash, sig);
        found = sig[3] == 0x20;
        BOOST_CHECK(sig.size() <= 70);
        found_small |= sig.size() < 70;
    }
    BOOST_CHECK(found);
    BOOST_CHECK(found_small);
}

BOOST_AUTO_TEST_SUITE_END()
