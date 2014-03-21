#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/digibyte.png
ICON_DST=../../src/qt/res/icons/digibyte.ico
convert ${ICON_SRC} -resize 16x16 digibyte-16.png
convert ${ICON_SRC} -resize 32x32 digibyte-32.png
convert ${ICON_SRC} -resize 48x48 digibyte-48.png
convert digibyte-16.png digibyte-32.png digibyte-48.png ${ICON_DST}

