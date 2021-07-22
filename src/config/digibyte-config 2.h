/* src/config/digibyte-config.h.  Generated from digibyte-config.h.in by configure.  */
/* src/config/digibyte-config.h.in.  Generated from configure.ac by autoheader.  */

#ifndef DIGIBYTE_CONFIG_H

#define DIGIBYTE_CONFIG_H

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* Define this symbol if type char equals int8_t */
/* #undef CHAR_EQUALS_INT8 */

/* Version Build */
#define CLIENT_VERSION_BUILD 0

/* Version is release */
#define CLIENT_VERSION_IS_RELEASE true

/* Major version */
#define CLIENT_VERSION_MAJOR 22

/* Minor version */
#define CLIENT_VERSION_MINOR 0

/* Copyright holder(s) before %s replacement */
#define COPYRIGHT_HOLDERS "The %s developers"

/* Copyright holder(s) */
#define COPYRIGHT_HOLDERS_FINAL "The Bitcoin Core developers"

/* Replacement for %s in copyright holders string */
#define COPYRIGHT_HOLDERS_SUBSTITUTION "Bitcoin Core"

/* Copyright year */
#define COPYRIGHT_YEAR 2021

/* Define this symbol to build code that uses AVX2 intrinsics */
#define ENABLE_AVX2 1

/* define if external signer support is enabled */
#define ENABLE_EXTERNAL_SIGNER /**/

/* Define this symbol to build code that uses SHA-NI intrinsics */
#define ENABLE_SHANI 1

/* Define this symbol to build code that uses SSE4.1 intrinsics */
#define ENABLE_SSE41 1

/* Define to 1 to enable eBPF user static defined tracepoints */
/* #undef ENABLE_TRACING */

/* Define to 1 to enable wallet functions */
#define ENABLE_WALLET 1

/* Define to 1 to enable ZMQ functions */
#define ENABLE_ZMQ 0

/* define if the Boost library is available */
#define HAVE_BOOST /**/

/* define if the Boost::Filesystem library is available */
#define HAVE_BOOST_FILESYSTEM /**/

/* define if the Boost::System library is available */
#define HAVE_BOOST_SYSTEM /**/

/* define if the Boost::Unit_Test_Framework library is available */
#define HAVE_BOOST_UNIT_TEST_FRAMEWORK /**/

/* Define this symbol if you have __builtin_clzl */
#define HAVE_BUILTIN_CLZL 1

/* Define this symbol if you have __builtin_clzll */
#define HAVE_BUILTIN_CLZLL 1

/* Define to 1 if you have the <byteswap.h> header file. */
/* #undef HAVE_BYTESWAP_H */

/* Define this symbol if the consensus lib has been built */
#define HAVE_CONSENSUS_LIB 1

/* define if the compiler supports basic C++17 syntax */
#define HAVE_CXX17 1

/* Define to 1 if you have the declaration of `be16toh', and to 0 if you
   don't. */
#define HAVE_DECL_BE16TOH 0

/* Define to 1 if you have the declaration of `be32toh', and to 0 if you
   don't. */
#define HAVE_DECL_BE32TOH 0

/* Define to 1 if you have the declaration of `be64toh', and to 0 if you
   don't. */
#define HAVE_DECL_BE64TOH 0

/* Define to 1 if you have the declaration of `bswap_16', and to 0 if you
   don't. */
#define HAVE_DECL_BSWAP_16 0

/* Define to 1 if you have the declaration of `bswap_32', and to 0 if you
   don't. */
#define HAVE_DECL_BSWAP_32 0

/* Define to 1 if you have the declaration of `bswap_64', and to 0 if you
   don't. */
#define HAVE_DECL_BSWAP_64 0

/* Define to 1 if you have the declaration of `fork', and to 0 if you don't.
   */
#define HAVE_DECL_FORK 1

/* Define to 1 if you have the declaration of `freeifaddrs', and to 0 if you
   don't. */
#define HAVE_DECL_FREEIFADDRS 1

/* Define to 1 if you have the declaration of `getifaddrs', and to 0 if you
   don't. */
#define HAVE_DECL_GETIFADDRS 1

/* Define to 1 if you have the declaration of `htobe16', and to 0 if you
   don't. */
#define HAVE_DECL_HTOBE16 0

/* Define to 1 if you have the declaration of `htobe32', and to 0 if you
   don't. */
#define HAVE_DECL_HTOBE32 0

/* Define to 1 if you have the declaration of `htobe64', and to 0 if you
   don't. */
#define HAVE_DECL_HTOBE64 0

/* Define to 1 if you have the declaration of `htole16', and to 0 if you
   don't. */
#define HAVE_DECL_HTOLE16 0

/* Define to 1 if you have the declaration of `htole32', and to 0 if you
   don't. */
#define HAVE_DECL_HTOLE32 0

/* Define to 1 if you have the declaration of `htole64', and to 0 if you
   don't. */
#define HAVE_DECL_HTOLE64 0

/* Define to 1 if you have the declaration of `le16toh', and to 0 if you
   don't. */
#define HAVE_DECL_LE16TOH 0

/* Define to 1 if you have the declaration of `le32toh', and to 0 if you
   don't. */
#define HAVE_DECL_LE32TOH 0

/* Define to 1 if you have the declaration of `le64toh', and to 0 if you
   don't. */
#define HAVE_DECL_LE64TOH 0

/* Define to 1 if you have the declaration of `pipe2', and to 0 if you don't.
   */
#define HAVE_DECL_PIPE2 0

/* Define to 1 if you have the declaration of `setsid', and to 0 if you don't.
   */
#define HAVE_DECL_SETSID 1

/* Define to 1 if you have the declaration of `strerror_r', and to 0 if you
   don't. */
#define HAVE_DECL_STRERROR_R 1

/* Define to 1 if you have the declaration of `strnlen', and to 0 if you
   don't. */
#define HAVE_DECL_STRNLEN 1

/* Define if the visibility attribute is supported. */
#define HAVE_DEFAULT_VISIBILITY_ATTRIBUTE 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define if the dllexport attribute is supported. */
/* #undef HAVE_DLLEXPORT_ATTRIBUTE */

/* Define to 1 if you have the <endian.h> header file. */
/* #undef HAVE_ENDIAN_H */

/* Define to 1 if fdatasync is available. */
#define HAVE_FDATASYNC 0

/* Define this symbol if the BSD getentropy system call is available */
/* #undef HAVE_GETENTROPY */

/* Define this symbol if the BSD getentropy system call is available with
   sys/random.h */
#define HAVE_GETENTROPY_RAND 1

/* Define this symbol if gmtime_r is available */
#define HAVE_GMTIME_R 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `advapi32' library (-ladvapi32). */
/* #undef HAVE_LIBADVAPI32 */

/* Define to 1 if you have the `comctl32' library (-lcomctl32). */
/* #undef HAVE_LIBCOMCTL32 */

/* Define to 1 if you have the `comdlg32' library (-lcomdlg32). */
/* #undef HAVE_LIBCOMDLG32 */

/* Define to 1 if you have the `gdi32' library (-lgdi32). */
/* #undef HAVE_LIBGDI32 */

/* Define to 1 if you have the `iphlpapi' library (-liphlpapi). */
/* #undef HAVE_LIBIPHLPAPI */

/* Define to 1 if you have the `kernel32' library (-lkernel32). */
/* #undef HAVE_LIBKERNEL32 */

/* Define to 1 if you have the `ole32' library (-lole32). */
/* #undef HAVE_LIBOLE32 */

/* Define to 1 if you have the `oleaut32' library (-loleaut32). */
/* #undef HAVE_LIBOLEAUT32 */

/* Define to 1 if you have the `shell32' library (-lshell32). */
/* #undef HAVE_LIBSHELL32 */

/* Define to 1 if you have the `shlwapi' library (-lshlwapi). */
/* #undef HAVE_LIBSHLWAPI */

/* Define to 1 if you have the `ssp' library (-lssp). */
/* #undef HAVE_LIBSSP */

/* Define to 1 if you have the `user32' library (-luser32). */
/* #undef HAVE_LIBUSER32 */

/* Define to 1 if you have the `uuid' library (-luuid). */
/* #undef HAVE_LIBUUID */

/* Define to 1 if you have the `winmm' library (-lwinmm). */
/* #undef HAVE_LIBWINMM */

/* Define to 1 if you have the `ws2_32' library (-lws2_32). */
/* #undef HAVE_LIBWS2_32 */

/* Define this symbol if you have malloc_info */
/* #undef HAVE_MALLOC_INFO */

/* Define this symbol if you have mallopt with M_ARENA_MAX */
/* #undef HAVE_MALLOPT_ARENA_MAX */

/* Define to 1 if you have the <miniupnpc/miniupnpc.h> header file. */
#define HAVE_MINIUPNPC_MINIUPNPC_H 1

/* Define to 1 if you have the <miniupnpc/upnpcommands.h> header file. */
#define HAVE_MINIUPNPC_UPNPCOMMANDS_H 1

/* Define to 1 if you have the <miniupnpc/upnperrors.h> header file. */
#define HAVE_MINIUPNPC_UPNPERRORS_H 1

/* Define to 1 if you have the <natpmp.h> header file. */
/* #undef HAVE_NATPMP_H */

/* Define to 1 if O_CLOEXEC flag is available. */
#define HAVE_O_CLOEXEC 1

/* Define this symbol if you have posix_fallocate */
/* #undef HAVE_POSIX_FALLOCATE */

/* Define if you have POSIX threads libraries and header files. */
#define HAVE_PTHREAD 1

/* Have PTHREAD_PRIO_INHERIT. */
#define HAVE_PTHREAD_PRIO_INHERIT 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdio.h> header file. */
#define HAVE_STDIO_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if std::system is available. */
#define HAVE_STD__SYSTEM 1

/* Define if you have `strerror_r'. */
#define HAVE_STRERROR_R 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define this symbol to build code that uses getauxval) */
/* #undef HAVE_STRONG_GETAUXVAL */

/* Define this symbol if the BSD sysctl() is available */
#define HAVE_SYSCTL 1

/* Define this symbol if the BSD sysctl(KERN_ARND) is available */
/* #undef HAVE_SYSCTL_ARND */

/* std::system or ::wsystem */
#define HAVE_SYSTEM HAVE_STD__SYSTEM || HAVE_WSYSTEM

/* Define to 1 if you have the <sys/endian.h> header file. */
/* #undef HAVE_SYS_ENDIAN_H */

/* Define this symbol if the Linux getrandom system call is available */
/* #undef HAVE_SYS_GETRANDOM */

/* Define to 1 if you have the <sys/prctl.h> header file. */
/* #undef HAVE_SYS_PRCTL_H */

/* Define to 1 if you have the <sys/resources.h> header file. */
/* #undef HAVE_SYS_RESOURCES_H */

/* Define to 1 if you have the <sys/select.h> header file. */
#define HAVE_SYS_SELECT_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/sysctl.h> header file. */
#define HAVE_SYS_SYSCTL_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/vmmeter.h> header file. */
#define HAVE_SYS_VMMETER_H 1

/* Define if thread_local is supported. */
#define HAVE_THREAD_LOCAL 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the <vm/vm_param.h> header file. */
/* #undef HAVE_VM_VM_PARAM_H */

/* Define this symbol to build code that uses getauxval (weak linking) */
/* #undef HAVE_WEAK_GETAUXVAL */

/* Define to 1 if ::wsystem is available. */
/* #undef HAVE_WSYSTEM */

/* Define to 1 if the system has the type `__int128'. */
#define HAVE___INT128 1

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#define LT_OBJDIR ".libs/"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "https://github.com/digibyte/digibyte/issues"

/* Define to the full name of this package. */
#define PACKAGE_NAME "Bitcoin Core"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "Bitcoin Core 22.0.0rc1"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "digibyte"

/* Define to the home page for this package. */
#define PACKAGE_URL "https://digibytecore.org/"

/* Define to the version of this package. */
#define PACKAGE_VERSION "22.0.0rc1"

/* Define to necessary symbol if this constant uses a non-standard name on
   your system. */
/* #undef PTHREAD_CREATE_JOINABLE */

/* Define this symbol if the qt platform is android */
/* #undef QT_QPA_PLATFORM_ANDROID */

/* Define this symbol if the qt platform is cocoa */
/* #undef QT_QPA_PLATFORM_COCOA */

/* Define this symbol if the minimal qt platform exists */
/* #undef QT_QPA_PLATFORM_MINIMAL */

/* Define this symbol if the qt platform is windows */
/* #undef QT_QPA_PLATFORM_WINDOWS */

/* Define this symbol if the qt platform is xcb */
/* #undef QT_QPA_PLATFORM_XCB */

/* Define this symbol if qt plugins are static */
/* #undef QT_STATICPLUGIN */

/* Define to 1 if all of the C90 standard headers exist (not just the ones
   required in a freestanding environment). This macro is provided for
   backward compatibility; new code need not use it. */
#define STDC_HEADERS 1

/* Define to 1 if strerror_r returns char *. */
/* #undef STRERROR_R_CHAR_P */

/* Define this symbol to build in assembly routines */
#define USE_ASM 1

/* Define if BDB support should be compiled in */
#define USE_BDB 1

/* Define if dbus support should be compiled in */
#define USE_DBUS 1

/* NAT-PMP support not compiled if undefined, otherwise value (0 or 1)
   determines default state */
/* #undef USE_NATPMP */

/* Define if QR support should be compiled in */
#define USE_QRCODE 1

/* Define if sqlite support should be compiled in */
#define USE_SQLITE 1

/* UPnP support not compiled if undefined, otherwise value (0 or 1) determines
   default state */
#define USE_UPNP 0

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

#endif //DIGIBYTE_CONFIG_H
