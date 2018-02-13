
Debian
====================
This directory contains files used to package bitcoind/digibyte-qt
for Debian-based Linux systems. If you compile bitcoind/digibyte-qt yourself, there are some useful files here.

## digibyte: URI support ##


digibyte-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install digibyte-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your digibyte-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitcoin128.png` to `/usr/share/pixmaps`

digibyte-qt.protocol (KDE)

