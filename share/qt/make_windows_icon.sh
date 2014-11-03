#!/bin/bash
# create multiresolution windows icon
<<<<<<< HEAD
ICON_SRC=../../src/qt/res/icons/digibyte.png
ICON_DST=../../src/qt/res/icons/digibyte.ico
convert ${ICON_SRC} -resize 16x16 digibyte-16.png
convert ${ICON_SRC} -resize 32x32 digibyte-32.png
convert ${ICON_SRC} -resize 48x48 digibyte-48.png
convert digibyte-16.png digibyte-32.png digibyte-48.png ${ICON_DST}
=======
ICON_SRC=../../src/qt/res/icons/bitcoin.png
ICON_DST=../../src/qt/res/icons/bitcoin.ico
convert ${ICON_SRC} -resize 16x16 bitcoin-16.png
convert ${ICON_SRC} -resize 32x32 bitcoin-32.png
convert ${ICON_SRC} -resize 48x48 bitcoin-48.png
convert bitcoin-16.png bitcoin-32.png bitcoin-48.png ${ICON_DST}
>>>>>>> mryiad/master

