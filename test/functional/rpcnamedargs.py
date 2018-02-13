#!/usr/bin/env python3
# Copyright (c) 2016 The DigiByte Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
"""Test using named arguments for RPCs."""

<<<<<<< HEAD:qa/rpc-tests/rpcnamedargs.py
from decimal import Decimal

from test_framework.test_framework import DigiByteTestFramework
from test_framework.authproxy import JSONRPCException
=======
from test_framework.test_framework import DigiByteTestFramework
>>>>>>> a93234d596832862fe92c2dd0a0bf7d8febfd5f7:test/functional/rpcnamedargs.py
from test_framework.util import (
    assert_equal,
    assert_raises_rpc_error,
)

<<<<<<< HEAD:qa/rpc-tests/rpcnamedargs.py

class NamedArgumentTest(DigiByteTestFramework):
    """
    Test named arguments on RPC calls.
    """

    def __init__(self):
        super().__init__()
        self.setup_clean_chain = False
=======
class NamedArgumentTest(DigiByteTestFramework):
    def set_test_params(self):
>>>>>>> a93234d596832862fe92c2dd0a0bf7d8febfd5f7:test/functional/rpcnamedargs.py
        self.num_nodes = 1

    def run_test(self):
        node = self.nodes[0]
        h = node.help(command='getinfo')
        assert(h.startswith('getinfo\n'))

<<<<<<< HEAD:qa/rpc-tests/rpcnamedargs.py
        assert_raises_jsonrpc(-8, 'Unknown named parameter', node.help, random='getinfo')
=======
        assert_raises_rpc_error(-8, 'Unknown named parameter', node.help, random='getinfo')
>>>>>>> a93234d596832862fe92c2dd0a0bf7d8febfd5f7:test/functional/rpcnamedargs.py

        h = node.getblockhash(height=0)
        node.getblock(blockhash=h)

        assert_equal(node.echo(), [])
        assert_equal(node.echo(arg0=0,arg9=9), [0] + [None]*8 + [9])
        assert_equal(node.echo(arg1=1), [None, 1])
        assert_equal(node.echo(arg9=None), [None]*10)
        assert_equal(node.echo(arg0=0,arg3=3,arg9=9), [0] + [None]*2 + [3] + [None]*5 + [9])

if __name__ == '__main__':
    NamedArgumentTest().main()
