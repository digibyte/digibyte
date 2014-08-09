include Makefile.include

AM_CPPFLAGS += -I$(builddir)

noinst_LIBRARIES = \
  libdigibyte_server.a \
  libdigibyte_common.a \
  libdigibyte_cli.a
if ENABLE_WALLET
noinst_LIBRARIES += libdigibyte_wallet.a
endif

bin_PROGRAMS =

if BUILD_DIGIBYTED
  bin_PROGRAMS += digibyted
endif

if BUILD_DIGIBYTE_CLI
  bin_PROGRAMS += digibyte-cli
endif

SUBDIRS = . $(BUILD_QT) $(BUILD_TEST)
DIST_SUBDIRS = . qt test
.PHONY: FORCE
# digibyte core #
DIGIBYTE_CORE_H = \
  addrman.h \
  alert.h \
  allocators.h \
  base58.h bignum.h \
  bloom.h \
  chainparams.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coincontrol.h \
  coins.h \
  compat.h \
  core.h \
  crypter.h \
  db.h \
  hash.h \
  init.h \
  key.h \
  keystore.h \
  leveldbwrapper.h \
  limitedmap.h \
  main.h \
  miner.h \
  mruset.h \
  netbase.h \
  net.h \
  noui.h \
  protocol.h \
  rpcclient.h \
  rpcprotocol.h \
  rpcserver.h \
  script.h \
  serialize.h \
  sync.h \
  threadsafety.h \
  tinyformat.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  uint256.h \
  util.h \
  version.h \
  walletdb.h \
  wallet.h \
  scrypt.h \
  sph_blake.h \
  sph_groestl.h \
  sph_keccak.h \
  sph_bmw.h \
  sph_jh.h \
  sph_skein.h \
  sph_types.h \
  sph_echo.h \
  sph_luffa.h \
  sph_simd.h \
  sph_cubehash.h \
  sph_shavite.h \
  hashgroestl.h \
  hashskein.h \
  hashqubit.h

JSON_H = \
  json/json_spirit.h \
  json/json_spirit_error_position.h \
  json/json_spirit_reader.h \
  json/json_spirit_reader_template.h \
  json/json_spirit_stream_reader.h \
  json/json_spirit_utils.h \
  json/json_spirit_value.h \
  json/json_spirit_writer.h \
  json/json_spirit_writer_template.h

obj/build.h: FORCE
	@$(MKDIR_P) $(abs_top_builddir)/src/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
version.o: obj/build.h

libdigibyte_server_a_SOURCES = \
  addrman.cpp \
  alert.cpp \
  bloom.cpp \
  checkpoints.cpp \
  coins.cpp \
  init.cpp \
  keystore.cpp \
  leveldbwrapper.cpp \
  main.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  rpcblockchain.cpp \
  rpcmining.cpp \
  rpcmisc.cpp \
  rpcnet.cpp \
  rpcrawtransaction.cpp \
  rpcserver.cpp \
  txdb.cpp \
  txmempool.cpp \
  $(JSON_H) \
  $(DIGIBYTE_CORE_H)

libdigibyte_wallet_a_SOURCES = \
  db.cpp \
  crypter.cpp \
  rpcdump.cpp \
  rpcwallet.cpp \
  wallet.cpp \
  walletdb.cpp \
  $(DIGIBYTE_CORE_H)

libdigibyte_common_a_SOURCES = \
	base58.cpp \
  allocators.cpp \
  chainparams.cpp \
  core.cpp \
  hash.cpp \
  key.cpp \
  netbase.cpp \
  protocol.cpp \
  rpcprotocol.cpp \
  script.cpp \
  sync.cpp \
  util.cpp \
  version.cpp \
  scrypt.cpp \
  scrypt-sse2.cpp \
  blake.c \
  bmw.c \
  groestl.c \
  jh.c \
  keccak.c \
  skein.c \
  aes_helper.c \
  echo.c \
  luffa.c \
  simd.c \
  cubehash.c \
  shavite.c \
  $(DIGIBYTE_CORE_H)

if GLIBC_BACK_COMPAT
libbitcoin_common_a_SOURCES += compat/glibc_compat.cpp
libbitcoin_common_a_SOURCES += compat/glibcxx_compat.cpp
endif

libdigibyte_cli_a_SOURCES = \
  rpcclient.cpp \
  $(DIGIBYTE_CORE_H)

nodist_libdigibyte_common_a_SOURCES = $(top_srcdir)/src/obj/build.h
#

# digibyted binary #
digibyted_LDADD = \
  libdigibyte_server.a \
  libdigibyte_cli.a \
  libdigibyte_common.a \
  $(LIBLEVELDB) \
  $(LIBMEMENV)
if ENABLE_WALLET
digibyted_LDADD += libdigibyte_wallet.a
endif
digibyted_SOURCES = digibyted.cpp
#

if TARGET_WINDOWS
digibyted_SOURCES += digibyted-res.rc
endif

AM_CPPFLAGS += $(BDB_CPPFLAGS)
digibyted_LDADD += $(BOOST_LIBS) $(BDB_LIBS)

# digibyte-cli binary #
digibyte_cli_LDADD = \
  libdigibyte_cli.a \
  libdigibyte_common.a \
  $(BOOST_LIBS)
digibyte_cli_SOURCES = digibyte-cli.cpp
#

if TARGET_WINDOWS
digibyte_cli_SOURCES += digibyte-cli-res.rc
endif

# NOTE: This dependency is not strictly necessary, but without it make may try to build both in parallel, which breaks the LevelDB build system in a race
leveldb/libleveldb.a: leveldb/libmemenv.a

leveldb/%.a:
	@echo "Building LevelDB ..." && $(MAKE) -C $(@D) $(@F) CXX="$(CXX)" \
	  CC="$(CC)" PLATFORM=$(TARGET_OS) AR="$(AR)" $(LEVELDB_TARGET_FLAGS) \
	  OPT="$(CXXFLAGS) $(CPPFLAGS)"

qt/digibytestrings.cpp: $(libdigibyte_server_a_SOURCES) $(libdigibyte_common_a_SOURCES) $(libdigibyte_cli_a_SOURCES)
	@test -n $(XGETTEXT) || echo "xgettext is required for updating translations"
	@cd $(top_srcdir); XGETTEXT=$(XGETTEXT) share/qt/extract_strings_qt.py

CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a *.gcda *.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb Makefile.include

clean-local:
	-$(MAKE) -C leveldb clean
	rm -f leveldb/*/*.gcno leveldb/helpers/memenv/*.gcno
