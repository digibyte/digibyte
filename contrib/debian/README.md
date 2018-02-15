
Debian
====================
This directory contains files used to package digibyted/digibyte-qt
for Debian-based Linux systems. If you compile digibyted/digibyte-qt yourself, there are some useful files here.

## digibyte: URI support ##


digibyte-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install digibyte-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your digibyte-qt binary to `/usr/bin`
and the `../../share/pixmaps/digibyte128.png` to `/usr/share/pixmaps`

digibyte-qt.protocol (KDE)

