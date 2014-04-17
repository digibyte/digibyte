=======
DigiByte Core integration/staging tree
=====================================

http://www.digibyte.co

Copyright (c) 2009-2013 DigiByte Core Developers

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

 - Scrypt proof-of-work algorithm
 - 60 second block time target
 - ~21 billion total coins
 - 8000 coins per block, reduces by 0.5% each week starting 2/28/14
 - Difficulty retarget every 1 block
 
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
