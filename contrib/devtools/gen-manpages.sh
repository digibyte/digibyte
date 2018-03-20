#!/bin/bash

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
BUILDDIR=${BUILDDIR:-$TOPDIR}

BINDIR=${BINDIR:-$BUILDDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

DIGIBYTED=${DIGIBYTED:-$SRCDIR/digibyted}
DIGIBYTECLI=${DIGIBYTECLI:-$SRCDIR/digibyte-cli}
DIGIBYTETX=${DIGIBYTETX:-$SRCDIR/digibyte-tx}
DIGIBYTEQT=${DIGIBYTEQT:-$SRCDIR/qt/digibyte-qt}

[ ! -x $DIGIBYTED ] && echo "$DIGIBYTED not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
DGBVER=($($DIGIBYTECLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for digibyted if --version-string is not set,
# but has different outcomes for digibyte-qt and digibyte-cli.
echo "[COPYRIGHT]" > footer.h2m
$DIGIBYTED --version | sed -n '1!p' >> footer.h2m

for cmd in $DIGIBYTED $DIGIBYTECLI $DIGIBYTETX $DIGIBYTEQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${DGBVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${DGBVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
