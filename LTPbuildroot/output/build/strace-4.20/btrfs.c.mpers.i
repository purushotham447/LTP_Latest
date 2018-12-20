typedef signed char int8_t;
typedef short int int16_t;
typedef int int32_t;
__extension__
typedef long long int int64_t;
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
__extension__
typedef unsigned long long int uint64_t;
typedef signed char int_least8_t;
typedef short int int_least16_t;
typedef int int_least32_t;
__extension__
typedef long long int int_least64_t;
typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;
__extension__
typedef unsigned long long int uint_least64_t;
typedef signed char int_fast8_t;
typedef int int_fast16_t;
typedef int int_fast32_t;
__extension__
typedef long long int int_fast64_t;
typedef unsigned char uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
__extension__
typedef unsigned long long int uint_fast64_t;
typedef int intptr_t;
typedef unsigned int uintptr_t;
__extension__
typedef long long int intmax_t;
__extension__
typedef unsigned long long int uintmax_t;

typedef struct
  {
    long long int quot;
    long long int rem;
  } imaxdiv_t;
extern intmax_t imaxabs (intmax_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern imaxdiv_t imaxdiv (intmax_t __numer, intmax_t __denom)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern intmax_t strtoimax (const char *__restrict __nptr,
      char **__restrict __endptr, int __base) __attribute__ ((__nothrow__ , __leaf__));
extern uintmax_t strtoumax (const char *__restrict __nptr,
       char ** __restrict __endptr, int __base) __attribute__ ((__nothrow__ , __leaf__));


typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
__extension__ typedef signed long long int __int64_t;
__extension__ typedef unsigned long long int __uint64_t;
__extension__ typedef long long int __quad_t;
__extension__ typedef unsigned long long int __u_quad_t;
__extension__ typedef __u_quad_t __dev_t;
__extension__ typedef unsigned int __uid_t;
__extension__ typedef unsigned int __gid_t;
__extension__ typedef unsigned long int __ino_t;
__extension__ typedef __u_quad_t __ino64_t;
__extension__ typedef unsigned int __mode_t;
__extension__ typedef unsigned int __nlink_t;
__extension__ typedef long int __off_t;
__extension__ typedef __quad_t __off64_t;
__extension__ typedef int __pid_t;
__extension__ typedef struct { int __val[2]; } __fsid_t;
__extension__ typedef long int __clock_t;
__extension__ typedef unsigned long int __rlim_t;
__extension__ typedef __u_quad_t __rlim64_t;
__extension__ typedef unsigned int __id_t;
__extension__ typedef long int __time_t;
__extension__ typedef unsigned int __useconds_t;
__extension__ typedef long int __suseconds_t;
__extension__ typedef int __daddr_t;
__extension__ typedef long int __swblk_t;
__extension__ typedef int __key_t;
__extension__ typedef int __clockid_t;
__extension__ typedef void * __timer_t;
__extension__ typedef long int __blksize_t;
__extension__ typedef long int __blkcnt_t;
__extension__ typedef __quad_t __blkcnt64_t;
__extension__ typedef unsigned long int __fsblkcnt_t;
__extension__ typedef __u_quad_t __fsblkcnt64_t;
__extension__ typedef unsigned long int __fsfilcnt_t;
__extension__ typedef __u_quad_t __fsfilcnt64_t;
__extension__ typedef int __ssize_t;
typedef __off64_t __loff_t;
typedef __quad_t *__qaddr_t;
typedef char *__caddr_t;
typedef long int __t_scalar_t;
typedef unsigned long int __t_uscalar_t;
__extension__ typedef int __intptr_t;
__extension__ typedef unsigned int __socklen_t;
typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;
typedef __loff_t loff_t;
typedef __ino64_t ino_t;
typedef __ino64_t ino64_t;
typedef __dev_t dev_t;
typedef __gid_t gid_t;
typedef __mode_t mode_t;
typedef __nlink_t nlink_t;
typedef __uid_t uid_t;
typedef __off64_t off_t;
typedef __off64_t off64_t;
typedef __pid_t pid_t;
typedef __id_t id_t;
typedef __ssize_t ssize_t;
typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;
typedef __key_t key_t;

typedef __clock_t clock_t;



typedef __time_t time_t;


typedef __clockid_t clockid_t;
typedef __timer_t timer_t;
typedef __useconds_t useconds_t;
typedef __suseconds_t suseconds_t;
typedef unsigned int size_t;
typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
typedef unsigned int u_int8_t __attribute__ ((__mode__ (__QI__)));
typedef unsigned int u_int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int u_int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int u_int64_t __attribute__ ((__mode__ (__DI__)));
typedef int register_t __attribute__ ((__mode__ (__word__)));
static __inline unsigned int
__bswap_32 (unsigned int __bsx)
{
  return __builtin_bswap32 (__bsx);
}
static __inline __uint64_t
__bswap_64 (__uint64_t __bsx)
{
  return __builtin_bswap64 (__bsx);
}
typedef int __sig_atomic_t;
typedef struct {
 unsigned long __val[(64 / (8 * sizeof (unsigned long)))];
} __sigset_t;
typedef __sigset_t sigset_t;
struct timespec
  {
    __time_t tv_sec;
    long int tv_nsec;
  };
struct timeval
  {
    __time_t tv_sec;
    __suseconds_t tv_usec;
  };
typedef long int __fd_mask;
typedef struct
  {
    __fd_mask fds_bits[1024 / (8 * sizeof (__fd_mask))];
  } fd_set;
typedef __fd_mask fd_mask;

extern int select (int __nfds, fd_set *__restrict __readfds,
     fd_set *__restrict __writefds,
     fd_set *__restrict __exceptfds,
     struct timeval *__restrict __timeout);
extern int pselect (int __nfds, fd_set *__restrict __readfds,
      fd_set *__restrict __writefds,
      fd_set *__restrict __exceptfds,
      const struct timespec *__restrict __timeout,
      const __sigset_t *__restrict __sigmask);


__extension__
extern unsigned int gnu_dev_major (unsigned long long int __dev)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__
extern unsigned int gnu_dev_minor (unsigned long long int __dev)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__
extern unsigned long long int gnu_dev_makedev (unsigned int __major,
       unsigned int __minor)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));

typedef __blksize_t blksize_t;
typedef __blkcnt64_t blkcnt_t;
typedef __fsblkcnt64_t fsblkcnt_t;
typedef __fsfilcnt64_t fsfilcnt_t;
typedef __blkcnt64_t blkcnt64_t;
typedef __fsblkcnt64_t fsblkcnt64_t;
typedef __fsfilcnt64_t fsfilcnt64_t;
typedef unsigned long int pthread_t;
typedef union
{
  char __size[36];
  long int __align;
} pthread_attr_t;
typedef struct __pthread_internal_slist
{
  struct __pthread_internal_slist *__next;
} __pthread_slist_t;
typedef union
{
  struct __pthread_mutex_s
  {
    int __lock;
    unsigned int __count;
    int __owner;
    int __kind;
    unsigned int __nusers;
    __extension__ union
    {
      int __spins;
      __pthread_slist_t __list;
    };
  } __data;
  char __size[24];
  long int __align;
} pthread_mutex_t;
typedef union
{
  char __size[4];
  long int __align;
} pthread_mutexattr_t;
typedef union
{
  struct
  {
    int __lock;
    unsigned int __futex;
    __extension__ unsigned long long int __total_seq;
    __extension__ unsigned long long int __wakeup_seq;
    __extension__ unsigned long long int __woken_seq;
    void *__mutex;
    unsigned int __nwaiters;
    unsigned int __broadcast_seq;
  } __data;
  char __size[48];
  __extension__ long long int __align;
} pthread_cond_t;
typedef union
{
  char __size[4];
  long int __align;
} pthread_condattr_t;
typedef unsigned int pthread_key_t;
typedef int pthread_once_t;
typedef union
{
  struct
  {
    int __lock;
    unsigned int __nr_readers;
    unsigned int __readers_wakeup;
    unsigned int __writer_wakeup;
    unsigned int __nr_readers_queued;
    unsigned int __nr_writers_queued;
    unsigned char __flags;
    unsigned char __shared;
    unsigned char __pad1;
    unsigned char __pad2;
    int __writer;
  } __data;
  char __size[32];
  long int __align;
} pthread_rwlock_t;
typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;
typedef volatile int pthread_spinlock_t;
typedef union
{
  char __size[20];
  long int __align;
} pthread_barrier_t;
typedef union
{
  char __size[4];
  int __align;
} pthread_barrierattr_t;

typedef int ptrdiff_t;
typedef unsigned int wchar_t;
typedef struct {
  long long __max_align_ll __attribute__((__aligned__(__alignof__(long long))));
  long double __max_align_ld __attribute__((__aligned__(__alignof__(long double))));
} max_align_t;

typedef __socklen_t socklen_t;
extern int access (const char *__name, int __type) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int euidaccess (const char *__name, int __type)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int eaccess (const char *__name, int __type)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int faccessat (int __fd, const char *__file, int __type, int __flag)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) ;
extern __off64_t lseek (int __fd, __off64_t __offset, int __whence) __asm__ ("" "lseek64") __attribute__ ((__nothrow__ , __leaf__));
extern __off64_t lseek64 (int __fd, __off64_t __offset, int __whence)
     __attribute__ ((__nothrow__ , __leaf__));
extern int close (int __fd);
extern ssize_t read (int __fd, void *__buf, size_t __nbytes) ;
extern ssize_t write (int __fd, const void *__buf, size_t __n) ;
extern ssize_t pread (int __fd, void *__buf, size_t __nbytes, __off64_t __offset) __asm__ ("" "pread64") ;
extern ssize_t pwrite (int __fd, const void *__buf, size_t __nbytes, __off64_t __offset) __asm__ ("" "pwrite64") ;
extern ssize_t pread64 (int __fd, void *__buf, size_t __nbytes,
   __off64_t __offset) ;
extern ssize_t pwrite64 (int __fd, const void *__buf, size_t __n,
    __off64_t __offset) ;
extern int pipe (int __pipedes[2]) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int pipe2 (int __pipedes[2], int __flags) __attribute__ ((__nothrow__ , __leaf__)) ;
extern unsigned int alarm (unsigned int __seconds) __attribute__ ((__nothrow__ , __leaf__));
extern unsigned int sleep (unsigned int __seconds);
extern __useconds_t ualarm (__useconds_t __value, __useconds_t __interval)
     __attribute__ ((__nothrow__ , __leaf__));
extern int usleep (__useconds_t __useconds);
extern int pause (void);
extern int chown (const char *__file, __uid_t __owner, __gid_t __group)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int fchown (int __fd, __uid_t __owner, __gid_t __group) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int lchown (const char *__file, __uid_t __owner, __gid_t __group)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int fchownat (int __fd, const char *__file, __uid_t __owner,
       __gid_t __group, int __flag)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) ;
extern int chdir (const char *__path) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int fchdir (int __fd) __attribute__ ((__nothrow__ , __leaf__)) ;
extern char *getcwd (char *__buf, size_t __size) __attribute__ ((__nothrow__ , __leaf__)) ;
extern char *get_current_dir_name (void) __attribute__ ((__nothrow__ , __leaf__));
extern int dup (int __fd) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int dup2 (int __fd, int __fd2) __attribute__ ((__nothrow__ , __leaf__));
extern int dup3 (int __fd, int __fd2, int __flags) __attribute__ ((__nothrow__ , __leaf__));
extern char **__environ;
extern char **environ;
extern int execve (const char *__path, char *const __argv[],
     char *const __envp[]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int execv (const char *__path, char *const __argv[])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int execle (const char *__path, const char *__arg, ...)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int execl (const char *__path, const char *__arg, ...)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int execvp (const char *__file, char *const __argv[])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int execlp (const char *__file, const char *__arg, ...)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int execvpe (const char *__file, char *const __argv[],
  char *const __envp[])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int nice (int __inc) __attribute__ ((__nothrow__ , __leaf__)) ;
extern void _exit (int __status) __attribute__ ((__noreturn__));
enum
  {
    _PC_LINK_MAX,
    _PC_MAX_CANON,
    _PC_MAX_INPUT,
    _PC_NAME_MAX,
    _PC_PATH_MAX,
    _PC_PIPE_BUF,
    _PC_CHOWN_RESTRICTED,
    _PC_NO_TRUNC,
    _PC_VDISABLE,
    _PC_SYNC_IO,
    _PC_ASYNC_IO,
    _PC_PRIO_IO,
    _PC_SOCK_MAXBUF,
    _PC_FILESIZEBITS,
    _PC_REC_INCR_XFER_SIZE,
    _PC_REC_MAX_XFER_SIZE,
    _PC_REC_MIN_XFER_SIZE,
    _PC_REC_XFER_ALIGN,
    _PC_ALLOC_SIZE_MIN,
    _PC_SYMLINK_MAX,
    _PC_2_SYMLINKS
  };
enum
  {
    _SC_ARG_MAX,
    _SC_CHILD_MAX,
    _SC_CLK_TCK,
    _SC_NGROUPS_MAX,
    _SC_OPEN_MAX,
    _SC_STREAM_MAX,
    _SC_TZNAME_MAX,
    _SC_JOB_CONTROL,
    _SC_SAVED_IDS,
    _SC_REALTIME_SIGNALS,
    _SC_PRIORITY_SCHEDULING,
    _SC_TIMERS,
    _SC_ASYNCHRONOUS_IO,
    _SC_PRIORITIZED_IO,
    _SC_SYNCHRONIZED_IO,
    _SC_FSYNC,
    _SC_MAPPED_FILES,
    _SC_MEMLOCK,
    _SC_MEMLOCK_RANGE,
    _SC_MEMORY_PROTECTION,
    _SC_MESSAGE_PASSING,
    _SC_SEMAPHORES,
    _SC_SHARED_MEMORY_OBJECTS,
    _SC_AIO_LISTIO_MAX,
    _SC_AIO_MAX,
    _SC_AIO_PRIO_DELTA_MAX,
    _SC_DELAYTIMER_MAX,
    _SC_MQ_OPEN_MAX,
    _SC_MQ_PRIO_MAX,
    _SC_VERSION,
    _SC_PAGESIZE,
    _SC_RTSIG_MAX,
    _SC_SEM_NSEMS_MAX,
    _SC_SEM_VALUE_MAX,
    _SC_SIGQUEUE_MAX,
    _SC_TIMER_MAX,
    _SC_BC_BASE_MAX,
    _SC_BC_DIM_MAX,
    _SC_BC_SCALE_MAX,
    _SC_BC_STRING_MAX,
    _SC_COLL_WEIGHTS_MAX,
    _SC_EQUIV_CLASS_MAX,
    _SC_EXPR_NEST_MAX,
    _SC_LINE_MAX,
    _SC_RE_DUP_MAX,
    _SC_CHARCLASS_NAME_MAX,
    _SC_2_VERSION,
    _SC_2_C_BIND,
    _SC_2_C_DEV,
    _SC_2_FORT_DEV,
    _SC_2_FORT_RUN,
    _SC_2_SW_DEV,
    _SC_2_LOCALEDEF,
    _SC_PII,
    _SC_PII_XTI,
    _SC_PII_SOCKET,
    _SC_PII_INTERNET,
    _SC_PII_OSI,
    _SC_POLL,
    _SC_SELECT,
    _SC_UIO_MAXIOV,
    _SC_IOV_MAX = _SC_UIO_MAXIOV,
    _SC_PII_INTERNET_STREAM,
    _SC_PII_INTERNET_DGRAM,
    _SC_PII_OSI_COTS,
    _SC_PII_OSI_CLTS,
    _SC_PII_OSI_M,
    _SC_T_IOV_MAX,
    _SC_THREADS,
    _SC_THREAD_SAFE_FUNCTIONS,
    _SC_GETGR_R_SIZE_MAX,
    _SC_GETPW_R_SIZE_MAX,
    _SC_LOGIN_NAME_MAX,
    _SC_TTY_NAME_MAX,
    _SC_THREAD_DESTRUCTOR_ITERATIONS,
    _SC_THREAD_KEYS_MAX,
    _SC_THREAD_STACK_MIN,
    _SC_THREAD_THREADS_MAX,
    _SC_THREAD_ATTR_STACKADDR,
    _SC_THREAD_ATTR_STACKSIZE,
    _SC_THREAD_PRIORITY_SCHEDULING,
    _SC_THREAD_PRIO_INHERIT,
    _SC_THREAD_PRIO_PROTECT,
    _SC_THREAD_PROCESS_SHARED,
    _SC_NPROCESSORS_CONF,
    _SC_NPROCESSORS_ONLN,
    _SC_PHYS_PAGES,
    _SC_AVPHYS_PAGES,
    _SC_ATEXIT_MAX,
    _SC_PASS_MAX,
    _SC_XOPEN_VERSION,
    _SC_XOPEN_XCU_VERSION,
    _SC_XOPEN_UNIX,
    _SC_XOPEN_CRYPT,
    _SC_XOPEN_ENH_I18N,
    _SC_XOPEN_SHM,
    _SC_2_CHAR_TERM,
    _SC_2_C_VERSION,
    _SC_2_UPE,
    _SC_XOPEN_XPG2,
    _SC_XOPEN_XPG3,
    _SC_XOPEN_XPG4,
    _SC_CHAR_BIT,
    _SC_CHAR_MAX,
    _SC_CHAR_MIN,
    _SC_INT_MAX,
    _SC_INT_MIN,
    _SC_LONG_BIT,
    _SC_WORD_BIT,
    _SC_MB_LEN_MAX,
    _SC_NZERO,
    _SC_SSIZE_MAX,
    _SC_SCHAR_MAX,
    _SC_SCHAR_MIN,
    _SC_SHRT_MAX,
    _SC_SHRT_MIN,
    _SC_UCHAR_MAX,
    _SC_UINT_MAX,
    _SC_ULONG_MAX,
    _SC_USHRT_MAX,
    _SC_NL_ARGMAX,
    _SC_NL_LANGMAX,
    _SC_NL_MSGMAX,
    _SC_NL_NMAX,
    _SC_NL_SETMAX,
    _SC_NL_TEXTMAX,
    _SC_XBS5_ILP32_OFF32,
    _SC_XBS5_ILP32_OFFBIG,
    _SC_XBS5_LP64_OFF64,
    _SC_XBS5_LPBIG_OFFBIG,
    _SC_XOPEN_LEGACY,
    _SC_XOPEN_REALTIME,
    _SC_XOPEN_REALTIME_THREADS,
    _SC_ADVISORY_INFO,
    _SC_BARRIERS,
    _SC_BASE,
    _SC_C_LANG_SUPPORT,
    _SC_C_LANG_SUPPORT_R,
    _SC_CLOCK_SELECTION,
    _SC_CPUTIME,
    _SC_THREAD_CPUTIME,
    _SC_DEVICE_IO,
    _SC_DEVICE_SPECIFIC,
    _SC_DEVICE_SPECIFIC_R,
    _SC_FD_MGMT,
    _SC_FIFO,
    _SC_PIPE,
    _SC_FILE_ATTRIBUTES,
    _SC_FILE_LOCKING,
    _SC_FILE_SYSTEM,
    _SC_MONOTONIC_CLOCK,
    _SC_MULTI_PROCESS,
    _SC_SINGLE_PROCESS,
    _SC_NETWORKING,
    _SC_READER_WRITER_LOCKS,
    _SC_SPIN_LOCKS,
    _SC_REGEXP,
    _SC_REGEX_VERSION,
    _SC_SHELL,
    _SC_SIGNALS,
    _SC_SPAWN,
    _SC_SPORADIC_SERVER,
    _SC_THREAD_SPORADIC_SERVER,
    _SC_SYSTEM_DATABASE,
    _SC_SYSTEM_DATABASE_R,
    _SC_TIMEOUTS,
    _SC_TYPED_MEMORY_OBJECTS,
    _SC_USER_GROUPS,
    _SC_USER_GROUPS_R,
    _SC_2_PBS,
    _SC_2_PBS_ACCOUNTING,
    _SC_2_PBS_LOCATE,
    _SC_2_PBS_MESSAGE,
    _SC_2_PBS_TRACK,
    _SC_SYMLOOP_MAX,
    _SC_STREAMS,
    _SC_2_PBS_CHECKPOINT,
    _SC_V6_ILP32_OFF32,
    _SC_V6_ILP32_OFFBIG,
    _SC_V6_LP64_OFF64,
    _SC_V6_LPBIG_OFFBIG,
    _SC_HOST_NAME_MAX,
    _SC_TRACE,
    _SC_TRACE_EVENT_FILTER,
    _SC_TRACE_INHERIT,
    _SC_TRACE_LOG,
    _SC_LEVEL1_ICACHE_SIZE,
    _SC_LEVEL1_ICACHE_ASSOC,
    _SC_LEVEL1_ICACHE_LINESIZE,
    _SC_LEVEL1_DCACHE_SIZE,
    _SC_LEVEL1_DCACHE_ASSOC,
    _SC_LEVEL1_DCACHE_LINESIZE,
    _SC_LEVEL2_CACHE_SIZE,
    _SC_LEVEL2_CACHE_ASSOC,
    _SC_LEVEL2_CACHE_LINESIZE,
    _SC_LEVEL3_CACHE_SIZE,
    _SC_LEVEL3_CACHE_ASSOC,
    _SC_LEVEL3_CACHE_LINESIZE,
    _SC_LEVEL4_CACHE_SIZE,
    _SC_LEVEL4_CACHE_ASSOC,
    _SC_LEVEL4_CACHE_LINESIZE,
    _SC_IPV6 = _SC_LEVEL1_ICACHE_SIZE + 50,
    _SC_RAW_SOCKETS,
    _SC_V7_ILP32_OFF32,
    _SC_V7_ILP32_OFFBIG,
    _SC_V7_LP64_OFF64,
    _SC_V7_LPBIG_OFFBIG,
    _SC_SS_REPL_MAX,
    _SC_TRACE_EVENT_NAME_MAX,
    _SC_TRACE_NAME_MAX,
    _SC_TRACE_SYS_MAX,
    _SC_TRACE_USER_EVENT_MAX,
    _SC_XOPEN_STREAMS,
    _SC_THREAD_ROBUST_PRIO_INHERIT,
    _SC_THREAD_ROBUST_PRIO_PROTECT
  };
enum
  {
    _CS_PATH,
    _CS_V6_WIDTH_RESTRICTED_ENVS,
    _CS_GNU_LIBC_VERSION,
    _CS_GNU_LIBPTHREAD_VERSION,
    _CS_V5_WIDTH_RESTRICTED_ENVS,
    _CS_V7_WIDTH_RESTRICTED_ENVS,
    _CS_LFS_CFLAGS = 1000,
    _CS_LFS_LDFLAGS,
    _CS_LFS_LIBS,
    _CS_LFS_LINTFLAGS,
    _CS_LFS64_CFLAGS,
    _CS_LFS64_LDFLAGS,
    _CS_LFS64_LIBS,
    _CS_LFS64_LINTFLAGS,
    _CS_XBS5_ILP32_OFF32_CFLAGS = 1100,
    _CS_XBS5_ILP32_OFF32_LDFLAGS,
    _CS_XBS5_ILP32_OFF32_LIBS,
    _CS_XBS5_ILP32_OFF32_LINTFLAGS,
    _CS_XBS5_ILP32_OFFBIG_CFLAGS,
    _CS_XBS5_ILP32_OFFBIG_LDFLAGS,
    _CS_XBS5_ILP32_OFFBIG_LIBS,
    _CS_XBS5_ILP32_OFFBIG_LINTFLAGS,
    _CS_XBS5_LP64_OFF64_CFLAGS,
    _CS_XBS5_LP64_OFF64_LDFLAGS,
    _CS_XBS5_LP64_OFF64_LIBS,
    _CS_XBS5_LP64_OFF64_LINTFLAGS,
    _CS_XBS5_LPBIG_OFFBIG_CFLAGS,
    _CS_XBS5_LPBIG_OFFBIG_LDFLAGS,
    _CS_XBS5_LPBIG_OFFBIG_LIBS,
    _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS,
    _CS_POSIX_V6_ILP32_OFF32_CFLAGS,
    _CS_POSIX_V6_ILP32_OFF32_LDFLAGS,
    _CS_POSIX_V6_ILP32_OFF32_LIBS,
    _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS,
    _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS,
    _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS,
    _CS_POSIX_V6_ILP32_OFFBIG_LIBS,
    _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS,
    _CS_POSIX_V6_LP64_OFF64_CFLAGS,
    _CS_POSIX_V6_LP64_OFF64_LDFLAGS,
    _CS_POSIX_V6_LP64_OFF64_LIBS,
    _CS_POSIX_V6_LP64_OFF64_LINTFLAGS,
    _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS,
    _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS,
    _CS_POSIX_V6_LPBIG_OFFBIG_LIBS,
    _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS,
    _CS_POSIX_V7_ILP32_OFF32_CFLAGS,
    _CS_POSIX_V7_ILP32_OFF32_LDFLAGS,
    _CS_POSIX_V7_ILP32_OFF32_LIBS,
    _CS_POSIX_V7_ILP32_OFF32_LINTFLAGS,
    _CS_POSIX_V7_ILP32_OFFBIG_CFLAGS,
    _CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS,
    _CS_POSIX_V7_ILP32_OFFBIG_LIBS,
    _CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS,
    _CS_POSIX_V7_LP64_OFF64_CFLAGS,
    _CS_POSIX_V7_LP64_OFF64_LDFLAGS,
    _CS_POSIX_V7_LP64_OFF64_LIBS,
    _CS_POSIX_V7_LP64_OFF64_LINTFLAGS,
    _CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS,
    _CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS,
    _CS_POSIX_V7_LPBIG_OFFBIG_LIBS,
    _CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS
  };
extern long int pathconf (const char *__path, int __name)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern long int fpathconf (int __fd, int __name) __attribute__ ((__nothrow__ , __leaf__));
extern long int sysconf (int __name) __attribute__ ((__nothrow__ , __leaf__));
extern size_t confstr (int __name, char *__buf, size_t __len) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t getpid (void) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t getppid (void) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t getpgrp (void) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t __getpgid (__pid_t __pid) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t getpgid (__pid_t __pid) __attribute__ ((__nothrow__ , __leaf__));
extern int setpgid (__pid_t __pid, __pid_t __pgid) __attribute__ ((__nothrow__ , __leaf__));
extern int setpgrp (void) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t setsid (void) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t getsid (__pid_t __pid) __attribute__ ((__nothrow__ , __leaf__));
extern __uid_t getuid (void) __attribute__ ((__nothrow__ , __leaf__));
extern __uid_t geteuid (void) __attribute__ ((__nothrow__ , __leaf__));
extern __gid_t getgid (void) __attribute__ ((__nothrow__ , __leaf__));
extern __gid_t getegid (void) __attribute__ ((__nothrow__ , __leaf__));
extern int getgroups (int __size, __gid_t __list[]) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int setuid (__uid_t __uid) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int setreuid (__uid_t __ruid, __uid_t __euid) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int seteuid (__uid_t __uid) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int setgid (__gid_t __gid) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int setregid (__gid_t __rgid, __gid_t __egid) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int setegid (__gid_t __gid) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int getresuid (__uid_t *__ruid, __uid_t *__euid, __uid_t *__suid)
     __attribute__ ((__nothrow__ , __leaf__));
extern int getresgid (__gid_t *__rgid, __gid_t *__egid, __gid_t *__sgid)
     __attribute__ ((__nothrow__ , __leaf__));
extern int setresuid (__uid_t __ruid, __uid_t __euid, __uid_t __suid)
     __attribute__ ((__nothrow__ , __leaf__)) ;
extern int setresgid (__gid_t __rgid, __gid_t __egid, __gid_t __sgid)
     __attribute__ ((__nothrow__ , __leaf__)) ;
extern __pid_t fork (void) __attribute__ ((__nothrow__));
extern __pid_t vfork (void) __attribute__ ((__nothrow__ , __leaf__));
extern char *ttyname (int __fd) __attribute__ ((__nothrow__ , __leaf__));
extern int ttyname_r (int __fd, char *__buf, size_t __buflen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) ;
extern int isatty (int __fd) __attribute__ ((__nothrow__ , __leaf__));
extern int link (const char *__from, const char *__to)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) ;
extern int linkat (int __fromfd, const char *__from, int __tofd,
     const char *__to, int __flags)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4))) ;
extern int symlink (const char *__from, const char *__to)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) ;
extern ssize_t readlink (const char *__restrict __path,
    char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) ;
extern int symlinkat (const char *__from, int __tofd,
        const char *__to) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3))) ;
extern ssize_t readlinkat (int __fd, const char *__restrict __path,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3))) ;
extern int unlink (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int unlinkat (int __fd, const char *__name, int __flag)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int rmdir (const char *__path) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern __pid_t tcgetpgrp (int __fd) __attribute__ ((__nothrow__ , __leaf__));
extern int tcsetpgrp (int __fd, __pid_t __pgrp_id) __attribute__ ((__nothrow__ , __leaf__));
extern char *getlogin (void);
extern int getlogin_r (char *__name, size_t __name_len) __attribute__ ((__nonnull__ (1)));

extern char *optarg;
extern int optind;
extern int opterr;
extern int optopt;
extern int getopt (int ___argc, char *const *___argv, const char *__shortopts)
       __attribute__ ((__nothrow__ , __leaf__));

extern int gethostname (char *__name, size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int sethostname (const char *__name, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int sethostid (long int __id) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int getdomainname (char *__name, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int setdomainname (const char *__name, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int vhangup (void) __attribute__ ((__nothrow__ , __leaf__));
extern int acct (const char *__name) __attribute__ ((__nothrow__ , __leaf__));
extern char *getusershell (void) __attribute__ ((__nothrow__ , __leaf__));
extern void endusershell (void) __attribute__ ((__nothrow__ , __leaf__));
extern void setusershell (void) __attribute__ ((__nothrow__ , __leaf__));
extern int daemon (int __nochdir, int __noclose) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int chroot (const char *__path) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern char *getpass (const char *__prompt) __attribute__ ((__nonnull__ (1)));
extern int fsync (int __fd);
extern int syncfs (int __fd) __attribute__ ((__nothrow__ , __leaf__));
extern long int gethostid (void);
extern void sync (void) __attribute__ ((__nothrow__ , __leaf__));
extern int getpagesize (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int getdtablesize (void) __attribute__ ((__nothrow__ , __leaf__));
extern int truncate (const char *__file, __off64_t __length) __asm__ ("" "truncate64") __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int truncate64 (const char *__file, __off64_t __length)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int ftruncate (int __fd, __off64_t __length) __asm__ ("" "ftruncate64") __attribute__ ((__nothrow__ , __leaf__)) ;
extern int ftruncate64 (int __fd, __off64_t __length) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int brk (void *__addr) __attribute__ ((__nothrow__ , __leaf__)) ;
extern void *sbrk (intptr_t __delta) __attribute__ ((__nothrow__ , __leaf__));
extern long int syscall (long int __sysno, ...) __attribute__ ((__nothrow__ , __leaf__));
extern int _pe_secure;
extern int issetugid(void);
extern int lockf (int __fd, int __cmd, __off64_t __len) __asm__ ("" "lockf64") ;
extern int lockf64 (int __fd, int __cmd, __off64_t __len) ;
extern int fdatasync (int __fildes);
extern char *crypt (const char *__key, const char *__salt)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern void encrypt (char *__block, int __edflag) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void swab (const void *__restrict __from, void *__restrict __to,
    ssize_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


union wait
  {
    int w_status;
    struct
      {
 unsigned int __w_termsig:7;
 unsigned int __w_coredump:1;
 unsigned int __w_retcode:8;
 unsigned int:16;
      } __wait_terminated;
    struct
      {
 unsigned int __w_stopval:8;
 unsigned int __w_stopsig:8;
 unsigned int:16;
      } __wait_stopped;
  };
typedef union
  {
    union wait *__uptr;
    int *__iptr;
  } __WAIT_STATUS __attribute__ ((__transparent_union__));

typedef struct
  {
    int quot;
    int rem;
  } div_t;
typedef struct
  {
    long int quot;
    long int rem;
  } ldiv_t;


__extension__ typedef struct
  {
    long long int quot;
    long long int rem;
  } lldiv_t;


extern double atof (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;
extern int atoi (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;
extern long int atol (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;


__extension__ extern long long int atoll (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;


extern double strtod (const char *__restrict __nptr,
        char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;


extern float strtof (const char *__restrict __nptr,
       char **__restrict __endptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern long double strtold (const char *__restrict __nptr,
       char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;


extern long int strtol (const char *__restrict __nptr,
   char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern unsigned long int strtoul (const char *__restrict __nptr,
      char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;

__extension__
extern quad_t strtoq (const char *__restrict __nptr,
        char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
__extension__
extern u_quad_t strtouq (const char *__restrict __nptr,
           char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;

__extension__
extern long long int strtoll (const char *__restrict __nptr,
         char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
__extension__
extern unsigned long long int strtoull (const char *__restrict __nptr,
     char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;

extern char *l64a (long int __n) __attribute__ ((__nothrow__ , __leaf__)) ;
extern long int a64l (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;
extern long int random (void) __attribute__ ((__nothrow__ , __leaf__));
extern void srandom (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));
extern char *initstate (unsigned int __seed, char *__statebuf,
   size_t __statelen) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern char *setstate (char *__statebuf) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
struct random_data
  {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int8_t rand_type;
    int8_t rand_deg;
    int8_t rand_sep;
    int32_t *end_ptr;
  };
extern int random_r (struct random_data *__restrict __buf,
       int32_t *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int srandom_r (unsigned int __seed, struct random_data *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int initstate_r (unsigned int __seed, char *__restrict __statebuf,
   size_t __statelen,
   struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)));
extern int setstate_r (char *__restrict __statebuf,
         struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern int rand (void) __attribute__ ((__nothrow__ , __leaf__));
extern void srand (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));

extern int rand_r (unsigned int *__seed) __attribute__ ((__nothrow__ , __leaf__));
extern double drand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern double erand48 (unsigned short int __xsubi[3]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern long int lrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int nrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern long int mrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int jrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void srand48 (long int __seedval) __attribute__ ((__nothrow__ , __leaf__));
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void lcong48 (unsigned short int __param[7]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
struct drand48_data
  {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
    unsigned long long int __a;
  };
extern int drand48_r (struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int erand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int lrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int nrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int mrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int jrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int seed48_r (unsigned short int __seed16v[3],
       struct drand48_data *__buffer) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int lcong48_r (unsigned short int __param[7],
        struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern void *malloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;
extern void *calloc (size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;


extern void *realloc (void *__ptr, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) ;
extern void free (void *__ptr) __attribute__ ((__nothrow__ , __leaf__));


extern void *alloca (size_t __size) __attribute__ ((__nothrow__ , __leaf__));

extern void *valloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;
extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern void *aligned_alloc (size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__alloc_size__ (2))) ;

extern void abort (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));
extern int atexit (void (*__func) (void)) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern void exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));


extern void _Exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));


extern char *getenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;

extern char *secure_getenv (const char *__name)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int putenv (char *__string) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int setenv (const char *__name, const char *__value, int __replace)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int unsetenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__));
extern int clearenv (void) __attribute__ ((__nothrow__ , __leaf__));
extern char *mktemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int mkstemp (char *__template) __asm__ ("" "mkstemp64")
     __attribute__ ((__nonnull__ (1))) ;
extern int mkstemp64 (char *__template) __attribute__ ((__nonnull__ (1))) ;
extern char *mktemps (char *__template, int __suffixlen) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int mkstemps (char *__template, int __suffixlen) __asm__ ("" "mkstemps64")
     __attribute__ ((__nonnull__ (1))) ;
extern int mkstemps64 (char *__template, int __suffixlen) __attribute__ ((__nonnull__ (1))) ;
extern char *mkdtemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int mkostemp (char *__template, int __flags) __asm__ ("" "mkostemp64")
     __attribute__ ((__nonnull__ (1))) ;
extern int mkostemp64 (char *__template, int __flags) __attribute__ ((__nonnull__ (1))) ;
extern int mkostemps (char *__template, int __suffixlen, int __flags) __asm__ ("" "mkostemps64")
     __attribute__ ((__nonnull__ (1))) ;
extern int mkostemps64 (char *__template, int __suffixlen, int __flags) __attribute__ ((__nonnull__ (1))) ;

extern int system (const char *__command) ;

extern char *canonicalize_file_name (const char *__name)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern char *realpath (const char *__restrict __name,
         char *__restrict __resolved) __attribute__ ((__nothrow__ , __leaf__)) ;
typedef int (*__compar_fn_t) (const void *, const void *);
typedef __compar_fn_t comparison_fn_t;
typedef int (*__compar_d_fn_t) (const void *, const void *, void *);

extern void *bsearch (const void *__key, const void *__base,
        size_t __nmemb, size_t __size, __compar_fn_t __compar)
     __attribute__ ((__nonnull__ (1, 2, 5))) ;
extern void qsort (void *__base, size_t __nmemb, size_t __size,
     __compar_fn_t __compar) __attribute__ ((__nonnull__ (1, 4)));
extern void qsort_r (void *__base, size_t __nmemb, size_t __size,
     __compar_d_fn_t __compar, void *__arg)
  __attribute__ ((__nonnull__ (1, 4)));
extern int abs (int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern long int labs (long int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;

__extension__ extern long long int llabs (long long int __x)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;

extern div_t div (int __numer, int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern ldiv_t ldiv (long int __numer, long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;


__extension__ extern lldiv_t lldiv (long long int __numer,
        long long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;

extern char *gcvt (double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) ;
extern int rpmatch (const char *__response) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int getsubopt (char **__restrict __optionp,
        char *const *__restrict __tokens,
        char **__restrict __valuep)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2, 3))) ;
extern void setkey (const char *__key) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int posix_openpt (int __oflag) ;
extern int grantpt (int __fd) __attribute__ ((__nothrow__ , __leaf__));
extern int unlockpt (int __fd) __attribute__ ((__nothrow__ , __leaf__));
extern char *ptsname (int __fd) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int ptsname_r (int __fd, char *__buf, size_t __buflen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int getpt (void);



typedef struct __STDIO_FILE_STRUCT FILE;


typedef struct __STDIO_FILE_STRUCT __FILE;
typedef struct {
 __off_t __pos;
} __STDIO_fpos_t;
typedef struct {
 __off64_t __pos;
} __STDIO_fpos64_t;
typedef __off64_t __offmax_t;
typedef __ssize_t __io_read_fn(void *__cookie, char *__buf, size_t __bufsize);
typedef __ssize_t __io_write_fn(void *__cookie,
     const char *__buf, size_t __bufsize);
typedef int __io_seek_fn(void *__cookie, __offmax_t *__pos, int __whence);
typedef int __io_close_fn(void *__cookie);
typedef struct {
 __io_read_fn *read;
 __io_write_fn *write;
 __io_seek_fn *seek;
 __io_close_fn *close;
} _IO_cookie_io_functions_t;
typedef __io_read_fn cookie_read_function_t;
typedef __io_write_fn cookie_write_function_t;
typedef __io_seek_fn cookie_seek_function_t;
typedef __io_close_fn cookie_close_function_t;
typedef _IO_cookie_io_functions_t cookie_io_functions_t;
struct __STDIO_FILE_STRUCT {
 unsigned short __modeflags;
 unsigned char __ungot[2];
 int __filedes;
 unsigned char *__bufstart;
 unsigned char *__bufend;
 unsigned char *__bufpos;
 unsigned char *__bufread;
 unsigned char *__bufgetc_u;
 unsigned char *__bufputc_u;
 struct __STDIO_FILE_STRUCT *__nextopen;
 int __user_locking;
 pthread_mutex_t __lock;
};
extern int __fgetc_unlocked(FILE *__stream);
extern int __fputc_unlocked(int __c, FILE *__stream);
extern FILE *__stdin;
extern FILE *__stdout;
typedef __builtin_va_list __gnuc_va_list;

typedef __STDIO_fpos64_t fpos_t;

typedef __STDIO_fpos64_t fpos64_t;
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

extern int remove (const char *__filename) __attribute__ ((__nothrow__ , __leaf__));
extern int rename (const char *__old, const char *__new) __attribute__ ((__nothrow__ , __leaf__));

extern int renameat (int __oldfd, const char *__old, int __newfd,
       const char *__new) __attribute__ ((__nothrow__ , __leaf__));

extern FILE *tmpfile (void) __asm__ ("" "tmpfile64") ;
extern FILE *tmpfile64 (void) ;
extern char *tmpnam (char *__s) __attribute__ ((__nothrow__ , __leaf__)) ;

extern char *tmpnam_r (char *__s) __attribute__ ((__nothrow__ , __leaf__)) ;
extern char *tempnam (const char *__dir, const char *__pfx)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;

extern int fclose (FILE *__stream);
extern int fflush (FILE *__stream);

extern int fflush_unlocked (FILE *__stream);
extern int fcloseall (void);

extern FILE *fopen (const char *__restrict __filename, const char *__restrict __modes) __asm__ ("" "fopen64")
  ;
extern FILE *freopen (const char *__restrict __filename, const char *__restrict __modes, FILE *__restrict __stream) __asm__ ("" "freopen64")
  ;

extern FILE *fopen64 (const char *__restrict __filename,
        const char *__restrict __modes) ;
extern FILE *freopen64 (const char *__restrict __filename,
   const char *__restrict __modes,
   FILE *__restrict __stream) ;
extern FILE *fdopen (int __fd, const char *__modes) __attribute__ ((__nothrow__ , __leaf__)) ;
extern FILE *fopencookie (void *__restrict __magic_cookie,
     const char *__restrict __modes,
     _IO_cookie_io_functions_t __io_funcs) __attribute__ ((__nothrow__ , __leaf__)) ;
extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
  __attribute__ ((__nothrow__ , __leaf__)) ;
extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) __attribute__ ((__nothrow__ , __leaf__)) ;

extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));
extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
      int __modes, size_t __n) __attribute__ ((__nothrow__ , __leaf__));

extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
         size_t __size) __attribute__ ((__nothrow__ , __leaf__));
extern void setlinebuf (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));

extern int fprintf (FILE *__restrict __stream,
      const char *__restrict __format, ...);
extern int printf (const char *__restrict __format, ...);
extern int sprintf (char *__restrict __s,
      const char *__restrict __format, ...) __attribute__ ((__nothrow__))
     __attribute__ ((__format__ (__printf__, 2, 3)));
extern int vfprintf (FILE *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg);
extern int vprintf (const char *__restrict __format, __gnuc_va_list __arg);
extern int vsprintf (char *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg) __attribute__ ((__nothrow__))
     __attribute__ ((__format__ (__printf__, 2, 0)));


extern int snprintf (char *__restrict __s, size_t __maxlen,
       const char *__restrict __format, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 4)));
extern int vsnprintf (char *__restrict __s, size_t __maxlen,
        const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 0)));

extern int vasprintf (char **__restrict __ptr, const char *__restrict __f,
        __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 0))) ;
extern int asprintf (char **__restrict __ptr,
       const char *__restrict __fmt, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 3))) ;
extern int vdprintf (int __fd, const char *__restrict __fmt,
       __gnuc_va_list __arg)
     __attribute__ ((__format__ (__printf__, 2, 0)));
extern int dprintf (int __fd, const char *__restrict __fmt, ...)
     __attribute__ ((__format__ (__printf__, 2, 3)));

extern int fscanf (FILE *__restrict __stream,
     const char *__restrict __format, ...)
     __attribute__ ((__format__ (__scanf__, 2, 3))) ;
extern int scanf (const char *__restrict __format, ...)
     __attribute__ ((__format__ (__scanf__, 1, 2))) ;
extern int sscanf (const char *__restrict __s,
     const char *__restrict __format, ...)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__format__ (__scanf__, 2, 3)));


extern int vfscanf (FILE *__restrict __s, const char *__restrict __format,
      __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 2, 0))) ;
extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 1, 0))) ;
extern int vsscanf (const char *__restrict __s,
      const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__format__ (__scanf__, 2, 0)));


extern int fgetc (FILE *__stream);
extern int getc (FILE *__stream);
extern int getchar (void);

extern int getc_unlocked (FILE *__stream);
extern int getchar_unlocked (void);
extern int fgetc_unlocked (FILE *__stream);

extern int fputc (int __c, FILE *__stream);
extern int putc (int __c, FILE *__stream);
extern int putchar (int __c);

extern int fputc_unlocked (int __c, FILE *__stream);
extern int putc_unlocked (int __c, FILE *__stream);
extern int putchar_unlocked (int __c);
extern int getw (FILE *__stream);
extern int putw (int __w, FILE *__stream);

extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
     ;

extern char *fgets_unlocked (char *__restrict __s, int __n,
        FILE *__restrict __stream) ;
extern __ssize_t getdelim (char **__restrict __lineptr,
        size_t *__restrict __n, int __delimiter,
        FILE *__restrict __stream) ;
extern __ssize_t getline (char **__restrict __lineptr,
       size_t *__restrict __n,
       FILE *__restrict __stream) ;

extern int fputs (const char *__restrict __s, FILE *__restrict __stream);
extern int puts (const char *__s);
extern int ungetc (int __c, FILE *__stream);
extern size_t fread (void *__restrict __ptr, size_t __size,
       size_t __n, FILE *__restrict __stream) ;
extern size_t fwrite (const void *__restrict __ptr, size_t __size,
        size_t __n, FILE *__restrict __s) ;

extern int fputs_unlocked (const char *__restrict __s,
      FILE *__restrict __stream);
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
         size_t __n, FILE *__restrict __stream) ;
extern size_t fwrite_unlocked (const void *__restrict __ptr, size_t __size,
          size_t __n, FILE *__restrict __stream) ;

extern int fseek (FILE *__stream, long int __off, int __whence);
extern long int ftell (FILE *__stream) ;
extern void rewind (FILE *__stream);

extern int fseeko (FILE *__stream, __off64_t __off, int __whence) __asm__ ("" "fseeko64");
extern __off64_t ftello (FILE *__stream) __asm__ ("" "ftello64");

extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos) __asm__ ("" "fgetpos64");
extern int fsetpos (FILE *__stream, const fpos_t *__pos) __asm__ ("" "fsetpos64");

extern int fseeko64 (FILE *__stream, __off64_t __off, int __whence);
extern __off64_t ftello64 (FILE *__stream) ;
extern int fgetpos64 (FILE *__restrict __stream, fpos64_t *__restrict __pos);
extern int fsetpos64 (FILE *__stream, const fpos64_t *__pos);

extern void clearerr (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern int feof (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int ferror (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;

extern void clearerr_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern int feof_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int ferror_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;

extern void perror (const char *__s);

extern int fileno (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int fileno_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern FILE *popen (const char *__command, const char *__modes) ;
extern int pclose (FILE *__stream);
extern char *ctermid (char *__s) __attribute__ ((__nothrow__ , __leaf__));
extern char *cuserid (char *__s);
extern void flockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern int ftrylockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern void funlockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));



extern void *memcpy (void *__restrict __dest,
       const void *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *memmove (void *__dest, const void *__src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern void *memccpy (void *__restrict __dest, const void *__restrict __src,
        int __c, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern void *memset (void *__s, int __c, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int memcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *memchr (const void *__s, int __c, size_t __n)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));

extern void *rawmemchr (const void *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern void *memrchr (const void *__s, int __c, size_t __n)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));

extern char *strcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strcat (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strncat (char *__restrict __dest, const char *__restrict __src,
        size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strcmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strncmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strcoll (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern size_t strxfrm (char *__restrict __dest,
         const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern char *strdup (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));
extern char *strndup (const char *__string, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));

extern char *strchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern char *strrchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));

extern char *strchrnul (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));

extern size_t strcspn (const char *__s, const char *__reject)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern size_t strspn (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strpbrk (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strstr (const char *__haystack, const char *__needle)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strtok (char *__restrict __s, const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern char *strtok_r (char *__restrict __s, const char *__restrict __delim,
         char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));
extern char *strcasestr (const char *__haystack, const char *__needle)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *memmem (const void *__haystack, size_t __haystacklen,
       const void *__needle, size_t __needlelen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 3)));
extern void *mempcpy (void *__restrict __dest,
        const void *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern size_t strlen (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));

extern size_t strnlen (const char *__string, size_t __maxlen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));

extern char *strerror (int __errnum) __attribute__ ((__nothrow__ , __leaf__));

extern char *__glibc_strerror_r (int __errnum, char *__buf, size_t __buflen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern char * strerror_r (int __errnum, char *__buf, size_t __buflen) __asm__ ("" "__glibc_strerror_r") __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern void bcopy (const void *__src, void *__dest, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern void bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int bcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *index (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern char *rindex (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern int ffs (int __i) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int ffsl (long int __l) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__ extern int ffsll (long long int __ll)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int strcasecmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strncasecmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strsep (char **__restrict __stringp,
       const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strsignal (int __sig) __attribute__ ((__nothrow__ , __leaf__));
extern char *stpcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strverscmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *basename (const char *__filename) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern size_t strlcat(char *__restrict dst, const char *__restrict src,
                      size_t n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern size_t strlcpy(char *__restrict dst, const char *__restrict src,
                      size_t n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int *__errno_location (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern const char *program_invocation_name, *program_invocation_short_name;

typedef int error_t;


struct tm
{
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
  long int tm_gmtoff;
  const char *tm_zone;
};


struct itimerspec
  {
    struct timespec it_interval;
    struct timespec it_value;
  };
struct sigevent;

extern clock_t clock (void) __attribute__ ((__nothrow__ , __leaf__));
extern time_t time (time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));
extern double difftime (time_t __time1, time_t __time0)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern time_t mktime (struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));
extern size_t strftime (char *__restrict __s, size_t __maxsize,
   const char *__restrict __format,
   const struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));

extern char *strptime (const char *__restrict __s,
         const char *__restrict __fmt, struct tm *__tp)
     __attribute__ ((__nothrow__ , __leaf__));

extern struct tm *gmtime (const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));
extern struct tm *localtime (const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));

extern struct tm *gmtime_r (const time_t *__restrict __timer,
       struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));
extern struct tm *localtime_r (const time_t *__restrict __timer,
          struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));

extern char *asctime (const struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));
extern char *ctime (const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));

extern char *asctime_r (const struct tm *__restrict __tp,
   char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));
extern char *ctime_r (const time_t *__restrict __timer,
        char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));
extern char *tzname[2];
extern void tzset (void) __attribute__ ((__nothrow__ , __leaf__));
extern int daylight;
extern long int timezone;
extern int stime (const time_t *__when) __attribute__ ((__nothrow__ , __leaf__));
extern time_t timegm (struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));
extern time_t timelocal (struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));
extern int dysize (int __year) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int nanosleep (const struct timespec *__requested_time,
        struct timespec *__remaining);
extern int clock_getres (clockid_t __clock_id, struct timespec *__res) __attribute__ ((__nothrow__ , __leaf__));
extern int clock_gettime (clockid_t __clock_id, struct timespec *__tp) __attribute__ ((__nothrow__ , __leaf__));
extern int clock_settime (clockid_t __clock_id, const struct timespec *__tp)
     __attribute__ ((__nothrow__ , __leaf__));
extern int clock_nanosleep (clockid_t __clock_id, int __flags,
       const struct timespec *__req,
       struct timespec *__rem);
extern int clock_getcpuclockid (pid_t __pid, clockid_t *__clock_id) __attribute__ ((__nothrow__ , __leaf__));
extern int timer_create (clockid_t __clock_id,
    struct sigevent *__restrict __evp,
    timer_t *__restrict __timerid) __attribute__ ((__nothrow__ , __leaf__));
extern int timer_delete (timer_t __timerid) __attribute__ ((__nothrow__ , __leaf__));
extern int timer_settime (timer_t __timerid, int __flags,
     const struct itimerspec *__restrict __value,
     struct itimerspec *__restrict __ovalue) __attribute__ ((__nothrow__ , __leaf__));
extern int timer_gettime (timer_t __timerid, struct itimerspec *__value)
     __attribute__ ((__nothrow__ , __leaf__));
extern int timer_getoverrun (timer_t __timerid) __attribute__ ((__nothrow__ , __leaf__));


struct timezone
  {
    int tz_minuteswest;
    int tz_dsttime;
  };
typedef struct timezone *__restrict __timezone_ptr_t;
extern int gettimeofday (struct timeval *__restrict __tv,
    __timezone_ptr_t __tz) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int settimeofday (const struct timeval *__tv,
    const struct timezone *__tz)
     __attribute__ ((__nothrow__ , __leaf__));
extern int adjtime (const struct timeval *__delta,
      struct timeval *__olddelta) __attribute__ ((__nothrow__ , __leaf__));
enum __itimer_which
  {
    ITIMER_REAL = 0,
    ITIMER_VIRTUAL = 1,
    ITIMER_PROF = 2
  };
struct itimerval
  {
    struct timeval it_interval;
    struct timeval it_value;
  };
typedef enum __itimer_which __itimer_which_t;
extern int getitimer (__itimer_which_t __which,
        struct itimerval *__value) __attribute__ ((__nothrow__ , __leaf__));
extern int setitimer (__itimer_which_t __which,
        const struct itimerval *__restrict __new,
        struct itimerval *__restrict __old) __attribute__ ((__nothrow__ , __leaf__));
extern int utimes (const char *__file, const struct timeval __tvp[2])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int lutimes (const char *__file, const struct timeval __tvp[2])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int futimesat (int __fd, const char *__file,
        const struct timeval __tvp[2]) __attribute__ ((__nothrow__ , __leaf__));

void die(void) __attribute__((__noreturn__));
void error_msg(const char *fmt, ...) __attribute__((__format__ (printf, 1, 2)));
void perror_msg(const char *fmt, ...) __attribute__((__format__ (printf, 1, 2)));
void perror_msg_and_die(const char *fmt, ...)
 __attribute__((__format__ (printf, 1, 2))) __attribute__((__noreturn__));
void error_msg_and_help(const char *fmt, ...)
 __attribute__((__format__ (printf, 1, 2))) __attribute__((__noreturn__));
void error_msg_and_die(const char *fmt, ...)
 __attribute__((__format__ (printf, 1, 2))) __attribute__((__noreturn__));
typedef unsigned short __kernel_mode_t;
typedef unsigned short __kernel_ipc_pid_t;
typedef unsigned short __kernel_uid_t;
typedef unsigned short __kernel_gid_t;
typedef unsigned short __kernel_old_dev_t;
typedef long __kernel_long_t;
typedef unsigned long __kernel_ulong_t;
typedef __kernel_ulong_t __kernel_ino_t;
typedef int __kernel_pid_t;
typedef __kernel_long_t __kernel_suseconds_t;
typedef int __kernel_daddr_t;
typedef unsigned int __kernel_uid32_t;
typedef unsigned int __kernel_gid32_t;
typedef __kernel_uid_t __kernel_old_uid_t;
typedef __kernel_gid_t __kernel_old_gid_t;
typedef unsigned int __kernel_size_t;
typedef int __kernel_ssize_t;
typedef int __kernel_ptrdiff_t;
typedef struct {
 int val[2];
} __kernel_fsid_t;
typedef __kernel_long_t __kernel_off_t;
typedef long long __kernel_loff_t;
typedef __kernel_long_t __kernel_time_t;
typedef __kernel_long_t __kernel_clock_t;
typedef int __kernel_timer_t;
typedef int __kernel_clockid_t;
typedef char * __kernel_caddr_t;
typedef unsigned short __kernel_uid16_t;
typedef unsigned short __kernel_gid16_t;
typedef __kernel_long_t kernel_long_t;
typedef __kernel_ulong_t kernel_ulong_t;
typedef struct {
 kernel_ulong_t d_ino;
 kernel_ulong_t d_off;
 unsigned short d_reclen;
 char d_name[1];
} kernel_dirent;
typedef unsigned long mpers_ptr_t;
extern int
string_to_uint(const char *str);
extern int
string_to_uint_ex(const char *str, char **endptr,
    unsigned int max_val, const char *accepted_ending);
static inline int
string_to_uint_upto(const char *const str, const unsigned int max_val)
{
 return string_to_uint_ex(str, ((void *)0), max_val, ((void *)0));
}
typedef struct sysent {
 unsigned nargs;
 int sys_flags;
 int sen;
 int (*sys_func)();
 const char *sys_name;
} struct_sysent;
void *xcalloc(size_t nmemb, size_t size)
 __attribute__((__malloc__)) __attribute__((__alloc_size__ (1, 2)));
void *xmalloc(size_t size) __attribute__((__malloc__)) __attribute__((__alloc_size__ (1)));
void *xreallocarray(void *ptr, size_t nmemb, size_t size)
 __attribute__((__alloc_size__ (2, 3)));
char *xstrdup(const char *str) __attribute__((__malloc__));
char *xstrndup(const char *str, size_t n) __attribute__((__malloc__));
typedef struct ioctlent {
 const char *symbol;
 unsigned int code;
} struct_ioctlent;
struct inject_data {
 uint16_t flags;
 uint16_t signo;
 int rval;
};
struct inject_opts {
 uint16_t first;
 uint16_t step;
 struct inject_data data;
};
struct tcb {
 int flags;
 int pid;
 int qual_flg;
 unsigned long u_error;
 kernel_ulong_t scno;
 kernel_ulong_t u_arg[6];
 kernel_long_t u_rval;
 int sys_func_rval;
 int curcol;
 FILE *outf;
 const char *auxstr;
 void *_priv_data;
 void (*_free_priv_data)(void *);
 const struct_sysent *s_ent;
 const struct_sysent *s_prev_ent;
 struct inject_opts *inject_vec[1];
 struct timeval stime;
 struct timeval dtime;
 struct timeval etime;
};
struct xlat {
 uint64_t val;
 const char *str;
};
extern const struct xlat addrfams[];
extern const struct xlat arp_hardware_types[];
extern const struct xlat at_flags[];
extern const struct xlat clocknames[];
extern const struct xlat dirent_types[];
extern const struct xlat ethernet_protocols[];
extern const struct xlat evdev_abs[];
extern const struct xlat iffflags[];
extern const struct xlat inet_protocols[];
extern const struct xlat ip_type_of_services[];
extern const struct xlat msg_flags[];
extern const struct xlat netlink_protocols[];
extern const struct xlat nl_route_types[];
extern const struct xlat open_access_modes[];
extern const struct xlat open_mode_flags[];
extern const struct xlat resource_flags[];
extern const struct xlat routing_scopes[];
extern const struct xlat routing_table_ids[];
extern const struct xlat routing_types[];
extern const struct xlat seccomp_ret_action[];
extern const struct xlat setns_types[];
extern const struct xlat sg_io_info[];
extern const struct xlat socketlayers[];
extern const struct xlat socktypes[];
extern const struct xlat tcp_state_flags[];
extern const struct xlat tcp_states[];
extern const struct xlat whence_codes[];
enum sock_proto {
 SOCK_PROTO_UNKNOWN,
 SOCK_PROTO_UNIX,
 SOCK_PROTO_TCP,
 SOCK_PROTO_UDP,
 SOCK_PROTO_TCPv6,
 SOCK_PROTO_UDPv6,
 SOCK_PROTO_NETLINK
};
extern enum sock_proto get_proto_by_name(const char *);
enum iov_decode {
 IOV_DECODE_ADDR,
 IOV_DECODE_STR,
 IOV_DECODE_NETLINK
};
typedef enum {
 CFLAG_NONE = 0,
 CFLAG_ONLY_STATS,
 CFLAG_BOTH
} cflag_t;
extern cflag_t cflag;
extern _Bool debug_flag;
extern _Bool Tflag;
extern _Bool iflag;
extern _Bool count_wallclock;
extern unsigned int qflag;
extern _Bool not_failing_only;
extern unsigned int show_fd_path;
extern struct path_set {
 const char **paths_selected;
 unsigned int num_selected;
} global_path_set;
extern unsigned xflag;
extern unsigned followfork;
extern unsigned ptrace_setoptions;
extern unsigned max_strlen;
extern unsigned os_release;
extern int read_int_from_file(const char *, int *);
extern void set_sortby(const char *);
extern void set_overhead(int);
extern void print_pc(struct tcb *);
extern int syscall_entering_decode(struct tcb *);
extern int syscall_entering_trace(struct tcb *, unsigned int *);
extern void syscall_entering_finish(struct tcb *, int);
extern int syscall_exiting_decode(struct tcb *, struct timeval *);
extern int syscall_exiting_trace(struct tcb *, struct timeval, int);
extern void syscall_exiting_finish(struct tcb *);
extern void count_syscall(struct tcb *, const struct timeval *);
extern void call_summary(FILE *);
extern void clear_regs(void);
extern int get_scno(struct tcb *);
extern kernel_ulong_t get_rt_sigframe_addr(struct tcb *);
extern const char *syscall_name(kernel_ulong_t scno);
extern const char *err_name(unsigned long err);
extern _Bool is_erestart(struct tcb *);
extern void temporarily_clear_syserror(struct tcb *);
extern void restore_cleared_syserror(struct tcb *);
extern void *get_tcb_priv_data(const struct tcb *);
extern int set_tcb_priv_data(struct tcb *, void *priv_data,
        void (*free_priv_data)(void *));
extern void free_tcb_priv_data(struct tcb *);
static inline unsigned long get_tcb_priv_ulong(const struct tcb *tcp)
{
 return (unsigned long) get_tcb_priv_data(tcp);
}
static inline int set_tcb_priv_ulong(struct tcb *tcp, unsigned long val)
{
 return set_tcb_priv_data(tcp, (void *) val, 0);
}
extern int
umoven(struct tcb *, kernel_ulong_t addr, unsigned int len, void *laddr);
extern int
umoven_or_printaddr(struct tcb *, kernel_ulong_t addr,
      unsigned int len, void *laddr);
extern int
umoven_or_printaddr_ignore_syserror(struct tcb *, kernel_ulong_t addr,
        unsigned int len, void *laddr);
extern int
umovestr(struct tcb *, kernel_ulong_t addr, unsigned int len, char *laddr);
extern int upeek(int pid, unsigned long, kernel_ulong_t *);
extern int upoke(int pid, unsigned long, kernel_ulong_t);
extern _Bool
print_array(struct tcb *,
     kernel_ulong_t start_addr,
     size_t nmemb,
     void *elem_buf,
     size_t elem_size,
     int (*umoven_func)(struct tcb *,
         kernel_ulong_t,
         unsigned int,
         void *),
     _Bool (*print_func)(struct tcb *,
         void *elem_buf,
         size_t elem_size,
         void *opaque_data),
     void *opaque_data);
extern const char *signame(const int);
extern void pathtrace_select_set(const char *, struct path_set *);
extern _Bool pathtrace_match_set(struct tcb *, struct path_set *);
extern int getfdpath(struct tcb *, int, char *, unsigned);
extern unsigned long getfdinode(struct tcb *, int);
extern enum sock_proto getfdproto(struct tcb *, int);
extern const char *xlookup(const struct xlat *, const uint64_t);
extern const char *xlat_search(const struct xlat *, const size_t, const uint64_t);
struct dyxlat;
struct dyxlat *dyxlat_alloc(size_t nmemb);
void dyxlat_free(struct dyxlat *);
const struct xlat *dyxlat_get(const struct dyxlat *);
void dyxlat_add_pair(struct dyxlat *, uint64_t val, const char *str, size_t len);
const struct xlat *genl_families_xlat(void);
extern unsigned long get_pagesize(void);
extern int next_set_bit(const void *bit_array, unsigned cur_bit, unsigned size_bits);
static inline const char *
str_strip_prefix_len(const char *str, const char *prefix, size_t prefix_len)
{
 return strncmp(str, prefix, prefix_len) ? str : str + prefix_len;
}
extern int string_quote(const char *, char *, unsigned int, unsigned int);
extern int print_quoted_string(const char *, unsigned int, unsigned int);
extern int print_quoted_cstring(const char *, unsigned int);
extern int getllval(struct tcb *, unsigned long long *, int);
extern int printllval(struct tcb *, const char *, int)
 __attribute__((__format__ (printf, 2, 0)));
extern void printaddr(kernel_ulong_t addr);
extern int printxvals(const uint64_t, const char *, const struct xlat *, ...)
 __attribute__((__sentinel__));
extern int printxval_searchn(const struct xlat *xlat, size_t xlat_size,
 uint64_t val, const char *dflt);
extern int printargs(struct tcb *);
extern int printargs_u(struct tcb *);
extern int printargs_d(struct tcb *);
extern void addflags(const struct xlat *, uint64_t);
extern int printflags_ex(uint64_t, const char *, const struct xlat *, ...)
 __attribute__((__sentinel__));
extern const char *sprintflags(const char *, const struct xlat *, uint64_t);
extern const char *sprinttime(long long sec);
extern const char *sprinttime_nsec(long long sec, unsigned long long nsec);
extern const char *sprinttime_usec(long long sec, unsigned long long usec);
extern void print_symbolic_mode_t(unsigned int);
extern void print_numeric_umode_t(unsigned short);
extern void print_numeric_long_umask(unsigned long);
extern void print_dev_t(unsigned long long dev);
extern void print_abnormal_hi(kernel_ulong_t);
extern void
dumpiov_in_msghdr(struct tcb *, kernel_ulong_t addr, kernel_ulong_t data_size);
extern void
dumpiov_in_mmsghdr(struct tcb *, kernel_ulong_t addr);
extern void
dumpiov_upto(struct tcb *, int len, kernel_ulong_t addr, kernel_ulong_t data_size);
extern void
dumpstr(struct tcb *, kernel_ulong_t addr, int len);
extern void
printstr_ex(struct tcb *, kernel_ulong_t addr, kernel_ulong_t len,
     unsigned int user_style);
extern void
printpathn(struct tcb *, kernel_ulong_t addr, unsigned int n);
extern void
printpath(struct tcb *, kernel_ulong_t addr);
extern void printfd(struct tcb *, int);
extern void print_sockaddr(const void *sa, int len);
extern _Bool
print_inet_addr(int af, const void *addr, unsigned int len, const char *var_name);
extern _Bool
decode_inet_addr(struct tcb *, kernel_ulong_t addr,
   unsigned int len, int family, const char *var_name);
extern const char *get_sockaddr_by_inode(struct tcb *, int fd, unsigned long inode);
extern _Bool print_sockaddr_by_inode(struct tcb *, int fd, unsigned long inode);
extern void print_dirfd(struct tcb *, int);
extern int
decode_sockaddr(struct tcb *, kernel_ulong_t addr, int addrlen);
extern void printuid(const char *, const unsigned int);
extern void
print_sigset_addr_len(struct tcb *, kernel_ulong_t addr, kernel_ulong_t len);
extern void
print_sigset_addr(struct tcb *, kernel_ulong_t addr);
extern const char *sprintsigmask_n(const char *, const void *, unsigned int);
extern void printsignal(int);
extern void
tprint_iov_upto(struct tcb *, kernel_ulong_t len, kernel_ulong_t addr,
  enum iov_decode, kernel_ulong_t data_size);
extern void
decode_netlink(struct tcb *, int fd, kernel_ulong_t addr, kernel_ulong_t len);
extern void tprint_open_modes(unsigned int);
extern const char *sprint_open_modes(unsigned int);
extern void
decode_seccomp_fprog(struct tcb *, kernel_ulong_t addr);
extern void
print_seccomp_fprog(struct tcb *, kernel_ulong_t addr, unsigned short len);
extern void
decode_sock_fprog(struct tcb *, kernel_ulong_t addr);
extern void
print_sock_fprog(struct tcb *, kernel_ulong_t addr, unsigned short len);
struct strace_stat;
extern void print_struct_stat(struct tcb *, const struct strace_stat *const st);
struct strace_statfs;
struct strace_keyctl_kdf_params;
extern void
print_struct_statfs(struct tcb *, kernel_ulong_t addr);
extern void
print_struct_statfs64(struct tcb *, kernel_ulong_t addr, kernel_ulong_t size);
extern void print_ifindex(unsigned int);
extern void qualify(const char *);
extern unsigned int qual_flags(const unsigned int);
extern int dm_ioctl(struct tcb *, unsigned int request, kernel_ulong_t arg);
extern int file_ioctl(struct tcb *, unsigned int request, kernel_ulong_t arg);
extern int fs_x_ioctl(struct tcb *, unsigned int request, kernel_ulong_t arg);
extern int nsfs_ioctl(struct tcb *, unsigned int request, kernel_ulong_t arg);
extern int ptp_ioctl(struct tcb *, unsigned int request, kernel_ulong_t arg);
extern int scsi_ioctl(struct tcb *, unsigned int request, kernel_ulong_t arg);
extern int term_ioctl(struct tcb *, unsigned int request, kernel_ulong_t arg);
extern int ubi_ioctl(struct tcb *, unsigned int request, kernel_ulong_t arg);
extern int uffdio_ioctl(struct tcb *, unsigned int request, kernel_ulong_t arg);
extern int decode_sg_io_v4(struct tcb *, const kernel_ulong_t arg);
struct nlmsghdr;
typedef _Bool (*netlink_decoder_t)(struct tcb *, const struct nlmsghdr *,
      kernel_ulong_t addr, unsigned int len);
extern _Bool decode_netlink_crypto(struct tcb *, const struct nlmsghdr *, kernel_ulong_t addr, unsigned int len);
extern _Bool decode_netlink_route(struct tcb *, const struct nlmsghdr *, kernel_ulong_t addr, unsigned int len);
extern _Bool decode_netlink_selinux(struct tcb *, const struct nlmsghdr *, kernel_ulong_t addr, unsigned int len);
extern _Bool decode_netlink_sock_diag(struct tcb *, const struct nlmsghdr *, kernel_ulong_t addr, unsigned int len);
extern int tv_nz(const struct timeval *);
extern int tv_cmp(const struct timeval *, const struct timeval *);
extern double tv_float(const struct timeval *);
extern void tv_add(struct timeval *, const struct timeval *, const struct timeval *);
extern void tv_sub(struct timeval *, const struct timeval *, const struct timeval *);
extern void tv_mul(struct timeval *, const struct timeval *, int);
extern void tv_div(struct timeval *, const struct timeval *, int);
static inline void
printstrn(struct tcb *tcp, kernel_ulong_t addr, kernel_ulong_t len)
{
 printstr_ex(tcp, addr, len, 0);
}
static inline void
printstr(struct tcb *tcp, kernel_ulong_t addr)
{
 printstr_ex(tcp, addr, -1, 0x01);
}
static inline int
printflags64(const struct xlat *x, uint64_t flags, const char *dflt)
{
 return printflags_ex(flags, dflt, x, ((void *)0));
}
static inline int
printflags(const struct xlat *x, unsigned int flags, const char *dflt)
{
 return printflags64(x, flags, dflt);
}
static inline int
printxval64(const struct xlat *x, const uint64_t val, const char *dflt)
{
 return printxvals(val, dflt, x, ((void *)0));
}
static inline int
printxval(const struct xlat *x, const unsigned int val, const char *dflt)
{
 return printxvals(val, dflt, x, ((void *)0));
}
static inline void
tprint_iov(struct tcb *tcp, kernel_ulong_t len, kernel_ulong_t addr,
    enum iov_decode decode_iov)
{
 tprint_iov_upto(tcp, len, addr, decode_iov, -1);
}
extern struct tcb *printing_tcp;
extern void printleader(struct tcb *);
extern void line_ended(void);
extern void tabto(void);
extern void tprintf(const char *fmt, ...) __attribute__((__format__ (printf, 1, 2)));
extern void tprints(const char *str);
extern void tprintf_comment(const char *fmt, ...) __attribute__((__format__ (printf, 1, 2)));
extern void tprints_comment(const char *str);
extern _Bool printnum_short(struct tcb *, kernel_ulong_t addr, const char *fmt) __attribute__((__format__ (printf, 3, 0)));
extern _Bool printnum_int(struct tcb *, kernel_ulong_t addr, const char *fmt) __attribute__((__format__ (printf, 3, 0)));
extern _Bool printnum_int64(struct tcb *, kernel_ulong_t addr, const char *fmt) __attribute__((__format__ (printf, 3, 0)));
extern _Bool printnum_addr_int(struct tcb *, kernel_ulong_t addr);
extern _Bool printnum_addr_int64(struct tcb *, kernel_ulong_t addr);
extern _Bool printpair_int(struct tcb *, kernel_ulong_t addr, const char *fmt) __attribute__((__format__ (printf, 3, 0)));
extern _Bool printpair_int64(struct tcb *, kernel_ulong_t addr, const char *fmt) __attribute__((__format__ (printf, 3, 0)));
static inline kernel_long_t
truncate_klong_to_current_wordsize(const kernel_long_t v)
{
 {
  return v;
 }
}
static inline kernel_ulong_t
truncate_kulong_to_current_wordsize(const kernel_ulong_t v)
{
 {
  return v;
 }
}
extern const struct_sysent sysent0[];
extern const char *const errnoent0[];
extern const char *const signalent0[];
extern const struct_ioctlent ioctlent0[];
extern unsigned nsyscalls;
extern unsigned nerrnos;
extern unsigned nsignals;
extern unsigned nioctlents;
extern const unsigned int nsyscall_vec[1];
extern const struct_sysent *const sysent_vec[1];
extern struct inject_opts *inject_vec[1];
static inline _Bool
scno_in_range(kernel_ulong_t scno)
{
 return scno < nsyscalls;
}
static inline _Bool
scno_is_valid(kernel_ulong_t scno)
{
 return scno_in_range(scno)
        && sysent0[scno].sys_func
        && !(sysent0[scno].sys_flags & 00002000);
}
typedef __signed__ char __s8;
typedef unsigned char __u8;
typedef __signed__ short __s16;
typedef unsigned short __u16;
typedef __signed__ int __s32;
typedef unsigned int __u32;
__extension__ typedef __signed__ long long __s64;
__extension__ typedef unsigned long long __u64;
typedef struct {
 unsigned long fds_bits[1024 / (8 * sizeof(long))];
} __kernel_fd_set;
typedef void (*__kernel_sighandler_t)(int);
typedef int __kernel_key_t;
typedef int __kernel_mqd_t;
typedef __u16 __le16;
typedef __u16 __be16;
typedef __u32 __le32;
typedef __u32 __be32;
typedef __u64 __le64;
typedef __u64 __be64;
typedef __u16 __sum16;
typedef __u32 __wsum;
struct btrfs_ioctl_vol_args {
 __s64 fd;
 char name[4087 + 1];
};
struct btrfs_qgroup_limit {
 __u64 flags;
 __u64 max_rfer;
 __u64 max_excl;
 __u64 rsv_rfer;
 __u64 rsv_excl;
};
struct btrfs_qgroup_inherit {
 __u64 flags;
 __u64 num_qgroups;
 __u64 num_ref_copies;
 __u64 num_excl_copies;
 struct btrfs_qgroup_limit lim;
 __u64 qgroups[0];
};
struct btrfs_ioctl_qgroup_limit_args {
 __u64 qgroupid;
 struct btrfs_qgroup_limit lim;
};
struct btrfs_ioctl_vol_args_v2 {
 __s64 fd;
 __u64 transid;
 __u64 flags;
 union {
  struct {
   __u64 size;
   struct btrfs_qgroup_inherit *qgroup_inherit;
  };
  __u64 unused[4];
 };
 union {
  char name[4039 + 1];
  __u64 devid;
 };
};
struct btrfs_scrub_progress {
 __u64 data_extents_scrubbed;
 __u64 tree_extents_scrubbed;
 __u64 data_bytes_scrubbed;
 __u64 tree_bytes_scrubbed;
 __u64 read_errors;
 __u64 csum_errors;
 __u64 verify_errors;
 __u64 no_csum;
 __u64 csum_discards;
 __u64 super_errors;
 __u64 malloc_errors;
 __u64 uncorrectable_errors;
 __u64 corrected_errors;
 __u64 last_physical;
 __u64 unverified_errors;
};
struct btrfs_ioctl_scrub_args {
 __u64 devid;
 __u64 start;
 __u64 end;
 __u64 flags;
 struct btrfs_scrub_progress progress;
 __u64 unused[(1024-32-sizeof(struct btrfs_scrub_progress))/8];
};
struct btrfs_ioctl_dev_replace_start_params {
 __u64 srcdevid;
 __u64 cont_reading_from_srcdev_mode;
 __u8 srcdev_name[1024 + 1];
 __u8 tgtdev_name[1024 + 1];
};
struct btrfs_ioctl_dev_replace_status_params {
 __u64 replace_state;
 __u64 progress_1000;
 __u64 time_started;
 __u64 time_stopped;
 __u64 num_write_errors;
 __u64 num_uncorrectable_read_errors;
};
struct btrfs_ioctl_dev_replace_args {
 __u64 cmd;
 __u64 result;
 union {
  struct btrfs_ioctl_dev_replace_start_params start;
  struct btrfs_ioctl_dev_replace_status_params status;
 };
 __u64 spare[64];
};
struct btrfs_ioctl_dev_info_args {
 __u64 devid;
 __u8 uuid[16];
 __u64 bytes_used;
 __u64 total_bytes;
 __u64 unused[379];
 __u8 path[1024];
};
struct btrfs_ioctl_fs_info_args {
 __u64 max_id;
 __u64 num_devices;
 __u8 fsid[16];
 __u32 nodesize;
 __u32 sectorsize;
 __u32 clone_alignment;
 __u32 reserved32;
 __u64 reserved[122];
};
struct btrfs_ioctl_feature_flags {
 __u64 compat_flags;
 __u64 compat_ro_flags;
 __u64 incompat_flags;
};
struct btrfs_balance_args {
 __u64 profiles;
 union {
  __u64 usage;
  struct {
   __u32 usage_min;
   __u32 usage_max;
  };
 };
 __u64 devid;
 __u64 pstart;
 __u64 pend;
 __u64 vstart;
 __u64 vend;
 __u64 target;
 __u64 flags;
 union {
  __u64 limit;
  struct {
   __u32 limit_min;
   __u32 limit_max;
  };
 };
 __u32 stripes_min;
 __u32 stripes_max;
 __u64 unused[6];
} __attribute__ ((__packed__));
struct btrfs_balance_progress {
 __u64 expected;
 __u64 considered;
 __u64 completed;
};
struct btrfs_ioctl_balance_args {
 __u64 flags;
 __u64 state;
 struct btrfs_balance_args data;
 struct btrfs_balance_args meta;
 struct btrfs_balance_args sys;
 struct btrfs_balance_progress stat;
 __u64 unused[72];
};
struct btrfs_ioctl_ino_lookup_args {
 __u64 treeid;
 __u64 objectid;
 char name[4080];
};
struct btrfs_ioctl_search_key {
 __u64 tree_id;
 __u64 min_objectid;
 __u64 max_objectid;
 __u64 min_offset;
 __u64 max_offset;
 __u64 min_transid;
 __u64 max_transid;
 __u32 min_type;
 __u32 max_type;
 __u32 nr_items;
 __u32 unused;
 __u64 unused1;
 __u64 unused2;
 __u64 unused3;
 __u64 unused4;
};
struct btrfs_ioctl_search_header {
 __u64 transid;
 __u64 objectid;
 __u64 offset;
 __u32 type;
 __u32 len;
};
struct btrfs_ioctl_search_args {
 struct btrfs_ioctl_search_key key;
 char buf[(4096 - sizeof(struct btrfs_ioctl_search_key))];
};
struct btrfs_ioctl_search_args_v2 {
 struct btrfs_ioctl_search_key key;
 __u64 buf_size;
 __u64 buf[0];
};
struct btrfs_ioctl_clone_range_args {
  __s64 src_fd;
  __u64 src_offset, src_length;
  __u64 dest_offset;
};
struct btrfs_ioctl_defrag_range_args {
 __u64 start;
 __u64 len;
 __u64 flags;
 __u32 extent_thresh;
 __u32 compress_type;
 __u32 unused[4];
};
struct btrfs_ioctl_same_extent_info {
 __s64 fd;
 __u64 logical_offset;
 __u64 bytes_deduped;
 __s32 status;
 __u32 reserved;
};
struct btrfs_ioctl_same_args {
 __u64 logical_offset;
 __u64 length;
 __u16 dest_count;
 __u16 reserved1;
 __u32 reserved2;
 struct btrfs_ioctl_same_extent_info info[0];
};
struct btrfs_ioctl_space_info {
 __u64 flags;
 __u64 total_bytes;
 __u64 used_bytes;
};
struct btrfs_ioctl_space_args {
 __u64 space_slots;
 __u64 total_spaces;
 struct btrfs_ioctl_space_info spaces[0];
};
struct btrfs_data_container {
 __u32 bytes_left;
 __u32 bytes_missing;
 __u32 elem_cnt;
 __u32 elem_missed;
 __u64 val[0];
};
struct btrfs_ioctl_ino_path_args {
 __u64 inum;
 __u64 size;
 __u64 reserved[4];
 __u64 fspath;
};
struct btrfs_ioctl_logical_ino_args {
 __u64 logical;
 __u64 size;
 __u64 reserved[4];
 __u64 inodes;
};
enum btrfs_dev_stat_values {
 BTRFS_DEV_STAT_WRITE_ERRS,
 BTRFS_DEV_STAT_READ_ERRS,
 BTRFS_DEV_STAT_FLUSH_ERRS,
 BTRFS_DEV_STAT_CORRUPTION_ERRS,
 BTRFS_DEV_STAT_GENERATION_ERRS,
 BTRFS_DEV_STAT_VALUES_MAX
};
struct btrfs_ioctl_get_dev_stats {
 __u64 devid;
 __u64 nr_items;
 __u64 flags;
 __u64 values[BTRFS_DEV_STAT_VALUES_MAX];
 __u64 unused[128 - 2 - BTRFS_DEV_STAT_VALUES_MAX];
};
struct btrfs_ioctl_quota_ctl_args {
 __u64 cmd;
 __u64 status;
};
struct btrfs_ioctl_quota_rescan_args {
 __u64 flags;
 __u64 progress;
 __u64 reserved[6];
};
struct btrfs_ioctl_qgroup_assign_args {
 __u64 assign;
 __u64 src;
 __u64 dst;
};
struct btrfs_ioctl_qgroup_create_args {
 __u64 create;
 __u64 qgroupid;
};
struct btrfs_ioctl_timespec {
 __u64 sec;
 __u32 nsec;
};
struct btrfs_ioctl_received_subvol_args {
 char uuid[16];
 __u64 stransid;
 __u64 rtransid;
 struct btrfs_ioctl_timespec stime;
 struct btrfs_ioctl_timespec rtime;
 __u64 flags;
 __u64 reserved[16];
};
struct btrfs_ioctl_send_args {
 __s64 send_fd;
 __u64 clone_sources_count;
 __u64 *clone_sources;
 __u64 parent_root;
 __u64 flags;
 __u64 reserved[4];
};
enum btrfs_err_code {
 BTRFS_ERROR_DEV_RAID1_MIN_NOT_MET = 1,
 BTRFS_ERROR_DEV_RAID10_MIN_NOT_MET,
 BTRFS_ERROR_DEV_RAID5_MIN_NOT_MET,
 BTRFS_ERROR_DEV_RAID6_MIN_NOT_MET,
 BTRFS_ERROR_DEV_TGT_REPLACE,
 BTRFS_ERROR_DEV_MISSING_NOT_FOUND,
 BTRFS_ERROR_DEV_ONLY_WRITABLE,
 BTRFS_ERROR_DEV_EXCL_RUN_IN_PROGRESS
};
typedef struct btrfs_ioctl_dev_replace_args
 struct_btrfs_ioctl_dev_replace_args;
typedef struct btrfs_ioctl_send_args
 struct_btrfs_ioctl_send_args;
typedef struct btrfs_ioctl_received_subvol_args
 struct_btrfs_ioctl_received_subvol_args;
typedef struct btrfs_ioctl_vol_args_v2
 struct_btrfs_ioctl_vol_args_v2;
struct file_clone_range {
 __s64 src_fd;
 __u64 src_offset;
 __u64 src_length;
 __u64 dest_offset;
};
struct fstrim_range {
 __u64 start;
 __u64 len;
 __u64 minlen;
};
struct file_dedupe_range_info {
 __s64 dest_fd;
 __u64 dest_offset;
 __u64 bytes_deduped;
 __s32 status;
 __u32 reserved;
};
struct file_dedupe_range {
 __u64 src_offset;
 __u64 src_length;
 __u16 dest_count;
 __u16 reserved1;
 __u32 reserved2;
 struct file_dedupe_range_info info[0];
};
struct files_stat_struct {
 unsigned long nr_files;
 unsigned long nr_free_files;
 unsigned long max_files;
};
struct inodes_stat_t {
 long nr_inodes;
 long nr_unused;
 long dummy[5];
};
struct fsxattr {
 __u32 fsx_xflags;
 __u32 fsx_extsize;
 __u32 fsx_nextents;
 __u32 fsx_projid;
 __u32 fsx_cowextsize;
 unsigned char fsx_pad[8];
};
struct fscrypt_policy {
 __u8 version;
 __u8 contents_encryption_mode;
 __u8 filenames_encryption_mode;
 __u8 flags;
 __u8 master_key_descriptor[8];
};
struct fscrypt_key {
 __u32 mode;
 __u8 raw[64];
 __u32 size;
};
typedef int __kernel_rwf_t;
typedef __u64 u64;
static
const struct xlat btrfs_balance_args[] = {
 { (uint64_t)((1ULL << 0)), "BTRFS_BALANCE_ARGS_PROFILES" },
 { (uint64_t)((1ULL << 1)), "BTRFS_BALANCE_ARGS_USAGE" },
 { (uint64_t)((1ULL << 2)), "BTRFS_BALANCE_ARGS_DEVID" },
 { (uint64_t)((1ULL << 3)), "BTRFS_BALANCE_ARGS_DRANGE" },
 { (uint64_t)((1ULL << 4)), "BTRFS_BALANCE_ARGS_VRANGE" },
 { (uint64_t)((1ULL << 5)), "BTRFS_BALANCE_ARGS_LIMIT" },
 { (uint64_t)((1ULL << 6)), "BTRFS_BALANCE_ARGS_LIMIT_RANGE" },
 { (uint64_t)((1ULL << 7)), "BTRFS_BALANCE_ARGS_STRIPES_RANGE" },
 { (uint64_t)((1ULL << 8)), "BTRFS_BALANCE_ARGS_CONVERT" },
 { (uint64_t)((1ULL << 9)), "BTRFS_BALANCE_ARGS_SOFT" },
 { (uint64_t)((1ULL << 10)), "BTRFS_BALANCE_ARGS_USAGE_RANGE" },
 { 0, 0 }
};
static
const struct xlat btrfs_balance_ctl_cmds[] = {
 { (unsigned)(1), "BTRFS_BALANCE_CTL_PAUSE" },
 { (unsigned)(2), "BTRFS_BALANCE_CTL_CANCEL" },
 { 0, 0 }
};
static
const struct xlat btrfs_balance_flags[] = {
 { (uint64_t)((1ULL << 0)), "BTRFS_BALANCE_DATA" },
 { (uint64_t)((1ULL << 1)), "BTRFS_BALANCE_SYSTEM" },
 { (uint64_t)((1ULL << 2)), "BTRFS_BALANCE_METADATA" },
 { (uint64_t)((1ULL << 3)), "BTRFS_BALANCE_FORCE" },
 { (uint64_t)((1ULL << 4)), "BTRFS_BALANCE_RESUME" },
 { 0, 0 }
};
static
const struct xlat btrfs_balance_state[] = {
 { (unsigned)((1ULL << 0)), "BTRFS_BALANCE_STATE_RUNNING" },
 { (unsigned)((1ULL << 1)), "BTRFS_BALANCE_STATE_PAUSE_REQ" },
 { (unsigned)((1ULL << 2)), "BTRFS_BALANCE_STATE_CANCEL_REQ" },
 { 0, 0 }
};
static
const struct xlat btrfs_compress_types[] = {
 { (unsigned)(0), "BTRFS_COMPRESS_NONE" },
 { (unsigned)(1), "BTRFS_COMPRESS_ZLIB" },
 { (unsigned)(2), "BTRFS_COMPRESS_LZO" },
 { 0, 0 }
};
static
const struct xlat btrfs_defrag_flags[] = {
  { (uint64_t)(1), "BTRFS_DEFRAG_RANGE_COMPRESS" },
  { (uint64_t)(2), "BTRFS_DEFRAG_RANGE_START_IO" },
 { 0, 0 }
};
static
const struct xlat btrfs_dev_replace_cmds[] = {
  { (uint64_t)(0), "BTRFS_IOCTL_DEV_REPLACE_CMD_START" },
  { (uint64_t)(1), "BTRFS_IOCTL_DEV_REPLACE_CMD_STATUS" },
  { (uint64_t)(2), "BTRFS_IOCTL_DEV_REPLACE_CMD_CANCEL" },
 { 0, 0 }
};
static
const struct xlat btrfs_dev_replace_results[] = {
  { (uint64_t)(0), "BTRFS_IOCTL_DEV_REPLACE_RESULT_NO_ERROR" },
  { (uint64_t)(1), "BTRFS_IOCTL_DEV_REPLACE_RESULT_NOT_STARTED" },
  { (uint64_t)(2), "BTRFS_IOCTL_DEV_REPLACE_RESULT_ALREADY_STARTED" },
  { (uint64_t)(3), "BTRFS_IOCTL_DEV_REPLACE_RESULT_SCRUB_INPROGRESS" },
 { 0, 0 }
};
static
const struct xlat btrfs_dev_replace_state[] = {
  { (uint64_t)(0), "BTRFS_IOCTL_DEV_REPLACE_STATE_NEVER_STARTED" },
  { (uint64_t)(1), "BTRFS_IOCTL_DEV_REPLACE_STATE_STARTED" },
  { (uint64_t)(2), "BTRFS_IOCTL_DEV_REPLACE_STATE_FINISHED" },
  { (uint64_t)(3), "BTRFS_IOCTL_DEV_REPLACE_STATE_CANCELED" },
  { (uint64_t)(4), "BTRFS_IOCTL_DEV_REPLACE_STATE_SUSPENDED" },
 { 0, 0 }
};
static
const struct xlat btrfs_dev_stats_flags[] = {
  { (uint64_t)((1ULL << 0)), "BTRFS_DEV_STATS_RESET" },
 { 0, 0 }
};
static
const struct xlat btrfs_dev_stats_values[] = {
 { (uint64_t)(BTRFS_DEV_STAT_WRITE_ERRS), "BTRFS_DEV_STAT_WRITE_ERRS" },
 { (uint64_t)(BTRFS_DEV_STAT_READ_ERRS), "BTRFS_DEV_STAT_READ_ERRS" },
 { (uint64_t)(BTRFS_DEV_STAT_FLUSH_ERRS), "BTRFS_DEV_STAT_FLUSH_ERRS" },
 { (uint64_t)(BTRFS_DEV_STAT_CORRUPTION_ERRS), "BTRFS_DEV_STAT_CORRUPTION_ERRS" },
 { (uint64_t)(BTRFS_DEV_STAT_GENERATION_ERRS), "BTRFS_DEV_STAT_GENERATION_ERRS" },
 { 0, 0 }
};
static
const struct xlat btrfs_features_compat[] = {
 { 0, 0 }
};
static
const struct xlat btrfs_features_compat_ro[] = {
 { (uint64_t)((1ULL << 0)), "BTRFS_FEATURE_COMPAT_RO_FREE_SPACE_TREE" },
 { (uint64_t)((1ULL << 1)), "BTRFS_FEATURE_COMPAT_RO_FREE_SPACE_TREE_VALID" },
 { 0, 0 }
};
static
const struct xlat btrfs_features_incompat[] = {
 { (uint64_t)((1ULL << 0)), "BTRFS_FEATURE_INCOMPAT_MIXED_BACKREF" },
 { (uint64_t)((1ULL << 1)), "BTRFS_FEATURE_INCOMPAT_DEFAULT_SUBVOL" },
 { (uint64_t)((1ULL << 2)), "BTRFS_FEATURE_INCOMPAT_MIXED_GROUPS" },
 { (uint64_t)((1ULL << 3)), "BTRFS_FEATURE_INCOMPAT_COMPRESS_LZO" },
 { (uint64_t)((1ULL << 4)), "BTRFS_FEATURE_INCOMPAT_COMPRESS_LZOv2" },
 { (uint64_t)((1ULL << 5)), "BTRFS_FEATURE_INCOMPAT_BIG_METADATA" },
 { (uint64_t)((1ULL << 6)), "BTRFS_FEATURE_INCOMPAT_EXTENDED_IREF" },
 { (uint64_t)((1ULL << 7)), "BTRFS_FEATURE_INCOMPAT_RAID56" },
 { (uint64_t)((1ULL << 8)), "BTRFS_FEATURE_INCOMPAT_SKINNY_METADATA" },
 { (uint64_t)((1ULL << 9)), "BTRFS_FEATURE_INCOMPAT_NO_HOLES" },
 { 0, 0 }
};
static
const struct xlat btrfs_key_types[] = {
 { (uint64_t)(1), "BTRFS_INODE_ITEM_KEY" },
 { (uint64_t)(12), "BTRFS_INODE_REF_KEY" },
 { (uint64_t)(13), "BTRFS_INODE_EXTREF_KEY" },
 { (uint64_t)(24), "BTRFS_XATTR_ITEM_KEY" },
 { (uint64_t)(48), "BTRFS_ORPHAN_ITEM_KEY" },
 { (uint64_t)(60), "BTRFS_DIR_LOG_ITEM_KEY" },
 { (uint64_t)(72), "BTRFS_DIR_LOG_INDEX_KEY" },
 { (uint64_t)(84), "BTRFS_DIR_ITEM_KEY" },
 { (uint64_t)(96), "BTRFS_DIR_INDEX_KEY" },
 { (uint64_t)(108), "BTRFS_EXTENT_DATA_KEY" },
 { (uint64_t)(128), "BTRFS_EXTENT_CSUM_KEY" },
 { (uint64_t)(132), "BTRFS_ROOT_ITEM_KEY" },
 { (uint64_t)(144), "BTRFS_ROOT_BACKREF_KEY" },
 { (uint64_t)(156), "BTRFS_ROOT_REF_KEY" },
 { (uint64_t)(168), "BTRFS_EXTENT_ITEM_KEY" },
 { (uint64_t)(169), "BTRFS_METADATA_ITEM_KEY" },
 { (uint64_t)(176), "BTRFS_TREE_BLOCK_REF_KEY" },
 { (uint64_t)(178), "BTRFS_EXTENT_DATA_REF_KEY" },
 { (uint64_t)(180), "BTRFS_EXTENT_REF_V0_KEY" },
 { (uint64_t)(182), "BTRFS_SHARED_BLOCK_REF_KEY" },
 { (uint64_t)(184), "BTRFS_SHARED_DATA_REF_KEY" },
 { (uint64_t)(192), "BTRFS_BLOCK_GROUP_ITEM_KEY" },
 { (uint64_t)(198), "BTRFS_FREE_SPACE_INFO_KEY" },
 { (uint64_t)(199), "BTRFS_FREE_SPACE_EXTENT_KEY" },
 { (uint64_t)(200), "BTRFS_FREE_SPACE_BITMAP_KEY" },
 { (uint64_t)(204), "BTRFS_DEV_EXTENT_KEY" },
 { (uint64_t)(216), "BTRFS_DEV_ITEM_KEY" },
 { (uint64_t)(228), "BTRFS_CHUNK_ITEM_KEY" },
 { (uint64_t)(240), "BTRFS_QGROUP_STATUS_KEY" },
 { (uint64_t)(242), "BTRFS_QGROUP_INFO_KEY" },
 { (uint64_t)(244), "BTRFS_QGROUP_LIMIT_KEY" },
 { (uint64_t)(246), "BTRFS_QGROUP_RELATION_KEY" },
 { (uint64_t)(248), "BTRFS_BALANCE_ITEM_KEY" },
 { (uint64_t)(248), "BTRFS_TEMPORARY_ITEM_KEY" },
 { (uint64_t)(249), "BTRFS_DEV_STATS_KEY" },
 { (uint64_t)(249), "BTRFS_PERSISTENT_ITEM_KEY" },
 { (uint64_t)(250), "BTRFS_DEV_REPLACE_KEY" },
 { (uint64_t)(251), "BTRFS_UUID_KEY_SUBVOL" },
 { (uint64_t)(252), "BTRFS_UUID_KEY_RECEIVED_SUBVOL" },
 { (uint64_t)(253), "BTRFS_STRING_ITEM_KEY" },
 { (uint64_t)((4294967295U)), "UINT32_MAX" },
 { 0, 0 }
};
static
const struct xlat btrfs_qgroup_ctl_cmds[] = {
  { (uint64_t)(1), "BTRFS_QUOTA_CTL_ENABLE" },
  { (uint64_t)(2), "BTRFS_QUOTA_CTL_DISABLE" },
  { (uint64_t)(3), "BTRFS_QUOTA_CTL_RESCAN__NOTUSED" },
 { 0, 0 }
};
static
const struct xlat btrfs_qgroup_inherit_flags[] = {
  { (uint64_t)((1ULL << 0)), "BTRFS_QGROUP_INHERIT_SET_LIMITS" },
 { 0, 0 }
};
static
const struct xlat btrfs_qgroup_limit_flags[] = {
 { (uint64_t)((1ULL << 0)), "BTRFS_QGROUP_LIMIT_MAX_RFER" },
 { (uint64_t)((1ULL << 1)), "BTRFS_QGROUP_LIMIT_MAX_EXCL" },
 { (uint64_t)((1ULL << 2)), "BTRFS_QGROUP_LIMIT_RSV_RFER" },
 { (uint64_t)((1ULL << 3)), "BTRFS_QGROUP_LIMIT_RSV_EXCL" },
 { (uint64_t)((1ULL << 4)), "BTRFS_QGROUP_LIMIT_RFER_CMPR" },
 { (uint64_t)((1ULL << 5)), "BTRFS_QGROUP_LIMIT_EXCL_CMPR" },
 { 0, 0 }
};
static
const struct xlat btrfs_qgroup_status_flags[] = {
 { (uint64_t)((1ULL << 0)), "BTRFS_QGROUP_STATUS_FLAG_ON" },
 { (uint64_t)((1ULL << 1)), "BTRFS_QGROUP_STATUS_FLAG_RESCAN" },
 { 0, 0 }
};
static
const struct xlat btrfs_scrub_flags[] = {
 { (uint64_t)(1), "BTRFS_SCRUB_READONLY" },
 { 0, 0 }
};
static
const struct xlat btrfs_send_flags[] = {
 { (unsigned)(0x1), "BTRFS_SEND_FLAG_NO_FILE_DATA" },
 { (unsigned)(0x2), "BTRFS_SEND_FLAG_OMIT_STREAM_HEADER" },
 { (unsigned)(0x4), "BTRFS_SEND_FLAG_OMIT_END_CMD" },
 { 0, 0 }
};
static
const struct xlat btrfs_snap_flags_v2[] = {
  { (uint64_t)((1ULL << 0)), "BTRFS_SUBVOL_CREATE_ASYNC" },
  { (uint64_t)((1ULL << 1)), "BTRFS_SUBVOL_RDONLY" },
  { (uint64_t)((1ULL << 2)), "BTRFS_SUBVOL_QGROUP_INHERIT" },
 { 0, 0 }
};
static
const struct xlat btrfs_space_info_flags[] = {
 { (uint64_t)((1ULL << 0)), "BTRFS_BLOCK_GROUP_DATA" },
 { (uint64_t)((1ULL << 1)), "BTRFS_BLOCK_GROUP_SYSTEM" },
 { (uint64_t)((1ULL << 2)), "BTRFS_BLOCK_GROUP_METADATA" },
 { (uint64_t)((1ULL << 3)), "BTRFS_BLOCK_GROUP_RAID0" },
 { (uint64_t)((1ULL << 4)), "BTRFS_BLOCK_GROUP_RAID1" },
 { (uint64_t)((1ULL << 5)), "BTRFS_BLOCK_GROUP_DUP" },
 { (uint64_t)((1ULL << 6)), "BTRFS_BLOCK_GROUP_RAID10" },
 { (uint64_t)((1ULL << 7)), "BTRFS_BLOCK_GROUP_RAID5" },
 { (uint64_t)((1ULL << 8)), "BTRFS_BLOCK_GROUP_RAID6" },
 { (uint64_t)((1ULL << 48)), "BTRFS_AVAIL_ALLOC_BIT_SINGLE" },
 { (uint64_t)((1ULL << 49)), "BTRFS_SPACE_INFO_GLOBAL_RSV" },
 { 0, 0 }
};
static
const struct xlat btrfs_tree_objectids[] = {
 { (uint64_t)(1ULL), "BTRFS_ROOT_TREE_OBJECTID" },
 { (uint64_t)(2ULL), "BTRFS_EXTENT_TREE_OBJECTID" },
 { (uint64_t)(3ULL), "BTRFS_CHUNK_TREE_OBJECTID" },
 { (uint64_t)(4ULL), "BTRFS_DEV_TREE_OBJECTID" },
 { (uint64_t)(5ULL), "BTRFS_FS_TREE_OBJECTID" },
 { (uint64_t)(6ULL), "BTRFS_ROOT_TREE_DIR_OBJECTID" },
 { (uint64_t)(7ULL), "BTRFS_CSUM_TREE_OBJECTID" },
 { (uint64_t)(8ULL), "BTRFS_QUOTA_TREE_OBJECTID" },
 { (uint64_t)(9ULL), "BTRFS_UUID_TREE_OBJECTID" },
 { (uint64_t)(10ULL), "BTRFS_FREE_SPACE_TREE_OBJECTID" },
 { (uint64_t)(256ULL), "BTRFS_FIRST_FREE_OBJECTID" },
 { (uint64_t)(-256ULL), "BTRFS_LAST_FREE_OBJECTID" },
 { (uint64_t)((18446744073709551615ULL)), "UINT64_MAX" },
 { 0, 0 }
};
static inline char
prnibble(char v)
{
 if (v >= 10)
  return 'a' + (v - 10);
 return '0' + v;
}
static int
btrfs_unparse_uuid(unsigned char *uuid, char *out)
{
 int i;
 int ret = 0;
 for (i = 0; i < 16; i++) {
  if (i == 4 || i == 6 || i == 8 || i == 10)
   *out++ = '-';
  *out++ = prnibble(uuid[i] >> 4);
  *out++ = prnibble(uuid[i] & 0xf);
  if (uuid[i])
   ret = 1;
 }
 *out = '\0';
 return ret;
}
static void
print_u64(const char *name, uint64_t value)
{
 tprintf(", %s=%" "ll" "u", name, value);
 if (value == (18446744073709551615ULL))
  tprints_comment("UINT64_MAX");
}
static void
btrfs_print_balance_args(const char *name, const struct btrfs_balance_args *bba)
{
 tprintf(", %s={profiles=", name);
 printflags64(btrfs_space_info_flags, bba->profiles,
       "BTRFS_BLOCK_GROUP_???");
 print_u64("usage", bba->usage);
 print_u64("devid", bba->devid);
 print_u64("pstart", bba->pstart);
 print_u64("pend", bba->pend);
 print_u64("vstart", bba->vstart);
 print_u64("vend", bba->vend);
 print_u64("target", bba->target);
 tprints(", flags=");
 printflags64(btrfs_balance_args, bba->flags, "BTRFS_BALANCE_ARGS_???");
 tprints("}");
}
static void
btrfs_print_balance(struct tcb *const tcp, const kernel_ulong_t arg, _Bool out)
{
 struct btrfs_ioctl_balance_args balance_args;
 if (umoven_or_printaddr((tcp), (arg), sizeof(*(&balance_args)), (void *) (&balance_args)))
  return;
 tprints("{flags=");
 printflags64(btrfs_balance_flags, balance_args.flags,
       "BTRFS_BALANCE_???");
 if (out) {
  tprints(", state=");
  printflags64(btrfs_balance_state, balance_args.state,
        "BTRFS_BALANCE_STATE_???");
 }
 if (balance_args.flags & (1ULL << 0))
  btrfs_print_balance_args("data", &balance_args.data);
 if (balance_args.flags & (1ULL << 2))
  btrfs_print_balance_args("meta", &balance_args.meta);
 if (balance_args.flags & (1ULL << 1))
  btrfs_print_balance_args("sys", &balance_args.sys);
 tprints("}");
}
static void
btrfs_print_features(const struct btrfs_ioctl_feature_flags *flags)
{
 tprints("{compat_flags=");
 printflags64(btrfs_features_compat, flags->compat_flags,
       "BTRFS_FEATURE_COMPAT_???");
 tprints(", compat_ro_flags=");
 printflags64(btrfs_features_compat_ro, flags->compat_ro_flags,
       "BTRFS_FEATURE_COMPAT_RO_???");
 tprints(", incompat_flags=");
 printflags64(btrfs_features_incompat, flags->incompat_flags,
       "BTRFS_FEATURE_INCOMPAT_???");
 tprints("}");
}
static void
btrfs_print_qgroup_limit(const struct btrfs_qgroup_limit *lim)
{
 tprints("{flags=");
 printflags64(btrfs_qgroup_limit_flags, lim->flags,
       "BTRFS_QGROUP_LIMIT_???");
 tprintf(", max_rfer=%" "ll""u" ", max_excl=%" "ll""u"
  ", rsv_rfer=%" "ll""u" ", rsv_excl=%" "ll""u" "}",
  lim->max_rfer, lim->max_excl,
  lim->rsv_rfer, lim->rsv_excl);
}
static void
btrfs_print_key_type(uint32_t type)
{
 tprintf("%u", type);
 tprints_comment(xlookup(btrfs_key_types, type));
}
static void
btrfs_print_objectid(uint64_t objectid)
{
 tprintf("%" "ll" "u", objectid);
 tprints_comment(xlookup(btrfs_tree_objectids, objectid));
}
static void
btrfs_print_data_container_header(const struct btrfs_data_container *container)
{
 tprintf("{bytes_left=%u, bytes_missing=%u"
  ", elem_cnt=%u, elem_missed=%u, val=",
  container->bytes_left, container->bytes_missing,
  container->elem_cnt, container->elem_missed);
}
static void
btrfs_print_data_container_footer(void)
{
 tprints("}");
}
static _Bool
print_btrfs_data_container_logical_ino(struct tcb *tcp, void *elem_buf,
           size_t elem_size, void *data)
{
 const uint64_t *const record = elem_buf;
 tprintf("{inum=%" "ll" "u" ", offset=%" "ll" "u" ", root=%" "ll" "u" "}",
  record[0], record[1], record[2]);
 return 1;
}
static void
btrfs_print_logical_ino_container(struct tcb *tcp,
      const uint64_t inodes_addr)
{
 struct btrfs_data_container container;
 if (umoven_or_printaddr((tcp), (inodes_addr), sizeof(*(&container)), (void *) (&container)))
  return;
 btrfs_print_data_container_header(&container);
 if (((tcp)->qual_flg & 0x002)) {
  tprints("...");
 } else {
  const uint64_t val_addr =
   inodes_addr + __builtin_offsetof (typeof(container), val);
  uint64_t record[3];
  print_array(tcp, val_addr, container.elem_cnt / 3,
       record, sizeof(record),
       umoven_or_printaddr,
       print_btrfs_data_container_logical_ino, 0);
 }
 btrfs_print_data_container_footer();
}
static _Bool
print_btrfs_data_container_ino_path(struct tcb *tcp, void *elem_buf,
           size_t elem_size, void *data)
{
 const uint64_t *const offset = elem_buf;
 const uint64_t *const val_addr = data;
 printpath(tcp, *val_addr + *offset);
 return 1;
}
static void
btrfs_print_ino_path_container(struct tcb *tcp,
          const uint64_t fspath_addr)
{
 struct btrfs_data_container container;
 if (umoven_or_printaddr((tcp), (fspath_addr), sizeof(*(&container)), (void *) (&container)))
  return;
 btrfs_print_data_container_header(&container);
 if (((tcp)->qual_flg & 0x002)) {
  tprints("...");
 } else {
  uint64_t val_addr =
   fspath_addr + __builtin_offsetof (typeof(container), val);
  uint64_t offset;
  print_array(tcp, val_addr, container.elem_cnt,
       &offset, sizeof(offset),
       umoven_or_printaddr,
       print_btrfs_data_container_ino_path, &val_addr);
 }
 btrfs_print_data_container_footer();
}
static _Bool
print_uint64(struct tcb *tcp, void *elem_buf, size_t elem_size, void *data)
{
 tprintf("%" "ll" "u", *(uint64_t *) elem_buf);
 return 1;
}
static void
btrfs_print_qgroup_inherit(struct tcb *const tcp, const kernel_ulong_t qgi_addr)
{
 struct btrfs_qgroup_inherit inherit;
 if (umoven_or_printaddr((tcp), (qgi_addr), sizeof(*(&inherit)), (void *) (&inherit)))
  return;
 tprints("{flags=");
 printflags64(btrfs_qgroup_inherit_flags, inherit.flags,
       "BTRFS_QGROUP_INHERIT_???");
 tprintf(", num_qgroups=%" "ll""u" ", num_ref_copies=%" "ll""u"
  ", num_excl_copies=%" "ll""u" ", lim=",
  inherit.num_qgroups, inherit.num_ref_copies,
  inherit.num_excl_copies);
 btrfs_print_qgroup_limit(&inherit.lim);
 tprints(", qgroups=");
 if (((tcp)->qual_flg & 0x002)) {
  tprints("...");
 } else {
  uint64_t record;
  print_array(tcp, qgi_addr + __builtin_offsetof (typeof(inherit), qgroups),
       inherit.num_qgroups, &record, sizeof(record),
       umoven_or_printaddr, print_uint64, 0);
 }
 tprints("}");
}
static void
print_key_value_internal(struct tcb *tcp, const char *name, uint64_t value)
{
 if (value) {
  tprintf(", %s=%" "ll" "u", name, value);
  if (value == (18446744073709551615ULL))
   tprints_comment("UINT64_MAX");
 }
}
static void
btrfs_print_tree_search(struct tcb *tcp, struct btrfs_ioctl_search_key *key,
   uint64_t buf_addr, uint64_t buf_size, _Bool print_size)
{
 if ((!((tcp)->flags & 0x04))) {
  tprints("{key={tree_id=");
  btrfs_print_objectid(key->tree_id);
  if (key->min_objectid != 256ULL ||
      !((tcp)->qual_flg & 0x002)) {
   tprints(", min_objectid=");
   btrfs_print_objectid(key->min_objectid);
  }
  if (key->max_objectid != -256ULL ||
      !((tcp)->qual_flg & 0x002)) {
   tprints(", max_objectid=");
   btrfs_print_objectid(key->max_objectid);
  }
  print_key_value_internal((tcp), "min_offset", (key)->min_offset);
  print_key_value_internal((tcp), "max_offset", (key)->max_offset);
  print_key_value_internal((tcp), "min_transid", (key)->min_transid);
  print_key_value_internal((tcp), "max_transid", (key)->max_transid);
  tprints(", min_type=");
  btrfs_print_key_type(key->min_type);
  tprints(", max_type=");
  btrfs_print_key_type(key->max_type);
  tprintf(", nr_items=%u}", key->nr_items);
  if (print_size)
   tprintf(", buf_size=%" "ll" "u", buf_size);
  tprints("}");
 } else {
  tprintf("{key={nr_items=%u}", key->nr_items);
  if (print_size)
   tprintf(", buf_size=%" "ll" "u", buf_size);
  tprints(", buf=");
  if (((tcp)->qual_flg & 0x002))
   tprints("...");
  else {
   uint64_t i;
   uint64_t off = 0;
   tprints("[");
   for (i = 0; i < key->nr_items; i++) {
    struct btrfs_ioctl_search_header sh;
    uint64_t addr = buf_addr + off;
    if (i)
     tprints(", ");
    if (i > max_strlen ||
        umoven((tcp), (addr), sizeof(*(&sh)), (void *) (&sh))) {
     tprints("...");
     break;
    }
    tprintf("{transid=%" "ll""u" ", objectid=",
     sh.transid);
    btrfs_print_objectid(sh.objectid);
    tprintf(", offset=%" "ll""u" ", type=", sh.offset);
    btrfs_print_key_type(sh.type);
    tprintf(", len=%u}", sh.len);
    off += sizeof(sh) + sh.len;
   }
   tprints("]");
  }
  tprints("}");
 }
}
static _Bool
print_objectid_callback(struct tcb *tcp, void *elem_buf,
   size_t elem_size, void *data)
{
 btrfs_print_objectid(*(uint64_t *) elem_buf);
 return 1;
}
static _Bool
print_btrfs_ioctl_space_info(struct tcb *tcp, void *elem_buf,
        size_t elem_size, void *data)
{
 const struct btrfs_ioctl_space_info *info = elem_buf;
 tprints("{flags=");
 printflags64(btrfs_space_info_flags, info->flags,
       "BTRFS_SPACE_INFO_???");
 tprintf(", total_bytes=%" "ll""u" ", used_bytes=%" "ll""u" "}",
  info->total_bytes, info->used_bytes);
 return 1;
}
MPERS_PRINTER_DECL(int, btrfs_ioctl, struct tcb *const tcp, const unsigned int code, const kernel_ulong_t arg)
{
 switch (code) {
 case (((0U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((6)) << 0) | ((0) << ((0 +8)+8))):
 case (((0U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((7)) << 0) | ((0) << ((0 +8)+8))):
 case (((0U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((8)) << 0) | ((0) << ((0 +8)+8))):
 case (((0U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((28)) << 0) | ((0) << ((0 +8)+8))):
 case (((0U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((46)) << 0) | ((0) << ((0 +8)+8))):
 case (((1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((2)) << 0) | ((((sizeof(struct btrfs_ioctl_vol_args)))) << ((0 +8)+8))):
 case (((1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((12)) << 0) | ((((sizeof(struct btrfs_ioctl_vol_args)))) << ((0 +8)+8))):
  break;
 case (((1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((33)) << 0) | ((((sizeof(int)))) << ((0 +8)+8))):
  tprints(", ");
  printxval(btrfs_balance_ctl_cmds, arg, "BTRFS_BALANCE_CTL_???");
  break;
 case (((2U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((24)) << 0) | ((((sizeof(__u64)))) << ((0 +8)+8))):
  if ((!((tcp)->flags & 0x04)))
   return 0;
 case (((1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((19)) << 0) | ((((sizeof(__u64)))) << ((0 +8)+8))):
 case (((1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((22)) << 0) | ((((sizeof(__u64)))) << ((0 +8)+8))):
  tprints(", ");
  printnum_int64(tcp, arg, "%" "ll" "u");
  break;
 case (((2U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((25)) << 0) | ((((sizeof(__u64)))) << ((0 +8)+8))): {
  uint64_t flags;
  if ((!((tcp)->flags & 0x04)))
   return 0;
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&flags)), (void *) (&flags)))
   break;
  printflags64(btrfs_snap_flags_v2, flags, "BTRFS_SUBVOL_???");
  break;
 }
 case (((1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((26)) << 0) | ((((sizeof(__u64)))) << ((0 +8)+8))): {
  uint64_t flags;
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&flags)), (void *) (&flags)))
   break;
  printflags64(btrfs_snap_flags_v2, flags, "BTRFS_SUBVOL_???");
  break;
 }
 case (((2U|1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((32)) << 0) | ((((sizeof(struct btrfs_ioctl_balance_args)))) << ((0 +8)+8))):
  if ((!((tcp)->flags & 0x04))) {
   tprints(", ");
   btrfs_print_balance(tcp, arg, 0);
   return 0;
  }
  if (((tcp)->u_error != 0))
   break;
  tprints(" => ");
  btrfs_print_balance(tcp, arg, 1);
  break;
 case (((2U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((34)) << 0) | ((((sizeof(struct btrfs_ioctl_balance_args)))) << ((0 +8)+8))):
  if ((!((tcp)->flags & 0x04)))
   return 0;
  tprints(", ");
  btrfs_print_balance(tcp, arg, 1);
  break;
 case (((1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((16)) << 0) | ((((sizeof(struct btrfs_ioctl_defrag_range_args)))) << ((0 +8)+8))): {
  struct btrfs_ioctl_defrag_range_args args;
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&args)), (void *) (&args)))
   break;
  tprintf("{start=%" "ll" "u" ", len=", (uint64_t)args.start);
  tprintf("%" "ll" "u", (uint64_t) args.len);
  if (args.len == (18446744073709551615ULL))
   tprints_comment("UINT64_MAX");
  tprints(", flags=");
  printflags64(btrfs_defrag_flags, args.flags,
        "BTRFS_DEFRAG_RANGE_???");
  tprintf(", extent_thresh=%u, compress_type=",
   args.extent_thresh);
  printxval(btrfs_compress_types, args.compress_type,
     "BTRFS_COMPRESS_???");
  tprints("}");
  break;
 }
 case (((2U|1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((30)) << 0) | ((((sizeof(struct btrfs_ioctl_dev_info_args)))) << ((0 +8)+8))): {
  struct btrfs_ioctl_dev_info_args args;
  char uuid[36 +1];
  int valid;
  if ((!((tcp)->flags & 0x04)))
   tprints(", ");
  else if (((tcp)->u_error != 0))
   break;
  else
   tprints(" => ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&args)), (void *) (&args)))
   break;
  tprints("{");
  valid = btrfs_unparse_uuid(args.uuid, uuid);
  if ((!((tcp)->flags & 0x04))) {
   tprintf("devid=%" "ll""u", args.devid);
   if (valid)
    tprintf(", uuid=%s", uuid);
   tprints("}");
   return 0;
  }
  if (valid)
   tprintf("uuid=%s, ", uuid);
  tprintf("bytes_used=%" "ll""u"
   ", total_bytes=%" "ll""u",
   args.bytes_used, args.total_bytes);
  do { tprintf("%s%s=", (", "), "path"); print_quoted_cstring((const char *)(args).path, sizeof((args).path)); } while (0);
  tprints("}");
  break;
 }
 case (((2U|1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((53)) << 0) | ((((sizeof(struct btrfs_ioctl_dev_replace_args)))) << ((0 +8)+8))): {
  struct_btrfs_ioctl_dev_replace_args args;
  if ((!((tcp)->flags & 0x04)))
   tprints(", ");
  else if (((tcp)->u_error != 0))
   break;
  else
   tprints(" => ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&args)), (void *) (&args)))
   break;
  if ((!((tcp)->flags & 0x04))) {
   tprints("{cmd=");
   printxval64(btrfs_dev_replace_cmds, args.cmd,
        "BTRFS_IOCTL_DEV_REPLACE_CMD_???");
   if (args.cmd == 0) {
    const char *str;
    tprintf(", start={srcdevid=%" "ll" "u"
       ", cont_reading_from_srcdev_mode=%" "ll" "u"
       ", srcdev_name=",
       (uint64_t) args.start.srcdevid,
       (uint64_t) args.start.cont_reading_from_srcdev_mode);
    str = (const char *) args.start.srcdev_name;
    print_quoted_cstring(str,
      sizeof(args.start.srcdev_name));
    tprints(", tgtdev_name=");
    str = (const char *) args.start.tgtdev_name;
    print_quoted_cstring(str,
      sizeof(args.start.tgtdev_name));
    tprints("}");
   }
   tprints("}");
   return 0;
  }
  tprints("{result=");
  printxval64(btrfs_dev_replace_results, args.result,
       "BTRFS_IOCTL_DEV_REPLACE_RESULT_???");
  if (args.cmd == 1) {
   tprints(", ");
   printxval64(btrfs_dev_replace_state,
       args.status.replace_state,
       "BTRFS_IOCTL_DEV_REPLACE_STATE_???");
   tprintf(", progress_1000=%" "ll" "u",
    (uint64_t) args.status.progress_1000);
   if (args.status.progress_1000 <= 1000)
    tprintf_comment("%u.%u%%",
     (unsigned) args.status.progress_1000 / 10,
     (unsigned) args.status.progress_1000 % 10);
   tprintf(", time_started=%" "ll" "u",
    (uint64_t) args.status.time_started);
   tprints_comment(sprinttime(args.status.time_started));
   tprintf(", time_stopped=%" "ll" "u",
    (uint64_t) args.status.time_stopped);
   tprints_comment(sprinttime(args.status.time_stopped));
   tprintf(", num_write_errors=%" "ll" "u"
    ", num_uncorrectable_read_errors=%" "ll" "u",
    (uint64_t) args.status.num_write_errors,
    (uint64_t) args.status.num_uncorrectable_read_errors);
  }
  tprints("}");
  break;
 }
 case (((2U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((57)) << 0) | ((((sizeof(struct btrfs_ioctl_feature_flags)))) << ((0 +8)+8))): {
  struct btrfs_ioctl_feature_flags flags;
  if ((!((tcp)->flags & 0x04)))
   return 0;
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&flags)), (void *) (&flags)))
   break;
  btrfs_print_features(&flags);
  break;
 }
 case (((1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((57)) << 0) | ((((sizeof(struct btrfs_ioctl_feature_flags[2])))) << ((0 +8)+8))): {
  struct btrfs_ioctl_feature_flags flarg[2];
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&flarg)), (void *) (&flarg)))
   break;
  tprints("[");
  btrfs_print_features(&flarg[0]);
  tprints(", ");
  btrfs_print_features(&flarg[1]);
  tprints("]");
  break;
 }
 case (((2U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((57)) << 0) | ((((sizeof(struct btrfs_ioctl_feature_flags[3])))) << ((0 +8)+8))): {
  struct btrfs_ioctl_feature_flags flarg[3];
  if ((!((tcp)->flags & 0x04)))
   return 0;
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&flarg)), (void *) (&flarg)))
   break;
  tprints("[");
  btrfs_print_features(&flarg[0]);
  tprints_comment("supported");
  tprints(", ");
  btrfs_print_features(&flarg[1]);
  tprints_comment("safe to set");
  tprints(", ");
  btrfs_print_features(&flarg[2]);
  tprints_comment("safe to clear");
  tprints("]");
  break;
 }
 case (((2U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((31)) << 0) | ((((sizeof(struct btrfs_ioctl_fs_info_args)))) << ((0 +8)+8))): {
  struct btrfs_ioctl_fs_info_args args;
  char uuid[36 +1];
  uint32_t nodesize, sectorsize, clone_alignment;
  if ((!((tcp)->flags & 0x04)))
   return 0;
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&args)), (void *) (&args)))
   break;
  nodesize = args.nodesize,
  sectorsize = args.sectorsize,
  clone_alignment = args.clone_alignment;
  btrfs_unparse_uuid(args.fsid, uuid);
  tprints("{");
  tprintf("max_id=%" "ll""u" ", num_devices=%" "ll""u"
   ", fsid=%s, nodesize=%u, sectorsize=%u"
   ", clone_alignment=%u",
   args.max_id, args.num_devices, uuid,
   nodesize, sectorsize, clone_alignment);
  tprints("}");
  break;
 }
 case (((2U|1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((52)) << 0) | ((((sizeof(struct btrfs_ioctl_get_dev_stats)))) << ((0 +8)+8))): {
  struct btrfs_ioctl_get_dev_stats args;
  uint64_t i;
  if ((!((tcp)->flags & 0x04)))
   tprints(", ");
  else if (((tcp)->u_error != 0))
   break;
  else
   tprints(" => ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&args)), (void *) (&args)))
   break;
  tprints("{");
  if ((!((tcp)->flags & 0x04)))
   tprintf("devid=%" "ll""u" ", ", args.devid);
  tprintf("nr_items=%" "ll""u" ", flags=", args.nr_items);
  printflags64(btrfs_dev_stats_flags, args.flags,
        "BTRFS_DEV_STATS_???");
  if ((!((tcp)->flags & 0x04))) {
   tprints("}");
   return 0;
  }
  tprints(", [");
  for (i = 0; i < args.nr_items; i++) {
   if (i)
    tprints(", ");
   if (i >= (sizeof(args.values) / sizeof((args.values)[0]) + (sizeof(int[-1 + 2 * !!(!__builtin_types_compatible_p(typeof((args.values)), typeof(&(args.values)[0])))]) * 0))) {
    tprints("...");
    break;
   }
   tprintf("%" "ll""u", args.values[i]);
   tprints_comment(xlookup(btrfs_dev_stats_values, i));
  }
  tprints("]}");
  break;
 }
 case (((2U|1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((18)) << 0) | ((((sizeof(struct btrfs_ioctl_ino_lookup_args)))) << ((0 +8)+8))): {
  struct btrfs_ioctl_ino_lookup_args args;
  if ((!((tcp)->flags & 0x04)))
   tprints(", ");
  else if (((tcp)->u_error != 0))
   break;
  else
   tprints(" => ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&args)), (void *) (&args)))
   break;
  if ((!((tcp)->flags & 0x04))) {
   if (args.treeid == 0)
    set_tcb_priv_ulong(tcp, 1);
   tprints("{treeid=");
   btrfs_print_objectid(args.treeid);
   tprints(", objectid=");
   btrfs_print_objectid(args.objectid);
   tprints("}");
   return 0;
  }
  tprints("{");
  if (get_tcb_priv_ulong(tcp)) {
   tprints("treeid=");
   btrfs_print_objectid(args.treeid);
   tprints(", ");
  }
  do { tprintf("%s%s=", (""), "name"); print_quoted_cstring((const char *)(args).name, sizeof((args).name)); } while (0);
  tprints("}");
  break;
 }
 case (((2U|1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((35)) << 0) | ((((sizeof(struct btrfs_ioctl_ino_path_args)))) << ((0 +8)+8))): {
  struct btrfs_ioctl_ino_path_args args;
  if ((!((tcp)->flags & 0x04)))
   tprints(", ");
  else if (((tcp)->u_error != 0))
   break;
  else
   tprints(" => ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&args)), (void *) (&args)))
   break;
  tprints("{");
  if ((!((tcp)->flags & 0x04))) {
   tprintf("inum=%" "ll""u" ", size=%" "ll""u",
    args.inum, args.size);
   tprintf(", fspath=0x%" "ll""x" "}", args.fspath);
   return 0;
  }
  tprints("fspath=");
  btrfs_print_ino_path_container(tcp, args.fspath);
  tprints("}");
  break;
 }
 case (((2U|1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((36)) << 0) | ((((sizeof(struct btrfs_ioctl_logical_ino_args)))) << ((0 +8)+8))): {
  struct btrfs_ioctl_logical_ino_args args;
  if ((!((tcp)->flags & 0x04)))
   tprints(", ");
  else if (((tcp)->u_error != 0))
   break;
  else
   tprints(" => ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&args)), (void *) (&args)))
   break;
  tprints("{");
  if ((!((tcp)->flags & 0x04))) {
   tprintf("logical=%" "ll""u" ", size=%" "ll""u",
    args.logical, args.size);
   tprintf(", inodes=0x%" "ll""x" "}", args.inodes);
   return 0;
  }
  tprints("inodes=");
  btrfs_print_logical_ino_container(tcp, args.inodes);
  tprints("}");
  break;
 }
 case (((1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((41)) << 0) | ((((sizeof(struct btrfs_ioctl_qgroup_assign_args)))) << ((0 +8)+8))): {
  struct btrfs_ioctl_qgroup_assign_args args;
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&args)), (void *) (&args)))
   break;
  tprintf("{assign=%" "ll""u" ", src=%" "ll""u"
   ", dst=%" "ll""u" "}",
   args.assign, args.src, args.dst);
  break;
 }
 case (((1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((42)) << 0) | ((((sizeof(struct btrfs_ioctl_qgroup_create_args)))) << ((0 +8)+8))): {
  struct btrfs_ioctl_qgroup_create_args args;
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&args)), (void *) (&args)))
   break;
  tprintf("{create=%" "ll""u" ", qgroupid=%" "ll""u" "}",
   args.create, args.qgroupid);
  break;
 }
 case (((2U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((43)) << 0) | ((((sizeof(struct btrfs_ioctl_qgroup_limit_args)))) << ((0 +8)+8))): {
  struct btrfs_ioctl_qgroup_limit_args args;
  if ((!((tcp)->flags & 0x04)))
   return 0;
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&args)), (void *) (&args)))
   break;
  tprintf("{qgroupid=%" "ll""u" ", lim=", args.qgroupid);
  btrfs_print_qgroup_limit(&args.lim);
  tprints("}");
  break;
 }
 case (((2U|1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((40)) << 0) | ((((sizeof(struct btrfs_ioctl_quota_ctl_args)))) << ((0 +8)+8))): {
  struct btrfs_ioctl_quota_ctl_args args;
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&args)), (void *) (&args)))
   break;
  printxval64(btrfs_qgroup_ctl_cmds, args.cmd,
       "BTRFS_QUOTA_CTL_???");
  tprints("}");
  break;
 }
 case (((1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((44)) << 0) | ((((sizeof(struct btrfs_ioctl_quota_rescan_args)))) << ((0 +8)+8))): {
  struct btrfs_ioctl_quota_rescan_args args;
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&args)), (void *) (&args)))
   break;
  tprintf("{flags=%" "ll" "u" "}", (uint64_t) args.flags);
  break;
 }
 case (((2U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((45)) << 0) | ((((sizeof(struct btrfs_ioctl_quota_rescan_args)))) << ((0 +8)+8))): {
  struct btrfs_ioctl_quota_rescan_args args;
  if ((!((tcp)->flags & 0x04)))
   return 0;
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&args)), (void *) (&args)))
   break;
  tprintf("{flags=%" "ll" "u" ", progress=", (uint64_t) args.flags);
  btrfs_print_objectid(args.progress);
  tprints("}");
  break;
 }
 case (((2U|1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((37)) << 0) | ((((sizeof(struct btrfs_ioctl_received_subvol_args)))) << ((0 +8)+8))): {
  struct_btrfs_ioctl_received_subvol_args args;
  char uuid[36 +1];
  if ((!((tcp)->flags & 0x04)))
   tprints(", ");
  else if (((tcp)->u_error != 0))
   break;
  else
   tprints(" => ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&args)), (void *) (&args)))
   break;
  if ((!((tcp)->flags & 0x04))) {
   btrfs_unparse_uuid((unsigned char *)args.uuid, uuid);
   tprintf("{uuid=%s, stransid=%" "ll" "u"
    ", stime=%" "ll" "u" ".%u, flags=%" "ll" "u"
    "}", uuid, (uint64_t) args.stransid,
    (uint64_t) args.stime.sec, args.stime.nsec,
    (uint64_t) args.flags);
   return 0;
  }
  tprintf("{rtransid=%" "ll" "u" ", rtime=%" "ll" "u" ".%u}",
   (uint64_t) args.rtransid, (uint64_t) args.rtime.sec,
   args.rtime.nsec);
  break;
 }
 case (((2U|1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((27)) << 0) | ((((sizeof(struct btrfs_ioctl_scrub_args)))) << ((0 +8)+8))):
 case (((2U|1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((29)) << 0) | ((((sizeof(struct btrfs_ioctl_scrub_args)))) << ((0 +8)+8))): {
  struct btrfs_ioctl_scrub_args args;
  if ((!((tcp)->flags & 0x04)))
   tprints(", ");
  else if (((tcp)->u_error != 0))
   break;
  else
   tprints(" => ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&args)), (void *) (&args)))
   break;
  if ((!((tcp)->flags & 0x04))) {
   tprintf("{devid=%" "ll""u", args.devid);
   if (code == (((2U|1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((27)) << 0) | ((((sizeof(struct btrfs_ioctl_scrub_args)))) << ((0 +8)+8)))) {
    tprintf(", start=%" "ll""u" ", end=",
     args.start);
    tprintf("%" "ll""u", args.end);
    if (args.end == (18446744073709551615ULL))
     tprints_comment("UINT64_MAX");
    tprints(", flags=");
    printflags64(btrfs_scrub_flags, args.flags,
          "BTRFS_SCRUB_???");
   }
   tprints("}");
   return 0;
  }
  tprintf("{data_extents_scrubbed=%" "ll""u"
   ", tree_extents_scrubbed=%" "ll""u"
   ", data_bytes_scrubbed=%" "ll""u"
   ", tree_bytes_scrubbed=%" "ll""u"
   ", read_errors=%" "ll""u"
   ", csum_errors=%" "ll""u"
   ", verify_errors=%" "ll""u"
   ", no_csum=%" "ll""u"
   ", csum_discards=%" "ll""u"
   ", super_errors=%" "ll""u"
   ", malloc_errors=%" "ll""u"
   ", uncorrectable_errors=%" "ll""u"
   ", corrected_errors=%" "ll""u"
   ", last_physical=%" "ll""u"
   ", unverified_errors=%" "ll""u" "}",
   args.progress.data_extents_scrubbed,
   args.progress.tree_extents_scrubbed,
   args.progress.data_bytes_scrubbed,
   args.progress.tree_bytes_scrubbed,
   args.progress.read_errors,
   args.progress.csum_errors,
   args.progress.verify_errors,
   args.progress.no_csum,
   args.progress.csum_discards,
   args.progress.super_errors,
   args.progress.malloc_errors,
   args.progress.uncorrectable_errors,
   args.progress.corrected_errors,
   args.progress.last_physical,
   args.progress.unverified_errors);
  break;
 }
 case (((2U|1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((17)) << 0) | ((((sizeof(struct btrfs_ioctl_search_args)))) << ((0 +8)+8))): {
  struct btrfs_ioctl_search_args args;
  uint64_t buf_offset;
  if ((!((tcp)->flags & 0x04)))
   tprints(", ");
  else if (((tcp)->u_error != 0))
   break;
  else
   tprints(" => ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&args)), (void *) (&args)))
   break;
  buf_offset = __builtin_offsetof (struct btrfs_ioctl_search_args, buf);
  btrfs_print_tree_search(tcp, &args.key, arg + buf_offset,
     sizeof(args.buf), 0);
  if ((!((tcp)->flags & 0x04)))
   return 0;
  break;
 }
 case (((2U|1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((17)) << 0) | ((((sizeof(struct btrfs_ioctl_search_args_v2)))) << ((0 +8)+8))): {
  struct btrfs_ioctl_search_args_v2 args;
  uint64_t buf_offset;
  if ((!((tcp)->flags & 0x04)))
   tprints(", ");
  else if (((tcp)->u_error != 0)) {
   if (tcp->u_error == 75) {
    tprints(" => ");
    tcp->u_error = 0;
    if (!umoven_or_printaddr((tcp), (arg), sizeof(*(&args)), (void *) (&args)))
     tprintf("{buf_size=%" "ll" "u" "}",
      (uint64_t)args.buf_size);
    tcp->u_error = 75;
   }
   break;
  } else
   tprints(" => ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&args)), (void *) (&args)))
   break;
  buf_offset = __builtin_offsetof (struct btrfs_ioctl_search_args_v2, buf);
  btrfs_print_tree_search(tcp, &args.key, arg + buf_offset,
     args.buf_size, 1);
  if ((!((tcp)->flags & 0x04)))
   return 0;
  break;
 }
 case (((1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((38)) << 0) | ((((sizeof(struct btrfs_ioctl_send_args)))) << ((0 +8)+8))): {
  struct_btrfs_ioctl_send_args args;
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&args)), (void *) (&args)))
   break;
  tprints("{send_fd=");
  printfd(tcp, args.send_fd);
  tprintf(", clone_sources_count=%" "ll" "u" ", clone_sources=",
   (uint64_t) args.clone_sources_count);
  if (((tcp)->qual_flg & 0x002))
   tprints("...");
  else {
   uint64_t record;
   print_array(tcp, ((kernel_ulong_t) (unsigned long) (args.clone_sources)),
        args.clone_sources_count,
        &record, sizeof(record),
        umoven_or_printaddr,
        print_objectid_callback, 0);
  }
  tprints(", parent_root=");
  btrfs_print_objectid(args.parent_root);
  tprints(", flags=");
  printflags64(btrfs_send_flags, args.flags,
        "BTRFS_SEND_FLAGS_???");
  tprints("}");
  break;
 }
 case (((2U|1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((20)) << 0) | ((((sizeof(struct btrfs_ioctl_space_args)))) << ((0 +8)+8))): {
  struct btrfs_ioctl_space_args args;
  if ((!((tcp)->flags & 0x04)))
   tprints(", ");
  else if (((tcp)->u_error != 0))
   break;
  else
   tprints(" => ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&args)), (void *) (&args)))
   break;
  tprints("{");
  if ((!((tcp)->flags & 0x04))) {
   tprintf("space_slots=%" "ll""u" "}", args.space_slots);
   return 0;
  }
  tprintf("total_spaces=%" "ll""u", args.total_spaces);
  if (args.space_slots == 0 && args.total_spaces) {
   tprints("}");
   break;
  }
  tprints(", spaces=");
  if (((tcp)->qual_flg & 0x002))
   tprints("...");
  else {
   struct btrfs_ioctl_space_info info;
   print_array(tcp, arg + __builtin_offsetof (typeof(args), spaces),
        args.total_spaces,
        &info, sizeof(info), umoven_or_printaddr,
        print_btrfs_ioctl_space_info, 0);
  }
  tprints("}");
  break;
 }
 case (((1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((1)) << 0) | ((((sizeof(struct btrfs_ioctl_vol_args)))) << ((0 +8)+8))):
 case (((1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((3)) << 0) | ((((sizeof(struct btrfs_ioctl_vol_args)))) << ((0 +8)+8))):
 case (((1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((4)) << 0) | ((((sizeof(struct btrfs_ioctl_vol_args)))) << ((0 +8)+8))):
 case (((1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((10)) << 0) | ((((sizeof(struct btrfs_ioctl_vol_args)))) << ((0 +8)+8))):
 case (((1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((11)) << 0) | ((((sizeof(struct btrfs_ioctl_vol_args)))) << ((0 +8)+8))):
 case (((1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((14)) << 0) | ((((sizeof(struct btrfs_ioctl_vol_args)))) << ((0 +8)+8))):
 case (((1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((15)) << 0) | ((((sizeof(struct btrfs_ioctl_vol_args)))) << ((0 +8)+8))):
 case (((2U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((39)) << 0) | ((((sizeof(struct btrfs_ioctl_vol_args)))) << ((0 +8)+8))): {
  struct btrfs_ioctl_vol_args args;
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&args)), (void *) (&args)))
   break;
  tprints("{fd=");
  printfd(tcp, args.fd);
  do { tprintf("%s%s=", (", "), "name"); print_quoted_cstring((const char *)(args).name, sizeof((args).name)); } while (0);
  tprints("}");
  break;
 }
 case (((1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((23)) << 0) | ((((sizeof(struct btrfs_ioctl_vol_args_v2)))) << ((0 +8)+8))):
 case (((1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((24)) << 0) | ((((sizeof(struct btrfs_ioctl_vol_args_v2)))) << ((0 +8)+8))): {
  struct_btrfs_ioctl_vol_args_v2 args;
  if ((!((tcp)->flags & 0x04)))
   tprints(", ");
  else if (((tcp)->u_error != 0))
   break;
  else
   tprints(" => ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&args)), (void *) (&args)))
   break;
  if ((!((tcp)->flags & 0x04))) {
   tprints("{fd=");
   printfd(tcp, args.fd);
   tprints(", flags=");
   printflags64(btrfs_snap_flags_v2, args.flags,
         "BTRFS_SUBVOL_???");
   if (args.flags & (1ULL << 2)) {
    tprintf(", size=%" "ll" "u" ", qgroup_inherit=",
     (uint64_t) args.size);
    btrfs_print_qgroup_inherit(tcp,
     ((kernel_ulong_t) (unsigned long) (args.qgroup_inherit)));
   }
   do { tprintf("%s%s=", (", "), "name"); print_quoted_cstring((const char *)(args).name, sizeof((args).name)); } while (0);
   tprints("}");
   return 0;
  }
  tprintf("{transid=%" "ll" "u" "}", (uint64_t) args.transid);
  break;
 }
 case (((2U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((49)) << 0) | ((((sizeof(char[256])))) << ((0 +8)+8))):
  if ((!((tcp)->flags & 0x04)))
   return 0;
 case (((1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((50)) << 0) | ((((sizeof(char[256])))) << ((0 +8)+8))): {
  char label[256];
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&label)), (void *) (&label)))
   break;
  print_quoted_cstring(label, sizeof(label));
  break;
 }
 case (((1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((9)) << 0) | ((((sizeof(int)))) << ((0 +8)+8))):
 case (((1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((13)) << 0) | ((((sizeof(struct btrfs_ioctl_clone_range_args)))) << ((0 +8)+8))):
 case (((2U|1U) << (((0 +8)+8)+14)) | (((0x94)) << (0 +8)) | (((54)) << 0) | ((((sizeof(struct btrfs_ioctl_same_args)))) << ((0 +8)+8))):
  return file_ioctl(tcp, code, arg);
 default:
  return 0100;
 };
 return 0200;
}
