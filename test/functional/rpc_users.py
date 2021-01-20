#!/usr/bin/env python3
<<<<<<< HEAD
# Copyright (c) 2009-2019 The Bitcoin Core developers
# Copyright (c) 2014-2019 The DigiByte Core developers
=======
# Copyright (c) 2015-2019 The DigiByte Core developers
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
"""Test multiple RPC users."""

from test_framework.test_framework import DigiByteTestFramework
from test_framework.util import (
    assert_equal,
    get_datadir_path,
    str_to_b64str,
)

import os
import http.client
import urllib.parse
import subprocess
from random import SystemRandom
import string
import configparser
import sys


<<<<<<< HEAD
=======
def call_with_auth(node, user, password):
    url = urllib.parse.urlparse(node.url)
    headers = {"Authorization": "Basic " + str_to_b64str('{}:{}'.format(user, password))}

    conn = http.client.HTTPConnection(url.hostname, url.port)
    conn.connect()
    conn.request('POST', '/', '{"method": "getbestblockhash"}', headers)
    resp = conn.getresponse()
    conn.close()
    return resp


>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25
class HTTPBasicsTest(DigiByteTestFramework):
    def set_test_params(self):
        self.num_nodes = 2
        self.supports_cli = False

    def setup_chain(self):
        super().setup_chain()
        #Append rpcauth to digibyte.conf before initialization
<<<<<<< HEAD
=======
        self.rtpassword = "cA773lm788buwYe4g4WT+05pKyNruVKjQ25x3n0DQcM="
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25
        rpcauth = "rpcauth=rt:93648e835a54c573682c2eb19f882535$7681e9c5b74bdd85e78166031d2058e1069b3ed7ed967c93fc63abba06f31144"

        self.rpcuser = "rpcuser💻"
        self.rpcpassword = "rpcpassword🔑"

        config = configparser.ConfigParser()
        config.read_file(open(self.options.configfile))
        gen_rpcauth = config['environment']['RPCAUTH']

        # Generate RPCAUTH with specified password
        self.rt2password = "8/F3uMDw4KSEbw96U3CA1C4X05dkHDN2BPFjTgZW4KI="
        p = subprocess.Popen([sys.executable, gen_rpcauth, 'rt2', self.rt2password], stdout=subprocess.PIPE, universal_newlines=True)
        lines = p.stdout.read().splitlines()
        rpcauth2 = lines[1]

        # Generate RPCAUTH without specifying password
        self.user = ''.join(SystemRandom().choice(string.ascii_letters + string.digits) for _ in range(10))
        p = subprocess.Popen([sys.executable, gen_rpcauth, self.user], stdout=subprocess.PIPE, universal_newlines=True)
        lines = p.stdout.read().splitlines()
        rpcauth3 = lines[1]
        self.password = lines[3]

        with open(os.path.join(get_datadir_path(self.options.tmpdir, 0), "digibyte.conf"), 'a', encoding='utf8') as f:
<<<<<<< HEAD
            f.write(rpcauth+"\n")
            f.write(rpcauth2+"\n")
            f.write(rpcauth3+"\n")
        with open(os.path.join(get_datadir_path(self.options.tmpdir, 1), "digibyte.conf"), 'a', encoding='utf8') as f:
            f.write(rpcuser+"\n")
            f.write(rpcpassword+"\n")

    def run_test(self):

        ##################################################
        # Check correctness of the rpcauth config option #
        ##################################################
        url = urllib.parse.urlparse(self.nodes[0].url)

        #Old authpair
        authpair = url.username + ':' + url.password

        #New authpair generated via share/rpcauth tool
        password = "cA773lm788buwYe4g4WT+05pKyNruVKjQ25x3n0DQcM="

        #Second authpair with different username
        password2 = "8/F3uMDw4KSEbw96U3CA1C4X05dkHDN2BPFjTgZW4KI="
        authpairnew = "rt:"+password

        self.log.info('Correct...')
        headers = {"Authorization": "Basic " + str_to_b64str(authpair)}

        conn = http.client.HTTPConnection(url.hostname, url.port)
        conn.connect()
        conn.request('POST', '/', '{"method": "getbestblockhash"}', headers)
        resp = conn.getresponse()
        assert_equal(resp.status, 200)
        conn.close()
=======
            f.write(rpcauth + "\n")
            f.write(rpcauth2 + "\n")
            f.write(rpcauth3 + "\n")
        with open(os.path.join(get_datadir_path(self.options.tmpdir, 1), "digibyte.conf"), 'a', encoding='utf8') as f:
            f.write("rpcuser={}\n".format(self.rpcuser))
            f.write("rpcpassword={}\n".format(self.rpcpassword))
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25

    def test_auth(self, node, user, password):
        self.log.info('Correct...')
        assert_equal(200, call_with_auth(node, user, password).status)

        self.log.info('Wrong...')
        assert_equal(401, call_with_auth(node, user, password + 'wrong').status)

        self.log.info('Wrong...')
        assert_equal(401, call_with_auth(node, user + 'wrong', password).status)

        self.log.info('Wrong...')
        assert_equal(401, call_with_auth(node, user + 'wrong', password + 'wrong').status)

    def run_test(self):
        self.log.info('Check correctness of the rpcauth config option')
        url = urllib.parse.urlparse(self.nodes[0].url)

        self.test_auth(self.nodes[0], url.username, url.password)
        self.test_auth(self.nodes[0], 'rt', self.rtpassword)
        self.test_auth(self.nodes[0], 'rt2', self.rt2password)
        self.test_auth(self.nodes[0], self.user, self.password)

        self.log.info('Check correctness of the rpcuser/rpcpassword config options')
        url = urllib.parse.urlparse(self.nodes[1].url)

        self.test_auth(self.nodes[1], self.rpcuser, self.rpcpassword)

        self.log.info('Check that failure to write cookie file will abort the node gracefully')
        self.stop_node(0)
        cookie_file = os.path.join(get_datadir_path(self.options.tmpdir, 0), self.chain, '.cookie.tmp')
        os.mkdir(cookie_file)
        init_error = 'Error: Unable to start HTTP server. See debug log for details.'
        self.nodes[0].assert_start_raises_init_error(expected_msg=init_error)


if __name__ == '__main__':
    HTTPBasicsTest().main()
