/*
 * WIN32 specific interfaces
 *
 * Modification History:
 *
 * May 12th, 2014 by Robin T. Miller
 * 	Major cleanup to remove unused code, a lot more cleanup is forthcoming.
 * 	Note: After all these changes, not 100% sure this code will compile.
 * 	My compile machine for XP is at home, and this code is for public dt.
 * 	FWIW: The next version of dt, v19.xx, has this stuff cleaned up! ;)
 *
 * January 2012 by Robin T. Miller
 * 	pthread* API's should not report errors, but simply return the
 * error to the caller, so these changes have been made. The caller needs
 * to use OS specific functions to handle *nix vs. Windows error reporting.
 */

#include "dt.h"
#include "dtwin.h"
#include <stdio.h>
#include <signal.h>
#include <winbase.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <io.h>

#define Thread __declspec(thread)

/*
 * Local Storage:
 */
HANDLE exitMutex;			/* Synchronize terminate exit.	*/

int
pthread_attr_init(pthread_attr_t *attr)
{
    return PTHREAD_NORMAL_EXIT;
}

int
pthread_attr_setscope(pthread_attr_t *attr, unsigned type)
{
    return PTHREAD_NORMAL_EXIT;
}

int
pthread_attr_setdetachstate(pthread_attr_t *attr, int type)
{
    return PTHREAD_NORMAL_EXIT;
}

/* 
 * Reference:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/ms682453(v=vs.85).aspx
 */ 
int
pthread_attr_getstacksize(const pthread_attr_t *attr, size_t *stacksize)
{
    *stacksize = MBYTE_SIZE;
    return PTHREAD_NORMAL_EXIT;
}

int
pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize)
{
    return PTHREAD_NORMAL_EXIT;
}

/* 
 * Windows Notes from:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/ms682659(v=vs.85).aspx
 * A thread in an executable that is linked to the static C run-time library  
 * (CRT) should use _beginthread and _endthread for thread management rather  
 * than CreateThread and ExitThread. Failure to do so results in small memory  
 * leaks when the thread calls ExitThread. Another work around is to link the  
 * executable to the CRT in a DLL instead of the static CRT.  
 * Note that this memory leak only occurs from a DLL if the DLL is linked to  
 * the static CRT *and* a thread calls the DisableThreadLibraryCalls function.  
 * Otherwise, it is safe to call CreateThread and ExitThread from a thread in  
 * a DLL that links to the static CRT.  
 *  
 * Robin's Note: September 2012
 * Since we are NOT calling DisableThreadLibraryCalls(), I'm assuming we  
 * do not need to worry about using these alternate thread create/exit API's!
 * Note: The code has left, but not enabled since _MT changes to _MTx.
 * Update: Reenabling _MT method for threads, otherwise hangs occur!
 * Note: The hangs occur while waiting for the parent thread to exit.
 *  
 * A different warning...
 * If you are going to call C run-time routines from a program built
 * with Libcmt.lib, you must start your threads with the _beginthread
 * or _beginthreadex function. Do not use the Win32 functions ExitThread
 * and CreateThread. Using SuspendThread can lead to a deadlock when more
 * than one thread is blocked waiting for the suspended thread to complete
 * its access to a C run-time data structure.
 * URL: http://msdn.microsoft.com/en-us/library/7t9ha0zh(VS.80).aspx
 *
 * Note: My testing proved this to be true, but hangs occured regardless
 * of using these alternate thread API's with thread suspect/resume!
 *
 * Outputs:
 *	tid for Windows is actually the Thread handle, NOT the thread ID!
 */
int
pthread_create(pthread_t *tid, pthread_attr_t *attr,
	       void *(*func)(void *), void *arg)
{
    DWORD dwTid;
#if defined(_MTx)
    /* 
     * uintptr_t _beginthreadex( 
     *   void *security,
     *   unsigned stack_size,
     *   unsigned ( *start_address )( void * ),
     *   void *arglist,
     *   unsigned initflag,
     *   unsigned *thrdaddr );
     */
#define myTHREAD_START_ROUTINE unsigned int (__stdcall *)(void *)
    *tid = (pthread_t *)_beginthreadex(NULL, 0, (myTHREAD_START_ROUTINE)func,
				       arg, 0, &dwTid);
#else /* !defined(_MTx) */
    /*
     * Use CreateThread so we have a real thread handle
     * to synchronize on
     * HANDLE WINAPI CreateThread(
     *  _In_opt_   LPSECURITY_ATTRIBUTES lpThreadAttributes,
     *  _In_       SIZE_T dwStackSize,
     *  _In_       LPTHREAD_START_ROUTINE lpStartAddress,
     *  _In_opt_   LPVOID lpParameter,
     *  _In_       DWORD dwCreationFlags,
     *  _Out_opt_  LPDWORD lpThreadId
     * );
     */
    *tid = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) func,
			   arg, 0, &dwTid);
#endif /* defined(_MTx) */
    if (*tid == NULL) {
	return GetLastError();
    }
    return PTHREAD_NORMAL_EXIT;
}

void
pthread_exit(void *status)
{
#if defined(_MTx)
    /* 
     * void _endthreadex(unsigned retval);
     */
    _endthreadex( (unsigned)status );
#else /* !defined(_MTx) */
    ExitThread( (DWORD)status );
#endif /* defined(_MTx) */
}

int
pthread_mutex_init(pthread_mutex_t * lock, void *attr)
{
    *lock = CreateMutex(NULL, FALSE, NULL);

    if (*lock == NULL) {
	return GetLastError();
    }
    return PTHREAD_NORMAL_EXIT;
}

/* 
 * the diff b/w this and mutex_lock is that this one returns
 * if any thread including itself has the mutex object locked
 * (man pthread_mutex_trylock on Solaris)
 */
int
pthread_mutex_trylock(pthread_mutex_t *lock)
{
    DWORD dw = WaitForSingleObject (*lock, INFINITE);

    return PTHREAD_NORMAL_EXIT;
}

int
pthread_mutex_lock(pthread_mutex_t * lock)
{
    DWORD dw = WaitForSingleObject (*lock, INFINITE);

    switch (dw) {
	case WAIT_ABANDONED:    /* owning thread gone without unlocking */
	case WAIT_TIMEOUT:  
	    /* should never occur in this case since we called 
	     * with INFINITE time */
	    break;
	case WAIT_FAILED: /* TODO - set errno */
	    return 1;
    }
    return PTHREAD_NORMAL_EXIT;
}

int
pthread_mutex_unlock(pthread_mutex_t * lock)
{
    ReleaseMutex (*lock);
    return PTHREAD_NORMAL_EXIT;
}

/* Note: This should return pthread_t, but cannot due to mismatch! */
unsigned long
pthread_self()
{
    return (unsigned long)GetCurrentThreadId();
}

int
pthread_join(pthread_t thread, void **exit_value)
{
    if (GetCurrentThread() == thread) {
	return -1;
    }

    WaitForSingleObject((HANDLE)thread, INFINITE);

    if (exit_value) {
	*exit_value = PTHREAD_NORMAL_EXIT;
    }
    return PTHREAD_NORMAL_EXIT;
}

int
win32_open(char *name, int oflags, int perm)
{
    HANDLE Handle;
    DWORD flags = 0;
    DWORD DesiredAccess;
    DWORD Disposition;
    DWORD ShareMode = (FILE_SHARE_READ | FILE_SHARE_WRITE);

    if (oflags & O_RDONLY) {
	DesiredAccess = FILE_READ_DATA;
    } else if (oflags & O_WRONLY) {
	DesiredAccess = FILE_WRITE_DATA;
    } else {
	DesiredAccess = (FILE_READ_DATA | FILE_WRITE_DATA);
    }

    if (oflags & O_CREAT) {
	Disposition = CREATE_ALWAYS; // OPEN_ALWAYS;
    } else {
	Disposition = OPEN_EXISTING;
    }

    /*
     * http://msdn.microsoft.com/en-us/library/windows/desktop/aa363858(v=vs.85).aspx
     *
     * HANDLE WINAPI CreateFile(
     *  _In_      LPCTSTR lpFileName,
     *  _In_      DWORD dwDesiredAccess,
     *  _In_      DWORD dwShareMode,
     *  _In_opt_  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
     *  _In_      DWORD dwCreationDisposition,
     *  _In_      DWORD dwFlagsAndAttributes,
     *  _In_opt_  HANDLE hTemplateFile
     *);
     */
    Handle = CreateFile (name, DesiredAccess, ShareMode,
			 NULL, Disposition, flags, NULL);

    if (Handle == INVALID_HANDLE_VALUE) {
	return(FAILURE);
    }
    return((int) Handle);
}

int
win32_read(HANDLE handle, char *buffer, size_t size)
{
    DWORD bytesRead;
    BOOL op;

    op = ReadFile(handle, buffer, (DWORD)size, &bytesRead, NULL);
    if (!op) {
	bytesRead = FAILURE:
    }
    return( (ssize_t)(int)bytesRead );
}

int
win32_write(HANDLE handle, char *buffer, size_t size)
{
    DWORD bytesWritten;
    BOOL op;

    op = WriteFile(handle, buffer, (DWORD)size, &bytesWritten, NULL);
    if (!op) {
	bytesWritten = FAILURE;
    }
    return( (ssize_t)(int)bytesWritten );
}

/* Do not simply redefine SEEK_XXX, they may be macros already */
static int seek_map[] = { FILE_BEGIN, FILE_CURRENT, FILE_END };

/*
 * Note that this is a 64-bit seek, Offset_t better be 64 bits
 */
Offset_t
win32_lseek(HANDLE handle, Offset_t off, int whence) 
{
    LARGE_INTEGER li;
    li.QuadPart = off;
    li.LowPart = SetFilePointer (handle, li.LowPart, &li.HighPart,
				 seek_map[whence]);
    if (li.LowPart == 0xffffffff && GetLastError() != NO_ERROR)	{
	li.QuadPart = -1;
    }
    return li.QuadPart;
}

int
win32_pread(HANDLE handle, char *buffer, size_t size, Offset_t offset)
{
    DWORD bytesRead;
    OVERLAPPED ol;
    BOOL res;
    LARGE_INTEGER li;

    li.QuadPart = offset;
    ol.Offset = li.LowPart;
    ol.OffsetHigh = li.HighPart;
    ol.hEvent = NULL;

    res = ReadFile(handle, buffer, (DWORD)size, &bytesRead, &ol);
    if (!res) {
	if (GetLastError() == ERROR_IO_PENDING) {
	    res = GetOverlappedResult(handle, &ol, &bytesRead, TRUE);
	}
	if (!res) {
	    bytesRead = FAILURE;
	}
    }

    if (ol.hEvent!=NULL) {
	CloseHandle(ol.hEvent);
    }
    return( (ssize_t)(int)bytesRead );
}

int
win32_pwrite(HANDLE handle, char *buffer, size_t size, Offset_t offset)
{
    DWORD bytesWrite;
    OVERLAPPED ol;
    BOOL res;
    LARGE_INTEGER li;

    li.QuadPart = offset;
    ol.Offset = li.LowPart;
    ol.OffsetHigh = li.HighPart;
    ol.hEvent = NULL;

    res = WriteFile(handle, buffer, size, &bytesWrite, &ol);
    if (!res) {
	if (GetLastError() == ERROR_IO_PENDING) {
	    res = GetOverlappedResult(handle, &ol, &bytesWrite, TRUE);
	}
	if (!res) {
	    bytesWrite = FAILURE;
	}
    }
    if (ol.hEvent!=NULL) {
	CloseHandle(ol.hEvent);
    }
    return( (ssize_t)(int)bytesWrite );
}

HANDLE
win32_dup(HANDLE handle)
{
    HANDLE hDup = (HANDLE)-1;

    /* http://msdn.microsoft.com/en-us/library/ms724251(VS.85).aspx */

    if ( !DuplicateHandle(GetCurrentProcess(), 
			  handle, 
			  GetCurrentProcess(),
			  &hDup, 
			  0,
			  FALSE,
			  DUPLICATE_SAME_ACCESS) ) {
	DWORD dwErr = GetLastError();
	errno = EINVAL;
    }
    return (hDup);
}

/* ============================================================================== */
/* Functions added from dt code. */

/*
 * resume_thread() - Resume the Specifed Thread.
 *
 * Inputs:
 *	dip = The device information pointer.
 *	thread_handle = Handle to thread to suspend.
 *
 * Return Value:
 *	The resume count, or -1 on failure.
 */
DWORD
resume_thread(dinfo_t *dip, HANDLE thread_handle)
{
    DWORD retval;

    if (dip->di_debug_flag) {
	Printf("Resuming thread %p...\n", thread_handle);
    }
    retval = ResumeThread(thread_handle);
    if (retval == -1) {
	DWORD error = GetLastError();
	/*
	 * Parent thread may be terminating due to signal.
	 */
	if ( (error != ERROR_ACCESS_DENIED) &&
	     (error != ERROR_INVALID_HANDLE) ) {
	    report_error(dip, "ResumeThread() failed", FALSE);
	}
    } else if (dip->di_tDebugFlag) {
	if (retval == 1) {
	    Printf("Suspended thread was restarted!\n");
	} else {
	    Printf("Resume count is %d (still suspended!)\n", retval);
	}
    }
    return(retval);
}

/*
 * suspend_thread() - Suspend the Specifed Thread.
 *
 * Inputs:
 *	dip = The device information pointer.
 *	thread_handle = Handle to thread to suspend.
 *
 * Return Value:
 *	The previous suspend count, or -1 on failure.
 */
DWORD
suspend_thread(dinfo_t *dip, HANDLE thread_handle)
{
    DWORD retval;
    /*
     * Suspend/Resume parent to emulate Unix signaling.
     * Main reason is to keep parent from exiting on us!
     * With native Windows, we're called from a separate thread.
     */
    if (dip->di_debug_flag) {
	Printf("Suspending thread %p...\n", thread_handle);
    }
    retval = SuspendThread(thread_handle);
    if (retval == -1) {
	DWORD error = GetLastError();
	/*
	 * Parent thread may be terminating due to signal.
	 */
	if ( (error != ERROR_ACCESS_DENIED) &&
	     (error != ERROR_INVALID_HANDLE) ) {
	    report_error(dip, "SuspendThread() failed", FALSE);
	}
    } else if (dip->di_tDebugFlag) {
	Printf("Suspend count is %d\n", retval);
    }
    return(retval);
}

#if 0
/*
 * TerminateParentThread() - Terminate the Parent Thread.
 *
 * NOTE: This *should* be a generic function!
 * 
 * Inputs:
 * 	dip = The device information pointer.
 *
 * Implicit Inputs:
 *	ParentThread = The parent thread handle.
 *	ParentThreadId = The parent thread ID.
 *
 * Return Value:
 *	Void
 */
void
TerminateParentThread(dinfo_t *dip)
{
    HANDLE thread_handle = ParentThread;
    DWORD thread_id = ParentThreadId;

    ParentThreadId = 0;
    ParentThread = (HANDLE) 0;	/* Help avoid recursion until locks added. */
    if (dip->di_debug_flag) {
	Printf("Terminating parent thread %d...\n", thread_id);
    }
    /*
     * BEWARE: I found these warnings here...
     * URL: http://msdn.microsoft.com/en-us/library/ms686717(VS.85).aspx
     *
     * TerminateThread is a dangerous function that should only be used in the
     * most extreme cases. You should call TerminateThread only if you know exactly
     * what the target thread is doing, and you control all of the code that the
     * target thread could possibly be running at the time of the termination.
     *
     * For example, TerminateThread can result in the following problems:
     *  - If the target thread owns a critical section, the critical section
     *    will not be released. 
     *  - If the target thread is allocating memory from the heap, the heap lock
     *    will not be released. 
     *  - If the target thread is executing certain kernel32 calls when it is
     *    terminated, the kernel32 state for the thread's process could be inconsistent. 
     *  - If the target thread is manipulating the global state of a shared DLL, the
     *    state of the DLL could be destroyed, affecting other users of the DLL. 
     *
     * A user added these additional warnings:
     * The warnings above are a gross understatement. TerminateThread is NOT a
     * solution for shutting down worker threads. You will break your app, and
     * it will fail randomly.
     *
     * Set a flag for the thread to watch for and then voluntarily shut itself down.
     * If your threads are hanging, fix the hang. Involuntarily killing threads only
     * makes things worse.
     *
     * Robin: In general, I'm finding this to be TRUE, so should be last resort!
     */
    if ( !TerminateThread(thread_handle, ERROR_SUCCESS) ) {
	/*
	 * During Ctrl/C aborting, sometimes the parent thread is gone,
	 * while we're running in the signal handler thread.
	 */
	if ( (GetLastError() != ERROR_INVALID_HANDLE) || dip->di_debug_flag) {
	    report_error(dip, "TerminateThread() failed", TRUE);
	}
    } else {
	DWORD thread_status;
	/*
	 * The terminated thread can still be active, so wait for it!
	 * Not waiting, can lead to unexpected things (like hangs).
	 */
	if (dip->di_debug_flag) {
	    Printf("Waiting for parent thread %d to exit...\n", thread_id);
	}
	do {
	    if ( !GetExitCodeThread(thread_handle, &thread_status) ) {
		report_error(dip, "GetExitCodeThread() failed", TRUE);
		break;
	    }
	} while (thread_status == STILL_ACTIVE);
	if (dip->di_debug_flag) {
	    Printf("Parent thread exited with status %d\n", thread_status);
	    if (thread_status) abort();
	}
    }
    (void)CloseHandle(thread_handle);
    return;
}
#endif /* 0 */

hbool_t
IsDriveLetter(char *device)
{
    /* Check for drive letters "[a-zA-Z]:" */
    if ((strlen(device) >= 2) && (device[1] == ':') &&
        ((device[0] >= 'a') && (device[0] <= 'z') ||
         (device[0] >= 'A') && (device[0] <= 'Z'))) {
        return(True);
    }
    return(False);
}

char *
setup_scsi_device(char *path)
{
    char *scsi_device;

    scsi_device = Malloc(DEV_DIR_LEN * 2);
    if (scsi_device == NULL) return(scsi_device);
    /* Format: \\.\[A-Z]: */
    strcpy(scsi_device, DEV_DIR_PREFIX);
    scsi_device[DEV_DIR_LEN] = path[0];		/* The drive letter. */
    scsi_device[DEV_DIR_LEN+1] = path[1];	/* The ':' terminator. */
    return(scsi_device);
}

hbool_t
FindMountDevice(dinfo_t *dip, char *path, hbool_t debug)
{
    hbool_t match = False;
    char *sdsf = NULL;

    if ( IsDriveLetter(path) ) {
	match = True;
	sdsf = setup_scsi_device(path);
    } else if ( EQL(path, "\\\\", 2) || EQL(path, "//", 2) ) {
	;	/* Skip UNC paths! */
    } else {
	char path_dir[PATH_BUFFER_SIZE];
	char *path_dirp;
	memset(path_dir, '\0', sizeof(path_dir));
	path_dirp = getcwd(path_dir, sizeof(path_dir));
	if (path_dirp == NULL) return(match);
	if ( IsDriveLetter(path_dirp) ) {
	    match = True;
	    sdsf = setup_scsi_device(path_dirp);
	}
    }
    if (match == True) {
	dip->di_mounted_from_device = strdup(sdsf);
	//dip->di_mounted_on_dir = strdup(mounted_path);
    }
    return(match);
}

char *
os_ctime(time_t *timep, char *time_buffer, int timebuf_size)
{
    int error;

    error = ctime_s(time_buffer, timebuf_size, timep);
    if (error) {
	tPerror(error, "_ctime_s() failed");
	(int)sprintf(time_buffer, "<no time available>\n");
    }
    return(time_buffer);
}

char *
os_gethostname(void)
{
    char hostname[MAXHOSTNAMELEN];
    DWORD len = MAXHOSTNAMELEN;

    if ( (GetComputerNameEx(ComputerNameDnsFullyQualified,
				hostname, &len)) == 0) {
	  os_perror("GetComputerNameEx() failed");
	  return(NULL);
    }
    return ( strdup(hostname) );
}

char *
os_getusername(void)
{
    DWORD size = STRING_BUFFER_SIZE;
    TCHAR username[STRING_BUFFER_SIZE];

    if ( !GetUserName(username, &size) ) {
	os_perror("GetUserName() failed");
	return(NULL);
    }
    return ( strdup(username) );
}

/*
 * Taken from URL: 
 *  http://msdn.microsoft.com/en-us/library/windows/desktop/ms686277(v=vs.85).aspx
 */
#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
# define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
# define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif
 
int
gettimeofday(struct timeval *tv, struct timezone *tz)
{
    FILETIME ft;
    unsigned __int64 tmpres = 0;
    static int tzflag;

    if (NULL != tv) {
	/* Precision is 10-15ms. */
	GetSystemTimeAsFileTime(&ft);
	tmpres |= ft.dwHighDateTime;
	tmpres <<= 32;
	tmpres |= ft.dwLowDateTime;

	/*converting file time to unix epoch*/
	tmpres -= DELTA_EPOCH_IN_MICROSECS; 
	tmpres /= 10;  /*convert into microseconds*/
	tv->tv_sec = (long)(tmpres / 1000000UL);
	tv->tv_usec = (long)(tmpres % 1000000UL);
    }

    if (NULL != tz) {
	if (!tzflag) {
	    _tzset();
	    tzflag++;
	}
	tz->tz_minuteswest = _timezone / 60;
	tz->tz_dsttime = _daylight;
    }
    return 0;
}
