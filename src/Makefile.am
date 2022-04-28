# Copyright (c) 2009-2019 The Bitcoin Core developers
# Copyright (c) 2014-2019 The DigiByte Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

# Pattern rule to print variables, e.g. make print-top_srcdir
print-%: FORCE
	@echo '$*'='$($*)'

DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS) $(GPROF_LDFLAGS) $(SANITIZER_LDFLAGS)
AM_CXXFLAGS = $(DEBUG_CXXFLAGS) $(HARDENED_CXXFLAGS) $(WARN_CXXFLAGS) $(NOWARN_CXXFLAGS) $(ERROR_CXXFLAGS) $(GPROF_CXXFLAGS) $(SANITIZER_CXXFLAGS)
AM_CPPFLAGS = $(DEBUG_CPPFLAGS) $(HARDENED_CPPFLAGS)
AM_LIBTOOLFLAGS = --preserve-dup-deps
PTHREAD_FLAGS = $(PTHREAD_CFLAGS) $(PTHREAD_LIBS)
EXTRA_LIBRARIES =

if EMBEDDED_UNIVALUE
LIBUNIVALUE = univalue/libunivalue.la

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
else
LIBUNIVALUE = $(UNIVALUE_LIBS)
endif

DIGIBYTE_INCLUDES=-I$(builddir) -I$(srcdir)/secp256k1/include $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS)

DIGIBYTE_INCLUDES += -I$(srcdir)/secp256k1/include
DIGIBYTE_INCLUDES += $(UNIVALUE_CFLAGS)

LIBDIGIBYTE_SERVER=libdigibyte_server.a
LIBDIGIBYTE_COMMON=libdigibyte_common.a
LIBDIGIBYTE_CONSENSUS=libdigibyte_consensus.a
LIBDIGIBYTE_CLI=libdigibyte_cli.a
LIBDIGIBYTE_UTIL=libdigibyte_util.a
LIBDIGIBYTE_CRYPTO_BASE=crypto/libdigibyte_crypto_base.a
LIBDIGIBYTEQT=qt/libdigibyteqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

if ENABLE_ZMQ
LIBDIGIBYTE_ZMQ=libdigibyte_zmq.a
endif
if BUILD_DIGIBYTE_LIBS
LIBDIGIBYTECONSENSUS=libdigibyteconsensus.la
endif
if ENABLE_WALLET
LIBDIGIBYTE_WALLET=libdigibyte_wallet.a
LIBDIGIBYTE_WALLET_TOOL=libdigibyte_wallet_tool.a
endif

LIBDIGIBYTE_CRYPTO= $(LIBDIGIBYTE_CRYPTO_BASE)
if ENABLE_SSE41
LIBDIGIBYTE_CRYPTO_SSE41 = crypto/libdigibyte_crypto_sse41.a
LIBDIGIBYTE_CRYPTO += $(LIBDIGIBYTE_CRYPTO_SSE41)
endif
if ENABLE_AVX2
LIBDIGIBYTE_CRYPTO_AVX2 = crypto/libdigibyte_crypto_avx2.a
LIBDIGIBYTE_CRYPTO += $(LIBDIGIBYTE_CRYPTO_AVX2)
endif
if ENABLE_SHANI
LIBDIGIBYTE_CRYPTO_SHANI = crypto/libdigibyte_crypto_shani.a
LIBDIGIBYTE_CRYPTO += $(LIBDIGIBYTE_CRYPTO_SHANI)
endif

$(LIBSECP256K1): $(wildcard secp256k1/src/*.h) $(wildcard secp256k1/src/*.c) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBDIGIBYTE_CRYPTO) \
  $(LIBDIGIBYTE_UTIL) \
  $(LIBDIGIBYTE_COMMON) \
  $(LIBDIGIBYTE_CONSENSUS) \
  $(LIBDIGIBYTE_SERVER) \
  $(LIBDIGIBYTE_CLI) \
  $(LIBDIGIBYTE_IPC) \
  $(LIBDIGIBYTE_WALLET) \
  $(LIBDIGIBYTE_WALLET_TOOL) \
  $(LIBDIGIBYTE_ZMQ)

lib_LTLIBRARIES = $(LIBDIGIBYTECONSENSUS)

bin_PROGRAMS =
noinst_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_DIGIBYTED
  bin_PROGRAMS += digibyted
endif

if BUILD_DIGIBYTE_NODE
  bin_PROGRAMS += digibyte-node
endif

if BUILD_DIGIBYTE_CLI
  bin_PROGRAMS += digibyte-cli
endif

if BUILD_DIGIBYTE_TX
  bin_PROGRAMS += digibyte-tx
endif

if ENABLE_WALLET
if BUILD_DIGIBYTE_WALLET
  bin_PROGRAMS += digibyte-wallet
endif
endif

if BUILD_DIGIBYTE_UTIL
  bin_PROGRAMS += digibyte-util
endif

.PHONY: FORCE check-symbols check-security
# digibyte core #
DIGIBYTE_CORE_H = \
  addrdb.h \
  addrman.h \
  attributes.h \
  banman.h \
  base58.h \
  bech32.h \
  blockencodings.h \
  blockfilter.h \
  bloom.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkqueue.h \
  clientversion.h \
  coins.h \
  compat.h \
  compat/assumptions.h \
  compat/byteswap.h \
  compat/cpuid.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  consensus/tx_check.h \
  consensus/tx_verify.h \
  core_io.h \
  core_memusage.h \
  cuckoocache.h \
  dbwrapper.h \
  deploymentinfo.h \
  deploymentstatus.h \
  external_signer.h \
  flatfile.h \
  fs.h \
  httprpc.h \
  httpserver.h \
  i2p.h \
  index/base.h \
  index/blockfilterindex.h \
  index/coinstatsindex.h \
  index/disktxpos.h \
  index/txindex.h \
  indirectmap.h \
  init.h \
  init/common.h \
  interfaces/chain.h \
  interfaces/echo.h \
  interfaces/handler.h \
  interfaces/init.h \
  interfaces/ipc.h \
  interfaces/node.h \
  interfaces/wallet.h \
  key.h \
  key_io.h \
  logging.h \
  logging/timer.h \
  mapport.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  net.h \
  net_permissions.h \
  net_processing.h \
  net_types.h \
  netaddress.h \
  netbase.h \
  netmessagemaker.h \
  node/blockstorage.h \
  node/coin.h \
  node/coinstats.h \
  node/context.h \
  node/psbt.h \
  node/transaction.h \
  node/ui_interface.h \
  node/utxo_snapshot.h \
  noui.h \
  outputtype.h \
  policy/feerate.h \
  policy/fees.h \
  policy/packages.h \
  policy/policy.h \
  policy/rbf.h \
  policy/settings.h \
  pow.h \
  protocol.h \
  psbt.h \
  random.h \
  randomenv.h \
  reverse_iterator.h \
  rpc/blockchain.h \
  rpc/client.h \
  rpc/mining.h \
  rpc/net.h \
  rpc/protocol.h \
  rpc/rawtransaction_util.h \
  rpc/register.h \
  rpc/request.h \
  rpc/server.h \
  rpc/util.h \
  scheduler.h \
  script/descriptor.h \
  script/keyorigin.h \
  script/sigcache.h \
  script/sign.h \
  script/signingprovider.h \
  script/standard.h \
  shutdown.h \
  signet.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/events.h \
  support/lockedpool.h \
  sync.h \
  threadinterrupt.h \
  threadsafety.h \
  timedata.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  txorphanage.h \
  txrequest.h \
  undo.h \
  util/asmap.h \
  util/bip32.h \
  util/bytevectorhash.h \
  util/check.h \
  util/epochguard.h \
  util/error.h \
  util/fees.h \
  util/getuniquepath.h \
  util/golombrice.h \
  util/hash_type.h \
  util/hasher.h \
  util/macros.h \
  util/message.h \
  util/moneystr.h \
  util/rbf.h \
  util/readwritefile.h \
  util/serfloat.h \
  util/settings.h \
  util/sock.h \
  util/spanparsing.h \
  util/string.h \
  util/system.h \
  util/thread.h \
  util/threadnames.h \
  util/time.h \
  util/tokenpipe.h \
  util/trace.h \
  util/translation.h \
  util/ui_change_type.h \
  util/url.h \
  util/vector.h \
  validation.h \
  validationinterface.h \
  versionbits.h \
  wallet/bdb.h \
  wallet/coincontrol.h \
  wallet/coinselection.h \
  wallet/context.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/dump.h \
  wallet/external_signer_scriptpubkeyman.h \
  wallet/feebumper.h \
  wallet/fees.h \
  wallet/ismine.h \
  wallet/load.h \
  wallet/receive.h \
  wallet/rpcwallet.h \
  wallet/salvage.h \
  wallet/scriptpubkeyman.h \
  wallet/spend.h \
  wallet/sqlite.h \
  wallet/transaction.h \
  wallet/wallet.h \
  wallet/walletdb.h \
  wallet/wallettool.h \
  wallet/walletutil.h \
  walletinitinterface.h \
  warnings.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h \
  zmq/zmqrpc.h \
  zmq/zmqutil.h


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh "$(abs_top_builddir)/src/obj/build.h" \
	  "$(abs_top_srcdir)"
libdigibyte_util_a-clientversion.$(OBJEXT): obj/build.h

ipc/capnp/libdigibyte_ipc_a-ipc.$(OBJEXT): $(libdigibyte_ipc_mpgen_input:=.h)

# server: shared between digibyted and digibyte-qt
# Contains code accessing mempool and chain state that is meant to be separated
# from wallet and gui code (see node/README.md). Shared code should go in
# libdigibyte_common or libdigibyte_util libraries, instead.
libdigibyte_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(DIGIBYTE_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(NATPMP_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libdigibyte_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libdigibyte_server_a_SOURCES = \
  addrdb.cpp \
  addrman.cpp \
  banman.cpp \
  blockencodings.cpp \
  blockfilter.cpp \
  chain.cpp \
  consensus/tx_verify.cpp \
  dandelion.cpp \
  dbwrapper.cpp \
  deploymentstatus.cpp \
  flatfile.cpp \
  httprpc.cpp \
  httpserver.cpp \
  i2p.cpp \
  index/base.cpp \
  index/blockfilterindex.cpp \
  index/coinstatsindex.cpp \
  index/txindex.cpp \
  init.cpp \
  mapport.cpp \
  miner.cpp \
  net.cpp \
  net_processing.cpp \
  node/blockstorage.cpp \
  node/coin.cpp \
  node/coinstats.cpp \
  node/context.cpp \
  node/interfaces.cpp \
  node/psbt.cpp \
  node/transaction.cpp \
  node/ui_interface.cpp \
  noui.cpp \
  policy/fees.cpp \
  policy/packages.cpp \
  policy/rbf.cpp \
  policy/settings.cpp \
  pow.cpp \
  rest.cpp \
  rpc/blockchain.cpp \
  rpc/mining.cpp \
  rpc/misc.cpp \
  rpc/net.cpp \
  rpc/rawtransaction.cpp \
  rpc/server.cpp \
  script/sigcache.cpp \
  shutdown.cpp \
  signet.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  txorphanage.cpp \
  txrequest.cpp \
  validation.cpp \
  validationinterface.cpp \
  versionbits.cpp \
  $(DIGIBYTE_CORE_H)

if ENABLE_WALLET
libdigibyte_server_a_SOURCES += wallet/init.cpp
endif
if !ENABLE_WALLET
libdigibyte_server_a_SOURCES += dummywallet.cpp
endif

if ENABLE_ZMQ
libdigibyte_zmq_a_CPPFLAGS = $(AM_CPPFLAGS) $(DIGIBYTE_INCLUDES) $(ZMQ_CFLAGS)
libdigibyte_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libdigibyte_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp \
  zmq/zmqrpc.cpp \
  zmq/zmqutil.cpp
endif


# wallet: shared between digibyted and digibyte-qt, but only linked
# when wallet enabled
libdigibyte_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(DIGIBYTE_INCLUDES) $(SQLITE_CFLAGS)
libdigibyte_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libdigibyte_wallet_a_SOURCES = \
  wallet/coincontrol.cpp \
  wallet/context.cpp \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/dump.cpp \
  wallet/external_signer_scriptpubkeyman.cpp \
  wallet/feebumper.cpp \
  wallet/fees.cpp \
  wallet/interfaces.cpp \
  wallet/load.cpp \
  wallet/receive.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/scriptpubkeyman.cpp \
  wallet/spend.cpp \
  wallet/transaction.cpp \
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  wallet/walletutil.cpp \
  wallet/coinselection.cpp \
  $(DIGIBYTE_CORE_H)

if USE_SQLITE
libdigibyte_wallet_a_SOURCES += wallet/sqlite.cpp
endif
if USE_BDB
libdigibyte_wallet_a_SOURCES += wallet/bdb.cpp wallet/salvage.cpp
endif

libdigibyte_wallet_tool_a_CPPFLAGS = $(AM_CPPFLAGS) $(DIGIBYTE_INCLUDES)
libdigibyte_wallet_tool_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libdigibyte_wallet_tool_a_SOURCES = \
  wallet/wallettool.cpp \
  $(DIGIBYTE_CORE_H)

# crypto primitives library
crypto_libdigibyte_crypto_base_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libdigibyte_crypto_base_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libdigibyte_crypto_base_a_SOURCES = \
  crypto/aes.cpp \
  crypto/aes_helper.c \
  crypto/aes.h \
  crypto/chacha_poly_aead.h \
  crypto/chacha_poly_aead.cpp \
  crypto/chacha20.h \
  crypto/chacha20.cpp \
  crypto/common.h \
  crypto/hkdf_sha256_32.cpp \
  crypto/hkdf_sha256_32.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/KeccakP-800-reference.c \
  crypto/KeccakP-800-SnP.h \
  crypto/poly1305.h \
  crypto/poly1305.cpp \
  crypto/muhash.h \
  crypto/muhash.cpp \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha3.cpp \
  crypto/sha3.h \
  crypto/sha512.cpp \
  crypto/sha512.h \
  crypto/siphash.cpp \
  crypto/siphash.h


if USE_ASM
crypto_libdigibyte_crypto_base_a_SOURCES += crypto/sha256_sse4.cpp
endif

crypto_libdigibyte_crypto_sse41_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libdigibyte_crypto_sse41_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libdigibyte_crypto_sse41_a_CXXFLAGS += $(SSE41_CXXFLAGS)
crypto_libdigibyte_crypto_sse41_a_CPPFLAGS += -DENABLE_SSE41
crypto_libdigibyte_crypto_sse41_a_SOURCES = crypto/sha256_sse41.cpp

crypto_libdigibyte_crypto_avx2_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libdigibyte_crypto_avx2_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libdigibyte_crypto_avx2_a_CXXFLAGS += $(AVX2_CXXFLAGS)
crypto_libdigibyte_crypto_avx2_a_CPPFLAGS += -DENABLE_AVX2
crypto_libdigibyte_crypto_avx2_a_SOURCES = crypto/sha256_avx2.cpp

crypto_libdigibyte_crypto_shani_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libdigibyte_crypto_shani_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libdigibyte_crypto_shani_a_CXXFLAGS += $(SHANI_CXXFLAGS)
crypto_libdigibyte_crypto_shani_a_CPPFLAGS += -DENABLE_SHANI
crypto_libdigibyte_crypto_shani_a_SOURCES = crypto/sha256_shani.cpp

# consensus: shared between all executables that validate any consensus rules.
libdigibyte_consensus_a_CPPFLAGS = $(AM_CPPFLAGS) $(DIGIBYTE_INCLUDES)
libdigibyte_consensus_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libdigibyte_consensus_a_SOURCES = \
  amount.h \
  arith_uint256.cpp \
  arith_uint256.h \
  consensus/merkle.cpp \
  consensus/merkle.h \
  consensus/params.h \
  consensus/tx_check.cpp \
  consensus/validation.h \
  crypto/blake.c \
  crypto/bmw.c \
  crypto/cubehash.c \
  crypto/echo.c \
  crypto/groestl.c \
  crypto/jh.c \
  crypto/keccak.c \
  crypto/luffa.c \
  crypto/shavite.c \
  crypto/simd.c \
  crypto/skein.c \
  crypto/hashgroestl.h \
  crypto/hashodo.h \
  crypto/hashqubit.h \
  crypto/hashskein.h \
  crypto/odocrypt.cpp \
  crypto/odocrypt.h \
  crypto/scrypt.cpp \
  crypto/scrypt-sse2.cpp \
  crypto/sph_blake.h \
  crypto/sph_bmw.h \
  crypto/sph_cubehash.h \
  crypto/sph_echo.h \
  crypto/sph_groestl.h \
  crypto/sph_jh.h \
  crypto/sph_keccak.h \
  crypto/sph_luffa.h \
  crypto/sph_shavite.h \
  crypto/sph_simd.h \
  crypto/sph_skein.h \
  crypto/sph_types.h \
  crypto/scrypt.h \
  hash.cpp \
  hash.h \
  prevector.h \
  primitives/block.cpp \
  primitives/block.h \
  primitives/transaction.cpp \
  primitives/transaction.h \
  pubkey.cpp \
  pubkey.h \
  script/digibyteconsensus.cpp \
  script/interpreter.cpp \
  script/interpreter.h \
  script/script.cpp \
  script/script.h \
  script/script_error.cpp \
  script/script_error.h \
  serialize.h \
  span.h \
  tinyformat.h \
  uint256.cpp \
  uint256.h \
  util/strencodings.cpp \
  util/strencodings.h \
  version.h

# common: shared between digibyted, and digibyte-qt and non-server tools
libdigibyte_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(DIGIBYTE_INCLUDES)
libdigibyte_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libdigibyte_common_a_SOURCES = \
  base58.cpp \
  bech32.cpp \
  bloom.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  core_read.cpp \
  core_write.cpp \
  deploymentinfo.cpp \
  external_signer.cpp \
  init/common.cpp \
  key.cpp \
  key_io.cpp \
  merkleblock.cpp \
  netaddress.cpp \
  netbase.cpp \
  net_permissions.cpp \
  outputtype.cpp \
  policy/feerate.cpp \
  policy/policy.cpp \
  protocol.cpp \
  psbt.cpp \
  rpc/rawtransaction_util.cpp \
  rpc/external_signer.cpp \
  rpc/util.cpp \
  scheduler.cpp \
  script/descriptor.cpp \
  script/sign.cpp \
  script/signingprovider.cpp \
  script/standard.cpp \
  warnings.cpp \
  $(DIGIBYTE_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libdigibyte_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(DIGIBYTE_INCLUDES)
libdigibyte_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libdigibyte_util_a_SOURCES = \
  support/lockedpool.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  fs.cpp \
  interfaces/echo.cpp \
  interfaces/handler.cpp \
  interfaces/init.cpp \
  logging.cpp \
  random.cpp \
  randomenv.cpp \
  rpc/request.cpp \
  support/cleanse.cpp \
  sync.cpp \
  threadinterrupt.cpp \
  util/asmap.cpp \
  util/bip32.cpp \
  util/bytevectorhash.cpp \
  util/error.cpp \
  util/fees.cpp \
  util/getuniquepath.cpp \
  util/hasher.cpp \
  util/sock.cpp \
  util/system.cpp \
  util/message.cpp \
  util/moneystr.cpp \
  util/rbf.cpp \
  util/readwritefile.cpp \
  util/settings.cpp \
  util/thread.cpp \
  util/threadnames.cpp \
  util/serfloat.cpp \
  util/spanparsing.cpp \
  util/strencodings.cpp \
  util/string.cpp \
  util/time.cpp \
  util/tokenpipe.cpp \
  $(DIGIBYTE_CORE_H)

if USE_LIBEVENT
libdigibyte_util_a_SOURCES += util/url.cpp
endif

if GLIBC_BACK_COMPAT
libdigibyte_util_a_SOURCES += compat/glibc_compat.cpp
AM_LDFLAGS += $(COMPAT_LDFLAGS)
endif

# cli: shared between digibyte-cli and digibyte-qt
libdigibyte_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(DIGIBYTE_INCLUDES)
libdigibyte_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libdigibyte_cli_a_SOURCES = \
  compat/stdin.h \
  compat/stdin.cpp \
  rpc/client.cpp \
  $(DIGIBYTE_CORE_H)

nodist_libdigibyte_util_a_SOURCES = $(srcdir)/obj/build.h
#

# digibyted & digibyte-node binaries #
digibyte_daemon_sources = digibyted.cpp
digibyte_bin_cppflags = $(AM_CPPFLAGS) $(DIGIBYTE_INCLUDES)
digibyte_bin_cxxflags = $(AM_CXXFLAGS) $(PIE_FLAGS)
digibyte_bin_ldflags = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS) $(PTHREAD_FLAGS)

if TARGET_WINDOWS
digibyte_daemon_sources += digibyted-res.rc
endif

digibyte_bin_ldadd = \
  $(LIBDIGIBYTE_WALLET) \
  $(LIBDIGIBYTE_COMMON) \
  $(LIBDIGIBYTE_UTIL) \
  $(LIBUNIVALUE) \
  $(LIBDIGIBYTE_UTIL) \
  $(LIBDIGIBYTE_ZMQ) \
  $(LIBDIGIBYTE_CONSENSUS) \
  $(LIBDIGIBYTE_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBLEVELDB_SSE42) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

digibyte_bin_ldadd += $(BOOST_LIBS) $(BDB_LIBS) $(MINIUPNPC_LIBS) $(NATPMP_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS) $(SQLITE_LIBS)

digibyted_SOURCES = $(digibyte_daemon_sources) init/digibyted.cpp
digibyted_CPPFLAGS = $(digibyte_bin_cppflags)
digibyted_CXXFLAGS = $(digibyte_bin_cxxflags)
digibyted_LDFLAGS = $(digibyte_bin_ldflags)
digibyted_LDADD = $(LIBDIGIBYTE_SERVER) $(digibyte_bin_ldadd)

digibyte_node_SOURCES = $(digibyte_daemon_sources) init/digibyte-node.cpp
digibyte_node_CPPFLAGS = $(digibyte_bin_cppflags)
digibyte_node_CXXFLAGS = $(digibyte_bin_cxxflags)
digibyte_node_LDFLAGS = $(digibyte_bin_ldflags)
digibyte_node_LDADD = $(LIBDIGIBYTE_SERVER) $(digibyte_bin_ldadd) $(LIBDIGIBYTE_IPC) $(LIBMULTIPROCESS_LIBS)

# digibyte-cli binary #
digibyte_cli_SOURCES = digibyte-cli.cpp
digibyte_cli_CPPFLAGS = $(AM_CPPFLAGS) $(DIGIBYTE_INCLUDES) $(EVENT_CFLAGS)
digibyte_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
digibyte_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS) $(PTHREAD_FLAGS)

if TARGET_WINDOWS
digibyte_cli_SOURCES += digibyte-cli-res.rc
endif

digibyte_cli_LDADD = \
  $(LIBDIGIBYTE_CLI) \
  $(LIBUNIVALUE) \
  $(LIBDIGIBYTE_COMMON) \
  $(LIBDIGIBYTE_CONSENSUS) \  
  $(LIBDIGIBYTE_UTIL) \
  $(LIBDIGIBYTE_CRYPTO)

digibyte_cli_LDADD += $(BOOST_LIBS) $(EVENT_LIBS)
#

# digibyte-tx binary #
digibyte_tx_SOURCES = digibyte-tx.cpp
digibyte_tx_CPPFLAGS = $(AM_CPPFLAGS) $(DIGIBYTE_INCLUDES)
digibyte_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
digibyte_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS) $(PTHREAD_FLAGS)

if TARGET_WINDOWS
digibyte_tx_SOURCES += digibyte-tx-res.rc
endif

digibyte_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBDIGIBYTE_COMMON) \
  $(LIBDIGIBYTE_UTIL) \
  $(LIBDIGIBYTE_CONSENSUS) \
  $(LIBDIGIBYTE_CRYPTO) \
  $(LIBSECP256K1)

digibyte_tx_LDADD += $(BOOST_LIBS)
#

# digibyte-wallet binary #
digibyte_wallet_SOURCES = digibyte-wallet.cpp
digibyte_wallet_CPPFLAGS = $(digibyte_bin_cppflags)
digibyte_wallet_CXXFLAGS = $(digibyte_bin_cxxflags)
digibyte_wallet_LDFLAGS = $(digibyte_bin_ldflags)
digibyte_wallet_LDADD = $(LIBDIGIBYTE_WALLET_TOOL) $(digibyte_bin_ldadd)

if TARGET_WINDOWS
digibyte_wallet_SOURCES += digibyte-wallet-res.rc
endif
#

# digibyte-util binary #
digibyte_util_SOURCES = digibyte-util.cpp
digibyte_util_CPPFLAGS = $(AM_CPPFLAGS) $(DIGIBYTE_INCLUDES)
digibyte_util_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
digibyte_util_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS) $(PTHREAD_FLAGS)

if TARGET_WINDOWS
digibyte_util_SOURCES += digibyte-util-res.rc
endif

digibyte_util_LDADD = \
  $(LIBDIGIBYTE_COMMON) \
  $(LIBDIGIBYTE_UTIL) \
  $(LIBUNIVALUE) \
  $(LIBDIGIBYTE_CONSENSUS) \
  $(LIBDIGIBYTE_CRYPTO) \
  $(LIBSECP256K1)

digibyte_util_LDADD += $(BOOST_LIBS)
#

# digibyteconsensus library #
if BUILD_DIGIBYTE_LIBS
include_HEADERS = script/digibyteconsensus.h
libdigibyteconsensus_la_SOURCES = support/cleanse.cpp $(crypto_libdigibyte_crypto_base_a_SOURCES) $(libdigibyte_consensus_a_SOURCES)

if GLIBC_BACK_COMPAT
  libdigibyteconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libdigibyteconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libdigibyteconsensus_la_LIBADD = $(LIBSECP256K1)
libdigibyteconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_DIGIBYTE_INTERNAL
libdigibyteconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CTAES_DIST =  crypto/ctaes/bench.c
CTAES_DIST += crypto/ctaes/ctaes.c
CTAES_DIST += crypto/ctaes/ctaes.h
CTAES_DIST += crypto/ctaes/README.md
CTAES_DIST += crypto/ctaes/test.c

CLEANFILES = $(EXTRA_LIBRARIES)

CLEANFILES += *.gcda *.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crc32c/src/*.gcda crc32c/src/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += index/*.gcda index/*.gcno
CLEANFILES += interfaces/*.gcda interfaces/*.gcno
CLEANFILES += node/*.gcda node/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += rpc/*.gcda rpc/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += util/*.gcda util/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno
CLEANFILES += obj/build.h

EXTRA_DIST = $(CTAES_DIST)


config/digibyte-config.h: config/stamp-h1
	@$(MAKE) -C $(top_builddir) $(subdir)/$(@)
config/stamp-h1: $(top_srcdir)/$(subdir)/config/digibyte-config.h.in $(top_builddir)/config.status
	$(AM_V_at)$(MAKE) -C $(top_builddir) $(subdir)/$(@)
$(top_srcdir)/$(subdir)/config/digibyte-config.h.in:  $(am__configure_deps)
	$(AM_V_at)$(MAKE) -C $(top_srcdir) $(subdir)/config/digibyte-config.h.in

clean-local:
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h
	-rm -rf test/__pycache__

.rc.o:
	@test -f $(WINDRES)
	## FIXME: How to get the appropriate modulename_CPPFLAGS in here?
	$(AM_V_GEN) $(WINDRES) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) -DWINDRES_PREPROC -i $< -o $@

check-symbols: $(bin_PROGRAMS)
if TARGET_DARWIN
	@echo "Checking macOS dynamic libraries..."
	$(AM_V_at) $(PYTHON) $(top_srcdir)/contrib/devtools/symbol-check.py $(bin_PROGRAMS)
endif

if TARGET_WINDOWS
	@echo "Checking Windows dynamic libraries..."
	$(AM_V_at) $(PYTHON) $(top_srcdir)/contrib/devtools/symbol-check.py $(bin_PROGRAMS)
endif

if TARGET_LINUX
	@echo "Checking glibc back compat..."
	$(AM_V_at) CPPFILT='$(CPPFILT)' $(PYTHON) $(top_srcdir)/contrib/devtools/symbol-check.py $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) $(PYTHON) $(top_srcdir)/contrib/devtools/security-check.py $(bin_PROGRAMS)
endif

libdigibyte_ipc_mpgen_input = \
  ipc/capnp/echo.capnp \
  ipc/capnp/init.capnp
EXTRA_DIST += $(libdigibyte_ipc_mpgen_input)
%.capnp:

if BUILD_MULTIPROCESS
LIBDIGIBYTE_IPC=libdigibyte_ipc.a
libdigibyte_ipc_a_SOURCES = \
  ipc/capnp/init-types.h \
  ipc/capnp/protocol.cpp \
  ipc/capnp/protocol.h \
  ipc/exception.h \
  ipc/interfaces.cpp \
  ipc/process.cpp \
  ipc/process.h \
  ipc/protocol.h
libdigibyte_ipc_a_CPPFLAGS = $(AM_CPPFLAGS) $(DIGIBYTE_INCLUDES)
libdigibyte_ipc_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS) $(LIBMULTIPROCESS_CFLAGS)

include $(MPGEN_PREFIX)/include/mpgen.mk
libdigibyte_ipc_mpgen_output = \
  $(libdigibyte_ipc_mpgen_input:=.c++) \
  $(libdigibyte_ipc_mpgen_input:=.h) \
  $(libdigibyte_ipc_mpgen_input:=.proxy-client.c++) \
  $(libdigibyte_ipc_mpgen_input:=.proxy-server.c++) \
  $(libdigibyte_ipc_mpgen_input:=.proxy-types.c++) \
  $(libdigibyte_ipc_mpgen_input:=.proxy-types.h) \
  $(libdigibyte_ipc_mpgen_input:=.proxy.h)
nodist_libdigibyte_ipc_a_SOURCES = $(libdigibyte_ipc_mpgen_output)
CLEANFILES += $(libdigibyte_ipc_mpgen_output)
endif

if EMBEDDED_LEVELDB
include Makefile.crc32c.include
include Makefile.leveldb.include
endif

include Makefile.test_util.include
include Makefile.test_fuzz.include

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
