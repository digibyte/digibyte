/* confdefs.h */
#define PACKAGE_NAME "DigiByte Core"
#define PACKAGE_TARNAME "digibyte"
#define PACKAGE_VERSION "6.15.1"
#define PACKAGE_STRING "DigiByte Core 6.15.1"
#define PACKAGE_BUGREPORT "https://github.com/digibyte/digibyte/issues"
#define PACKAGE_URL "https://digibyte.io/"
#define HAVE_CXX11 1
#define STDC_HEADERS 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_SYS_STAT_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRING_H 1
#define HAVE_MEMORY_H 1
#define HAVE_STRINGS_H 1
#define HAVE_INTTYPES_H 1
#define HAVE_STDINT_H 1
#define HAVE_UNISTD_H 1
#define HAVE_DLFCN_H 1
#define LT_OBJDIR ".libs/"
#define HAVE_PTHREAD_PRIO_INHERIT 1
#define HAVE_PTHREAD 1
#define HAVE_DECL_STRERROR_R 1
#define HAVE_STRERROR_R 1
#define HAVE_STDIO_H 1
#define HAVE_STDLIB_H 1
#define HAVE_UNISTD_H 1
#define HAVE_STRINGS_H 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_SYS_STAT_H 1
#define HAVE_SYS_SELECT_H 1
#define HAVE_DECL_STRNLEN 1
#define HAVE_DECL_DAEMON 1
#define HAVE_DECL_LE16TOH 0
#define HAVE_DECL_LE32TOH 0
#define HAVE_DECL_LE64TOH 0
#define HAVE_DECL_HTOLE16 0
#define HAVE_DECL_HTOLE32 0
#define HAVE_DECL_HTOLE64 0
#define HAVE_DECL_BE16TOH 0
#define HAVE_DECL_BE32TOH 0
#define HAVE_DECL_BE64TOH 0
#define HAVE_DECL_HTOBE16 0
#define HAVE_DECL_HTOBE32 0
#define HAVE_DECL_HTOBE64 0
#define HAVE_DECL_BSWAP_16 0
#define HAVE_DECL_BSWAP_32 0
#define HAVE_DECL_BSWAP_64 0
#define HAVE_VISIBILITY_ATTRIBUTE 1
#define HAVE_MINIUPNPC_MINIWGET_H 1
#define HAVE_MINIUPNPC_MINIUPNPC_H 1
#define HAVE_MINIUPNPC_UPNPCOMMANDS_H 1
#define HAVE_MINIUPNPC_UPNPERRORS_H 1
#define HAVE_BOOST /**/
#define HAVE_BOOST_SYSTEM /**/
#define HAVE_BOOST_FILESYSTEM /**/
#define HAVE_BOOST_PROGRAM_OPTIONS /**/
#define HAVE_BOOST_THREAD /**/
#define HAVE_BOOST_CHRONO /**/
/* end confdefs.h.  */

  #include <boost/thread/thread.hpp>
  #include <boost/version.hpp>

int
main ()
{

  #if BOOST_VERSION >= 105000 && (!defined(BOOST_HAS_NANOSLEEP) || BOOST_VERSION >= 105200)
      boost::this_thread::sleep_for(boost::chrono::milliseconds(0));
  #else
   choke me
  #endif

  ;
  return 0;
}
