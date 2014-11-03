<<<<<<< HEAD
DigiByte version 0.6.3 is now available for download at:
=======
Bitcoin version 0.6.3 is now available for download at:
>>>>>>> mryiad/master
  http://sourceforge.net/projects/bitcoin/files/Bitcoin/bitcoin-0.6.3/

This is a bug-fix release, with no new features.

Please report bugs using the issue tracker at github:
  https://github.com/bitcoin/bitcoin/issues

CHANGE SUMMARY

Fixed a serious denial-of-service attack that could cause the
<<<<<<< HEAD
digibyte process to become unresponsive. Thanks to Sergio Lerner
=======
bitcoin process to become unresponsive. Thanks to Sergio Lerner
>>>>>>> mryiad/master
for finding and responsibly reporting the problem. (CVE-2012-3789)

Optimized the process of checking transaction signatures, to
speed up processing of new block messages and make propagating
blocks across the network faster.

<<<<<<< HEAD
Fixed an obscure bug that could cause the digibyte process to get
stuck on an invalid block-chain, if the invalid chain was
hundreds of blocks long.

DigiByte-Qt no longer automatically selects the first address
=======
Fixed an obscure bug that could cause the bitcoin process to get
stuck on an invalid block-chain, if the invalid chain was
hundreds of blocks long.

Bitcoin-Qt no longer automatically selects the first address
>>>>>>> mryiad/master
in the address book (Issue #1384).

Fixed minimize-to-dock behavior of Bitcon-Qt on the Mac.

Added a block checkpoint at block 185,333 to speed up initial
blockchain download.
