/****************************************************************************
 *									    *
 *			  COPYRIGHT (c) 1988 - 2013			    *
 *			   This Software Provided			    *
 *				     By					    *
 *			  Robin's Nest Software Inc.			    *
 *									    *
 * Permission to use, copy, modify, distribute and sell this software and   *
 * its documentation for any purpose and without fee is hereby granted,	    *
 * provided that the above copyright notice appear in all copies and that   *
 * both that copyright notice and this permissikn notice appear in the	    *
 * supporting documentation, and that the name of the author not be used    *
 * in advertising or publicity pertaining to distribution of the software   *
 * without specific, written prior permission.				    *
 *									    *
 * THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, 	    *
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN	    *
 * NO EVENT SHALL HE BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL   *
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR    *
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS  *
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF   *
 * THIS SOFTWARE.							    *
 *									    *
 ****************************************************************************/
/*
 * Modification History:
 *
 * July 27th, 2012 by Robin T. Miller
 * 	Add SCSI support.
 *
 * October 29th, 2007 by Robin T. Miller
 *	Modify Windows times() definition to return a clock ticks value,
 * which is consistent with what's returned by standard Unix times() API.
 *
 * January 19th, 2005 by Nagendra Vadlakunta
 * 	Added AIO and IA64 support for Windows.
 *
 * June 22nd, 2004 by Robin Miller.
 *      Added support for triggers on corruption.
 *
 * September 27th, 2003 by Robin Miller.
 *      Added support for AIX.
 *
 * March 14th, 2003 by Robin Miller.
 *	Add declarations for slice and prefix variables.
 *
 * November 14th, 2002 by Robin Miller.
 *	Add support for 32-bit HP-UX compilation.
 *
 * February 23rd, 2002 by Robin Miller.
 *	Make porting changes for HP-UX IA64.
 *
 * February 1st, 2002 by Robin Miller.
 *	Make porting changes necessary for Solaris 8.
 *
 * August 31st, 2001 by Robin Miller.
 *	Increase size of di_capacity from 32 to 64 bits in preparation
 * for larger capacity volumes, esp. logical volumes on array controllers.
 *
 * January 24th, 2001 by Robin Miller.
 *	For Windows/NT, use /dev/[n]rmt instead of "tapeN" for tape
 * device names, since this is the name used when tapes are mounted
 * using the Cygnus toolkit.
 *
 * January 14th, 2001 by Robin Miller.
 *	Added support for multiple volumes option.
 *
 * January 11th, 2001 by Robin Miller.
 *	Modify conditionals so Windows tape devices are /dev/rmtN
 * and /dev/nrmtN (norewind)  which the latest Cygnus README states.
 *
 * December 30th, 2000 by Robin Miller.
 *	Make changes to build using MKS/NuTCracker product.
 *
 * April 17th, 2000 by Robin Miller.
 *	Added device path failure flag, to force re-open of tapes
 * on Wave4 clusters which forces alternate paths or servers to be
 * located by CAM or DRD.
 *
 * January 22nd, 2000 by Robin Miller.
 *	Added support for Cygwin tape devices for Windows/NT.
 *
 * August 6th, 1999 by Robin Miller.
 *      Better parameterizing of "long long" printf formatting.
 *
 * July 29, 1999 by Robin Miller.
 *	Merge in changes made to compile on FreeBSD.
 *
 * July 22nd, 1999 by Robin Miller.
 *	Added support for IOT (DJ's) test pattern.
 * 
 * May 27, 1999 by Robin Miller.
 *	Added support for micro-second delays.
 *
 * April 8, 1999 by Robin Miller.
 *	Merge in Jeff Detjen's changes for table()/sysinfo timing.
 *
 * December 21, 1998 by Robin Miller.
 *	For DUNIX, changes to handle tape resets.
 *
 * April 29, 1998 by Robin Miller.
 *	Add support for an alternate device directory, e.g. "/devices/",
 * as a prefix to physical device names.  Just checking for "/dev...",
 * described below, is too general and sure to get me into trouble.
 *
 * April 25, 1998 by Robin Miller.
 *	Change device prefix to account for "/dev" or "/devices" (steel),
 * since this knowledge is used to determine if a device should exist
 * (to avoid creating files in the /dev directory), as well as whether
 * the PID is appended during multiple process testing.
 *
 * February 28, 1996 by Robin Miller.
 *	Added support for copying and verifying device/files.
 *
 * December 19, 1995 by Robin Miller
 *      Conditionalize for Linux Operating System.
 *
 * September 23, 1994 by Robin Miller.
 *      Make changes necessary to build on QNX 4.21 release.
 *
 * September 5, 1992 by Robin Miller.
 *	Initial port to QNX 4.1 Operating System.
 */
#if defined(AIX)
/*
 * These should come from sys/types.h, but I can't seem to find the
 * magic compile options to get these defined properly, so cludge it!
 *
 * Failure to define these results in numerous errors here using cc_r:
 * /usr/include/pthread.h:666: error: parse error before '*' token
 *
 * FWIW: I'm fairly certain the wrong include files are getting picked up!
 */
typedef struct {
#ifdef __64BIT__
        long    __sp_word[3];
#else
        int     __sp_word[6];
#endif /* __64BIT__ */
} pthread_spinlock_t;
typedef struct {
#ifdef __64BIT__
        long    __br_word[5];
#else
        int     __br_word[8];
#endif /* __64BIT__ */
} pthread_barrier_t;
typedef void *pthread_barrierattr_t;

#endif /* defined(AIX) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h> 				/* CLK_TCK defined here */
#include <math.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#if defined(WIN32)
//#  define TIMER_METHOD 1
#  if defined(TIMER_METHOD)
     /* For CreateWaitableTimer() & SetWaitableTimer() */
#    define _WIN32_WINNT 0x0500
#  endif /* defined(TIMER_METHOD) */
#  include<windows.h>
#  include<io.h>
#  include<direct.h>
#  include<process.h>
#  include "dtwin.h"
#else /* !defined(WIN32) */
#  if defined(AIO)
#    include <aio.h>
#  endif /* defined(AIO) */
#  include <pthread.h>
#  include <unistd.h>
#  include <termios.h>
#  include <sys/times.h>
#  if !defined(NOSYSLOG)
#    define SYSLOG 1
#    include <syslog.h>
#  endif /* defined(NOSYSLOG) */
#  endif /* defined(WIN32) */
#if defined(__QNXNTO__)
#  include <unix.h>
#endif

/*
 * Definition to control timestamps (may affect performance).
 */
#define TIMESTAMP       1

/* TODO: Cleanup this junk! Really still needed? */
#if !defined(HZ)
#  if defined(sun) || defined(__WIN32__) || defined(SCO) || defined(HP_UX)
#    include <sys/param.h>
#  endif /* defined(sun) */
#  if defined(CLK_TCK) && !defined(HZ)
#    define HZ		CLK_TCK
#  else
#    if !defined(HZ)
#      define HZ		256
#    endif /* !defined(HZ) */
#    if !defined(CLK_TCK)
#      define CLK_TCK	HZ
#    endif /* !defined(CLK_TCK) */
#  endif /* defined(CLK_TCK) */
#endif /* !defined(HZ) */

#include "common.h"

#define DIR_PREFIX	"d"
#define DEFAULT_IOTUNE_FILE	TEMP_DIR_NAME"dtiotune.txt"

#if !defined(MAXHOSTNAMELEN)
#   define MAXHOSTNAMELEN 256
#endif
#if !defined(MAXBADBLOCKS)
#    define MAXBADBLOCKS 10
#endif

#define DEFAULT_COMPARE_FLAG	TRUE
#define DEFAULT_LBDATA_FLAG	FALSE
#define DEFAULT_MOUNT_LOOKUP	TRUE
#define DEFAULT_TIMESTAMP_FLAG	FALSE
#define DEFAULT_UNIQUE_PATTERN	TRUE
#define DEFAULT_USER_PATTERN	FALSE
#define DEFAULT_HEALTH_CHECK	TRUE
#define DEFAULT_HEALTH_ERRORS	FALSE
#define DEFAULT_HEALTH_LENGTH	4096
#define DEFAULT_HEALTH_RETRIES	10
#define DEFAULT_HEALTH_TIMEOUT	(10 * MSECS)
#define DEFAULT_SCSI_FLAG	TRUE
#define DEFAULT_SCSI_ERRORS	FALSE
#define DEFAULT_VERBOSE_FLAG	TRUE
#define DEFAULT_VERIFY_FLAG	TRUE

#define DEFAULT_DUMP_LIMIT	BLOCK_SIZE	/* Default dump limit.		*/
#define DEFAULT_ERROR_LIMIT	1		/* Default error limit.		*/
#define DEFAULT_FILE_LIMIT	0		/* Default file limit.		*/
#define DEFAULT_PASS_LIMIT	1		/* Default pass limit.		*/
/*
 * This controls the default frequency of checking the IO tune file.
 * This also controls the IO tuning thread run interval (see below).
 *
 * Note: Currently the IO tune file is serviced from the monitoring thread,
 * and this threads' interval is affected by noprog or keepalive intervals.
 */
#define DEFAULT_IOTUNE_FREQ	3		/* Default tuning frequency.	*/

#define DEFAULT_CANCEL_DELAY	3		/* Time to delay before cancel.	*/
#define DEFAULT_KILL_DELAY	3		/* Time to delay before kill.	*/
#define DEFAULT_TERM_DELAY	1		/* Child terminate delay count.	*/
#define DEFAULT_OPEN_DELAY	0		/* Delay before opening file.	*/
#define DEFAULT_CLOSE_DELAY	0		/* Delay before closing file.	*/
#define DEFAULT_END_DELAY	0		/* Delay between multiple passes*/
#define DEFAULT_READ_DELAY	0		/* Delay before reading record.	*/
#define DEFAULT_START_DELAY	0		/* Delay before starting test.	*/
#define DEFAULT_WRITE_DELAY	0		/* Delay before writing record.	*/
#define DEFAULT_IOTUNE_DELAY DEFAULT_IOTUNE_FREQ/* The I/O tuning interval.	*/
#define DEFAULT_IOTUNE_FLAG	TRUE		/* The I/O tuning control flag.	*/
#define DEFAULT_IOTUNE_ADJUST	1000		/* The I/O tuning adjustment.	*/
#define DEFAULT_IOTUNE_DIVISOR	3		/* The I/O tuning scale divisor.*/
#define DEFAULT_IOTUNE_MIN_CPU	40		/* The mimimum CPU busy value.	*/
#define DEFAULT_IOTUNE_MAX_CPU	60		/* The maximum CPU busy value.	*/

#define AIO_BUFS	8			/* Default number AIO buffers.	*/
#define IOT_SEED	0x01010101		/* Default seed for IOT pattern	*/
#define RETRY_DELAY	5			/* Default retry delay (secs).	*/
#define RETRY_ENTRIES	5
/* Note: (5 * 60) = 300 seconds or 5 minutes! */
#define RETRY_LIMIT	60

/*
 * Default random block sizes (match up with sio).
 */
#define MIN_RANDOM_SIZE		512		/* Minimum random size.	*/
#define MAX_RANDOM_SIZE		(256*KBYTE_SIZE)/* Maximum random size.	*/

/*
 * Note: Now that long file paths are created, this string buffer must
 *	 be large enough for message text *and* the long file names!
 */
#undef STRING_BUFFER_SIZE
#define STRING_BUFFER_SIZE (PATH_BUFFER_SIZE+256)/* String buffer size.	*/

#define HANDLE_TERMINATE(dip) if (terminating_flag) handle_terminating(NULL)
//#define HANDLE_TERMINATE if (terminating_flag) pthread_exit(NULL);
#if defined(WIN32)
#  define MAX_PROCS       MAXIMUM_WAIT_OBJECTS	/* Maximum processes.	*/
#  define MAX_SLICES      MAXIMUM_WAIT_OBJECTS	/* Maximum processes.	*/
#  define TERM_WAIT_TIMEOUT	10		/* Wait timeout (secs).	*/
#  define TERM_WAIT_RETRIES	6		/* Time to retry wait.	*/
#  define TERM_WAIT_ARETRIES	1		/* Abnormal wait retry.	*/
#else /* !defined(WIN32) */
#  define MAX_PROCS	256			/* Maximum processes.	*/
#  define MAX_SLICES	256			/* Maximum slices.	*/
#endif /* defined(WIN32) */
#define USE_PATTERN_BUFFER			/* Use pattern buffer.	*/

#define RANDOM_DELAY_VALUE 0xFFFFFFFF		/* Randomized delay.	*/

#define DEFAULT_PATTERN	 0x39c39c39U	/* Default data pattern.	*/
#define ASCII_PATTERN	 0x41424344U	/* Default ASCII data pattern.	*/

//#define DEF_LOG_BUFSIZE	2048	/* Large enough for all stats.	*/
#define DEF_LOG_BUFSIZE	(PATH_BUFFER_SIZE * 2) /* File name + stats!	*/

#if defined(BUFSIZ) && (BUFSIZ > DEF_LOG_BUFSIZE)
#  define LOG_BUFSIZE	BUFSIZ		/* The log file buffer size.	*/
#else /* !defined(BUFSIZ) */
#  define LOG_BUFSIZE	DEF_LOG_BUFSIZE	/* The log file buffer size.	*/
#endif /* defined(BUFSIZ) */

#if defined(SCSI)
#  include "libscsi.h"
#  include "inquiry.h"
#endif /* defined(SCSI) */

/*
 * The buffer pad bytes are allocated at the end of all data buffers,
 * initialized with the inverted data pattern, and then checked after
 * each read operation to ensure extra bytes did not get transferred
 * at the end of buffer.  This test is necessary, since quite often
 * we've seen data corruption (extra bytes) due to improper flushing
 * of DMA FIFO's, or other coding errors in our SCSI/CAM sub-system.
 */
#define PADBUFR_SIZE	sizeof(u_int32)	/* The data buffer pad size.	*/
					/* MUST match pattern length!!!	*/

/*
 * The buffer rotate size are used to force unaligned buffer access
 * by rotating the starting buffer address through the sizeof(ptr).
 * This feature has been very useful in forcing drivers through special
 * code to handle unaligned addresses & buffers crossing page boundaries.
 */
#define ROTATE_SIZE	sizeof(char *)	/* Forces through all ptr bytes	*/

/*
 * 'dt' specific exit status codes:
 */
#define END_OF_FILE	254			/* End of file code.	*/
#define FATAL_ERROR	255			/* Fatal error code.	*/

#define get_lbn(bp)	( ((u_int32)bp[3] << 24) | ((u_int32)bp[2] << 16) | \
			  ((u_int32)bp[1] << 8) | (u_int32)bp[0])

typedef unsigned int	mytime_t;
typedef volatile time_t	vtime_t;

typedef enum bfmt {DEC_FMT, HEX_FMT} bfmt_t;
typedef enum dfmt {NONE_FMT, BYTE_FMT, SHORT_FMT, WORD_FMT, QUAD_FMT} dfmt_t;

typedef enum opt {OFF, ON, OPT_NONE} opt_t;
typedef enum flow {FLOW_NONE, CTS_RTS, XON_XOFF} flow_t;
typedef enum stats {COPY_STATS, READ_STATS, RAW_STATS, WRITE_STATS, TOTAL_STATS, VERIFY_STATS} stats_t;
typedef enum dispose {DELETE_FILE, KEEP_FILE, KEEP_ON_ERROR} dispose_t;
typedef enum file_type {INPUT_FILE, OUTPUT_FILE} file_type_t;
typedef enum test_mode {READ_MODE, WRITE_MODE} test_mode_t;
typedef enum onerrors {ABORT, CONTINUE} onerrors_t;
typedef enum iodir {FORWARD, REVERSE} iodir_t;
typedef enum iomode {COPY_MODE, TEST_MODE, VERIFY_MODE} iomode_t;
typedef enum iotype {SEQUENTIAL_IO, RANDOM_IO} iotype_t;
/* 
 * Buffering Modes: 
 * buffered = normal FS buffering, unbuffered = Direct I/O
 * readcache = disabled write caching, writecache = disable read caching 
 */
typedef enum bufmodes {
    NONE_SPECIFIED = 0,		/* No buffering mode specified.		*/
    BUFFERED_IO = 1,		/* Normal FS buffering (buffer cache).	*/
    UNBUFFERED_IO = 2,		/* No buffering (full direct I/O).	*/
    CACHE_READS = 3,		/* Cache reads (write cache disabled).	*/
    CACHE_WRITES = 4,		/* Cache writes (reads cache disabled).	*/
    NUM_BUFMODES = 4
} bufmodes_t;

/*
 * History Information:
 */
typedef struct history {
    test_mode_t	hist_test_mode;		/* The I/O mode.       		*/
    u_long	hist_file_number;	/* The file number.		*/
    u_long	hist_record_number;	/* The record number.		*/
    OFF_T	hist_file_offset;	/* The file offset.		*/
    size_t	hist_request_size;	/* Size of the request.		*/
    ssize_t	hist_transfer_size;	/* Size of the transfer.	*/
    u_char	*hist_request_data;	/* First 'N' bytes of data.	*/
    struct timeval hist_timer_info;	/* Timer info in sec/usecs.	*/
} history_t;

#define DEFAULT_HISTORY_DATA_SIZE	32

/*
 * The operation type is used with no-progress option to report operation.
 */
typedef enum optype {
    NONE_OP, OPEN_OP, CLOSE_OP, READ_OP, WRITE_OP, IOCTL_OP, FSYNC_OP, MSYNC_OP, AIOWAIT_OP, NUM_OPS
} optype_t;
typedef struct optiming {
    optype_t	opt_optype;		/* The operation type.      */
    bool	opt_timing_flag;	/* The timing control flag. */
    char	*opt_name;		/* The operation name.      */
} optiming_t;
extern optiming_t optiming_table[];

typedef enum statslevel {STATS_BRIEF, STATS_FULL, STATS_NONE} statslevel_t;
typedef enum stats_value {ST_BYTES, ST_BLOCKS, ST_FILES, ST_RECORDS, ST_OFFSET} stats_value_t;
typedef enum trigger_type {
    TRIGGER_NONE, TRIGGER_BR, TRIGGER_BDR, TRIGGER_LR, TRIGGER_SEEK, TRIGGER_CMD, TRIGGER_ZAPI_PANIC,
    TRIGGER_PANIC_NODE, TRIGGER_PANIC_ALL_NODES, TRIGGER_DUMP_RASTRACE, TRIGGER_INVALID=-1
} trigger_type_t;
typedef enum trigger_action {
    TRIGACT_CONTINUE = 0, TRIGACT_TERMINATE = 1, TRIGACT_SLEEP = 2, TRIGACT_ABORT = 3
} trigger_action_t;

#define NUM_TRIGGERS	3

typedef struct trigger_data {
    enum trigger_type td_trigger;	/* Trigger for corruptions.   */
    char	*td_trigger_cmd;	/* The users' trigger command.  */
    char	*td_trigger_args;	/* Extra user trigger arguments	*/
} trigger_data_t;

typedef enum logLevel {
	logLevelCrit = -1,
	logLevelError,
	logLevelInfo,
	logLevelWarn,
	logLevelDiag,
	logLevelQdiag,
	logLevelLog,
	logLevelSpecial,
	logLevelTrace
} logLevel_t;

/*
 * Flags to control print behaviour:
 */
#define PRT_NOFLUSH	0x01
#define PRT_NOIDENT	0x02
#define PRT_NOLEVEL	0x04

/*
 * Declare External Test Functions:
 */
#define NOFUNC		(int (*)()) 0	/* No test function exists yet. */
#define NoFd          INVALID_HANDLE_VALUE

extern int nofunc();			/* Stub return (no test func).	*/
extern struct dtfuncs generic_funcs;	/* Generic test functions.	*/
#if defined(AIO)
extern struct dtfuncs aio_funcs;	/* POSIX AIO test functions.	*/
#endif /* defined(AIO) */
#if defined(MMAP)
extern struct dtfuncs mmap_funcs;	/* Memory map test functions.	*/
#endif /* defined(MMAP) */

/*
 * Define Device Types:
 */
enum devtype {DT_BLOCK, DT_CHARACTER, DT_COMM, DT_DISK,
	      DT_GRAPHICS, DT_MEMORY, DT_MMAP, DT_NETWORK,
	      DT_PIPE, DT_PROCESSOR, DT_REGULAR,
	      DT_SOCKET, DT_SPECIAL, DT_STREAMS, DT_TAPE,
	      DT_DIRECTORY, DT_UNKNOWN };
struct dtype {
	char	*dt_type;
	enum	devtype dt_dtype;
};

#define PROC_ALLOC (sizeof(pid_t) * 3)	/* Extra allocation for PID.	*/

/*
 * Definitions for Multiple Processes:
 */
typedef struct dt_procs {
	pid_t	dt_pid;			/* The child process ID.	*/
	int	dt_status;		/* The child exit status.	*/
	bool	dt_active;		/* The process active flag.	*/
	char	*dt_device;		/* The process target device.	*/
#if defined(WIN32)
	PROCESS_INFORMATION *dt_pip;	/* Process information.		*/
#endif /* defined(WIN32) */
} dt_procs_t;

/*
 * Slice Range Definition:
 */
typedef struct slice_info {
	int	slice;			/* Slice number.		*/
	large_t	slice_position;		/* Starting slice position.	*/
	large_t	slice_length;		/* The slice data length.	*/
} slice_info_t;

/*
 * Define File Control Flags:
 */
#define DCF_ACTIVE	1		/* File test is active.		*/

/*
 * Define Device Information:
 */
typedef struct dinfo {
	FILE	*di_efp;		/* Default error data stream.	*/
	FILE	*di_ofp;		/* Default output data stream.	*/
	HANDLE	di_fd;			/* The file descriptor.		*/
	int	di_flags;		/* The file control flags.	*/
	int	di_oflags;		/* The last file open flags.	*/
	char	*di_bname;		/* The base file name.		*/
	char	*di_dname;		/* The /dev device name.	*/
	char	*di_device;		/* The real device name.	*/
	u_int32	di_device_size;		/* Default device block size.	*/
	bool	di_stdin_flag;		/* Presume not reading stdin.	*/
	bool	di_stdout_flag;		/* Presume not writing stdout.	*/
	v_bool	di_terminating;		/* Flag to control terminating.	*/
	int	di_exit_status;		/* The thread exit status.	*/
	/*
	 * Test Information:
	 */
	enum test_mode di_mode;		/* The current test mode.	*/
	enum file_type di_ftype;	/* The file access type.	*/
	struct dtfuncs *di_funcs;	/* The test functions to use.	*/
	struct dtype *di_dtype;		/* The device type information.	*/
	/* For parsing and both input/output devices (copy/verify). */
	struct dtype *di_input_dtype;	/* The input device type info.	*/
	struct dtype *di_output_dtype;	/* The output device type info.	*/
	enum iodir  di_io_dir;		/* Default is forward I/O.	*/
	enum iomode di_io_mode;		/* Default to testing mode.	*/
	enum iotype di_io_type;		/* Default to sequential I/O.	*/
	enum dispose di_dispose_mode;	/* Output file dispose mode.	*/
	enum onerrors di_oncerr_action;	/* The child error action.	*/
					/* Error limit controls tests.	*/
	enum statslevel di_stats_level;	/* Type of statistics to report.*/
	/*
	 * Test Control Information:
	 */
	size_t	di_block_size;		/* Default block size to use.	*/
	size_t	di_incr_count;		/* Record increment byte count.	*/
	size_t	di_min_size;		/* The minimum record size.	*/
	size_t	di_max_size;		/* The maximum record size.	*/
	bufmodes_t di_buffer_mode;	/* The current buffering mode.	*/
	char	*di_bufmode_type;	/* The buffering mode type.	*/
	bool	di_closing;		/* The device is being closed.	*/
	bool	di_compare_flag;	/* Controls data comparisions.	*/
	bool	di_existing_file;	/* The file already exists.	*/
	vu_long	di_error_count;		/* Number of errors detected.	*/
	u_long	di_error_limit;		/* Number of errors tolerated.	*/
	bool	di_flushing;		/* The file is being flushed.	*/
	u_int32	di_dsize;		/* The device block size.	*/
	u_int32	di_rdsize;		/* The real device block size.	*/
        u_int   di_qdepth;              /* The device queue depth.      */
	large_t	di_capacity;		/* The device capacity (blocks)	*/
	v_bool	di_end_of_file;		/* End of file was detected.	*/
	v_bool	di_end_of_logical;	/* End of logical tape detected	*/
	v_bool	di_end_of_media;	/* End of media was detected.	*/
	v_bool	di_beginning_of_file;	/* Beginning of file/media flag	*/
	v_bool	di_no_space_left;	/* The "no space left" flag.	*/
	bool	di_eof_processing;	/* End of file proessing.	*/
	bool	di_eom_processing;	/* End of media processing.	*/
	bool	di_random_io;		/* Random I/O selected flag.	*/
	bool	di_random_access;	/* Random access device flag.	*/
	u_long	di_pass_count;		/* Number of passes completed.	*/
	u_long	di_pass_limit;		/* Default number of passes.	*/
	bool    di_timestamp_flag;	/* Timestamp each data block.   */
	bool	di_verbose_flag;	/* Verbose messages output.	*/
	bool	di_verify_flag;		/* Verify the read/write data.	*/
	bool	di_verify_only;		/* Verify of copied data flag.	*/
	/*
	 * Per Pass Statistics: 
	 */
	v_large	di_dbytes_read;		/* Number of data bytes read.	*/
	v_large	di_dbytes_written;	/* Number of data bytes written.*/
	v_large	di_fbytes_read;		/* Number of file bytes read.	*/
	v_large	di_fbytes_written;	/* Number of file bytes written.*/
	v_large	di_vbytes_read;		/* Number of volume bytes read.	*/
	v_large	di_vbytes_written;	/* Number of volume bytes wrote.*/
	/*
	 * Information to Handle "File System Full":
	 */
	size_t	di_last_write_attempted;/* The last write attempted.	*/
	size_t	di_last_write_size;	/* The last write transferred.	*/
        OFF_T	di_last_write_offset;	/* The last write offset used.	*/
	large_t	di_last_dbytes_written;	/* The last data bytes written.	*/
	large_t	di_last_fbytes_written;	/* The last file bytes written.	*/
	large_t	di_last_vbytes_written;	/* The last volume bytes wrote.	*/
	large_t	di_discarded_write_data;/* Discarded write data bytes.	*/
	/*
	 * Multiple Directory Data:
	 */
	char	*di_dir;		/* The base directory path.	*/
	char	*di_dirpath;		/* The directory path.		*/
	char	*di_dirprefix;		/* The directory prefix.	*/
	char	*di_subdir;		/* The sub-directory path.	*/
	bool	di_dir_created;		/* We created directory flag.	*/
	u_int	di_dir_number;		/* The directory number.	*/
	u_int	di_subdir_number;	/* The subdirectory number.	*/
	u_int	di_subdir_depth;	/* The subdirectory depth.	*/
	u_int	di_last_dir_number;	/* The last directory number.	*/
	u_int	di_last_subdir_number;	/* The subdirectory number.	*/
	u_int	di_last_subdir_depth;	/* The subdirectory depth.	*/
	u_int	di_max_dir_number;	/* The maximum directory.	*/
	u_int	di_max_subdir_number;	/* The maximum subdirectory.	*/
	u_int	di_max_subdir_depth;	/* The maximum subdir depth.	*/
	u_int	di_user_dir_limit;	/* The number of directories.	*/
	u_int	di_user_subdir_depth;	/* The subdirectory depth.	*/
	u_int	di_user_subdir_limit;	/* Number of subdirectories.	*/
	/*
	 * Multiple Files Data:
	 */
	u_int	di_file_limit;		/* The maximum files per pass.	*/
	u_int	di_file_number;		/* The current file number.	*/
	u_long	di_last_files_read;	/* The last files read.		*/
	u_long	di_last_files_written;	/* The last files written.	*/
	u_long	di_max_files_read;	/* The maximum files read.	*/
	u_long	di_max_files_written;	/* The maximum files written.	*/
	large_t di_max_data;		/* Max data limit (all files).	*/
	u_int	di_max_files;		/* Max file limit (all dirs).	*/
	v_large	di_maxdata_read;	/* Max data read (all files).	*/
	v_large	di_maxdata_written;	/* Max data written (all files)	*/
	/*
	 * Per Pass Information:
	 */
	vu_long	di_files_read;		/* Number of files read.	*/
	vu_long	di_files_written;	/* Number of files written.	*/
        u_long  di_full_reads;          /* The # of full records read.  */
        u_long  di_full_writes;         /* The # of full records written*/
        u_long  di_partial_reads;       /* Partial # of records read.   */
        u_long  di_partial_writes;      /* Partial # of records written */
	vu_long	di_records_read;	/* Number of records read.	*/
	vu_long	di_records_written;	/* Number of records written.	*/
	vu_long di_read_errors;		/* Number of read errors.	*/
	vu_long di_write_errors;	/* Number of write errors.	*/
	large_t	di_data_limit;		/* The data limit (in bytes).	*/
	large_t	di_rdata_limit;		/* The random I/O data limit.	*/
	large_t	di_record_limit;	/* Max # of records to process.	*/
	large_t	di_storage_size;	/* The device/file data size.	*/
	large_t	di_user_limit;		/* The user specific data limit.*/
	large_t	di_volume_bytes;	/* Accumulated volume bytes.	*/
	int	di_volume_limit;	/* Number of volumes to process.*/
	vu_long	di_volume_records;	/* The last volume record limit.*/
	/*
	 * Monitoring Information:
	 */
	vtime_t	di_initiated_time;	/* Time the I/O was initiated.	*/
	time_t	di_last_alarm_time;	/* The last alarm time (secs).	*/
	time_t	di_last_keepalive;	/* The last keepalive (secs).	*/
	/*
	 * Program Run Time Information:
	 */
	time_t	di_alarmtime;		/* The alarm interval time.     */
	time_t	di_keepalive_time;	/* The keepalive time.		*/
	time_t	di_noprogtime;		/* The no progress time (secs).	*/
	time_t	di_noprogttime;		/* The no prog trigger time.	*/
	time_t	di_runtime;		/* The program run time.	*/
	time_t	di_runtime_end;		/* The ending future runtime.   */
	time_t	di_program_start;	/* The program start time.	*/
	time_t	di_program_end;		/* The program end time.	*/
	time_t	di_error_time;		/* Time last error occurred.	*/
	char	di_time_buffer[TIME_BUFFER_SIZE]; /* For ASCII time.	*/
	bool	di_TimerActive;		/* Set after timer activated.	*/
	bool	di_TimerExpired;	/* Set after timer has expired.	*/
	char	*di_user_runtime;	/* User specific runtime string	*/
        /*
         * Information for Error Reporting / Trigger:
         */
        OFF_T	di_offset;		/* Device/file offset at error.	*/
        large_t di_lba;                 /* Logical/relative block addr. */
        u_int32 di_position;            /* Position into failing block. */
	v_int	di_errno;		/* The last errno encountered.	*/
	optype_t di_optype;		/* The current operation type.	*/
	/*
	 * Retry Parameters:
	 */
	v_bool	di_retrying;		/* The recovery retrying flag.	*/
	u_char	*di_saved_pattern_ptr;	/* Saved pattern buf pointer.	*/
	bool	di_retryDC_flag;	/* Retry data corruptions.	*/
	u_int	di_retry_delay;		/* The default retry delay.	*/
	int	di_retry_errors[RETRY_ENTRIES];
					/* The error codes to retry.	*/
	int	di_retry_entries;	/* The number of error codes.	*/
	u_int	di_retry_count;		/* Current number of retries.	*/
	u_int	di_retry_limit;		/* The retryable error limit.	*/
	/*
	 * History Information:
	 */
	bool	di_history_dump;	/* Dump history when exiting.	*/
	bool	di_history_timing;	/* History timing control flag.	*/
	int	di_history_size;	/* Size of the history array.	*/
	int	di_history_entries;	/* Number of history entries.	*/
	int	di_history_index;	/* Index to next history entry.	*/
	int	di_history_data_size;	/* Request data size to save.	*/
	history_t *di_history;		/* Array of history entries.	*/
	/*
	 * Data Pattern Related Information:
	 */
	bool	di_lbdata_flag;		/* Logical block data flag.	*/
	bool	di_unique_pattern;	/* Unique pattern per process.	*/
	bool	di_iot_pattern;		/* IOT test pattern selected.	*/
	u_int32	di_lbdata_addr;		/* Starting logical block addr.	*/
	size_t	di_lbdata_size;		/* Logical block data size.	*/
	u_int32	di_iot_seed;		/* The default IOT seed value.	*/
	u_int32	di_iot_seed_per_pass;	/* The per pass IOT seed value.	*/
	/*
	 * Pattern Buffer Information: 
	 */
	size_t	di_patbuf_size;		/* The pattern buffer size.	*/
	u_int32 di_pattern;		/* The data pattern (not IOT).	*/
	u_char	*di_pattern_buffer;	/* Pointer to pattern buffer.	*/
	u_char	*di_pattern_bufptr;	/* Pointer into pattern buffer.	*/
	u_char	*di_pattern_bufend;	/* Pointer to end of pat buffer	*/
	char	*di_pattern_string;	/* The pattern string.		*/
	int	di_pattern_size;	/* The data pattern size.	*/
	int	di_pattern_index;	/* The pass pattern index.	*/
	/*
	 * Prefix String Data (initial and formatted): 
	 */
	char	*di_prefix_string;	/* The prefix string (if any).	*/
	int	di_prefix_size;		/* The prefix string size.	*/
	char	*di_fprefix_string;	/* The formatted prefix string.	*/
	int	di_fprefix_size;	/* The formatted prefix size.	*/

	/*
	 * Data Buffers: 
	 */
	size_t	di_data_size;		/* Data buffer size + pad bytes	*/
	u_char	*di_base_buffer;	/* Base address of data buffer.	*/
	u_char	*di_data_buffer;	/* Pointer to data buffer.	*/
	u_char	*di_mmap_buffer;	/* Pointer to mmapped buffer.	*/
	u_char	*di_mmap_bufptr;	/* Pointer into mmapped buffer.	*/
	u_char	*di_verify_buffer;	/* The data verification buffer.*/
	/*
	 * I/O Delays:
	 * Note: volatile, since can be overriden via a iotune file!
	 */
	vu_int	di_open_delay;		/* Delay before opening file.	*/
	vu_int	di_close_delay;		/* Delay before closing file.	*/
	vu_int	di_end_delay;		/* Delay between multiple passes*/
	vu_int	di_read_delay;		/* Delay before reading record.	*/
	vu_int	di_start_delay;		/* Delay before starting test.	*/
	vu_int	di_write_delay;		/* Delay before writing record.	*/
	vu_int	di_term_delay;		/* Child terminate delay count.	*/

	/*
	 * Test Times: 
	 */
	clock_t di_start_time;		/* Test start time.		*/
	clock_t	di_end_time;		/* Test end time.		*/
	clock_t	di_pass_time;		/* Per pass elapsed time.	*/
	struct tms di_stimes;		/* User system time.		*/
	struct tms di_ptimes;
	struct tms di_etimes;
	pid_t	di_child_pid;		/* For the child process ID.	*/
	int	di_child_status;	/* For child exit status.	*/

#if defined(AIO)
	/*
	 * Asynchronous I/O: 
	 */
	int	di_aio_bufs;		/* The number of AIO buffers.	*/
	int	di_aio_index;		/* Index to AIO control block.	*/
	volatile OFF_T di_aio_offset;	/* AIO offset (we maintain).	*/
	v_large	di_aio_data_bytes;	/* Total data bytes per pass.	*/
	v_large	di_aio_file_bytes;	/* # of file bytes processed.	*/
	vu_long	di_aio_record_count;	/* # of records to processed.	*/
	u_int32	di_aio_lba;		/* AIO logical block address.	*/
	
	/*
	 * The following variables are meant to be used with tape devices to
	 * backup unprocessed files and/or records due to read-ahead, to be
	 * repositioned prior to the next test or before closing the tape.
	 */
	u_long	di_aio_data_adjust;	/* # of data bytes to adjust.	*/
	u_long	di_aio_file_adjust;	/* # of tape files to adjust.	*/
	u_long	di_aio_record_adjust;	/* # of tape record to adjust.	*/
	
	struct aiocb	*di_acbs;	/* Pointer to AIO control blocks. */
	u_char		**di_aiobufs;	/* Pointer to base buffer addrs.  */
	struct aiocb	*di_current_acb;/* Current acb for error reports. */
	
#else /* !defined(AIO) */
	int	di_aio_bufs;		/* The number of AIO buffers.	*/
#endif /* !defined(AIO) */

	bool	di_aio_flag;		/* Asynchronous I/O (AIO) flag.	*/
	v_bool	di_dio_flag;		/* Solaris/Win32 Direct I/O.    */
	int	di_align_offset;	/* Align buffer at this offset.	*/
	
	bool	di_dumpall_flag;	/* Controls dumping all blocks.	*/
	u_int	di_max_bad_blocks;	/* Maximum bad blocks to dump.	*/
	bfmt_t	di_boff_format;		/* Buffer offset data format.	*/
	dfmt_t	di_data_format;		/* Data display format.		*/
	
	bufmodes_t di_buffer_modes[NUM_BUFMODES]; /* I/O buffer modes.	*/
	int	di_bufmode_index;	/* Current buffer mode index.	*/
	int	di_bufmode_count;	/* The user specified bufmodes.	*/
	
	size_t	di_dump_limit;		/* The dump buffer data limit.	*/
	bool	di_bypass_flag;		/* Bypass (some) sanity checks.	*/
	bool	di_cerrors_flag;	/* Report device close errors.	*/
	bool	di_child_flag;		/* This is a child process.	*/
	/*
	 * Debug Flags: 
	 */
	bool	di_debug_flag;		/* Enable debug output flag.	*/
	bool	di_Debug_flag;		/* Verbose debug output flag.	*/
	bool	di_eDebugFlag;		/* End of file debug flag.	*/
	bool	di_fDebugFlag;		/* File operations debug flag.	*/
	bool	di_mDebugFlag;		/* Memory related debug flag.	*/
	bool	di_mntDebugFlag;	/* Mount device lookup debug.	*/
	bool	di_pDebugFlag;		/* Process related debug flag.	*/
	bool	di_rDebugFlag;		/* Random (seek) debug flag.	*/
	bool	di_sDebugFlag;		/* SCSI debug output flag.	*/
	bool	di_tDebugFlag;		/* Timer (alarm) debug flag.	*/
	bool	di_delete_per_pass;	/* Delete files per pass flag.	*/
	/* File system caching is enabled by default, these control each. */
	v_bool	di_read_cache_flag;	/* FS Read cache control flag.	*/
	v_bool	di_write_cache_flag;	/* FS Write cache control flag.	*/
	bool	di_dump_flag;		/* Dump data buffer on errors.	*/
	bool	di_forked_flag;		/* Forked child process flag.	*/
	bool	di_fsincr_flag;		/* File size increment flag.	*/
	bool	di_fsync_flag;		/* fsync() after writes flag.	*/
	u_int	di_fsync_frequency;	/* The fsync frequency.		*/
	bool    di_fsalign_flag;	/* Align FS offsets and sizes.  */
	bool	di_mount_lookup;	/* The mount point lookup flag.	*/
	bool	di_multiple_devs;	/* Multiple devices flag.	*/
	bool	di_multiple_dirs;	/* Multiple directories flag.	*/
	bool	di_multiple_files;	/* Multiple files flag.		*/
	OFF_T	di_end_position;	/* End position for stepping.	*/
	OFF_T	di_file_position;	/* The starting file position.	*/
	OFF_T	di_ofile_position;	/* The output file position.	*/
	OFF_T	di_last_position;	/* Last position lseeked to.	*/
	OFF_T	di_step_offset;		/* Step offset for disk seeks.	*/
	bool	di_keep_existing;	/* Don't delete existing files.	*/
	bool	di_header_flag;		/* The log file header flag.	*/
	bool	di_noprog_flag;		/* Check for no I/O progress.	*/
	bool	di_prefill_flag;	/* I/O buffer pre-fill flag.	*/
	bool	di_unique_log;		/* Make the log file unique.	*/
	bool	di_unique_file;		/* Make output file unqiue.	*/
	bool	di_user_incr;		/* User specified incr count.	*/
	bool	di_user_min;		/* User specified min size.	*/
	bool	di_user_max;		/* User specified max size.	*/
	bool	di_user_ralign;		/* User specified random align. */
	bool	di_user_rseed;		/* Flags user specified rseed.	*/
	bool	di_user_lbdata;		/* User specified starting lba.	*/
	bool	di_user_lbsize;		/* User specified lbdata size.	*/
	bool	di_user_pattern;	/* Flags user specified pattern	*/
	bool	di_user_position;	/* User specified file position.*/
	bool	di_incr_pattern;	/* Incrementing data pattern.	*/
	bool	di_logappend_flag;	/* Append to log file flag.	*/
	bool	di_logdiag_flag;	/* Log diagnostic messages.	*/
	bool	di_logpid_flag;		/* Log process ID w/messages.	*/
	bool	di_syslog_flag;		/* Log errors to syslog.	*/
	bool	di_loop_on_error;	/* The loop on error flag.	*/
	v_bool	di_micro_flag;		/* Controls micro-second delay.	*/
	bool	di_mmap_flag;		/* Do memory mapped file I/O.	*/
	bool	di_media_changed;	/* Shows when media changed.	*/
	int	di_open_flags;		/* Common file open flags.	*/
	int	di_wopen_flags;		/* Additional write open flags.	*/
	int	di_ropen_mode;		/* The read open mode to use.	*/
	int	di_wopen_mode;		/* The write open mode to use.	*/
	int	di_rwopen_mode;		/* The read/write open mode.	*/
	bool	di_pad_check;		/* Check data buffer pad bytes.	*/
	bool	di_spad_check;		/* Check short record pad bytes.*/
	u_long	di_skip_count;		/* # of input record to skip.	*/
	u_long	di_seek_count;		/* # of output records to seek.	*/
	u_long  di_records_processed;	/* # of full records processed.	*/
	u_long	di_partial_records;	/* # of partial records proc'ed	*/
	u_long	di_random_align;	/* Random I/O offset alignment.	*/
	large_t	di_total_bytes;		/* Total bytes transferred.	*/
	large_t di_total_bytes_read;	/* Total bytes read.		*/
	large_t di_total_bytes_written;	/* Total bytes written.		*/
	vu_long	di_total_errors;	/* Total errors (all passes).	*/
	large_t	di_total_files;		/* Total files (all passes).	*/
	large_t di_total_files_read;	/* Total files read.		*/
	large_t di_total_files_written;	/* Total files written.		*/
	large_t	di_total_records;	/* Total records (all passes).	*/
	large_t di_total_records_read;	/* Total records read (test).   */
	large_t di_total_records_written; /* Total records written (test) */
	u_long	di_total_partial;	/* Total partial records.	*/
	u_long	di_total_partial_reads; /* Total partial record reads.  */
	u_long	di_total_partial_writes;/* Total partial record writes. */
	u_long	di_warning_errors;	/* Total non-fatal error count.	*/
	bool	di_pstats_flag;		/* Display per pass statistics.	*/
	bool	di_raw_flag;		/* The read after write flag.	*/
	bool	di_reread_flag;		/* Force a re-read after raw.	*/
	bool	di_rotate_flag;		/* Force data buffer rotating.	*/
	int	di_rotate_offset;	/* Current rotate buffer offset	*/
	bool	di_prealloc_flag;	/* Preallocate file blocks (win)*/
	bool	di_sparse_flag;		/* Sparse file attribute (win).	*/
	bool	di_stats_flag;		/* Display total statistics.	*/
	char	*di_cmd_line;		/* Copy of our command line.	*/
	char	*di_log_file;		/* Pointer to log file name.	*/
	char	*di_log_format;		/* The log file format string.	*/
	char	*di_log_buffer;		/* Pointer to log file buffer.	*/
	char	*di_log_bufptr;		/* Pointer into log buffer.	*/
	ssize_t	di_log_bufsize;		/* The log buffer size.		*/
	char	*di_msg_buffer;		/* Diagnostic message buffer.	*/
	char	*di_stderr_buffer;	/* The standard error buffer.	*/
	/*
	 * I/O Tuning Definitions:
	 */
        bool    di_iotuning_active;     /* The iotuning active flag.    */
        bool    di_iotuning_flag;       /* The iotuning control flag.   */
        unsigned int di_iotune_delay;   /* The iotuning retry delay.    */
        time_t	di_iotune_mtime;	/* The last modification time.	*/
	char	*di_iotune_file;	/* Pointer to IO tune file.	*/
	char	*di_input_file;		/* Pointer to input file name.	*/
	char	*di_output_file;	/* Pointer to output file name.	*/
	char	*di_pattern_file;	/* Pointer to pattern file name	*/
	char	*di_stop_on_file;	/* Stop on file existance.	*/
	u_int	di_random_seed;		/* Seed for random # generator.	*/
	bool	di_max_capacity;	/* Use max capacity from IOCTL.	*/
	large_t	di_user_capacity;	/* The user set drive capacity.	*/
	/* 
	 * Multiple Volumes: 
	 */
	bool	di_multi_flag;		/* Multi-volume media flag.	*/
	v_int	di_multi_volume;	/* Multi-volume media count.	*/
	bool	di_variable_flag;	/* Variable block size flag.	*/
	bool	di_volumes_flag;	/* Flags the volumes option.	*/
	
	/*
	 * Trigger Definitions: 
	 */
	bool	di_trigargs_flag;	/* Trigger arguments flag.	*/
	int	di_num_triggers;	/* The number of triggers.	*/
	trigger_data_t di_triggers[NUM_TRIGGERS];
	/*
	 * Keepalive Definitions: 
	 */
	char	*di_keepalive;		/* The keepalive string.	*/
	char    *di_pkeepalive;		/* The pass keepalive string.	*/
	char    *di_tkeepalive;		/* The total keepalive string.	*/
	bool    di_user_keepalive;	/* User specified keepalive flag*/
	bool    di_user_pkeepalive;	/*        ... ditto ...         */
	bool    di_user_tkeepalive;	/*        ... ditto ...         */
	/*
	 * Multiple Process Information: 
	 */
	bool	di_aborted_processes;	/* Processes have been aborted.	*/
	char	*di_dtcmd;		/* Command line for subprocs.	*/
#if defined(WIN32)
	HANDLE	di_proc_handles[MAXIMUM_WAIT_OBJECTS]; /* for subprocs.	*/
#endif /* defined(WIN32) */
	pid_t	di_process_id;		/* The current process ID.	*/
	struct dt_procs *di_ptable;	/* Multiple process table.	*/
	int	di_num_devs;		/* Number of devices specified.	*/
	int	di_num_procs;		/* Number of procs to create.	*/
	int	di_cur_proc;		/* The current process number.	*/
	int	di_max_procs;		/* Maximum processes started.	*/
	int	di_procs_active;	/* Number of active processes.	*/
	int	di_num_slices;		/* Number of slices to create.	*/
	int	di_slice_num;		/* Slice number to operate on.	*/
#if defined(SCSI)
	/*
	 * SCSI Specific Information:
	 */
	bool	di_scsi_flag;		/* The SCSI control flag.	*/
	bool	di_scsi_errors;		/* The SCSI error logging flag.	*/
	char	*di_scsi_dsf;		/* The SCSI device special file	*/
					/* Note: Optional, use for FS!	*/
	scsi_generic_t *di_sgp;		/* The SCSI generic data.       */
	unsigned di_scsi_timeout;	/* The SCSI CDB timeout value.	*/
	inquiry_t *di_inquiry;		/* The device Inquiry data.	*/
	idt_t	di_idt;			/* The Inquiry data type.	*/
	char	*di_vendor_id;		/* The Inquiry vendor ID.	*/
	char	*di_product_id;		/* The Inquiry product ID.	*/
	char	*di_revision_level;	/* The Inquiry revision level.	*/
	char	*di_device_id;		/* The device identifier.	*/
	char	*di_serial_number;	/* The device serial number.	*/
	/* Read Capacity Information */
	large_t	di_device_capacity;	/* The device capacity.		*/
	u_int32	di_block_length;	/* The device block length.	*/
	/*
	 * SCSI Unmap Information:
	 */ 
	bool	di_unmap_flag;		/* SCSI Unmap control flag.	*/
	u_int	di_unmap_frequency;	/* The unmap frequency.		*/
	char	*di_spt_path;		/* Until spt is integrated.	*/
#endif /* defined(SCSI) */
	char	*di_mounted_from_device;/* The mount from device name.	*/
	char	*di_mounted_on_dir;	/* The mounted on directory.	*/
	char	*di_filesystem_type;	/* The type of file system.	*/
	char	*di_filesystem_options;	/* The file system options.	*/
	/* 
	 * For Copy/Verify, the output device is here (for now)! 
	 */
	struct dinfo *di_output_dinfo;	/* Output device information.	*/
					/* This is used for copy/verify	*/
} dinfo_t;

/*
 * Define test function dispatch structure:
 *
 * [ NOTE:  These functions are not all used at this time.  The intent
 *   is to cleanup the code later by grouping functions appropriately. ]
 */
struct dtfuncs {
						/* Open device or file.	   */
    int	(*tf_open)(struct dinfo	*dip, int oflags);
						/* Close device or file.   */
    int	(*tf_close)(struct dinfo *dip);
						/* Special initilization.  */
    int	(*tf_initialize)(struct dinfo *dip);
						/* Start test processing.  */
    int	(*tf_start_test)(struct dinfo *dip);
						/* End of test processing. */
    int	(*tf_end_test)(struct dinfo *dip);
						/* Read file data.	   */
    int	(*tf_read_file)(struct dinfo *dip);
						/* Processes read data.	   */
    int	(*tf_read_data)(struct dinfo *dip);
						/* Cancel read requests.   */
    int	(*tf_cancel_reads)(struct dinfo *dip);
						/* Write file data.	   */
    int	(*tf_write_file)(struct dinfo *dip);
						/* Processes write data.   */
    int	(*tf_write_data)(struct dinfo *dip);
						/* Cancel write requests.  */
    int	(*tf_cancel_writes)(struct dinfo *dip);
						/* Flush data to media.	   */
    int	(*tf_flush_data)(struct dinfo *dip);
						/* Verify data read.	   */
    int	(*tf_verify_data)(	struct dinfo	*dip,
				u_char		*buffer,
				size_t		count,
				u_int32		pattern,
				u_int32		*lba );
						/* Reopen device or file.  */
    int	(*tf_reopen_file)(struct dinfo *dip, int oflags);
						/* Test startup handling.  */
    int	(*tf_startup)(struct dinfo *dip);
						/* Test cleanup handling.  */
    int	(*tf_cleanup)(struct dinfo *dip);
						/* Validate test options.  */
    int	(*tf_validate_opts)(struct dinfo *dip);
};

/*
 * Macros to Improve Performance:
 *
 * Note: Others can be added after debug is conditionalized.
 */
#define INLINE_FUNCS 1

#if defined(INLINE_FUNCS)

#define make_lba(dip, pos)	\
	(u_int32)((pos == (OFF_T) 0) ? (u_int32) 0 : (pos / dip->di_lbdata_size))

#define make_offset(dip, lba)	((OFF_T)(lba * dip->di_lbdata_size))

#define make_lbdata(dip, pos)	\
	(u_int32)((pos == (OFF_T) 0) ? (u_int32) 0 : (pos / dip->di_lbdata_size))

#define make_position(dip, lba)	((OFF_T)(lba * dip->di_lbdata_size))

#if defined(_BSD)
#  define get_position(dip) (seek_position (dip, (OFF_T) 0, L_INCR, FALSE))
#else /* !defined(_BSD) */
#  define get_position(dip) (seek_position (dip, (OFF_T) 0, SEEK_CUR, FALSE))
#endif /* defined(_BSD) */

#endif /* defined(INLINE_FUNCS) */

extern FILE *efp, *ofp;
extern struct dinfo *active_dinfo, *input_dinfo, *output_dinfo;

#if defined(AIX)
#  undef hz
#endif
extern clock_t hz;
extern int exit_status;
extern u_int32 data_patterns[];
extern int npatterns;

extern bool core_dump;
/* TODO: These debug flags... */
extern volatile hbool_t CmdInterruptedFlag;
extern bool debug_flag,	mDebugFlag, pDebugFlag, tDebugFlag;
extern bool logpid_flag;
extern bool hazard_flag;
extern bool nate_flag;
extern volatile bool terminating_flag;
extern bool sighup_flag;

extern char *cmdname, *dtpath;
extern int page_size;

/*
 * Volatile Storage:
 */
extern bool eof_status_flag;

extern bool StdinIsAtty, StdoutIsAtty, StderrIsAtty;
extern char *keepalive0, *keepalive1;

#if defined(SOLARIS)
/* This is for enabling Direct I/O on VxFS! */
/* NOTE: Added very long time ago... is this still valid? */
#  define VX_IOCTL        (('V' << 24) | ('X' << 16) | ('F' << 8))
#  define VX_SETCACHE     (VX_IOCTL | 1)   /* set cache advice */
#  define VX_DIRECT       0x00004          /* perform direct (un-buffered) I/O */
#endif /* defined(SOLARIS) */

/*
 * Function Prototypes:
 */

/* dt.c */
extern void log_header(dinfo_t *dip);
extern void report_error(dinfo_t *dip,char *error_info, int record_flag);
extern void report_record(
			struct dinfo	*dip,
			u_long		files,
			u_long		records,
			large_t		lba,
                        OFF_T           pos,
			enum test_mode	mode,
			void		*buffer,
			size_t		bytes );
extern void keepalive_alarm(int sig);
extern void handle_terminating(dinfo_t *dip);
extern void terminate(int code);
extern int nofunc(struct dinfo *dip);
extern int HandleMultiVolume(struct dinfo *dip);
extern int RequestFirstVolume(struct dinfo *dip, int oflags);
extern int RequestMultiVolume(struct dinfo *dip, bool reopen, int open_flags);
extern bool match(char **sptr, char *s);
extern unsigned int number(dinfo_t *dip, char *str, int base, int *status, bool report_error);
extern large_t large_number(dinfo_t *dip, char *str, int base, int *status, bool report_error);
extern time_t time_value(char *str);

/* dtgen.c */
extern char *make_file_name(struct dinfo *dip);
extern int open_file(struct dinfo *dip, int mode);
extern int close_file(struct dinfo *dip);
extern int reopen_file(struct dinfo *dip, int mode);
extern int initialize(struct dinfo *dip);
extern int init_file(struct dinfo *dip);
extern int flush_file(struct dinfo *dip);
extern int read_file(struct dinfo *dip);
extern int write_file(struct dinfo *dip);
extern int validate_opts(struct dinfo *dip);
#if defined(SOLARIS)
extern int SolarisDIO(struct dinfo *dip, char *file, bool flag);
#endif /* defined(SOLARIS) */
extern void SetupBufferingMode(dinfo_t *dip, int *oflags);

/* dtinfo.c */
extern struct dtype *setup_device_type(char *str);
extern int setup_device_info(struct dinfo *dip, char *dname, struct dtype *dtp);
extern void system_device_info(struct dinfo *dip);
extern int setup_directory_info(struct dinfo *dip, char *dir);
extern void setup_toplevel_directory(dinfo_t *dip, char *dir);
extern int init_scsi_info(dinfo_t *dip);
extern void report_vdisk_attributes(dinfo_t *dip);
extern int unmap_blocks(dinfo_t *dip, large_t starting_block, large_t data_limit);

/* dtread.c */
extern void check_last_write_info(dinfo_t *dip, OFF_T offset, size_t bsize, size_t dsize);
extern int read_data(struct dinfo *dip);
extern int check_read(struct dinfo *dip, ssize_t count, size_t size);
extern int read_eof(struct dinfo *dip);
extern int read_eom(struct dinfo *dip);
extern ssize_t read_record(	struct dinfo	*dip,
				u_char		*buffer,
				size_t		bsize,
				size_t		dsize,
				int		*status );
extern int verify_record(	struct dinfo	*dip,
				u_char		*buffer,
				size_t		bsize );
extern int FindCapacity(struct dinfo *dip);

/* dtwrite.c */
extern int write_data(struct dinfo *dip);
extern int check_write(struct dinfo *dip, ssize_t count, size_t size);
extern int copy_record(		struct dinfo	*dip,
				u_char		*buffer,
				size_t		bsize );
extern ssize_t write_record(	struct dinfo	*dip,
				u_char		*buffer,
				size_t		bsize,
				size_t		dsize,
				int		*status );
extern int write_verify(	struct dinfo	*dip,
				u_char		*buffer,
				size_t		bsize,
				size_t		dsize,
				OFF_T		pos );

/* dtstats.c */
extern void accumulate_stats(dinfo_t *dip);
extern void gather_stats(struct dinfo *dip);
extern void gather_totals(struct dinfo *dip);
extern void init_stats(struct dinfo *dip);
extern void report_pass(struct dinfo *dip, enum stats stats_type);
extern void report_stats(struct dinfo *dip, enum stats stats_type);

/* dtutil.c */
extern int create_directory(struct dinfo *dip, char *dir);
extern int remove_current_directory(struct dinfo *dip);
extern int remove_directory(struct dinfo *dip, char *dir);
extern int delete_file(struct dinfo *dip, char *file);
extern int delete_files(struct dinfo *dip);
extern int delete_subdir_files(struct dinfo *dip, char *spath);
extern bool file_exists(struct dinfo *dip, char *file);
extern int truncate_file(struct dinfo *dip, OFF_T offset);
extern void mySleep(dinfo_t *dip, unsigned int sleep_time);
extern void SleepSecs(unsigned int sleep_time);

extern void dump_buffer(	dinfo_t		*dip,
				char		*name,
				u_char		*base,
				u_char		*ptr,
				size_t		dump_size,
				size_t		bufr_size,
				bool		expected);
extern void fill_buffer(	dinfo_t		*dip,
				u_char		*buffer,
				size_t		byte_count,
				u_int32		pattern);
extern void init_buffer(	dinfo_t		*dip,
				u_char		*buffer,
				size_t		count,
				u_int32		pattern );
#if _BIG_ENDIAN_
extern void init_swapped (	dinfo_t		*dip,
				u_char		*buffer,
		                size_t		count,
		                u_int32		pattern );
#endif /* _BIG_ENDIAN_ */

extern u_int32 init_lbdata(	struct dinfo	*dip,
				u_char		*buffer,
				size_t		count,
				u_int32		lba,
				u_int32		lbsize );
#if defined(TIMESTAMP)
extern void init_timestamp (	dinfo_t		*dip,
				u_char		*buffer,
                        	size_t		count,
                        	u_int32		dsize );
extern void display_timestamp(dinfo_t *dip, u_char *buffer);
#endif /* defined(TIMESTAMP) */

#if !defined(INLINE_FUNCS)
extern u_int32 make_lba(	struct dinfo	*dip,
				OFF_T		pos );
extern OFF_T make_offset(	struct dinfo	*dip,
				u_int32		lba);
extern u_int32 make_lbdata(	struct dinfo	*dip,
				OFF_T		pos );
#endif /* !defined(INLINE_FUNCS) */
extern u_int32 winit_lbdata(	struct dinfo	*dip,
				OFF_T		pos,
				u_char		*buffer,
				size_t		count,
				u_int32		lba,
				u_int32		lbsize );
extern u_int32 init_iotdata(	dinfo_t		*dip,
				u_char		*buffer,
				size_t		bcount,
				u_int32		lba,
				u_int32		lbsize );
extern void init_padbytes(	u_char		*buffer,
				size_t		offset,
				u_int32		pattern);
extern char *bformat_time (char *bp, clock_t time);
extern void print_time(FILE *fp, clock_t time);
extern void format_time(dinfo_t *dip, clock_t time);
extern int verify_buffers(	struct dinfo	*dip,
				u_char		*dbuffer,
				u_char		*vbuffer,
				size_t		count );
extern int verify_lbdata(	struct dinfo	*dip,
				u_char		*dbuffer,
				u_char		*vbuffer,
				size_t		count,
				u_int32		*lba );
extern int verify_data(		struct dinfo	*dip,
				u_char		*buffer,
				size_t		byte_count,
				u_int32		pattern,
				u_int32		*lba );
extern int verify_reread(	struct dinfo	*cdip,
				u_char		*buffer,
				size_t		bcount,
				u_int32		pattern,
				u_int32		*lba );
extern int verify_padbytes(	struct dinfo	*dip,
				u_char		*buffer,
				size_t		count,
				u_int32		pattern,
				size_t		offset );
extern void process_pfile(dinfo_t *dip, char *file, int mode);
extern void process_iotune(dinfo_t *dip, char *file);
extern void copy_pattern(u_int32 pattern, u_char *buffer);
extern void setup_pattern(dinfo_t *dip, u_char *buffer, size_t size);
extern OFF_T seek_file(dinfo_t *dip, HANDLE fd, u_long records, OFF_T size, int whence);
extern OFF_T seek_position(struct dinfo *dip, OFF_T size, int whence, bool expect_error);
#if !defined(INLINE_FUNCS)
extern OFF_T get_position(struct dinfo *dip);
#endif /* !defined(INLINE_FUNCS) */
extern u_int32 get_lba(struct dinfo *dip);
extern OFF_T incr_position(struct dinfo *dip, OFF_T offset, bool expect_error);
extern OFF_T set_position(struct dinfo *dip, OFF_T offset, bool expect_error);
#if !defined(INLINE_FUNCS)
extern OFF_T make_position(struct dinfo *dip, u_int32 lba);
#endif /* !defined(INLINE_FUNCS) */
extern void show_position(struct dinfo *dip, OFF_T pos);
extern u_long get_random(void);
extern large_t get_random64(void);
extern size_t get_variable(struct dinfo *dip);
extern void set_rseed(u_int seed);
extern OFF_T do_random(struct dinfo *dip, bool doseek, size_t xfer_size);
extern int skip_records(struct dinfo *dip, u_long records, u_char *buffer, size_t size);
extern void *Malloc(size_t bytes);
extern void *Realloc(void *bp, size_t bytes);
extern unsigned int CvtStrtoValue(dinfo_t *dip, char *nstr, char **eptr, int base);
extern large_t CvtStrtoLarge(dinfo_t *dip, char *nstr, char **eptr, int base);
extern time_t CvtTimetoValue(char *nstr, char **eptr);
extern void Ctime(dinfo_t *dip, time_t timer);
extern char *fmtmsg_prefix(char *bp, int flags, logLevel_t level);
extern void LogMsg(FILE *fp, enum logLevel level, int flags, char *fmtstr, ...);
extern u_long RecordError(struct dinfo *dip);
extern u_long RecordWarning(dinfo_t *dip, u_long record);
#if defined(WIN32)
extern LPVOID werror_msg(DWORD error);
extern OFF_T SetFilePtr(HANDLE hf, OFF_T distance, DWORD MoveMethod);
#endif /* defined(WIN32) */
extern void Fprintf(char *format, ...);
extern void Fprint(char *format, ...);
extern void Lprintf(dinfo_t *dip, char *format, ...);
extern void Printf(char *format, ...);
extern void Print(char *format, ...);
extern void Perror(char *format, ...);
#if defined(WIN32)
extern void wPerror(char *format, ...);
extern void tPerror(DWORD error, char *format, ...);
#else /* !defined(WIN32) */
extern void tPerror(int error, char *format, ...);
#endif /* defined(WIN32) */
extern void Lflush(dinfo_t *dip);
extern int Sprintf(char *bufptr, char *msg, ...);
extern int Fputs(char *str, FILE *stream);
extern bool isFsFullOk(struct dinfo *dip, char *op);
extern int is_Eof(struct dinfo *dip, size_t count, int *status);
extern bool is_retryable(dinfo_t *dip, int error_code);
extern bool retry_operation(dinfo_t *dip);
extern void set_Eof(struct dinfo *dip);
extern void ReportCompareError(	struct dinfo	*dip,
				size_t		byte_count,
				u_int		byte_position,
				u_int		expected_data,
				u_int		data_found );
extern void ReportDeviceInfo(	struct dinfo	*dip,
				size_t		byte_count,
				u_int		byte_position,
				bool		eio_error );
extern void ReportLbdataError(	struct dinfo	*dip,
			        u_int32		lba,
				u_int32		byte_count,
				u_int32		byte_position,
				u_int32		expected_data,
				u_int32		data_found );

extern int IS_HexString(char *s);
extern int FmtKeepAlive(struct dinfo *dip, char *keepalivefmt, char *buffer);
extern int FmtPrefix(struct dinfo *dip, char *prefix, int psize);
extern int StrCopy(void *to_buffer, void *from_buffer, size_t length);
extern large_t stoh(u_char *bp, size_t size);
extern void htos(u_char *bp, large_t value, size_t size);
extern void LogDiagMsg(dinfo_t *dip, char *msg);
extern enum trigger_type check_trigger_type(dinfo_t *dip, char *str);
extern int ExecuteCommand(dinfo_t *dip, char *cmd);
extern int ExecuteTrigger(struct dinfo *dip, ...);
extern int get_cpu_utilization(dinfo_t *dip);
extern large_t GetStatsValue(struct dinfo *dip, stats_value_t stv, bool pass_stats, int *secs);
extern void *malloc_palign(size_t bytes, int offset);
extern void free_palign(void *pa_addr);
extern void dump_history_data(struct dinfo *dip);
extern void save_history_data(	struct dinfo	*dip,
				u_long		file_number,
				u_long		record_number,
				test_mode_t	test_mode,
				OFF_T		offset,
				u_char		*buffer,
				size_t		rsize,
				ssize_t		tsize);

/*
 * Strings used by Common Printing Functions.
 */
#define ASCII_FIELD	"%38.38s: %s"
#define EMPTY_FIELD	"%40.40s%s"
#define NUMERIC_FIELD	"%38.38s: %lu"
#define DEC_HEX_FIELD	"%38.38s: %lu (%#lx)"
#define HEX_FIELD	"%38.38s: %#lx"
#define HEX_DEC_FIELD	"%38.38s: %#lx (%u)"
#define FIELD_WIDTH	40		/* The field width (see above).	*/
#define DEFAULT_WIDTH   132			/* tty display width.   */

#define LNUMERIC_FIELD	"%38.38s: " LUF
#define LDEC_HEX_FIELD	"%38.38s: " LUF " (" LXF ")"
#define LHEX_FIELD	"%38.38s: " LXF
#define LHEX_DEC_FIELD	"%38.38s: " LXF " (" LUF ")"

#define DNL		0			/* Disable newline.	*/
#define PNL		1			/* Print newline.	*/

extern int DisplayWidth;
extern void DumpFieldsOffset(uint8_t *bptr, int length);
extern void PrintFields (u_char *bptr, int length);
extern void PrintHAFields(unsigned char *bptr, int length);

extern void PrintHeader(char *header);
extern void PrintNumeric(char *field_str, uint32_t numeric_value, int nl_flag);
#define PrintDec PrintDecimal
extern void PrintDecimal(char *field_str, uint32_t numeric_value, int nl_flag);
extern void PrintDecHex(char *field_str, uint32_t numeric_value, int nl_flag);
extern void PrintHex(char *field_str, uint32_t numeric_value, int nl_flag);
extern void PrintHexDec(char *field_str, uint32_t numeric_value, int nl_flag);
extern void PrintAscii(char *field_str, char *ascii_str, int nl_flag);
extern void PrintLongLong(char *field_str, uint64_t numeric_value, int nl_flag);
extern void PrintLongDec(char *field_str, uint64_t numeric_value, int nl_flag);
extern void PrintLongDecHex(char *field_str, uint64_t numeric_value, int nl_flag);
extern void PrintLongHex(char *field_str, uint64_t numeric_value, int nl_flag);
extern void PrintLongHexDec(char *field_str, uint64_t numeric_value, int nl_flag);
extern void PrintBoolean( hbool_t	numeric,
			  char		*field_str,
			  hbool_t	boolean_flag,
			  hbool_t	nl_flag);
extern void PrintEnDis( hbool_t	numeric,
			char	*field_str,
			hbool_t	boolean_flag,
			hbool_t	nl_flag);
extern void PrintOnOff( hbool_t	numeric,
			char	*field_str,
			hbool_t	boolean_flag,
			hbool_t	nl_flag);
extern void PrintYesNo( hbool_t	numeric,
			char	*field_str,
			hbool_t	boolean_flag,
			hbool_t	nl_flag);

/* dtusage.c */
extern char *version_str;
extern void dthelp(dinfo_t *dip);
extern void dtusage(void), dtversion(void);

/* dtprocs.c */
extern void abort_procs(dinfo_t *dip);
extern void await_procs(dinfo_t *dip);
extern pid_t fork_process(dinfo_t *dip);
extern pid_t start_devs(dinfo_t *dip);
extern pid_t start_procs(dinfo_t *dip);
extern pid_t start_slices(dinfo_t *dip);
extern void init_slice(struct dinfo *dip, int slice);
extern char *make_unique_file(dinfo_t *dip, char *file);
extern void make_unique_log(dinfo_t *dip);
extern char *skip_device_prefix(char *device);
extern char *FmtLogFile(dinfo_t *dip, char *logfile);
extern char *FmtFilePath(dinfo_t *dip, char *filepath);

#if !defined(_QNX_SOURCE)
/*
 * POSIX does *not* define a special device interface, and since no
 * Magtape API exists, these functions are operating system dependent.
 * [ I'll add QNX tape functions after I find out the interface. ]
 */

/* dttape.c */

#if defined(TAPE)
#if defined(_QNX_SOURCE) || defined(SCO)
extern int DoIoctl(dinfo_t *dip, int cmd, int argp, caddr_t msgp);
#else /* !defined(_QNX_SOURCE) && !defined(SCO) */
extern int DoIoctl(dinfo_t *dip, int cmd, caddr_t argp, caddr_t msgp);
#endif /* defined(_QNX_SOURCE) || defined(SCO) */
extern int DoMtOp(dinfo_t *dip, short cmd, daddr_t count, caddr_t msgp);
extern int DoWriteFileMark(dinfo_t *dip, daddr_t count);
extern int DoForwardSpaceFile(dinfo_t *dip, daddr_t count);
extern int DoBackwardSpaceFile(dinfo_t *dip, daddr_t count);
extern int DoForwardSpaceRecord(dinfo_t *dip, daddr_t count);
extern int DoBackwardSpaceRecord(dinfo_t *dip, daddr_t count);
extern int DoRewindTape(dinfo_t *dip);
extern int DoTapeOffline(dinfo_t *dip);
extern int DoRetensionTape(dinfo_t *dip);

#if defined(__osf__)			/* Really DEC specific. */

extern int DoSpaceEndOfData(dinfo_t *dip);
extern int DoEraseTape(dinfo_t *dip);
extern int DoTapeOnline(dinfo_t *dip);
extern int DoLoadTape(dinfo_t *dip);
extern int DoUnloadTape(dinfo_t *dip);

#endif /* defined(__osf__) */

#else /* defined(_QNX_SOURCE) */

extern int DoWriteFileMark(dinfo_t *dip, daddr_t count);

#endif /* !defined(_QNX_SOURCE) */
#endif /* defined(TAPE) */

/* dtaio.c */

#if defined(AIO)

extern int dtaio_close_file(struct dinfo *dip);
extern int dtaio_initialize(struct dinfo *dip);
extern int dtaio_cancel(struct dinfo *dip);
extern int dtaio_cancel_reads(struct dinfo *dip);
extern int dtaio_read_data(struct dinfo *dip);
extern int dtaio_write_data(struct dinfo *dip);

#endif /* defined(AIO) */

/* dtmmap.c */

#if defined(MMAP)

extern int mmap_file(struct dinfo *dip);
extern int mmap_flush(struct dinfo *dip);
extern int mmap_reopen_file(struct dinfo *dip, int mode);
extern int mmap_validate_opts(struct dinfo *dip);
extern int mmap_read_data(struct dinfo *dip);
extern int mmap_write_data(struct dinfo *dip);

#endif /* defined(MMAP) */

#if defined(FIFO)

extern int fifo_open(struct dinfo *dip, int mode);

#endif /* defined(FIFO) */

/*
 * OS Specific Functions: (dtunix.c and dtwin.c)
 */
extern hbool_t FindMountDevice(dinfo_t *dip, char *path, hbool_t debug);
extern char *os_ctime(time_t *timep, char *time_buffer, int timebuf_size);
