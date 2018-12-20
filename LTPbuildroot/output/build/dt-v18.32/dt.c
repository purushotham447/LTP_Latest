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
 * both that copyright notice and this permission notice appear in the	    *
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
 * Module:	dt.c
 * Author:	Robin T. Miller
 *
 * Description:
 *	Main line code for generic data test program 'dt'.
 */
#include "dt.h"
#include <ctype.h>
#include <fcntl.h>
#include <math.h>
#include <signal.h>
#if !defined(WIN32)
#  if !defined(_QNX_SOURCE) 
#    if !defined(sun)
#      include <sys/ioctl.h>
#    endif /* !defined(sun) */
#    include <sys/file.h>
#    include <sys/param.h>
#    if defined(sun) || defined(_OSF_SOURCE)
#      include <sys/mman.h>
#    endif /* defined(sun) || defined(_OSF_SOURCE) */
#  endif /* !defined(_QNX_SOURCE) */
#include <sys/wait.h>
#endif /* !defined(WIN32) */
#if defined(DEC)
#  include <sys/utsname.h>
#endif /* defined(DEC) */

#if defined(HP_UX)
#  include <sys/scsi.h>
#  if !defined(SCSI_MAX_Q_DEPTH)
#    define SCSI_MAX_Q_DEPTH 255
#  endif
#endif /* defined(HP_UX) */

/*
 * Modification History:
 *
 * February 13th, 2013 by Robin T. Miller
 *	If stdout is not a tty, log the header (command line and version)
 * 	When processing multiple devices (via processes at present), ensure
 * we catch desired signals, otherwise the parent doesn't wait for children.
 * This was noticable with debug enabled, and via the incorrect exit status.
 * 	When processing I/O tuning data, only create I/O tune file the first
 * time, overwiting the existing file thereafter (avoiding race when reading).
 * 
 * February 7th, 2013 by Robin T. Miller
 * 	Added open delay option (odelay=).
 * 	Changed end delay to be end of pass delay (like help states!).
 *
 * December 10th, 2012 by Robin T. Miller
 * 	When setting up the top level directory, add a trailing directory
 * separator (as necessary). This is required for Windows with just a drive
 * letter, e.g. of=h:\dt.data, as well as multiple files with multiple procs.
 * 
 * December 4th, 2012 by Robin T. Miller
 * 	If variable I/O sizes has been enabled via bs=random or incr=var,
 * and then a later option wishes to override variable I/O, clear the flag.
 * 
 * September 7th, 2012 by Robin T. Miller
 *	Removed TTY support (if required, the old dt is available).
 *	Removed DEC Tru64 Unix specific code: LOGDIAG_INFO and EEI.
 *	Move copy/verify to separate thread, and hack'ed it to work!
 *	Allow multiple passes and runtime with copy/verify operations.
 *
 * August 30th, 2012 by Robin T. Miller
 *	Decoupled processing of I/O tuning file from the monitoring thread.
 *	The IO tuning is done via its' own thread, very simple (for now).
 *
 * August 11th, 2012 by Robin T. Miller
 *	Removed _BSD conditionalization (only POSIX now!).
 *
 * July 19th, 2012 by Robin T. Miller
 * 	Add parsing of error retry options: retry_error and retry_limit.
 *
 * June 20th, 2012 by Robin T. Miller
 * 	Per request of SAN Automation, when receiving and unexpected exit status
 * from ExecuteTrigger(), call terminate(). This usually means the script path
 * cannot be found, but our usual exit status tells dt to terminate, so we will!
 * 
 * June 6th, 2012 by Robin T. Miller
 * 	Add support for multiple devices (you'll get one process per device).
 * 	Fix bug with enable=deleteperpass, correctly handle WARNING (dir exists)
 * from setup_directory_info(). Was breaking out of main loop in warning! :-(
 * 
 * January 5th, 2012 by Robin T. Miller
 *	Added prealloc flag for use with Windows when sparse files are disabled.
 * Please see the modification history in dtgen.c for a full description of why.
 *
 * December 19th, 2011 by Robin T. Miller
 *	Removed MUNSA for DEC TruCluster and locking.
 * 	Removed table() code for Tru64 Unix (DEC) systems.
 * 	Removed defined(THREADS), which we assume is always true now!
 * 	Moved init_vars() here from dtinfo.c and started added more per device
 * variables to the device information data structure (dinfo_t), in preparation
 * to (eventually) make dt multi-threaded. Alot of work, given it's original
 * single threaded design (too many globals, etc), but we expect to get there!
 * 
 * December 16th, 2011 by Robin T. Miller
 * 	Add iotune=file to allow IO delays to be overriden from file while running.
 * 	Allow keyword 'random' with *delay values to support random IO delays.
 *
 * November 11th, 2011 by Robin T. Miller
 * 	Remove setting the thread stack size, causing issues with being too small,
 * and we don't need this until dt is reworked for doing threaded I/O anyways.
 * 
 * October 13th, 2011 by Robin T. Miller
 * 	Added enable=reread option for use with read-after-write (raw) option.
 * This allows a full read pass to help determine if data was incorrectly changed
 * after the initial write/read/verify pass. Adds an extra debug data point. :-)
 * 
 * October 6th, 2011 by Robin T. Miller
 * 	When "deleteperpass" option is enabled, do NOT delete the files when the
 * error limit is reached, otherwise the files cannot be reread for analysis.
 * The terminate function will honor the dispose={delete|keep|keeponerror} param.
 * 
 * August 18th, 2011 by Robin T. Miller
 * 	Update StartMonitorThread() to ensure the thread stack isn't too large!
 * 
 * August 16th, 2011 by Robin T. Miller
 * 	Added stop=filename option, to watch for file existance and stop after
 * a pass (therefore, a complete pass is considered a write/read/verify).
 * 
 * August 14th, 2011 by Robin T. Miller
 * 	Enhanced the no-progress message to include the lba and file offset to
 * help with debugging slow/hung I/O (easier to track in traces).
 * 
 * August 5th, 2011 by Robin T. Miller
 * 	Added enable=fsincr option to support file size incrementing. This only
 * has meaning with multiple files, and basically sets the record count to the
 * file number. So, bs=512 files=3 enable=fsincr writes: 512, 1024, 1536 bytes.
 *
 * July 28th, 2011 by Robin T Miller
 * 	When the parent dt receives a signal and starts terminating, added a kill
 * delay to give children a chance to terminate from same process group signal.
 * If parent sends another signal immediately, child may terminate before cleanup
 * and reporting its' statistics. For file systems, files were not getting removed.
 * Note: The default kill delay is 1 second, settable via: kill_delay=value option.
 * 
 * July 27th, 2011 by Robin T. Miller
 * 	Update thread cancel logic when terminating, so set asynchronous aborts,
 * to avoid a race with I/O thread and cancelation points (it may continue to run).
 * Async cancel should terminate the thread immediately, avoiding false errors.
 * Also added a "cancel_delay=value" option to permit an option delay after cancel.
 * 
 * May 6th, 2011 by Robin T. Miller
 * 	Fix bug when step option and slices are speicifed, set the end position.
 * When this is *not* set, then we set a premature EOF/EOM with both options.
 * 
 * March 24th, 2011 by Robin T. Miller
 * 	Adding bufmodes={buffered,unbuffered,cachereads,cachewrites} option.
 * This allows testing different buffering modes on each pass. One or all
 * buffering modes can be specified, and we'll round-robin on each pass.
 * 
 * March 3rd, 2011 by Robin T. Miller
 * 	Allocate the global message buffer much earlier, since report_error()
 * uses this to log messages to syslog(). (gulp, we were seg faulting! :-().
 * 
 * February 16th, 2011 by Robin T. Miller
 * 	In report_error(), ensure we have a valid dip (early errors do not!).
 * Otherwise we seg fault dereferencing a NULL pointer (grrr).
 * 
 * January 15th, 2011 by Robin T. Miller
 *	Added separate options for controlling read/write caching. Well,
 * what this really provides is control of direct I/O for write pass and
 * read pass, to bypass the buffer cache (actually separate DIO control).
 *
 * November 16th, 2010 by Robin T. Miller
 *	Added enable=deleteperpass option to delete files between passes.
 *	This only applies to regular files (of course) on file systems.
 *
 * January 23rd, 2010 by Robin T. Miller
 *	Add support for maxdata= and maxfiles= options to limit the amount of
 * data and files when creating multiple directories and files.
 *
 * December 4th, 2009 by Robin T. Miller
 *	When exiting due to a signal, do NOT exit with the signal number, but
 * detect and map the signal to FAILURE status, easier for scripts to handle.
 * Note: Expected signals, such as SIGALRM, still get handled properly.
 *
 * December 2nd, 2009 by Robin T. Miller
 *	When executing multiple processes, when the parent receives a signal,
 * don't send a signal to child processes, since they automatically receive the
 * signal since they are part of the process group. If the parent sends another
 * signal, the child process will terminate immediately and won't get a chance
 * to perform its' cleanup (reporting stats and deleting files).
 *
 * December 1st, 2009 by Robin T. Miller
 *	Added support for file systems: dirs=, sdirs=, depth=, and dirprefix=.
 *
 * November 25th, 2009 by Robin T. Miller
 *	Added support for a directory path option (dir=dirpath). The dirpath
 * is made unique for multiple processes, so each proc uses its' own directory.
 * The directory is created is it doesn't exist, and automatically removed,
 * assuming all files are deleted when exiting.
 *
 * November 21st, 2009 by Robin T. Miller
 *	Added support for multiple (regular) files via files= option. This
 * option was previous only implemented for multiple tape files, now it is
 * honored for multiple disk files. This is the first step towards improved
 * file system testing (with multiple procs, lots of metedata activity).
 *
 * October 29th, 2009 by Robin T. Miller
 *	Honor the runtime, even when the runtime is greater than the alarm time.
 *	Add support for a keepalive time, so keepalive messages can be used in
 * conjunction with short alarm values doing I/O monitoring.
 *
 * September 2nd, 2009 by Robin T. Miller.
 *	Add nice=value option to allow dt's priority to be altered.
 *
 * February 4th, 2009 by Robin T. Miller.
 *	Change default for eof_status flag to FALSE to map EOF to Successful
 * exit status.  This can be reverted via "enable=eof", but most folks expect
 * Success (0) when tests complete, and checking for EOF status (254) causes
 * more problems than it's worth right now. Legacy scripts may want EOF status.
 *
 * November 14th, 2008 by Robin T. Miller.
 *	When using the step option in the forward direction to regular files,
 * added an end position to be used by the I/O function to stop properly.
 *
 * October 4th, 2008 by Robin T Miller.
 *	Two major changes for native Windows:
 *	- use beginthreadex() instead of CreateThread() for C RTL
 *	- do NOT use ThreadSuspect/ThreadResume, since it may deadlock
 *	  with the multi-threaded LIBCMT and MSVCRT C run-time libraries
 *
 * September 30th, 2008 by Robin T. Miller.
 *	When trigger script exits with TERMINATE or ABORT status code, then
 * ensure the exit status gets set to FAILURE.  This ensures failure is used
 * as our exit status, and with multiple procs, this failed status forced
 * other processes to be aborted whtn oncerr=abort is specified.
 *	In terminate() for Windows, do not continue waiting for processes
 * after calling abort_procs(), since we do not need to reap their status.
 * This can cause the parent dt to hang after being aborted via Ctrl/C.
 *
 * September 9th, 2008 by Robin T. Miller.
 *	Read ThreadSuspend/ThreadResume around calls to keepalive_alarm(),
 * to avoid race conditions (and avoid adding locks).  This function handles
 * no-progress, keepalive messages, and runtime (overloaded).
 *
 * September 8th, 2008 by Robin T. Miller.
 *	Move signal arming earlier, so it's in affect for multiple processes.
 *
 * July 23rd, 2008 by Robin T. Miller.
 *	Add support for a history mechanism.  This saves the specified number
 * of I/O request in a circular history buffer, which is dumped when there's
 * a data corruptiom or an I/O error. New options are history= & hdsize=value.
 * Added dispose=keeponerror option, so file is kept on errors, else deleted.
 *
 * July 15th, 2008 by Robin T. Miller.
 *	Map O_APPEND to FILE_APPEND_DATA for native Windows.
 *
 * June 24th, 2008 by Robin T. Miller.
 *	Add support for new notime=optype to control no-progress operation types.
 *	For parsing errors, log failures as logLevelError instead of logLevelCrit.
 *
 * June 7th, 2008 by Robin T. Miller.
 *	Implement no-progress/keepalive timers for Windows.
 *	Removed PRT_NOIDENT when logging keepalive stats so the process ID is
 * printed with multiple processes. Needed to identify proc!
 *
 * March 11th, 2008 by Robin T. Miller.
 *	Add enable/disable=prefill option to control the automatic pre-filling
 * of the read buffers, which add to the compute (cpu) intensity (step 1).
 * Note: This prefill was needed for simple 4-byte internal data patterns,
 * but is *not* required for IOT and most pattern files since they're unique.
 *
 * December 18th, 2007 by Robin T. Miller.
 *	Add trigargs flag to disable trigger arguments appended to trigger
 * command/script.  This allows a simple trigger command, without the need
 * to generate a script to invoke.
 *
 * December 13th, 2007 by Robin T. Miller.
 *	Add support for logging errors to syslog on Unix based systems.
 *
 * October 24th, 2007 by Robin T. Miller.
 *	When a user pattern is specified, disable the unqiue pattern flag so
 * multiple slices use the users' pattern rather than a unique pattern per proc.
 *
 * October 23rd, 2007 by Robin T. Miller.
 *	When exiting with no-progress trigger script, ensure the exit status
 * is set to the SIGALRM, to ensure a non-zero exit status. Otherwise, SIGALRM
 * is mapped to SUCCESS, which is desired when a runtime=secs expires.
 *
 * September 26th, 2007 by Robin T. Miller.
 *	When IOT pattern is chosen, enable fsalign_flag so variable I/O sizes
 * are aligned to the device size instead of the pattern size. The latter gets
 * set to the max size, thus preventing variable IOT blocks with a regular file.
 * Note: This SNAFU affected variable I/O sizes and random I/O offsets w/IOT!
 *
 * June 22nd, 2007 by Robin T. Miller.
 *	Added "disable=sighup" option to control handling of SIGHUP. Ignoring
 * SIGHUP is desirable when backgrounding 'dt' from shell scripts, so it keeps
 * running when folks log off (most shells send a SIGHUP).  Yea, Unix 'nohup'
 * could be used. Also altered the no-progress message to include device name
 * and "mm:hh:ss" format when the number of seconds is over a minute.
 *
 * October 27th, 2006 by Robin T. Miller.
 *      Fixed logic error where we were reopen'ing the file in preparation
 * for the next write pass, when we've reached the error limit.  This was
 * a problem if oflags=trunc and dispose=keep were used since the resulting
 * output file would be zero length.
 *
 * January 6th, 2007 by Robin T. Miller.
 *	Updated report_record(), used by debug code, since LBA's are now
 * treated as 64-bit values to support capacities over 2TB!
 *
 * October 16th, 2006 by Robin T. Miller.
 *      Added support for "enable=timestamp" option to write a timestamp
 * at the beginning of each data block to help troubleshooting corruptions.
 *
 * October 4th, 2006 by Robin Miller.
 *      If regular file is not open when terminating, do not try to delete.
 *      Added check for non-modulo block size patterns, when random I/O is
 * enabled, to avoid false data corruption when blocks are overwritten.
 *
 * May 16th, 2006 by Robin Miller.
 *	Added options "noprog" and "noprogt" to be used in conjunction with
 * alarm option to detect no I/O progress being made.
 *
 * December 7th, 2005 by Robin Miller.
 *	Added __linux__ conditional for hz initialization, so compiles will
 * work on Red Hat RHEL4 (patch from Alan Brunelle, thanks!).
 *
 * November 22nd, 2005 by Robin Miller.
 *      For Hazard, allow empty prefix string so users can override default.
 *
 * January 4th, 2005 by Robin Miller.
 *	Fix bug in terminate() where signal code was getting overwritten when
 * a timer was active.  Now, only set code with exit_status on SIGALRM.
 *
 * December 23rd, 2004 by Robin Miller.
 *      Added "stats={brief,full,none}" option to provide finer control
 * over pass and total statistics.  This finer control was previously
 * provided by the "verbose" flag, but that was inadequate.
 *
 * December 21st, 2004 by Robin Miller.
 *      Added per pass and total keepalive format control messages.
 *
 * December 20th, 2004 by Robin Miller.
 *      Added support for alarm/keepalive options. The alarm=time specifies
 * the alarm time (same format as runtime), and keepalive=string specifies
 * the alive message with special format control characters to display when
 * the alarm expires.
 *
 * November 22nd, 2004 by Robin Miller.
 *      Change the dump data limit from 64 byte to one block (512 bytes).
 * If read-after-write (raw) is enabled, don't enable FS align logic.
 *
 * November 11th, 2004 by Robin Miller.
 *      For Solaris, since O_DIRECT isn't supported, set dio_flag so
 * directio() API can be used after the file is open'ed.
 *
 * October 21st, 2004 by Robin Miller.
 *      Enable file system alignments by default for random I/O,
 * since variable sizes and offsets cause false data corruptions.
 * When logic is added to track previously written blocks, this
 * can be reverted.
 *
 * July 7th, 2004 by Robin Miller.
 *      For HP-UX, add option qdepth=N" to set the queue depth.
 *
 * June 24th, 2004 by Robin Miller.
 *      Handle errors from ctime_r() - two flavors are around!
 *      Added "enable/disable=fsalign" option to control behaviour
 * of aligning FS offsets and variable record sizes to device size.
 * This option is off by default so random non-device sized values
 * will now be generated (useful for file system testing).  This
 * option can be enabled to return to previous behaviour for FS's.
 *
 * June 22nd, 2004 by Robin Miller.
 *      Added support for triggers on corruption.
 *
 * February 27th, 2004 by Robin Miller.
 *       Switch ctime() to ctime_r() in preparation for threads.
 *
 * February 24th, 2004 by Robin Miller.
 *      Allow parsing of aios=0, to ease supporting of OS's which
 * don't support POSIX AIO.  Makes script writing a little simpler.
 *
 * December 6th, 2003 by Robin Miller.
 *      Conditionalize to exclude tty code.
 *
 * November 17th, 2003 by Robin Miller.
 *	Breakup output to stdout or stderr, rather than writing
 * all output to stderr.  If output file is stdout ('-') or a log
 * file is specified, then all output reverts to stderr.
 *	Parse AIO options, but then emit warning if not supported.
 * This allows portable scripts to be written without parameterizing
 * exlusion of AIO if a platform (OS) does not support it.
 *
 * October 31st, 2003 by Robin Miller.
 *	In terminate(), don't attempt flush if device or file is
 * not open when we receive the alarm signal.
 *
 * September 27th, 2003 by Robin Miller.
 *	Added support for AIX.
 *
 * June 9th, 2003 by Robin Miller.
 *	When terminating as result of alarm, flush output data if we
 * were writing a file.  Thanks to Hank Jakiela for reporting this.
 *
 * March 20th, 2003 by Robin Miller.
 *	Fix bug or'ing O_LARGEFILE into open flags (thanks Kris Corwin!).
 *
 * March 15th, 2003 by Robin Miller.
 *	Added "prefix=" option to support data pattern prefix string.
 *
 * March 14th, 2003 by Robin Miller.
 *	Added "slice=" option to support testing an individual slice.
 *
 * February 23rd, 2002 by Robin Miller.
 *      Make porting changes for HP-UX IA64.
 *
 * May 31st, 2001 by Robin Miller.
 *	Don't allow different data patterns with multiple processes,
 * unless writing to a regular file (each process has own filename).
 *
 * April 13th, 2001 by Robin Miller.
 *	Added "capacity=max" for Tru64 Unix, this will force using the
 * driver returned media capacity.  Prevents lseek/read algorithm when
 * using random I/O too!  Note:  Will inhibit disk driver EOM testing.
 *
 * February 24th, 2001 by Robin Miller.
 *	Add conditionalization for QNX RTP (Neutrino).
 *
 * February 21st, 2001 by Robin Miller.
 *	Disable EOF/EOM exit status by default.  This causes trouble for
 * normal testers.  Use "enable=eof" to reenable previous behaviour.
 *
 * February 6th, 2001 by Robin Miller.
 *	If input file and multiple slices, allow cycling through data
 * patterns, since the file is expected to have been written with unique
 * patterns in each slice region.  Minor update to deleting files too.
 *
 * February 3rd, 2001 by Robin Miller.
 *	Lift restriction of bs= or min= sizes being smaller than
 * sizeof(u_int32) for IOT pattern or lbdata option.  Although this
 * isn't *really* correct, enforcing this breaks numerious scripts.
 * Although smaller works, it's only by luck and the fact we have
 * pad bytes at EOB, which prvented data corruption in the past!
 *
 * January 28th, 2001 by Robin Miller.
 *	Added "slices=value" and "enable/disable=unique" options.
 * The slices option carves up a disk with each process exercising a
 * differnent range of blocks.  The unique pattern option sets up a
 * unique pattern for each process started for slices & regular files.
 *
 * January 26th, 2001 by Robin Miller.
 *	Added report_record() to the report record information.
 *	Added "iodir={forward,reverse}" option to all reverse I/O
 * to rotating media.  Add validation checks both before and after
 * a device is open (mostly random/reverse I/O checks).
 *
 * January 24th, 2001 by Robin Miller.
 *	Added "dsize=value" to set the device block size.
 *	Added "incr=var" option for variable request sizes.
 *	Removed some dead code (#if 0 stuff), to cleanup a bit.
 *	Updates to allow the IOT pattern to use non-modulo 512 byte
 * sizes.  The logic is: 1) user defined "lbs=value", 2) device block
 * size (Tru64 Unix), or 3) default to 512 byte block (original default).
 * This change was initiated by Windows/NT IOT disc using 2KB sector size.
 *
 * January 18th, 2001 by Robin Miller.
 *	When requesting multiple volumes, ensure the tape device gets
 * closed prior to retries, if the rewind operation fails.  Otherwise,
 * the next tape open fails with EBUSY (exclusive open device).
 *
 * January 14th, 2001 by Robin Miller.
 *	Added support for multiple volumes option.
 *
 * December 30th, 2000 by Robin Miller.
 *	Make changes to build using MKS/NuTCracker product.
 *
 * November 19th, 2000 by Robin Miller.
 *	Add missing enable/disable=fsync goto label statements.
 *
 * November 10th, 2000 by Robin Miller.
 *	Added sanity check to warn user about unpredictable results
 * when writing to a disk with multiple procs and multiple passes.
 *
 * November 8th, 2000 by Robin Miller.
 *	Added "disable=cerrors" to disable device close errors.
 * [ Note: This is really a workaround for the Linux tape driver. ]
 *	In HandleMultiVolume(), if closing the device fails, then
 * return that failure to abort the test.  With tapes, this means
 * flushing the buffered data or writing filemarks has failed.
 *
 * October 2nd, 2000 by Robin Miller.
 *	Enhanced report_error() to display errno value (same as Scu).
 *
 * August 22nd, 2000 by Robin Miller.
 *	Added boolean flags to track user set min, max, & incr values.
 *
 * July 14th, 2000 by Robin Miller.
 *	Added fsync_flag to control sync'ing data to disk files.
 *
 * May 8th, 2000 by Robin Miller.
 *	Adding parsing of "version" option, which is used to only
 * display the version string, dtversion() in file dtusage.c
 *
 * May 5th, 2000 by Robin Miller.
 *	Set proper exit code in terminate(), when exiting due to
 * an alarm, i.e., runtime= option.  Previously, the end of file
 * exit status was being ignored and we exited with failure status.
 *
 * April 25th, 2000 by Robin Miller.
 *	Fix problem of not breaking out of test loop if the error
 * limit has been reached on previous pass.
 *
 * March 28th, 2000 by Robin Miller.
 *	Modify "position=value" to accept a large numeric value,
 * otherwise we were limited to 32 bit value on non-64bit systems.
 * Do the same thing for "step=value" for 64-bit file offsets.
 * When using the "runtime=" option, when the alarm expires and
 * we call terminate() to exit, look at the exit_status variable
 * instead of error_count for errors, so we don't miss errors!
 *
 * March 27th, 2000 by Robin Miller.
 *   o	Fixed parsing of a couple flags, including "flags=direct".
 *   o	Added "capacity=value" option to set the drive capacity.
 *
 * March 20th, 2000 by Robin Miller.
 *	Don't allow a pass limit of zero.  This also avoids a
 * core dump when preparing statistics, since the active device
 * never got setup.
 *
 * March 2nd, 2000 by Robin Miller.
 *	In HandleMultiVolume(), reset the exit status to SUCCESS,
 * since this got set to END_OF_FILE earlier.  Failure to do this
 * means we exit with an END_OF_FILE (254) status (no good :-).
 *
 * February 17th, 2000 by Robin Miller.
 *	Adding better support for multi-volume tape testing.
 *
 * January 17th, 2000 by Robin Miller.
 *	In copy mode, is input file is stdin, don't do verify.
 *	Enable random I/O, for ralign, rlimit, or rseed options.
 *
 * January 14th, 2000 by Robin Miller.
 *	Don't delete the output file unless we're in test mode.
 *
 * January 6th, 2000 by Robin Miller.
 *	Added support for multi-volume media (lot's of changes).
 *
 * January 1st, 2000 by Robin Miller.
 *	Added read after write support, "enable=raw" option.
 *
 * December 31st, 1999 by Robin Miller.
 *	Added "rseed=" option, so user can specify the random seed.
 *	Modify reopen_file logic to use O_RDWR if skip_count exists.
 *
 * November 11th, 1999 by Robin Miller.
 *	Added logging of diagnostic information to event logger.
 *
 * November 10th. 1999 by Robin Miller.
 *	Fixed parsing of "dispose=delete".
 *
 * November 9th, 1999 by Robin Miller.
 *	Modify logic associated with making stderr stream buffered.
 *
 * August 26th, 1999 by Robin Miller.
 *	If during the write pass no data was transferred, don't do
 * the read pass since obviously this will result in a compare error.
 *
 * August 7th, 1999 by Robin Miller.
 *	Allow enabling open w/O_LARGEFILE via "flags=large", incase
 * _FILE_OFFSET_BITS=64 does _not_ enable this by default.
 *
 * July 22nd, 1999 by Robin Miller.
 *	Added support for IOT (DJ's) test pattern.
 * 
 * July 19th, 1999 by Robin Miller.
 *	Add flag to control log file header normally displayed.
 *
 * June 28, 1999 by Robin Miller.
 *	For 32-bit systems, change count and limit variables from
 * u_long to double, since u_long limits us to 4GB (too small).
 *
 * May 27, 1999 by Robin Miller.
 *	Merge in George Bittner's changes for micro-second delays.
 *	Conditionalized all common/output file open flags.
 *
 * April 8, 1999 by Robin Miller.
 *	Merge in Jeff Detjen's changes for table()/sysinfo timing.
 *
 * April 7, 1999 by Robin Miller.
 *	On DEC systems, obtain tick/second via sysconf(_SC_CLK_TCK).
 *
 * December 21, 1998 by Robin Miller.
 *	Add pasing of "enable=resets", which enables tape repositioning
 * logic when bus/device resets are detected by DUNIX EEI status codes.
 *
 * December 19, 1998 by Robin Miller.
 *	- Disable setbuf() for stderr... screws up log files.
 *	- Write cmd line and version to log file for reference.
 *
 * December 16, 1998 by Robin Miller.
 *	Merge in changes made by George Bittner:
 *	- set random_seed using times() instead of time(0).
 *	- remove DLM_VALB, per Dan Christians' recommendation.
 *
 * October 29, 1998 by Robin Miller.
 *	Implement a random I/O data limit, instead of using the normal
 * data limit variable (not good to dual purpose this value).
 *
 * October 22, 1998 by Robin Miller. (Happy Birthday Mom!)
 *	When specifying a runtime, ensure we break out of the
 * passes loop if we exceed the error limit.  Previously, we'd
 * loop (possibly with error) for the duration of runtime :-)
 *
 * June 16, 1998 by Robin Miller.
 *	Add common open "flags={excl,ndelay,nonblock,rsync}".
 *	Add output (write) open "oflags={defer,dsync,trunc}".
 *
 * April 29, 1998 by Robin Miller.
 *	Add support for an alternate device directory.
 *
 * April 7, 1998 by Robin Miller.
 *	Setup the pattern as a pattern string, so non-modulo
 *	sizeof(pattern) read counts will data compare properly.
 *
 * March 20, 1998 by Robin Miller.
 *	When terminating, call close function before reporting stats,
 *	since in the case of AIO the I/O rundown updates statistics
 *	with outstanding requests, when we're aborted by a signal.
 *
 * May 14, 1997 by Robin Miller.
 *	In report_error(), set exit value to FAILURE instead of errno
 *	since this makes detecting errors easier in scripts.
 *
 * May 13, 1997 by Robin Miller.
 *	If a "skip=" count is specified with an output file "of=",
 *	open the file for R/W access since skips are accompished via
 *	read()'s of record size.
 *
 * March 27, 1997 by Ali Eghlima.
 *      Added cluster support, so more than one process or one system
 *      can access a resource. dlm are being used to synchronize all
 *      access.
 * 
 * March 7, 1997 by Robin Miller.
 *	If a copy or verify operation is selected, and a data limit
 *	is specified, then double the data limit to account for double
 *	the I/O's.  Previously, only half of the desired data limit was
 *	copied and/or verified.
 *
 * February 3, 1997 by Robin Miller.
 *	Check status from closing file descriptor, and if it's not
 *	SUCCESS, use this for the exit status.  For tapes, deferred
 *	writes and failure to write file marks occur at close time.
 *
 * March 30, 1996 by Robin Miller.
 *	When writing, now default to an infinite record limit, so
 *	writes stop when EOF is reached (disks and tapes only).
 *
 * February 29, 1996 by Robin Miller.
 *	Added callouts to setup data limit for disk random I/O.
 *
 * February 28, 1996 by Robin Miller.
 *	Added support for copying and verifying device/files.
 *
 * February 17, 1996 by Robin Miller.
 *	Add "enable=spad" option to control checking of pad bytes
 *	when long reads of short records is performed, since some
 *	controllers corrupt data bytes following the short record.
 *	[ NOTE:  At DEC, this action was deemed acceptable, since
 *	  the requester stated the driver could trash a larger buf. ]
 *
 * December 6, 1995 by Robin Miller.
 *	Add "ttymin=value" option to give user control over tty VMIN.
 *
 * November 19, 1995 by Robin Miller.
 *	When the device type is a disk, default min_size & incr_count to
 *	BLOCK_SIZE (512) instead of 1 (which is non-modulo for disks).
 *
 * November 18, 1995 by Robin Miller.
 *	Removing unaligned data access (ade) test code (code cleanup).
 *
 * July 24, 1995 by Robin Miller.
 *	Changed O_NDELAY to O_NONBLOCK which is defined by POSIX.  They are
 *	supposed to do the same thing, but they _do_ have different values.
 *	[ NOTE: This is only used for serial line modem testing. ]
 *
 * July 22, 1995 by Robin Miller.
 *	Add additional checking on "pattern=string" to avoid ambiguity
 *	with 4-byte hex data pattern strings... which is misleading).
 *
 * July 15, 1995 by Robin Miller.
 *	Add "oncerr=action" option to control child process
 *	error processing.
 *
 * July 7, 1995 by Robin Miller.
 *	Add "dlimit=value" option to override default dump limit.
 *
 * July 6, 1995 by Robin Miller.
 *	Enable dumping of data bytes on compare errors by default,
 *	since this program is used mainly as a diagnostic tool, and
 *	we now limit the number of bytes dumped.
 *
 * November 5, 1994 by Robin Miller.
 *	Don't set SIGCHLD signal to SIG_IGN (set to SIG_DFL) or else
 *	waitpid() won't detect any child processes (OSF R1.3 and QNX).
 *
 * September 23, 1994 by Robin Miller.
 *      Make changes necessary to build on QNX 4.21 release.  This
 *      required changing O_DSYNCH to O_DSYNC, and O_FSYNCH to O_SYNC.
 *
 * November 11, 1993 by Robin Miller.
 *	Removed code which was inadvertantly disabling data compares
 *	when there was no output file and verify was disabled.  This
 *	caused data comparisions to be disabled for terminal devices,
 *	now that the code has been rewritten/restructured (shit!!!).
 *
 * October 31, 1993 by Robin Miller.
 *	Enhance device type setup and honor user specified device type.
 *
 * October 28, 1993 by Robin Miller.
 *	Correct problem during loopback testing, where the device info
 *	structure fd's were not marked closed due to two places where
 *	close() was called directly (oops, missed a couple changes).
 *	After forking, display which process is the reader and writer.
 *
 * October 11, 1993 by Robin Miller.
 *	Conditionalize SunOS code (4.1.2 used) to avoid using strerror()
 *	function for obtaining error messages (return to perror() method).
 *
 * October 7, 1993 by Robin Miller.
 *	Add appropriate casting to block size checking, use ssize_t to
 *	prevent negative block sizes which don't work with read & write
 *	system calls (even though the count arg is declared as size_t).
 *
 * September 16, 1993 by Robin Miller.
 *	Properly report write pass count when read verify is disabled.
 *	Only update data pattern when writing files or loopback enabled
 *	when multiple passes specified (pattern cannot change for reads).
 *	Support "enable=loop" to enable loopback operation, rather than
 *	requiring both the same input & output devices (need only one).
 *	Added "oflags={append,sync}" for DEC OSF/1 systems (write opts).
 *
 * September 15, 1993 by Robin Miller.
 *	Added additional check for FIFO's prior to opening the device
 *	since O_NONBLOCK flag must be set to keep open() from blocking.
 *
 * September 8, 1993 by Robin Miller.
 *	Moved generic test functions into file dtgen.c.
 *
 * September 7, 1993 by Robin Miller.
 *	Moved tty specific code into dttty.c.  This code is dispatched
 *	to automatically after being setup in the device info structure.
 *
 * September 4, 1993 by Robin Miller.
 *	Lots of restructuring & code cleanup.  Nearly all testing is
 *	now appropriately parameterized (helps speed & new tests).
 *
 * September 3, 1993 by Robin Miller.
 *	Dispatch to test functions via function lookup table in
 *	preparation for device specific tests.
 *
 * September 1, 1993 by Robin Miller.
 *	Added "min=value", "max=value", and "incr=value" options for
 *	testing variable length records (mainly for tape devices).
 *
 * August 31, 1993 by Robin Miller.
 *	Added "align=rotate" option to rotate the starting data buffer
 *	address through sizeof(ptr) to force unaligned buffer accesses.
 *	This feature tests special handling of unaligned DMA addresses.
 *	Added "pattern=incr" option to use incrementing data pattern.
 *
 * August 27, 1993 by Robin MIller.
 *	Added support for DEC OSF/1 POSIX Asynchronous I/O (AIO).
 *
 * August 20, 1993 by Robin Miller.
 *	Added handling of reading & writing multiple tape files.
 *
 * August 18, 1993 by Robin Miller.
 *	Added "step=" option to specify a step offset for seeks.
 *	This is the number of bytes stepped after an I/O request.
 *
 * August 17, 1993 by Robin Miller.
 *	Added reporting of start & end times, time of errors, and
 *	added "runtime=" option to specify how long to run.
 *
 * August 13, 1993 by Robin Miller.
 *	Added alternate data patterns to use with multiple passes.
 *
 * August 5, 1993 by Robin Miller.
 *	Added "files=value" option for processing tape files.
 *
 * August 3, 1993 by Robin Miller.
 *	Added "procs=value" option to create multiple processes.
 *
 * September 19, 1992 by Robin Miller.
 *	Initialize flush_flag to TRUE so flushing of tty I/O queues
 *	gets done by default to discard any left over junk.
 * 
 * September 18, 1992 by Robin Miller.
 *	Added calls to save & restore terminal characteristics.
 *
 * September 17, 1992 by Robin Miller.
 *	Added parsing for "pattern=string" to allow ASCII string.
 *
 * September 12, 1992 by Robin Miller.
 *	Ensure the stderr stream is fully buffered, so the total time
 *	is not affected by flushing previous statistics.
 *
 * September 11, 1992 by Robin Miller.
 *	Added "oflags={cache,dsync,fsync,temp}" options to allow testing
 *	the affect of these open flags on QNX systems.
 *
 * September 10, 1992 by Robin Miller.
 *	Added parsing of MARK & SPACE parity for QNX Operating System.
 *
 * September 9, 1992 by Robin Miller.
 *	Allow loopback to same tty port (avoid exclusive open).
 *
 * September 5, 1992 by Robin Miller.
 *	Initial port to QNX 4.1 Operating System.
 *
 * September 3, 1992 by Robin Miller.
 *	Make changes necessary to remove BSD dependencies.
 *
 * August 19, 1992 by Robin Miller.
 *	Added support for testing tty modem control.
 *
 * May 25, 1992 by Robin Miller.
 *	Don't set exclusive open mode for terminal device if debug is
 *	enabled, so "stty -a" can be done on terminal under test.
 *
 * May 22, 1992 by Robin Miller.
 *	Control / force kernel address data exception via flag.
 *	Added option "enable=ade" (address data exception).
 *
 * April 24, 1992 by Robin Miller.
 *	Inform user that either a record count or a data limit must be
 *	specified.  Added flags to determine if we are reading stdin or
 *	writing to stdout streams.
 *
 * March 11, 1992 by Robin Miller.
 *	Changes necessary for port to 64-bit Alpha architecture.
 *
 * October 16, 1990 by Robin Miller.
 *	Added "align=offset" option to align memory buffers at a specific
 *	offset.  The default is page aligned.
 *
 * October 9, 1990 by Robin Miller.
 *	Added "hz=ticks" option to allow the ticks per second value to
 *	be specified.  On VAX systems, this is consistent (100), but on
 *	MIPS systems it various and is setup at boot time in the machine
 *	dependent code.
 *
 * August 21, 1990 by Robin Miller.
 *	Changed exit status so scripts can detect and handle errors
 *	based on the exit code.  If not success, fatal error, or end
 *	of file/tape, the exit code is the error number (errno).
 *
 * August 21, 1990 by Robin Miller.
 *	Added "position=offset" option to position to specified offset
 *	before starting test.
 *
 * August 16, 1990 by Robin Miller.
 *	Added "enable=coredump" option so if exiting with error status,
 *	we'll generate a core dump for analysis purposes.
 *
 * August 8, 1990 by Robin Miller.
 *	Changed malloc() to valloc() to align buffer on page boundry.
 *	On some archetectures, this results on better performance to
 *	raw devices since the DMA is done directly to the users' buffer.
 *
 * August 2, 1990 by Robin Miller.
 *	Added "pf=file" to specify a pattern file to use.  In this
 *	case, the contents of the specified file are used for the
 *	data pattern.
 *
 * April 11, 1990 by Robin Miller.
 *	Added "enable=mmap" option to enable memory mapped I/O.
 *
 * March 22, 1990 by Robin Miller.
 *	Added "dispose={delete|keep}" option to control deleting the
 *	output file at the end of testing.  "delete" is the default
 *	action, to avoid leaving test files around.
 *
 * Novemeber 9, 1989 by Robin Miller.
 *	Add additional delay commands (cdelay=, rdelay=, wdelay=) to
 *	help with testing and debugging various devices.  These aren't
 *	normally enabled and don't appear in the help section.
 *
 * Novemeber 6, 1989 by Robin Miller.
 *	Allow start delay (sdelay=) and end delay (edelay=) to be used
 *	with any device, not just terminals.  The parallel output device
 *	needs an end delay to allow the parallel input device to reopen
 *	during multiple passes (can't disable cycle request).
 *
 * November 3, 1989 by Robin Miller.
 *	Change open mode for output files from read/write (O_RDWR) to
 *	write only (O_WRONLY) so write only devices can be tested.
 *
 * October 16, 1989 by Robin Miller.
 *	Made flushing of input queue before testing optional via
 *	the "enable=flush" command.  This caused a timing problem
 *	where occasionally the writer started before the reader.
 *
 * October 4, 1989 by Robin Miller.
 *	Added fsync() system call to force in-core buffers to disk
 *	before reporting statistics after writing the file.
 *
 * September 27, 1989 by Robin Miller.
 *	Display statistics at end of each read/write pass by default.
 *	Added enable/disable=pstats to control end of pass statistics.
 *	Added enable/disable=compare to control data comparisions.
 *
 * September 18, 1989 by Robin Miller.
 *	Allow both an input and an output device to be specified.
 *	This was done mainly for terminal devices so a child could
 *	be forked to allow proper synchronization.
 *
 * July 25, 1989 by Robin Miller.
 *	Added support for testing terminal ports.  New options are:
 *		speed=, timeout=, parity=, flow=, sdelay=, edelay=
 *
 * January 25, 1989 by Robin Miller.
 *	Added reporting of pass statistics if debugging is enabled
 *	so write/read elapsed times can be determined.
 *
 * December 8, 1988 by Robin Miller.
 *	Added catching of software terminate signal (SIGTERM) so the
 *	final statistics will be displayed before exiting.
 */

pthread_attr_t thread_attrs;
pthread_attr_t *tattrp = &thread_attrs;
pthread_t ParentThread;			/* The parents' thread.		*/
pthread_t IO_Thread;			/* One IO thread to get started	*/
pthread_t iotuneThread;			/* The IO tuning thread.	*/
pthread_t MonitorThread;		/* The monitoring thread.	*/
#if defined(WIN32)
DWORD ParentThreadId;			/* The parents' thread ID.	*/
DWORD IO_ThreadId;			/* One IO thread to get started	*/
DWORD iotuneThreadId;			/* The IO tuning thread ID.	*/
DWORD MonitorThreadId;			/* The monitoring thread ID.	*/
#else /* !defined(WIN32) */
# define ParentThreadId		ParentThread
# define IO_ThreadId		IO_Thread
# define iotuneThreadId		iotuneThread
# define MonitorThreadId	MonitorThread       
#endif /* defined(WIN32) */

/*
 * Forward References: 
 */
void catch_signals(void);
void ignore_signals(void);
void *docopy(void *arg);
void *doio(void *arg);
int finish_test(dinfo_t *dip, int code, bool do_cleanup);
void *do_monitoring(void *arg);
int SetThreadCancelType(dinfo_t *dip, int cancel_type);
char *decodeCancelType(int cancel_type);

int init_pthread_attributes(dinfo_t *dip);
int StartMonitorThread(dinfo_t *dip, int interval);

void parse_args(dinfo_t *dip, int argc, char **argv);
void SignalHandler(int signal_number);
void finish_exiting(dinfo_t *dip, int code);

static dinfo_t *init_device_information(void);
int start_iotuning(dinfo_t *dip);
void *do_iotune_file(void *arg);
int HandleThreads(dinfo_t *dip, int code);
void report_times(time_t initiated_time, time_t current_time);

/*
 * Variable Declarations:
 */
volatile hbool_t CmdInterruptedFlag;	/* User interrupted command.	*/ 
bool	core_dump = FALSE;		/* Generate core dump on errors	*/
/* TODO: Couple more functions require dip! */
bool	debug_flag = FALSE;		/* Enable debug output flag.	*/
bool	mDebugFlag = FALSE;		/* Memory related debug flag.	*/
bool	pDebugFlag = FALSE;		/* Process related debug flag.	*/
bool	tDebugFlag = FALSE;		/* Thread related debug flag.	*/
bool	eof_status_flag = FALSE;	/* Controls EOF exit status.	*/
int	exit_status = SUCCESS;		/* Normal success exit status.	*/
/* TODO: Exposing logpid to printing functions? */
bool	hazard_flag = FALSE;		/* Emit Hazard RPCLOGn: prefix.	*/
bool	nate_flag = FALSE;		/* Emit NATE log file prefix.	*/

int	nice_value = 0;			/* Apply nice value when <> 0.	*/
int	term_wait_retries = 0;		/* Termination wait retries.	*/
int	term_wait_timeout = 0;		/* Termination wait timeout.	*/
bool	sighup_flag = TRUE;		/* Hangup signal control.	*/
v_bool	terminating_flag = FALSE;	/* Program terminating flag.	*/
int	page_size = 0;			/* Define number of bytes/page.	*/
u_int	cancel_delay = DEFAULT_CANCEL_DELAY;
					/* Time to delay before cancel.	*/
u_int	kill_delay = DEFAULT_KILL_DELAY;/* Delay before children kill.	*/

#if defined(SOLARIS) || defined(OSFMK) || defined(__QNXNTO__) || defined(AIX) || defined(__linux__)
clock_t hz;
#else
clock_t	hz = HZ;			/* Default clock ticks / second	*/
#endif

/* Note: These will become unique per thread w/log option! */
FILE	*efp;				/* Default error data stream.	*/
FILE	*ofp;				/* Default output data stream.	*/
char	*cmdname;			/* Pointer to our program name.	*/
char	*dtpath;			/* Path to our dt executable.	*/

/*
 * Pointers to various device information.
 */
struct dinfo *active_dinfo;		/* Active device information.	*/
struct dinfo *input_dinfo;		/* Input device information.	*/
struct dinfo *output_dinfo;		/* Output device information.	*/

bool	StdinIsAtty;			/* Standard input isatty flag.  */
bool	StdoutIsAtty;			/* Standard output isatty flag. */
bool	StderrIsAtty;			/* Standard error isatty flag.  */

/*
 * Default alarm message is per pass statistics, user can override.
 */
char    *keepalive0 = "%d Stats: mode %i, blocks %l, %m Mbytes, pass %p/%P,"
                      " elapsed %t";
char    *keepalive1 = "%d Stats: mode %i, blocks %L, %M Mbytes, pass %p/%P,"
                      " elapsed %T";
                                        /* Default keepalive messages.  */
/*
 * When stats is set to brief, these message strings get used:
 */
char    *pass_msg = "pass %p/%P, %l blocks, %m Mbytes, %c records,"
                    " errors %e/%E, elapsed %t";
                                        /* Per pass keepalive message.  */
char    *totals_msg = "%d Totals: %L blocks, %M Mbytes,"
                      " errors %e/%E, passes %p/%P, elapsed %T";
                                        /* Totals keepalive message.    */ 

/*
 * Data patterns used for multiple passes.
 */
u_int32 data_patterns[] = {
	DEFAULT_PATTERN,
	0x00ff00ffU,
	0x0f0f0f0fU,
	0xc6dec6deU,
	0x6db6db6dU,
	0x55555555U,
	0xaaaaaaaaU,	/* Complement of previous data pattern.		 */
	0x33333333U,	/* Continuous worst case pattern (media defects) */
	0x26673333U,	/* Frequency burst worst case pattern #1.	 */
	0x66673326U,	/* Frequency burst worst case pattern #2.	 */
	0x71c7c71cU,	/* Dibit worst case data pattern.		 */
	0x00000000U,
	0xffffffffU,
};
int npatterns = sizeof(data_patterns) / sizeof(u_int32);

/*
 * This table is indexed by the operation type (enum optype):
 */
optiming_t optiming_table[] =
{
  /*  Operation Type  Control Flag      Name       */
    { NONE_OP,		FALSE,		NULL       },
    { OPEN_OP,		TRUE,		"open"     },
    { CLOSE_OP,		TRUE,		"close"    },
    { READ_OP,		TRUE,		"read"     },
    { WRITE_OP,		TRUE,		"write"    },
    { IOCTL_OP,		TRUE,		"ioctl"    },
    { FSYNC_OP,		TRUE,		"fsync"    },
    { MSYNC_OP,		TRUE,		"msync"    },
    { AIOWAIT_OP,	TRUE,		"aiowait"  }
};

/*
 * The mainline sets this up, need common for logging anywhere!
 */
void
log_header(dinfo_t *dip)
{
    /*
     * Write the command line for future reference.
     */
    Lprintf(dip, "Command Line:\n\n    %c ", getuid() ? '%' : '#');
    Lprintf(dip, "%s ", dip->di_cmd_line);
    Lprintf(dip, "\n\t--> %s <--\n", version_str);
    if (dip->di_debug_flag || dip->di_Debug_flag || dip->di_rDebugFlag | dip->di_tDebugFlag) {
	Lprintf(dip, "\n");
    }
    Lflush(dip);
    return;
}

/*
 * main() - Start of data transfer program.
 */
int
main (int argc, char **argv)
{
	struct dinfo *dip, *dinfo;
	char *tmp, *devs;
	int status;
#if defined(WIN32)
        SYSTEM_INFO pgsize;
#endif /* defined(WIN32) */

	/* TODO: active dinfo must go for multiple threads! */
	active_dinfo = dip = dinfo = init_device_information();

	dtpath = argv[0];
	/* Note: For Windows we need to check both path separators! (Cygwin) */
	tmp = strrchr (argv[0], '/');
#if defined(WIN32)
	if (tmp == NULL) {
	    tmp = strrchr (argv[0], '\\');
	}
#endif /* defined(WIN32) */
	cmdname = tmp ? &(tmp[1]) : argv[0];
	dip->di_process_id = getpid();
#if defined(_QNX_SOURCE) && defined(_QNX_32BIT)
	page_size = 4096;	/* Not sure how to query for this... */
#elif defined(__unix)
	hz = sysconf(_SC_CLK_TCK);
	page_size = sysconf(_SC_PAGESIZE);
#elif defined(WIN32)
	GetSystemInfo(&pgsize);
	dip->di_process_id = GetCurrentProcessId();
	page_size = pgsize.dwPageSize;
	/*
	 * Convert the pseudo handle into a real handle by duplicating!
	 */
	if (!DuplicateHandle(GetCurrentProcess(), GetCurrentThread(),
		     GetCurrentProcess(), &ParentThread, 0, TRUE, DUPLICATE_SAME_ACCESS)) {
	    wPerror("DuplicateHandle() failed\n");
	}
	/*
	 * Create a mutex to synchronize multiple threads when exiting.
	 */
	exitMutex = CreateMutex(NULL,	/* Default security attributes. */
				FALSE,	/* Initially not owned. */
				NULL);	/* Unnamed mutex. */
	if (exitMutex == NULL) {
	    Perror("CreateMutex() failed");
	    finish_exiting(NULL, FAILURE);
	}
#else /* !defined(_QNX_SOURCE) && !defined(_QNX_32BIT) */
	page_size = getpagesize();
#endif /* defined(_QNX_SOURCE) && !defined(_QNX_32BIT) */
	/* TODO: More cleanup! */
#if defined(OSFMK) || defined(__QNXNTO__) || defined(WIN32)
	hz = CLK_TCK;			/* Actually a libc function. */
#endif /* defined(OSFMK) || defined(__QNX_NTO__) defined(WIN32) */

        CmdInterruptedFlag = False;
	/* That's right, one day we'll have an interactive mode! */
        StdinIsAtty = isatty (fileno(stdin));
        StdoutIsAtty = isatty (fileno(stdout));
        StderrIsAtty = isatty (fileno(stderr));

	(void)init_pthread_attributes(dip);

	parse_args(dip, argc, argv);

	if (!dip->di_input_file && !dip->di_output_file) {
	    LogMsg (efp, logLevelCrit, 0,
		    "You must specify an input file, an output file, or both.\n");
	    finish_exiting(dip, FATAL_ERROR);
	}
	devs = (dip->di_input_file) ? dip->di_input_file : dip->di_output_file;
	if ( EQS(devs, ",") ) {
	    dip->di_multiple_devs = TRUE;
	}

	/*
	 * Catch some of the pattern option conflicts, misleading!
	 */
	if ((dip->di_iot_pattern || dip->di_incr_pattern || dip->di_pattern_size) && dip->di_pattern_file) {
	    LogMsg (efp, logLevelCrit, 0,
		    "Multiple pattern options selected, please choose only one!\n");
	    finish_exiting(dip, FATAL_ERROR);
	}

	/*
	 * Set the default display data format, if not specified by the user.
	 */
	if (dip->di_data_format == NONE_FMT) {
	    dip->di_data_format = BYTE_FMT;
	}

	/*
	 * Options parsed, validate options, do initialization, and open
	 * input & output files to be tested.
	 */
	dip->di_program_start = time((time_t) 0);	/* Record our start time. */

	/*
	 * If a log file was specified, redirect stderr to that file.
	 */
	if (dip->di_log_file) {
	    ofp = efp;			/* Send all output to stderr. */
            /*
             * Note: The child flag is enabled for Windows children.
             */
	    if (dip->di_unique_log && dip->di_child_flag) {
		char *logp = NULL;	/* Threaded dt will cleanup! */
		/* Add the process ID, if not part of the log format. */
                if ( strstr(dip->di_log_file, "%pid") == (char *) 0 ) {
		    logp = dip->di_log_file = make_unique_file(dip, dip->di_log_file);
                }
		/* Translate any other format strings. */
		dip->di_log_file = FmtLogFile(dip, dip->di_log_file);
		if (logp) free(logp);
	    } else if (strstr (dip->di_log_file, "%")) {
		dip->di_log_format = strdup(dip->di_log_file);
                dip->di_log_file = FmtLogFile(dip, dip->di_log_file);
            }
	    if (freopen (dip->di_log_file, (dip->di_logappend_flag) ? "a" : "w", efp) == NULL) {
	        Perror ("freopen() of %s failed, exiting...", dip->di_log_file);
		finish_exiting(dip, FAILURE);
	    }
	}

	/*
	 * Make stderr buffered, so timing is not affected by output.
	 */
	dip->di_log_bufsize = LOG_BUFSIZE;
	dip->di_log_buffer = (char *)Malloc(dip->di_log_bufsize);

	/*
	 * The concept here is simple, set stderr buffered so multiple processes
	 * don't have their output intermixed.  This piece of code has been very
	 * problematic, so it you have problems with garbled output, remove it.
	 */
	dip->di_log_bufptr = dip->di_log_buffer;

	/*
	 * Since stderr is normally unbuffered, we make it buffered here.
	 * The reason for this is to keep text from getting fragnmented.
	 */
	if ( StderrIsAtty ) {
	    dip->di_stderr_buffer = Malloc(LOG_BUFSIZE);
	    /*
	     * Can't use log buffer, or we get undesirable results :-)
	     */
	    if (setvbuf(efp, dip->di_stderr_buffer, _IOFBF, LOG_BUFSIZE) < 0) {
		Perror ("setvbuf() failed, exiting...");
		exit (FAILURE);
	    }
	}

	/*
	 * Save the command line for logging later (log file or syslog).
	 */
	{
	    int arg;
	    char *buffer, *bp;

	    bp = buffer = (char *)Malloc(LOG_BUFSIZE);
	    for (arg = 0; arg < argc; arg++) {
		bp += sprintf(bp, "%s ", argv[arg]);
	    }
	    sprintf(bp, "\n");
	    dip->di_cmd_line = Malloc(strlen(buffer)+1);
	    strcpy(dip->di_cmd_line, buffer);
	    free(buffer);
	}

	/*
	 * Write the command line (if enabled).
	 */
	if ( dip->di_header_flag &&
	     (dip->di_log_file || (!StdoutIsAtty && !dip->di_child_flag)) ) {
	    log_header(dip);
	}

	/*
	 * Users can also use "enable=logpid" to log this with messages.
	 */
	if (dip->di_debug_flag || dip->di_pDebugFlag || dip->di_tDebugFlag) {
	    Printf("Parent process ID is %d, Thread ID is %u\n",
		   dip->di_process_id, ParentThreadId);
	    if (dip->di_tDebugFlag) {
		Printf("INFO: The sizeof(time_t) is %d bytes!\n",  sizeof(time_t));
	    }
	}

	/*
	 * Ok, sanity check options that are allowing folks to shoot themselves
	 * in the foot (sometimes due to hardcoded automation) when adding options
	 * via a pass-through parameter.
	 * 
	 * Note: Done here to avoid multiple messages from each process.
	 * Also Note: This check belongs in dtgen.c with others, which should
	 *  be switched to when slices (procs) become multiple threads.
	 */ 
#if defined(O_TRUNC)
	if ( (dip->di_num_slices && (dip->di_wopen_flags & O_TRUNC)) ) {
	    if (dip->di_verbose_flag) {
		Printf("Warning: Disabling file truncate flag, not valid with multiple slices!\n");
	    }
	    dip->di_wopen_flags &= ~O_TRUNC;
	}
#endif /* defined(O_TRUNC) */
	if (dip->di_num_slices && dip->di_delete_per_pass) {
	    if (dip->di_verbose_flag) {
		Printf("Warning: Disabling delete per pass flag, not valid with multiple slices!\n");
	    }
	    dip->di_delete_per_pass = FALSE;
	}
	
	/*
	 * Since Windows does NOT have a fork() API, we will doing
	 * a CreateProcess() and need the original command line,
	 * without options like procs= (of course).
	 * 
	 * Note: We also need this for *nix dt for multiple devices.
	 */
	if (dip->di_num_procs || dip->di_num_slices || dip->di_multiple_devs) {
	    int arg;
	    char *bp;
	    bp = dip->di_dtcmd = (char *)Malloc(LOG_BUFSIZE);
	    for (arg = 0; arg < argc; arg++) {
		char *opt = argv[arg];
		/* Options to skip. */
		if ( !dip->di_multiple_devs && EQL(opt, "procs=", 6) ) {
		    continue;
		} else if ( dip->di_num_slices &&
			    ( EQL(opt, "enable=", 7) &&
			      EQS(opt, "deleteperpass") ) ) {
		    continue; /* Note: May lose other flags! */
		} else if ( dip->di_num_slices &&
			    ( EQL(opt, "oflags=", 7) &&
			      EQS(opt, "trunc") ) ) {
		    continue; /* Note: May lose other flags! */
		} else if ( dip->di_multiple_devs &&
			    (EQL(opt, "if=", 3) && EQS(opt, ",")) ||
			    (EQL(opt, "of=", 3) && EQS(opt, ",")) ) {
		    continue; /* Skip input or output devices. */
		} else if ( EQS(opt, "keepalive=") ||
			    EQS(opt, "prefix=")    ||
			    EQS(opt, "trigger=cmd:") ) {
		    /* Quote the entire option! */
		    bp += sprintf(bp, "\"%s\" ", argv[arg]);
		} else {
		    bp += sprintf(bp, "%s ", argv[arg]);
		}
	    }
	    bp--;
	    if (*bp == ' ') *bp = '\0';
	}

	/* Multiple Device Support! */
	if ( dip->di_multiple_devs ) { /* Multiple devices? */
	    if ( start_devs(dip) ) {
		if (dip->di_iotune_file) {
		    (void)start_iotuning(dip);
		}
		catch_signals();
		await_procs(dip);	/* Parent waits. */
		if (dip->di_debug_flag || dip->di_pDebugFlag) {
		    Printf ("Parent exiting with status %d...\n", exit_status);
		}
		exit (exit_status);
	    }
	}
	
	/*
	 * Multiple Directory Sanity Checks:
	 */
	dip->di_multiple_dirs = (dip->di_dir || dip->di_user_dir_limit || dip->di_user_subdir_limit || dip->di_user_subdir_depth);
	dip->di_multiple_files = (dip->di_dir || dip->di_user_dir_limit || dip->di_user_subdir_limit || dip->di_user_subdir_depth || dip->di_file_limit);

	if ( dip->di_dir &&
	     ((dip->di_input_file && strrchr(dip->di_input_file, DIRSEP)) ||
	      (dip->di_output_file && strrchr(dip->di_output_file, DIRSEP))) ) {
	    LogMsg (efp, logLevelCrit, 0,
		    "Please do not specify an if/of= path with dir= option!\n");
	    finish_exiting(dip, FATAL_ERROR);
	}

	/*
	 * If we're doing multiple files, set the dirpath from the file path.
	 */
	if ( !dip->di_dir && dip->di_multiple_files ) {
	    char *p;
	    if (dip->di_input_file && (p = strrchr(dip->di_input_file, DIRSEP)) ) {
		*p = '\0';
		dip->di_dir = dip->di_input_file;
		dip->di_input_file = ++p;
		if (dip->di_debug_flag || dip->di_fDebugFlag) {
		    Printf("Directory Path: %s, Input File: %s\n",
			   dip->di_dir, dip->di_input_file);
		}
	    }
	    if (dip->di_output_file && (p = strrchr(dip->di_output_file, DIRSEP)) ) {
		*p = '\0';
		dip->di_dir = dip->di_output_file;
		dip->di_output_file = ++p;
		if (dip->di_debug_flag || dip->di_fDebugFlag) {
		    Printf("Directory Path: %s, Output File: %s\n",
			   dip->di_dir, dip->di_output_file);
		}
	    }
	}
	if (dip->di_dir) {
	    setup_toplevel_directory(dip, dip->di_dir);
	}

	/*
	 * With multiple files, we'll create a top level directory "d0",
	 * by default, to place files. This allows multiple procs with
	 * just a mount point to work properly (help out automation).
	 */
	if (dip->di_multiple_dirs) {
	    char topdir[PATH_BUFFER_SIZE];
	    if (dip->di_dir) {
		/* Handle case where we already have a directory separator. */
		/* Note: User may have specified or we added it for Windows! */
		if (dip->di_dir[strlen(dip->di_dir)-1] == DIRSEP) {
		    (void)sprintf(topdir, "%s%s0", dip->di_dir, dip->di_dirprefix);
		} else {
		    (void)sprintf(topdir, "%s%c%s0", dip->di_dir, DIRSEP, dip->di_dirprefix);
		}
	    } else {
		(void)sprintf(topdir, "%s0", dip->di_dirprefix);
	    }
	    dip->di_dir = strdup(topdir);
	}

	/*
	 * Disallow both seek type options, to simplify test loops.
	 */
	if ( (dip->di_io_dir == REVERSE) && (dip->di_io_type == RANDOM_IO) ) {
	    LogMsg (efp, logLevelCrit, 0,
		    "Please specify one of iodir=reverse or iotype=random, not both!\n");
	    finish_exiting(dip, FATAL_ERROR);
	}

	if (dip->di_slice_num) {
	    if (!dip->di_num_slices) {
		LogMsg (efp, logLevelCrit, 0,
			"Please specify number of slices with slice option!\n");
		finish_exiting(dip, FATAL_ERROR);
	    } else if (dip->di_slice_num > dip->di_num_slices) {
		LogMsg (efp, logLevelCrit, 0,
			"Please specify slice (%d) <= max slices (%d)\n",
						dip->di_slice_num, dip->di_num_slices);
		finish_exiting(dip, FATAL_ERROR);
	    }
	}

	if ( (!dip->di_input_file || !dip->di_output_file) &&
	      ((dip->di_io_mode == COPY_MODE) || (dip->di_io_mode == VERIFY_MODE)) ) {
	    LogMsg (efp, logLevelCrit, 0,
		    "Copy/verify modes require both input and output devices.\n");
	    finish_exiting(dip, FATAL_ERROR);
	}

	/*
	 * When reading multiple tape files, don't require data or record
	 * limits (these will vary).  But when writing multiple tape files,
	 * we need to know how many records or bytes to be written.
	 */
	if (dip->di_input_file && !dip->di_output_file && dip->di_file_limit && !dip->di_record_limit) {
	    dip->di_record_limit = INFINITY;
	}

	/*
	 * Check the variable record size parameters.
	 */
	if (dip->di_min_size && !dip->di_max_size) dip->di_max_size = dip->di_block_size;
	if (dip->di_block_size < dip->di_max_size) dip->di_block_size = dip->di_max_size;
	/* NOTE: Other checks are done below now... */

	/*
	 * Calculate the data limit if it wasn't specified by the user.
	 */
	if ( (dip->di_data_limit == INFINITY) &&
	     ( (dip->di_record_limit != 0L) && (dip->di_record_limit != INFINITY) ) ) {
	    dip->di_data_limit = (dip->di_block_size * dip->di_record_limit);
	}

	/*
	 * Process the pattern file (if one was specified).
	 */
	if (dip->di_pattern_file) {
#if defined(WIN32)
	    process_pfile (dip, dip->di_pattern_file, GENERIC_READ);
#else /* !defined(WIN32) */
	    process_pfile (dip, dip->di_pattern_file, O_RDONLY);
#endif /* defined(WIN32) */
	}

	if (dip->di_min_size && (dip->di_max_size <= dip->di_min_size)) {
	    LogMsg (efp, logLevelCrit, 0,
		    "Please specify max count > min count for record sizes.\n");
	    finish_exiting(dip, FATAL_ERROR);
	}

	/*
	 * If the pattern is unique, disable prefilling of buffer.
	 */
	if (dip->di_iot_pattern || dip->di_lbdata_flag) {
	    dip->di_prefill_flag = FALSE;
	}
	/*
	 * Verify counts are large enough, to avoid false compare errors.
	 */
	if ( (dip->di_iot_pattern || dip->di_lbdata_flag || dip->di_timestamp_flag) && (dip->di_block_size < dip->di_lbdata_size) ) {
	    LogMsg (efp, logLevelCrit, 0,
	"Please specify a block size >= %u (lbdata size) for iot, lbdata, or timestamp options!\n",
								dip->di_lbdata_size);
	    finish_exiting(dip, FATAL_ERROR);
	}

	if ( ((dip->di_io_mode == COPY_MODE) || (dip->di_io_mode == VERIFY_MODE)) &&
	     (dip->di_iot_pattern || dip->di_lbdata_flag || dip->di_prefix_string || dip->di_timestamp_flag) ) {
	    LogMsg (efp, logLevelCrit, 0,
		    "IOT, Lbdata, prefix, & timestamp options disallowed with Copy/Verify options!\n");
	    finish_exiting(dip, FATAL_ERROR);
	}

        /*
         * Do special handling of IOT data pattern.
         */
	if (dip->di_iot_pattern) {
	    size_t size = dip->di_block_size;
	    u_char *buffer = malloc_palign(size, 0);
	    setup_pattern(dip, buffer, size);
	    dip->di_pattern_string = "IOT Pattern";
	    /*
	     * When variable I/O sizes are requested, align sizes to device size
	     * instead of pattern buffer size else max transfer size is used!
	     */
	    dip->di_fsalign_flag = TRUE;
	    /* IOT takes precedence! */
	    dip->di_lbdata_flag = FALSE;
	    dip->di_user_lbdata = FALSE;
	}

	/*
	 * Setup the pattern as a pattern string, so non-modulo
	 * sizeof(u_int) read counts will compare data properly.
	 */
	if (!dip->di_pattern_buffer) {
	    size_t size = sizeof(u_int32);
	    u_char *buffer = (u_char *)Malloc(size);
	    copy_pattern (dip->di_pattern, buffer);
	    setup_pattern(dip, buffer, size);
	}

	/*
	 * We don't test loopback devices anymore, so automatically setup copy mode!
	 */
	if ( (dip->di_input_file && dip->di_output_file) &&
	     (dip->di_io_mode == TEST_MODE) ) {
	    dip->di_io_mode = COPY_MODE;
	    dip->di_dispose_mode = KEEP_FILE;
	}

	/*
	 * Setup the initial device information & validate options.
	 * 
	 * Note: The original dip is used for parsing. It gets copied to
	 * the input and/or output dinfo then updated accordingly. This
	 * will be expanded for multiple threads (eventually).
	 */
	if (dip->di_input_file) {
	    input_dinfo = (struct dinfo *)Malloc(sizeof(*dip));
	    *input_dinfo = *dip;
	}
	if (dip->di_output_file) {
	    output_dinfo = (struct dinfo *)Malloc(sizeof(*dip));
	    *output_dinfo = *dip;
	    if (input_dinfo) {
		input_dinfo->di_output_dinfo = output_dinfo;
	    }
	    /* HACK, until multiple device support is cleaned up! */
	    if ( (dip->di_io_mode == COPY_MODE) || (dip->di_io_mode == VERIFY_MODE) ) {
		if (!dip->di_record_limit) {
		    output_dinfo->di_record_limit = input_dinfo->di_record_limit;
		}
		output_dinfo->di_aio_flag = FALSE; /* Writes are synchronize (right now). */
		output_dinfo->di_aio_bufs = 0;
	    }
	}

	/************************************************************************/
	/* NOTE: Don't use original dip from this point onward! (until rewrite) */
	/************************************************************************/

	if (input_dinfo) {
	    active_dinfo = dip = input_dinfo;
	    dip->di_output_file = NULL;
	    (void)setup_device_info(dip, dip->di_input_file, dip->di_input_dtype);
	    dip->di_mode = READ_MODE;
	    dip->di_ftype = INPUT_FILE;
	    dip->di_fsync_flag = FALSE;
	    status = (*dip->di_funcs->tf_validate_opts)(dip);
	    if (status == FAILURE) finish_exiting(dip, FATAL_ERROR);
	}
	if (output_dinfo) {
	    active_dinfo = dip = output_dinfo;
	    dip->di_input_file = NULL;
	    (void)setup_device_info(dip, dip->di_output_file, dip->di_output_dtype);
	    dip->di_mode = WRITE_MODE;
	    dip->di_ftype = OUTPUT_FILE;
	    status = (*dip->di_funcs->tf_validate_opts)(dip);
	    if (status == FAILURE) finish_exiting(dip, FATAL_ERROR);
	}

	if (input_dinfo && output_dinfo) dip = input_dinfo;	/* HACK */

#if 1 /* #if def'ed out for debug only!!! */

        /*
         * When doing random I/O, enable file system alignments, to help
         * prevent false corruptions.  This only affects regular files,
         * and only when read-after-write (raw) is disabled.  When raw
         * is enabled, we don't have to worry about data overwrites,
         * unless POSIX Async I/O (AIO) is enabled.
         */
        active_dinfo = dip = (input_dinfo) ? input_dinfo : output_dinfo;
	/*
	 * Note: The device type may not get setup until device is open'ed below!
	 */
        if ( dip->di_dtype &&
	     ((dip->di_dtype->dt_dtype == DT_DISK)  ||
	      (dip->di_dtype->dt_dtype == DT_BLOCK) ||
	      (dip->di_dtype->dt_dtype == DT_CHARACTER)) ) {
	    /* 
	     * IOT pattern changes with each pass, so disable this unqiueness
	     * if user selects multiple procs with multiple passes, otherwise
	     * false data corruptions may occur when procs on differnet passes.
	     */
	    if (dip->di_iot_pattern && dip->di_num_procs && dip->di_unique_pattern &&
		(dip->di_runtime || (dip->di_pass_limit > 1)) ) {
		Printf("Warning: Disabling unique IOT patterns with multiple procs!\n");
		Printf("Please consider using slices= option instead of procs= option.\n");
		dip->di_unique_pattern = FALSE;
	    }
	}
	/*
	 * Special file system handling. 
	 */
        if ( (dip->di_dtype && (dip->di_dtype->dt_dtype == DT_REGULAR)) &&
	     (dip->di_io_type == RANDOM_IO) && !dip->di_bypass_flag &&
	     (!dip->di_raw_flag || (dip->di_raw_flag && dip->di_reread_flag) || dip->di_aio_flag) ) {
            if (dip->di_debug_flag || dip->di_Debug_flag) {
                LogMsg(efp, logLevelWarn, 0,
                       "Enabling FS alignment for sizes and random offsets!\n");
            }
            dip->di_fsalign_flag = TRUE;    /* Align FS sizes & random offsets. */
            /*
             * Sanity check the pattern size is modulo the device size,
             * otherwise this too will cause false failures w/random I/O.
             */
            if (dip->di_patbuf_size && dip->di_dsize) {
                if ( ((dip->di_patbuf_size > dip->di_dsize) && (dip->di_patbuf_size % dip->di_dsize)) ||
                     ((dip->di_patbuf_size < dip->di_dsize) && (dip->di_dsize % dip->di_patbuf_size)) ) {
                    LogMsg(efp, logLevelCrit, 0,
                           "Please specify a pattern size (%u) modulo the device size (%u)!\n",
                            dip->di_patbuf_size, dip->di_dsize);
		    finish_exiting(dip, FATAL_ERROR);
                }
            }
        }
#endif /* #if def'ed out for debug only!!! */

	catch_signals();

    /*
     * Do multiple slices processing.
     */
    if (dip->di_num_slices) {
	if (input_dinfo && output_dinfo) {
	    LogMsg (efp, logLevelCrit, 0,
		    "Please specify only an input or output file, not both!\n");
	    finish_exiting(dip, FATAL_ERROR);
	}

	/*
	 * Create multiple slices (if requested).
	 */
	active_dinfo = dip = (input_dinfo) ? input_dinfo : output_dinfo;
	if (!dip->di_random_access) {
	    LogMsg (efp, logLevelCrit, 0,
		    "Multiple slices is only supported on random access devices!\n");
	    finish_exiting(dip, FATAL_ERROR);
	}
	if ((status = FindCapacity (dip)) == FAILURE) {
	    finish_exiting(dip, FATAL_ERROR);
	}
	/*
	 * The remaining work is done when starting the processes.
	 */
	if (dip->di_slice_num) {
	    init_slice(active_dinfo, dip->di_slice_num);
	    dip->di_cur_proc = dip->di_slice_num;
	    //dip->di_num_slices = 0; /* Operate on a single slice. */
	} else {
	    if ( start_slices(dip) ) {
		if (dip->di_iotune_file) {
		    (void)start_iotuning(dip);
		}
		await_procs(dip);
		if (dip->di_debug_flag || dip->di_pDebugFlag) {
		    Printf ("Parent exiting with status %d...\n", exit_status);
		}
		exit (exit_status);
	    }
	}
    } /* End of multiple slices processing. */

    /* Until we find the Windows equivalent! */
#if !defined(WIN32)
    if (nice_value) {
	errno = 0;
	if ( (nice(nice_value) == -1) && (errno != 0) ) {
	    Perror("nice() failed");
	    exit (FAILURE);
	}
    }
#endif /* !defined(WIN32) */

	/*
	 * Create multiple processes (if requested).
	 */
	if (dip->di_num_procs) {
	    if ( start_procs(dip) ) {
		if (dip->di_iotune_file) {
		    (void)start_iotuning(dip);
		}
		await_procs(dip);		/* Parent waits. */
		if (dip->di_debug_flag || dip->di_pDebugFlag) {
		    Printf ("Parent exiting with status %d...\n", exit_status);
		}
		exit (exit_status);
	    }
	}

	if ( dip->di_mount_lookup && (dip->di_dtype->dt_dtype == DT_REGULAR) ) {
	    if (dip->di_dir) {
		(void)FindMountDevice(dip, dip->di_dir, dip->di_mntDebugFlag);
	    } else {
		char *device = (dip->di_input_file) ? dip->di_input_file : dip->di_output_file;
		(void)FindMountDevice(dip, device, dip->di_mntDebugFlag);
	    }
	    if (dip->di_debug_flag && dip->di_mounted_from_device) {
		Printf ("Mounted from device: %s\n", dip->di_mounted_from_device);
	    }
	    /* Note: For Copy/Verify, may wish to do both device? */
	}
#if defined(SCSI)
	    if (dip->di_scsi_flag && dip->di_mounted_from_device) {
		/* Note: May need to massage DSF's for some OS's! */
		if (strncmp(dip->di_mounted_from_device, DEV_DIR_PREFIX, DEV_DIR_LEN) == 0) {
		    if (!dip->di_scsi_dsf) {
#if defined(DEV_BDIR_LEN)
			dip->di_scsi_dsf = ConvertBlockToRawDevice(dip->di_mounted_from_device);
#else /* !defined(DEV_BDIR_LEN) */
			dip->di_scsi_dsf = strdup(dip->di_mounted_from_device);
#endif /* defined(DEV_BDIR_LEN) */
		    }
		}
	    }
#endif /* defined(SCSI) */

	/*
	 * Open device / Setup system / device specific test information.
	 */
	if (input_dinfo) {
	    int open_mode = (dip->di_ropen_mode | dip->di_open_flags);
	    dip = active_dinfo = input_dinfo;
	    if ( dip->di_dir &&
		 ((dip->di_dtype->dt_dtype == DT_MMAP) ||
		  (dip->di_dtype->dt_dtype == DT_REGULAR)) ) {
		int status = setup_directory_info(dip, dip->di_dir);
		if (status == FAILURE) terminate(status); /* For now! */
	    }
	    SetupBufferingMode(dip, &open_mode);
	    if ((*dip->di_funcs->tf_open)(dip, open_mode) == FAILURE) {
		exit (exit_status);
	    }
	    system_device_info (dip);
	    dip->di_input_dtype = dip->di_dtype;

	    status = (*dip->di_funcs->tf_validate_opts)(dip);
	    if (status == FAILURE) finish_exiting(dip, FATAL_ERROR);

	    /*
	     * The new logic for the IOT pattern is to make it unique during
	     * multiple passes. However, during reads it must remain constant.
	     */
	    if (dip->di_iot_pattern) {
		dip->di_unique_pattern = FALSE;	/* Re-reads during all pass use same seed! */
	    }

	    /*
	     * If disk device and random I/O selected, attempt to get
	     * device / partition capacity to limit random I/O seeks.
	     */
	    if ( !dip->di_num_slices &&
		 (dip->di_user_capacity ||
		  (dip->di_random_io && dip->di_random_access)) ) {
		if ((status = FindCapacity (dip)) == FAILURE) {
		    exit (exit_status);
		}
	    }
	    if (!dip->di_record_limit) {
		dip->di_record_limit = INFINITY;	/* Read until EOF on reads. */
	    }
#if defined(SCSI)
	    if (dip->di_scsi_flag &&
		((dip->di_dtype->dt_dtype == DT_DISK) || dip->di_scsi_dsf) ) {
		(void)init_scsi_info(dip);
	    }
#endif /* defined(SCSI) */
	} /* end if (dip->di_input_file) */

	/*
	 * Process the output device/file.
	 */
	if (output_dinfo) {
	    int open_mode;
	    dip = active_dinfo = output_dinfo;
	    if (dip->di_unique_file && (dip->di_dtype->dt_dtype == DT_REGULAR)) {
		/* Note: Must be dynamic for multiple dirs/files. */
		dip->di_dname = make_unique_file(dip, dip->di_output_file);
		dip->di_bname = strdup(dip->di_dname);
		dip->di_output_file = strdup(dip->di_dname); /* Cleanup usage! */
		/* NOTE: Some flags may be wrong if file existed! */
	    }
	    if ( dip->di_dir &&
		 ((dip->di_dtype->dt_dtype == DT_MMAP) ||
		  (dip->di_dtype->dt_dtype == DT_REGULAR)) ) {
		int status = setup_directory_info(dip, dip->di_dir);
		if (status == FAILURE) terminate(status); /* For now! */
	    }
	    /*
	     * If a skip count was specified, open output file for R/W,
	     * since skips are accomplished via read()'s. (for pelle)
	     */
	    if (dip->di_skip_count || dip->di_raw_flag) {
#if defined(WIN32)
		open_mode = dip->di_rwopen_mode;
#else /* !defined(WIN32) */
		open_mode = (dip->di_rwopen_mode | dip->di_wopen_flags | dip->di_open_flags);
#endif /* defined(WIN32) */
	    } else {
		open_mode = (dip->di_wopen_mode | dip->di_wopen_flags | dip->di_open_flags);
	    }
	    /*
	     * Don't create files in the /dev directory (presume the file
	     * should exist instead of creating file & misleading user).
	     */
	    if ( (NEL (dip->di_output_file, DEV_PREFIX, DEV_LEN)) &&
		 (NEL (dip->di_output_file, ADEV_PREFIX, ADEV_LEN)) ) {
		open_mode |= O_CREAT;	/* For creating test files.	*/
	    }
	    /*
	     * If verify mode, the output device is open for reads.
	     */
	    if (dip->di_io_mode == VERIFY_MODE) {
		open_mode = (dip->di_ropen_mode | dip->di_open_flags);
		dip->di_mode = READ_MODE;
	    }
	    SetupBufferingMode(dip, &open_mode);
	    if ((*dip->di_funcs->tf_open)(dip, open_mode) == FAILURE) {
		exit (exit_status);
	    }

	    system_device_info (dip);
	    dip->di_output_dtype = dip->di_dtype;
	    dip->di_open_flags &= ~O_CREAT;	/* Only create on first open. */
	    status = (*dip->di_funcs->tf_validate_opts)(dip);
	    if (status == FAILURE) finish_exiting(dip, FATAL_ERROR);

	    /*
	     * If disk device and random I/O selected, attempt to get
	     * device / partition capacity to limit random I/O seeks.
	     */
	    if ( !dip->di_num_slices &&
		 (dip->di_user_capacity ||
		  (dip->di_random_io && dip->di_random_access)) ) {
		if ((status = FindCapacity (dip)) == FAILURE) {
		    finish_exiting(dip, exit_status);
		}
	    }

	    /*
	     * For disks and tapes, default writing until EOF is reached.
	     */
	    if ( !dip->di_record_limit &&
		 ((dip->di_dtype->dt_dtype == DT_DISK)  ||
		  (dip->di_dtype->dt_dtype == DT_BLOCK) ||
		  (dip->di_dtype->dt_dtype == DT_TAPE)) ) {
		dip->di_record_limit = INFINITY;
	    }
#if defined(SCSI)
	    if (dip->di_scsi_flag &&
		((dip->di_dtype->dt_dtype == DT_DISK) || dip->di_scsi_dsf) ) {
		(void)init_scsi_info(dip);
	    }
#endif /* defined(SCSI) */
	} /* end if (dip->di_output_file) */

	if (input_dinfo && output_dinfo) dip = input_dinfo;	/* HACK */

	/*
	 * Set the default lbdata size, if not setup by the system
	 * dependent functions above.  Delaying this check to this
	 * point allows the device sector size to be setup, instead
	 * of forcing it to 512 byte blocks.  At least this is true
	 * on Tru64 Unix, where this disk information is available.
	 */
	if (!dip->di_lbdata_size) dip->di_lbdata_size = BLOCK_SIZE;
	if ( (dip->di_rdata_limit || dip->di_random_align) &&
	     ((dip->di_io_dir != REVERSE) && (dip->di_io_type != RANDOM_IO)) ) {
	    Printf ("Warning, random options have no effect without iotype=random!\n");
	}

	/*
	 * If random I/O was selected, and a data limit isn't available,
	 * inform the user we need one, and don't allow testing.
	 */
	if (dip->di_rdata_limit == 0UL) dip->di_rdata_limit = dip->di_data_limit;
	if ( (dip->di_rdata_limit == 0) && (dip->di_io_type == RANDOM_IO) ) {
	    LogMsg (efp, logLevelCrit, 0,
		    "Please specify a record or data limit for random I/O.\n");
	    finish_exiting(dip, FATAL_ERROR);
	}

	/*
	 * Sanity check the random I/O data limits.
	 */
	if ( (dip->di_io_type == RANDOM_IO) &&
	     ((large_t)(dip->di_file_position + dip->di_block_size + dip->di_random_align) > dip->di_rdata_limit)) {
	    LogMsg (efp, logLevelCrit, 0,
		    "The max block size is too large for random data limits!\n");
	    if (dip->di_Debug_flag) {
	        Printf ("file position " FUF ", bs=%ld, ralign=%ld, rlimit=" LUF "\n",
			dip->di_file_position, dip->di_block_size, dip->di_random_align, dip->di_rdata_limit);
	    }
	    finish_exiting(dip, FATAL_ERROR);
	}

	/*
	 * Special handling for step option:
	 *
	 * For regular files, we must setup an end position (offset), since
	 * doing I/O to a file system will NOT encounter an EOF like raw disks.
	 * Slices also requires an ending position when step option is used.
	 */
	if (dip->di_step_offset &&
	    ((dip->di_dtype->dt_dtype == DT_REGULAR) || dip->di_num_slices) ) {
	    if (dip->di_data_limit && (dip->di_data_limit != INFINITY)) {
		dip->di_end_position = (dip->di_file_position + dip->di_data_limit);
	    } else {
		dip->di_end_position = (dip->di_file_position + (dip->di_record_limit * dip->di_block_size));
	    }
	}
	/*
	 * Ensure either a data limit and/or a record count was specified.
	 */
	if (!dip->di_record_limit) {
	    LogMsg (efp, logLevelCrit, 0,
		    "You must specify a data limit, a record count, or both.\n");
	    finish_exiting(dip, FATAL_ERROR);
	}
	
	/*
	 * Reset the data limit, if specified by the user and we overwrote it earlier.
	 * The data limit gets set to the max data limit in ReadCapacity (needs cleanup!).
	 * Note: This is a workaround for random I/O or slices so user limit is not ignored!
	 */
	if (dip->di_user_limit && (dip->di_user_limit < dip->di_data_limit)) {
	    dip->di_data_limit = dip->di_user_limit;
	}

	/*
	 * Some drivers require the input device to open before we start
	 * writing. For example, terminal devices must have speed, parity,
	 * and flow control setup before we start writing.  The parallel
	 * input device must open before we send the "readya" interrupt.
	 */
	if (output_dinfo && (dip->di_start_delay != 0)) {
	    mySleep(dip, dip->di_start_delay);	/* Allow reader to start. */
	}

	/*
	 * Calculate size necessary for the data buffer & the pad bytes.
	 */
	dip->di_data_size = (dip->di_block_size + PADBUFR_SIZE);
	if (dip->di_rotate_flag) dip->di_data_size += ROTATE_SIZE;

	/* HACK, until multiple device support is cleaned up! */
	if (input_dinfo && output_dinfo) {
	    if (dip != input_dinfo) abort();
	    output_dinfo->di_data_size = dip->di_data_size;
	}

	/*
	 * For read-after-write (raw) option, we need a verification buffer.
	 * Note:  Other tests can benefit from this too, switch to later.
	 */
	if (dip->di_raw_flag) {
	    dip->di_verify_buffer = malloc_palign(dip->di_data_size, dip->di_align_offset);
	}

	/*
	 * Do the device / test specific initialization.
	 *
	 * This function is responsible for allocating the necessary
	 * data buffers and performing special device setup/checking.
	 */
	if (input_dinfo) {
	    dip = input_dinfo;
	    status = (*dip->di_funcs->tf_initialize)(dip);
	    if (status == FAILURE) finish_exiting(dip, FATAL_ERROR);
	}
	if (output_dinfo) {
	    dip = output_dinfo;
	    status = (*dip->di_funcs->tf_initialize)(dip);
	    if (status == FAILURE) finish_exiting(dip, FATAL_ERROR);
	}

	if (input_dinfo && output_dinfo) dip = input_dinfo;	/* HACK */

	/*
	 * Re-adjust size of data buffer to avoid init'ing too much.
	 *
	 * Note: This is Mickey Mouse, clean this crap up! (not clean)
	 */
	if (dip->di_rotate_flag) dip->di_data_size -= ROTATE_SIZE;
	/* HACK! */
	if (input_dinfo && output_dinfo) {
	    if (dip != input_dinfo) abort();
	    output_dinfo->di_data_size = dip->di_data_size;
	}

	/*
	 * Finally format the prefix string (if any), after the device is
	 * setup and processes are forked so we can setup a unique prefix.
	 */
	if (dip->di_prefix_string) {
	    status = FmtPrefix(dip, dip->di_prefix_string, dip->di_prefix_size);
	    if (status == FAILURE) finish_exiting(dip, FATAL_ERROR);
            if ((size_t)dip->di_fprefix_size > dip->di_lbdata_size) {
                LogMsg (efp, logLevelCrit, 0,
                        "The prefix size (%d) is larger than lbdata size (%d)!\n",
                        dip->di_fprefix_size, dip->di_lbdata_size);
                finish_exiting(dip, FATAL_ERROR);
            }
	}

	/*
	 * Start an alarm timer if the run time was specified.
	 */
	if (dip->di_alarmtime || dip->di_runtime) {
            if (dip->di_runtime) {
                dip->di_runtime_end = time((time_t *)NULL) + dip->di_runtime;
            }
	    /*
	     * Adjust the alarm time, if it's greater than other times.
	     */
	    if (dip->di_alarmtime) {
		if (dip->di_noprogtime) dip->di_alarmtime = MIN(dip->di_alarmtime,dip->di_noprogtime);
		if (dip->di_keepalive_time) dip->di_alarmtime = MIN(dip->di_alarmtime,dip->di_keepalive_time);
		if (dip->di_runtime) dip->di_alarmtime = MIN(dip->di_alarmtime,dip->di_runtime);
	    }

	    /*
	     * With monitor no I/O progress, user must specify a keepalive
	     * string, otherwise we won't log anything (just monitor).
	     */
	    if (dip->di_noprog_flag && !dip->di_noprogtime) { dip->di_noprogtime = dip->di_alarmtime; }
	    if (dip->di_noprog_flag && !dip->di_user_keepalive && !dip->di_keepalive_time) {
		dip->di_keepalive = "";
		dip->di_user_keepalive = TRUE;
	    }
	    /*
	     * Only enable alarm for child processes.
	     */
            if (dip->di_alarmtime && (dip->di_child_pid == (pid_t)0) ) {
		if ( !dip->di_keepalive ) {
		    if ( !dip->di_keepalive || (!dip->di_user_keepalive && !strlen(dip->di_keepalive)) ) {
			if (dip->di_pstats_flag) {
			    dip->di_keepalive = keepalive0;
			} else {
			    dip->di_keepalive = keepalive1;
			}
		    }
                }
                (void) StartMonitorThread(dip, dip->di_alarmtime);
		dip->di_TimerActive = TRUE;
            } else {
		/*
    		 * Even without monitoring, use a thread to avoid those
		 * nasty signals from being blocked, thus hanging dt!
		 */
                (void) StartMonitorThread(dip, dip->di_runtime);
		dip->di_TimerActive = TRUE;
            }
	} /* end if (dip->di_alarmtime || dip->di_runtime) */

        /*
         * When stats=brief, we allow a one line format for pass and totals.
         * If the user has not specified their own format, set our defaults.
         * Note:  They aren't really keepalive, just use the same logic. :-)
         */
        if ( !dip->di_pkeepalive || !strlen(dip->di_pkeepalive) ) {
            dip->di_pkeepalive = pass_msg;
        }
        if ( !dip->di_tkeepalive || !strlen(dip->di_tkeepalive) ) {
            dip->di_tkeepalive = totals_msg;
        }

	/*
	 * Start of main test loop.
	 */
#if defined(SYSLOG)
	if (dip->di_syslog_flag) {
	    syslog(LOG_INFO, "(%d) Starting: %s", dip->di_process_id, dip->di_cmd_line);
	}
#endif /* defined(SYSLOG) */

    /* TODO: Remove need for active_dinfo! */
	
    if ( (dip->di_io_mode == COPY_MODE) || (dip->di_io_mode == VERIFY_MODE) ) {
	dip = active_dinfo = input_dinfo;
    } else { /* not Copy or Verify modes, Test Mode! */
	if (dip->di_output_file) {	/* Write/read the file.	*/
	    dip = active_dinfo = output_dinfo;
	} else { /* Reading only. */
	    dip = active_dinfo = input_dinfo;
	}
    }

    (void)start_iotuning(dip);

    /*
     * Create test threads.
     *
     * TODO: Clean this up!
     */
  { void *thread_status = NULL;

    status = pthread_attr_setdetachstate(tattrp, PTHREAD_CREATE_JOINABLE);
    if (status != SUCCESS) {
	tPerror(status, "pthread_attr_setdetachstate() failed setting PTHREAD_CREATE_JOINABLE");
    }
    if ( (dip->di_io_mode == COPY_MODE) || (dip->di_io_mode == VERIFY_MODE) ) {
	status = pthread_create( &IO_Thread, tattrp, docopy, dip );
    } else {
	status = pthread_create( &IO_Thread, tattrp, doio, dip );
    }
    if (status != SUCCESS) {
	tPerror (status, "pthread_create() failed");
	return (status);
    }
    if (dip->di_debug_flag || dip->di_tDebugFlag) {
	Printf("Waiting for IO thread to complete...\n");
    }
    status = pthread_join( IO_Thread, &thread_status );
    IO_Thread = (pthread_t) 0;
    if (thread_status == NULL) {
	status = FAILURE;   /* Assumed canceled, etc. */
    } else {
	if (dip != (dinfo_t *)thread_status) {
	    Fprintf("Sanity check of thread status failed for device %s!\n", dip->di_dname);
	    Fprintf("Expected dip = %p, Received: %p\n", dip, thread_status);
	    abort(); /* sanity */
	}
    }
    if (dip->di_exit_status == FAILURE) {
	exit_status = dip->di_exit_status;
    }

  }
  if (dip->di_debug_flag || dip->di_tDebugFlag) {
      Printf("I/O thread(s) have completed, terminating...\n");
  }
    /* TODO: Each thread will call terminate()! */	
    terminate (exit_status);		/* Terminate with exit status.	*/
    /*NOTREACHED*/
    return (exit_status);		/* Quiet certain compilers!	*/
}

/*
 * catch_signals() = Enable Signals we wish to Catch.
 */ 
void
catch_signals(void)
{
    /*
     * Catch a couple signals to do elegant cleanup.
     */
    (void) signal (SIGTERM, SignalHandler);
    (void) signal (SIGINT, SignalHandler);
#if !defined(WIN32)
    (void) signal (SIGHUP, (sighup_flag) ? SignalHandler : SIG_IGN);
    /*
     * Windows Note: SIGINT is not supported for any Win32 application,
     * including Windows 98/Me and Windows NT/2000/XP. When a CTRL+C
     * interrupt occurs, Win32 operating systems generate a new thread
     * to specifically handle that interrupt.  This can cause a
     * single-thread application such as UNIX, to become multithreaded,
     * resulting in unexpected behavior. (and indeed it does!)
     *
     * Note: Multiple threads are now handled by terminate().
     */
    (void) signal (SIGPIPE, SignalHandler);
#endif /* !defined(WIN32) */
#if (!defined(__MSDOS__) && !defined(WIN32)) || defined(__NUTC__)
    (void) signal (SIGCHLD, SIG_DFL);
#endif
    return;
}

/*
 * ignore_signals() = Ignore Signals in Threads.
 *
 * Description:
 *  We don't want threads handling signals, just the mainline.
 */
void
ignore_signals(void)
{
#if !defined(WIN32)
    sigset_t sigs;

    /*
     * int pthread_sigmask(int how, const sigset_t  *set,  sigset_t *oset);
     */
    sigemptyset(&sigs);
    sigaddset(&sigs, SIGINT);
    sigaddset(&sigs, SIGTERM);
    sigaddset(&sigs, SIGHUP);
    sigaddset(&sigs, SIGCHLD);
    if (pthread_sigmask(SIG_BLOCK, &sigs, NULL) == FAILURE) {
        Perror("pthread_sigmask() failed\n");
    }
#endif /* !defined(WIN32) */
    return;
}

/*************************/
/* Start of Test Threads */
/*************************/

void *
docopy(void *arg)
{
    int status = SUCCESS;
    dinfo_t *dip = arg;
    dinfo_t *odip = dip->di_output_dinfo;
    struct dtfuncs *dtf = dip->di_funcs;

    ignore_signals();
#if defined(WIN32)
    IO_ThreadId = pthread_self();
#endif
    if (dip->di_debug_flag || dip->di_tDebugFlag) {
	Printf("Copy/Verify Thread ID is %u\n", IO_ThreadId);
    }

    if (dip != input_dinfo) abort();	/* Assert! */

    dip->di_start_time = times (&dip->di_stimes);
    odip->di_start_time = dip->di_start_time;	/* HACK! */

    /*
     * Note: Currently, the pattern buffer is ued as the verify buffer.
     */
    if ( (dip->di_io_mode == VERIFY_MODE) || dip->di_verify_flag) {
	dip->di_pattern_buffer = malloc_palign(dip->di_data_size, dip->di_align_offset);
	setup_pattern(dip, dip->di_pattern_buffer, dip->di_data_size);
	/* HACK! Setup output device to use the same buffer! */
	setup_pattern(odip, dip->di_pattern_buffer, dip->di_data_size);
    }

    while ( !dip->di_terminating			 &&
	    (dip->di_total_errors < dip->di_error_limit) &&
	    ((dip->di_pass_count < dip->di_pass_limit) || dip->di_runtime) ) {

	/*
	 * Copy or Verify the input and output devices.
	 */
	dip->di_pass_time = times (&dip->di_ptimes);	/* Start the pass timer	*/
	odip->di_pass_time = dip->di_pass_time;		/* HACK! */

	//dip->di_mode = READ_MODE;
	(void) (*dtf->tf_start_test)(dip);
	(void) (*dtf->tf_read_file)(dip);
	(void) (*dtf->tf_end_test)(dip);
	gather_stats(odip);
	accumulate_stats(dip);

	/*
	 * Now verify the data copied, if copying (if requested).
	 */
	if ( (dip->di_io_mode == COPY_MODE) && dip->di_verify_flag &&
	     !dip->di_stdin_flag && (dip->di_error_count < dip->di_error_limit) ) {

	    int open_mode = (dip->di_ropen_mode | dip->di_open_flags);
	    report_pass (dip, COPY_STATS);	/* Report copy statistics. */
	    /*
	     * Verify Pass.
	     */
	    status = (*dtf->tf_reopen_file)(dip, open_mode);
	    if (status != SUCCESS) break;

	    /* Reopen the output file to reading. */
	    odip->di_mode = READ_MODE;		/* Switch to read mode. */
	    status = (*odip->di_funcs->tf_reopen_file)(odip, open_mode);
	    if (status != SUCCESS) break;
	    dip->di_pass_time = times (&dip->di_ptimes); /* Time the verify. */
	    dip->di_io_mode = VERIFY_MODE;
	    (void) (*dtf->tf_start_test)(dip);
	    (void) (*dtf->tf_read_file)(dip);
	    (void) (*dtf->tf_end_test)(dip);
	    dip->di_pass_count++;		/* End of copy/verify pass. */
	    gather_stats(odip);			/* Gather device statistics. */
	    accumulate_stats(dip);
	    report_pass (dip, VERIFY_STATS);	/* Report the verify stats. */
	    if ( (dip->di_pass_limit > 1) || dip->di_runtime) {
		if (dip->di_end_delay) {	/* Optional end delay. 	*/
		    mySleep(dip, dip->di_end_delay);
		}
	    }
	} else {
	    dip->di_pass_count++;		/* End of copy pass. */
	    if ( (dip->di_pass_limit > 1) || dip->di_runtime) {
		report_pass (dip, VERIFY_STATS);/* Report verify stats.	*/
		if (dip->di_end_delay) {	/* Optional end delay. 	*/
		    mySleep(dip, dip->di_end_delay);
		}
	    }
	}

	/*
	 * Allow folks to loop on copy/verify operations.
	 */
	if ( !dip->di_terminating			 &&
	    (dip->di_total_errors < dip->di_error_limit) &&
	    ((dip->di_pass_count < dip->di_pass_limit) || dip->di_runtime) ) {

	    int open_mode = (dip->di_ropen_mode | dip->di_open_flags);

	    /* Reopen the input file. */
	    status = (*dtf->tf_reopen_file)(dip, open_mode);
	    if (status != SUCCESS) break;

	    /* Reopen the output file. */
	    if (odip->di_io_mode == COPY_MODE) {
		dip->di_io_mode = COPY_MODE;
		open_mode = (dip->di_wopen_mode | dip->di_wopen_flags | dip->di_open_flags);
		odip->di_mode = WRITE_MODE;		/* Switch back to write mode. */
	    }
	    status = (*odip->di_funcs->tf_reopen_file)(odip, open_mode);
	    if (status != SUCCESS) break;
	}
    }

    //status = finish_test(dip, status, TRUE);
    dip->di_exit_status = status;
    if (dip->di_debug_flag || dip->di_tDebugFlag) {
	Printf("Copy/Verify has completed, thread exiting with status %d...\n", dip->di_exit_status);
    }
    pthread_exit(dip);
    return(NULL);
}

void *  
doio(void *arg)
{           
    int status = SUCCESS;
    dinfo_t *dip = arg;
    struct dtfuncs *dtf;

    ignore_signals();
#if defined(WIN32)
    IO_ThreadId = pthread_self();
#endif
    if (dip->di_debug_flag || dip->di_tDebugFlag) {
	Printf("I/O Thread ID is %u\n", IO_ThreadId);
    }

    dip->di_start_time = times (&dip->di_stimes);

    while ( !dip->di_terminating			 &&
	    (dip->di_total_errors < dip->di_error_limit) &&
	    ((dip->di_pass_count < dip->di_pass_limit) || dip->di_runtime) ) {

	if (dip->di_pattern_buffer) {
	    dip->di_pattern_bufptr = dip->di_pattern_buffer;
	}
	/*
	 * Use a different data pattern for each pass.
	 */
	if ( !dip->di_user_pattern			&&
	     (dip->di_output_file || dip->di_stdin_flag ||
	      (dip->di_input_file && dip->di_num_slices)) ) {
	    /*
	     * Logic:
	     * - If multiple slices, choose a different pattern
	     *   for each pass, factoring in the process number.
	     * - Else, each pass gets a different data pattern
	     *   unless multiple processes were selected.
	     */
	    if ( dip->di_unique_pattern &&
		 ( (!dip->di_num_procs && dip->di_num_slices) ||
		   (dip->di_num_procs && (dip->di_dtype->dt_dtype == DT_REGULAR)) ) ) {
		dip->di_pattern_index = ((dip->di_cur_proc - 1) + dip->di_pass_count);
	    } else if (!dip->di_num_procs) {
		dip->di_pattern_index = dip->di_pass_count;
	    }
	    dip->di_pattern = data_patterns[dip->di_pattern_index % npatterns];
	    if (dip->di_pattern_buffer) copy_pattern (dip->di_pattern, dip->di_pattern_buffer);
	    if (dip->di_debug_flag) {
		Printf ("Using data pattern 0x%08x for pass %u\n",
			dip->di_pattern, (dip->di_pass_count + 1));
	    }
	} else if (dip->di_iot_pattern) {
	    dip->di_iot_seed_per_pass = dip->di_iot_seed;
	    if (dip->di_unique_pattern) {
		/*
		 * For uniqueness, factor the pass count into the seed.
		 */
		dip->di_iot_seed_per_pass *= (dip->di_pass_count + 1);
	    }
	}
	/*
	 * Use time for random # generator seed so different areas
	 * of disk get affected during multiple passes.  Seed set
	 * here, since it must be the same seed during read pass.
	 * NOTE: Pid is added so seed different for each process.
	 */
	if ( (dip->di_io_type == RANDOM_IO) || dip->di_variable_flag) {
	    if ( !dip->di_user_rseed ) {
		dip->di_random_seed = (u_int) times(&dip->di_ptimes) + dip->di_process_id;
	    }
	    set_rseed (dip->di_random_seed);
	}
	dip->di_pass_time = times (&dip->di_ptimes);	/* Start the pass timer	*/
	if (dip->di_output_file) {			/* Write/read the file.	*/
	    bool do_read_pass;
	    //dip = active_dinfo = output_dinfo;
	    dtf = dip->di_funcs;
	    dip->di_mode = WRITE_MODE;
	    (void) (*dtf->tf_start_test)(dip);
	    (void) (*dtf->tf_write_file)(dip);
	    (void) (*dtf->tf_flush_data)(dip);
	    (void) (*dtf->tf_end_test)(dip);
	    if (dip->di_terminating ||
		(dip->di_error_count >= dip->di_error_limit) ) {
		break;
	    }
	    do_read_pass = (dip->di_dbytes_written != (large_t) 0);
	    /*
	     * Now verify (read and compare) the data just written.
	     */
	    if ( dip->di_verify_flag && do_read_pass && 
		 (!dip->di_raw_flag || (dip->di_raw_flag && dip->di_reread_flag)) ) {
		int open_mode = (dip->di_ropen_mode | dip->di_open_flags);
		
		if (dip->di_raw_flag) {
		    report_pass (dip, RAW_STATS);	/* Report read-after-write. */
		} else {
		    report_pass (dip, WRITE_STATS);	/* Report write stats.	*/
		}
		/*
		 * For  multiple files, reset the pattern/IOT seed for read pass!
		 */
		if (dip->di_file_limit) {
		    if (!dip->di_user_pattern) {
			dip->di_pattern = data_patterns[dip->di_pattern_index % npatterns];
			if (dip->di_pattern_buffer) copy_pattern (dip->di_pattern, dip->di_pattern_buffer);
		    } else if (dip->di_iot_pattern) {
			dip->di_iot_seed_per_pass = dip->di_iot_seed;
			if (dip->di_unique_pattern) {
			    dip->di_iot_seed_per_pass *= (dip->di_pass_count + 1);
			}
		    }
		}
		dip->di_mode = READ_MODE;
		if (dip->di_multi_flag && dip->di_media_changed) {
		    status = RequestFirstVolume(dip, dip->di_open_flags);
		} else {
		    status = (*dtf->tf_reopen_file)(dip, open_mode);
		}
		if (status != SUCCESS) break;
		/*
		 * Reset the random seed, so reads mimic what we wrote!
		 */
		if ( (dip->di_io_type == RANDOM_IO) || dip->di_variable_flag) {
		    set_rseed (dip->di_random_seed);
		}
		dip->di_pass_time = times (&dip->di_ptimes);/* Time just the read.	*/
		/*dip->di_rotate_offset = 0;*/
		if (dip->di_pattern_buffer) {
		    dip->di_pattern_bufptr = dip->di_pattern_buffer;
		}
		(void) (*dtf->tf_start_test)(dip);
		(void) (*dtf->tf_read_file)(dip);
		(void) (*dtf->tf_end_test)(dip);
		dip->di_pass_count++;		/* End read/write pass. */
		report_pass (dip, READ_STATS);	/* Report read stats.	*/
		if (dip->di_end_delay) {	/* Optional end delay. 	*/
		    mySleep(dip, dip->di_end_delay);
		}
	    } else {
		dip->di_pass_count++;		/* End of write pass.	*/
		if ( (dip->di_pass_limit > 1) || dip->di_runtime) {
		    /* Report write stats. */
		    if (dip->di_raw_flag) {
			report_pass (dip, RAW_STATS);
		    } else {
			report_pass (dip, WRITE_STATS);
		    }
		    if (dip->di_end_delay) {	/* Optional end delay. 	*/
			mySleep(dip, dip->di_end_delay);
		    }
		}
	    }
	    if (dip->di_terminating ||
		(dip->di_error_count >= dip->di_error_limit) ) {
		break;
	    }
#if defined(SCSI)
	    if ( (dip->di_dtype->dt_dtype == DT_DISK) && dip->di_scsi_flag && 
		 (dip->di_unmap_flag ||
		  ( dip->di_unmap_frequency &&
		    ((dip->di_pass_count % dip->di_unmap_frequency) == 0)) ) ) {
		large_t starting_block = 0, data_limit = 0;
		
		if (dip->di_offset) {
		    /* Note: Not using the device size, since real is 512 byte blocks! */
		    starting_block = (dip->di_file_position / BLOCK_SIZE);
		}
		if (dip->di_random_io) {
		    data_limit = dip->di_rdata_limit;
		} else if (dip->di_data_limit && (dip->di_data_limit != INFINITY)) {
		    data_limit = dip->di_data_limit;
		}
		status = unmap_blocks(dip, starting_block, data_limit);
		if (status != SUCCESS) {
		    /* Note: Revisit this when spt pulled into dt! */
		    /* Expect spt to report the real error! */
		    dip->di_error_count++;
		    exit_status = FAILURE;
		    if (dip->di_error_count >= dip->di_error_limit) {
			break;
		    }
		}
	    }
#endif /* defined(SCSI) */
	    if ( dip->di_delete_per_pass			    		&&
		 (dip->di_total_errors < dip->di_error_limit)           	&&
		 ((dip->di_pass_count < dip->di_pass_limit) || dip->di_runtime) &&
		 ((dip->di_dtype->dt_dtype == DT_MMAP) ||
		  (dip->di_dtype->dt_dtype == DT_REGULAR)) ) {
		if (dip->di_fd != NoFd) {
		    status = (*dip->di_funcs->tf_close)(dip);
		}
		status = delete_files(dip);
		if (status == FAILURE) break;
		if (dip->di_dir) {
		    dip->di_mode = WRITE_MODE;
		    status = setup_directory_info(dip, dip->di_dir);
		    if (status == FAILURE) break;
		}
	    }
	    /*
	     * Don't reopen if we've reached the error limit or the
	     * pass count, since we'll be terminating shortly.
	     */
	    if ( !dip->di_terminating &&
		 (dip->di_total_errors < dip->di_error_limit) &&
		 ((dip->di_pass_count < dip->di_pass_limit) || dip->di_runtime) ) {
		int open_mode;
		SetupBufferingMode(dip, &dip->di_open_flags);
		if (dip->di_skip_count || dip->di_raw_flag) {
#if defined(WIN32)
		    open_mode = dip->di_rwopen_mode;
#else /* !defined(WIN32) */
		    open_mode = (dip->di_rwopen_mode | dip->di_wopen_flags | dip->di_open_flags);
#endif /* defined(WIN32) */
		} else {
		    open_mode = (dip->di_wopen_mode | dip->di_wopen_flags | dip->di_open_flags);
		}
		dip->di_mode = WRITE_MODE;
		if (dip->di_delete_per_pass) {
#if !defined(WIN32)
		    open_mode |= O_CREAT;
#endif
		    dip->di_file_number = 0;
		    dip->di_subdir_number = 0;
		    dip->di_subdir_depth = 0;
		    status = (*dtf->tf_open)(dip, open_mode);
		} else {
		    status = (*dtf->tf_reopen_file)(dip, open_mode);
		}
		if (status != SUCCESS) break;
	    }
	} else { /* Reading only. */
	    //dip = active_dinfo = input_dinfo;
	    dtf = dip->di_funcs;
	    dip->di_mode = READ_MODE;
	    /*
	     * Note: User must set random seed to repeat previous write sequence!
	     */
	    if (dip->di_user_rseed && ((dip->di_io_type == RANDOM_IO) || dip->di_variable_flag)) {
		set_rseed (dip->di_random_seed);
	    }
	    (void) (*dtf->tf_start_test)(dip);
	    (void) (*dtf->tf_read_file)(dip);
	    (void) (*dtf->tf_end_test)(dip);
	    dip->di_pass_count++;			/* End of read pass.	*/
	    /*
	     * Prevent pass unless looping, since terminate reports
	     * the total statistics when called (prevents dup stats).
	     */
	    if ( (dip->di_pass_limit > 1) || dip->di_runtime) {
		report_pass (dip, READ_STATS);	/* Report read stats.	*/
		if (dip->di_end_delay) {	/* Optional end delay. 	*/
		    mySleep(dip, dip->di_end_delay);
		}
	    }
	    if ( (dip->di_total_errors < dip->di_error_limit) &&
		 ((dip->di_pass_count < dip->di_pass_limit) || dip->di_runtime) ) {
		int open_mode;
		SetupBufferingMode(dip, &dip->di_open_flags);
		open_mode = (dip->di_ropen_mode | dip->di_open_flags);
		status = (*dtf->tf_reopen_file)(dip, open_mode);
		if (status != SUCCESS) break;
	    }
	} /* End of a pass! */
	if (dip->di_stop_on_file) {
	    struct stat sb;
	    if (stat (dip->di_stop_on_file, &sb) == SUCCESS) {
		if (dip->di_verbose_flag) {
		    Printf("Detected stop on file '%s', so stopping test...\n",  dip->di_stop_on_file);
		}
		break;
	    }
	}
    }

    //status = finish_test(dip, status, TRUE);
    dip->di_exit_status = status;
    if (dip->di_debug_flag || dip->di_tDebugFlag) {
	Printf("I/O has completed, thread exiting with status %d...\n", dip->di_exit_status);
    }
    pthread_exit(dip);
    return(NULL);
}

int
finish_test(dinfo_t *dip, int code, bool do_cleanup)
{
    int status = SUCCESS;

    /*
     * Close file, which for AIO waits for outstanding I/O's,
     * before reporting statistics so they'll be correct.
     */
    if (dip && do_cleanup && (dip->di_fd != NoFd) ) {
	status = (*dip->di_funcs->tf_close)(dip);
	if (status != SUCCESS) code = status;
    }
    gather_stats(dip);		/* Gather the device statistics. */
    gather_totals(dip);		/* Update the total statistics.	*/
    report_stats(dip, TOTAL_STATS);

    /*
     * If keep on error, do the appropriate thing!
     */
    if (dip->di_dispose_mode == KEEP_ON_ERROR) {
	/* Note: Signals cause files to be kept! */
	if ( (code != SUCCESS) && (code != END_OF_FILE) ) {
	    dip->di_dispose_mode = KEEP_FILE;
	} else if (dip && !dip->di_existing_file) {
	    dip->di_dispose_mode = DELETE_FILE;
	}
    }
    /*
     * Delete the output file, if requested to do so.
     */
    if (do_cleanup && dip->di_output_file && (dip->di_io_mode == TEST_MODE)	&&
	(dip->di_dispose_mode == DELETE_FILE)					&&
	(dip && dip->di_dtype && (dip->di_dtype->dt_dtype == DT_REGULAR)) ) {
	int status = delete_files(dip);
	if (status) code = status; /* Delete failed, that's a test failure! */
    }

#if defined(SYSLOG)
    if (dip->di_syslog_flag) {
	syslog(LOG_INFO, "(%d) Finished: %s", dip->di_process_id, dip->di_cmd_line);
    }
#endif /* defined(SYSLOG) */

    if (dip && dip->di_history_size && dip->di_history_dump) {
	dump_history_data(dip);	/* For debugging history mechanism */
    }
    if ( (eof_status_flag == FALSE) && (code == END_OF_FILE)) {
	code = SUCCESS;		/* Map end-of-file status to Success! */
    }
    if (dip->di_debug_flag || dip->di_pDebugFlag || dip->di_tDebugFlag || nate_flag) {
	Printf ("Terminating with status code %d...\n", code);
    }
    if (core_dump && (code != SUCCESS) && (code != END_OF_FILE)) {
	abort();			/* Generate a core dump. */
    }
    /*
     * Map signal numbers and/or other errno's to FAILURE. (cleanup)
     * ( easier for scripts to handle! )
     */
    if ( (code != FAILURE) && (code != SUCCESS) && (code != END_OF_FILE) ) {
	code = FAILURE;			/* Usually a signal number. */
    }
    return (code);
}

/************************************************************************
 *									*
 * parse_args() - Parse 'dt' Program Arguments.				*
 *									*
 * Inputs:								*
 * 	dip = The device information pointer.				*
 *	argc = The number of arguments.					*
 *	argv = Array pointer to arguments.				*
 *									*
 ************************************************************************/
void
parse_args(dinfo_t *dip, int argc, char **argv)
{
	int i;
	char *string;
	int status = SUCCESS;

	/* TODO: All strings must be dup'ed for threads! */
	
	if (argc == 1) dtusage();
	for (i = 1; i < argc; i++) {
	    string = argv[i];
	    if (match (&string, "aios=")) {
		dip->di_aio_bufs = (int)number(dip, string, ANY_RADIX, &status, TRUE);
		if (dip->di_aio_bufs) dip->di_aio_flag = TRUE;
		continue;
	    }
            if (match (&string, "alarm=")) {
                dip->di_alarmtime = time_value(string);
                continue;
            }
	    if (match (&string, "bufmodes=")) {
            bufmode_loop:
                if (match(&string, ","))
                    goto bufmode_loop;
                if (*string == '\0')
                    continue;
		if (dip->di_bufmode_count == NUM_BUFMODES) {
		    LogMsg (efp, logLevelError, 0,
			    "Too many buffering modes specified, max is %d\n", NUM_BUFMODES);
		    finish_exiting(dip, FATAL_ERROR);
		}
		if (match(&string, "buffered")) {
		    dip->di_buffer_modes[dip->di_bufmode_count++] = BUFFERED_IO;
		} else if (match(&string, "unbuffered")) {
		    dip->di_buffer_modes[dip->di_bufmode_count++] = UNBUFFERED_IO;
		} else if (match(&string, "cachereads")) {
		    dip->di_buffer_modes[dip->di_bufmode_count++] = CACHE_READS;
		} else if (match(&string, "cachewrites")) {
		    dip->di_buffer_modes[dip->di_bufmode_count++] = CACHE_WRITES;
		} else {
		    LogMsg (efp, logLevelError, 0,
			    "Invalid bufmode keyword: %s\n", string);
		    finish_exiting(dip, FATAL_ERROR);
		}
		goto bufmode_loop;
	    }
	    if (match (&string, "boff=")) {
		if (match(&string, "dec")) {
		    dip->di_boff_format = DEC_FMT;
		} else if (match (&string, "hex")) {
		    dip->di_boff_format = HEX_FMT;
		} else {
		    LogMsg (efp, logLevelError, 0,
			    "Valid buffer offset formats are: dec or hex\n");
		    finish_exiting(dip, FATAL_ERROR);
		}
		continue;
	    }
	    if (match (&string, "dfmt=")) {
		if (match(&string, "byte")) {
		    dip->di_data_format = BYTE_FMT;
		} else if (match (&string, "word")) {
		    dip->di_data_format = WORD_FMT;
		} else {
		    LogMsg (efp, logLevelError, 0,
			    "Valid data formats are: byte or word\n");
		    finish_exiting(dip, FATAL_ERROR);
		}
		continue;
	    }
            if (match (&string, "keepalive=")) {
                dip->di_keepalive = string;
                dip->di_user_keepalive = TRUE;
                continue;
            }
            if (match (&string, "keepalivet=")) {
                dip->di_keepalive_time = time_value(string);
		if (dip->di_keepalive_time) {
		    if (!dip->di_alarmtime) dip->di_alarmtime = dip->di_keepalive_time;
		}
		continue;
	    }
            if (match (&string, "pkeepalive=")) {
                dip->di_pkeepalive = string;
                dip->di_user_pkeepalive = TRUE;
                continue;
            }
            if (match (&string, "tkeepalive=")) {
                dip->di_tkeepalive = string;
                dip->di_user_tkeepalive = TRUE;
                continue;
            }
            if (match (&string, "noprogt=")) {
                dip->di_noprogtime = time_value(string);
                if (dip->di_noprogtime) {
		    dip->di_noprog_flag = TRUE;
		    if (!dip->di_alarmtime) dip->di_alarmtime = dip->di_noprogtime;
                }
                continue;
            }
            if (match (&string, "noprogtt=")) {
                dip->di_noprogttime = time_value(string);
		if (dip->di_noprogttime && !dip->di_noprogtime) {
		    dip->di_noprog_flag = TRUE;
		    dip->di_noprogtime = dip->di_noprogttime;
		    if (!dip->di_alarmtime) dip->di_alarmtime = dip->di_noprogttime;
		}
                continue;
            }
	    if (match (&string, "notime=")) {
		int i;
		optiming_t *optp;
		/*
		 * May loop through table more than once, as we parse
		 * multiple options: notime=fsync,open,close...
		 */
		do {
		    optp = &optiming_table[OPEN_OP];
		    for ( i = OPEN_OP; (i < NUM_OPS); optp++, i++ ) {
			if ( match(&string, ",") ) break;
			if ( match(&string, optp->opt_name) ) {
			    optp->opt_timing_flag = FALSE;
			    break;
			}
		    }
		    if (i == NUM_OPS) break;	/* optype not found! */
		    if (*string == '\0') break; /* done parsing */
		} while (TRUE);
		if ( i == NUM_OPS ) {
		    Fprintf("%s is not a valid operation type to disable!\n", string);
		    optp = &optiming_table[OPEN_OP];
		    Fprintf("Valid operation types are: ");
		    for ( i = OPEN_OP; (i < NUM_OPS); optp++, i++ ) {
			Fprint("%s ", optp->opt_name);
		    }
		    Fprint("\n");
		    finish_exiting(dip, FATAL_ERROR);
		}
                continue;
            }
            if (match (&string, "totals=")) {
                totals_msg = string;
                continue;
            }
	    if (match (&string, "align=")) {
		if (match (&string, "rotate")) {
		    dip->di_rotate_flag = TRUE;
		    continue;
		}
		dip->di_align_offset = (u_int) number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "bs=")) {
		if (match(&string, "random")) {
		    if (dip->di_user_min == FALSE) {
			dip->di_min_size = MIN_RANDOM_SIZE;
		    }
		    if (dip->di_user_max == FALSE) {
			dip->di_max_size = MAX_RANDOM_SIZE;
		    }
		    dip->di_variable_flag = TRUE;
		    continue;
		}
		dip->di_variable_flag = FALSE;
		dip->di_block_size = number(dip, string, ANY_RADIX, &status, TRUE);
		if ((ssize_t)dip->di_block_size <= (ssize_t) 0) {
		    LogMsg (efp, logLevelError, 0,
			    "block size must be positive and non-zero.\n");
		    finish_exiting(dip, FATAL_ERROR);
		}
		continue;
	    }
	    if (match (&string, "capacity=")) {
		if (match (&string, "max")) {
		    dip->di_max_capacity = TRUE;
		} else {
		    dip->di_user_capacity = large_number(dip, string, ANY_RADIX, &status, TRUE);
		}
		continue;
	    }
	    if (match (&string, "dsize=")) {
		dip->di_device_size = number(dip, string, ANY_RADIX, &status, TRUE);
		/*
		 * Adjust the dump limit to the device size (as appropriate).
		 */
		if ( (dip->di_dump_limit == DEFAULT_DUMP_LIMIT) &&
		     (dip->di_device_size > DEFAULT_DUMP_LIMIT) ) {
		    dip->di_dump_limit = dip->di_device_size;
		}
		continue;
	    }
	    if (match (&string, "ffreq=")) {
		dip->di_fsync_frequency = number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "hdsize=")) {
		dip->di_history_data_size = (int)number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "history=")) {
		dip->di_history_size = (int)number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "lba=")) {
		dip->di_lbdata_flag = TRUE;
		dip->di_lbdata_addr = number(dip, string, ANY_RADIX, &status, TRUE);
		dip->di_user_lbdata = TRUE;
		continue;
	    }
	    if (match (&string, "lbs=")) {
		dip->di_lbdata_flag = TRUE;
		dip->di_lbdata_size = number(dip, string, ANY_RADIX, &status, TRUE);
		dip->di_user_lbsize = TRUE;
		if ((ssize_t)dip->di_lbdata_size <= (ssize_t) 0) {
		    LogMsg (efp, logLevelError, 0,
			    "lbdata size must be positive and non-zero.\n");
		    finish_exiting(dip, FATAL_ERROR);
		}
		continue;
	    }
	    if (match (&string, "maxbad=")) {
		dip->di_max_bad_blocks = (u_int)number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if ( (match (&string, "count=")) || (match (&string, "records=")) ) {
		if (dip->di_fsincr_flag) {
		    LogMsg (efp, logLevelError, 0,
			    "Cannot use record count with file size increment option!\n");
		    finish_exiting(dip, FATAL_ERROR);
		}
		dip->di_record_limit = large_number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "cancel_delay=")) {
		cancel_delay = (u_int) number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "kill_delay=")) {
		kill_delay = (u_int) number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "odelay=")) {
		if (match (&string, "random")) {
		    dip->di_open_delay = RANDOM_DELAY_VALUE;
		} else {
		    dip->di_open_delay = (u_int) number(dip, string, ANY_RADIX, &status, TRUE);
		}
		continue;
	    }
	    if (match (&string, "cdelay=")) {
		if (match (&string, "random")) {
		    dip->di_close_delay = RANDOM_DELAY_VALUE;
		} else {
		    dip->di_close_delay = (u_int) number(dip, string, ANY_RADIX, &status, TRUE);
		}
		continue;
	    }
	    if (match (&string, "edelay=")) {
		if (match (&string, "random")) {
		    dip->di_end_delay = RANDOM_DELAY_VALUE;
		} else {
		    dip->di_end_delay = (u_int) number(dip, string, ANY_RADIX, &status, TRUE);
		}
		continue;
	    }
	    if (match (&string, "rdelay=")) {
		if (match (&string, "random")) {
		    dip->di_read_delay = RANDOM_DELAY_VALUE;
		} else {
		    dip->di_read_delay = (u_int) number(dip, string, ANY_RADIX, &status, TRUE);
		}
		continue;
	    }
	    if (match (&string, "sdelay=")) {
		if (match (&string, "random")) {
		    dip->di_start_delay = RANDOM_DELAY_VALUE;
		} else {
		    dip->di_start_delay = (u_int) number(dip, string, ANY_RADIX, &status, TRUE);
		}
		continue;
	    }
	    if (match (&string, "tdelay=")) {
		dip->di_term_delay = (u_int) number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "wdelay=")) {
		if (match (&string, "random")) {
		    dip->di_write_delay = RANDOM_DELAY_VALUE;
		} else {
		    dip->di_write_delay = (u_int) number(dip, string, ANY_RADIX, &status, TRUE);
		}
		continue;
	    }
	    if (match (&string, "retry_delay=")) {
		dip->di_retry_delay = (u_int) number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "retry_error=")) {
		int error_code;
		if (dip->di_retry_entries == RETRY_ENTRIES) {
		    LogMsg (efp, logLevelError, 0,
			    "Maximum retry entries is %d.\n", RETRY_ENTRIES);
		    finish_exiting(dip, FATAL_ERROR);
		}
		/* Add a few errors that can be referenced by name. */
#if defined(WIN32)
		if (match(&string, "ERROR_BUSY")) {
		    error_code = ERROR_BUSY;			// 170L
		} else if (match(&string, "ERROR_IO_DEVICE")) {
		    error_code = ERROR_IO_DEVICE;		// 1117L
		} else if (match(&string, "ERROR_VC_DISCONNECTED")) {
		    error_code = ERROR_VC_DISCONNECTED;		// 240L
		} else if (match(&string, "ERROR_UNEXP_NET_ERR")) {
		    error_code = ERROR_UNEXP_NET_ERR;		// 59L
		} else if (match(&string, "ERROR_SEM_TIMEOUT")) {
		    error_code = ERROR_SEM_TIMEOUT;		// 121L
		} else if (match(&string, "ERROR_NETNAME_DELETED")) {
		    error_code = ERROR_NETNAME_DELETED;		// 64L
		} else if (match(&string, "*")) {
		    error_code = -1;				// All errors!
		} else {
		    error_code = (int)number(dip, string, ANY_RADIX, &status, TRUE);
		}
#else /* !defined(WIN32) */
		/* Note: I think the value of these varies by Host OS! */
		if (match(&string, "EBUSY")) {
		    error_code = EBUSY;
		} else if (match(&string, "EIO")) {
		    error_code = EIO;
		} else if (match(&string, "ENXIO")) {
		    error_code = ENXIO;
		} else if (match(&string, "ENODEV")) {
		    error_code = ENODEV;
		} else if (match(&string, "ESTALE")) {
		    error_code = ESTALE;
		} else if (match(&string, "*")) {
		    error_code = -1;
		} else {
		    error_code = (int)number(dip, string, ANY_RADIX, &status, TRUE);
		}
#endif /* defined(WIN32) */
		dip->di_retry_errors[dip->di_retry_entries++] = error_code;
		if (dip->di_error_limit < dip->di_retry_limit) {
		    dip->di_error_limit = dip->di_retry_limit;
		}
		continue;
	    }
	    if (match (&string, "retry_limit=")) {
		dip->di_retry_limit = (u_int)number(dip, string, ANY_RADIX, &status, TRUE);
		if (dip->di_error_limit < dip->di_retry_limit) {
		    dip->di_error_limit = dip->di_retry_limit;
		}
		continue;
	    }
	    if (match (&string, "term_retries=")) {
		term_wait_retries = (u_int) number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "term_timeout=")) {
		term_wait_timeout = (u_int) number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "errors=")) {
		dip->di_error_limit = number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "hz=")) {
		hz = (u_int) number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "incr=")) {
		dip->di_user_incr = TRUE;
		if (match (&string, "var")) {
		    dip->di_variable_flag = TRUE;
		} else {
		    dip->di_variable_flag = FALSE;
		    dip->di_incr_count = number(dip, string, ANY_RADIX, &status, TRUE);
		}
		continue;
	    }
	    if (match (&string, "dlimit=")) {
		dip->di_dump_limit = number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "limit=")) {
		dip->di_data_limit = large_number(dip, string, ANY_RADIX, &status, TRUE);
		dip->di_user_limit = dip->di_data_limit;
		if (!dip->di_record_limit) {
		    dip->di_record_limit = INFINITY;
		}
		continue;
	    }
	    if (match (&string, "maxdata=")) {
		dip->di_max_data = large_number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "ralign=")) {
		dip->di_io_type = RANDOM_IO;
                dip->di_user_ralign = TRUE;
		dip->di_random_align = number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "rlimit=")) {
		dip->di_io_type = RANDOM_IO;
		dip->di_rdata_limit = large_number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "max=")) {
		dip->di_user_max = TRUE;
		dip->di_max_size = (size_t) number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "min=")) {
		dip->di_user_min = TRUE;
		dip->di_min_size = (size_t) number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "enable=")) {
	    eloop:
		if (match(&string, ","))
		    goto eloop;
		if (*string == '\0')
		    continue;
		if (match(&string, "aio")) {
		    dip->di_aio_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "bypass")) {
		    dip->di_bypass_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "cerrors")) {
		    dip->di_cerrors_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "child")) {
		    dip->di_child_flag = TRUE;
		    dip->di_logpid_flag = TRUE;
		    dip->di_unique_file = TRUE;
		    goto eloop;
		}
		if (match(&string, "compare")) {
		    dip->di_compare_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "coredump")) {
		    core_dump = TRUE;
		    goto eloop;
		}
		if (match(&string, "deleteperpass")) {
		    dip->di_delete_per_pass = TRUE;
		    goto eloop;
		}
		if (match(&string, "debug")) {
		    dip->di_debug_flag = debug_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "Debug")) {
		    dip->di_Debug_flag = dip->di_debug_flag = debug_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "edebug")) {
		    dip->di_eDebugFlag = TRUE;
		    goto eloop;
		}
		if (match(&string, "fdebug")) {
		    dip->di_fDebugFlag = TRUE;
		    goto eloop;
		}
		if (match(&string, "mdebug")) {
		    dip->di_mDebugFlag = mDebugFlag = TRUE;
		    goto eloop;
		}
		if (match(&string, "mntdebug")) {
		    dip->di_mntDebugFlag = TRUE;
		    goto eloop;
		}
		if (match(&string, "pdebug")) {
		    dip->di_pDebugFlag = pDebugFlag = TRUE;
		    goto eloop;
		}
		if (match(&string, "rdebug")) {
		    dip->di_rDebugFlag = TRUE;
		    goto eloop;
		}
		if (match(&string, "sdebug")) {
		    dip->di_sDebugFlag = TRUE;
		    goto eloop;
		}
		if (match(&string, "tdebug")) {
		    dip->di_tDebugFlag = tDebugFlag = TRUE;
		    goto eloop;
		}
		if (match(&string, "diag")) {
		    dip->di_logdiag_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "dumpall")) {
		    dip->di_dumpall_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "dump")) {
		    dip->di_dump_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "eof")) {
		    eof_status_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "fsincr")) {
		    /* Note: limit= sets the record limit too! */
		    if (dip->di_record_limit && (dip->di_record_limit != INFINITY)) {
			LogMsg (efp, logLevelError, 0,
				"Cannot use file size increment option with a record limit!\n");
			finish_exiting(dip, FATAL_ERROR);
		    }
		    dip->di_fsincr_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "fsync")) {
		    dip->di_fsync_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "fsalign")) {
		    dip->di_fsalign_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "funique")) {
		    dip->di_unique_file = TRUE;
		    goto eloop;
		}
		if (match(&string, "hazard")) {
		    efp = ofp;			/* Write errors to stdout. */
		    hazard_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "header")) {
		    dip->di_header_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "hdump")) {
		    dip->di_history_dump = TRUE;
		    goto eloop;
		}
		if (match(&string, "htiming")) {
		    dip->di_history_timing = TRUE;
		    goto eloop;
		}
		if (match(&string, "lbdata")) {
		    dip->di_lbdata_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "logpid")) {
		    dip->di_logpid_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "looponerror")) {
		    dip->di_loop_on_error = TRUE;
		    goto eloop;
		}
		if (match(&string, "microdelay")) {
		    dip->di_micro_flag = TRUE;
		    goto eloop;
		}
#if defined(MMAP)
		if (match(&string, "mmap")) {
		    dip->di_mmap_flag = TRUE;
		    dip->di_wopen_mode = O_RDWR;	/* MUST open read/write. */
		    goto eloop;
		}
#endif /* defined(MMAP) */
		if (match(&string, "mount_lookup")) {
		    dip->di_mount_lookup = TRUE;
		    goto eloop;
		}
		if (match(&string, "multi")) {
		    dip->di_multi_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "noprog")) {
		    dip->di_noprog_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "prefill")) {
		    dip->di_prefill_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "pstats")) {
		    dip->di_pstats_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "raw")) {
		    dip->di_raw_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "reread")) {
		    dip->di_reread_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "readcache")) {
		    dip->di_read_cache_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "writecache")) {
		    dip->di_write_cache_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "retryDC")) {
		    dip->di_retryDC_flag = TRUE;
		    goto eloop;
		}
#if defined(SCSI)
		if (match(&string, "scsi")) {
		    dip->di_scsi_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "serrors")) {
		    dip->di_scsi_errors = TRUE;
		    goto eloop;
		}
		if (match(&string, "unmap")) {
		    dip->di_unmap_flag = TRUE;
		    goto eloop;
		}
#endif /* defined(SCSI) */
		if (match(&string, "spad")) {
		    dip->di_spad_check = TRUE;
		    goto eloop;
		}
		if (match(&string, "sighup")) {
		    sighup_flag = TRUE;
		    goto eloop;
		}
#if defined(WIN32)
		if (match(&string, "prealloc")) {
		    dip->di_prealloc_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "sparse")) {
		    dip->di_sparse_flag = TRUE;
		    goto eloop;
		}
#endif /* defined(WIN32) */
		if (match(&string, "stats")) {
		    dip->di_stats_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "syslog")) {
		    dip->di_syslog_flag = TRUE;
		    goto eloop;
		}
#if defined(TIMESTAMP)
		if (match(&string, "timestamp")) {
		    dip->di_timestamp_flag = TRUE;
		    goto eloop;
		}
#endif /* !defined(TIMESTAMP) */
		if (match(&string, "trigargs")) {
		    dip->di_trigargs_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "unique")) {
		    dip->di_unique_pattern = TRUE;
		    goto eloop;
		}
		if (match(&string, "verbose")) {
		    dip->di_verbose_flag = TRUE;
		    goto eloop;
		}
		if (match(&string, "verify")) {
		    dip->di_verify_flag = TRUE;
		    goto eloop;
		}
		LogMsg (efp, logLevelError, 0,
			"Invalid enable keyword: %s\n", string);
		finish_exiting(dip, FATAL_ERROR);
	    }
	    if (match (&string, "disable=")) {
	    dloop:
		if (match(&string, ","))
		    goto dloop;
		if (*string == '\0')
		    continue;
		if (match(&string, "aio")) {
		    dip->di_aio_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "bypass")) {
		    dip->di_bypass_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "cerrors")) {
		    dip->di_cerrors_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "compare")) {
		    dip->di_compare_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "deleteperpass")) {
		    dip->di_delete_per_pass = FALSE;
		    goto dloop;
		}
		if (match(&string, "debug")) {
		    dip->di_debug_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "Debug")) {
		    dip->di_Debug_flag = dip->di_debug_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "edebug")) {
		    dip->di_eDebugFlag = FALSE;
		    goto dloop;
		}
		if (match(&string, "fdebug")) {
		    dip->di_fDebugFlag = FALSE;
		    goto dloop;
		}
		if (match(&string, "mdebug")) {
		    dip->di_mDebugFlag = mDebugFlag = FALSE;
		    goto dloop;
		}
		if (match(&string, "mntdebug")) {
		    dip->di_mntDebugFlag = FALSE;
		    goto dloop;
		}
		if (match(&string, "pdebug")) {
		    dip->di_pDebugFlag = pDebugFlag = FALSE;
		    goto dloop;
		}
		if (match(&string, "rdebug")) {
		    dip->di_rDebugFlag = FALSE;
		    goto dloop;
		}
		if (match(&string, "sdebug")) {
		    dip->di_sDebugFlag = FALSE;
		    goto dloop;
		}
		if (match(&string, "tdebug")) {
		    dip->di_tDebugFlag = tDebugFlag = FALSE;
		    goto dloop;
		}
		if (match(&string, "diag")) {
		    dip->di_logdiag_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "dumpall")) {
		    dip->di_dumpall_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "dump")) {
		    dip->di_dump_flag = TRUE;
		    goto dloop;
		}
		if (match(&string, "eof")) {
		    eof_status_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "fsincr")) {
		    dip->di_fsincr_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "fsync")) {
		    dip->di_fsync_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "fsalign")) {
		    dip->di_fsalign_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "funique")) {
		    dip->di_unique_file = FALSE;
		    goto dloop;
		}
		if (match(&string, "hazard")) {
		    hazard_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "header")) {
		    dip->di_header_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "hdump")) {
		    dip->di_history_dump = FALSE;
		    goto dloop;
		}
		if (match(&string, "htiming")) {
		    dip->di_history_timing = FALSE;
		    goto dloop;
		}
		if (match(&string, "lbdata")) {
		    dip->di_lbdata_flag = FALSE;
		    dip->di_user_lbdata = FALSE;
		    goto dloop;
		}
		if (match(&string, "logpid")) {
		    dip->di_logpid_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "looponerror")) {
		    dip->di_loop_on_error = FALSE;
		    goto dloop;
		}
		if (match(&string, "microdelay")) {
		    dip->di_micro_flag = FALSE;
		    goto dloop;
		}
#if defined(MMAP)
		if (match(&string, "mmap")) {
		    dip->di_mmap_flag = FALSE;
		    goto dloop;
		}
#endif /* defined(MMAP) */
		if (match(&string, "mount_lookup")) {
		    dip->di_mount_lookup = FALSE;
		    goto dloop;
		}
		if (match(&string, "multi")) {
		    dip->di_multi_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "noprog")) {
		    dip->di_noprog_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "pad")) {
		    dip->di_pad_check = FALSE;
		    goto dloop;
		}
		if (match(&string, "prefill")) {
		    dip->di_prefill_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "pstats")) {
		    dip->di_pstats_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "raw")) {
		    dip->di_raw_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "reread")) {
		    dip->di_reread_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "readcache")) {
		    dip->di_read_cache_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "writecache")) {
		    dip->di_write_cache_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "retryDC")) {
		    dip->di_retryDC_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "sighup")) {
		    sighup_flag = FALSE;
		    goto dloop;
		}
#if defined(SCSI)
		if (match(&string, "scsi")) {
		    dip->di_scsi_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "serrors")) {
		    dip->di_scsi_errors = FALSE;
		    goto dloop;
		}
		if (match(&string, "unmap")) {
		    dip->di_unmap_flag = FALSE;
		    goto dloop;
		}
#endif /* defined(SCSI) */
		if (match(&string, "spad")) {
		    dip->di_spad_check = FALSE;
		    goto dloop;
		}
#if defined(WIN32)
		if (match(&string, "prealloc")) {
		    dip->di_prealloc_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "sparse")) {
		    dip->di_sparse_flag = FALSE;
		    goto dloop;
		}
#endif /* defined(WIN32) */
		if (match(&string, "stats")) {
		    dip->di_stats_flag = FALSE;
                    dip->di_stats_level = STATS_NONE;
		    goto dloop;
		}
		if (match(&string, "syslog")) {
		    dip->di_syslog_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "timestamp")) {
		    dip->di_timestamp_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "trigargs")) {
		    dip->di_trigargs_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "unique")) {
		    dip->di_unique_pattern = FALSE;
		    goto dloop;
		}
		if (match(&string, "verbose")) {
		    dip->di_verbose_flag = FALSE;
		    goto dloop;
		}
		if (match(&string, "verify")) {
		    dip->di_verify_flag = FALSE;
		    goto dloop;
		}
		LogMsg (efp, logLevelError, 0,
			"Invalid disable keyword: %s\n", string);
		finish_exiting(dip, FATAL_ERROR);
	    }
	    if (match (&string, "dispose=")) {
		if (match(&string, "delete")) {
		    dip->di_keep_existing = FALSE;
		    dip->di_dispose_mode = DELETE_FILE;
		} else if (match(&string, "keeponerror")) { /* parse first! */
		    dip->di_keep_existing = TRUE;
		    dip->di_dispose_mode = KEEP_ON_ERROR;
		} else if (match(&string, "keep")) {
		    dip->di_keep_existing = TRUE;
		    dip->di_dispose_mode = KEEP_FILE;
		} else {
		    LogMsg (efp, logLevelError, 0,
			    "Dispose modes are 'delete', 'keep', or 'keeponerror'.\n", string);
		    finish_exiting(dip, FATAL_ERROR);
		}
		continue;
	    }
	    if (match (&string, "dir=")) {
		dip->di_dir = string;
		continue;
	    }
	    if (match (&string, "dirp=")) {
		dip->di_dirprefix = string;
		continue;
	    }
#if not_implemented_yet
	    if (match (&string, "dirs=")) {
		dip->di_user_dir_limit = number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
#endif /* not_implemented_yet */
	    if (match (&string, "files=")) {
		dip->di_file_limit = number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "maxfiles=")) {
		dip->di_max_files = number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "sdirs=")) {
		dip->di_user_subdir_limit = number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "depth=")) {
		dip->di_user_subdir_depth = number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "if=")) {
		dip->di_input_file = string;
		continue;
	    }
	    if (match (&string, "of=")) {
		dip->di_output_file = string;
		continue;
	    }
#if defined(SCSI)
	    if (match (&string, "sdsf=")) {
		dip->di_scsi_dsf = string;
		continue;
	    }
#endif /* defined(SCSI) */
	    if (match (&string, "pf=")) {
		dip->di_pattern_file = string;
		dip->di_user_pattern = TRUE;
		continue;
	    }
	    if (match (&string, "log=")) {
		dip->di_log_file = string;
		continue;
	    }
	    if (match (&string, "logt=")) {
		dip->di_log_file = string;
		dip->di_logappend_flag = FALSE;
		continue;
	    }
	    if (match (&string, "logu=")) {
		dip->di_log_file = string;
		dip->di_unique_log = TRUE;
		continue;
	    }
	    if (match (&string, "iodir=")) {
		if (match (&string, "for")) {
		    dip->di_io_dir = FORWARD;
		    dip->di_random_io = FALSE;
		    dip->di_io_type = SEQUENTIAL_IO;
		} else if (match (&string, "rev")) {
		    dip->di_io_dir = REVERSE;
		    dip->di_random_io = TRUE;
		    dip->di_io_type = SEQUENTIAL_IO;
		} else {
		    LogMsg (efp, logLevelError, 0,
			    "Valid I/O directions are: 'forward' or 'reverse'.\n");
		    finish_exiting(dip, FATAL_ERROR);
		}
		continue;
	    }
	    if (match (&string, "iomode=")) {
		if (match (&string, "copy")) {
		    dip->di_dispose_mode = KEEP_FILE;
		    dip->di_io_mode = COPY_MODE;
		} else if (match (&string, "test")) {
		    dip->di_io_mode = TEST_MODE;
		} else if (match (&string, "verify")) {
		    dip->di_io_mode = VERIFY_MODE;
		    dip->di_verify_only = TRUE;
		} else {
		    LogMsg (efp, logLevelError, 0,
			    "Valid I/O modes are: 'copy', 'test', or verify.\n");
		    finish_exiting(dip, FATAL_ERROR);
		}
		continue;
	    }
	    if (match (&string, "iotype=")) {
		if (match (&string, "random")) {
		    dip->di_io_type = RANDOM_IO;
		    dip->di_random_io = TRUE;
		} else if (match (&string, "sequential")) {
		    dip->di_io_type = SEQUENTIAL_IO;
		    dip->di_random_io = FALSE;
		} else {
		    LogMsg (efp, logLevelError, 0,
			    "Valid I/O types are: 'random' or 'sequential'.\n");
		    finish_exiting(dip, FATAL_ERROR);
		}
		continue;
	    }
	    /*
	     * Special options to help seed IOT pattern with multiple passes.
	     */
	    if (match (&string, "iotpass=")) {
		int iot_pass = number(dip, string, ANY_RADIX, &status, TRUE);
		dip->di_iot_seed *= iot_pass;
		dip->di_iot_pattern = TRUE;
		continue;
	    }
	    if (match (&string, "iotseed=")) {
		dip->di_iot_seed = (u_int32)number(dip, string, HEX_RADIX, &status, TRUE);
		dip->di_iot_pattern = TRUE;
		continue;
	    }
	    if (match (&string, "iotune=")) {
		dip->di_iotune_file = FmtFilePath(dip, string);
		dip->di_micro_flag = TRUE;
		continue;
	    }
	    /*
	     * Flags which apply to read and write of a file.
	     *
	     * NOTE: I'm not sure all of flags applying to write only!
	     */
	    if (match (&string, "flags=")) {
	    floop:
		if (match(&string, ","))
		    goto floop;
		if (*string == '\0')
		    continue;
		if (match(&string, "none")) {
		    dip->di_open_flags = 0;		/* Clear all flags! */
		    goto floop;
		}
#if defined(O_EXCL)
		if (match(&string, "excl")) {
		    dip->di_open_flags |= O_EXCL;	/* Exclusive open. */
		    goto floop;
		}
#endif /* defined(O_EXCL) */
#if defined(O_NDELAY)
		if (match(&string, "ndelay")) {
		    dip->di_open_flags |= O_NDELAY;	/* Non-delay open. */
		    goto floop;
		}
#endif /* defined(O_NDELAY) */
#if defined(O_NONBLOCK)
		if (match(&string, "nonblock")) {
		    dip->di_open_flags |= O_NONBLOCK;	/* Non-blocking open. */
		    goto floop;
		}
#endif /* defined(O_NONBLOCK) */
#if defined(O_CACHE)
		if (match(&string, "cache")) {		/* QNX specific. */
		    dip->di_open_flags |= O_CACHE;	/* Keep data in cache. */
		    goto floop;
		}
#endif /* defined(O_CACHE) */
#if defined(O_DIRECT)
		if (match(&string, "direct")) {
		    dip->di_open_flags |= O_DIRECT;	/* Direct disk access. */
		    goto floop;
		}
#endif /* defined(O_DIRECT) */
#if defined(SOLARIS) || defined(WIN32)
		if (match(&string, "direct")) {
		    dip->di_dio_flag = TRUE;	/* No O_DIRECT on Solaris! */
		    goto floop;
		}
#endif /* defined(SOLARIS) || defined(WIN32) */
#if defined(O_FSYNC)
		if (match(&string, "fsync")) {		/* File integrity. */
		    dip->di_open_flags |= O_FSYNC;	/* Syncronize file I/O. */
		    goto floop;
		}
#endif /* defined(O_FSYNC) */
#if defined(O_RSYNC)
		if (match(&string, "rsync")) {
		    dip->di_open_flags |= O_RSYNC;	/* Read I/O integrity. */
		    goto floop;			/* Use with O_DSYNC or O_SYNC. */
		}
#endif /* defined(O_RSYNC) */
#if defined(O_SYNC)
		if (match(&string, "sync")) {
		    dip->di_open_flags |= O_SYNC;	/* Synchronous all data access. */
		    goto floop;			/* Sync data & file attributes. */
		}
#endif /* defined(O_SYNC) */
#if defined(O_LARGEFILE)
		if (match(&string, "large")) {
		    dip->di_open_flags |= O_LARGEFILE;	/* Enable large file support. */
		    goto floop;			/* Same as _FILE_OFFSET_BITS=64 */
		}
#endif /* defined(O_LARGEFILE) */
		LogMsg (efp, logLevelError, 0,
			"Invalid flag '%s' specified, please use 'help' for valid flags.\n", string); 
		finish_exiting(dip, FATAL_ERROR);
	    } /* End if "flags=" option. */
	    if (match (&string, "nice=")) {
		nice_value = number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    /*
	     * Flags which apply to opening a file for writes.
	     */
	    if (match (&string, "oflags=")) {
	    oloop:
		if (match(&string, ","))
		    goto oloop;
		if (*string == '\0')
		    continue;
		if (match(&string, "none")) {
		    dip->di_wopen_mode = 0;		/* Clear all flags! */
		    goto oloop;
		}
#if defined(WIN32)
		if (match(&string, "append")) {
		    dip->di_wopen_mode = FILE_APPEND_DATA;
		    goto oloop;
		}
#else /* !defined(WIN32) */
# if defined(O_APPEND)
		if (match(&string, "append")) {
		    dip->di_wopen_flags |= O_APPEND;	/* Append to file. */
		    goto oloop;
		}
# endif /* defined(O_APPEND) */
#endif /* defined(WIN32) */
#if defined(O_DEFER)
		if (match(&string, "defer")) {
		    dip->di_wopen_flags |= O_DEFER;	/* Defer updates. */
		    goto oloop;
		}
#endif /* defined(O_DEFER) */
#if defined(O_DSYNC)
		if (match(&string, "dsync")) {		/* Write data integrity. */
		    dip->di_wopen_flags |= O_DSYNC;	/* Synchronize data written. */
		    goto oloop;
		}
#endif /* defined(O_DSYNC) */
#if defined(O_SYNC)
		if (match(&string, "sync")) {
		    dip->di_wopen_flags |= O_SYNC;	/* Synchronous all data access. */
		    goto oloop;				/* Sync data & file attributes. */
		}
#endif /* defined(O_SYNC) */
#if defined(O_TRUNC)
		if (match(&string, "trunc")) {
		    dip->di_wopen_flags |= O_TRUNC;	/* Truncate output file. */
		    goto floop;
		}
#endif /* defined(O_TRUNC) */
#if defined(O_TEMP)
		if (match(&string, "temp")) {
		    dip->di_wopen_flags |= O_TEMP;	/* Temporary file. */
		    goto oloop;
		}
#endif /* defined(O_TEMP) */
		LogMsg (efp, logLevelError, 0,
			"Invalid output flag '%s' specified, please use 'help' for valid flags.\n", string); 
		finish_exiting(dip, FATAL_ERROR);
	    } /* End of "oflags=" option. */
	    if (match (&string, "oncerr=")) {
		if (match(&string, "abort")) {
		    dip->di_oncerr_action = ABORT;
		} else if (match(&string, "continue")) {
		    dip->di_oncerr_action = CONTINUE;
		} else {
		    LogMsg (efp, logLevelError, 0,
			    "On error actions are 'abort' or 'continue'.\n");
		    finish_exiting(dip, FATAL_ERROR);
		}
		continue;
	    }
	    if (match (&string, "passes=")) {
		dip->di_pass_limit = number(dip, string, ANY_RADIX, &status, TRUE);
		if (dip->di_pass_limit == 0) {
		    LogMsg (efp, logLevelError, 0,
			    "Please specify a pass limit greater than zero!\n");
		    finish_exiting(dip, FATAL_ERROR);
		}
		continue;
	    }
	    if (match (&string, "pattern=")) {	/* TODO: This is overloaded! */
		int size = strlen(string);
		if (size == 0) {
		    LogMsg (efp, logLevelError, 0,
		"Please specify pattern of: { hex-pattern | incr | iot | string }\n");
		    finish_exiting(dip, FATAL_ERROR);
		}
		dip->di_iot_pattern = FALSE;
		dip->di_user_pattern = TRUE;
		if (match (&string, "incr")) {	/* Incrementing pattern. */
		    int v, size = 256;
		    u_char *buffer = malloc_palign(size, 0);
		    u_char *bp = buffer;
		    for (v = 0; v < size; v++) {
			*bp++ = v;
		    }
		    dip->di_incr_pattern = TRUE;
		    setup_pattern(dip, buffer, size);
		} else if ( (size == 3) && 
			    (match(&string, "iot") || match(&string, "IOT")) ) {
		    dip->di_iot_pattern = TRUE;
		    if (dip->di_data_format == NONE_FMT) {
			dip->di_data_format = WORD_FMT;
		    }
		    /* Allocate pattern buffer after parsing. */
		} else if ( IS_HexString(string) && (size <= 10) ) {
		    /* valid strings: XXXXXXXX or 0xXXXXXXXX */
		    dip->di_pattern = (u_int32)number(dip, string, HEX_RADIX, &status, TRUE);
		} else { /* Presume ASCII string for data pattern. */
		    u_char *buffer = malloc_palign(size, 0);
		    size = StrCopy (buffer, string, size);
		    dip->di_pattern_size = size;
		    dip->di_pattern_string = string;
		    setup_pattern(dip, buffer, size);
		}
		if ( !dip->di_iot_pattern ) dip->di_unique_pattern = FALSE;
		continue;
	    }
	    if (match (&string, "prefix=")) {
                if (dip->di_prefix_string) { /* Free previous prefix (if any). */
                    free(dip->di_prefix_string);
                    dip->di_prefix_string = NULL;
                }
		dip->di_prefix_size = strlen(string);
		if (dip->di_prefix_size == 0) {
                    if (hazard_flag) {
                        continue;   /* Allow NULL override for Hazard. */
                    }
		    LogMsg (efp, logLevelError, 0,
			    "Please specify a non-empty prefix string!\n");
		    finish_exiting(dip, FATAL_ERROR);
		} else if (dip->di_prefix_size > BLOCK_SIZE) {
		    LogMsg (efp, logLevelError, 0,
			    "Please specify a prefix string < %d bytes!\n",
								dip->di_prefix_size);
		    finish_exiting(dip, FATAL_ERROR);
		}
		dip->di_prefix_string = Malloc(++dip->di_prefix_size); /* plus NULL! */
		(void)strcpy(dip->di_prefix_string, string);
		continue;
	    }
	    if (match (&string, "position=")) {
		dip->di_file_position = (OFF_T)large_number(dip, string, ANY_RADIX, &status, TRUE);
		dip->di_user_position = TRUE;
		continue;
	    }
	    if (match (&string, "oposition=")) {
		dip->di_ofile_position = (OFF_T)large_number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "procs=")) {
		dip->di_num_procs = (u_short)number(dip, string, ANY_RADIX, &status, TRUE);
		if (dip->di_num_procs > MAX_PROCS) {
		    LogMsg (efp, logLevelError, 0,
			    "Please limit procs to <= %d!\n", MAX_PROCS);
		    finish_exiting(dip, FATAL_ERROR);
		}
		continue;
	    }
#if defined(HP_UX)
            if (match (&string, "qdepth=")) {
                dip->di_qdepth = (u_int)number(dip, string, ANY_RADIX, &status, TRUE);
                if (dip->di_qdepth > SCSI_MAX_Q_DEPTH) {
                    LogMsg (efp, logLevelError, 0,
                            "Please specify a SCSI queue depth <= %d!\n", SCSI_MAX_Q_DEPTH);
		    finish_exiting(dip, FATAL_ERROR);
                }
                continue;
            }
#endif /* defined(HP_UX) */
	    if (match (&string, "rseed=")) {
		dip->di_random_seed = (u_int)number(dip, string, ANY_RADIX, &status, TRUE);
		dip->di_user_rseed = TRUE;
		continue;
	    }
	    if (match (&string, "runtime=")) {
		dip->di_user_runtime = string;
		dip->di_runtime = time_value(string);
		if (!dip->di_record_limit) {
		    dip->di_record_limit = INFINITY;
		}
		continue;
	    }
	    if (match (&string, "seek=")) {
		dip->di_seek_count = number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "skip=")) {
		dip->di_skip_count = number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "slice=")) {
		dip->di_slice_num = (u_short)number(dip, string, ANY_RADIX, &status, TRUE);
		if ( (dip->di_slice_num < 1) || (dip->di_slice_num > MAX_SLICES) ) {
		    LogMsg (efp, logLevelError, 0,
			    "Please limit slice to (1 - %d)!\n", MAX_SLICES);
		    finish_exiting(dip, FATAL_ERROR);
		}
		continue;
	    }
	    if (match (&string, "slices=")) {
		dip->di_num_slices = (u_short)number(dip, string, ANY_RADIX, &status, TRUE);
		if (dip->di_num_slices > MAX_SLICES) {
		    LogMsg (efp, logLevelError, 0,
			    "Please limit maximum slices to <= %d!\n", MAX_SLICES);
		    finish_exiting(dip, FATAL_ERROR);
		}
		continue;
	    }
	    if (match (&string, "step=")) {
		dip->di_step_offset = (OFF_T)large_number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "stats=")) {
                if (match (&string, "brief")) {
                    dip->di_stats_level = STATS_BRIEF;
		} else if (match (&string, "full")) {
		    dip->di_stats_level = STATS_FULL;
		} else if (match (&string, "none")) {
                    dip->di_pstats_flag = dip->di_stats_flag = FALSE;
		    dip->di_stats_level = STATS_NONE;
		    dip->di_verbose_flag = FALSE; /* To overcome compatability check in report_pass()! */
		} else {
		    LogMsg (efp, logLevelError, 0,
			    "Valid stat levels are: 'brief', 'full', or 'none'\n");
		    finish_exiting(dip, FATAL_ERROR);
		}
		continue;
	    }
	    if (match (&string, "dtype=")) {
		struct dtype *dtp;
		if ((dtp = setup_device_type (string)) == NULL) {
		    finish_exiting(dip, FATAL_ERROR);
		}
		dip->di_input_dtype = dip->di_output_dtype = dtp;
		continue;
	    }
	    if (match (&string, "idtype=")) {
		if ((dip->di_input_dtype = setup_device_type (string)) == NULL) {
		    finish_exiting(dip, FATAL_ERROR);
		}
		continue;
	    }
	    if (match (&string, "odtype=")) {
		if ((dip->di_output_dtype = setup_device_type (string)) == NULL) {
		    finish_exiting(dip, FATAL_ERROR);
		}
		continue;
	    }
#if defined(SCSI)
	    if (match (&string, "scsi_timeout=")) {
		dip->di_scsi_timeout = (u_short)number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "spt_path=")) {
		dip->di_spt_path = string;
		continue;
	    }
	    if (match (&string, "unmap_freq=")) {
		dip->di_unmap_frequency = number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
#endif /* defined(SCSI) */
	    if (match (&string, "stopon=")) {
		dip->di_stop_on_file = string;
		continue;
	    }
            if (match (&string, "trigger=")) {
		trigger_data_t *tdp = &dip->di_triggers[dip->di_num_triggers];
		if (dip->di_num_triggers == NUM_TRIGGERS) {
		    LogMsg (efp, logLevelError, 0,
			    "Maximum number of triggers is %d.\n", NUM_TRIGGERS);
		    finish_exiting(dip, FATAL_ERROR);
		}
                if ((tdp->td_trigger = check_trigger_type(dip, string)) == TRIGGER_INVALID) {
		    finish_exiting(dip, FATAL_ERROR);
                }
		dip->di_num_triggers++;
                continue;
            }
	    if (match (&string, "vrecords=")) {
	        dip->di_volume_records = number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "volumes=")) {
	        dip->di_multi_flag = TRUE;
		dip->di_volumes_flag = TRUE;
	        dip->di_volume_limit = number(dip, string, ANY_RADIX, &status, TRUE);
		continue;
	    }
	    if (match (&string, "help")) {
		dthelp(dip);
	    }
	    if (match (&string, "version")) {
		dtversion();
	    }
	    LogMsg (efp, logLevelError, 0,
		    "Invalid option '%s' specified, please use 'help' for valid options.\n",
									string);
	    finish_exiting(dip, FATAL_ERROR);
	}
#if !defined(AIO)
	if (dip->di_aio_flag) {
	    Printf ("Warning, POSIX AIO is NOT supported on this platform, disabling AIO!\n");
	    dip->di_aio_flag = FALSE;
	}
#endif /* !defined(AIO) */
}

/*
 * match() - Match a Substring within a String.
 *
 * Inputs:
 *	sptr = Pointer to string pointer.
 *	s = The substring to match.
 *
 * Outputs:
 *	sptr = Points past substring (on match).
 *
 * Return Value:
 *	Returns TRUE/FALSE = Match / Not Matched
 */
bool
match (char **sptr, char *s)
{
    char *cs;

    cs = *sptr;
    while (*cs++ == *s) {
	if (*s++ == '\0') {
	    goto true;
	}
    }
    if (*s != '\0') {
	return(FALSE);
    }
true:
    cs--;
    *sptr = cs;
    return(TRUE);
}

/*
 * number() - Converts ASCII string into numeric value.
 *
 * Inputs:
 *	str = The string to convert.
 * 	base = The base for numeric conversions.
 * 	status = Pointer to return parse status.
 * 	report_error = Flag to control errors.
 * 
 * Outputs:
 * 	status = SUCCESS or FAILURE
 *
 * Return Value:
 *      Returns converted number.
 */
unsigned int
number(dinfo_t *dip, char *str, int base, int *status, bool report_error)
{
    char *eptr;
    unsigned int value;

    *status = SUCCESS;
    value = CvtStrtoValue(dip, str, &eptr, base);
    if (*eptr != '\0') {
	if (report_error) {
	    Fprintf("Error parsing '%s', invalid character detected in number: '%c'\n",
		    str, *eptr);
	}
        *status = FAILURE;
    }
    return(value);
}

large_t
large_number(dinfo_t *dip, char *str, int base, int *status, bool report_error)
{
    char *eptr;
    large_t value;

    *status = SUCCESS;
    value = CvtStrtoLarge(dip, str, &eptr, base);
    if (*eptr != '\0') {
	if (report_error) {
	    Fprintf("Error parsing '%s', invalid character detected in number: '%c'\n",
		    str, *eptr);
	}
        *status = FAILURE;
    }
    return(value);
}

time_t
time_value(char *str)
{
    char *eptr;
    time_t value;

    value = CvtTimetoValue (str, &eptr);

    if (*eptr != '\0') {
	LogMsg (efp, logLevelError, 0,
		"Invalid character detected in time string: '%c'\n", *eptr);
	finish_exiting(NULL, FATAL_ERROR);
    }
    return (value);
}

/************************************************************************
 *									*
 * report_error() - Report system error information.			*
 *									*
 * Inputs:							        * 
 * 	dip = The device information pointer.				*
 *	error_info = Additional error info for perror.			*
 *	record_flag = Controls reporting error/time info.		*
 *									*
 ************************************************************************/
void
report_error(
	dinfo_t		*dip,
	char		*error_info,
	int		record_flag)
{
    int saved_errno;
    char *emsg;

    saved_errno = errno;
#if defined(WIN32)
    errno = GetLastError();
#endif /* defined(WIN32) */

    dip->di_errno = errno;
    
    /*
     * History is dumped here to display history on ALL errors.
     */
    if (dip->di_history_size) {
	dump_history_data(dip);
    }

#if defined(WIN32)
    emsg = werror_msg(errno);
#else /* !defined(WIN32) */
    emsg = strerror(errno);
#endif /* defined(WIN32) */

    if (dip->di_file_limit && dip->di_dname) {
	LogMsg (efp, logLevelCrit, 0,
		"File %s: '%s', errno = %d - %s\n", dip->di_dname, error_info, errno, emsg);
    } else {
	LogMsg (efp, logLevelCrit, 0,
		"'%s', errno = %d - %s\n", error_info, errno, emsg);
    }

#if defined(SYSLOG)
    if (dip->di_syslog_flag) {
	if (dip->di_file_limit && dip->di_dname) {
	    (void)sprintf(dip->di_msg_buffer, "(%d): File %s, '%s', errno = %d - %s\n",
			  dip->di_process_id, dip->di_dname, error_info, errno, emsg);
	} else {
	    (void)sprintf(dip->di_msg_buffer, "(%d): '%s', errno = %d - %s\n",
			  dip->di_process_id, error_info, errno, emsg);
	}
	syslog(LOG_ERR, dip->di_msg_buffer);
    }
#endif /* defined(SYSLOG) */

    exit_status = FAILURE;
    if (record_flag) {
	(void)time(&dip->di_error_time);
	Fprintf ("Error number %lu occured on %s", ++dip->di_error_count,
		 os_ctime(&dip->di_error_time, dip->di_time_buffer, sizeof(dip->di_time_buffer)));
    }
    errno = saved_errno;
    return;
}

/*
 * report_record() - Report Record Information.
 *
 * Description:
 *	This function is used when Debug is enabled, and is also
 * used to dump a history data entry.
 *
 * Inputs:
 *	dip = The device information pointer.
 *	files = The file number (limited to tapes at present).
 *	records = The record number.
 *	lba = The logical block number (NO_LBA if none).
 *	pos = The file position.
 *	mode = The test mode (READ_MODE or WRITE_MODE).
 *	buffer = The data buffer.
 *	bytes = The data byte count.
 *
 * Return Value:
 *	void
 */
void
report_record(
	struct dinfo	*dip,
	u_long		files,
	u_long		records,
	large_t		lba,
        OFF_T           pos,
	enum test_mode	mode,
	void		*buffer,
	size_t		bytes )
{
    char msg[STRING_BUFFER_SIZE];
    char *bp = msg;
    u_int32 boff = 0, eoff = 0;
    u_int32 blocks = 0;
    large_t elba = 0;

    /*
     * Depending on data supplied, calculate ending block,
     * and block offsets (for file system testing).
     */
    if ( (lba != NO_LBA) && dip->di_dsize) {
        elba = ((lba + howmany(bytes, dip->di_dsize)) - 1);
        blocks = (u_int32)((elba - lba) + 1);
	boff = (u_int32)(pos % dip->di_dsize);
	eoff = (u_int32)((pos + bytes) % dip->di_dsize);
    }
    if ( dip->di_multiple_files || (dip->di_dtype->dt_dtype == DT_TAPE) ) {
	bp += sprintf(bp, "File #%lu, ", files);
    }
    bp += sprintf(bp, "Record #%lu - ", records);
    /*
     * A buffer indicates runtime debug, else assume dumping history.
     */
    if (buffer) {
	bp += sprintf(bp, "%s %u byte%s ",
		      (mode == READ_MODE) ? "Reading" : "Writing",
		      (unsigned int)bytes, (bytes > 1) ? "s" : "");
    } else {
	bp += sprintf(bp, "%s %u byte%s ",
		      (mode == READ_MODE) ? "Read" : "Wrote",
		      (unsigned int)bytes, (bytes > 1) ? "s" : "");
    }
    if (lba != NO_LBA) {
        bp += sprintf(bp, "(%u block%s) ", blocks, (blocks > 1) ? "s" : "");
    }
    if (buffer) {
	bp += sprintf(bp, "%s buffer %#lx, ",
		 (mode == READ_MODE) ? "into" : "from",
		 (u_long)buffer);
    }
    if (lba != NO_LBA) {
        bp += sprintf(bp, "lba%s ", (elba > lba) ? "'s" : "");
        if (boff && eoff) {
            bp += sprintf(bp, LUF ".%u - " LUF ".%u", lba, boff, elba, eoff);
        } else if (boff) {
            bp += sprintf(bp, LUF ".%u - " LUF, lba, boff, elba);
        } else if (eoff) {
            bp += sprintf(bp, LUF " - " LUF ".%u", lba, elba, eoff);
        } else if (lba != elba) {
	    bp += sprintf(bp, LUF " - " LUF, lba, elba);
        } else {
            bp += sprintf(bp, LUF, lba);
        }
    }
    bp += sprintf(bp, " (pos " FUF ")", pos);
    bp += sprintf(bp, "\n");
    if (buffer) {
	Printf(msg);
    } else {
	Print(msg);
    }
}

int
start_iotuning(dinfo_t *dip)
{
    int pstatus = WARNING;

    if ( (dip->di_iotuning_flag == TRUE) && (dip->di_iotune_file) ) {
        pstatus = pthread_attr_setdetachstate(tattrp, PTHREAD_CREATE_DETACHED);
        if (pstatus != SUCCESS) {
            tPerror(pstatus, "pthread_attr_setdetachstate() failed setting PTHREAD_CREATE_DETACHED");
        }
        pstatus = pthread_create( &iotuneThread, tattrp, do_iotune_file, dip );
        if (pstatus != SUCCESS) {
            tPerror(pstatus, "pthread_create() failed for iotuning");
        }
    }
    return (pstatus);
}

void *
do_iotune_file(void *arg)
{
    dinfo_t *dip = arg;

    dip->di_iotuning_active = TRUE;
#if defined(WIN32)
    iotuneThreadId = pthread_self();
#endif
    if (dip->di_debug_flag || dip->di_tDebugFlag) {
        Printf("I/O Tuning Thread ID is %u\n", iotuneThreadId);
    }
    do {
        SleepSecs(dip->di_iotune_delay);
        HANDLE_TERMINATE(dip);
        process_iotune(dip, dip->di_iotune_file);

    } while ( TRUE );

    dip->di_iotuning_active = FALSE;
    pthread_exit(dip);
    return(NULL);
}

void
report_times(time_t initiated_time, time_t current_time)
{
    char time_buffer[TIME_BUFFER_SIZE];

    Printf("   The current time is: " TMF " seconds => %s", current_time,
	   os_ctime(&current_time, time_buffer, sizeof(time_buffer)));
    Printf("The initiated time was: " TMF " seconds => %s", initiated_time,
	   os_ctime(&initiated_time, time_buffer, sizeof(time_buffer)));
	   /* Note: os_ctime() adds a newline! */
    Printf("Please Note: The initiated time is when this request was issued.\n");
    return;
}

/*
 * keepalive_alarm() - Format and Display the Keepalive Message.
 *
 * Description:
 *    This function serves multiple purposes:
 *    o monitoring I/O (noprog's)
 *    o process keepalive messages
 *    o terminate when runtime reached
 *
 * Inputs:
 *    sig = The signal number (SIGALRM). (dated, but retained)
 */
void
keepalive_alarm(int sig)
{
    struct dinfo *dip = active_dinfo;
    char buffer[STRING_BUFFER_SIZE];
    register time_t initiated_time;
    register time_t current_time;
    register time_t elapsed = 0;
    int trig_action;

    initiated_time = dip->di_initiated_time;
    current_time = dip->di_last_alarm_time = time((time_t *)0);
    if (initiated_time) {
	elapsed = (current_time - initiated_time);
	/* Sanity Check! */
	if (elapsed < 0) {
	    Fprintf("Warning: The current time has gone backwards, elapsed is %d seconds!\n", elapsed);
	    report_times(initiated_time, current_time);
	    return;
	}
    }

    if (dip->di_tDebugFlag && dip->di_noprog_flag) {
	char *bp = buffer;
	bp += Sprintf(bp, "Timer expired: initiated time " TMF ", current time " TMF,
		      initiated_time, current_time);
	if (initiated_time) {
	    bp += Sprintf(bp, " (elapsed %d secs)\n", elapsed);
	} else {
	    bp += Sprintf(bp, "\n");
	}
	Printf("%s", buffer);
    }

    /*
     * Check for no progress being made?
     */
    if (dip->di_noprog_flag && initiated_time && (elapsed > dip->di_noprogtime) ) {
	char *bp = buffer;
	time_t it = initiated_time;
	char time_buffer[TIME_BUFFER_SIZE];
	char *optmsg = optiming_table[dip->di_optype].opt_name;

	if ( (dip->di_optype == READ_OP)  ||
	     (dip->di_optype == WRITE_OP) ||
	     (dip->di_optype == AIOWAIT_OP) ) {
	    OFF_T offset = (OFF_T)GetStatsValue(dip, ST_OFFSET, FALSE, NULL);
	    u_long records = (u_long)GetStatsValue(dip, ST_RECORDS, TRUE, NULL);
	    u_int32 lba = (dip->di_dsize) ? (u_int32)(offset / dip->di_dsize) : 0;
	    records++; /* Current outstanding record. */
	    if (optmsg) {
		bp += Sprintf(bp, "No progress made for record %u (lba %u, offset " FUF ") during %s() on %s for %d seconds!",
			      records, lba, offset, optmsg, dip->di_dname, elapsed);
	    } else {
		bp += Sprintf(bp, "No progress made for record %u (lba %u, offset " FUF ") on %s for %d seconds!",
			      records, lba, offset, dip->di_dname, elapsed);
	    }
	} else {
	    if (optmsg) {
		bp += Sprintf(bp, "No progress made during %s() on %s for %d seconds!",
			      optmsg, dip->di_dname, elapsed);
	    } else {
		bp += Sprintf(bp, "No progress made on %s for %d seconds!",
			      dip->di_dname, elapsed);
	    }
	}

	if (elapsed > SECS_PER_MIN) {
	    bp += Sprintf(bp, " (");
	    bp = bformat_time(bp, (elapsed * hz));
	    bp += Sprintf(bp, ")");
	}
	/* Note: os_ctime() adds a newline! */
	Printf("%s Since: %s", buffer, os_ctime(&it, time_buffer, sizeof(time_buffer)));

	/*
	 * The user can specify a no-progress trigger time to control when
	 * this gets executed.  This way one can emit no-progress messages to
	 * monitor progress, then execute the trigger at a higher threshold.
	 */
	if (dip->di_noprogttime && (elapsed > dip->di_noprogttime) ) {

	    Printf("This requests' elapsed time of %d, has exceeded the noprogtt of %d seconds!\n", 
		   elapsed, dip->di_noprogttime);

	    report_times(initiated_time, current_time);

	    trig_action = ExecuteTrigger(dip, "noprog");
	    switch ( trig_action ) {
		case TRIGACT_CONTINUE:
		    break;
		case TRIGACT_TERMINATE:
		    ++dip->di_error_count;
		    Printf("Terminating...\n");
		    terminate(exit_status = FAILURE);
		    break;
		case TRIGACT_SLEEP:
		    Printf("Sleeping forever...\n");
		    while (1) {
			SleepSecs(60);
		    }
		    break;
		case TRIGACT_ABORT:
		    ++dip->di_error_count;
		    Printf("Aborting...\n");
		    core_dump = TRUE;
		    terminate(exit_status = FAILURE);
		    break;
		default:
		    Printf("Unknown trigger action %d, continuing...\n", trig_action);
		    /* Per request of SAN Automation, we now exit on unexpected status! */
		    terminate(exit_status = FAILURE);
		    break;
	    }
	}
    }

    /*
     * Allow empty keepalive to monitor I/O progress only.
     */
    if ( dip->di_keepalive && strlen(dip->di_keepalive) &&
	 ((current_time - dip->di_last_keepalive) >= dip->di_keepalive_time) ) {
	dip->di_last_keepalive = current_time;
        if (FmtKeepAlive(dip, dip->di_keepalive, buffer) == SUCCESS) {
	    LogMsg (ofp, logLevelLog, 0, "%s\n", buffer);
	}
    }

    /*
     * If runtime specified, see if we hit our end time.
     */
    if (dip->di_runtime) {
	if (current_time >= dip->di_runtime_end) {
	    if (dip->di_debug_flag || dip->di_tDebugFlag) {
		Printf("The runtime of %d seconds has expired, so exiting...\n", dip->di_runtime);
	    }
	    terminate(sig); /* End of our runtime, exit. */
	}
    }
    return;
}

/*
 * SignalHandler() - Signal handler for all signals we care about.
 *
 * Inputs:
 *	signal_number = The signal number.
 *
 * Return Value:
 *	void
 */
void
SignalHandler(int signal_number)
{
    if (debug_flag || pDebugFlag) {
	Printf("Caught signal %d\n", signal_number);
    }

    if (terminating_flag) {
	/* If already terminating, then exit the process (likly hung)! */
	if (debug_flag || pDebugFlag || tDebugFlag) {
	    Printf("Exiting with signal %d, due to already terminating!\n", signal_number);
	}
	finish_exiting(NULL, signal_number);
    }
    CmdInterruptedFlag = True;
    terminate(signal_number);
}

/*
 * terminate() - Terminate program with specified exit code.
 *
 * Notes:
 *	This needs reworked for multiple threads!
 *	This was originally was written for a single IO process and hacked
 * in some support for multiple threads. This needs rethought and reworked!
 *
 * Inputs:
 *	code = The exit code or signal number if kill done.
 */
void
terminate(int code)
{
    struct dinfo *dip = active_dinfo;
    bool do_cleanup = TRUE;

    if (dip->di_debug_flag || dip->di_pDebugFlag || dip->di_tDebugFlag) {
	Printf("Terminating with code %d...\n", code);
    }

    /*
     * If we enter here more than once, just exit to avoid
     * possible recursion.  kernel should do I/O rundown!
     */
    if (dip->di_terminating || terminating_flag) {
	if (core_dump && (code != SUCCESS)) {
	    if (dip->di_debug_flag || dip->di_pDebugFlag) {
		Printf("Forcing core dump via abort()...\n");
	    }
	    abort();		/* Generate a core dump. */
	} else {
	    /* If already terminating, just exit this thread! */
	    if (dip->di_debug_flag || dip->di_pDebugFlag || dip->di_tDebugFlag) {
		Printf("Exiting with code %d, due to already terminating!\n", code);
	    }
	    /*
	     * We expect some thread to be doing termination processing, so we
	     * do not wish to exit which would kill all threads and keep us from
	     * doing cleanup and displaying total statistics.
	     *
	     * Note: This should be cleaned up with full threading support!
	     */
	    HANDLE_TERMINATE(dip);
	    finish_exiting(dip, code);
	}
    } else {
	dip->di_terminating++; terminating_flag++; /* Show we're terminating. */
    }

    if ( !(dip->di_procs_active && dip->di_child_pid) ) {
	do_cleanup = HandleThreads(dip, code);
    }

    /*
     * If our timer expired, flush any data (if writing files).
     */
    if ( do_cleanup && (code == SIGALRM) && dip && (dip->di_mode == WRITE_MODE) ) {
	/*
	 * We may get alarm while open() is in progress, so handle.
	 */
	if ( !dip->di_closing && !dip->di_flushing && (dip->di_fd != NoFd) ) {
	    (void)(*dip->di_funcs->tf_flush_data)(dip);
	}
    }

    /*
     * If terminating via monitoring thread, use the global exit status. (for now)
     */
    if (code == SIGALRM) {
	code = exit_status;
    }

    /*
     * We only come here for signals when executing multiple
     * processes, so abort active procs and continue waiting.
     */
    if (dip->di_procs_active && dip->di_child_pid) {
	if (kill_delay) {
	    /* 
	     * When running interactively, process group gets signal, so
	     * if we send another signal quickly, children exit immediately
	     * rather than doing their cleanup and reporting statistics.
	     *
	     * Note: This is timing dependent, so need a better method!
	     */
	    SleepSecs(kill_delay);
	}
	abort_procs(dip);		/* Abort any active procs. */
	/*
	 * For Unix, we must return to waiting for processes to reap their
	 * exit status to avoid zombie processes!
	 * For native Windows, this is not required, but it's good practice! 
	 */
	if (dip->di_debug_flag || dip->di_pDebugFlag || dip->di_tDebugFlag) {
	    Printf("Parent returning from signal to wait for children...\n");
	}
	/* Ensure signals are still enabled! (some OS's reset them) */
	(void) signal (SIGTERM, SignalHandler);
	(void) signal (SIGINT, SignalHandler);
	return;
    }
    /* TODO: More tty support? */
#if !defined(WIN32)
    if (dip->di_debug_flag && (code == SIGCHLD)) {
	Printf ("Child process exited prematurely, parent exiting...\n");
    } else 
#endif

#if !defined(WIN32)
    (void) signal (SIGCHLD, SIG_DFL); /* Don't deliver SIGCHLD now. */
#endif

    code = finish_test(dip, code, do_cleanup);

    finish_exiting(dip, code);
    /*NOTREACHED*/
}

void
finish_exiting(dinfo_t *dip, int code)
{
    if (debug_flag || pDebugFlag || tDebugFlag || nate_flag) {
	Printf ("Exiting with status code %d...\n", code);
    }
    if (core_dump && (code != SUCCESS) && (code != END_OF_FILE)) {
	abort(); /* Generate a core dump. */
    }
    /*
     * Map signal numbers and/or other errno's to FAILURE. (cleanup)
     * ( easier for scripts to handle! )
     */
    if ( (code != FAILURE) && (code != SUCCESS) && (code != END_OF_FILE) ) {
	code = FAILURE;			/* Usually a signal number. */
    }
    if (nate_flag) {
	/*
	 * This is one of the NATE log file signatures recognized:
	 *
	 * END OF TEST
	 *     Warning
	 *     Test failure
	 *     Test explicitly passed
	 */
	Printf("END OF TEST\n");
	if ( (code == SUCCESS) || (code == END_OF_FILE) ) {
	    Printf("    Test explicitly passed\n");
	} else if (code == FAILURE) {
	    Printf("    Test failure\n");
	} else {
	    Printf("    Warning\n");
	}
    }
    /* TODO: Do we really need this? Was this for tty support? */
    if (dip &&
	(dip->di_forked_flag && dip->di_term_delay && (dip->di_child_pid == (pid_t) 0)) ) {
	(void)SleepSecs(dip->di_term_delay);	/* Allow parent to wait for us.	*/
    }
    if (dip && dip->di_log_file) {
	/* TODO: This will become thread specific log in the future! */
	(void)fclose(efp);
    }
    exit (code);
}

void
handle_terminating(dinfo_t *dip)
{
    if (debug_flag || tDebugFlag) {
	Printf("Thread %u is exiting...\n", (unsigned int)pthread_self() );
    }
    pthread_exit(dip);
    return;
}

int
nofunc (struct dinfo *dip)
{
	return (SUCCESS);
}

static char *multi_prompt = 
    "\nPlease insert volume #%d in drive %s, press ENTER when ready to proceed: \007";
static char *multi_nready =
    "The drive is NOT ready or encountered an error, Retry operation (Yes): \007";

int
HandleMultiVolume (struct dinfo *dip)
{
    int status;

    status = RequestMultiVolume (dip, FALSE, dip->di_oflags);
    if (status == FAILURE) return (status);

    if (dip->di_mode == READ_MODE) {
	dip->di_volume_bytes = (large_t)(dip->di_dbytes_read + dip->di_total_bytes_read);
	if (dip->di_verbose_flag) {
	  if ( dip->di_multiple_files || (dip->di_dtype->dt_dtype == DT_TAPE) ) {
	    Print ("    [ Continuing in file #%lu, record #%lu, bytes read so far " LUF "... ]\n",
		(dip->di_files_read + 1), (dip->di_records_read + 1), dip->di_volume_bytes);
	  } else {
	    Print ("    [ Continuing at record #%lu, bytes read so far " LUF "... ]\n",
			(dip->di_records_read + 1), dip->di_volume_bytes);
	  }
	}
	dip->di_vbytes_read = (large_t) 0;
    } else {
	dip->di_volume_bytes = (large_t)(dip->di_dbytes_written + dip->di_total_bytes_written);
	if (dip->di_verbose_flag) {
	  if ( dip->di_multiple_files || dip->di_dtype->dt_dtype == DT_TAPE) {
	    Print ("    [ Continuing in file #%lu, record #%lu, bytes written so far " LUF "... ]\n",
		(dip->di_files_written + 1), (dip->di_records_written + 1), dip->di_volume_bytes);
	  } else {
	    Print ("    [ Continuing at record #%lu, bytes written so far " LUF "... ]\n",
			(dip->di_records_written + 1), dip->di_volume_bytes);
	  }
	}
	dip->di_vbytes_written = (large_t) 0;
    }
    (void)fflush(ofp);
    dip->di_media_changed = TRUE;
    dip->di_volume_records = 0;
    if (exit_status == END_OF_FILE) {
	exit_status = SUCCESS;		/* Ensure END_OF_FILE status is reset! */
    }
    return (status);
}

int
RequestFirstVolume (struct dinfo *dip, int oflags)
{
    int status;

    dip->di_multi_volume = 0;

    status = RequestMultiVolume (dip, TRUE, oflags);

    dip->di_volume_bytes = (large_t) 0;
    dip->di_volume_records = 0;

    return (status);
}

int
RequestMultiVolume (struct dinfo *dip, bool reopen, int oflags)
{
    struct dtfuncs *dtf = dip->di_funcs;
    char buffer[256];
    char *bp = buffer;
    FILE *fp;
    int saved_exit_status;
    u_long saved_error_count;
    int status;

    if (terminating_flag) return (FAILURE);

    if ( (status = (*dtf->tf_close)(dip)) == FAILURE) {
	return (status);
    }

    if ( (fp = fopen("/dev/tty", "r+")) == NULL) {
	report_error(dip, "open of /dev/tty failed", FALSE);
	return (FAILURE);
    }
    dip->di_multi_volume++;

    (void)sprintf(bp, multi_prompt, dip->di_multi_volume, dip->di_dname);

    (void) fputs (bp, fp); fflush(fp);
    if (fgets (bp, sizeof(buffer), fp) == NULL) {
	Print ("\n");
	status = FAILURE;	/* eof or an error */
	return (status);
    }

    saved_error_count = dip->di_error_count;
    saved_exit_status = exit_status;

    /*
     * This is an important step, so allow the user to retry on errors.
     */
    do {
	if (!reopen) {
	    status = (*dtf->tf_open)(dip, oflags);
	} else {
	    status = (*dtf->tf_reopen_file)(dip, oflags);
	}
	if (status == SUCCESS) {
#if defined(TAPE) && !defined(__NUTC__) && !defined(__QNXNTO__) && !defined(AIX) && !defined(WIN32)
	    if (dip->di_dtype->dt_dtype == DT_TAPE) {
		status = DoRewindTape (dip);
		if (status == FAILURE) {
		    (void)(*dtf->tf_close)(dip);
		}
	    }
#endif /* defined(TAPE) && !defined(__NUTC__) && !defined(__QNX_NTO__) && !defined(AIX) && !defined(WIN32) */
	}
	if (status == FAILURE) {
	    (void) fputs (multi_nready, fp); fflush(fp);
	    if (fgets (bp, sizeof(buffer), fp) == NULL) {
		Print ("\n");
		break;
	    }
	    if ( (bp[0] == 'N') || (bp[0] == 'n') ) {
		break;
	    }
	    dip->di_error_count = saved_error_count;
	    exit_status = saved_exit_status;
	} else {
	    break;		/* device is ready! */
	}
    } while (status == FAILURE);

    (void)fclose(fp);
    return (status);
}

/*
 * do_monitoring() - Monitoring Thread.
 *
 * Description:
 *      This thread is used to implement SIGALRM usually done via alarm()
 * but is necessary to avoid the issue where signals are blocked on some
 * OS's while doing I/O (Linux, HP-UX, Solaris, etc).
 *
 * Inputs:
 *	arg = Pointer to monitoring interval.
 *
 * Return Value:
 *	NULL pointer.
 */
void *
do_monitoring(void *arg)
{
    unsigned int *interval = (unsigned int *)arg;

    ignore_signals();
#if defined(WIN32)
    MonitorThreadId = pthread_self();
#endif
    if (debug_flag || tDebugFlag) {
	Printf("Monitor Thread ID is %u\n", MonitorThreadId);
    }

    /*
     * Basically wait for the monitor interval, and allow the standard
     * keepalive() handling to process noprog, keepalive, & runtime.
     */
    while (1) {
        SleepSecs(*interval);
	//(void)os_msleep(1); /* For DEBUG! Try to hit time race conditions! */
	HANDLE_TERMINATE(NULL);
	(void)keepalive_alarm(SIGALRM);
	HANDLE_TERMINATE(NULL);
    }
    pthread_exit(NULL);
    return(NULL);
}

/*
 * WTF! Linux stack size is 10MB by default! (will get cleaned up one day)
 */
#define THREAD_STACK_ENV "DT_THREAD_STACK_SIZE" /* Thread stack size.	*/
#if !defined(PTHREAD_STACK_MIN)
#  define PTHREAD_STACK_MIN 16384
#endif
/* Note: If the stack size is too small we seg fault, too large wastes address space! */
//#define THREAD_STACK_SIZE	((PTHREAD_STACK_MIN + STRING_BUFFER_SIZE) * 4)
//				/* Reduce TLS to avoid wasting swap/memory! */
#define THREAD_STACK_SIZE	MBYTE_SIZE	/* Same default as Windows! */

int
init_pthread_attributes(dinfo_t *dip)
{
    size_t currentStackSize = 0;
    size_t desiredStackSize = THREAD_STACK_SIZE;
    int status;
    char *p, *string;

    if (p = getenv(THREAD_STACK_ENV)) {
	string = p;
	desiredStackSize = number(dip, string, ANY_RADIX, &status, ANY_RADIX);
    }
    ParentThreadId = pthread_self();
    /* Remember: pthread API's return 0 for success; otherwise, an error number to indicate the error! */
    status = pthread_attr_init(tattrp);
    if (status != SUCCESS) {
	tPerror(status, "pthread_attr_init() failed");
	return (status);
    }
#if !defined(WIN32)
    status = pthread_attr_setscope(tattrp, PTHREAD_SCOPE_SYSTEM);
    if ( (status != SUCCESS) && (status != ENOTSUP) ) {
	tPerror(status, "pthread_attr_setscope() failed setting PTHREAD_SCOPE_SYSTEM");
	/* This is considered non-fatal! */
    }

    /*
     * Verify the thread stack size (TLS) is NOT too large! (Linux issue). 
     * Yea, only one thread right now, but I'm preparing for the future. :-)
     */
    status = pthread_attr_getstacksize(tattrp, &currentStackSize);
    if (status == SUCCESS) {
	if (dip->di_debug_flag || dip->di_tDebugFlag) {
	    Printf("Current thread stack size is %u (%.3f Kbytes)\n",
		   currentStackSize, ((float)currentStackSize / (float)KBYTE_SIZE));
	}
    } else {
	if (dip->di_debug_flag || dip->di_tDebugFlag) {
	    tPerror(status, "pthread_attr_getstacksize() failed!");
	}
    }

    /*
     * The default stack size on Linux is 10M, which limits the threads created! 
     */
    if (currentStackSize && desiredStackSize && (currentStackSize > desiredStackSize) ) {
	/* Too small and we seg fault, too large limits our threads. */
	status = pthread_attr_setstacksize(tattrp, desiredStackSize);
	if (status == SUCCESS) {
	    if (dip->di_debug_flag || dip->di_tDebugFlag) {
		Printf("Thread stack size set to %u bytes (%.3f Kbytes)\n",
		       desiredStackSize, ((float)desiredStackSize / (float)KBYTE_SIZE));
	    }
	} else {
	    tPerror(status, "pthread_attr_setstacksize() failed setting stack size %u",
		   desiredStackSize);
	}
    }
#endif /* !defined(WIN32) */
    return (status);
}

int
StartMonitorThread(dinfo_t *dip, int interval)
{
    static int monitorInterval;
    int status;

    monitorInterval = interval;
    status = pthread_create( &MonitorThread, tattrp, do_monitoring, &monitorInterval );
    if (status != SUCCESS) {
        tPerror (status, "pthread_create() failed");
        return (status);
    }
    return (status);
}

#if !defined(WIN32)

# if defined(DEBUG)

char *
decodeCancelType(int cancel_type)
{
    switch (cancel_type) {
	case PTHREAD_CANCEL_ASYNCHRONOUS:
	    return ("PTHREAD_CANCEL_ASYNCHRONOUS");
	    break;
	case PTHREAD_CANCEL_DEFERRED:
	    return ("PTHREAD_CANCEL_DEFERRED");
	    break;
	default:
	    return ("cancel type unknown");
	    break;
    }
}
# endif /* defined(DEBUG) */

int
SetThreadCancelType(dinfo_t *dip, int cancel_type)
{
    int status;
    int old_cancel_type = 0;

# if defined(DEBUG)
    if (dip->di_tDebugFlag) {
	Printf("Setting the thread cancel type to %s...\n", decodeCancelType(cancel_type));
    }
    if ( (status = pthread_setcanceltype(cancel_type, &old_cancel_type)) == SUCCESS) {
	if (dip->di_tDebugFlag) {
	    Printf("Previous cancel type is %d (%s)\n",
		  old_cancel_type, decodeCancelType(old_cancel_type));
	}
    } else {
	tPerror(status, "pthread_setcanceltype() failed");
    }
# else /* !defined(DEBUG) */
    if ( (status = pthread_setcanceltype(cancel_type, &old_cancel_type)) != SUCCESS) {
	tPerror(status, "pthread_setcanceltype() failed");
    }
# endif /* defined(DEBUG) */
    return (status);
}

#endif /* !defined(WIN32) */

int
HandleThreads(dinfo_t *dip, int code)
{
    hbool_t do_cleanup = True;
#if defined(WIN32)
    DWORD waitResult;
#endif

    if (dip->di_debug_flag || dip->di_tDebugFlag) {
	if (ParentThreadId)  Printf("     Parent thread ID: %u\n", ParentThreadId);
	if (IO_ThreadId)     Printf("    The I/O thread ID: %u\n", IO_ThreadId);
	if (iotuneThreadId)  Printf(" I/O Tuning thread ID: %u\n", iotuneThreadId);
	if (MonitorThreadId) Printf("The Monitor thread ID: %u\n", MonitorThreadId);
    }

#if defined(WIN32)
    /*
     * Note: We don't actually cancel on Windows... NOT Safe! :-(
     */
    waitResult = WaitForSingleObject(exitMutex, INFINITE);
    if (waitResult != WAIT_OBJECT_0) {
	Fprintf("WaitForSingleObject() returned %d\n", waitResult);
    }
    /*
     * We wait for the IO thread, so we know if we can close handles, etc.
     *
     * Note: This logic assumes the parent thread will terminate when all
     *	     I/O threads exit (only one IO thread at present).
     *       This synchronization is kinda Micky Mouse (IMO).
     */
    if ( ParentThreadId != GetCurrentThreadId() ) {
	DWORD status;
	DWORD timeoutMs;
	int wait_retries = 0;

	/*
	 * SIGALRM means we've completed our runtime, so wait longer
	 * than if we're terminating due to another signal or exiting
	 * due to the trigger script (which now uses FAILURE).
	 */
	if (term_wait_retries == 0) { /* May get set by option. */
	    if (code == SIGALRM) {
		term_wait_retries = TERM_WAIT_RETRIES;
	    } else {
		term_wait_retries = TERM_WAIT_ARETRIES;
	    }
	}
	if (term_wait_timeout == 0) { /* May get set by option. */
	    term_wait_timeout = TERM_WAIT_TIMEOUT;
	}
	timeoutMs = (1000 * TERM_WAIT_TIMEOUT);
	/*
	 * Give the I/O thread time to exit, which may take a while
	 * if the file is being flushed or there's heavy I/O load.
	 * Note: The I/O loops are now checking for terminating!
	 */
	do {
	    wait_retries++;
	    if (dip->di_debug_flag) {
		Printf("Waiting for Parent thread to exit, retry %d...\n", wait_retries);
	    }
	    status = WaitForSingleObject(ParentThread, timeoutMs);
	    if (wait_retries >= term_wait_retries) break;
	} while (status == WAIT_TIMEOUT);
	/*
	 * If the thread did NOT exit cleanly, don't do file operations!
	 */
	if (status != WAIT_OBJECT_0) {
	    Printf("Parent thread ID: %u is still active, exiting anyways...\n", ParentThreadId);
	    do_cleanup = FALSE;
	    /* Terminating threads is MT libc is very dangerous! */
	}
    }
#else /* !defined(WIN32) */
    /*
     * If this is the parent, we assume all IO is complete!
     */
    if ( ParentThread != pthread_self() ) {
	/* We set the terminating flag, give threads chance to exit! */
	if (cancel_delay) SleepSecs(cancel_delay);
    }
    (void)SetThreadCancelType(dip, PTHREAD_CANCEL_ASYNCHRONOUS);
    if (iotuneThread) {
	/* Parent Thread Processing */
	if (dip->di_debug_flag || dip->di_tDebugFlag) {
	    Printf("Canceling I/O Tuning thread ID: %u...\n", iotuneThread);
	}
	if (pthread_cancel(iotuneThread) == FAILURE) {
	    Perror("pthread_cancel() on I/O Tuning ID %u failed!\n", iotuneThread);
	}
	iotuneThread = (pthread_t) 0;
    }
    /*
     * We can get here via parent thread, or monitoring thread, or from the
     * signal handler (expect this to be the parents' context).
     *
     * Note: This is messy, so we may wish to rethink this cancelling!
     */
    if ( ( ParentThread == pthread_self() ) ||
	 ( IO_Thread == pthread_self()    ) ) {
	if (MonitorThread) {
	    /* Parent Thread Processing */
	    if (dip->di_debug_flag || dip->di_tDebugFlag) {
		Printf("Canceling the Monitor thread ID: %u...\n", MonitorThread);
	    }
	    if (pthread_cancel(MonitorThread) == FAILURE) {
		Perror("pthread_cancel() on Monitor thread ID %u failed!\n", MonitorThread);
	    }
	    MonitorThread = (pthread_t) 0;
	}
	/*
	 * If we came in via a signal, we still need to cancel the IO thread.
	 */
	if (ParentThread == pthread_self() ) {
	    if (IO_Thread) {
		if (dip->di_debug_flag || dip->di_tDebugFlag) {
		    Printf("Canceling the I/O thread ID: %u...\n", IO_Thread);
		}
		if (pthread_cancel(IO_Thread) == FAILURE) {
		    Perror("pthread_cancel() on parent thread ID %u failed!\n", IO_Thread);
		}
		IO_Thread = (pthread_t) 0;
	    }
	}
    } else {
	/* Monitor Thread Processing */
	if (dip->di_debug_flag || dip->di_tDebugFlag) {
	    Printf("Canceling the parent thread ID: %u...\n", ParentThreadId);
	}
	if (pthread_cancel(ParentThreadId) == FAILURE) {
	    Perror("pthread_cancel() on parent thread ID %u failed!\n", ParentThreadId);
	}
	/*
	 * IO has been moved to a separate thread, but only one IO thread (at present).
	 */ 
	if (IO_Thread) {
	    if (dip->di_debug_flag || dip->di_tDebugFlag) {
		Printf("Canceling the I/O thread ID %u...\n", IO_Thread);
	    }
	    if (pthread_cancel(IO_Thread) == FAILURE) {
		Perror("pthread_cancel() on parent thread ID %u failed!\n", IO_Thread);
	    }
	    IO_Thread = (pthread_t) 0;
	}
	//if (cancel_delay) {
	//    SleepSecs(cancel_delay);/* Give the thread a chance to actually cancel... */
	//			    /* Note: This delay will affect throughput stats! */
	//}
    }
#endif /* defined(WIN32) */
    return (do_cleanup);
}

/*
 * init_device_information() - Initialize The Device Information Structure.
 *
 * Return Value:
 *      Returns a pointer to the device information data structure.
 */
static dinfo_t *
init_device_information(void)
{
    int i;
    dinfo_t *dip;
    dip = (struct dinfo *)Malloc(sizeof(*dip));
    
    /* Setup Defaults */
    
    dip->di_stdin_flag = FALSE;
    dip->di_stdout_flag = FALSE;
    
    /* Note: These will become unique per thread w/log option! */
    dip->di_efp = efp = stderr;
    dip->di_ofp = ofp = stdout;
    dip->di_msg_buffer = (char *)Malloc(LOG_BUFSIZE);
    
    dip->di_fd = NoFd;
    dip->di_block_size = BLOCK_SIZE;
    dip->di_data_limit = INFINITY;		/* Set to maximum limit. */

    dip->di_compare_flag = DEFAULT_COMPARE_FLAG;
    dip->di_lbdata_flag = DEFAULT_LBDATA_FLAG;
    dip->di_timestamp_flag = DEFAULT_TIMESTAMP_FLAG;
    dip->di_user_pattern = DEFAULT_USER_PATTERN;
#if defined(SCSI)
    dip->di_scsi_flag = DEFAULT_SCSI_FLAG;
    dip->di_scsi_errors = DEFAULT_SCSI_ERRORS;
    dip->di_idt = IDT_BOTHIDS;
#endif /* defined(SCSI) */
    dip->di_verbose_flag = DEFAULT_VERBOSE_FLAG;
    dip->di_verify_flag = DEFAULT_VERIFY_FLAG;
    dip->di_unique_pattern = DEFAULT_UNIQUE_PATTERN;
    dip->di_error_limit = DEFAULT_ERROR_LIMIT;
    dip->di_file_limit = DEFAULT_FILE_LIMIT;
    dip->di_pass_limit = DEFAULT_PASS_LIMIT;

    dip->di_iot_pattern = FALSE;
    dip->di_iot_seed = IOT_SEED;
    dip->di_pattern = DEFAULT_PATTERN;

#if defined(AIO)
    /* Asynchronous I/O */
    dip->di_aio_bufs = AIO_BUFS;
#endif /* !defined(AIO) */
    dip->di_aio_flag = FALSE;
    dip->di_align_offset = 0;
    
    dip->di_dumpall_flag = FALSE;
    dip->di_max_bad_blocks = MAXBADBLOCKS;
    dip->di_boff_format = HEX_FMT;
    dip->di_data_format = NONE_FMT;
    dip->di_bufmode_index = 0;
    dip->di_bufmode_count = 0;
    
    dip->di_dump_limit = DEFAULT_DUMP_LIMIT;
    dip->di_bypass_flag = FALSE;
    dip->di_cerrors_flag = TRUE;
    dip->di_child_flag = FALSE;
    dip->di_debug_flag = FALSE;
    dip->di_Debug_flag = FALSE;
    dip->di_eDebugFlag = FALSE;
    dip->di_fDebugFlag = FALSE;
    dip->di_pDebugFlag = FALSE;
    dip->di_rDebugFlag = FALSE;
    dip->di_sDebugFlag = FALSE;
    dip->di_tDebugFlag = FALSE;
    dip->di_delete_per_pass = FALSE;
    dip->di_dio_flag = FALSE;
    /* File system caching is enabled by default, these control each. */
    dip->di_read_cache_flag = TRUE;
    dip->di_write_cache_flag = TRUE;
    dip->di_dump_flag = TRUE;
    dip->di_forked_flag = FALSE;
    dip->di_fsincr_flag = FALSE;
    dip->di_fsync_flag = UNINITIALIZED;
    dip->di_fsync_frequency = 0;
    dip->di_fsalign_flag = FALSE;
    dip->di_multiple_dirs = FALSE;
    dip->di_multiple_files = FALSE;
    dip->di_keep_existing = TRUE;
    dip->di_header_flag = TRUE;
    dip->di_history_size = 0;
    dip->di_history_dump = FALSE;
    dip->di_history_timing = FALSE;
    dip->di_history_data_size = DEFAULT_HISTORY_DATA_SIZE;
    dip->di_mount_lookup = DEFAULT_MOUNT_LOOKUP;
    dip->di_noprog_flag = FALSE;
    dip->di_prefill_flag = TRUE;
    dip->di_unique_log = FALSE;
    dip->di_unique_file = FALSE;
    dip->di_user_incr = FALSE;
    dip->di_user_min = FALSE;
    dip->di_user_max = FALSE;
    dip->di_user_ralign = FALSE;
    dip->di_user_rseed = FALSE;
    dip->di_user_lbdata = FALSE;
    dip->di_user_lbsize = FALSE;
    dip->di_user_position = FALSE;
    dip->di_incr_pattern = FALSE;
    dip->di_logappend_flag = TRUE;
    dip->di_logdiag_flag = FALSE;
    dip->di_logpid_flag = FALSE;
    dip->di_syslog_flag = FALSE;
    dip->di_loop_on_error = FALSE;
    dip->di_micro_flag = FALSE;
    dip->di_mmap_flag = FALSE;
    dip->di_media_changed = FALSE;
    /* This are user specified open flags! */
    dip->di_open_flags = 0;
    dip->di_wopen_flags = 0;
#if defined(WIN32)
    dip->di_ropen_mode = GENERIC_READ;
    dip->di_wopen_mode = GENERIC_WRITE;
    dip->di_rwopen_mode = (GENERIC_READ | GENERIC_WRITE);
#else /* !defined(WIN32) */
    dip->di_ropen_mode = O_RDONLY;
    dip->di_wopen_mode = O_WRONLY;
    dip->di_rwopen_mode = O_RDWR;
#endif /* defined(WIN32) */
    dip->di_pad_check = TRUE;
    dip->di_spad_check = FALSE;
    dip->di_pstats_flag = TRUE;
    dip->di_raw_flag = FALSE;
    dip->di_reread_flag = FALSE;
    dip->di_rotate_flag = FALSE;
    dip->di_rotate_offset = 0;
    dip->di_prealloc_flag = TRUE;
    dip->di_sparse_flag = TRUE;
    dip->di_stats_flag = TRUE;
    dip->di_dirprefix = DIR_PREFIX;
#if defined(HP_UX)
    dip->di_qdepth = 0xFFFFFFFF;
#endif
    dip->di_random_seed = 0;
    dip->di_retry_delay = RETRY_DELAY;
    dip->di_retry_limit = RETRY_LIMIT;
    dip->di_open_delay = DEFAULT_OPEN_DELAY;
    dip->di_close_delay = DEFAULT_CLOSE_DELAY;
    dip->di_read_delay = DEFAULT_READ_DELAY;
    dip->di_write_delay = DEFAULT_WRITE_DELAY;
    dip->di_start_delay = DEFAULT_START_DELAY;
    dip->di_end_delay = DEFAULT_END_DELAY;
    dip->di_term_delay = DEFAULT_TERM_DELAY;
    dip->di_retryDC_flag = TRUE;
    dip->di_max_capacity = FALSE;
    dip->di_variable_flag = FALSE;
    
    dip->di_multi_flag = FALSE;
    dip->di_multi_volume = 1;
    dip->di_volumes_flag = FALSE;
    dip->di_volume_limit = 0;
    dip->di_volume_records = 1;
    
    dip->di_io_dir  = FORWARD;
    dip->di_io_mode = TEST_MODE;
    dip->di_io_type = SEQUENTIAL_IO;
    dip->di_dispose_mode = DELETE_FILE;
    dip->di_oncerr_action = CONTINUE;
    dip->di_stats_level = STATS_FULL;
    
    dip->di_trigargs_flag = TRUE;	/* Note: This should go away! */
    dip->di_num_triggers = 0;
    for (i = 0; (i < NUM_TRIGGERS); i++) {
	dip->di_triggers[i].td_trigger = TRIGGER_NONE;
	dip->di_triggers[i].td_trigger_cmd = NULL;
	dip->di_triggers[i].td_trigger_args = NULL;
    }
    return (dip);
}
