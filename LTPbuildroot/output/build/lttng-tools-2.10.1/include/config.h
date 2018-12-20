/* include/config.h.  Generated from config.h.in by configure.  */
/* include/config.h.in.  Generated from configure.ac by autoheader.  */

/* Location of the babeltrace viewer executable. */
#define CONFIG_BABELTRACE_BIN ""

/* CMD_DESCR_ADD_CONTEXT */
#define CONFIG_CMD_DESCR_ADD_CONTEXT "Add context fields to a channel"

/* CMD_DESCR_CREATE */
#define CONFIG_CMD_DESCR_CREATE "Create a tracing session"

/* CMD_DESCR_DESTROY */
#define CONFIG_CMD_DESCR_DESTROY "Tear down tracing sessions"

/* CMD_DESCR_DISABLE_CHANNEL */
#define CONFIG_CMD_DESCR_DISABLE_CHANNEL "Disable tracing channels"

/* CMD_DESCR_DISABLE_EVENT */
#define CONFIG_CMD_DESCR_DISABLE_EVENT "Disable event rules"

/* CMD_DESCR_ENABLE_CHANNEL */
#define CONFIG_CMD_DESCR_ENABLE_CHANNEL "Create or enable tracing channels"

/* CMD_DESCR_ENABLE_EVENT */
#define CONFIG_CMD_DESCR_ENABLE_EVENT "Create or enable event rules"

/* CMD_DESCR_HELP */
#define CONFIG_CMD_DESCR_HELP "Display help information about a command"

/* CMD_DESCR_LIST */
#define CONFIG_CMD_DESCR_LIST "List tracing sessions, domains, channels, and events"

/* CMD_DESCR_LOAD */
#define CONFIG_CMD_DESCR_LOAD "Load tracing session configurations"

/* CMD_DESCR_REGENERATE */
#define CONFIG_CMD_DESCR_REGENERATE "Manage an LTTng tracing session's data regeneration"

/* CMD_DESCR_SAVE */
#define CONFIG_CMD_DESCR_SAVE "Save tracing session configurations"

/* CMD_DESCR_SET_SESSION */
#define CONFIG_CMD_DESCR_SET_SESSION "Set current tracing session"

/* CMD_DESCR_SNAPSHOT */
#define CONFIG_CMD_DESCR_SNAPSHOT "Snapshot buffers of current tracing session"

/* CMD_DESCR_START */
#define CONFIG_CMD_DESCR_START "Start tracing"

/* CMD_DESCR_STATUS */
#define CONFIG_CMD_DESCR_STATUS "Get the status of the current tracing session"

/* CMD_DESCR_STOP */
#define CONFIG_CMD_DESCR_STOP "Stop tracing"

/* CMD_DESCR_TRACK */
#define CONFIG_CMD_DESCR_TRACK "Track specific system resources"

/* CMD_DESCR_UNTRACK */
#define CONFIG_CMD_DESCR_UNTRACK "Untrack specific system resources"

/* CMD_DESCR_VERSION */
#define CONFIG_CMD_DESCR_VERSION "Show version information"

/* CMD_DESCR_VIEW */
#define CONFIG_CMD_DESCR_VIEW "Start trace viewer"

/* Location of the 32-bit consumerd executable. */
#define CONFIG_CONSUMERD32_BIN ""

/* Search for consumerd 32-bit libraries in this location. */
#define CONFIG_CONSUMERD32_LIBDIR ""

/* Location of the 64-bit consumerd executable */
#define CONFIG_CONSUMERD64_BIN ""

/* Search for consumerd 64-bit libraries in this location. */
#define CONFIG_CONSUMERD64_LIBDIR ""

/* DEFAULT_AGENT_BIND_ADDRESS */
#define CONFIG_DEFAULT_AGENT_BIND_ADDRESS "localhost"

/* DEFAULT_AGENT_TCP_PORT */
#define CONFIG_DEFAULT_AGENT_TCP_PORT 5345

/* DEFAULT_APP_SOCKET_RW_TIMEOUT */
#define CONFIG_DEFAULT_APP_SOCKET_RW_TIMEOUT 5

/* DEFAULT_CHANNEL_SUBBUF_SIZE */
#define CONFIG_DEFAULT_CHANNEL_SUBBUF_SIZE 16384

/* DEFAULT_CHANNEL_TRACEFILE_COUNT */
#define CONFIG_DEFAULT_CHANNEL_TRACEFILE_COUNT 0

/* DEFAULT_CHANNEL_TRACEFILE_SIZE */
#define CONFIG_DEFAULT_CHANNEL_TRACEFILE_SIZE 0

/* DEFAULT_KERNEL_CHANNEL_BLOCKING_TIMEOUT */
#define CONFIG_DEFAULT_KERNEL_CHANNEL_BLOCKING_TIMEOUT 0

/* DEFAULT_KERNEL_CHANNEL_LIVE_TIMER */
#define CONFIG_DEFAULT_KERNEL_CHANNEL_LIVE_TIMER 0

/* DEFAULT_KERNEL_CHANNEL_MONITOR_TIMER */
#define CONFIG_DEFAULT_KERNEL_CHANNEL_MONITOR_TIMER 1000000

/* DEFAULT_KERNEL_CHANNEL_READ_TIMER */
#define CONFIG_DEFAULT_KERNEL_CHANNEL_READ_TIMER 200000

/* DEFAULT_KERNEL_CHANNEL_SUBBUF_NUM */
#define CONFIG_DEFAULT_KERNEL_CHANNEL_SUBBUF_NUM 4

/* DEFAULT_KERNEL_CHANNEL_SUBBUF_SIZE */
#define CONFIG_DEFAULT_KERNEL_CHANNEL_SUBBUF_SIZE 1048576

/* DEFAULT_KERNEL_CHANNEL_SWITCH_TIMER */
#define CONFIG_DEFAULT_KERNEL_CHANNEL_SWITCH_TIMER 0

/* DEFAULT_LTTNG_LIVE_TIMER */
#define CONFIG_DEFAULT_LTTNG_LIVE_TIMER 1000000

/* DEFAULT_METADATA_CACHE_SIZE */
#define CONFIG_DEFAULT_METADATA_CACHE_SIZE 4096

/* DEFAULT_METADATA_READ_TIMER */
#define CONFIG_DEFAULT_METADATA_READ_TIMER 0

/* DEFAULT_METADATA_SUBBUF_NUM */
#define CONFIG_DEFAULT_METADATA_SUBBUF_NUM 2

/* DEFAULT_METADATA_SUBBUF_SIZE */
#define CONFIG_DEFAULT_METADATA_SUBBUF_SIZE 4096

/* DEFAULT_METADATA_SWITCH_TIMER */
#define CONFIG_DEFAULT_METADATA_SWITCH_TIMER 0

/* DEFAULT_NETWORK_CONTROL_BIND_ADDRESS */
#define CONFIG_DEFAULT_NETWORK_CONTROL_BIND_ADDRESS "0.0.0.0"

/* DEFAULT_NETWORK_CONTROL_PORT */
#define CONFIG_DEFAULT_NETWORK_CONTROL_PORT 5342

/* DEFAULT_NETWORK_DATA_BIND_ADDRESS */
#define CONFIG_DEFAULT_NETWORK_DATA_BIND_ADDRESS "0.0.0.0"

/* DEFAULT_NETWORK_DATA_PORT */
#define CONFIG_DEFAULT_NETWORK_DATA_PORT 5343

/* DEFAULT_NETWORK_VIEWER_BIND_ADDRESS */
#define CONFIG_DEFAULT_NETWORK_VIEWER_BIND_ADDRESS "localhost"

/* DEFAULT_NETWORK_VIEWER_PORT */
#define CONFIG_DEFAULT_NETWORK_VIEWER_PORT 5344

/* DEFAULT_UST_PID_CHANNEL_BLOCKING_TIMEOUT */
#define CONFIG_DEFAULT_UST_PID_CHANNEL_BLOCKING_TIMEOUT 0

/* DEFAULT_UST_PID_CHANNEL_LIVE_TIMER */
#define CONFIG_DEFAULT_UST_PID_CHANNEL_LIVE_TIMER 0

/* DEFAULT_UST_PID_CHANNEL_MONITOR_TIMER */
#define CONFIG_DEFAULT_UST_PID_CHANNEL_MONITOR_TIMER 1000000

/* DEFAULT_UST_PID_CHANNEL_READ_TIMER */
#define CONFIG_DEFAULT_UST_PID_CHANNEL_READ_TIMER 0

/* DEFAULT_UST_PID_CHANNEL_SUBBUF_NUM */
#define CONFIG_DEFAULT_UST_PID_CHANNEL_SUBBUF_NUM 4

/* DEFAULT_UST_PID_CHANNEL_SUBBUF_SIZE */
#define CONFIG_DEFAULT_UST_PID_CHANNEL_SUBBUF_SIZE 16384

/* DEFAULT_UST_PID_CHANNEL_SWITCH_TIMER */
#define CONFIG_DEFAULT_UST_PID_CHANNEL_SWITCH_TIMER 0

/* DEFAULT_UST_UID_CHANNEL_BLOCKING_TIMEOUT */
#define CONFIG_DEFAULT_UST_UID_CHANNEL_BLOCKING_TIMEOUT 0

/* DEFAULT_UST_UID_CHANNEL_LIVE_TIMER */
#define CONFIG_DEFAULT_UST_UID_CHANNEL_LIVE_TIMER 0

/* DEFAULT_UST_UID_CHANNEL_MONITOR_TIMER */
#define CONFIG_DEFAULT_UST_UID_CHANNEL_MONITOR_TIMER 1000000

/* DEFAULT_UST_UID_CHANNEL_READ_TIMER */
#define CONFIG_DEFAULT_UST_UID_CHANNEL_READ_TIMER 0

/* DEFAULT_UST_UID_CHANNEL_SUBBUF_NUM */
#define CONFIG_DEFAULT_UST_UID_CHANNEL_SUBBUF_NUM 4

/* DEFAULT_UST_UID_CHANNEL_SUBBUF_SIZE */
#define CONFIG_DEFAULT_UST_UID_CHANNEL_SUBBUF_SIZE 524288

/* DEFAULT_UST_UID_CHANNEL_SWITCH_TIMER */
#define CONFIG_DEFAULT_UST_UID_CHANNEL_SWITCH_TIMER 0

/* LTTng system configuration directory. */
#define CONFIG_LTTNG_SYSTEM_CONFIGDIR "/etc"

/* LTTng system data directory. */
#define CONFIG_LTTNG_SYSTEM_DATADIR "/usr/share"

/* LTTng system runtime directory */
#define CONFIG_LTTNG_SYSTEM_RUNDIR "/var/run/lttng"

/* Location of the lttv GUI viewer executable. */
#define CONFIG_LTTV_GUI_BIN ""

/* Location of the sessiond executable. */
#define CONFIG_SESSIOND_BIN ""

/* Define to 1 if you have the <arpa/inet.h> header file. */
#define HAVE_ARPA_INET_H 1

/* Define to 1 if you have the `atexit' function. */
#define HAVE_ATEXIT 1

/* Define to 1 if you have the `bzero' function. */
#define HAVE_BZERO 1

/* Define to 1 if you have the `clock_gettime' function. */
#define HAVE_CLOCK_GETTIME 1

/* Define to 1 if you have the `dirfd' function. */
#define HAVE_DIRFD 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* "Define to 1 if dlmopen is available." */
/* #undef HAVE_DLMOPEN */

/* Define to 1 if you have the `dup2' function. */
#define HAVE_DUP2 1

/* This platform supports epoll(7). */
#define HAVE_EPOLL 1

/* Define to 1 if you have the `epoll_create1' function. */
#define HAVE_EPOLL_CREATE1 1

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the `fdatasync' function. */
#define HAVE_FDATASYNC 1

/* Define to 1 if you have the `fls' function. */
/* #undef HAVE_FLS */

/* Define to 1 if you have the `ftruncate' function. */
#define HAVE_FTRUNCATE 1

/* Define to 1 if you have the `gethostbyname' function. */
#define HAVE_GETHOSTBYNAME 1

/* Define to 1 if you have the `gethostbyname2' function. */
#define HAVE_GETHOSTBYNAME2 1

/* Define to 1 if you have the `gethostname' function. */
#define HAVE_GETHOSTNAME 1

/* Define to 1 if you have the `getipnodebyname' function. */
/* #undef HAVE_GETIPNODEBYNAME */

/* Define to 1 if you have the <getopt.h> header file. */
#define HAVE_GETOPT_H 1

/* Define to 1 if you have the `getpagesize' function. */
#define HAVE_GETPAGESIZE 1

/* Define to 1 if you have the <grp.h> header file. */
#define HAVE_GRP_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define if you have kmod support */
/* #undef HAVE_KMOD */

/* Define if you have LTTng-UST control support */
/* #undef HAVE_LIBLTTNG_UST_CTL */

/* Define to 1 if you have the `rt' library (-lrt). */
#define HAVE_LIBRT 1

/* Define to 1 if you have the `urcu-cds' library (-lurcu-cds). */
#define HAVE_LIBURCU_CDS 1

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if you have the `localtime_r' function. */
#define HAVE_LOCALTIME_R 1

/* Define to 1 if you have the `memchr' function. */
#define HAVE_MEMCHR 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `memset' function. */
#define HAVE_MEMSET 1

/* Define to 1 if you have the `mkdir' function. */
#define HAVE_MKDIR 1

/* Define to 1 if you have the `munmap' function. */
#define HAVE_MUNMAP 1

/* Define to 1 if you have the <netdb.h> header file. */
#define HAVE_NETDB_H 1

/* Define to 1 if you have the <netinet/in.h> header file. */
#define HAVE_NETINET_IN_H 1

/* Define to 1 if you have the <paths.h> header file. */
#define HAVE_PATHS_H 1

/* Define to 1 if you have the <popt.h> header file. */
#define HAVE_POPT_H 1

/* Define if you have POSIX threads libraries and header files. */
#define HAVE_PTHREAD 1

/* Define to 1 if you have the <pthread.h> header file. */
#define HAVE_PTHREAD_H 1

/* Have PTHREAD_PRIO_INHERIT. */
#define HAVE_PTHREAD_PRIO_INHERIT 1

/* Define to 1 if you have the `putenv' function. */
#define HAVE_PUTENV 1

/* Define to 1 if you have the `realpath' function. */
#define HAVE_REALPATH 1

/* Define to 1 if you have the `rmdir' function. */
#define HAVE_RMDIR 1

/* Define to 1 if you have the `sched_getcpu' function. */
#define HAVE_SCHED_GETCPU 1

/* Define to 1 if you have the <signal.h> header file. */
#define HAVE_SIGNAL_H 1

/* Define to 1 if you have the `socket' function. */
#define HAVE_SOCKET 1

/* Define to 1 if you have the <stddef.h> header file. */
#define HAVE_STDDEF_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdio.h> header file. */
#define HAVE_STDIO_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strchr' function. */
#define HAVE_STRCHR 1

/* Define to 1 if you have the `strcspn' function. */
#define HAVE_STRCSPN 1

/* Define to 1 if you have the `strdup' function. */
#define HAVE_STRDUP 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strncasecmp' function. */
#define HAVE_STRNCASECMP 1

/* Define to 1 if you have the `strndup' function. */
#define HAVE_STRNDUP 1

/* Define to 1 if you have the `strnlen' function. */
#define HAVE_STRNLEN 1

/* Define to 1 if you have the `strpbrk' function. */
#define HAVE_STRPBRK 1

/* Define to 1 if you have the `strrchr' function. */
#define HAVE_STRRCHR 1

/* Define to 1 if you have the `strstr' function. */
#define HAVE_STRSTR 1

/* Define to 1 if you have the `strtol' function. */
#define HAVE_STRTOL 1

/* Define to 1 if you have the `strtoul' function. */
#define HAVE_STRTOUL 1

/* Define to 1 if you have the `strtoull' function. */
#define HAVE_STRTOULL 1

/* Define to 1 if you have the `sync_file_range' function. */
#define HAVE_SYNC_FILE_RANGE 1

/* Define to 1 if you have the `sysconf' function. */
#define HAVE_SYSCONF 1

/* Define to 1 if you have the <sys/file.h> header file. */
#define HAVE_SYS_FILE_H 1

/* Define to 1 if you have the <sys/ioctl.h> header file. */
#define HAVE_SYS_IOCTL_H 1

/* Define to 1 if you have the <sys/ipc.h> header file. */
#define HAVE_SYS_IPC_H 1

/* Define to 1 if you have the <sys/mount.h> header file. */
#define HAVE_SYS_MOUNT_H 1

/* Define to 1 if you have the <sys/param.h> header file. */
#define HAVE_SYS_PARAM_H 1

/* Define to 1 if you have the <sys/shm.h> header file. */
#define HAVE_SYS_SHM_H 1

/* Define to 1 if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/un.h> header file. */
#define HAVE_SYS_UN_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `uuid_generate' function. */
/* #undef HAVE_UUID_GENERATE */

/* define if your compiler has __attribute__ */
#define HAVE___ATTRIBUTE__ 1

/* Embed --help messages. */
/* #undef LTTNG_EMBED_HELP */

/* Has clock_gettime() support. */
#define LTTNG_HAVE_CLOCK_GETTIME 1

/* Has fmemopen support. */
#define LTTNG_HAVE_FMEMOPEN 1

/* Define if you have libuuid support */
#define LTTNG_HAVE_LIBUUID 1

/* Has open_memstream support. */
#define LTTNG_HAVE_OPEN_MEMSTREAM 1

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#define LT_OBJDIR ".libs/"

/* Path to man pages. */
#define MANPATH "/usr/share/man"

/* Name of package */
#define PACKAGE "lttng-tools"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "jeremie.galarneau@efficios.com"

/* Define to the full name of this package. */
#define PACKAGE_NAME "lttng-tools"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "lttng-tools 2.10.1"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "lttng-tools"

/* Define to the home page for this package. */
#define PACKAGE_URL "https://lttng.org"

/* Define to the version of this package. */
#define PACKAGE_VERSION "2.10.1"

/* Define to necessary symbol if this constant uses a non-standard name on
   your system. */
/* #undef PTHREAD_CREATE_JOINABLE */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Version number of package */
#define VERSION "2.10.1"

/* "" */
#define VERSION_DESCRIPTION "From Brasserie Dunham, a sour mashed golden wheat ale fermented with local sour cherries from Tougas orchards. Fresh sweet cherry notes with some tartness, lively carbonation with a dry finish."

/* LTTng-Tools major version number */
#define VERSION_MAJOR 2

/* LTTng-Tools minor version number */
#define VERSION_MINOR 10

/* "" */
#define VERSION_NAME "KeKriek"

/* LTTng-Tools patchlevel version number */
#define VERSION_PATCHLEVEL 1

/* Define to 1 if `lex' declares `yytext' as a `char *' by default, not a
   `char[]'. */
/* #undef YYTEXT_POINTER */

/* Enable large inode numbers on Mac OS X 10.5.  */
#ifndef _DARWIN_USE_64_BIT_INODE
# define _DARWIN_USE_64_BIT_INODE 1
#endif

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Define for Solaris 2.5.1 so the uint32_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT32_T */

/* Define for Solaris 2.5.1 so the uint64_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT64_T */

/* Define for Solaris 2.5.1 so the uint8_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT8_T */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef gid_t */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* Define to the type of a signed integer type of width exactly 32 bits if
   such a type exists and the standard includes do not define it. */
/* #undef int32_t */

/* Define to the type of a signed integer type of width exactly 64 bits if
   such a type exists and the standard includes do not define it. */
/* #undef int64_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef mode_t */

/* Define to `long int' if <sys/types.h> does not define. */
/* #undef off_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef pid_t */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef ssize_t */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef uid_t */

/* Define to the type of an unsigned integer type of width exactly 16 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint16_t */

/* Define to the type of an unsigned integer type of width exactly 32 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint32_t */

/* Define to the type of an unsigned integer type of width exactly 64 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint64_t */

/* Define to the type of an unsigned integer type of width exactly 8 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint8_t */
