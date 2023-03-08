#!/usr/bin/env python3
# Copyright (c) 2018 Bradley Denby
# Distributed under the MIT software license. See the accompanying file COPYING
# or http://www.opensource.org/licenses/mit-license.php.

"""Test transaction behaviors under the Dandelion spreading policy

Tests:
1. Resistance to active probing:
    Stem:    0 --> 1 --> 2 --> 0 where each node has argument "-dandelion=1"
    Probe: TestNode --> 0
    Node 0 generates a Dandelion transaction "tx": 1.0 BTC from Node 0 to Node 2
    TestNode immediately sends getdata for tx to Node 0
    Assert that Node 0 does not reply with tx

2. Loop behavior:
    Stem:    0 --> 1 --> 2 --> 0 where each node has argument "-dandelion=1"
    Probe: TestNode --> 0
    Wait ~5 seconds after Test 1, then TestNode sends getdata for tx to Node 0
    Assert that Node 0 does not reply with tx

3. Resistance to black holes:
    Stem:    0 --> 1 --> 2 --> 0 where each node has argument "-dandelion=1"
    Probe: TestNode --> 0
    Wait ~45 seconds after Test 2, then TestNode sends getdata for tx to Node 0
    Assert that Node 0 replies with tx
"""

from test_framework.p2p import P2PInterface
from test_framework.test_framework import DigiByteTestFramework
from test_framework.blocktools import COINBASE_MATURITY
from test_framework.messages import (
    CTransaction,
    tx_from_hex,
    msg_getdata,
    CInv,
)

import time                                                                                                         # sleep

class TestP2PConn(P2PInterface):
    def __init__(self):
        super().__init__()

    def send_dandeliontx_getdata(self, dandeliontx_hash):
        msg = msg_getdata()
        msg.inv.append(CInv(5, dandeliontx_hash)) # 5: "DandelionTx"
        self.send_message(msg)

class DandelionTest(DigiByteTestFramework):
    def set_test_params(self):
        self.setup_clean_chain = True
        self.num_nodes = 3
        self.extra_args = []
        for i in range(self.num_nodes):
            self.extra_args.append(["-dandelion=1"]) # ,"-debug=dandelion","-printtoconsole=1"

    def setup_network(self):
        self.setup_nodes()
        # Tests 1,2,3: 0 --> 1 --> 2 --> 0
        self.connect_nodes(0, 1)
        self.connect_nodes(1, 2)
        self.connect_nodes(2, 0)

        self.nodes[0].createwallet(wallet_name='w0', load_on_startup=True)
        self.nodes[1].createwallet(wallet_name='w1', load_on_startup=True)
        self.nodes[2].createwallet(wallet_name='w2', load_on_startup=True)

    def run_test(self):
        # Convenience variables
        node0, node1, node2 = self.nodes
        w0 = node0.get_wallet_rpc('w0')
        w1 = node0.get_wallet_rpc('w1')
        w2 = node0.get_wallet_rpc('w2')

        # Setup TestP2PConns
        test_node0 = node0.add_p2p_connection(TestP2PConn())

        # Start networking thread
        test_node0.wait_for_verack()

        # Get out of Initial Block Download (IBD)
        for node in self.nodes:
            self.generatetoaddress(node, 1, w0.getnewaddress(), sync_fun=self.no_op)

        # Generate funds for node0
        self.generate(node0, COINBASE_MATURITY + 1)

        # Tests 1,2,3
        # There is a low probability that one of these tests will fail even if
        # the implementation is correct. Thus, these tests are repeated upon
        # failure. A true bug will result in repeated failures.
        self.log.info('Starting tests...')
        test_1_passed = False
        test_2_passed = False
        test_3_passed = False
        tries_left = 5
        while(not (test_1_passed and test_2_passed and test_3_passed) and tries_left > 0):
            tries_left -= 1
            # Test 1: Resistance to active probing
            test_node0.message_count['notfound'] = 0
            node0_txid = node0.sendtoaddress(node2.getnewaddress(), 1.0)
            node0_tx = tx_from_hex(node0.gettransaction(node0_txid)['hex'])
            test_node0.send_dandeliontx_getdata(node0_tx.calc_sha256(True))
            time.sleep(1)

            try:
                assert(test_node0.message_count['notfound']==1)
                if not test_1_passed:
                    test_1_passed = True
                    self.log.info('Success: resistance to active probing')
            except AssertionError:
                if not test_1_passed and tries_left == 0:
                    self.log.info('Failed: resistance to active probing')

            # Test 2: Loop behavior
            test_node0.message_count['notfound'] = 0
            time.sleep(3)
            test_node0.send_dandeliontx_getdata(node0_tx.calc_sha256(True))
            time.sleep(1)

            try:
                assert(test_node0.message_count['notfound']==1)
                if not test_2_passed:
                    test_2_passed = True
                    self.log.info('Success: loop behavior')
            except AssertionError:
                if not test_2_passed and tries_left == 0:
                    self.log.info('Failed: loop behavior')

            # Test 3: Resistance to black holes
            test_node0.message_count['tx'] = 0
            time.sleep(44)
            test_node0.send_dandeliontx_getdata(node0_tx.calc_sha256(True))
            time.sleep(1)
            try:
                assert(test_node0.message_count['tx']==1)
                if not test_3_passed:
                    test_3_passed = True
                    self.log.info('Success: resistance to black holes')
            except AssertionError:
                if not test_3_passed and tries_left == 0:
                    self.log.info('Failed: resistance to black holes')

        all_tests_passed = test_1_passed and test_2_passed and test_3_passed
        assert(all_tests_passed)

if __name__ == '__main__':
    DandelionTest().main()
