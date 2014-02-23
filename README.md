Technical Specifications
========================

 - Srypt proof-of-work algorithm
 - 60 second block time target
 - ~21 billion total coins
 - 8000 coins per block, reduces by 0.5% each week starting 2/28/14
 - Difficulty retarget every 1 block
 
Ubuntu Dependencies
===================
sudo apt-get install build-essential libboost-all-dev libcurl4-openssl-dev libdb5.1-dev libdb5.1++-dev git qt-sdk libminiupnpc-dev

sudo apt-get install qrencode libqrencode-dev 

Qt v 4 is what we used to compile DigiByte.

Ubuntu Compile digibyted
========================
cd ~

git clone git://github.com/digibyte/DigiByteProject.git

cd DigiByteProject/src

make -f makefile.unix USE_UPNP=-

sudo cp digibyted /usr/bin


When trying to compile if you get this error: "../share/genbuild.sh: 34: ../share/genbuild.sh: cannot create obj/build.h: Directory nonexistent
make: *** [obj/build.h] Error "

Make sure to create the folder "obj" in the "src" folder:

cd DigiByteProject/src

If Root: cd ~DigiByteProject/src

mkdir obj

Then try compiling again.


Ubuntu Compile digibyte-qt
========================
cd DigiByteProject

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



