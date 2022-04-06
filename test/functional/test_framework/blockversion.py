#!/usr/bin/env python3
# Copyright (c) 2022 The DigiByte Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
"""DigiByte Block Version for Regtest"""

VERSIONBITS_TOP_BITS = 0x20000000
BLOCK_VERSION = 2
VERSIONBITS_LAST_OLD_BLOCK_VERSION = BLOCK_VERSION | VERSIONBITS_TOP_BITS

def calc_block_version(v):
    return v | VERSIONBITS_TOP_BITS
