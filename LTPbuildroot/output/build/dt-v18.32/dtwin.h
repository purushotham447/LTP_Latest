#if !defined(_DT_WIN32_H_)
#define _DT_WIN32_H_ 1

#include <process.h>
#include <time.h>
#include <windows.h>
#include <io.h>                 
#include <direct.h>

typedef signed int ssize_t;
typedef __int64 Offset_t;

/*
 * OS Specific Functions:
 */ 
#define os_sleep(value)		Sleep(value*1000)
#define os_msleep(value)	Sleep(value)
#define os_usleep(value)	Sleep(value/1000)

/*
 * POSIX Thread Definitions:
 */
typedef HANDLE pthread_t;
typedef unsigned long pthread_attr_t;
typedef HANDLE pthread_mutex_t;

/* Note: These are *not* real, just required for compiling! */
#define PTHREAD_CREATE_JOINABLE		0
#define PTHREAD_CREATE_DETACHED		1

extern int pthread_attr_init(pthread_attr_t *attr);
extern int pthread_attr_setscope(pthread_attr_t *attr, unsigned type);
extern int pthread_attr_setdetachstate(pthread_attr_t *attr, int type);
extern int pthread_attr_getstacksize(const pthread_attr_t *attr, size_t *stacksize);
extern int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize);

extern int pthread_create(pthread_t *tid, pthread_attr_t *attr, 
			  void *(*func)(void *), void *arg);
extern void pthread_exit(void *exit_code );
extern int pthread_mutex_init(pthread_mutex_t *lock, void *attr);
extern int pthread_mutex_trylock(pthread_mutex_t *lock);
extern int pthread_mutex_lock(pthread_mutex_t *lock);
extern int pthread_mutex_unlock(pthread_mutex_t *lock);
extern int pthread_join(pthread_t thread, void **exit_value);
extern unsigned long pthread_self();

#define PTHREAD_SCOPE_PROCESS	0 
#define PTHREAD_SCOPE_SYSTEM	1
#define PTHREAD_NORMAL_EXIT	0

/*
 * I/O routines
 */
extern int win32_read(HANDLE handle, char *buffer, size_t size);
extern int win32_write(HANDLE handle, char *buffer, size_t size);
extern Offset_t win32_lseek(HANDLE han, Offset_t, int whence);
extern int win32_open(char *name, int oflags, int perm);
extern int win32_pread(HANDLE handle, char *buffer, size_t size, Offset_t offset);
extern int win32_pwrite(HANDLE handle, char *buffer, size_t size, Offset_t offset);

/* -----------------------------------------------------------------
 * Note: Moved here from dt.h 
 */
#define getuid()	1
#define sleep(a)	Sleep(a*1000)
#define msleep(a)	Sleep(a)
#define usleep(a)	Sleep(a/1000)
#define times(a)	(time(0) * hz)

#define chdir(x)	_chdir(x)
#define dup		_dup
#define getcwd		_getcwd
#define getpid		_getpid
#define unlink		_unlink
#define stat		_stat
#define strdup		_strdup
#define fileno		_fileno
#define isatty		_isatty
#if defined(_USE_32BIT_TIME_T)
#  define localtime_s	_localtime32_s
#else
#  define localtime_s	_localtime64_s
#endif
#define mkdir		_mkdir
#define popen(cmd, mode) _popen(cmd, mode "b")
//#  define popen		_popen
#define pclose		_pclose
#define strncasecmp	_strnicmp
#define strtoll		_strtoi64
#define strtoull	_strtoui64
#define strtok_r	strtok_s
#define SIGALRM		14

/* Note: unlink() exists, but we wish to use native Windows API's! */
#define os_delete_file(file)	(( DeleteFile(file) ) ? SUCCESS : FAILURE)
#define os_msleep(msecs)	Sleep(msecs)

typedef int pid_t;
typedef unsigned int	speed_t;
typedef int		ssize_t; 
typedef LONGLONG	OFF_T;

struct timezone {
    int	tz_minuteswest;	/* minutes W of Greenwich */
    int	tz_dsttime;	/* type of dst correction */
};
extern int gettimeofday(struct timeval *tv, struct timezone *tz);

#define SYSLOG		1
#define LOG_ERR		EVENTLOG_ERROR_TYPE
#define LOG_INFO	EVENTLOG_INFORMATION_TYPE

extern void syslog(int priority, char *format, ...);

#if !defined(INVALID_SET_FILE_POINTER)
#   define INVALID_SET_FILE_POINTER -1
#endif

typedef int             pid_t;
typedef int             ssize_t;        // signed size_t

struct tms {                
     clock_t  tms_utime;     
     clock_t  tms_stime;     
     clock_t  tms_cutime;    
     clock_t  tms_cstime;    
};
 
#define DIRSEP		'\\'
#define DEV_PREFIX	"\\\\.\\"	/* Native Windows device dir.	*/
#define DEV_LEN		4		/* That's for "\\.\" prefix.	*/
#define ADEV_PREFIX	"//./"		/* Windows hidden device dir.	*/
#define ADEV_LEN	4		/* Length of device name prefix.*/

#define DEV_DIR_PREFIX		"\\\\.\\"
#define DEV_DIR_LEN		(sizeof(DEV_DIR_PREFIX) - 1)
#define DEV_DEVICE_LEN		64

#define TEMP_DIR_NAME		"C:\\temp\\"
#define TEMP_DIR_LEN		(sizeof(TEMP_DIR_NAME) - 1)

/* ------------------------------------------------------------------------ */

#define open(file, mode, perm)	\
	win32_open(file, mode, perm)

#define lseek(han, off, whence) \
	win32_lseek((HANDLE)han, off, whence)

#define read(han, buf, size) \
	win32_read((HANDLE)han, buf, size)

#define write(han, buf, size) \
	win32_write((HANDLE)han, buf, size)

#define close(han) \
	CloseHandle((HANDLE)han)
               
#define pread(handle, buffer, nbyte, offset) \
		win32_pread((HANDLE)han, (buf), (nbyte), (offset))

#define pwrite(handle, buffer, nbyte, offset) \
		win32_pwrite((HANDLE)han, (buf), (nbyte), (offset))

typedef void *	caddr_t;

#define popen(cmd, mode) _popen(cmd, mode "b")

extern HANDLE win32_dup(HANDLE handle);
//extern DWORD resume_thread(dinfo_t *dip, HANDLE thread_handle);
//extern DWORD suspend_thread(dinfo_t *dip, HANDLE thread_handle);
//extern void TerminateParentThread(dinfo_t *dip);
extern int IsDriveLetter(char *device);
extern char *FindScsiDevice(char *device);

extern void wPerror(char *format, ...);
#define os_perror wPerror
extern char *os_gethostname(void);
extern char *os_getusername(void);

#endif /* _DT_WIN32_H_ */
