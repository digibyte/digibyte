#!/usr/bin/env python3
<<<<<<< HEAD
# Copyright (c) 2009-2019 The Bitcoin Core developers
# Copyright (c) 2014-2019 The DigiByte Core developers
=======
# Copyright (c) 2014-2018 The DigiByte Core developers
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
"""Test running digibyted with -reindex and -reindex-chainstate options.

- Start a single node and generate 3 blocks.
- Stop the node and restart it with -reindex. Verify that the node has reindexed up to block 3.
- Stop the node and restart it with -reindex-chainstate. Verify that the node has reindexed up to block 3.
"""

from test_framework.test_framework import DigiByteTestFramework
<<<<<<< HEAD
from test_framework.util import wait_until

class ReindexTest(DigiByteTestFramework):
=======
from test_framework.util import assert_equal

>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25

class ReindexTest(DigiByteTestFramework):
    def set_test_params(self):
        self.setup_clean_chain = True
        self.num_nodes = 1

    def skip_test_if_missing_module(self):
        self.skip_if_no_wallet()

    def reindex(self, justchainstate=False):
        self.nodes[0].generatetoaddress(3, self.nodes[0].get_deterministic_priv_key().address)
        blockcount = self.nodes[0].getblockcount()
        self.stop_nodes()
        extra_args = [["-reindex-chainstate" if justchainstate else "-reindex"]]
        self.start_nodes(extra_args)
        assert_equal(self.nodes[0].getblockcount(), blockcount)  # start_node is blocking on reindex
        self.log.info("Success")

    def run_test(self):
        self.reindex(False)
        self.reindex(True)
        self.reindex(False)
        self.reindex(True)

if __name__ == '__main__':
    ReindexTest().main()
