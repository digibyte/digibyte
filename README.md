Technical Specifications
========================

 - Srypt proof-of-work algorithm
 - 60 second block time targets
 - ~21 billion total coins
 - 8,000 coins per block, halves every ~2 years
 - Retarget every 144 blocks
 
UBUNTU DEPENDENCIES
===================
sudo apt-get install build-essential libboost-all-dev libcurl4-openssl-dev libdb5.1-dev libdb5.1++-dev git qt-sdk libminiupnpc-dev

sudo apt-get install qrencode libqrencode-dev 

UBUNTU COMPILE digibyted
========================
cd ~

git clone git://github.com/digibyte/DigiByteProject.git

cd /digibyte/src

make -f makefile.unix USE_UPNP=-

sudo cp digibyted /usr/bin


When trying to compile if you get this error: "../share/genbuild.sh: 34: ../share/genbuild.sh: cannot create obj/build.h: Directory nonexistent
make: *** [obj/build.h] Error "

Make sure to create the folder "obj" in the "src" folder:

cd /digibyte/src

mkdir obj

Then try compiling again.


UBUNTU COMPILE digibyte-qt
========================
cd digibyte

qmake "USE_UPNP=-" digibyte-qt.pro

make

Links
======

Website: http://www.digibyte.co

DigiByteTalk: http://digibytetalk.com/index.php

BitcoinTalk: https://bitcointalk.org/index.php?topic=408268.0

Facebook: https://www.facebook.com/digibytecoin

Twitter: https://twitter.com/digibytecoin

VK: https://vk.com/digibyte

Reddit: http://www.reddit.com/r/Digibyte/

IRC Channel: http://webchat.freenode.net/?channels=#digibytecoin



