#!/usr/bin/env python3
# Copyright (c) 2016-2021 The DigiByte Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
"""Test the SegWit changeover logic."""

from decimal import Decimal

from test_framework.address import (
    key_to_p2pkh,
    program_to_witness,
    script_to_p2sh,
    script_to_p2sh_p2wsh,
    script_to_p2wsh,
)
from test_framework.blocktools import (
    send_to_witness,
    witness_script,
)
from test_framework.descriptors import descsum_create
from test_framework.messages import (
    COIN,
    COutPoint,
    CTransaction,
    CTxIn,
    CTxOut,
    tx_from_hex,
)
from test_framework.script import (
    CScript,
    OP_0,
    OP_1,
    OP_DROP,
    OP_TRUE,
)
from test_framework.script_util import (
    key_to_p2pk_script,
    key_to_p2pkh_script,
    key_to_p2wpkh_script,
    keys_to_multisig_script,
    script_to_p2sh_script,
    script_to_p2wsh_script,
)
from test_framework.test_framework import DigiByteTestFramework
from test_framework.util import (
    assert_equal,
    assert_greater_than_or_equal,
    assert_is_hex_string,
    assert_raises_rpc_error,
    try_rpc,
)
from test_framework.wallet_util import (
    get_generate_key,
)

NODE_0 = 0
NODE_2 = 2
P2WPKH = 0
P2WSH = 1


def getutxo(txid):
    utxo = {}
    utxo["vout"] = 0
    utxo["txid"] = txid
    return utxo


def find_spendable_utxo(node, min_value):
    for utxo in node.listunspent(query_options={'minimumAmount': min_value}):
        if utxo['spendable']:
            return utxo

    raise AssertionError(f"Unspent output equal or higher than {min_value} not found")


txs_mined = {}  # txindex from txid to blockhash


class SegWitTest(DigiByteTestFramework):
    def set_test_params(self):
        self.setup_clean_chain = True
        self.num_nodes = 3
        # This test tests SegWit both pre and post-activation, so use the normal BIP9 activation.
        self.extra_args = [
            [
                "-acceptnonstdtxn=1",
                "-rpcserialversion=0",
                "-testactivationheight=segwit@432",
                "-addresstype=legacy",
            ],
            [
                "-acceptnonstdtxn=1",
                "-rpcserialversion=1",
                "-testactivationheight=segwit@432",
                "-addresstype=legacy",
            ],
            [
                "-acceptnonstdtxn=1",
                "-testactivationheight=segwit@432",
                "-addresstype=legacy",
            ],
        ]
        self.rpc_timeout = 120

    def skip_test_if_missing_module(self):
        self.skip_if_no_wallet()

    def setup_network(self):
        super().setup_network()
        self.connect_nodes(0, 2)
        self.sync_all()

    def success_mine(self, node, txid, sign, redeem_script=""):
        send_to_witness(1, node, getutxo(txid), self.pubkey[0], False, Decimal("71999.998"), sign, redeem_script)
        block = self.generate(node, 1)
        assert_equal(len(node.getblock(block[0])["tx"]), 2)
        self.sync_blocks()

    def skip_mine(self, node, txid, sign, redeem_script=""):
        send_to_witness(1, node, getutxo(txid), self.pubkey[0], False, Decimal("71999.998"), sign, redeem_script)
        block = self.generate(node, 1)
        assert_equal(len(node.getblock(block[0])["tx"]), 1)
        self.sync_blocks()

    def fail_accept(self, node, error_msg, txid, sign, redeem_script=""):
        assert_raises_rpc_error(-26, error_msg, send_to_witness, use_p2wsh=1, node=node, utxo=getutxo(txid), pubkey=self.pubkey[0], encode_p2sh=False, amount=Decimal("71999.998"), sign=sign, insert_redeem_script=redeem_script)

    def run_test(self):
        self.generate(self.nodes[0], 161)  # block 161

        self.log.info("Verify sigops are counted in GBT with pre-BIP141 rules before the fork")
        txid = self.nodes[0].sendtoaddress(self.nodes[0].getnewaddress(), 1)
        tmpl = self.nodes[0].getblocktemplate({'rules': ['segwit']})
        assert_equal(tmpl['sizelimit'], 1000000)
        assert 'weightlimit' not in tmpl
        assert_equal(tmpl['sigoplimit'], 20000)
        assert_equal(tmpl['transactions'][0]['hash'], txid)
        assert_equal(tmpl['transactions'][0]['sigops'], 2)
        assert '!segwit' not in tmpl['rules']
        self.generate(self.nodes[0], 1)  # block 162

        balance_presetup = self.nodes[0].getbalance()
        self.pubkey = []
        p2sh_ids = []  # p2sh_ids[NODE][TYPE] is an array of txids that spend to P2WPKH (TYPE=0) or P2WSH (TYPE=1) scripts to an address for NODE embedded in p2sh
        wit_ids = []  # wit_ids[NODE][TYPE] is an array of txids that spend to P2WPKH (TYPE=0) or P2WSH (TYPE=1) scripts to an address for NODE via bare witness
        for i in range(3):
            key = get_generate_key()
            self.pubkey.append(key.pubkey)

            multiscript = keys_to_multisig_script([self.pubkey[-1]])
            p2sh_ms_addr = self.nodes[i].createmultisig(1, [self.pubkey[-1]], 'p2sh-segwit')['address']
            bip173_ms_addr = self.nodes[i].createmultisig(1, [self.pubkey[-1]], 'bech32')['address']
            assert_equal(p2sh_ms_addr, script_to_p2sh_p2wsh(multiscript))
            assert_equal(bip173_ms_addr, script_to_p2wsh(multiscript))

            p2sh_ms_desc = descsum_create(f"sh(wsh(multi(1,{key.privkey})))")
            bip173_ms_desc = descsum_create(f"wsh(multi(1,{key.privkey}))")
            assert_equal(self.nodes[i].deriveaddresses(p2sh_ms_desc)[0], p2sh_ms_addr)
            assert_equal(self.nodes[i].deriveaddresses(bip173_ms_desc)[0], bip173_ms_addr)

            sh_wpkh_desc = descsum_create(f"sh(wpkh({key.privkey}))")
            wpkh_desc = descsum_create(f"wpkh({key.privkey})")
            assert_equal(self.nodes[i].deriveaddresses(sh_wpkh_desc)[0], key.p2sh_p2wpkh_addr)
            assert_equal(self.nodes[i].deriveaddresses(wpkh_desc)[0], key.p2wpkh_addr)

            if self.options.descriptors:
                res = self.nodes[i].importdescriptors([
                {"desc": p2sh_ms_desc, "timestamp": "now"},
                {"desc": bip173_ms_desc, "timestamp": "now"},
                {"desc": sh_wpkh_desc, "timestamp": "now"},
                {"desc": wpkh_desc, "timestamp": "now"},
            ])
            else:
                # The nature of the legacy wallet is that this import results in also adding all of the necessary scripts
                res = self.nodes[i].importmulti([
                    {"desc": p2sh_ms_desc, "timestamp": "now"},
                ])
            assert all([r["success"] for r in res])

            p2sh_ids.append([])
            wit_ids.append([])
            for _ in range(2):
                p2sh_ids[i].append([])
                wit_ids[i].append([])

        for _ in range(5):
            for n in range(3):
                for v in range(2):
                    wit_ids[n][v].append(send_to_witness(v, self.nodes[0], find_spendable_utxo(self.nodes[0], 72000), self.pubkey[n], False, Decimal("71999.999")))
                    p2sh_ids[n][v].append(send_to_witness(v, self.nodes[0], find_spendable_utxo(self.nodes[0], 72000), self.pubkey[n], True, Decimal("71999.999")))

        self.generate(self.nodes[0], 1)  # block 163

        # Make sure all nodes recognize the transactions as theirs
        assert_equal(self.nodes[0].getbalance(), balance_presetup - 60 * 72000 + 20 * Decimal("71999.999") + 72000)
        assert_equal(self.nodes[1].getbalance(), 20 * Decimal("71999.999"))
        assert_equal(self.nodes[2].getbalance(), 20 * Decimal("71999.999"))

        self.generate(self.nodes[0], 260)  # block 423

        self.log.info("Verify witness txs are skipped for mining before the fork")
        self.skip_mine(self.nodes[2], wit_ids[NODE_2][P2WPKH][0], True)  # block 424
        self.skip_mine(self.nodes[2], wit_ids[NODE_2][P2WSH][0], True)  # block 425
        self.skip_mine(self.nodes[2], p2sh_ids[NODE_2][P2WPKH][0], True)  # block 426
        self.skip_mine(self.nodes[2], p2sh_ids[NODE_2][P2WSH][0], True)  # block 427

        self.log.info("Verify unsigned p2sh witness txs without a redeem script are invalid")
        self.fail_accept(self.nodes[2], "mandatory-script-verify-flag-failed (Operation not valid with the current stack size)", p2sh_ids[NODE_2][P2WPKH][1], sign=False)
        self.fail_accept(self.nodes[2], "mandatory-script-verify-flag-failed (Operation not valid with the current stack size)", p2sh_ids[NODE_2][P2WSH][1], sign=False)

        self.generate(self.nodes[2], 4)  # blocks 428-431

        self.log.info("Verify previous witness txs skipped for mining can now be mined")
        assert_equal(len(self.nodes[2].getrawmempool()), 4)
        blockhash = self.generate(self.nodes[2], 1)[0]  # block 432 (first block with new rules; 432 = 144 * 3)
        assert_equal(len(self.nodes[2].getrawmempool()), 0)
        segwit_tx_list = self.nodes[2].getblock(blockhash)["tx"]
        assert_equal(len(segwit_tx_list), 5)

        self.log.info("Verify default node can't accept txs with missing witness")
        # unsigned, no scriptsig
        self.fail_accept(self.nodes[0], "non-mandatory-script-verify-flag (Witness program hash mismatch)", wit_ids[NODE_0][P2WPKH][0], sign=False)
        self.fail_accept(self.nodes[0], "non-mandatory-script-verify-flag (Witness program was passed an empty witness)", wit_ids[NODE_0][P2WSH][0], sign=False)
        self.fail_accept(self.nodes[0], "mandatory-script-verify-flag-failed (Operation not valid with the current stack size)", p2sh_ids[NODE_0][P2WPKH][0], sign=False)
        self.fail_accept(self.nodes[0], "mandatory-script-verify-flag-failed (Operation not valid with the current stack size)", p2sh_ids[NODE_0][P2WSH][0], sign=False)
        # unsigned with redeem script
        self.fail_accept(self.nodes[0], "non-mandatory-script-verify-flag (Witness program hash mismatch)", p2sh_ids[NODE_0][P2WPKH][0], sign=False, redeem_script=witness_script(False, self.pubkey[0]))
        self.fail_accept(self.nodes[0], "non-mandatory-script-verify-flag (Witness program was passed an empty witness)", p2sh_ids[NODE_0][P2WSH][0], sign=False, redeem_script=witness_script(True, self.pubkey[0]))

        self.log.info("Verify block and transaction serialization rpcs return differing serializations depending on rpc serialization flag")
        assert self.nodes[2].getblock(blockhash, False) != self.nodes[0].getblock(blockhash, False)
        assert self.nodes[1].getblock(blockhash, False) == self.nodes[2].getblock(blockhash, False)

        for tx_id in segwit_tx_list:
            tx = tx_from_hex(self.nodes[2].gettransaction(tx_id)["hex"])
            assert self.nodes[2].getrawtransaction(tx_id, False, blockhash) != self.nodes[0].getrawtransaction(tx_id, False, blockhash)
            assert self.nodes[1].getrawtransaction(tx_id, False, blockhash) == self.nodes[2].getrawtransaction(tx_id, False, blockhash)
            assert self.nodes[0].getrawtransaction(tx_id, False, blockhash) != self.nodes[2].gettransaction(tx_id)["hex"]
            assert self.nodes[1].getrawtransaction(tx_id, False, blockhash) == self.nodes[2].gettransaction(tx_id)["hex"]
            assert self.nodes[0].getrawtransaction(tx_id, False, blockhash) == tx.serialize_without_witness().hex()

        # Coinbase contains the witness commitment nonce, check that RPC shows us
        coinbase_txid = self.nodes[2].getblock(blockhash)['tx'][0]
        coinbase_tx = self.nodes[2].gettransaction(txid=coinbase_txid, verbose=True)
        witnesses = coinbase_tx["decoded"]["vin"][0]["txinwitness"]
        assert_equal(len(witnesses), 1)
        assert_is_hex_string(witnesses[0])
        assert_equal(witnesses[0], '00' * 32)

        self.log.info("Verify witness txs without witness data are invalid after the fork")
        self.fail_accept(self.nodes[2], 'non-mandatory-script-verify-flag (Witness program hash mismatch)', wit_ids[NODE_2][P2WPKH][2], sign=False)
        self.fail_accept(self.nodes[2], 'non-mandatory-script-verify-flag (Witness program was passed an empty witness)', wit_ids[NODE_2][P2WSH][2], sign=False)
        self.fail_accept(self.nodes[2], 'non-mandatory-script-verify-flag (Witness program hash mismatch)', p2sh_ids[NODE_2][P2WPKH][2], sign=False, redeem_script=witness_script(False, self.pubkey[2]))
        self.fail_accept(self.nodes[2], 'non-mandatory-script-verify-flag (Witness program was passed an empty witness)', p2sh_ids[NODE_2][P2WSH][2], sign=False, redeem_script=witness_script(True, self.pubkey[2]))

        self.log.info("Verify default node can now use witness txs")
        self.success_mine(self.nodes[0], wit_ids[NODE_0][P2WPKH][0], True)  # block 432
        self.success_mine(self.nodes[0], wit_ids[NODE_0][P2WSH][0], True)  # block 433
        self.success_mine(self.nodes[0], p2sh_ids[NODE_0][P2WPKH][0], True)  # block 434
        self.success_mine(self.nodes[0], p2sh_ids[NODE_0][P2WSH][0], True)  # block 435

        self.log.info("Verify sigops are counted in GBT with BIP141 rules after the fork")
        txid = self.nodes[0].sendtoaddress(self.nodes[0].getnewaddress(), 1)
        raw_tx = self.nodes[0].getrawtransaction(txid, True)
        tmpl = self.nodes[0].getblocktemplate({'rules': ['segwit']})
        assert_greater_than_or_equal(tmpl['sizelimit'], 3999577)  # actual maximum size is lower due to minimum mandatory non-witness data
        assert_equal(tmpl['weightlimit'], 4000000)
        assert_equal(tmpl['sigoplimit'], 80000)
        assert_equal(tmpl['transactions'][0]['txid'], txid)
        expected_sigops = 9 if 'txinwitness' in raw_tx["vin"][0] else 8
        assert_equal(tmpl['transactions'][0]['sigops'], expected_sigops)
        assert '!segwit' in tmpl['rules']

        self.generate(self.nodes[0], 1)  # Mine a block to clear the gbt cache

        self.log.info("Non-segwit miners are able to use GBT response after activation.")
        # Create a 3-tx chain: tx1 (non-segwit input, paying to a segwit output) ->
        #                      tx2 (segwit input, paying to a non-segwit output) ->
        #                      tx3 (non-segwit input, paying to a non-segwit output).
        # tx1 is allowed to appear in the block, but no others.
        txid1 = send_to_witness(1, self.nodes[0], find_spendable_utxo(self.nodes[0], 72000), self.pubkey[0], False, Decimal("71999.996"))
        hex_tx = self.nodes[0].gettransaction(txid)['hex']
        tx = tx_from_hex(hex_tx)
        assert tx.wit.is_null()  # This should not be a segwit input
        assert txid1 in self.nodes[0].getrawmempool()

        tx1_hex = self.nodes[0].gettransaction(txid1)['hex']
        tx1 = tx_from_hex(tx1_hex)

        # Check that wtxid is properly reported in mempool entry (txid1)
        assert_equal(int(self.nodes[0].getmempoolentry(txid1)["wtxid"], 16), tx1.calc_sha256(True))

        # Check that weight and vsize are properly reported in mempool entry (txid1)
        assert_equal(self.nodes[0].getmempoolentry(txid1)["vsize"], tx1.get_vsize())
        assert_equal(self.nodes[0].getmempoolentry(txid1)["weight"], tx1.get_weight())

        # Now create tx2, which will spend from txid1.
        tx = CTransaction()
        tx.vin.append(CTxIn(COutPoint(int(txid1, 16), 0), b''))
        tx.vout.append(CTxOut(int(71999.99 * COIN), CScript([OP_TRUE, OP_DROP] * 15 + [OP_TRUE])))
        tx2_hex = self.nodes[0].signrawtransactionwithwallet(tx.serialize().hex())['hex']
        txid2 = self.nodes[0].sendrawtransaction(tx2_hex)
        tx = tx_from_hex(tx2_hex)
        assert not tx.wit.is_null()

        # Check that wtxid is properly reported in mempool entry (txid2)
        assert_equal(int(self.nodes[0].getmempoolentry(txid2)["wtxid"], 16), tx.calc_sha256(True))

        # Check that weight and vsize are properly reported in mempool entry (txid2)
        assert_equal(self.nodes[0].getmempoolentry(txid2)["vsize"], tx.get_vsize())
        assert_equal(self.nodes[0].getmempoolentry(txid2)["weight"], tx.get_weight())

        # Now create tx3, which will spend from txid2
        tx = CTransaction()
        tx.vin.append(CTxIn(COutPoint(int(txid2, 16), 0), b""))
        tx.vout.append(CTxOut(int(71999.95 * COIN), CScript([OP_TRUE, OP_DROP] * 15 + [OP_TRUE])))  # Huge fee
        tx.calc_sha256()
        txid3 = self.nodes[0].sendrawtransaction(hexstring=tx.serialize().hex(), maxfeerate=0)
        assert tx.wit.is_null()
        assert txid3 in self.nodes[0].getrawmempool()

        # Check that getblocktemplate includes all transactions.
        template = self.nodes[0].getblocktemplate({"rules": ["segwit"]})
        template_txids = [t['txid'] for t in template['transactions']]
        assert txid1 in template_txids
        assert txid2 in template_txids
        assert txid3 in template_txids

        # Check that wtxid is properly reported in mempool entry (txid3)
        assert_equal(int(self.nodes[0].getmempoolentry(txid3)["wtxid"], 16), tx.calc_sha256(True))

        # Check that weight and vsize are properly reported in mempool entry (txid3)
        assert_equal(self.nodes[0].getmempoolentry(txid3)["vsize"], tx.get_vsize())
        assert_equal(self.nodes[0].getmempoolentry(txid3)["weight"], tx.get_weight())

        # Mine a block to clear the gbt cache again.
        self.generate(self.nodes[0], 1)

        if not self.options.descriptors:
            self.log.info("Verify behaviour of importaddress and listunspent")

            # Some public keys to be used later
            pubkeys = [
                "034e05dace5bcaf1d2ac67143bd071d4e040e5777663797310d2a3949ff15d9d4b",  # edSdzE6zFFJ8hMVEWh9idnu9h8uYPQUJLknbRANvMooiMTfQmsCS
                "02e0423ecad2fffb75c7414eb6bc8757e58c65a89ac5f9004d927e885633d7d29e",  # eboTiEYQbmStx9kN6ddGorGc45DxuiSgtytsaYmutW5iU4vWvLeF
                "04bcf5a134f4fd752048981454ea9fc95999b8553191d488ec44dd644e30331c9ac8a26b9510a153b21e84f77b41755606cd91012b3900a79ef3e367b68733adc1",  # 9Y1pSRPsx4PcmnX1Wd9j1DAW51BjaWEdXPcUFU4NdVpFvR2rNhH
                "0248bfd2bf6acd6ccec115c253460bbe5e4536964351aad94cc2dcc236dec83359",  # eeU9UuVcudMDbMwGnmZdYG1PYYtivFUiCzhtrxZbAnCr8dSXLXhz
                "02f9b7252b245ccc4a8264cef7dd1db325b138e7942a68a1a45e5b4c22ae529397",  # eh8Kjz7RDg6FrHPSru8xQZJyVgJFptVXZzusrY6esAEKboRu8kZs
                "03d3d161080106df78d1f535093138c1acbc7629c4a7cec40d779a430c362ca857",  # ehLPHFXfemHKbkZ1J3bVjq1vyB5hn9rTwXZHX6fah17jLKBwFDXh
                "047af4be859bf97b26d60e56665a9194c7ef6a8cdb46113fc987f0c7ffdea3994d4af42cce1a39d7b8db96f08aa63bc8abcca2b441876ade8123aacf92493f9b77",  # 9XzyrpAZo65SRLKChxQVbQ7L7MmWLDWeRvkPZVgZ6eGKvdgXbWC
            ]

            # Import a compressed key and an uncompressed key, generate some multisig addresses
            self.nodes[0].importprivkey("9WpZT7sXr6Zy6183PR89rxVzKbXrBSuDMfUDVVfErSwabyoJEa9")
            uncompressed_spendable_address = ["su9fCxU4iXjMgLe1Yx63jJs6WEJXeNvzv4"]
            self.nodes[0].importprivkey("efAPpKtYZjAcYHopymPdqjYd3LVxYGg2GdfyisVMZyP7SfMchyw1")
            compressed_spendable_address = ["ssEZmM9N4RxyVNd2rKXPoU6NUEGip1ySnf"]
            assert not self.nodes[0].getaddressinfo(uncompressed_spendable_address[0])['iscompressed']
            assert self.nodes[0].getaddressinfo(compressed_spendable_address[0])['iscompressed']

            self.nodes[0].importpubkey(pubkeys[0])
            compressed_solvable_address = [key_to_p2pkh(pubkeys[0])]
            self.nodes[0].importpubkey(pubkeys[1])
            compressed_solvable_address.append(key_to_p2pkh(pubkeys[1]))
            self.nodes[0].importpubkey(pubkeys[2])
            uncompressed_solvable_address = [key_to_p2pkh(pubkeys[2])]

            spendable_anytime = []                      # These outputs should be seen anytime after importprivkey and addmultisigaddress
            spendable_after_importaddress = []          # These outputs should be seen after importaddress
            solvable_after_importaddress = []           # These outputs should be seen after importaddress but not spendable
            unsolvable_after_importaddress = []         # These outputs should be unsolvable after importaddress
            solvable_anytime = []                       # These outputs should be solvable after importpubkey
            unseen_anytime = []                         # These outputs should never be seen

            uncompressed_spendable_address.append(self.nodes[0].addmultisigaddress(2, [uncompressed_spendable_address[0], compressed_spendable_address[0]])['address'])
            uncompressed_spendable_address.append(self.nodes[0].addmultisigaddress(2, [uncompressed_spendable_address[0], uncompressed_spendable_address[0]])['address'])
            compressed_spendable_address.append(self.nodes[0].addmultisigaddress(2, [compressed_spendable_address[0], compressed_spendable_address[0]])['address'])
            uncompressed_solvable_address.append(self.nodes[0].addmultisigaddress(2, [compressed_spendable_address[0], uncompressed_solvable_address[0]])['address'])
            compressed_solvable_address.append(self.nodes[0].addmultisigaddress(2, [compressed_spendable_address[0], compressed_solvable_address[0]])['address'])
            compressed_solvable_address.append(self.nodes[0].addmultisigaddress(2, [compressed_solvable_address[0], compressed_solvable_address[1]])['address'])

            # Test multisig_without_privkey
            # We have 2 public keys without private keys, use addmultisigaddress to add to wallet.
            # Money sent to P2SH of multisig of this should only be seen after importaddress with the BASE58 P2SH address.

            multisig_without_privkey_address = self.nodes[0].addmultisigaddress(2, [pubkeys[3], pubkeys[4]])['address']
            script = keys_to_multisig_script([pubkeys[3], pubkeys[4]])
            solvable_after_importaddress.append(script_to_p2sh_script(script))

            for i in compressed_spendable_address:
                v = self.nodes[0].getaddressinfo(i)
                if v['isscript']:
                    [bare, p2sh, p2wsh, p2sh_p2wsh] = self.p2sh_address_to_script(v)
                    # p2sh multisig with compressed keys should always be spendable
                    spendable_anytime.extend([p2sh])
                    # bare multisig can be watched and signed, but is not treated as ours
                    solvable_after_importaddress.extend([bare])
                    # P2WSH and P2SH(P2WSH) multisig with compressed keys are spendable after direct importaddress
                    spendable_after_importaddress.extend([p2wsh, p2sh_p2wsh])
                else:
                    [p2wpkh, p2sh_p2wpkh, p2pk, p2pkh, p2sh_p2pk, p2sh_p2pkh, p2wsh_p2pk, p2wsh_p2pkh, p2sh_p2wsh_p2pk, p2sh_p2wsh_p2pkh] = self.p2pkh_address_to_script(v)
                    # normal P2PKH and P2PK with compressed keys should always be spendable
                    spendable_anytime.extend([p2pkh, p2pk])
                    # P2SH_P2PK, P2SH_P2PKH with compressed keys are spendable after direct importaddress
                    spendable_after_importaddress.extend([p2sh_p2pk, p2sh_p2pkh, p2wsh_p2pk, p2wsh_p2pkh, p2sh_p2wsh_p2pk, p2sh_p2wsh_p2pkh])
                    # P2WPKH and P2SH_P2WPKH with compressed keys should always be spendable
                    spendable_anytime.extend([p2wpkh, p2sh_p2wpkh])

            for i in uncompressed_spendable_address:
                v = self.nodes[0].getaddressinfo(i)
                if v['isscript']:
                    [bare, p2sh, p2wsh, p2sh_p2wsh] = self.p2sh_address_to_script(v)
                    # p2sh multisig with uncompressed keys should always be spendable
                    spendable_anytime.extend([p2sh])
                    # bare multisig can be watched and signed, but is not treated as ours
                    solvable_after_importaddress.extend([bare])
                    # P2WSH and P2SH(P2WSH) multisig with uncompressed keys are never seen
                    unseen_anytime.extend([p2wsh, p2sh_p2wsh])
                else:
                    [p2wpkh, p2sh_p2wpkh, p2pk, p2pkh, p2sh_p2pk, p2sh_p2pkh, p2wsh_p2pk, p2wsh_p2pkh, p2sh_p2wsh_p2pk, p2sh_p2wsh_p2pkh] = self.p2pkh_address_to_script(v)
                    # normal P2PKH and P2PK with uncompressed keys should always be spendable
                    spendable_anytime.extend([p2pkh, p2pk])
                    # P2SH_P2PK and P2SH_P2PKH are spendable after direct importaddress
                    spendable_after_importaddress.extend([p2sh_p2pk, p2sh_p2pkh])
                    # Witness output types with uncompressed keys are never seen
                    unseen_anytime.extend([p2wpkh, p2sh_p2wpkh, p2wsh_p2pk, p2wsh_p2pkh, p2sh_p2wsh_p2pk, p2sh_p2wsh_p2pkh])

            for i in compressed_solvable_address:
                v = self.nodes[0].getaddressinfo(i)
                if v['isscript']:
                    # Multisig without private is not seen after addmultisigaddress, but seen after importaddress
                    [bare, p2sh, p2wsh, p2sh_p2wsh] = self.p2sh_address_to_script(v)
                    solvable_after_importaddress.extend([bare, p2sh, p2wsh, p2sh_p2wsh])
                else:
                    [p2wpkh, p2sh_p2wpkh, p2pk, p2pkh, p2sh_p2pk, p2sh_p2pkh, p2wsh_p2pk, p2wsh_p2pkh, p2sh_p2wsh_p2pk, p2sh_p2wsh_p2pkh] = self.p2pkh_address_to_script(v)
                    # normal P2PKH, P2PK, P2WPKH and P2SH_P2WPKH with compressed keys should always be seen
                    solvable_anytime.extend([p2pkh, p2pk, p2wpkh, p2sh_p2wpkh])
                    # P2SH_P2PK, P2SH_P2PKH with compressed keys are seen after direct importaddress
                    solvable_after_importaddress.extend([p2sh_p2pk, p2sh_p2pkh, p2wsh_p2pk, p2wsh_p2pkh, p2sh_p2wsh_p2pk, p2sh_p2wsh_p2pkh])

            for i in uncompressed_solvable_address:
                v = self.nodes[0].getaddressinfo(i)
                if v['isscript']:
                    [bare, p2sh, p2wsh, p2sh_p2wsh] = self.p2sh_address_to_script(v)
                    # Base uncompressed multisig without private is not seen after addmultisigaddress, but seen after importaddress
                    solvable_after_importaddress.extend([bare, p2sh])
                    # P2WSH and P2SH(P2WSH) multisig with uncompressed keys are never seen
                    unseen_anytime.extend([p2wsh, p2sh_p2wsh])
                else:
                    [p2wpkh, p2sh_p2wpkh, p2pk, p2pkh, p2sh_p2pk, p2sh_p2pkh, p2wsh_p2pk, p2wsh_p2pkh, p2sh_p2wsh_p2pk, p2sh_p2wsh_p2pkh] = self.p2pkh_address_to_script(v)
                    # normal P2PKH and P2PK with uncompressed keys should always be seen
                    solvable_anytime.extend([p2pkh, p2pk])
                    # P2SH_P2PK, P2SH_P2PKH with uncompressed keys are seen after direct importaddress
                    solvable_after_importaddress.extend([p2sh_p2pk, p2sh_p2pkh])
                    # Witness output types with uncompressed keys are never seen
                    unseen_anytime.extend([p2wpkh, p2sh_p2wpkh, p2wsh_p2pk, p2wsh_p2pkh, p2sh_p2wsh_p2pk, p2sh_p2wsh_p2pkh])

            op1 = CScript([OP_1])
            op0 = CScript([OP_0])
            # 2N7MGY19ti4KDMSzRfPAssP6Pxyuxoi6jLe is the P2SH(P2PKH) version of mjoE3sSrb8ByYEvgnC3Aox86u1CHnfJA4V
            unsolvable_address_key = bytes.fromhex("02341AEC7587A51CDE5279E0630A531AEA2615A9F80B17E8D9376327BAEAA59E3D")
            unsolvablep2pkh = key_to_p2pkh_script(unsolvable_address_key)
            unsolvablep2wshp2pkh = script_to_p2wsh_script(unsolvablep2pkh)
            p2shop0 = script_to_p2sh_script(op0)
            p2wshop1 = script_to_p2wsh_script(op1)
            unsolvable_after_importaddress.append(unsolvablep2pkh)
            unsolvable_after_importaddress.append(unsolvablep2wshp2pkh)
            unsolvable_after_importaddress.append(op1)  # OP_1 will be imported as script
            unsolvable_after_importaddress.append(p2wshop1)
            unseen_anytime.append(op0)  # OP_0 will be imported as P2SH address with no script provided
            unsolvable_after_importaddress.append(p2shop0)

            spendable_txid = []
            solvable_txid = []
            spendable_txid.append(self.mine_and_test_listunspent(spendable_anytime, 2))
            solvable_txid.append(self.mine_and_test_listunspent(solvable_anytime, 1))
            self.mine_and_test_listunspent(spendable_after_importaddress + solvable_after_importaddress + unseen_anytime + unsolvable_after_importaddress, 0)

            importlist = []
            for i in compressed_spendable_address + uncompressed_spendable_address + compressed_solvable_address + uncompressed_solvable_address:
                v = self.nodes[0].getaddressinfo(i)
                if v['isscript']:
                    bare = bytes.fromhex(v['hex'])
                    importlist.append(bare.hex())
                    importlist.append(script_to_p2wsh_script(bare).hex())
                else:
                    pubkey = bytes.fromhex(v['pubkey'])
                    p2pk = key_to_p2pk_script(pubkey)
                    p2pkh = key_to_p2pkh_script(pubkey)
                    importlist.append(p2pk.hex())
                    importlist.append(p2pkh.hex())
                    importlist.append(key_to_p2wpkh_script(pubkey).hex())
                    importlist.append(script_to_p2wsh_script(p2pk).hex())
                    importlist.append(script_to_p2wsh_script(p2pkh).hex())

            importlist.append(unsolvablep2pkh.hex())
            importlist.append(unsolvablep2wshp2pkh.hex())
            importlist.append(op1.hex())
            importlist.append(p2wshop1.hex())

            for i in importlist:
                # import all generated addresses. The wallet already has the private keys for some of these, so catch JSON RPC
                # exceptions and continue.
                try_rpc(-4, "The wallet already contains the private key for this address or script", self.nodes[0].importaddress, i, "", False, True)

            self.nodes[0].importaddress(script_to_p2sh(op0))  # import OP_0 as address only
            self.nodes[0].importaddress(multisig_without_privkey_address)  # Test multisig_without_privkey

            spendable_txid.append(self.mine_and_test_listunspent(spendable_anytime + spendable_after_importaddress, 2))
            solvable_txid.append(self.mine_and_test_listunspent(solvable_anytime + solvable_after_importaddress, 1))
            self.mine_and_test_listunspent(unsolvable_after_importaddress, 1)
            self.mine_and_test_listunspent(unseen_anytime, 0)

            spendable_txid.append(self.mine_and_test_listunspent(spendable_anytime + spendable_after_importaddress, 2))
            solvable_txid.append(self.mine_and_test_listunspent(solvable_anytime + solvable_after_importaddress, 1))
            self.mine_and_test_listunspent(unsolvable_after_importaddress, 1)
            self.mine_and_test_listunspent(unseen_anytime, 0)

            # Repeat some tests. This time we don't add witness scripts with importaddress
            # Import a compressed key and an uncompressed key, generate some multisig addresses
            self.nodes[0].importprivkey("9XHf5DujkEgpSSLNPQJhzC9uTne8CNAkANPyKSVbwNyMAeuj3yn")
            uncompressed_spendable_address = ["t4LrP9nZrhY2zijA6VMERNkBDojjpSbpyk"]
            self.nodes[0].importprivkey("ecL1RtGACiNhFDA3iGaFHaqNzDfHt3vfyttoL9QU2HC4yL5gTzR8")
            compressed_spendable_address = ["svCDbdBn7kpoH2ComzqxrPiuEDPhYA8Fak"]

            self.nodes[0].importpubkey(pubkeys[5])
            compressed_solvable_address = [key_to_p2pkh(pubkeys[5])]
            self.nodes[0].importpubkey(pubkeys[6])
            uncompressed_solvable_address = [key_to_p2pkh(pubkeys[6])]

            unseen_anytime = []                         # These outputs should never be seen
            solvable_anytime = []                       # These outputs should be solvable after importpubkey
            unseen_anytime = []                         # These outputs should never be seen

            uncompressed_spendable_address.append(self.nodes[0].addmultisigaddress(2, [uncompressed_spendable_address[0], compressed_spendable_address[0]])['address'])
            uncompressed_spendable_address.append(self.nodes[0].addmultisigaddress(2, [uncompressed_spendable_address[0], uncompressed_spendable_address[0]])['address'])
            compressed_spendable_address.append(self.nodes[0].addmultisigaddress(2, [compressed_spendable_address[0], compressed_spendable_address[0]])['address'])
            uncompressed_solvable_address.append(self.nodes[0].addmultisigaddress(2, [compressed_solvable_address[0], uncompressed_solvable_address[0]])['address'])
            compressed_solvable_address.append(self.nodes[0].addmultisigaddress(2, [compressed_spendable_address[0], compressed_solvable_address[0]])['address'])

            premature_witaddress = []

            for i in compressed_spendable_address:
                v = self.nodes[0].getaddressinfo(i)
                if v['isscript']:
                    [bare, p2sh, p2wsh, p2sh_p2wsh] = self.p2sh_address_to_script(v)
                    premature_witaddress.append(script_to_p2sh(p2wsh))
                else:
                    [p2wpkh, p2sh_p2wpkh, p2pk, p2pkh, p2sh_p2pk, p2sh_p2pkh, p2wsh_p2pk, p2wsh_p2pkh, p2sh_p2wsh_p2pk, p2sh_p2wsh_p2pkh] = self.p2pkh_address_to_script(v)
                    # P2WPKH, P2SH_P2WPKH are always spendable
                    spendable_anytime.extend([p2wpkh, p2sh_p2wpkh])

            for i in uncompressed_spendable_address + uncompressed_solvable_address:
                v = self.nodes[0].getaddressinfo(i)
                if v['isscript']:
                    [bare, p2sh, p2wsh, p2sh_p2wsh] = self.p2sh_address_to_script(v)
                    # P2WSH and P2SH(P2WSH) multisig with uncompressed keys are never seen
                    unseen_anytime.extend([p2wsh, p2sh_p2wsh])
                else:
                    [p2wpkh, p2sh_p2wpkh, p2pk, p2pkh, p2sh_p2pk, p2sh_p2pkh, p2wsh_p2pk, p2wsh_p2pkh, p2sh_p2wsh_p2pk, p2sh_p2wsh_p2pkh] = self.p2pkh_address_to_script(v)
                    # P2WPKH, P2SH_P2WPKH with uncompressed keys are never seen
                    unseen_anytime.extend([p2wpkh, p2sh_p2wpkh])

            for i in compressed_solvable_address:
                v = self.nodes[0].getaddressinfo(i)
                if v['isscript']:
                    [bare, p2sh, p2wsh, p2sh_p2wsh] = self.p2sh_address_to_script(v)
                    premature_witaddress.append(script_to_p2sh(p2wsh))
                else:
                    [p2wpkh, p2sh_p2wpkh, p2pk, p2pkh, p2sh_p2pk, p2sh_p2pkh, p2wsh_p2pk, p2wsh_p2pkh, p2sh_p2wsh_p2pk, p2sh_p2wsh_p2pkh] = self.p2pkh_address_to_script(v)
                    # P2SH_P2PK, P2SH_P2PKH with compressed keys are always solvable
                    solvable_anytime.extend([p2wpkh, p2sh_p2wpkh])

            self.mine_and_test_listunspent(spendable_anytime, 2)
            self.mine_and_test_listunspent(solvable_anytime, 1)
            self.mine_and_test_listunspent(unseen_anytime, 0)

            # Check that createrawtransaction/decoderawtransaction with non-v0 Bech32 works
            v1_addr = program_to_witness(1, [3, 5])
            v1_tx = self.nodes[0].createrawtransaction([getutxo(spendable_txid[0])], {v1_addr: 1})
            v1_decoded = self.nodes[1].decoderawtransaction(v1_tx)
            assert_equal(v1_decoded['vout'][0]['scriptPubKey']['address'], v1_addr)
            assert_equal(v1_decoded['vout'][0]['scriptPubKey']['hex'], "51020305")

            # Check that spendable outputs are really spendable
            self.create_and_mine_tx_from_txids(spendable_txid)

            # import all the private keys so solvable addresses become spendable
            self.nodes[0].importprivkey("edSdzE6zFFJ8hMVEWh9idnu9h8uYPQUJLknbRANvMooiMTfQmsCS")
            self.nodes[0].importprivkey("eboTiEYQbmStx9kN6ddGorGc45DxuiSgtytsaYmutW5iU4vWvLeF")
            self.nodes[0].importprivkey("9Y1pSRPsx4PcmnX1Wd9j1DAW51BjaWEdXPcUFU4NdVpFvR2rNhH")
            self.nodes[0].importprivkey("eeU9UuVcudMDbMwGnmZdYG1PYYtivFUiCzhtrxZbAnCr8dSXLXhz")
            self.nodes[0].importprivkey("eh8Kjz7RDg6FrHPSru8xQZJyVgJFptVXZzusrY6esAEKboRu8kZs")
            self.nodes[0].importprivkey("ehLPHFXfemHKbkZ1J3bVjq1vyB5hn9rTwXZHX6fah17jLKBwFDXh")
            self.nodes[0].importprivkey("9XzyrpAZo65SRLKChxQVbQ7L7MmWLDWeRvkPZVgZ6eGKvdgXbWC")
            self.create_and_mine_tx_from_txids(solvable_txid)

            # Test that importing native P2WPKH/P2WSH scripts works
            for use_p2wsh in [False, True]:
                if use_p2wsh:
                    scriptPubKey = "00203a59f3f56b713fdcf5d1a57357f02c44342cbf306ffe0c4741046837bf90561a"
                    transaction = "01000000000100e1f505000000002200203a59f3f56b713fdcf5d1a57357f02c44342cbf306ffe0c4741046837bf90561a00000000"
                else:
                    scriptPubKey = "a9142f8c469c2f0084c48e11f998ffbe7efa7549f26d87"
                    transaction = "01000000000100e1f5050000000017a9142f8c469c2f0084c48e11f998ffbe7efa7549f26d8700000000"

                self.nodes[1].importaddress(scriptPubKey, "", False)
                rawtxfund = self.nodes[1].fundrawtransaction(transaction)['hex']
                rawtxfund = self.nodes[1].signrawtransactionwithwallet(rawtxfund)["hex"]
                txid = self.nodes[1].sendrawtransaction(rawtxfund)

                assert_equal(self.nodes[1].gettransaction(txid, True)["txid"], txid)
                assert_equal(self.nodes[1].listtransactions("*", 1, 0, True)[0]["txid"], txid)

                # Assert it is properly saved
                self.restart_node(1)
                assert_equal(self.nodes[1].gettransaction(txid, True)["txid"], txid)
                assert_equal(self.nodes[1].listtransactions("*", 1, 0, True)[0]["txid"], txid)

    def mine_and_test_listunspent(self, script_list, ismine):
        utxo = find_spendable_utxo(self.nodes[0], 50)
        tx = CTransaction()
        tx.vin.append(CTxIn(COutPoint(int('0x' + utxo['txid'], 0), utxo['vout'])))
        for i in script_list:
            tx.vout.append(CTxOut(10000000, i))
        tx.rehash()
        signresults = self.nodes[0].signrawtransactionwithwallet(tx.serialize_without_witness().hex())['hex']
        txid = self.nodes[0].sendrawtransaction(hexstring=signresults, maxfeerate=0)
        txs_mined[txid] = self.generate(self.nodes[0], 1)[0]
        watchcount = 0
        spendcount = 0
        for i in self.nodes[0].listunspent():
            if i['txid'] == txid:
                watchcount += 1
                if i['spendable']:
                    spendcount += 1
        if ismine == 2:
            assert_equal(spendcount, len(script_list))
        elif ismine == 1:
            assert_equal(watchcount, len(script_list))
            assert_equal(spendcount, 0)
        else:
            assert_equal(watchcount, 0)
        return txid

    def p2sh_address_to_script(self, v):
        bare = CScript(bytes.fromhex(v['hex']))
        p2sh = CScript(bytes.fromhex(v['scriptPubKey']))
        p2wsh = script_to_p2wsh_script(bare)
        p2sh_p2wsh = script_to_p2sh_script(p2wsh)
        return [bare, p2sh, p2wsh, p2sh_p2wsh]

    def p2pkh_address_to_script(self, v):
        pubkey = bytes.fromhex(v['pubkey'])
        p2wpkh = key_to_p2wpkh_script(pubkey)
        p2sh_p2wpkh = script_to_p2sh_script(p2wpkh)
        p2pk = key_to_p2pk_script(pubkey)
        p2pkh = CScript(bytes.fromhex(v['scriptPubKey']))
        p2sh_p2pk = script_to_p2sh_script(p2pk)
        p2sh_p2pkh = script_to_p2sh_script(p2pkh)
        p2wsh_p2pk = script_to_p2wsh_script(p2pk)
        p2wsh_p2pkh = script_to_p2wsh_script(p2pkh)
        p2sh_p2wsh_p2pk = script_to_p2sh_script(p2wsh_p2pk)
        p2sh_p2wsh_p2pkh = script_to_p2sh_script(p2wsh_p2pkh)
        return [p2wpkh, p2sh_p2wpkh, p2pk, p2pkh, p2sh_p2pk, p2sh_p2pkh, p2wsh_p2pk, p2wsh_p2pkh, p2sh_p2wsh_p2pk, p2sh_p2wsh_p2pkh]

    def create_and_mine_tx_from_txids(self, txids, success=True):
        tx = CTransaction()
        for i in txids:
            txraw = self.nodes[0].getrawtransaction(i, 0, txs_mined[i])
            txtmp = tx_from_hex(txraw)
            for j in range(len(txtmp.vout)):
                tx.vin.append(CTxIn(COutPoint(int('0x' + i, 0), j)))
        tx.vout.append(CTxOut(0, CScript()))
        tx.rehash()
        signresults = self.nodes[0].signrawtransactionwithwallet(tx.serialize_without_witness().hex())['hex']
        self.nodes[0].sendrawtransaction(hexstring=signresults, maxfeerate=0)
        self.generate(self.nodes[0], 1)


if __name__ == '__main__':
    SegWitTest().main()
