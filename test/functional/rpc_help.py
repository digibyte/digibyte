#!/usr/bin/env python3
<<<<<<< HEAD
# Copyright (c) 2018 The DigiByte Core developers
=======
# Copyright (c) 2018-2019 The DigiByte Core developers
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
"""Test RPC help output."""

from test_framework.test_framework import DigiByteTestFramework
from test_framework.util import assert_equal, assert_raises_rpc_error

import os


class HelpRpcTest(DigiByteTestFramework):
    def set_test_params(self):
        self.num_nodes = 1
<<<<<<< HEAD
=======
        self.supports_cli = False
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25

    def run_test(self):
        self.test_categories()
        self.dump_help()
<<<<<<< HEAD
=======
        if self.is_wallet_compiled():
            self.wallet_help()
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25

    def test_categories(self):
        node = self.nodes[0]

        # wrong argument count
        assert_raises_rpc_error(-1, 'help', node.help, 'foo', 'bar')

        # invalid argument
        assert_raises_rpc_error(-1, 'JSON value is not a string as expected', node.help, 0)

        # help of unknown command
        assert_equal(node.help('foo'), 'help: unknown command: foo')

        # command titles
        titles = [line[3:-3] for line in node.help().splitlines() if line.startswith('==')]

        components = ['Blockchain', 'Control', 'Generating', 'Mining', 'Network', 'Rawtransactions', 'Util']

        if self.is_wallet_compiled():
            components.append('Wallet')

        if self.is_zmq_compiled():
            components.append('Zmq')

        assert_equal(titles, components)

    def dump_help(self):
        dump_dir = os.path.join(self.options.tmpdir, 'rpc_help_dump')
        os.mkdir(dump_dir)
        calls = [line.split(' ', 1)[0] for line in self.nodes[0].help().splitlines() if line and not line.startswith('==')]
        for call in calls:
            with open(os.path.join(dump_dir, call), 'w', encoding='utf-8') as f:
                # Make sure the node can generate the help at runtime without crashing
                f.write(self.nodes[0].help(call))

<<<<<<< HEAD
=======
    def wallet_help(self):
        assert 'getnewaddress ( "label" "address_type" )' in self.nodes[0].help('getnewaddress')
        self.restart_node(0, extra_args=['-nowallet=1'])
        assert 'getnewaddress ( "label" "address_type" )' in self.nodes[0].help('getnewaddress')

>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25

if __name__ == '__main__':
    HelpRpcTest().main()
