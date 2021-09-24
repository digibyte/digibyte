DigiByte Core
=============

Setup
---------------------
DigiByte Core is the original DigiByte client and it builds the backbone of the network. It downloads and, by default, stores the entire history of DigiByte transactions, which requires a few hundred gigabytes of disk space. Depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more.

To download DigiByte Core, visit [digibyte.org](https://digibyte.org/en/download/).

Running
---------------------
The following are some helpful notes on how to run DigiByte Core on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/digibyte-qt` (GUI) or
- `bin/digibyted` (headless)

### Windows

Unpack the files into a directory, and then run digibyte-qt.exe.

### macOS

Drag DigiByte Core to your applications folder, and then run DigiByte Core.

### Need Help?

* See the documentation at the [DigiByte Wiki](https://dgbwiki.com/)
for help and more information.
* Ask for help on [DigiByte-Core](https://gitter.im/DigiByte-Core) Gitter.
* Ask for help on the [DigiByte Official Discussion](https://t.me/DigiByteCoin) Telegram channels.
* Ask for help on #digibyte on Libera Chat. If you don't have an IRC client, you can use [web.libera.chat](https://web.libera.chat/#digibyte).


Building
---------------------
The following are developer notes on how to build DigiByte Core on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [Dependencies](dependencies.md)
- [macOS Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [FreeBSD Build Notes](build-freebsd.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [NetBSD Build Notes](build-netbsd.md)
- [Android Build Notes](build-android.md)
- [Gitian Building Guide (External Link)](https://github.com/digibyte-core/docs/blob/master/gitian-building.md)

Development
---------------------
The DigiByte repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Productivity Notes](productivity.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](https://doxygen.digibyte.org/)
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [JSON-RPC Interface](JSON-RPC-interface.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Shared Libraries](shared-libraries.md)
- [BIPS](bips.md)
- [Dnsseed Policy](dnsseed-policy.md)
- [Benchmarking](benchmarking.md)

### Resources
* Discuss on the [DigiByteTalk](https://digibytetalk.org/) forums, in the [Development & Technical Discussion board](https://digibytetalk.org/index.php?board=6.0).
* Discuss project-specific development on #digibyte-core-dev on Libera Chat. If you don't have an IRC client, you can use [web.libera.chat](https://web.libera.chat/#digibyte-core-dev).

### Miscellaneous

- [Assets Attribution](assets-attribution.md)
- [digibyte.conf Configuration File](digibyte-conf.md)
- [Files](files.md)
- [Fuzz-testing](fuzzing.md)
- [I2P Support](i2p.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)
- [PSBT support](psbt.md)
- [Reduce Memory](reduce-memory.md)
- [Reduce Traffic](reduce-traffic.md)
- [Tor Support](tor.md)
- [ZMQ](zmq.md)

License
---------------------
Distributed under the [MIT software license](/COPYING).
