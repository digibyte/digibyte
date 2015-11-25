====================================
DigiSpeed v4.0.0 Release Notes
=====================================
* Changes occur @ block 143,000
* 15 Second block timing (1 min  15 seconds per algo)
* Scalability to match Visa TPS by 2021 & continued scaling through 2035 http://www.digibyte.co/system/tdf/DigiByte_Network_Scalability.xlsx?file=1&type=node&id=274
* Minimum TX & Relay Fee set to 1 DGB to prevent attacks
* MultiAlgo Difficulty adjustment code changed to make 51% much, much harder https://github.com/digibyte/digibyte/pull/36
* Transaction propagation changes based upon Microsoft research
* Reward adjusted to accommodate faster blocks, still stays the same (21 billion DGB in 21 years)
* OP_RETURN data increased to 80 bytes to allow embedding more data (like document hashes)
* Safe mode warning error fixed
* Check point added
* Private key compatibility issue fixed ( addresses from the DGB paper wallet address generator now work properly)


====================================
Digibyte Ubuntu Build
=====================================

sudo apt-get install build-essential
sudo apt-get install libtool autotools-dev autoconf
sudo apt-get install libssl-dev

sudo apt-get install libboost-all-dev

git clone git://github.com/digibyte/digibyte.git

cd digibyte

./autogen.sh

./configure

make

cd src

sudo cp digibyted /usr/bin


=======
DigiByte Core integration/staging tree
=====================================

http://www.digibyte.co

Copyright (c) 2009-2014 DigiByte Core Developers

What is DigiByte?
----------------

DigiByte is an experimental new digital currency that enables instant payments to
anyone, anywhere in the world. DigiByte uses peer-to-peer technology to operate
with no central authority: managing transactions and issuing money are carried
out collectively by the network. DigiByte Core is the name of open source
software which enables the use of this currency.

For more information, as well as an immediately useable, binary version of
the DigiByte Core software, see http://www.digibyte.co.

Technical Specifications
---------------------

 - MultiAlgo POW (Scrypt, SHA256D, Qubit, Skein and Groestl) algorithms
 - 30 Second block Target (2.5 min per Algo)
 - ~21 billion total coins
 - 8000 coins per block, reduces by 0.5% every 10,080 blocks starting 2/28/14
 - Difficulty retarget every 1 block (2.5 Min) Averaged over previous 10 blocks per algo
 
Links
------------------------
Website: http://www.digibyte.co

DigiByteTalk: http://digibytetalk.com/index.php

BitcoinTalk: https://bitcointalk.org/index.php?topic=408268.0

Facebook: https://www.facebook.com/digibytecoin

Twitter: https://twitter.com/digibytecoin

VK: https://vk.com/digibyte

Reddit: http://www.reddit.com/r/Digibyte/

IRC Channel: http://webchat.freenode.net/?channels=#digibytecoin

License
-------

DigiByte Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see http://opensource.org/licenses/MIT.

Development process
-------------------

Developers work in their own trees, then submit pull requests when they think
their feature or bug fix is ready.

If it is a simple/trivial/non-controversial change, then one of the DigiByte
development team members simply pulls it.

If it is a *more complicated or potentially controversial* change, then the patch
submitter will be asked to start a discussion (if they haven't already) on the
[mailing list](http://sourceforge.net/mailarchive/forum.php?forum_name=digibyte-development).

The patch will be accepted if there is broad consensus that it is a good thing.
Developers should expect to rework and resubmit patches if the code doesn't
match the project's coding conventions (see [doc/coding.md](doc/coding.md)) or are
controversial.

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/bitcoin/bitcoin/tags) are created
regularly to indicate new official, stable release versions of DigiByte.

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test. Please be patient and help out, and
remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write unit tests for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run (assuming they weren't disabled in configure) with: `make check`
