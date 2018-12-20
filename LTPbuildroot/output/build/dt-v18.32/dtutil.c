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
 * Module:	dtutil.c
 * Author:	Robin T. Miller
 *
 * Description:
 *	Utility routines for generic data test program.
 */
#include "dt.h"
#include <ctype.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <sys/stat.h>

#if defined(WIN32)
#  include "dtwin.h"
#else /* !defined(WIN32) */
#  include <pthread.h>
#  include <poll.h>
#  include <signal.h>
#  include <strings.h>
#  include <sys/param.h>
#  include <netdb.h>		/* for MAXHOSTNAMELEN */
#  include <sys/time.h>		/* for gettimeofday() */
#  include <sys/wait.h>
#endif /* defined(WIN32) */

#if defined(sun)
#  define strtoul	strtol
#endif /* defined(sun) */

/*
 * Modification History:
 *
 * April 26th, 2013 by Robin T. Miller
 * 	Multiple problems when comparing IOT data with non-block sized data, plus
 * the init_buffer() function was using the wrong pattern when init'ing the buffer
 * (was using dip->di_pattern instead of the parameter passed in, mostly Ok, except
 *  when init'ing the end of buffers with ~0, then wrong but nobody noticed!).
 * So, when doing file system testing, and an non-block sizes step option (1m-1),
 * then we get odd sized IOT data to verify on short writes due to file system full.
 * This is now handled, by init'ing any residual IOT bytes with the partial IOT pattern,
 * rather that init'ing with ~0). Note: This is never hit with block aligned IOT data.
 * 
 * November 28th, 2012 by Robin T. Miller
 * 	Fix a bug in init_swapped() used for big-endian machines for swapping the
 * IOT pattern to little-endian. The bug resulted in zero data instead of IOT data.
 * 
 * October 21st, 2012 by Robin T. Miller
 *	In verify_reread(), invoked to re-read after a data corruption, on Linux
 * ensure the Direct I/O (DIO) flag is used with disk devices to bypass buffer cache.
 * Failure to use DIO when original read *was* with DIO, results in another (false)
 * corruption, since the data in the cuffer cache may be stale and incorrect! :-(
 * FWIW: This lack of a raw (character) device interface creates more problem than not!
 *
 * October 15th, 2012 by Robin T. Miller
 *	Fix long standing bug in do_random() where if the blocks size macthes the
 * random data limit, we'd loop infinitely while trying to adjust the offset value.
 * Nobody every reported this issue, but Robin has hit it several times in test. :-)
 *
 * September 8th, 2012 by Robin T. Miller
 *`	When formatting keepalive statistics, consider Copy mode.
 *
 * August 11th, 2012 by Robin T. Miller
 *	Removed _BSD conditionalization (only POSIX now!).
 *	Switched from Scu to SCSI library for triggers.
 *
 * July 27th, 2012 by Robin T. Miller
 * 	For 64-bit compiles, don't assume time_t is 32 bits when enabling
 * timestamps, which overwrite a 32-bit LBA. This leads to false corruptions!
 * 
 * July 19th, 2012 by Robin T. Miller
 * 	Add is_retryable() to check for user defined retryable error codes.
 *
 * May 9th, 2012 by Robin T. Miller
 * 	On Windows, changes GetComputerName() to GetComputerNameEx() to
 * avoid having the computer name truncated to 15 characters!
 * 
 * May 3rd, 2012 by Robin T. MIller
 *	When showing position, display the file name useful for copy mode.
 *
 * April 18th, 2012 by Robin T. Miller
 *	Updated trigger script offset, to use AIO offset (when enabled).
 * 
 * January 5th, 2012, by Robin T. Miller
 *	Updated set_position()/seek_position() function since their use of
 * va_arg() was broken, and the setting of expect_error was incorrect on some
 * OS's, which caused seek failures to *not* be reported.
 *
 * August 18th, 2011 by Robin T. Miller
 *	Actually, disable this busywait method altogether! (bad practice)
 * 	Update mySleep() to only do busywait for usecs < usec per msec,
 * otherwise we are eating too much CPU (my bad).
 * 
 * August 14th, 2011 by Robin T. Miller
 * 	Added %lba and %offset keywords to keepalive format sequences, so
 * the logical block address and/or file offset can be reported.
 * 
 * June 1st, 2011 by Robin T. Miller
 * 	On Windows, change strtoul() to _strtoui64() for 64-bit values.
 * 
 * April 23rd, 2011 by Robin T. Miller
 * 	Updated display_iot_block() to skip comparing timestamp bytes, so the
 * timestamp won't inadvertantly make a line look incorrect with '*' when all
 * blocks (good and bad) are being displayed.
 *	When displaying the IOT seeds, also report the pass the seed is for.
 *	Always report "bad data" if the IOT seed was calculated within a block,
 * rather than at the beginning of the block from correect data. This prevents
 * "stale data" display, which may or may not be true (was misleading to me).
 *
 * April 18th, 2011 by Robin T. Miller
 * 	Analyze additional IOT data: when start of block is corrupted, search
 * the remaining data to find a valid IOT seed, then calculate the block number.
 * Compare each blocks' prefix string, and report expected and received prefix.
 * Report the timestamp value to its' easily identifiable in the data displayed.
 *
 * March 24th, 2011 by Robin T. Miller
 * 	Updated LogMsg()/fmtmsg_prefix() to display "ERROR: " for messages
 * logged with logLevelCrit or logLevelError, to make errors more apparent.
 * 
 * March 23rd, 2011 by Robin T. Miller
 * 	Modified dump_buffer() to display the address and the offset, and ensure
 * the corruption offset matches the base offset, since just has lead to confusion.
 * 
 * March 14th, 2011 by Robin T. Miller
 * 	Updated set_position() and seek_position() function to access an option
 * argument to specify an expect error argument. That way, the caller can handle
 * the seek error, such as FindCapacity(). Linux returns EINVAL on invalid offsets.
 * 
 * February 3rd, 2011 by Robin T. Miller
 *	Don't execute the trigger, this is a miscompare on a read retry.
 *
 * January 30th, 2011 by Robin T. Miller
 *	Take timestamp into account during corruption analysis summary/display.
 *
 * January 27th, 2011 by Robin T. Miller
 *	Properly detect and report stale/wrong IOT data during corruption analysis.
 *
 * November 15th, 2010 by Robin T. Miller
 *	On end of file/media conditions, report the bytes read/written.
 *	When reporting re-read command line, add dsize= option if specified.
 *
 * November 12th, 2010 by Robin T. Miller
 *	Fixed bug in isFsFullOk(), where the "no space" flag was *not* set
 * correctly, when the file number was zero! This caused a false data corruption,
 * since setting the "no space" flag is required to break out of the file loop,
 * and retain bytes written state for the read pass.
 *
 * October 30th, 2009 by Robin T. Miller
 *	Honor dump_limit when displayng IOT data blocks (usually 512 bytes).
 *	When dumping IOT data with a prefix, display the ASCII prefix too.
 *	Add logic to determine if received IOT data is from a previous pass.
 *
 * October 5th, 2010 by Robin T. Miller
 * 	Modify init_iotdata() to pack prefix string into the specified buffer.
 * This is either the data buffer during writes, or the pattern buffer during
 * reads. This provides several things: allows memcmp() of expected/received
 * data, and allows us to corruption analysis summary, and prepares us for the
 * side by side comparision during data corruptions.
 * 
 * September 2nd, 2010 by Robin T. Miller
 * 	Added start of corruption analysis for IOT data pattern only.
 * 
 * June 2nd, 2010 by Robin T. Miller
 * 	Only enable Direct I/O for re-reads on regular files, otherwise
 * a false error may be reported for raw (character) disks, like Solaris.
 * 
 * December 1st, 2009 by Robin T. Miller
 *	Added support for removing multiple directories and files.
 *
 * November 25th, 2009 by Robin T. Miller
 *	Added remove_directory() to remove dt created directory.
 *
 * November 21st, 2009 by Robin T. Miller.
 *	Added delete_files() for support of mutliple disk files.
 *	Updated dump_buffer() to display ASCII (if printable) to the right
 * of the hex bytes. This helps with debug when prefix strings are used.
 *	On Linux, disable direct I/O flag in verify_reread() when the request
 * count is NOT modulo the block size, required for DIO (too bad). This avoids
 * an EINVAL error: dt: 'read', errno = 22 - Invalid argument
 *	In verify_data(), do NOT return status from verify_reread() since the
 * caller incorrectly assume success, just because the reread data matches!
 * We want to return the original verify status, not the reread verify status.
 *	Gee, the more fault injections I do, the more bugs I'm finding! :-(
 *
 * September 1st, 2009 by Robin T. Miller.
 *	Optimize compare logic in verify_data_with_lba() for IOT pattern, by
 * using memcmp() first, then if there's a miscompare, use the previous logic.
 * This reduces the CPU overhead by 40-50% the current logic. But that said,
 * using a prefix= string drives the CPU back up due to how data is packed.
 * Note: This high CPU usage is causing Veritas to take resources offline,
 * since other processes cannot run frequently enough. Using 'nice' may help!
 *
 * March 31st, 2009 by Robin T. Miller.
 *      In is_Eof(), if the exit_status is set to FAILURE, do NOT overwrite
 * it with the END_OF_FILE (254) status.  This can occur with AIO, where an
 * I/O fails, but a subsequent I/O encounters EOF (AIX team hit corner case!).
 *
 * February 5th, 2009 by Robin T, Miller.
 *	Cleaned up is_Eof() and report information message when we are
 * reporting an error due to EOF and no data was transferred.
 *
 * February 4th, 2009 by Robin T. Miller.
 *	In preparation for testing volumes with quotas enabled, added
 * check for EDQUOT (disk quota exceeded), to treat like ENOSPC.
 *
 * October 27th, 2008 by Robin T. Miller.
 *	In verify_reread(), disable aio_flag for native Windows to avoid
 * overlapped attribute during file open. as this will cause an error
 * during the reread when AIO is enabled.
 * Actual error is: 'ReadFile', errno = 87 - The parameter is incorrect.
 *	Fix bug in FmtPrefix() where the prefix was rounded up for random
 * I/O, but not for sequential I/O.  Ordinarily, this is Ok, unless one
 * pass is created with sequential, then reread using random I/O, then
 * the prefix strings will not match! (my bad... roundup for both now)
 *
 * October 21th, 2008 by Robin T. Miller.
 *	Updated mySleep() to ensure microsecond to millisecond conversion
 * does not result in 0 (or no delay).  See notes in this function.
 *
 * October 5th, 2008 by Robin T. Miller.
 *	When executing the trigger command, use popen() so output can
 * we read and written to the log file, rather than letting it go to
 * stardard output/error.  This is very important with multiple procs
 * each writing to their own log file.
 *
 * October 3rd, 2008 by Robin T. Miller.
 *	Update Fprintf() and Printf() functions to buffer output, to
 * avoid garbled/intermixed output with multiple processes.
 *
 * September 30th, 2008 by Robin T. Miller
 *	In delete_file(), switch to native Windows DeleteFile() API,
 * rather than using unlink() POSIX API. (moving more towards native)
 *
 * July 23rd, 2008 by Robin T. Miller.
 * 	Added support for saving and restoring history data. The history
 * data is dumped in RecordError(), a common error reporting function.
 *	Fix bug in ReportDeviceInfo() with AIO, as the file offset was
 * getting set incorrectly in the non-EIO case (data corruption occurred).
 * The gotcha caused the verify_reread() to fail with a bad lseek offset.
 * When dumping miscompared data, display the buffer offset instead of the
 * buffer address, which is more useful and be less confusing (I think).
 *
 * June 16th, 2008 by Robin T. Miller.
 *	Added reread logic to help troubleshoot data corruptions.
 *	For Unix, block SIGALRM in mySleep() to avoid premature wakeup.
 *	Added Perror() function to log errors with format string.
 *	Updated verify_prefix() to report the correct relative block
 * and offset during prefix string miscompares (incorrect so misleading).
 *	Added support for Windows event logging with syslog option.
 *
 * May 9th, 2008 by Robin T. Miller.
 *	Fix issue in init_iotdata() where too many IOT pattern bytes were
 * being generated when the prefix string was an odd length. This would
 * cause false data comparisons if we encountered short reads, but in
 * general the IOT data pattern was NOT packed properly.
 * Note: This is messy and overly complicated, and needs a re-write!
 *
 * April 29th, 2008 by Robin T. Miller.
 *	Updated verify_data_prefix() to account for timestamp when
 * enable=timestamp option is enabled, otherwise a false data corruption
 * is reported on the first read! (my bad, missed this verify function)
 * Also added tracking the timestamp position, rather than always reporting
 * the first timestamp in this record.
 *
 * February 12th, 2008 by Robin Miller.
 *	Added workaround for broken strtoul() on Solaris 8!
 *
 * December 13th, 2007 by Robin T. Miller
 *	Add support for logging errors to syslog on Unix based systems.
 *
 * November 27th, 2007 by Robin T. Miller.
 *	In mySleep(), switch to using poll()'s timeout for delays, instead of
 * sleep()/usleep() to avoid SIGALRM conflict which breaks our runtime option.
 *
 * November 19th, 2007 by Robin T. Miller.
 *	Parse trigger cmd:string, and if extra arguments were specified,
 * parse appropriately and set a pointer to the extra args.  These extra
 * args get appended to dt's normal arguments when executing the script.
 *
 * October 29th, 2007 by Robin T. Miller.
 *	Remove unnecessary native windows compilation in format_time(), now
 * that times() macro updated to return clock ticks Unix method will work.
 *
 * October 27th, 2007 by Robin T. Miller.
 *	Add check for ERROR_SECTOR_NOT_FOUND when checking for end of file
 * on native Windows.  This seems like a strange error to me, correct?
 *
 * October 24th, 2007 by Robin T. Miller.
 *	For Windows Cygwin emulation, expect EINVAL for read end of file.
 *
 * September 26th, 2007 by Robin T. Miller.
 *	When calculating random I/O offset, factor in the record count
 * for large capacity disks to avoid boundaries (1K,2K,4K,8K,etc), since
 * we're using a shift value to generate larger offsets (at present).
 *
 * September 9th, 2007 by Dudekula Masthan (STSD).
 *	When Hazard flag is enabled, log "CORRUPTION:" during data corruptions.
 *
 * May 17th, 2007 by Robin T. Miller.
 *	Update FmtKeepAlive() "%e" to use total_errors for now, otherwise
 * error count is incorrect during data compare failures (oversight, damn!).
 *
 * January 6th, 2007 by Robin T. Miller.
 *	When random I/O is used, scale the random number by a multiplier
 * and the device block size, to obtain larger offset for >1TB capacities.
 *
 * November 1st, 2006 by Robin T. Miller.
 *      In ReportDeviceInfo(), do not save the updated file offset
 * unless we're using AIO, since our normal read/write test functions
 * maintain this offset themselves.
 *
 * October 16th, 2006 by Robin T. Miller.
 *      Updated stoh() and htos() from Scu source.
 *      Handle new timestamp option:
 *      - skip timestamps during verification.
 *      - report time block was written during corruptions.
 *
 * October 4th, 2006 by Robin T. Miller.
 *      Added warning in delete_file() if file cannot be unlink'ed, but
 * this should never occur now that terminate() only calls if it's open.
 *
 * June 24th, 2006 by Robin T. Miller.
 *	Fix two places in ExecuteTrigger() where a status value was not
 * returned!  (overlooked when changing void to int return value).
 *
 * January 19th, 2005 by Nagendra Vadlakunta.
 * 	To add IA64 support for Windows, excluded MACHINE_64BIT
 * part of the code in functions stoh() and htos().
 * 
 * January 12th, 2005 by Robin T. Miller.
 *      Added keepalive format control string parsing (see help).
 *      For Hazard, do *not* prepend our program name to messages.
 *
 *      In Hazard mode, remove space following "RPCLOGn: ", so we are
 * consistent with how Hazard logs all its' output.
 *
 * December 16th, 2004 by Robin Miller.
 *      Updated printf control strings in ReportDeviceInfo() to properly
 * display lba following by offsets (the latter was incorrect, due to
 * wrong format used for lba).  Found on 32 bit systems (of course)
 * Side Note:  I've started coding lba's for 64 bits instead of 32 bits
 * which limits the size (of course), but there's much work to do yet!
 *
 * October 21st, 2004 by Robin Miller.
 *      Report the current file position during error report.
 * Although the relative block number is formulated from the file
 * offset, some folks would also like to see the actual offset.
 * For random I/O, always align offsets to the device size (dsize).
 * Failure to do this causes false data corruptions to regular files.
 * For big-endian machines, the IOT pattern must be byte swapped, since
 * IOT is designed to be little-endian only.
 *
 * June 24th, 2004 by Robin Miller.
 *      Major cleanup to init_iotdata() function to properly handle
 * non-modulo prefix and transfer counts.  The odd bytes were not
 * initialized to something (now ~0) which lead to false failures.
 *
 * June 22nd, 2004 by Robin Miller.
 *      Added support for triggers on corruption.
 *      Properly report failing lba when lbdata is used.
 *      Don't align random offsets to the device size when testing
 * regular files through a file system.  In general, random I/O is
 * not usually going to work to a file, since part of file usually
 * gets overwitten (sorry, we don't track blocks already written).
 *
 * March 30th, 2004 by Robin Miller.
 *      Improve lseek error messages (should they should fail).
 *
 * March 24th, 2004 by Robin Miller.
 *      Update code in do_random() where the random data limit
 * (rdata_limit) was being truncated to an unsigned long, which
 * is 32-bits many systems.  This causes large capacity disks,
 * such as 36GB (0x900000000), to be truncated to zero which
 * causes a divide by zero ("Arithmetic exception" on HP-UX).
 * Also increase the size of the random number (randum) to
 * 64-bits (on 32-bit systems), so larger seeks are possible.
 *
 * February 23, 2004 by Robin Miller.
 *      Reverse the buffer and prefix pattern bytes being dumped
 * in verify_prefix(), so they properly reflect the expected versus
 * found bytes.  Otherwise, the information is misleading.
 *
 * November 25th, 2003 by Robin Miller.
 *      When formatting the prefix string, if we're doing random
 * I/O, round the prefix string up to sizeof(u_int32), so partial
 * patterns (non-modulo our 4 byte pattern) do not get used, which
 * causes false data compare failures.
 * Note: Failures still occur if random I/O is used with pattern
 * files containing non-repeating data pattern bytes!
 *
 * November 20th, 2003 by Robin Miller.
 *	Broken verify data function up for better performance.
 *	Update prefix string logic to write the string in every
 * logical block (lbdata_size).  This had to be done or else random
 * I/O with prefix strings failed!  It also give better coverage.
 *
 * November 17th, 2003 by Robin Miller.
 *	Breakup output to stdout or stderr, rather than writing
 * all output to stderr.  If output file is stdout ('-') or a log
 * file is specified, then all output reverts to stderr.
 *
 * October 8th, 2003 by Robin Miller.
 *	On AIX, accept ENXIO for I/O's pass EOF.
 *
 * September 27th, 2003 by Robin Miller.
 *      Added support for AIX.
 *
 * March 20th, 2003 by Robin Miller.
 *	Added FmtPrefix() to format the prefix string.
 *
 * March 18th, 2003 by Robin Miller.
 *	Optimize code and loops using USE_PATTERN_BUFFER define.
 *
 * March 15th, 2003 by Robin Miller.
 *	Added support for data pattern prefix strings.
 *
 * March 4th, 2003 by Robin Miller.
 *	Add support for broken EOF SunOS release.  This means writes
 * at EOF return a count of zero, but there is no errno value to key
 * off like POSIX specifies.
 *
 * November 21st, 2002 by Robin Miller.
 *	On HP-UX, accept ENXIO for I/O's pass EOF.
 *
 * November 14th, 2002 by Robin Miller.
 *	Add support for 32-bit HP-UX compilation.
 *
 * October 10th, 2002 by Robin Miller.
 *	Display correct erroring byte during data compare errors,
 * when using a 32-bit hex data pattern.
 *
 * February 1st, 2002 by Robin Miller.
 *	Make porting changes necessary for Solaris 8.
 *
 * January 29th, by Robin Miller.
 *	Minor tweak to clarify correct versus incorrect data dumped.
 *
 * June 25th, 2001 by Robin Miller.
 *	Report mt status for all errors, not just EIO errors.  Also,
 * report mt status on unexpected EOF/EOM when no data transferred.
 * Note: Reporting mt and EEI status is only done for Tru64 Unix.
 *
 * February 24th, 2001 by Robin Miller.
 *	Add conditionalization for QNX RTP (Neutrino).
 *
 * January 24th, 2001 by Robin Miller.
 *	Add support for variable I/O requests sizes.
 *	Conditionalize some functions to allow INLINE macros.
 *	Modifications to allow IOT test pattern to honor the lba
 * size variable, rather than hardcoding IOT to 512 byte sectors.
 *
 * January 15th, 2001 by Robin Miller.
 *	Don't terminate() on failures, return error to caller.
 *	Note: seek functions still call terminate()... more work!
 *
 * January 2nd, 2001 by Robin Miller.
 *      Make changes to build using MKS/NuTCracker product.
 *
 * October 4th, 2000 by Robin Miller.
 *	Update is_Eof() to accept ENXIO for AIO reads @ EOM on
 * SCO UnixWare systems.  All other systems return ENOSPC or zero.
 *
 * April 25th, 2000 by Robin Miller.
 *	Added an expect flag to dump_buffer to help with formatting.
 *
 * April 18th, 2000 by Robin Miller.
 *	Modified calls to report_error() to ensure error count bumped.
 *
 * March 28th, 2000 by Robin Miller.
 *	Modified file position functions to accept device information
 * parameter, so necessary debug could be added to these funcitons.
 * Also, only scale the random position upwards by the device size
 * every other record, so low blocks gets utilized more often.
 * Note:  These changes degrade random I/O performance slightly.
 * [ All debug needs ripped out to obtain better performance, ]
 *
 * February 17th, 2000 by Robin Miller.
 *	Adding better support for multi-volume tape testing.  Mainly,
 * make it work with writing multiple tape files, rather than one file.
 *
 * February 16th, 2000 by Robin Miller.
 *	Set exit_status to FAILURE in RecordError() function.  This
 * is necessary to catch any error being logged, since test functions
 * no longer call terminate() with FAILURE status.
 *
 * January 22nd, 2000 by Robin Miller.
 *	Add check for Cygwin device names for Windows/NT.
 *
 * January 4th, 2000 by Robin Miller.
 *	Major cleanup in verify_data().  Now reports IOT block number.
 *	Added verify_buffers() and verify_lbdata() functions for raw.
 *
 * December 31st, 1999 by Robin Miller.
 *	Modify do_random() to ensure rlimit is not exceeded when the lower
 * file position is factored in, to stay within desired lba range.
 *
 * December 30th, 1999 by Robin Miller.
 *	Modify do_random() to take into consideration the transfer size,
 * to ensure the requested random I/O data limit is not exceeded.
 *	Added get_lba() function to return the current logical block address.
 *
 * November 11th, 1999 by Robin Miller.
 *	Add LogDiagMsg() to log diagnostic information to event logger.
 *
 * November 10th, 1999 by Robin Miller.
 *	Update make_lbdata() & winit_lbdata() so if the IOT test pattern is
 * selected, and the device block size is NOT 512 bytes, we force 1 block.
 * Note: This only affects Tru64 Unix, since we obtain the real sector size.
 *
 * November 9th, 1999 by Robin Miller.
 *	Remove use of '%p' in dump_buffer(), since it's use is inconsistent.
 * With Cygnus Solutions, '%p' displays a leading '0x', other OS's don't!
 *
 * August 26th, 1999 by Robin Miller.
 *	Report an error for ENOSPC, if no data has been transferred.
 *	Previously, this error was only reported for tape devices.
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
 * July 7th, 1999 by Robin Miller.
 *	Modify CvtStrtoValue() to check for recursive calls which return
 * zero (0) for '/' and '%', which cause a divide by zero fault/core dump.
 *
 * June 28, 1999 by Robin Miller.
 *	For 32-bit systems, added CvtStrtoLarge() function to
 * permit double or long long values, since u_long is too small.
 *
 * May 27, 1999 by Robin Miller.
 *	Added support for micro-second delays.
 *
 * April 8, 1999 by Robin Miller.
 *	Added format_ltime() to format table() sysinfo times.
 *
 * January 7, 1999 by Robin Miller.
 *	Removed fflush() in Fprintf() function which caused intermixed
 * output when multiple processes were running (i.e., serial line testing).
 *
 * December 21, 1998 by Robin Miller.
 *	- update Malloc() to clear allocated memory.
 *	- for DUNIX, updates to handle resets for tapes.
 *
 * December 16, 1998 by Robin Miller.
 *	Merge in changes made by George Bittner:
 *	- modify do_random(), use random value as a block number
 *	  instead of a byte offset, for testing larger disks/files.
 *	- ensure the random offset is within starting file position
 *	  and the end of the disk/partition.
 *
 * November 19, 1998, by Robin Miller.
 *	Fix problem where wrong lbdata lba was returned for offset 0.
 * This required updates to make_lbdata() and winit_lbdata() functions.
 *	[ sorry folks, major brain burp!!! ]
 *
 * November 16, 1998 by Robin Miller.
 *	For AIO, report the relative block from saved AIO control block.
 *
 * October 29, 1998 by Robin Miller.
 *	Implement a random I/O data limit, instead of using the normal
 * data limit variable (not good to dual purpose this value).
 *
 * October 26, 1998 by Robin Miller.
 *	Add functions make_lbdata() and winit_lbdata() which handle
 * using both random I/O and lbdata options.  The file offset seeked
 * to is used as the starting lbdata address.
 *
 * April 28, 1998 by Robin Miller.
 *	For WIN32/NT, or in O_BINARY into open flags to force binary
 *	mode (the default is text mode).
 *
 * May 16, 1997 by Robin Miller.
 *	Modified macro used in ReportDeviceInfo() which rounded block
 *	up, causing the erroring block to be off by one, when data
 *	compare errors were not at the beginning of a block.  Also,
 *	report the block offset (byte within block) when non-modulo.
 *
 * May 14, 1997 by Robin Miller.
 *	If we encounter a ENOSPC error and no data has been transferred,
 *	flag this as an error.  This normally indicates a zero length
 *	partition or the user may have seek'ed past eom or eop.
 *
 * March 27, 1997 by Ali Eghlima.
 *      Fix call to report_error() to reflect "unlink" failed.
 *
 * March 7, 1997 by Robin Miller.
 *	In ReportDeviceInfo(), when we're doing a copy/verify
 *	operation, allow output device to be a different offset.
 *
 * February 28, 1996 by Robin Miller.
 *	Modified ReportDeviceInfo() so we seek past disk errors.
 *	This action allows testing to continue with "errors=n".
 *
 * February 21, 1996 by Robin Miller.
 *	Added do_random() function for random I/O to disks.
 *
 * December 19, 1995 by Robin Miller.
 *	Conditionalize for Linux Operating System.
 *
 * Novemeber 18, 1995 by Robin Miller.
 *	Removing unaligned data access (ade) test code (code cleanup).
 *
 * November 11, 1995 by Robin Miller.
 *	Fix bug with verifying pad bytes.  Basically, the previous logic,
 *	while valid for short reads, was incorrect when the pad bytes did
 *	*not* start on a modulo sizeof(int) boundary. This caused variable
 *	length reads with small increment values to report an (invalid)
 *	pad byte data compare error.  NOTE: Only occurred w/pattern file.
 *
 * July 22, 1995 by Robin Miller.
 *	Finally, correctly dump data buffers with context (yes, I made
 *	sure I tested min/max limits via fault insertion this time).
 *
 * July 15, 1995 by Robin Miller.
 *	Add is_Eof() to handle end of media (ENOSPC), and cleanup code.
 *
 * July 7, 1995 by Robin Miller.
 *	Correctly dump the pattern buffer on data compare errors.
 *	When reporting a compare error, also display the byte count.
 *	This latter information is useful for variable length records.
 *
 * July 6, 1995 by Robin Miller.
 *	Changed a number of fprintf's to Fprintf so the child PID gets
 *	reported during error processing (how did I miss this stuff?).
 *
 * September 23, 1994 by Robin Miller.
 *      Make changes necessary to build on QNX 4.21 release.
 *
 * January 20, 1994 by Robin Miller.
 *	When checking the pad bytes, don't do the entire buffer since very
 *	large buffers (e.g. 100m) may have been specified using min, max,
 *	and incr options which cause excessive paging and poor performance.
 *
 * October 28, 1993 by Robin Miller.
 *	For multiple processes, display the PID to differentiate output.
 *
 * September 15, 1993 by Robin Miller.
 *	Limit pattern buffer dumping to size of pattern buffer.
 *
 * September 17, 1993 by Robin Miller.
 *	Added RecordWarning() function to reporting record number and
 *	time stamp on warning errors (useful for debugging purposes).
 *	More limiting of data & pattern buffer dumping (less bytes).
 *
 * September 3, 1993 by Robin Miller.
 *	Allow "inf" or "INF" keywords to set maximum counts.
 *
 * September 2, 1993 by Robin Miller.
 *	Added device specific information.
 *
 * September 1, 1993 by Robin Miller.
 *	Report proper record number during errors (add partial records).
 *	Limit data dumped when data verify errors occur (short records).
 *
 * August 27, 1993 by Robin MIller.
 *	Added support for DEC OSF/1 POSIX Asynchronous I/O (AIO).
 *
 * August 17, 1993 by Robin Miller.
 *	Added function RecordError() to record when an error occurs,
 *	and added function Ctime() to append date/time string to the
 *	log buffer.
 *
 * August 10, 1993 by Robin Miller.
 *	Added verify_padbuf() function to check pad buffer bytes after
 *	read operations to ensure they weren't overwritten.
 *
 * August 4, 1993 by Robin Miller.
 *	Added various printing functions to simplify error reporting.
 *
 * September 11, 1992 by Robin Miller.
 *	Added additional debug information when reopening a device.
 *
 * September 5, 1992 by Robin Miller.
 *	Initial port to QNX 4.1 Operating System.
 *
 * May 22, 1992 by Robin Miller.
 *	Control / force kernel address data exception via flag.
 *
 * March 11, 1992 by Robin Miller.
 *	Changes necessary for port to 64-bit Alpha architecture.
 *
 * October 16, 1990 by Robin Miller.
 *	Added myalloc() memory allocation function to allocate and
 *	align the buffer address using the alignment value.
 *
 * October 9, 1990 by Robin Miller.
 *	Use variable hz instead of HZ define for clock ticks per second
 *	so user can specify different value via "hz=ticks" option.
 *
 * August 21, 1990 by Robin Miller.
 *	Changed exit status so scripts can detect and handle errors
 *	based on the exit code.  If not success, fatal error, or end
 *	of file/tape, the exit code is the error number (errno).
 *
 * August 21, 1990 by Robin Miller.
 *	Added function dump_buffer() to dump buffer in hex bytes.
 *
 * August 8, 1990 by Robin Miller.
 *	Added functions seek_file() and skip_records().  Modified seek
 *	file function to avoid lseek() system call overhead (see code).
 *
 *	Changed malloc() to valloc() to align buffer on page boundry.
 *	On some archetectures, this results on better performance to
 *	raw devices since the DMA is done directly to the users' buffer.
 *
 * April 11, 1990 by Robin Miller.
 *	Added function mmap_file() to memory map a file.  Added munmap()
 *	syscall to reopen_file() which gets called for multiple passes.
 *	This allows us to time the mmap() as well as the munmap() code.
 *
 * March 21, 1990 by Robin Miller.
 *	Added function delete_file() which checks for a regular file
 *	and then unlinks it.
 *
 */

/*
 * Forward References:
 */
int ExecuteBuffered(dinfo_t *dip, char *cmd, char *buffer, int bufsize);
void analyze_iot_data(dinfo_t *dip, u_char *pbuffer, u_char *vbuffer, size_t bcount);
void display_iot_data(dinfo_t *dip, u_char *pbuffer, u_char *vbuffer, size_t bcount);
void display_iot_block(dinfo_t *dip, int block, OFF_T block_offset, u_char *pptr, u_char *vptr, size_t bsize);
void report_bad_sequence(dinfo_t *dip, int start, int length, OFF_T offset);
void report_good_sequence(dinfo_t *dip, int start, int length, OFF_T offset);
static size_t copy_prefix( dinfo_t *dip, u_char *buffer, size_t bcount );
int verify_prefix(struct dinfo *dip, u_char *buffer, size_t bcount, int bindex, size_t *pcount);

static int verify_data_normal(	struct dinfo	*dip,
				u_char		*buffer,
				size_t		bcount,
				u_int32		pattern);
static int verify_data_prefix(	struct dinfo	*dip,
				u_char		*buffer,
				size_t		bcount,
				u_int32		pattern );
static int verify_data_with_lba(struct dinfo	*dip,
				u_char		*buffer,
				size_t		bcount,
				u_int32		pattern,
				u_int32		*lba );

static size_t CalculateDumpSize(dinfo_t *dip, size_t size);
static int dopad_verify (
			struct dinfo	*dip,
			u_char		*buffer,
			size_t		offset,
			u_int32		pattern,
			size_t		pbytes,
			size_t		pindex,
			bool		inverted );
int vSprintf(char *bufptr, const char *msg, va_list ap);
static int get_max_cpu_busy(dinfo_t *dip, char *cmd);

#if 0
static char *pad_str =		"Pad";
#endif
static char *lba_str =          "Lba";
static char *data_str =		"Data";
static char *pattern_str =	"Pattern";
static char *prefix_str =	"Prefix";
static char *verify_str =	"Verify";

static char *compare_error_str =	"Data compare error at byte";
static char *bad_conversion_str =
		 "Warning: unexpected conversion size of %d bytes.\n";

/*
 * create_directory() - Create a Directory.
 *
 * Inputs:
 *	dip = The device information pointer.
 *	dir = Pointer to directory to be created.
 *
 * Return Value:
 *	Returns SUCCESS/FAILURE/WARNING
 *	  SUCCESS = Directory Created
 *	  FAILURE = Not a directory or creation failed.
 *	  WARNING = Already Exists
 */
int
create_directory(struct dinfo *dip, char *dir)
{
    struct stat sb;
    int status;

    /*
     * Ensure user specified a directory, or create as necessary.
     */
    if ( (status = stat(dir, &sb)) == SUCCESS) {
	if ( !(sb.st_mode & S_IFDIR) ) {
	    Fprintf("'%s' is not a directory!\n", dir);
	    status = FAILURE;
	} else {
	    // Too much noise with multiple passes.
	    //Fprintf("directory '%s' already exists!\n", dir);
	    status = WARNING;	/* Show it already exists. */
	}
    } else {
	if (dip->di_debug_flag || dip->di_fDebugFlag) {
	    Printf("Creating directory '%s'...\n", dir);
	}
#if defined(WIN32)
	if ( !CreateDirectory(dir, (LPSECURITY_ATTRIBUTES) 0) ) {
	    status = FAILURE;
	    if ( isFsFullOk(dip, "CreateDirectory()") ) return(status);
	    wPerror("Failed to create directory '%s'", dir);
	    report_error(dip, "CreateDirectory()", TRUE);
#else /* !defined(WIN32) */
	if ( (status = mkdir(dir, 0777)) < 0) {
	    if ( isFsFullOk(dip, "mkdir()") ) return(status);
	    Perror("Failed to create directory '%s'", dir);
	    report_error(dip, "mkdir()", TRUE);
#endif /* defined(WIN32) */
	    ++dip->di_error_count;
	} else {
	    status = SUCCESS;
	}
    }
    return (status);
}

/*
 * remove_current_directory() - Remove The Current Directory.
 *
 * Inputs:
 *	dip = The device information pointer.
 *
 * Return Value:
 *	Returns SUCCESS/FAILURE = Directory Removed/Not Removed.
 */
int
remove_current_directory(struct dinfo *dip)
{
    char dirpath[PATH_BUFFER_SIZE];
    char *bp = dirpath;

    if (dip->di_dirpath) {
	bp += sprintf(bp, "%s%c", dip->di_dirpath, DIRSEP);
    }
    /* Append subdirectory (if any). */
    if (dip->di_subdir) {
	bp += sprintf(bp, "%s", dip->di_subdir);
    }
    return( remove_directory(dip, dirpath) );
}

/*
 * remove_directory() - Remove a Directory (assumed to be emppty)
 *
 * Inputs:
 *	dip = The device information pointer.
 *	dir = Pointer to directory to be removed.
 *
 * Return Value:
 *	Returns SUCCESS/FAILURE = Directory Removed/Not Removed.
 */
int
remove_directory(struct dinfo *dip, char *dir)
{
    int status;

    if (dip->di_debug_flag || dip->di_fDebugFlag) {
	Printf("Removing directory '%s'...\n", dir);
    }
#if defined(WIN32)
    status = SUCCESS;
    if ( !RemoveDirectory(dir) ) {
	DWORD error = GetLastError();
	status = FAILURE;
	wPerror("Failed to remove directory '%s'", dir);
	report_error(dip, "RemoveDirectory", TRUE);
    }
#else /* !defined(WIN32) */
    if ( (status = rmdir(dir)) == FAILURE) {
        if (errno == ENOENT) {
            LogMsg (efp, logLevelWarn, 0,
                    "Warning: Directory '%s' does NOT exist during unlink, created?\n",
                    dir);
        } else {
	    Perror("Failed to remove directory '%s'", dir);
	    report_error (dip, "rmdir", TRUE);
        }
    }
#endif /* defined(WIN32) */
    return (status);
}

/************************************************************************
 *									*
 * delete_file() - Delete the specified file.				*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *		file = Pointer to the file to delete.			*
 *									*
 * Outputs:	Returns SUCCESS/FAILURE = File Delete/Not Deleted.	*
 *									*
 ************************************************************************/
int
delete_file (struct dinfo *dip, char *file)
{
    int status;

    if (dip->di_debug_flag || dip->di_fDebugFlag) {
	Printf("Deleting file '%s'...\n", file);
    }
#if defined(WIN32)
    status = SUCCESS;
    if ( !DeleteFile(file) ) {
	DWORD error = GetLastError();
	if (error == ERROR_FILE_NOT_FOUND) {
	    LogMsg (efp, logLevelWarn, 0,
		    "Warning: File '%s' does NOT exist during DeleteFile, created?\n",
		    file);
	} else {
	    status = FAILURE;
	    wPerror("Failed to delete file '%s'", file);
	    report_error(dip, "DeleteFile", TRUE);
	}
    }
#else /* !defined(WIN32) */
    if ( (status = unlink(file)) == FAILURE) {
        if (errno == ENOENT) {
            LogMsg (efp, logLevelWarn, 0,
                    "Warning: File '%s' does NOT exist during unlink, created?\n",
                    file);
        } else {
	    Perror("Failed to delete file '%s'", file);
	    report_error (dip, "unlink", TRUE);
        }
    }
#endif /* defined(WIN32) */
    return (status);
}

/*
 * delete_files() - Delete All Test Files.
 *
 * Description:
 *	This function deletes one or more files, and one or more
 * directories, assuming we created them.
 *
 * Inputs:
 *	dip = The device information pointer.
 *
 * Return Value:
 *	Returns SUCCESS/FAILURE = File Deleted/Deletion Failed
 */
int
delete_files(struct dinfo *dip)
{
    int error, status = SUCCESS;

    if (!dip->di_file_limit && !dip->di_user_dir_limit && !dip->di_user_subdir_limit && !dip->di_user_subdir_depth) {
	;
	/* Maybe a directory specified! */
	//status = delete_file(dip, dip->di_dname);
	//return (status); /* Single file! */
    } else if (dip->di_file_limit && !dip->di_user_dir_limit && !dip->di_user_subdir_limit && !dip->di_user_subdir_depth) {
	if (dip->di_debug_flag || dip->di_fDebugFlag) {
	    Printf("Removing up to %u files...\n", dip->di_file_limit);
	}
	/* Fall through to delete top level files/directory. */
    } else if (dip->di_user_subdir_limit && !dip->di_user_subdir_depth) {
	char spath[PATH_BUFFER_SIZE];
	u_int max_subdir = dip->di_max_subdir_number;
	u_int subdir;

	if (dip->di_debug_flag || dip->di_fDebugFlag) {
	    Printf("Removing %u subdirs...\n", max_subdir);
	}
	/*
	 * Delete subdirectory files and directories.
	 */
	for (subdir = 0; (subdir < max_subdir); ) {
	    subdir++;
	    (void)sprintf(spath, "%s%u", dip->di_dirprefix, subdir);
	    error = delete_subdir_files(dip, spath);
	    if (error && (status == SUCCESS)) {
		status = error;
	    }
	}
	/* Fall through to delete top level files/directory. */
    } else if (!dip->di_user_subdir_limit && dip->di_user_subdir_depth) {
	char spath[PATH_BUFFER_SIZE];
	char *bp = spath;
	u_int depth;
	u_int max_depth = dip->di_max_subdir_depth;

	if (dip->di_debug_flag || dip->di_fDebugFlag) {
	    Printf("Removing subdirs with depth of %u...\n", max_depth);
	}
	while (max_depth) {
	    bp = spath;
	    /*
	     * Start at bottom of tree.
	     */
	    for (depth = 0; (depth < max_depth); ) {
		depth++;
		if (bp == spath) {
		    bp += sprintf(bp, "%s%u", dip->di_dirprefix, depth);
		} else {
		    bp += sprintf(bp, "%c%s%u", DIRSEP, dip->di_dirprefix, depth);
		}
	    }
	    error = delete_subdir_files(dip, spath);
	    if (error && (status == SUCCESS)) {
		status = error;
	    }
	    max_depth--;
	}
	/* Fall through to delete top level files/directory. */
    } else {
	char spath[PATH_BUFFER_SIZE];
	char *bp;
	u_int subdir, depth;
	u_int max_subdir, max_depth;
	max_subdir = dip->di_max_subdir_number;
	max_depth = dip->di_max_subdir_depth;
	/*
	 * For each subdirectory, remove all files and directories.
	 */
	if (dip->di_debug_flag || dip->di_fDebugFlag) {
	    Printf("Removing %u subdirs with depth of %u...\n", max_subdir, max_depth);
	}
	while (max_subdir && max_depth) {
	    while (max_depth) {
		for (subdir=0; (subdir < max_subdir); ) {
		    bp = spath;
		    subdir++;
		    bp += sprintf(bp, "%s%u", dip->di_dirprefix, subdir);
		    for (depth = 1; (depth < max_depth); ) {
			depth++;
			bp += sprintf(bp, "%c%s%u", DIRSEP, dip->di_dirprefix, depth);
		    }
		    error = delete_subdir_files(dip, spath);
		    if (error && (status == SUCCESS)) {
			status = error;
		    }
		}
		max_depth--;
	    }
	    max_subdir--;
	}
	/* Fall through to delete top level files/directory. */
    }
 
    /* Delete the top level files. */
    error = delete_subdir_files(dip, NULL);
    if (error && (status == SUCCESS)) {
	status = error;
    }

    /* Ok, now delete the top level directory (if we created it). */
    if ( (status == SUCCESS) &&
	 (dip->di_dir_created && dip->di_dirpath) ) {
	error = remove_directory(dip, dip->di_dirpath);
	if (error && (status == SUCCESS)) {
	    status = error;
	}
    }
    return (status);
}

/*
 * delete_subdir_files() - Delete Subdirectory Files.
 *
 * Description:
 *	This function sets up the subdirectory path, then deletes
 * one or more files, then the subdirectory itself.
 *
 * Inputs:
 *	dip = The device information pointer.
 *	spath = The subdirectory to remove.
 *
 * Return Value:
 *	Returns SUCCESS/FAILURE = File/Directory Deleted/Deletion Failed
 */
int
delete_subdir_files(struct dinfo *dip, char *spath)
{
    char dirpath[PATH_BUFFER_SIZE];
    char *file;
    int status = SUCCESS;

    if (spath) {
	if (dip->di_dirpath) {
	    (void)sprintf(dirpath, "%s%c%s", dip->di_dirpath, DIRSEP, spath);
	} else {
	    (void)sprintf(dirpath, "%s", spath);
	}
	/*
	 * When terminating prematurely, we may be interrupting the creation
	 * of the directory or file, so we must check for existance, otherwise
	 * we'll encounter false failures.
	 */
	if ( !file_exists(dip, dirpath) ) {
	    return (SUCCESS);
	}
    }
    if (dip->di_subdir)	{
	free(dip->di_subdir);
	dip->di_subdir = NULL;
    }
    /*
     * Allow no subdirectory to setup for top level files.
     */
    if (spath) {
	dip->di_subdir = strdup(spath);
    }

    if (dip->di_file_limit == 0) {
	file = make_file_name(dip);
	if ( file_exists(dip, file) ) {
	    status = delete_file(dip, file);
	}
    } else {
	int error;
	dip->di_file_number = 0;
	do {
	    file = make_file_name(dip);
	    /*
	     * All files may not exist if the file system is full,
	     * or we terminated prematurely (runtime, signal, etc).
	     */
	    if ( file_exists(dip, file) ) {
		error = delete_file(dip, file);
		if (error && (status == SUCCESS)) {
		    status = error;
		}
	    } else {
		break; /* Try to remove directory below. */
	    }
	} while ( ++dip->di_file_number < dip->di_file_limit );
    }
    /*
     * If all files were removed, delete the subdirectory too!
     */
    if ( (status == SUCCESS) && spath) {
	status = remove_directory(dip, dirpath);
    }
    return (status);
}

/*
 * file_exists() - Check for file existance.
 *
 * Inputs:
 *	dip = The device information pointer.
 *	file = File name to check for existance.
 *
 * Return Value:
 *	Returns TRUE/FALSE = File exists / Does not exist.
 */
bool
file_exists(struct dinfo *dip, char *file)
{
    struct stat sb;
    int error;

    error = stat(file, &sb);
    if (error == FAILURE) {
	/* Note: Only really expect ENOENT! */
	if (dip->di_debug_flag || dip->di_fDebugFlag) {
	    Perror("DEBUG: stat() failed on file '%s'", file);
	}
	return (FALSE);
    } else {
	return (TRUE);
    }
}

/*
 * truncate_file() - Truncate a File.
 *
 * Description:
 *	This function truncates the file at the specified offset.
 *
 * Inputs
 *	dip = The device information pointer.
 *	offset = The offset to truncate file at.
 *
 * Return Value:
 *	Returns SUCCESS/FAILURE = File Truncated/Truncate failed.
 */
int
truncate_file (struct dinfo *dip, OFF_T offset)
{
    int status;

    if (dip->di_debug_flag || dip->di_fDebugFlag) {
	Printf("Truncating file '%s' at offset " FUF "...\n", dip->di_dname, offset);
    }
#if defined(WIN32)
    status = SUCCESS;
    if (set_position(dip, offset, FALSE) != (OFF_T) -1) {
	if ( !SetEndOfFile(dip->di_fd) ) {
	    report_error (dip, "SetEndOfFile", TRUE);
	    status = FAILURE;
	}
    } else {
	status = FAILURE;
    }
#else /* !defined(WIN32) */
    if ( (status = ftruncate(dip->di_fd, offset)) == FAILURE) {
	report_error (dip, "ftruncate", TRUE);
    }
#endif /* defined(WIN32) */
    return (status);
}

/*
 * mySleep() - Sleep in seconds and/or microseconds.
 *
 * Inputs:
 * 	dip = The device information pointer.
 *	sleep_time = The number of seconds/useconds to sleep.
 *	The global micro_delay flag if set selects microdelays.
 *
 * Return Value:
 *	void
 */
void
mySleep(dinfo_t *dip, unsigned int sleep_time)
{
    unsigned int timeout;

    /*
     * Allow a random delay. 
     */
    if (sleep_time == RANDOM_DELAY_VALUE) {
	if (dip->di_micro_flag) {
	    sleep_time = (unsigned int)(get_random() % uSECS_PER_SEC);
	} else {
	    sleep_time = (unsigned int)(get_random() % mSECS_PER_SEC);
	}
    }
    /*
     * Note: Convert microseconds (us) to milliseconds (ms), until
     * we have true microsecond delays again (see notes below).
     */
    if (dip->di_micro_flag) {
	timeout = howmany(sleep_time, MSECS); /* convert usecs to ms */
    } else {
	timeout = (sleep_time * MSECS);	/* convert secs to ms */
    }
    if (timeout == 0) timeout++;	/* minimum of one ms! */

    (void)os_msleep(timeout);

    return;
}

/*
 * Simple function to sleeping in seconds.
 *
 * Note: We don't use sleep() to avoid signal issues!
 */
void
SleepSecs(unsigned int sleep_time)
{
    unsigned int timeout;

    timeout = (sleep_time * MSECS);	/* convert secs to ms */
    if (timeout == 0) timeout++;	/* minimum of one ms! */
    (void)os_msleep(timeout);
    return;
}

/************************************************************************
 *									*
 * CalculateDumpSize() - Calculate the number of data bytes to dump.	*
 *									*
 * Description:								*
 *	For non-memory mapped files, we'll dump the pad bytes.  These	*
 * pad bytes do not exist for memory mapped files which are directly	*
 * mapped to memory addresses.						*
 *									*
 * Inputs:							        * 
 * 	dip = The device information pointer.			        *
 *	size = The size of the buffer to dump.				*
 *									*
 * Outputs:	Size of buffer to dump.					*
 *									*
 ************************************************************************/
static size_t
CalculateDumpSize (dinfo_t *dip, size_t size)
{
	size_t dump_size = size;

	if (!dip->di_mmap_flag) {
	    dump_size += PADBUFR_SIZE;
	}
	if (dump_size > dip->di_data_size) dump_size = dip->di_data_size;
	return (dump_size);
}

/************************************************************************
 *									*
 * dump_buffer() Dump data buffer in hex bytes.				*
 *									*
 * Inputs:							        * 
 * 	dip = The device infromation pointer.				*
 *	name = The buffer name being dumped.				*
 *	base = Base pointer of buffer to dump.				*
 *	ptr  = Pointer into buffer being dumped.			*
 *	dump_size = The size of the buffer to dump.			*
 *	bufr_size = The maximum size of this buffer.			*
 *	expected = Boolean flag (True = Expected).			*
 *									*
 * Return Value:							*
 *		Void.							*
 *									*
 ************************************************************************/
void
dump_buffer (	dinfo_t		*dip,
		char		*name,
		u_char		*base,
		u_char		*ptr,
		size_t		dump_size,
		size_t		bufr_size,
		bool		expected )
{
    size_t boff, coff, limit, offset;
    u_int field_width = 16;
    u_char *bend = (base + bufr_size);
    u_char *bptr;
    u_char data;
    u_char *abufp, *abp;

    /* TODO: Buffer each line? */
    abufp = abp = (u_char *) Malloc(field_width + 1);
    /*
     * Since many requests do large transfers, limit data dumped.
     */
    limit = (dump_size < dip->di_dump_limit) ? dump_size : dip->di_dump_limit;

    /*
     * Now to provide context, attempt to dump data on both sides of
     * the corrupted data, ensuring buffer limits are not exceeded.
     */
    bptr = (ptr - (limit >> 1));
    if (bptr < base) bptr = base;
    if ( (bptr + limit) > bend) {
	limit = (bend - bptr);		/* Dump to end of buffer. */
    }
    offset = (ptr - base);		/* Offset to failing data. */
    coff = (ptr - bptr);		/* Offset from dump start. */

    /*
     * NOTE: Rotate parameters are not displayed since we don't have
     * the base data address and can't use global due to AIO design.
     * [ if I get ambitious, I'll correct this in a future release. ]
     */
    Fprintf ("The %scorrect data starts at address %#lx (marked by asterisk '*')\n",
							(expected) ? "" : "in", ptr);
    Fprintf ("Dumping %s Buffer (base = %#lx, offset = %u, limit = %u bytes):\n",
							name, base, offset, limit);
    /* Note: 64-bit look strange, but I'd rather not truncate the address below. */
    /*       Generally, I prefer to compile for 32 bits, with 64 bits offsets. */
#if defined(MACHINE_64BITS)
    LogMsg (efp, logLevelError, (PRT_NOIDENT | PRT_NOFLUSH), "          Address / Offset\n");
#else /* !defined(MACHINE_64BITS) */
    LogMsg (efp, logLevelError, (PRT_NOIDENT | PRT_NOFLUSH), "  Address / Offset\n");
#endif /* defined(MACHINE_64BITS) */

    /*
     * Note: This may be deprecated with new side by side comparision, but at 
     * present it's needed for non-IOT patterns, and also provides context. 
     */
    for (boff = 0; boff < limit; boff++, bptr++) {
	if ((boff % field_width) == (size_t) 0) {
	    if (boff) Fprint(" \"%s\"\n", abufp); abp = abufp;
	    /* Note: This will need updated for 64-bit addresses! */
#if defined(MACHINE_64BITS)
	    LogMsg (efp, logLevelError, (PRT_NOIDENT | PRT_NOFLUSH), "%#018lx/%6d |",
#else /* !defined(MACHINE_64BITS) */
	    LogMsg (efp, logLevelError, (PRT_NOIDENT | PRT_NOFLUSH), "%#010lx/%6d |",
#endif /* defined(MACHINE_64BITS) */
		    bptr, (boff + (offset - coff)));
	}
	data = *bptr;
	Fprint("%c%02x", (bptr == ptr) ? '*' : ' ', data);
        abp += Sprintf ((char *)abp, "%c", isprint((int)data) ? data : ' ');
    }
    if (abp != abufp) {
        while (boff++ % field_width) Fprint("   ");
        Fprint(" \"%s\"\n", abufp);
    }
    free (abufp);
    if (expected) {
	LogMsg (efp, logLevelError, (PRT_NOIDENT | PRT_NOFLUSH), "\n");
    }
    (void)fflush(efp);
}

#if defined(TIMESTAMP)

void
display_timestamp(dinfo_t *dip, u_char *buffer)
{
    time_t seconds;

    seconds = (time_t)stoh(buffer, sizeof(iotlba_t));
    /* Note: ctime() appends newline automatically! */
    Fprintf("The data block was written on %s",
	    os_ctime(&seconds, dip->di_time_buffer, sizeof(dip->di_time_buffer)));
    return;
}
#endif /* defined(TIMESTAMP) */

/************************************************************************
 *									*
 * fill_buffer() - Fill Buffer with a Data Pattern.			*
 *									*
 * Description:								*
 *	If a pattern_buffer exists, then this data is used to fill the	*
 * buffer instead of the data pattern specified.			*
 *									*
 * Inputs:							        * 
 *	dip = The device information pointer.				*
 * 	buffer = Pointer to buffer to fill.				*
 *	byte_count = Number of bytes to fill.				*
 *	pattern = Data pattern to fill buffer with.			*
 *									*
 * Return Value:							*
 *		Void.							*
 *									*
 ************************************************************************/
void
fill_buffer (	dinfo_t		*dip,
		u_char		*buffer,
		size_t		byte_count,
		u_int32		pattern)
{
    register u_char *bptr = buffer;
    register u_char *pptr, *pend;
    register size_t bcount = byte_count;

    pptr = dip->di_pattern_bufptr;
    pend = dip->di_pattern_bufend;

    /*
     * Initialize the buffer with a data pattern.
     */
    if ( !dip->di_fprefix_string ) {
        while (bcount--) {
            *bptr++ = *pptr++;
            if (pptr == pend) {
                pptr = dip->di_pattern_buffer;
            }
        }
    } else {
        register size_t i;
        for (i = 0; i < bcount; ) {
            if ((i % dip->di_lbdata_size) == 0) {
                size_t pcount = copy_prefix (dip, bptr, (bcount - i));
                i += pcount;
                bptr += pcount;
                continue;
            }
            *bptr++ = *pptr++; i++;
            if (pptr == pend) {
                pptr = dip->di_pattern_buffer;
            }
        }
    }
    dip->di_pattern_bufptr = pptr;
    return;
}

/************************************************************************
 *									*
 * init_buffer() - Initialize Buffer with a Data Pattern.		*
 *									*
 * Inputs:							        * 
 * 	dip = The device information pointer.			        *
 *	buffer = Pointer to buffer to init.				*
 *	count = Number of bytes to initialize.				*
 *	pattern = Data pattern to init buffer with.			*
 *									*
 * Return Value:							*
 *		Void.							*
 *									*
 ************************************************************************/
void
init_buffer(	dinfo_t		*dip,
		u_char		*buffer,
		size_t		count,
		u_int32		pattern )
{
    register u_char *bptr;
    union {
        u_char pat[sizeof(u_int32)];
        u_int32 pattern;
    } p;
    register size_t i;

    /*
     * Initialize the buffer with a data pattern.
     */
    p.pattern = pattern;
    bptr = buffer;
    for (i = 0; i < count; i++) {
        *bptr++ = p.pat[i & (sizeof(u_int32) - 1)];
    }
    return;
}

#if _BIG_ENDIAN_
/************************************************************************
 *									*
 * init_swapped() - Initialize Buffer with a Swapped Data Pattern.	*
 *									*
 * Inputs:							        * 
 * 	dip = The device information pointer.			        *
 *	buffer = Pointer to buffer to init.				*
 *	count = Number of bytes to initialize.				*
 *	pattern = Data pattern to init buffer with.			*
 *									*
 * Return Value:							*
 *		Void.							*
 *									*
 ************************************************************************/
void
init_swapped (	dinfo_t		*dip,
		u_char		*buffer,
		size_t		count,
		u_int32		pattern )
{
    register u_char *bptr;
    union {
        u_char pat[sizeof(u_int32)];
        u_int32 pattern;
    } p;
    register size_t i;

    /*
     * Initialize the buffer with a data pattern.
     */
    p.pattern = pattern;
    bptr = buffer;
    for (i = count; i ; ) {
        *bptr++ = p.pat[--i & (sizeof(u_int32) - 1)];
    }
    return;
}
#endif /* _BIG_ENDIAN_ */

/************************************************************************
 *									*
 * init_lbdata() - Initialize Data Buffer with Logical Block Data.	*
 *									*
 * Description:								*
 *	This function takes the starting logical block address, and	*
 * inserts it every logical block size bytes, overwriting the first 4	*
 * bytes of each logical block with its' address.			*
 *									*
 * Inputs:							        * 
 * 	dip = The device information pointer.			        *
 *	buffer = The data buffer to initialize.				*
 *	count = The data buffer size (in bytes).			*
 *	lba = The starting logical block address.			*
 *	lbsize = The logical block size (in bytes).			*
 *									*
 * Outputs:							        * 
 * 	Returns the next lba to use.					*
 *									*
 ************************************************************************/
u_int32
init_lbdata (
	struct dinfo	*dip,
	u_char		*buffer,
	size_t		count,
	u_int32		lba,
	u_int32		lbsize )
{
    u_char *bptr = buffer;
    register ssize_t i;

    /*
     * Initialize the buffer with logical block data.
     */
    if (dip->di_fprefix_string) {
        register size_t pcount = 0, scount = lbsize;
	/*
	 * The lba is encoded after the prefix string.
	 */
	pcount = MIN((size_t)dip->di_fprefix_size, count);
	scount -= pcount;
        for (i = 0; (i+pcount+sizeof(lba)) <= count; ) {
            bptr += pcount;
            htos (bptr, lba, sizeof(lba));
            i += lbsize;
            bptr += scount;
            lba++;
        }
    } else {
        for (i = 0; (i+sizeof(lba)) <= count; ) {
            htos (bptr, lba, sizeof(lba));
            i += lbsize;
            bptr += lbsize;
            lba++;
        }
    }

    return (lba);
}

#if defined(TIMESTAMP)
/************************************************************************
 *									*
 * init_timestamp() - Initialize Data Buffer with a Timestamp.          *
 *									*
 * Description:								*
 *	This function places a timestamp in the first 4 bytes of each   *
 * data block.                                                          *
 *									*
 * Inputs:							        * 
 * 	dip = The device information pointer.			        *
 *	buffer = The data buffer to initialize.				*
 *	count = The data buffer size (in bytes).			*
 *	lbsize = The logical block size (in bytes).			*
 *									*
 * Outputs:	Returns the next lba to use.				*
 *									*
 ************************************************************************/
void
init_timestamp (
	dinfo_t		*dip,
	u_char		*buffer,
	size_t		count,
	u_int32		lbsize )
{
    u_char *bptr = buffer;
    register ssize_t i;
    register iotlba_t timestamp = (iotlba_t)time((time_t *)NULL);

    /*
     * Initialize the buffer with a timestamp (in seconds).
     */
    if (dip->di_fprefix_string) {
        register size_t pcount = 0, scount = lbsize;
	/*
	 * The timestamp is encoded after the prefix string.
	 */
	pcount = MIN((size_t)dip->di_fprefix_size, count);
	scount -= pcount;
        for (i = 0; (i+pcount+sizeof(timestamp)) <= count; ) {
            bptr += pcount;
            htos (bptr, (large_t)timestamp, sizeof(timestamp));
            i += lbsize;
            bptr += scount;
        }
    } else {
        for (i = 0; (i+sizeof(timestamp)) <= count; ) {
            htos (bptr, (large_t)timestamp, sizeof(timestamp));
            i += lbsize;
            bptr += lbsize;
        }
    }
    return;
}
#endif /* defined(TIMESTAMP) */

#if !defined(INLINE_FUNCS)
/*
 * Calculate the starting logical block number.
 */
u_int32
make_lba(
	struct dinfo	*dip,
	OFF_T		pos )
{
    if (pos == (OFF_T) 0) {
	return ((u_int32) 0);
    } else {
	return (pos / dip->di_lbdata_size);
    }
}

OFF_T
make_offset(struct dinfo *dip, u_int32 lba)
{
    return ((OFF_T)(lba * dip->di_lbdata_size));
}

/*
 * Calculate the starting lbdata block number.
 */
u_int32
make_lbdata(
	struct dinfo	*dip,
	OFF_T		pos )
{
    if (pos == (OFF_T) 0) {
	return ((u_int32) 0);
    } else {
	return (pos / dip->di_lbdata_size);
    }
}

#endif /* !defined(INLINE_FUNCS) */

u_int32
winit_lbdata(
	struct dinfo	*dip,
	OFF_T		pos,
	u_char		*buffer,
	size_t		count,
	u_int32		lba,
	u_int32		lbsize )
{
    if (dip->di_user_lbdata) {
	/* Using user defined lba, not file position! */
	return (init_lbdata (dip, buffer, count, lba, lbsize));
    } else if (pos == (OFF_T) 0) {
	return (init_lbdata (dip, buffer, count, (u_int32) 0, lbsize));
    } else {
	return (init_lbdata (dip, buffer, count, (u_int32)(pos / lbsize), lbsize));
    }
}

/*
 * init_iotdata() - Initialize Buffer with IOT test pattern.
 *
 * Description:
 *	This function takes the starting logical block address, and
 * inserts it every logical block size bytes.  The data pattern used
 * is the logical block with the constant 0x01010101 added every u_int.
 * Note: With multiple passes, the IOT constant is multiplied by the
 * pass count to generate uniqueness (unless disable=unique)
 *
 * Inputs:
 *	dip = The device information pointer.
 * 	buffer = The data buffer to initialize.
 * 	bcount = The data buffer size (in bytes).
 *	lba = The starting logical block address.
 *	lbsize = The logical block size (in bytes).
 *
 * Return Value:
 * 	Returns the next lba to use.
 * 
 * Note: If the count is smaller than sizeof(u_int32), then no lba is
 * encoded in the buffer.  Instead, we init odd bytes with ~0.
 */
u_int32	
init_iotdata (
	dinfo_t		*dip,
    	u_char		*buffer,
	size_t		bcount,
	u_int32		lba,
	u_int32		lbsize )
{
    register ssize_t count = (ssize_t)bcount;
    register u_int32 lba_pattern;
    /* IOT pattern initialization size. */
    register int iot_icnt = sizeof(lba_pattern);
    register int i;

    if (lbsize == 0) return (lba);
    dip->di_pattern_bufptr = buffer;

    /*
     * If the prefix string is a multiple of an unsigned int,
     * we can initialize the buffer using 32-bit words, otherwise
     * we must do so a byte at a time which is slower (of course).
     *
     * Note: This 32-bit fill is possible since the pattern buffer
     * is known to be page aligned!
     *
     * Format: <prefix string><IOT pattern>...
     *
     * Also Note:  The prefix string is copied to the data buffer
     * by fill_buffer(), so don't be mislead by this code.  The
     * IOT pattern bytes is adjusted for the sizeof(prefix_string).
     */
    if (count < iot_icnt) {
        init_buffer(dip, dip->di_pattern_bufptr, count, ~0);
    } else if (dip->di_fprefix_string && (dip->di_fprefix_size & (iot_icnt-1))) {
        register u_char *bptr = dip->di_pattern_bufptr;
        /*
         * Initialize the buffer with the IOT test pattern.
         */
        while ( (count > 0) && (count >= (ssize_t)sizeof(lba)) ) {
	    int adjust;
            /*
             * Process one lbsize'd block at a time.
             *
             * Format: <optional prefix><lba><lba data>...
             */
	    if (dip->di_fprefix_string) {
		size_t pcount = copy_prefix (dip, (u_char *)bptr, count);
		bptr += pcount;
		count -= pcount;
	    }
            lba_pattern = lba++;
            for (i = (lbsize - dip->di_fprefix_size);
		 ( (i > 0) && (count >= iot_icnt) ); ) {
#if _BIG_ENDIAN_
                init_swapped(dip, bptr, iot_icnt, lba_pattern);
#else /* !_BIG_ENDIAN_ */
                init_buffer(dip, bptr, iot_icnt, lba_pattern);
#endif /* _BIG_ENDIAN_ */
		lba_pattern += dip->di_iot_seed_per_pass;
		/* Adjust counts, but not too many! */
		adjust = MIN(i, iot_icnt);
                i -= adjust;
                bptr += adjust;
                count -= adjust;
            }
        }
        /* Handle any residual count here! */
        if (count && (count < iot_icnt)) {
	    //Printf("#1: Residual count is %d, lba_pattern = %04x\n",  count, lba_pattern);
            //init_buffer(dip, bptr, count, ~0);
            init_buffer(dip, (u_char *)bptr, count, lba_pattern);
        }
    } else {
        register int wperb; /* words per lbsize'ed buffer */
        register u_int32 *bptr;

        wperb = ( (lbsize - dip->di_fprefix_size) / iot_icnt);
        bptr = (u_int32 *)dip->di_pattern_bufptr;

        /*
         * Initialize the buffer with the IOT test pattern.
         */
        while ( (count > 0) && (count >= iot_icnt) ) {
	    /*
	     * Insert the prefix, if there is one.
	     */
	    if (dip->di_fprefix_string) {
		size_t pcount = copy_prefix (dip, (u_char *)bptr, count);
		bptr += (pcount / iot_icnt);
		count -= pcount;
	    }
            lba_pattern = lba++;
            for (i = 0; (i < wperb) && (count >= iot_icnt); i++) {
#if _BIG_ENDIAN_
                init_swapped(dip, (u_char *)bptr++, iot_icnt, lba_pattern);
#else /* !_BIG_ENDIAN_ */
                *bptr++ = lba_pattern;
#endif /* _BIG_ENDIAN_ */
		lba_pattern += dip->di_iot_seed_per_pass;
                count -= iot_icnt;
            }
        }
        /* Handle any residual count here! */
        if (count && (count < iot_icnt)) {
	    //Printf("#2: Residual count is %d, lba_pattern = %04x\n",  count, lba_pattern);
            //init_buffer(dip, (u_char *)bptr, count, ~0);
            init_buffer(dip, (u_char *)bptr, count, lba_pattern);
        }
    }
    return (lba);
}

/************************************************************************
 *									*
 * init_padbytes() - Initialize pad bytes at end of data buffer.	*
 *									*
 * Inputs:	buffer = Pointer to start of data buffer.		*
 *		offset = Offset to where pad bytes start.		*
 *		pattern = Data pattern to init buffer with.		*
 *									*
 * Return Value:							*
 *		Void.							*
 *									*
 ************************************************************************/
void
init_padbytes (	u_char		*buffer,
		size_t		offset,
		u_int32		pattern )
{
    size_t i;
    u_char *bptr;
    union {
	u_char pat[sizeof(u_int32)];
	u_int32 pattern;
    } p;

    p.pattern = pattern;
    bptr = buffer + offset;
    for (i = 0; i < PADBUFR_SIZE; i++) {
	*bptr++ = p.pat[i & (sizeof(u_int32) - 1)];
    }
}

/*
 * copy_prefix() - Copy Prefix String to Buffer.
 *
 * Inputs:
 *	dip = The device information pointer.
 *	buffer = Pointer to buffer to copy prefix.
 *	bcount = Count of remaining buffer bytes.
 *
 * Outputs:
 *	Returns number of prefix bytes copied.
 */
static size_t
copy_prefix( dinfo_t *dip, u_char *buffer, size_t bcount )
{
    size_t pcount;

    pcount = MIN((size_t)dip->di_fprefix_size, bcount);
    (void)memcpy(buffer, dip->di_fprefix_string, pcount);
    return (pcount);
}

/*
 * verify_prefix() - Verify Buffer with Prefix String.
 *
 * Inputs:
 *	dip = The device information pointer.
 *	buffer = Address of buffer to verify.
 *	bcount = The full buffer count.
 *	bindex = The index into the buffer.
 *	pcount = Pointer to return prefix count verified.
 *
 * Outputs:
 *	pcount gets the prefix string count verified.
 *	Return value is Success or Failure.
 */
int
verify_prefix( struct dinfo *dip, u_char *buffer, size_t bcount, int bindex, size_t *pcount )
{
    register u_char *bptr = buffer;
    register u_char *pstr = (u_char *)dip->di_fprefix_string;
    register size_t count;
    register size_t i;
    int status = SUCCESS;

    count = MIN((size_t)dip->di_fprefix_size, (bcount - bindex));

    for (i = 0; (i < count); i++, bptr++, pstr++) {
	if (*bptr != *pstr) {
	    size_t dump_size;
	    ReportCompareError (dip, bcount, (bindex + i), *pstr, *bptr);
	    Fprintf ("Mismatch of data pattern prefix: '%s'\n", dip->di_fprefix_string);
	    /* expected */
	    dump_size = CalculateDumpSize (dip, dip->di_fprefix_size);
	    dump_buffer (dip, prefix_str, (u_char *)dip->di_fprefix_string,
				pstr, dump_size, dip->di_fprefix_size, TRUE);
	    /* received */
#if defined(TIMESTAMP)
            if (dip->di_timestamp_flag) {
                display_timestamp(dip, buffer+count);
            }
#endif /* defined(TIMESTAMP) */
	    dump_size = CalculateDumpSize (dip, bcount);
	    dump_buffer (dip, data_str, buffer, bptr, dump_size, bcount, FALSE);
	    status = FAILURE;
            (void)ExecuteTrigger(dip, "miscompare");
	    break;
	}
    }
    *pcount = count;
    return (status);
}

/************************************************************************
 *									*
 * verify_buffers() - Verify Data Buffers.				*
 *									*
 * Description:								*
 *	Simple verification of two data buffers.			*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *		dbuffer = Data buffer to verify with.			*
 *		vbuffer = Verification buffer to use.			*
 *		count = The number of bytes to compare.			*
 *									*
 * Outputs:	Returns SUCCESS/FAILURE = Data Ok/Compare Error.	*
 *									*
 ************************************************************************/
int
verify_buffers(	struct dinfo	*dip,
		u_char		*dbuffer,
		u_char		*vbuffer,
		size_t		count )
{
    u_int32 i;
    u_char *dptr = dbuffer;
    u_char *vptr = vbuffer;

    for (i = 0; (i < count); i++, dptr++, vptr++) {
	if (*dptr != *vptr) {
	    size_t dump_size = CalculateDumpSize (dip, count);
	    ReportCompareError (dip, count, i, *dptr, *vptr);
	    /* expected */
	    dump_buffer (dip, data_str, dbuffer, dptr, dump_size, count, TRUE);
	    /* received */
#if defined(TIMESTAMP)
            if (dip->di_timestamp_flag) {
                display_timestamp(dip, vbuffer);
            }
#endif /* defined(TIMESTAMP) */
	    dump_buffer (dip, verify_str, vbuffer, vptr, dump_size, count, FALSE);
            (void)ExecuteTrigger(dip, "miscompare");
	    return (FAILURE);
	}
    }
    return (SUCCESS);
}

/************************************************************************
 *									*
 * verify_lbdata() - Verify Logical Block Address in Buffer.            *
 *									*
 * Description:								*
 *	Note: This function is used during read-after-write tests.      *
 *									*
 * Inputs:	dip = The device information pointer.			*
 *		dbuffer = Data buffer to verify with.			*
 *		vbuffer = Verification buffer to use.			*
 *		count = The number of bytes to compare.			*
 *              lba = Pointer to return last lba verified.              *
 *									*
 * Outputs:	Returns SUCCESS/FAILURE = lba Ok/Compare Error. 	*
 *									*
 ************************************************************************/
int
verify_lbdata(	struct dinfo	*dip,
		u_char		*dbuffer,
		u_char		*vbuffer,
		size_t		count,
		u_int32		*lba )
{
    u_int32 i, dlbn = 0, vlbn;
    u_char *dptr = dbuffer;
    u_char *vptr = vbuffer;
    int status = SUCCESS;

    /*
     * Note: With timestamps enabled, we overwrite the lba.
     */
    if (dip->di_timestamp_flag) { return (status); }
    for (i = 0; (i+sizeof(dlbn) <= count); i += dip->di_lbdata_size,
		 dptr += dip->di_lbdata_size, vptr += dip->di_lbdata_size) {
	if (dip->di_iot_pattern) {
	    dlbn = get_lbn(dptr);
	    vlbn = get_lbn(vptr);
	} else {
	    dlbn = (u_int32)stoh(dptr, sizeof(dlbn));
	    vlbn = (u_int32)stoh(vptr, sizeof(vlbn));
	}
	if (dlbn != vlbn) {
	    size_t dump_size = CalculateDumpSize (dip, count);
	    ReportLbdataError(dip, *lba, count, i, dlbn, vlbn);
	    /* expected */
	    dump_buffer (dip, data_str, dbuffer, dptr, dump_size, count, TRUE);
	    /* received */
	    dump_buffer (dip, verify_str, vbuffer, vptr, dump_size, count, FALSE);
	    status = FAILURE;
	    break;
	}
    }
    *lba = (dlbn + 1);
    return (status);
}

/************************************************************************
 *									*
 * verify_data() - Verify Data Pattern.					*
 *									*
 * Description:								*
 *	If a pattern_buffer exists, then this data is used to compare	*
 * the buffer instead of the pattern specified.				*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *		buffer = Pointer to data to verify.			*
 *		count = The number of bytes to compare.			*
 *		pattern = Data pattern to compare against.		*
 *		lba = Pointer to starting logical block address.	*
 *									*
 * Outputs:	Returns SUCCESS/FAILURE = Data Ok/Compare Error.	*
 *		lba gets updated with the next lba to verify with.	*
 *									*
 ************************************************************************/
int
verify_data (	struct dinfo	*dip,
		u_char		*buffer,
		size_t		count,
		u_int32		pattern,
		u_int32		*lba )
{
    bool check_lba = (dip->di_iot_pattern || (dip->di_lbdata_flag && dip->di_lbdata_size));
    int status;

    /*
     * I hate to duplicate code, but the smaller functions
     * optimize better and give *much* better performance.
     */
    if ( !check_lba && !dip->di_fprefix_string ) {
	status = verify_data_normal(dip, buffer, count, pattern);
    } else if ( !check_lba && dip->di_fprefix_string ) {
	status = verify_data_prefix(dip, buffer, count, pattern);
    } else {
	status = verify_data_with_lba(dip, buffer, count, pattern, lba);
    }
    if ( (status != SUCCESS)   && dip->di_retryDC_flag &&
	 dip->di_random_access && !dip->di_retrying) {
	(void)verify_reread(dip, buffer, count, pattern, lba);
    }
    return (status);
}

/*
 * verify_reread() - Verify Data after Rereading with DIO.
 *
 * Description:
 *	If a pattern_buffer exists, then this data is used to compare
 * the buffer instead of the pattern specified.
 *
 * Inputs:
 *	dip = The device information pointer.
 *	buffer = Pointer to data to verify.
 *	count = The number of bytes to compare.
 *	pattern = Data pattern to compare against.
 *	lba = Pointer to starting logical block address.
 *
 * Return Value:
 *	Returns SUCCESS/FAILURE = Data Ok/Compare Error.
 *	lba gets updated with the next lba to verify with.
 */
int
verify_reread(
    struct dinfo	*cdip,
    u_char		*buffer,
    size_t		bcount,
    u_int32		pattern,
    u_int32		*lba )
{
    struct dinfo	*dip;
    u_char		*reread_buffer;
    OFF_T		record_offset;
    ssize_t		count;
    int			oflags;
    int			retries = 0;
    bool		saved_aio_flag;
    bool		saved_dio_flag;
    bool		saved_rDebugFlag;
    int			status;

    Fprint ("\n");
    if ( (cdip->di_dtype->dt_dtype == DT_REGULAR) ||
	 (cdip->di_dtype->dt_dtype == DT_BLOCK) ) {
	Fprintf("Rereading and verifying record data using Direct I/O...\n");
    } else {
	Fprintf("Rereading and verifying record data...\n");
    }
    cdip->di_retrying = TRUE;

    /*
     * We have a bit of work to reread the data.
     */
    dip = Malloc(sizeof(*dip));
    reread_buffer = malloc_palign(bcount, 0);
    *dip = *cdip;	 /* Copy current device information. */
    dip->di_fd = NoFd;
    if (dip->di_aio_flag || dip->di_mmap_flag) {
	record_offset = dip->di_offset - bcount;
    } else {
	record_offset = get_position(cdip) - bcount;
    }

#if defined(WIN32)
    oflags = GENERIC_READ;
#else /* !defined(WIN32) */
    oflags = O_RDONLY;
#endif /* !defined(WIN32) */

    /*
     * Enable direct I/O for our reread (bypass buffer cache).
     */
    saved_aio_flag = dip->di_aio_flag;
    saved_dio_flag = dip->di_dio_flag;
    dip->di_aio_flag = FALSE;	/* Avoid overlapped attribute Windows. */
    /*
     * Only enable Direct I/O for regular files, not raw disks!
     */
    if ( (dip->di_dtype->dt_dtype == DT_REGULAR) ||
	 (dip->di_dtype->dt_dtype == DT_BLOCK) ) {
	/*
	 * For Linux and Windows DIO, the buffer, count, and offset must be
	 * block aligned/sized to avoid errors:
	 *  Linux:    dt: 'read', errno = 22 - Invalid argument
	 *  Windows: 'SetFilePointer', errno = 87 - The parameter is incorrect.
	 *  Others? Solaris, FreeBSD, etc?
	 * OS's like Tru64 and HP-UX have special fixup code so Ok.
	 */
#if defined(__linux__) || defined(WIN32)
	if ( (bcount % BLOCK_SIZE) ||
	     (record_offset % BLOCK_SIZE) ) {
	    dip->di_dio_flag = FALSE;
	    Fprintf("WARNING: Count or offset is NOT block aligned, so DIO is disabled!\n");
	} else 
#endif /* defined(__linux__) || defined(WIN32) */
	{
	    dip->di_dio_flag = TRUE;    /* Valid for Solaris & native Windows. */
#if defined(O_DIRECT)
	    oflags |= O_DIRECT;		/* Direct disk access. */
#endif
	}
#if defined(__linux__)
    } else if (dip->di_dtype->dt_dtype == DT_DISK) {
	  /* Linux disks are block devices, grrrr! */
	  oflags |= O_DIRECT;		/* Bypass the buffer cache, please! */
#endif /* defined(__linux__) */
    }

    /*
     * Open the device/file (again)
     * Seek to the failing offset
     * Reread the record data
     * Verify against previous read data (verify == write error)
     * Verify against expected data (verify == read error)
     */
    status = (*dip->di_funcs->tf_reopen_file)(dip, oflags);
    if (status != SUCCESS) terminate(status);
    saved_rDebugFlag = dip->di_rDebugFlag;
    dip->di_rDebugFlag = TRUE;		/* Report our seek info. */

    do {
	if ( (dip->di_offset = set_position(dip, record_offset, FALSE)) != record_offset) {
	    Fprintf("Seek failed, exiting...\n");
	    terminate(FAILURE);
	}
	report_record(dip, (dip->di_files_read + 1), (dip->di_records_read + 1),
			   (record_offset / dip->di_dsize), record_offset,
			   READ_MODE, reread_buffer, bcount);
	count = read_record(dip, reread_buffer, bcount, bcount, &status);
	if (status == FAILURE) terminate(status);

	/*
	 * Now, compare reread data to previous read, and if that
	 * fails, verify against the expect pattern data, to help
	 * make a decision on where the failure occurred.
	 */
	dip->di_pattern_bufptr = dip->di_saved_pattern_ptr;
	if (memcmp(buffer, reread_buffer, count) == 0) {
	    Fprintf("Reread data matches previous data read, possible write failure!\n");
	} else {
	    status = (*dip->di_funcs->tf_verify_data)(dip, reread_buffer, count, pattern, lba);
	    if (status == SUCCESS) {
		Fprintf("Reread data matches the expected data, possible read failure!\n");
	    } else {
		Fprintf("Reread data does NOT match previous data or expected data!\n");
	    }
	}
	if (dip->di_loop_on_error) {
	    retries++;
	    Fprintf("Delaying %u seconds after retry %d...\n", (dip->di_retry_delay * retries), retries);
	    SleepSecs( (dip->di_retry_delay * retries) );
	}
    } while ( dip->di_loop_on_error );

    /*
     * Ok, we're done... cleanup!
     */
    if ( (*dip->di_funcs->tf_close)(dip) != SUCCESS) terminate(FAILURE);
    cdip->di_retrying = FALSE;
    dip->di_aio_flag = saved_aio_flag;
    dip->di_dio_flag = saved_dio_flag;
    dip->di_rDebugFlag = saved_rDebugFlag;
    free_palign(reread_buffer);
    free(dip); dip = NULL;
    /*
     * Display a re-read command line, *if* parameters allow us to do so!
     *
     * Cannot do:
     *	pattern files (needs to save pattern data for this record)
     *	pattern strings (special case IOT text added here)
     *	non-modulo device sizes (pattern data usually wraps)
     */
    dip = cdip;
    if ( dip->di_iot_pattern					||
	 ( !dip->di_pattern_file && !dip->di_pattern_string )	&&
	 ( (bcount % dip->di_dsize) == 0) ) {
	char		str[STRING_BUFFER_SIZE];
	char		*sbp = str;
	Fprintf("Command line to re-read the corrupted data:\n");
	sbp += Sprintf(str, "-> %s if=%s bs=%u count=1 position=" FUF ,
		       dtpath, dip->di_dname, bcount, record_offset);
	if (dip->di_fprefix_string) {
	    sbp += Sprintf(sbp, " prefix=\"%s\"", dip->di_fprefix_string);
	}
	if (dip->di_iot_pattern) {
	    sbp += Sprintf(sbp, " pattern=iot");
	    if (dip->di_iot_seed_per_pass != IOT_SEED) {
		sbp += Sprintf(sbp, " iotseed=0x%08x", dip->di_iot_seed_per_pass);
	    }
	} else if (dip->di_incr_pattern) {
	    sbp += Sprintf(sbp, " pattern=incr");
	} else {
	    sbp += Sprintf(sbp, " pattern=0x%08x", pattern);
	}
	if (dip->di_lbdata_flag && dip->di_timestamp_flag) {
	    sbp += Sprintf(sbp, " enable=lbdata,timestamp");
	} else if (dip->di_lbdata_flag) {
	    sbp += Sprintf(sbp, " enable=lbdata");
	} else if (dip->di_timestamp_flag) {
	    sbp += Sprintf(sbp, " enable=timestamp");
	}
	if ( (dip->di_dtype->dt_dtype == DT_REGULAR) ||
	     (dip->di_dtype->dt_dtype == DT_BLOCK) ) {
	    sbp += Sprintf(sbp, " flags=direct");
	}
	if (dip->di_dump_limit != BLOCK_SIZE) {
	    sbp += Sprintf(sbp, " dlimit=%u", dip->di_dump_limit);
	}
	if (dip->di_dsize != BLOCK_SIZE) {
	    sbp += Sprintf(sbp, " dsize=%u", dip->di_dsize);
	}
	Fprintf("%s\n", str);
    }
    return (status);
}

static int
verify_data_normal(
	struct dinfo	*dip,
	u_char		*buffer,
	size_t		bcount,
	u_int32		pattern )
{
#if defined(TIMESTAMP)
    u_char *tptr = NULL;
#endif /* defined(TIMESTAMP) */
    register size_t i = 0;
    register u_char *vptr = buffer;
    register u_char *pptr = dip->di_pattern_bufptr;
    register u_char *pend = dip->di_pattern_bufend;
    register size_t count = bcount;
    bool error = FALSE;
    int status = SUCCESS;

    dip->di_saved_pattern_ptr = pptr;

    while ( (i < count) ) {
#if defined(TIMESTAMP)
        /*
         * Skip the timestamp (if enabled).
         */
        if (dip->di_timestamp_flag && ((i % dip->di_lbdata_size) == 0)) {
            int p;
            i += sizeof(iotlba_t);
	    tptr = vptr;
            vptr += sizeof(iotlba_t);
            for (p = 0; (p < (int)sizeof(iotlba_t)); p++) {
                if (++pptr == pend) pptr = dip->di_pattern_buffer;
            }
        }
	if (i >= count) break;
#endif /* defined(TIMESTAMP) */
	if (*vptr != *pptr) {
	    error = TRUE;
	    ReportCompareError (dip, count, i, *pptr, *vptr);
	    break;
	} else {
	    i++, pptr++, vptr++;
	    if (pptr == pend) pptr = dip->di_pattern_buffer;
	}
    }
    if (error) {
	if (dip->di_dump_flag) {
	    size_t dump_size = CalculateDumpSize (dip, count);
	    if (dip->di_pattern_buffer) {
		size_t pdump_size = (dump_size < dip->di_patbuf_size)
					? dump_size : dip->di_patbuf_size;
		/* expected */
		dump_buffer (dip, pattern_str, dip->di_pattern_buffer, pptr,
					pdump_size, dip->di_patbuf_size, TRUE);
	    }
	    /* received */
#if defined(TIMESTAMP)
            if (dip->di_timestamp_flag) {
                display_timestamp(dip, tptr);
            }
#endif /* defined(TIMESTAMP) */
	    dump_buffer (dip, data_str, buffer, vptr, dump_size, count, FALSE);
	}
	if (!dip->di_retrying) {
	    (void)ExecuteTrigger(dip, "miscompare");
	}
	status = FAILURE;
    }
    dip->di_pattern_bufptr = pptr;
    return (status);
}

static int
verify_data_prefix(
	struct dinfo	*dip,
	u_char		*buffer,
	size_t		bcount,
	u_int32		pattern )
{
#if defined(TIMESTAMP)
    u_char *tptr = NULL;
#endif /* defined(TIMESTAMP) */
    register size_t i = 0;
    register u_char *vptr = buffer;
    register u_char *pptr = dip->di_pattern_bufptr;
    register u_char *pend = dip->di_pattern_bufend;
    register size_t count = bcount;
    bool error = FALSE;
    int status = SUCCESS;

    dip->di_saved_pattern_ptr = pptr;

    while ( (i < count) ) {
	/*
	 * Verify the prefix string (if any).
	 */
	if (dip->di_fprefix_string && ((i % dip->di_lbdata_size) == 0)) {
	    size_t pcount;
	    status = verify_prefix (dip, vptr, count, i, &pcount);
	    if (status == FAILURE) return (status);
	    i += pcount;
	    vptr += pcount;
#if defined(TIMESTAMP)
	    /*
	     * Skip the timestamp (if enabled).
	     */
	    if (dip->di_timestamp_flag) {
		int p;
		i += sizeof(iotlba_t);
		tptr = vptr;
		vptr += sizeof(iotlba_t);
		for (p = 0; (p < (int)sizeof(iotlba_t)); p++) {
		    if (++pptr == pend) pptr = dip->di_pattern_buffer;
		}
	    }
#endif /* defined(TIMESTAMP) */
	    continue;
	}
	if (*vptr != *pptr) {
	    error = TRUE;
	    ReportCompareError (dip, count, i, *pptr, *vptr);
	    break;
	} else {
	    i++, pptr++, vptr++;
	    if (pptr == pend) pptr = dip->di_pattern_buffer;
	}
    }
    if (error) {
	if (dip->di_dump_flag) {
	    size_t dump_size = CalculateDumpSize (dip, count);
	    if (dip->di_pattern_buffer) {
		size_t pdump_size = (dump_size < dip->di_patbuf_size)
					? dump_size : dip->di_patbuf_size;
		/* expected */
		dump_buffer (dip, pattern_str, dip->di_pattern_buffer, pptr,
					pdump_size, dip->di_patbuf_size, TRUE);
	    }
	    /* received */
#if defined(TIMESTAMP)
            if (dip->di_timestamp_flag) {
                display_timestamp(dip, tptr);
            }
#endif /* defined(TIMESTAMP) */
	    dump_buffer (dip, data_str, buffer, vptr, dump_size, count, FALSE);
	}
	if (!dip->di_retrying) {
	    (void)ExecuteTrigger(dip, "miscompare");
	}
	status = FAILURE;
    }
    dip->di_pattern_bufptr = pptr;
    return (status);
}

static int
verify_data_with_lba(
	struct dinfo	*dip,
	u_char		*buffer,
	size_t		bcount,
	u_int32		pattern,
	u_int32		*lba )
{
    register size_t i = 0;
    register u_char *vptr = buffer;
    register u_char *pptr = dip->di_pattern_bufptr;
    register u_char *pend = dip->di_pattern_bufend;
    register size_t count = bcount;
    register u_int32 lbn, vlbn = *lba;
    bool error = FALSE, lbn_error = FALSE;
    int status = SUCCESS;

    dip->di_saved_pattern_ptr = pptr;

    /*
     * This optimization reduces IOT pattern compares by roughly 1/2
     * the CPU load. If it fails, we'll fall through to the previous
     * logic, which then determines if it's the prefix, LBA, or the
     * data which is incorrect. Sadly, the code below induces too
     * much overhead. It's time to implement block tags!
     */
    if (dip->di_iot_pattern) {
	/* TODO: Optimize this memcmp() for timestamp as well! */
        if (memcmp(pptr, vptr, count) == 0) {
	    *lba += (count / dip->di_lbdata_size);
	    return (status);
	}
    }
    while ( (i < count) ) {
	/*
	 * Handle IOT and Lbdata logical block checks first.
	 */
	if ( ((i % dip->di_lbdata_size) == 0) ) {
	    /*
	     * Verify the prefix string prior to encoded lba's.
	     */
	    if (dip->di_fprefix_string) {
		size_t pcount;
		/*
		 * For IOT data, the prefix is in the pattern buffer. 
		 * For lbdata, the prefix is NOT in the pattern buffer.
		 */
		status = verify_prefix (dip, vptr, count, i, &pcount);
		if (status == FAILURE) {
		    if (dip->di_iot_pattern) {
			analyze_iot_data(dip, dip->di_pattern_bufptr, buffer, bcount);
			display_iot_data(dip, dip->di_pattern_bufptr, buffer, bcount);
		    }
		    return (status);
		}
		if (dip->di_iot_pattern) pptr += pcount;
		vptr += pcount;
		if ( (i += pcount) == count) continue;
	    }
	    if ( (i+sizeof(lbn) <= count) ) {
		if (dip->di_iot_pattern) {
		    vlbn = get_lbn(pptr);
		    lbn = get_lbn(vptr);
		} else {
		    lbn = (u_int32)stoh(vptr, sizeof(lbn));
		}
	        if (!dip->di_timestamp_flag && (lbn != vlbn)) {
		    error = lbn_error = TRUE;
		    ReportLbdataError (dip, *lba, count, i, vlbn, lbn);
		    break;
		} else {
		    int size;
		    vlbn++;
		    i += sizeof(lbn);
		    vptr += sizeof(lbn);
		    /* Skip past pattern bytes, handling wrapping. */
		    size = sizeof(lbn);
		    while (size--) {
			pptr++;
			if (pptr == pend) pptr = dip->di_pattern_buffer;
		    }
		}
		continue;
	    }
	}

	if (*vptr != *pptr) {
	    error = TRUE;
	    ReportCompareError (dip, count, i, *pptr, *vptr);
	    break;
	} else {
	    i++, pptr++, vptr++;
	    if (pptr == pend) pptr = dip->di_pattern_buffer;
	}
    }

    if (error) {
	if (dip->di_dump_flag) {
	    size_t dump_size = CalculateDumpSize (dip, count);
            if (lbn_error && !dip->di_iot_pattern) {
                u_int32 elbn = vlbn; /* Can't take address of register. */
                /* expected - yep, real ugly, but gotta be correct! */
                dump_buffer (dip, lba_str, (u_char *)&elbn, (u_char *)&elbn,
                             sizeof(elbn), sizeof(elbn), TRUE); 
            } else if (dip->di_pattern_buffer) {
		size_t pdump_size = (dump_size < dip->di_patbuf_size)
					? dump_size : dip->di_patbuf_size;
		/* expected */
		dump_buffer (dip, pattern_str, dip->di_pattern_buffer, pptr,
					pdump_size, dip->di_patbuf_size, TRUE);
	    }
	    /* received */
#if defined(TIMESTAMP)
            if (dip->di_timestamp_flag) {
                display_timestamp(dip, buffer);
            }
#endif /* defined(TIMESTAMP) */
	    dump_buffer (dip, data_str, buffer, vptr, dump_size, count, FALSE);
	}
	if (!dip->di_retrying) {
	    (void)ExecuteTrigger(dip, "miscompare");
	}
	if (dip->di_iot_pattern) {
	    analyze_iot_data(dip, dip->di_pattern_bufptr, buffer, bcount);
	    display_iot_data(dip, dip->di_pattern_bufptr, buffer, bcount);
	}
	status = FAILURE;
    }
    dip->di_pattern_bufptr = pptr;
    *lba = vlbn;		/* Pass updated lba back to caller. */
    return (status);
}

#define CA_FIELD_WIDTH "%32.32s"

void
report_bad_sequence(dinfo_t *dip, int start, int length, OFF_T offset)
{
    OFF_T pos = (offset + ((start-1) * dip->di_lbdata_size));
    Fprint(CA_FIELD_WIDTH "%d\n",
	  "Start of corrupted blocks: ", start);
    Fprint(CA_FIELD_WIDTH "%d (%d bytes)\n",
	  "Length of corrupted blocks: ", length, (length * dip->di_lbdata_size));
    Fprint(CA_FIELD_WIDTH FUF " (lba %u)\n",
	   "Corrupted blocks file offset: ", pos, (u_int32)(pos / dip->di_lbdata_size));
    return;
}

void
report_good_sequence(dinfo_t *dip, int start, int length, OFF_T offset)
{
    OFF_T pos = (offset + ((start-1) * dip->di_lbdata_size));
    Fprint(CA_FIELD_WIDTH "%d\n",
	  "Start of good blocks: ", start);
    Fprint(CA_FIELD_WIDTH "%d (%d bytes)\n",
	  "Length of good blocks: ", length, (length * dip->di_lbdata_size));
    Fprint(CA_FIELD_WIDTH FUF " (lba %u)\n",
	   "Good blocks file offset: ", pos, (u_int32)(pos / dip->di_lbdata_size));
    return;
}

void
analyze_iot_data(dinfo_t *dip, u_char *pbuffer, u_char *vbuffer, size_t bcount)
{
    register u_char *pptr = pbuffer;
    register u_char *vptr = vbuffer;
    register size_t count = bcount;
    int bad_blocks = 0, good_blocks = 0;
    int bad_start = 0,  good_start = 0;
    int zero_blocks = 0;
    u_int32 block = 1;
    int blocks = (count / dip->di_lbdata_size);
    OFF_T record_offset;

    /*
     * TODO: Save starting offset in the dip!
     */
    if (dip->di_aio_flag || dip->di_mmap_flag) {
	record_offset = dip->di_offset - bcount;
    } else {
	record_offset = get_position(dip) - bcount;
    }

    Fprint("\n");
    Fprint("Analyzing IOT Record Data: (Note: Block #'s are relative to start of record!)\n");
    Fprint("\n");
    Fprint(CA_FIELD_WIDTH "%d\n",
	   "IOT block size: ", dip->di_lbdata_size);
    Fprint(CA_FIELD_WIDTH "%d (%u bytes)\n",
	  "Total number of blocks: ", blocks, count);
    Fprint(CA_FIELD_WIDTH "0x%08x (pass %u)\n",
	  "Current IOT seed value: ", dip->di_iot_seed_per_pass, (dip->di_iot_seed_per_pass / IOT_SEED));
    if (dip->di_iot_seed_per_pass != IOT_SEED) {
	Fprint(CA_FIELD_WIDTH "0x%08x (pass %u)\n",
	      "Previous IOT seed value: ", (dip->di_iot_seed_per_pass - IOT_SEED),
	       ((dip->di_iot_seed_per_pass - IOT_SEED) / IOT_SEED));
    }

    /*
     * Compare one lbdata sized block at a time.
     */
    while (blocks) {
	int result = 0;
	if (dip->di_timestamp_flag) {
	    if (dip->di_fprefix_size) {
		result = memcmp(pptr, vptr, dip->di_fprefix_size);
	    }
	    if (result == 0) {
		int doff = (dip->di_fprefix_size + sizeof(iotlba_t));
		result = memcmp( (pptr + doff), (vptr + doff),
				 (dip->di_lbdata_size - doff) );
	    }
	} else {
	    result = memcmp(pptr, vptr, dip->di_lbdata_size);
	}
	if (result == 0) {
	    good_blocks++;
	    if (good_start == 0) {
		good_start = block;
	    }
	    if (bad_start) {
		report_bad_sequence(dip, bad_start, (block - bad_start), record_offset);
		bad_start = 0;
	    }
	} else {
	    u_int32 i;
	    bad_blocks++;
	    if (bad_start == 0) {
		bad_start = block;
	    }
	    for (i = 0; (i < dip->di_lbdata_size); i++) {
		if (vptr[i] != '\0') {
		    break;
		}
	    }
	    if (i == dip->di_lbdata_size) {
		zero_blocks++;
	    }
	    if (good_start) {
		report_good_sequence(dip, good_start, (block - good_start), record_offset);
		good_start = 0;
	    }
	}
	block++; blocks--;
	pptr += dip->di_lbdata_size;
	vptr += dip->di_lbdata_size;
    }
    if (bad_start) {
	report_bad_sequence(dip, bad_start, (block - bad_start), record_offset);
	bad_start = 0;
    }
    if (good_start) {
	report_good_sequence(dip, good_start, (block - good_start), record_offset);
	good_start = 0;
    }
    Fprint(CA_FIELD_WIDTH "%d\n",
	  "Number of corrupted blocks: ", bad_blocks);
    Fprint(CA_FIELD_WIDTH "%d\n",
	  "Number of good blocks found: ", good_blocks);
    Fprint(CA_FIELD_WIDTH "%d\n",
	  "Number of zero blocks found: ", zero_blocks);
    return;
}

#define BITS_PER_BYTE		8
#define BYTES_PER_LINE		16
#define BYTE_EXPECTED_WIDTH	55
#define WORD_EXPECTED_WIDTH	43

void
display_iot_block(dinfo_t *dip, int block, OFF_T block_offset, u_char *pptr, u_char *vptr, size_t bsize)
{
    char str[LARGE_BUFFER_SIZE];
    char astr[LARGE_BUFFER_SIZE];
    register char *sbp = str;
    register char *abp = astr;
    u_char *tend = NULL, *tptr = NULL;
    int aprefix_size = 0;
    int boff = 0, i;
    int match, width;
    register int bytes_per_line;
    int expected_width;
    u_int32 expected_lbn, received_lbn;
    size_t limit = MIN(bsize,dip->di_dump_limit);
    u_int32 received_word0, received_word1, received_iot_seed;

    Fprint("\n");
    Fprint(CA_FIELD_WIDTH "%u\n", "Record block: ", block);
    Fprint(CA_FIELD_WIDTH FUF " (lba %u)\n", "Record block offset: ",
	   block_offset, (u_int32)(block_offset / dip->di_lbdata_size));

    if (dip->di_fprefix_size) {
	int result = 0;
	unsigned char byte;
	aprefix_size = strlen(dip->di_fprefix_string);
	result = memcmp(pptr, vptr, dip->di_fprefix_size);
	Fprint(CA_FIELD_WIDTH "%s\n", "Prefix string compare: ",
	       (result == 0) ? "correct" : "incorrect");
	if (result != 0) {
	    int printable = 0;
	    Fprint(CA_FIELD_WIDTH "%s\n", "Expected prefix string: ", pptr);
	    Fprint(CA_FIELD_WIDTH, "Received prefix string: ");
	    abp = astr;
	    /* Ensure received prefix string is printable! */
	    for (i = 0; (i < aprefix_size); i++) {
		byte = vptr[i];
		*abp++ = isprint((int)byte) ? (char)byte : ' ';
		if ( isprint((int)byte) ) {
		    printable++;
		}
	    }
	    if (printable) {
		*abp = '\0';
		Fprint("%s\n", astr);
	    } else {
		Fprint("<non-printable string>\n");
	    }
	}
    }

    expected_lbn = get_lbn((pptr + dip->di_fprefix_size));
    received_word0 = get_lbn( (vptr + dip->di_fprefix_size + (sizeof(received_lbn) * 1)) );
    received_word1 = get_lbn( (vptr + dip->di_fprefix_size + (sizeof(received_lbn) * 2)) );

    if (dip->di_timestamp_flag) {
	time_t seconds;
	tptr = (vptr + dip->di_fprefix_size);
	tend = (tptr + sizeof(iotlba_t));
	seconds = (time_t)stoh((vptr + dip->di_fprefix_size), sizeof(iotlba_t));
	Fprint(CA_FIELD_WIDTH "0x%08x\n", "Block timestamp value: ", get_lbn( (vptr + dip->di_fprefix_size) ));
	/* Note: ctime() appends newline automatically! */
	Fprint(CA_FIELD_WIDTH "%s", "Data block written on: ",
	       os_ctime(&seconds, dip->di_time_buffer, sizeof(dip->di_time_buffer)));
	/*
	 * Since timestamp overwrites the lba, calculate the seed and lba.
	 */
	received_iot_seed = (received_word1 - received_word0);
	received_lbn = (received_word0 - received_iot_seed);
    } else {
	received_lbn = get_lbn((vptr + dip->di_fprefix_size));
	received_word0 = get_lbn( (vptr + dip->di_fprefix_size + (sizeof(received_lbn) * 1)) );
	received_word1 = get_lbn( (vptr + dip->di_fprefix_size + (sizeof(received_lbn) * 2)) );
	received_iot_seed = (received_word0 - received_lbn);
    }
    Fprint(CA_FIELD_WIDTH "%u (0x%08x)\n", "Expected block number: ", expected_lbn, expected_lbn);
    Fprint(CA_FIELD_WIDTH "%u (0x%08x)\n", "Received block number: ", received_lbn, received_lbn);

    /*
     * Analyze the IOT data:
     * Steps:
     *  - Detect stale IOT data (most common case, past or future)
     * 	- Detect wrong IOT data (valid IOT data, but wrong block)
     * 	- Detect IOT data/seed anywhere within the data block.
     */
    if ( ((expected_lbn != received_lbn) ||
	  (dip->di_iot_seed_per_pass != received_iot_seed)) ) {
	/* Does this look like a valid IOT seed? */
	if ( (received_iot_seed && received_word0 && received_word1) &&
	     (received_word1 == (received_word0 + received_iot_seed)) &&
	     ((received_iot_seed % IOT_SEED) == 0) ) {
	    Fprint(CA_FIELD_WIDTH "%u\n",
		   "Data written during pass: ", (received_iot_seed / IOT_SEED));
	    Fprint(CA_FIELD_WIDTH "0x%08x (%s)\n",
		   "Received data is from seed: ", received_iot_seed,
		   (expected_lbn == received_lbn) ? "stale data" : "wrong data");
	} else {
	    /* Format: <optional prefix><lbn or timestamp><lbn + IOT_SEED>...*/
	    int doff = (dip->di_fprefix_size + sizeof(expected_lbn));
	    int seed_word = 1;
	    /* Loop through data looking for a valid IOT seed. */
	    for (; ((doff + sizeof(expected_lbn)) < bsize); doff += sizeof(expected_lbn) ) {
		received_word0 = get_lbn( (vptr + doff) );
		received_word1 = get_lbn( (vptr + doff + sizeof(expected_lbn)) );
		received_iot_seed = (received_word1 - received_word0);
		if ( (received_iot_seed && received_word0 && received_word1) &&
		     (received_iot_seed % IOT_SEED) == 0) {
		    Fprint(CA_FIELD_WIDTH "%u (0x%x) (word %u, zero based)\n",
			   "Seed detected at offset: ", doff, doff, (doff / sizeof(expected_lbn)));
		    Fprint(CA_FIELD_WIDTH "%u\n",
			   "Data written during pass: ", (received_iot_seed / IOT_SEED));
		    received_lbn = (received_word0 - (received_iot_seed * seed_word));
		    Fprint(CA_FIELD_WIDTH "%u (0x%08x)\n", "Calculated block number: ",
			   received_lbn, received_lbn);
		    /* Since part of the block is corrupt, always report wrong data. */
		    Fprint(CA_FIELD_WIDTH "0x%08x (%s)\n",
			   "Received data is from seed: ", received_iot_seed, "wrong data");
			   //(expected_lbn == received_lbn) ? "stale data" : "wrong data");
		    break; /* Stop upon 1st valid IOT data. */
		}
		seed_word++;
#if 0
		Fprint(CA_FIELD_WIDTH "0x%08x\n", "Seed word 0: ", received_word0);
		Fprint(CA_FIELD_WIDTH "0x%08x\n", "Seed word 1: ", received_word1);
		Fprint(CA_FIELD_WIDTH "0x%08x\n", "Difference: ", (received_word1 - received_word0));
		Fprint("offset = %d, seed word = %d\n", doff, seed_word);
#endif
	    }
	}
    }
    Fprint("\n");
    width = sprintf(sbp, "Byte Expected: address %p", pptr);
    sbp += width;
    if (dip->di_data_format == BYTE_FMT) {
	expected_width = BYTE_EXPECTED_WIDTH;
    } else {
	expected_width = WORD_EXPECTED_WIDTH;
    }
    while (width++ < expected_width) {
	sbp += sprintf(sbp, " ");
    }
    sbp += sprintf(sbp, "Received: address %p\n", vptr); 
    Fprint("%s", str);
    while (limit > 0) {
	sbp = str;
	bytes_per_line = MIN(bsize, BYTES_PER_LINE);
	if (dip->di_boff_format == DEC_FMT) {
	    sbp += sprintf(sbp, "%04d ", boff);
	} else {
	    sbp += sprintf(sbp, "%04x ", boff);
	}
	abp = NULL;
	if (aprefix_size && (boff < aprefix_size)) {
	    abp = astr;
	    abp += sprintf(abp, "     ");
	}
	/* Handle timestamp within this byte range. */
	if (tptr && (vptr < tend)) {
	    match = 0;
	    for (i = 0; (i < bytes_per_line); i++) {
		if ( ((vptr + i) >= tptr) &&
		     ((vptr + 1) < tend) ) {
		    continue; /* Skip the timestamp. */
		}
		if ( pptr[i] != vptr[i] ) {
		    match = 1;
		    break;
		}
	    }
	} else {
	    match = memcmp(pptr, vptr, bytes_per_line);
	}
	if (dip->di_data_format == BYTE_FMT) {
	    unsigned char byte;
	    for (i = 0; (i < bytes_per_line); i++) {
		byte = pptr[i];
		sbp += sprintf(sbp, "%02x ", byte);
		if (abp) abp += sprintf(abp, " %c ", isprint((int)byte) ? byte : ' ');
	    }
	    sbp += sprintf(sbp, "%c ", (match == 0) ? ' ' : '*');
	    if (abp) abp += sprintf(abp, "  ");
	    for (i = 0; (i < bytes_per_line); i++) {
		byte = vptr[i];
		sbp += sprintf(sbp, "%02x ", byte);
		if (abp) abp += sprintf(abp, " %c ", isprint((int)byte) ? byte : ' ');
	    }
	} else {
	    u_int32 data;
	    for (i = 0; (i < bytes_per_line); i += sizeof(data)) {
		data = get_lbn((pptr + i));
		sbp += sprintf(sbp, "%08x ", data);
		if (abp) {
		    unsigned char byte;
		    int x = sizeof(data);
		    while (x--) {
			byte = (data >> (x * BITS_PER_BYTE));
			abp += sprintf(abp, " %c", isprint((int)byte) ? byte : ' ');
		    }
		    abp += sprintf(abp, " ");
		}
	    }
	    sbp += sprintf(sbp, "%c ", (match == 0) ? ' ' : '*');
	    if (abp) abp += sprintf(abp, "  ");
	    for (i = 0; (i < bytes_per_line); i += sizeof(data)) {
		data = get_lbn((vptr + i));
		sbp += sprintf(sbp, "%08x ", data);
		if (abp) {
		    unsigned char byte;
		    int x = sizeof(data);
		    while (x--) {
			byte = (data >> (x * BITS_PER_BYTE));
			abp += sprintf(abp, " %c", isprint((int)byte) ? byte : ' ');
		    }
		    abp += sprintf(abp, " ");
		}
	    }
	}
	sbp += sprintf(sbp, "\n");
	Fprint(str);
	if (abp) {
	    abp += sprintf(abp, "\n");
	    Fprint(astr);
	}
	limit -= bytes_per_line;
	boff += bytes_per_line;
	pptr += bytes_per_line;
	vptr += bytes_per_line;
    }
    return;
}

void
display_iot_data(dinfo_t *dip, u_char *pbuffer, u_char *vbuffer, size_t bcount)
{
    register u_char *pptr = pbuffer;
    register u_char *vptr = vbuffer;
    register size_t count = bcount;
    int block = 0, blocks = (count / dip->di_lbdata_size);
    u_int bad_blocks = 0;
    OFF_T block_offset, record_offset;

    if (dip->di_aio_flag || dip->di_mmap_flag) {
	block_offset = record_offset = dip->di_offset - bcount;
    } else {
	block_offset = record_offset = get_position(dip) - bcount;
    }

    Fprint("\n");
    Fprint(CA_FIELD_WIDTH FUF "\n", "File offset: ", record_offset);
    Fprint(CA_FIELD_WIDTH "%u (%#x)\n", "Transfer count: ", bcount, bcount);
    Fprint(CA_FIELD_WIDTH "%p\n", "Read buffer address: ", vptr);
    Fprint(CA_FIELD_WIDTH "%p\n", "Pattern base address: ", pptr);
    if (dip->di_fprefix_size) {
	Fprint(CA_FIELD_WIDTH "%s\n", "Prefix string: ", dip->di_fprefix_string);
	Fprint(CA_FIELD_WIDTH "%d bytes (0x%x)\n", "Prefix length: ", dip->di_fprefix_size, dip->di_fprefix_size);
    }
    Fprint(CA_FIELD_WIDTH "%s\n", "Note: ", "Incorrect data is marked with asterisk '*'");

    /*
     * Compare one lbdata sized block at a time.
     * 
     * TODO: This does NOT handle any partial IOT blocks! (assumes full IOT data blocks)
     * This is *not* generally a problem, but partial blocks can occur with file system full,
     * and the file offset is not modulo the block size (crossing file system blocks).
     */
    while (blocks) {
	int result = 0;
	if (dip->di_timestamp_flag) {
	    if (dip->di_fprefix_size) {
		result = memcmp(pptr, vptr, dip->di_fprefix_size);
	    }
	    if (result == 0) {
		int doff = (dip->di_fprefix_size + sizeof(iotlba_t));
		result = memcmp( (pptr + doff), (vptr + doff),
				 (dip->di_lbdata_size - doff) );
	    }
	} else {
	    result = memcmp(pptr, vptr, dip->di_lbdata_size);
	}
	if (result == 0) {
	    if (dip->di_dumpall_flag) {
		display_iot_block(dip, block, block_offset, pptr, vptr, dip->di_lbdata_size);
	    }
	} else {
	    if (dip->di_dumpall_flag ||
		(dip->di_max_bad_blocks && (bad_blocks < dip->di_max_bad_blocks) )) {
		display_iot_block(dip, block, block_offset, pptr, vptr, dip->di_lbdata_size);
	    }
	    bad_blocks++;
	}
	block++;
	blocks--;
	pptr += dip->di_lbdata_size;
	vptr += dip->di_lbdata_size;
	block_offset += dip->di_lbdata_size;
    }
    /*
     * Warn user (including me), that some of the IOT data was NOT displayed!
     */ 
    if ((count % dip->di_lbdata_size) != 0) {
	Print("\n");
	Printf("WARNING: A partial IOT data block of %u bytes was NOT displayed!\n",
	       (count % dip->di_lbdata_size) );
    }
    return;
}

/************************************************************************
 *									*
 * verify_padbytes() - Verify Pad Bytes Consistency.			*
 *									*
 * Description:								*
 *	This function simply checks the pad bytes to ensure they	*
 * haven't been overwritten after a read operation.			*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *		buffer = Pointer to start of pad buffer.		*
 *		count = The last record read byte count.		*
 *		pattern = Data pattern to compare against.		*
 *		offset = Offset to where pad bytes start.		*
 *									*
 * Outputs:	Returns SUCCESS/FAILURE = Data Ok/Compare Error.	*
 *									*
 ************************************************************************/
int
verify_padbytes (
	struct dinfo	*dip,
	u_char		*buffer,
	size_t		count,
	u_int32		pattern,
	size_t		offset )
{
    size_t pbytes, pindex;
    int status;

    /*
     * For short reads, checks inverted data bytes & pad bytes.
     */
    if ( (offset != count) && dip->di_spad_check) {
	size_t resid = (offset - count);
	pindex = (count & (sizeof(u_int32) - 1));
	pbytes = (resid < PADBUFR_SIZE) ? resid : PADBUFR_SIZE;
	status = dopad_verify (dip, buffer, count, pattern, pbytes, pindex, TRUE);
	if (status == FAILURE) return (status);
    }
    pindex = 0;
    pbytes = PADBUFR_SIZE;
    return (dopad_verify (dip, buffer, offset, pattern, pbytes, pindex, FALSE));
}

static int
dopad_verify (
	struct dinfo	*dip,
	u_char		*buffer,
	size_t		offset,
	u_int32		pattern,
	size_t		pbytes,
	size_t		pindex,
	bool		inverted )
{
	int status = SUCCESS;
	u_char *vptr;
	size_t i;
	union {
	    u_char pat[sizeof(u_int32)];
	    u_int32 pattern;
	} p;

	p.pattern = pattern;
	vptr = buffer + offset;

	/*
	 * NOTE: We could be comparing inverted data on short reads.
	 */
	for (i = pindex; i < (pbytes + pindex); i++, vptr++) {
	    if (*vptr != p.pat[i & (sizeof(u_int32) - 1)]) {
		if (dip->di_history_size) dump_history_data(dip);
		(void) RecordError(dip);
		Fprintf (
		"Data compare error at %s byte %u in record number %lu\n",
				(inverted) ? "inverted" : "pad",
				(inverted) ? (offset + i) : i,
				(dip->di_records_read + 1));
		ReportDeviceInfo (dip, offset, i, FALSE);
		Fprintf ("Data expected = %#x, data found = %#x, pattern = 0x%08x\n",
			p.pat[i & (sizeof(u_int32) - 1)], *vptr, pattern);
		if (dip->di_dump_flag) {
		    /*
		     * Limit data dumped for short corrupted records.
		     */
		    size_t dump_size = CalculateDumpSize (dip, offset);
		    dump_buffer (dip, data_str, buffer, vptr, dump_size, dip->di_data_size, FALSE);
	        } else {
		    Fprintf ("Data buffer pointer = %#lx, buffer offset = %ld\n",
								vptr, offset);
		}
		fflush (efp);
		status = FAILURE;
                (void)ExecuteTrigger(dip, "miscompare");
		break;
	    }
	}
	return (status);
}

/************************************************************************
 *									*
 * process_pfile() - Process a pattern file.				*
 *									*
 * Inputs:							        * 
 * 	dip = The device information pointer.			        *
 *	file = Pointer to pattern file name.				*
 *	mode = The mode (read/write) for open.				*
 *									*
 * Outputs:	Returns on success, exits on open failure.		*
 *									*
 * Return Value:							*
 *		Void.							*
 *									*
 ************************************************************************/
void
process_pfile(dinfo_t *dip, char *file, int mode)
{
	HANDLE fd;
#if !defined(WIN32)
	struct stat sb;
#endif /* !defined(__WIN32__) */
	size_t count, size;
	u_char *buffer;

#if defined(__WIN32__)
	mode |= O_BINARY;
#endif /* defined(__WIN32__) */

#if defined(WIN32)
	if ( (fd = CreateFile (file, mode, (FILE_SHARE_READ | FILE_SHARE_WRITE),
			       NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == NoFd) {
#else /* !defined(WIN32) */
	if ( (fd = open (file, mode)) == FAILURE) {
#endif /* defined(WIN32) */
	    Fprintf ("Error opening pattern file '%s', mode = %o\n",
							file, mode);
	    report_error (dip, "process_pfile", TRUE);
	    exit (exit_status);
	}
#if defined(WIN32)
	if (GetFileType (fd) == FILE_TYPE_DISK) {
	    size = GetFileSize (fd, NULL);
	} else {
	    Fprintf ("Expect regular file for pattern file.\n");
	    exit (exit_status);
        }
#else /* !defined(WIN32) */
	if (fstat (fd, &sb) < 0) {
	    report_error (dip, "fstat", TRUE);
	    exit (exit_status);
	}
	/*
	 * Only support regular files at this time.
	 */
	if ((sb.st_mode & S_IFMT) != S_IFREG) {
	    Fprintf ("Expect regular file for pattern file.\n");
	    exit (exit_status);
	}
	size = (size_t) sb.st_size;
#endif /* defined(WIN32) */
	buffer = (u_char *)malloc_palign(size, 0);
#if defined(WIN32)
	if(!ReadFile (fd, buffer, size, &count, NULL)) count = FAILURE;
	if (count != size) {
#else /* !defined(WIN32) */
	if ( (count = read (fd, buffer, size)) != size) {
#endif /* defined(WIN32) */
	    Fprintf ("Pattern file '%s' read error!\n", file);
	    if ((ssize_t)count == FAILURE) {
#if defined(WIN32)
		report_error (dip, "ReadFile", TRUE);
#else /* !defined(WIN32) */
		report_error (dip, "read", TRUE);
#endif /* defined(WIN32) */
		exit (exit_status);
	    } else {
		LogMsg (efp, logLevelCrit, 0,
			"Attempted to read %d bytes, read only %d bytes.",
							 size, count);
		exit (FATAL_ERROR);
	    }
	}

	dip->di_patbuf_size = size;
	setup_pattern(dip, buffer, size);
	/*
	 * Currently don't need pattern file open for anything else.
	 */
#if defined(WIN32)
	CloseHandle (fd); fd = NoFd;
#else /* !defined(WIN32) */
	(void) close (fd); fd = -1;
#endif /* defined(WIN32) */
}

/*
 * process_iotune() - Process Parmaters from an IO Tune file.
 *
 * Inputs:
 *	dip = The device information pointer.
 *	file = Pointer to IO tune file name.
 *
 * Outputs:
 * 	Sets up new IO delays.
 *
 * Return Value:
 *	none
 */
void
process_iotune(dinfo_t *dip, char *file)
{
    FILE	*fp;
    ssize_t	count;
    int		size = STRING_BUFFER_SIZE;
    char	buffer[STRING_BUFFER_SIZE];
    char	*mode = "r";
    char	*string;
    unsigned int value;
    struct stat	statbuf, *sb = &statbuf;
    int		status;
    char	*func = "iotuning";

    if (stat(file, sb) == FAILURE) return;
    if (dip->di_iotune_mtime == sb->st_mtime) return;
    dip->di_iotune_mtime = sb->st_mtime;

    if (dip->di_debug_flag || dip->di_tDebugFlag) {
	Printf("Processing I/O tune file '%s'...\n", file);
    }
    if ( (fp = fopen (file, mode)) == (FILE *) 0) {
	Perror("Unable to open script file '%s' for reading", file);
	return;
    }

    do {
	memset(buffer, '\0', size);
	if (fgets (buffer, size, fp) == NULL) {
	    count = -1;		/* Error or EOF, stop reading! */
	} else {
	    char *p;
	    if (p = strrchr(buffer, '\r')) *p = '\0';
	    if (p = strrchr(buffer, '\n')) *p = '\0';
	    count = strlen(buffer);
	}
	/* Note: Eventually expect one line per device/thread. */
	if (count > 0 ) {
	    char *token, *saveptr;
	    token = string = buffer;
	    //if (dip->di_tDebugFlag) Printf("%s: Line: %s\n", func, buffer);
	    token = strtok_r(string, " ", &saveptr);
            while (token != NULL) {
		if (match (&token, "io_delay=")) {
		    value = number(dip, token, ANY_RADIX, &status, dip->di_tDebugFlag);
		    if (status == SUCCESS) {
			//if (dip->di_tDebugFlag) Printf("%s: delays being set to %u\n", func, value);
			dip->di_read_delay = dip->di_write_delay = value;
		    }
		} else if (match (&token, "open_delay=")) {
		    value = number(dip, token, ANY_RADIX, &status, dip->di_tDebugFlag);
		    if (status == SUCCESS) {
			//if (dip->di_tDebugFlag) Printf("%s: Open delay being set to %u\n", func, value);
			dip->di_open_delay = value;
		    }
		} else if (match (&token, "close_delay=")) {
		    value = number(dip, token, ANY_RADIX, &status, dip->di_tDebugFlag);
		    if (status == SUCCESS) {
			//if (dip->di_tDebugFlag) Printf("%s: Close delay being set to %u\n", func, value);
			dip->di_close_delay = value;
		    }
		} else if (match (&token, "end_delay=")) {
		    value = number(dip, token, ANY_RADIX, &status, dip->di_tDebugFlag);
		    if (status == SUCCESS) {
			//if (dip->di_tDebugFlag) Printf("%s: End delay being set to %u\n", func, value);
			dip->di_end_delay = value;
		    }
		} else if (match (&token, "read_delay=")) {
		    value = number(dip, token, ANY_RADIX, &status, dip->di_tDebugFlag);
		    if (status == SUCCESS) {
			//if (dip->di_tDebugFlag) Printf("%s: Read delay being set to %u\n", func, value);
			dip->di_read_delay = value;
		    }
		} else if (match (&token, "start_delay=")) {
		    value = number(dip, token, ANY_RADIX, &status, dip->di_tDebugFlag);
		    if (status == SUCCESS) {
			//if (dip->di_tDebugFlag) Printf("%s: Start delay being set to %u\n", func, value);
			dip->di_start_delay = value;
		    }
		} else if (match (&token, "write_delay=")) {
		    value = number(dip, token, ANY_RADIX, &status, dip->di_tDebugFlag);
		    if (status == SUCCESS) {
			//if (dip->di_tDebugFlag) Printf("%s: Write delay being set to %u\n", func, value);
			dip->di_write_delay = value;
		    }
		} else {
		    if (dip->di_tDebugFlag) {
			Printf("%s: Unknown IO tune parameter '%s'\n", func, token);
		    }
		}
		token = strtok_r(NULL, " ", &saveptr);
	    }
	}
    } while ( count > 0 );

#if defined(DEBUG)
    if (dip->di_debug_flag || dip->di_tDebugFlag) {
	Printf("Finished processing I/O tune file...\n");
    }
#endif
    (void)fclose(fp);
    return;
}

/************************************************************************
 *									*
 * setup_pattern() - Setup pattern variables.				*
 *									*
 * Inputs:							        * 
 * 	dip = The device information pointer.			        *
 *	buffer = Pointer to pattern buffer.				*
 *	size = Size of pattern buffer.					*
 *									*
 * Outputs:	pattern variable setup with 1st 4 bytes of pattern.	*
 *									*
 * Return Value:							*
 *		Void.							*
 *									*
 ************************************************************************/
void
setup_pattern(dinfo_t *dip, u_char *buffer, size_t size)
{
	dip->di_patbuf_size = size;
	dip->di_pattern_buffer = buffer;
	dip->di_pattern_bufptr = buffer;
	dip->di_pattern_bufend = buffer + size;
	dip->di_pattern = (u_int32) 0;

	switch (size) {

	    case sizeof(u_char):
		dip->di_pattern = (u_int32) buffer[0];
		break;

	    case sizeof(u_short):
		dip->di_pattern = ( ((u_int32)buffer[1] << 8) | (u_int32)buffer[0] );
		break;

	    case 0x03:
		dip->di_pattern = ( ((u_int32)buffer[2] << 16) | ((u_int32)buffer[1] << 8) |
			    (u_int32) buffer[0] );
		break;

	    default:
		dip->di_pattern = ( ((u_int32)buffer[3] << 24) | ((u_int32)buffer[2] << 16) |
			    ((u_int32)buffer[1] << 8) | (u_int32)buffer[0]);
		break;
	}
}

/*
 * Copy pattern bytes to pattern buffer with proper byte ordering.
 */
void
copy_pattern (u_int32 pattern, u_char *buffer)
{
	buffer[0] = (u_char) pattern;
	buffer[1] = (u_char) (pattern >> 8);
	buffer[2] = (u_char) (pattern >> 16);
	buffer[3] = (u_char) (pattern >> 24);
}

/*
 * Function to display ASCII time.
 */
char *
bformat_time (char *bp, clock_t time)
{
    u_int hr, min, sec, frac;

    frac = time % hz;
    frac = (frac * 100) / hz;
    time /= hz;
    sec = time % 60; time /= 60;
    min = time % 60;
    if ( (hr = time / 60) ) {
        bp += Sprintf(bp, "%dh", hr);
    }
    bp += Sprintf(bp, "%02dm", min);
    bp += Sprintf(bp, "%02d.", sec);
    bp += Sprintf(bp, "%02ds", frac);
    return (bp);
}

void
print_time (FILE *fp, clock_t time)
{
	u_int hr, min, sec, frac;

	frac = time % hz;
	frac = (frac * 100) / hz;
	time /= hz;
	sec = time % 60; time /= 60;
	min = time % 60;
	if ( (hr = time / 60) ) {
	    fprintf (fp, "%dh", hr);
	}
	fprintf (fp, "%02dm", min);
	fprintf (fp, "%02d.", sec);
	fprintf (fp, "%02ds\n", frac);
}

void
format_time (dinfo_t *dip, clock_t time)
{
	clock_t hr, min, sec, frac;
	frac = (time % hz);
	frac = (frac * 100) / hz;
	time /= hz;
	sec = time % 60; time /= 60;
	min = time % 60;
	if ( (hr = time / 60) ) {
	    Lprintf (dip, "%dh", hr);
	}
	Lprintf (dip, "%02dm", min);
	Lprintf (dip, "%02d.", sec);
	Lprintf (dip, "%02ds\n", frac);
}

/************************************************************************
 *									*
 * seek_file()	Seeks to the specified file offset.			*
 *									*
 * Inputs:							        * 
 * 	dip	= The device information pointer.		        *
 *	fd	= The file descriptor.					*
 *	records = The number of records.				*
 *	size    = The size of each record.				*
 *	whence  = The method of setting position:			*
 *									*
 *		SEEK_SET (L_SET)  = Set to offset bytes.		*
 *		SEEK_CUR (L_INCR) = Increment by offset bytes.		*
 *		SEEK_END (L_XTND) = Extend by offset bytes.		*
 *									*
 *		offset = (record count * size of each record)		*
 *									*
 * Return Value:							*
 *	Returns file position on Success, (OFF_T)-1 on Failure.		*
 *									*
 ************************************************************************/
OFF_T
seek_file(dinfo_t *dip, HANDLE fd, u_long records, OFF_T size, int whence)
{
    OFF_T pos;

    /*
     * Seek to specifed file position.
     */
#if defined(WIN32)
    if ((pos = SetFilePtr ( fd, (OFF_T)(records * size), whence)) == (OFF_T)-1) {
        Fprintf("SetFilePtr failed (fd %d, offset " FUF ", whence %d)\n",
                fd, (OFF_T)(records * size), whence);
        report_error (dip, "SetFilePointer", TRUE);
#else /* !defined(WIN32) */
    if ((pos = lseek (fd, (OFF_T)(records * size), whence)) == (OFF_T)-1) {
        Fprintf("lseek failed (fd %d, offset " FUF ", whence %d)\n",
                fd, (OFF_T)(records * size), whence);
	report_error (dip, "lseek", TRUE);
#endif /* defined(WIN32) */
    }
    return (pos);
}

/*
 * Utility functions to handle file positioning.
 */
OFF_T
seek_position (struct dinfo *dip, OFF_T offset, int whence, bool expect_error)
{
    OFF_T pos;

#if defined(DEBUG)
    if (dip->di_Debug_flag) {
        Printf ("attempting lseek (fd=%d, offset=" FUF ", whence=%d)\n",
					dip->di_fd, offset, whence);
    }
#endif /* defined(DEBUG) */

    /*
     * Seek to specifed file position.
     */
#if defined(WIN32)
    if ((pos = SetFilePtr (dip->di_fd, offset, whence)) == (OFF_T)-1) {
#else /* !defined(WIN32) */
    if ((pos = lseek (dip->di_fd, offset, whence)) == (OFF_T) -1) {
#endif /* defined(WIN32) */
	if (expect_error == FALSE) {
	    Fprintf ("failed lseek (fd %d, offset " FUF ", whence %d)\n",
					    dip->di_fd, offset, whence);
#if defined(WIN32)
	    report_error (dip, "SetFilePointer", TRUE);
#else /* !defined(WIN32) */
	    report_error (dip, "lseek", TRUE);
#endif /* defined(WIN32) */
	    terminate (exit_status);
	} else {
	    return (pos); /* Let caller handle the error! */
	}
    }

#if defined(DEBUG)
    if (dip->di_Debug_flag) {
	Printf ("pos=" FUF " = lseek (fd=%d, offset=%lu, whence=%d)\n",
					pos, dip->di_fd, offset, whence);
    }
#endif /* defined(DEBUG) */

    return (pos);
}

#if !defined(INLINE_FUNCS)

OFF_T
get_position (struct dinfo *dip)
{
    return (seek_position (dip, (OFF_T) 0, SEEK_CUR, FALSE));
}

#endif /* !defined(INLINE_FUNCS) */

u_int32
get_lba (struct dinfo *dip)
{
    OFF_T pos;
    if ( (pos = get_position(dip)) ) {
	return ( (u_int32)(pos / dip->di_lbdata_size) );
    } else {
	return ( (u_int32) 0 );
    }
}

OFF_T
incr_position (struct dinfo *dip, OFF_T offset, bool expect_error)
{
    OFF_T pos = seek_position (dip, offset, SEEK_CUR, expect_error);

    if ( (dip->di_Debug_flag || dip->di_rDebugFlag) && (pos != (OFF_T)-1) ) {
	large_t lba = (pos / (OFF_T)dip->di_dsize);
	Printf ("Seeked to block " LUF " (" LXF ") at offset " FUF "\n",
							lba, lba, pos);
    }
    return (pos);
}

OFF_T
set_position (struct dinfo *dip, OFF_T offset, bool expect_error)
{
    OFF_T pos;

    pos = seek_position (dip, offset, SEEK_SET, expect_error);

    if ( (dip->di_Debug_flag || dip->di_rDebugFlag) && (pos != (OFF_T)-1) ) {
	large_t lba = (pos / (OFF_T)dip->di_dsize);
	u_int32 boff = (pos % (OFF_T)dip->di_dsize);
	if (boff) { /* Show block offset too! Hex useful for traces! */
	    Printf ("Seeked to block " LUF ".%u (" LXF ".%x) at offset " FUF "\n",
							lba, boff, lba, boff, pos);
	} else {
	    Printf ("Seeked to block " LUF " (" LXF ") at offset " FUF "\n",
							lba, lba, pos);
	}
    }
    return (pos);
}

#if !defined(INLINE_FUNCS)

OFF_T
make_position(struct dinfo *dip, u_int32 lba)
{
    return ( (OFF_T)(lba * dip->di_lbdata_size));
}

#endif /* !defined(INLINE_FUNCS) */

void
show_position (struct dinfo *dip, OFF_T pos)
{
    if (dip->di_debug_flag || dip->di_rDebugFlag) {
	large_t lba = make_lba(dip, pos);
	Printf ("%s: File offset is " FUF " (" FXF "), relative lba is %u (%#x)\n",
		dip->di_dname, pos, pos, lba, lba);
    }
}

u_long
get_random(void)
{
    /*
     * These first 2 functions generate a number in range (0 - 2^31).
     */
#if defined(RAND48)
    return ( (u_long)lrand48() );
#elif defined(RANDOM)
    return ( (u_long)random() );
#else /* Use ANSI rand() below... */
    /*
     * ANSI specifies rand() returns value in range (0 - 32767).
     * NOTE: BSD rand() returns value in range (0 - 2^31) also.
     */
    return ( (u_long)rand() );
#endif /* defined(RAND28) */
}

large_t
get_random64(void)
{
#if defined(RAND48)
    /* Expected MAX is 2^31 from lrand48() */
    large_t high_bits, low_bits;
    high_bits = (large_t)lrand48();
    low_bits = (large_t)lrand48();
    return ( (high_bits << 32) | low_bits);
#else /* Use ANSI rand() below... */
    /* Expected MAX is 32767 from rand() */
    large_t high1_bits, high2_bits, low1_bits, low2_bits;
    high2_bits = (large_t)rand();
    high1_bits = (large_t)rand();
    low2_bits = (large_t)rand();
    low1_bits = (large_t)rand();
    return ( ((high2_bits << 48) | (high1_bits << 32) |
	      (low2_bits << 16)  | low1_bits) );
#endif /* defined(RAND28) */
}

/*
 * Function to calculate variable length request size.
 */
size_t
get_variable (struct dinfo *dip)
{
    register size_t length;
    register u_long randum;

    randum = get_random();
    length = (size_t)((randum % dip->di_max_size) + dip->di_min_size);
    if (dip->di_dsize) {
        if ( (dip->di_dtype->dt_dtype == DT_REGULAR) && !dip->di_fsalign_flag) {
            length = roundup(length, dip->di_patbuf_size);
        } else {
	    length = roundup(length, dip->di_dsize);
        }
    }
    if (length > dip->di_max_size) length = dip->di_max_size;
    return (length);
}

/*
 * Function to set random number generator seed.
 */
void
set_rseed(u_int seed)
{
#if defined(RAND48)		/* System V */
    srand48 ((long) seed);
#elif defined(RANDOM)		/* BSD? */
    srandom (seed);
#else 				/* ANSI */
    srand (seed);
#endif
}

/*
 * Function to set position for random I/O.
 */
OFF_T
do_random (struct dinfo *dip, bool doseek, size_t xfer_size)
{
    register OFF_T pos, dsize, ralign;
    register large_t randum;
    OFF_T align;

    dsize = (OFF_T)(dip->di_dsize);
    
    /*
     * Ensure the random alignment size is modulo the device size
     * for raw devices or the pattern file for regular FS files.
     */
    if ( (dip->di_dtype->dt_dtype == DT_REGULAR) && !dip->di_fsalign_flag) {
	align = dip->di_patbuf_size;
    } else {
	/* Note: File system random I/O usually forced to dsize! */
	align = dsize;
    }
    ralign = (OFF_T)((dip->di_random_align) ? (OFF_T)dip->di_random_align : align);
    ralign = roundup(ralign, align);

    randum = (large_t)get_random64();

    /*
     * Set position so that the I/O is in the range from file_position to 
     * {data|rdata}_limit and is block size aligned for raw (character) disks.
     */
    pos = (OFF_T)(randum % dip->di_rdata_limit);

    /*
     * Ensure the upper data limit isn't exceeded.
     */
    while ((large_t)(pos + xfer_size) >= dip->di_rdata_limit) {
	OFF_T npos = ( (pos + xfer_size) % dip->di_rdata_limit);
	/* Probably need a sanity check somewhere to prevent this! */
	if (npos == pos) {
	    pos = rounddown(pos, ralign);
	    break; /* Long standing bug... avoid infinite loop! */ 
	}
	pos = npos;
    }

    /*
     * Round up and align as necessary.
     */
    if (ralign) pos = roundup(pos, ralign);

    /*
     * Ensure the position is within random range.
     */
    if (pos < dip->di_file_position) {
	if ((large_t)(pos + dip->di_file_position + xfer_size) >= dip->di_rdata_limit) {
	    pos = (dip->di_file_position + ((pos + xfer_size) / dsize));
	} else {
	    pos += dip->di_file_position;
	}
	/* Round up and adjust back down as necessary. (yea, ugly :-) */
	while ( ((large_t)(pos = roundup(pos, ralign)) + xfer_size) >= dip->di_rdata_limit) {
	    pos -= (ralign + dsize);
	}
	if (pos < dip->di_file_position) pos = dip->di_file_position; /* too low! */
    }

    if (doseek) {
	return (set_position (dip, pos, FALSE));
    } else {
	/*
	 * Note:  For AIO, we just calculate the random position.
	 */
	if (dip->di_Debug_flag || dip->di_rDebugFlag) {
	    large_t lba = (pos / dsize);
	    Printf ("Random position set to offset " FUF ", block " LUF " (" LXF ").\n",
							pos, lba, lba);
	}
	return (pos);
    }
}

/************************************************************************
 *									*
 * skip_records() Skip past specified number of records.		*
 *									*
 * Inputs:	dip	= The device info pointer.			*
 *		records = The number of records.			*
 *		buffer  = The buffer to read into.			*
 *		size    = The size of each record.			*
 *									*
 * Return Value:							*
 *	Returns SUCCESS/FAILURE/WARNING = Ok/Read Failed/Partial Read.	*
 *									*
 ************************************************************************/
int
skip_records (	struct dinfo	*dip,
		u_long		records,
		u_char		*buffer,
		size_t		size)
{
    u_long i;
    size_t count;
    int status = SUCCESS;

    /*
     * Skip over the specified record(s).
     */
    for (i = 0; i < records; i++) {
#if defined(WIN32)
	if (!ReadFile (dip->di_fd, buffer, size, &count, NULL)) count = FAILURE;
#else /* !defined(WIN32) */
	count = read (dip->di_fd, buffer, size);
#endif /* defined(WIN32) */
	if ( (status = check_read (dip, count, size)) == FAILURE) {
	    break;
	}
    }
    return (status);
}

/************************************************************************
 *									*
 * CvtStrtoValue() - Converts ASCII String into Numeric Value.		*
 *									*
 * Inputs:							        * 
 * 	dip = The device information pointer.			        *
 *	nstr = String to convert.					*
 *	eptr = Pointer for terminating character pointer.		*
 *	base = The base used for the conversion.			*
 *									*
 * Outputs:								*
 * 	eptr = Points to terminating character or nstr if an		*
 *		invalid if numeric value cannot be formed.		*
 *									*
 * Return Value:							*
 *	Returns converted number or -1 for FAILURE.			*
 *									*
 ************************************************************************/
unsigned int 
CvtStrtoValue (dinfo_t *dip, char *nstr, char **eptr, int base)
{
	unsigned int n = 0, val;

	errno = 0;
	if ( (n = strtoul (nstr, eptr, base)) == 0) {
	    if (nstr == *eptr) {
		n++;
	    }
	} else if ( (errno == ERANGE) && (n == 0x7fffffff) ) {
	    /*
	     * Solaris 8 strtoul() is broken!
	     * Converting "c6dec6de" returns a failure!
	     * Thus, this cludgy workaround (for now).
	     */
	    return ( (unsigned int)CvtStrtoLarge(dip, nstr,eptr,base) );
	}
#ifdef notdef
	if (nstr == *eptr) {
	    return (n);
	}
#endif /* notdef */
	nstr = *eptr;
	for (;;) {

	    switch (*nstr++) {

		case 'k':
		case 'K':			/* Kilobytes */
			n *= KBYTE_SIZE;
			continue;

		case 'g':
		case 'G':			/* Gigibytes */
			n *= GBYTE_SIZE;
			continue;

		case 'm':
		case 'M':			/* Megabytes */
			n *= MBYTE_SIZE;
			continue;

#if defined(QuadIsLong)
	        case 't':
	        case 'T':
		        n *= TBYTE_SIZE;
			continue;
#endif /* defined(QuadIsLong) */

		case 'w':
		case 'W':			/* Word count. */
			n *= sizeof(int);
			continue;

		case 'q':
		case 'Q':			/* Quadword count. */
			n *= sizeof(large_t);
			continue;

		case 'b':
		case 'B':			/* Block count. */
			n *= BLOCK_SIZE;
			continue;

		case 'd':
		case 'D':			/* Device size. */
			n *= dip->di_device_size;
			continue;

		case 'c':
		case 'C':			/* Core clicks. */
		case 'p':
		case 'P':			/* Page size. */
			n *= page_size;
			continue;

		case 'i':
		case 'I':
			if ( ( ( nstr[0] == 'N' ) || ( nstr[0] == 'n' ) ) &&
			     ( ( nstr[1] == 'F' ) || ( nstr[1] == 'f' ) )) {
			    nstr += 2;
			    n = (unsigned int)INFINITY;
			    continue;
			} else {
			    goto error;
			}

		case '+':
			n += CvtStrtoValue (dip, nstr, eptr, base);
			nstr = *eptr;
			continue;

		case '-':
			n -= CvtStrtoValue (dip, nstr, eptr, base);
			nstr = *eptr;
			continue;

		case '*':
		case 'x':
		case 'X':
			n *= CvtStrtoValue (dip, nstr, eptr, base);
			nstr = *eptr;
			continue;

		case '/':
			val = CvtStrtoValue (dip, nstr, eptr, base);
			if (val) n /= val;
			nstr = *eptr;
			continue;

		case '%':
			val = CvtStrtoValue (dip, nstr, eptr, base);
			if (val) n %= val;
			nstr = *eptr;
			continue;

		case '~':
			n = ~CvtStrtoValue (dip, nstr, eptr, base);
			nstr = *eptr;
			continue;

		case '|':
			n |= CvtStrtoValue (dip, nstr, eptr, base);
			nstr = *eptr;
			continue;

		case '&':
			n &= CvtStrtoValue (dip, nstr, eptr, base);
			nstr = *eptr;
			continue;

		case '^':
			n ^= CvtStrtoValue (dip, nstr, eptr, base);
			nstr = *eptr;
			continue;

		case '<':
			if (*nstr++ != '<') goto error;
			n <<= CvtStrtoValue (dip, nstr, eptr, base);
			nstr = *eptr;
			continue;
			
		case '>':
			if (*nstr++ != '>') goto error;
			n >>= CvtStrtoValue (dip, nstr, eptr, base);
			nstr = *eptr;
			continue;
			
		case ' ':
		case '\t':
			continue;

		case '\0':
			*eptr = --nstr;
			break;

		default:
error:
			n = 0L;
			*eptr = --nstr;
			break;
	    }
	    return (n);
	}
}

/************************************************************************
 *									*
 * CvtStrtoLarge() - Converts ASCII String into Large Value.		*
 *									*
  * Inputs:							        * 
 * 	dip = The device information pointer.			        *
 *	nstr = String to convert.					*
 *	eptr = Pointer for terminating character pointer.		*
 *	base = The base used for the conversion.			*
 *									*
 * Outputs:								*
 * 	eptr = Points to terminating character or nstr if an		*
 *		invalid if numeric value cannot be formed.		*
 *									*
 * Return Value:							*
 *	Returns converted number or -1 for FAILURE.			*
 *									*
 ************************************************************************/
large_t
CvtStrtoLarge (dinfo_t *dip, char *nstr, char **eptr, int base)
{
	large_t n = 0, val;

	/* Thankfully we have POSIX standards, eh? :-( */
#if defined(QuadIsLong) || defined(HP_UX)  
	if ( (n = strtoul (nstr, eptr, base)) == (large_t) 0) {
#elif defined(QuadIsLongLong)
#  if defined(SCO) || defined(__QNXNTO__) || defined(SOLARIS) || defined(AIX) || defined(_NT_SOURCE)
	if ( (n = strtoull (nstr, eptr, base)) == (large_t) 0) {
#elif defined(WIN32)
	if ( (n = _strtoui64 (nstr, eptr, base)) == (large_t) 0) {
#  else /* !defined(SCO) && !defined(__QNXNTO__) && !defined(AIX) && !defined(_NT_SOURCE) */
	if ( (n = strtouq (nstr, eptr, base)) == (large_t) 0) {
#  endif /* defined(SCO) || defined(__QNXNTO__) || defined(SOLARIS) || defined(AIX) || defined(_NT_SOURCE) */
#else /* assume QuadIsDouble */
	if ( (n = strtod (nstr, eptr)) == (large_t) 0) {
#endif
	    if (nstr == *eptr) {
		n++;
	    }
	}
#ifdef notdef
	if (nstr == *eptr) {
	    return (n);
	}
#endif /* notdef */
	nstr = *eptr;
	for (;;) {

	    switch (*nstr++) {

		case 'k':
		case 'K':			/* Kilobytes */
			n *= KBYTE_SIZE;
			continue;

		case 'g':
		case 'G':			/* Gigibytes */
			n *= GBYTE_SIZE;
			continue;

		case 'm':
		case 'M':			/* Megabytes */
			n *= MBYTE_SIZE;
			continue;

	        case 't':
	        case 'T':
		        n *= TBYTE_SIZE;
			continue;

		case 'w':
		case 'W':			/* Word count. */
			n *= sizeof(int);
			continue;

		case 'q':
		case 'Q':			/* Quadword count. */
			n *= sizeof(large_t);
			continue;

		case 'b':
		case 'B':			/* Block count. */
			n *= BLOCK_SIZE;
			continue;

		case 'd':
		case 'D':			/* Device size. */
			n *= dip->di_device_size;
			continue;

		case 'c':
		case 'C':			/* Core clicks. */
		case 'p':
		case 'P':			/* Page size. */
			n *= page_size;
			continue;

		case 'i':
		case 'I':
			if ( ( ( nstr[0] == 'N' ) || ( nstr[0] == 'n' ) ) &&
			     ( ( nstr[1] == 'F' ) || ( nstr[1] == 'f' ) )) {
			    nstr += 2;
			    n = INFINITY;
			    continue;
			} else {
			    goto error;
			}

		case '+':
			n += CvtStrtoLarge (dip, nstr, eptr, base);
			nstr = *eptr;
			continue;

		case '-':
			n -= CvtStrtoLarge (dip, nstr, eptr, base);
			nstr = *eptr;
			continue;

		case '*':
		case 'x':
		case 'X':
			n *= CvtStrtoLarge (dip, nstr, eptr, base);
			nstr = *eptr;
			continue;

		case '/':
			val = CvtStrtoLarge (dip, nstr, eptr, base);
			if (val) n /= val;
			nstr = *eptr;
			continue;
#if !defined(QuadIsDouble)
		case '%':
			val = CvtStrtoLarge (dip, nstr, eptr, base);
			if (val) n %= val;
			nstr = *eptr;
			continue;

		case '~':
			n = ~CvtStrtoLarge (dip, nstr, eptr, base);
			nstr = *eptr;
			continue;

		case '|':
			n |= CvtStrtoLarge (dip, nstr, eptr, base);
			nstr = *eptr;
			continue;

		case '&':
			n &= CvtStrtoLarge (dip, nstr, eptr, base);
			nstr = *eptr;
			continue;

		case '^':
			n ^= CvtStrtoLarge (dip, nstr, eptr, base);
			nstr = *eptr;
			continue;

		case '<':
			if (*nstr++ != '<') goto error;
			n <<= CvtStrtoLarge (dip, nstr, eptr, base);
			nstr = *eptr;
			continue;
			
		case '>':
			if (*nstr++ != '>') goto error;
			n >>= CvtStrtoLarge (dip, nstr, eptr, base);
			nstr = *eptr;
			continue;
#endif /* !defined(QuadIsDouble) */
		case ' ':
		case '\t':
			continue;

		case '\0':
			*eptr = --nstr;
			break;

		default:
error:
			n = 0;
			*eptr = --nstr;
			break;
	    }
	    return (n);
	}
}

/************************************************************************
 *									*
 * CvtTimetoValue() - Converts ASCII Time String to Numeric Value.	*
 *									*
 * Inputs:	nstr = String to convert.				*
 *		eptr = Pointer for terminating character pointer.	*
 *									*
 * Outputs:	eptr = Points to terminating character or nstr if an	*
 *			invalid if numeric value cannot be formed.	*
 *									*
 * Return Value:							*
 *		Returns converted number in seconds or -1 for FAILURE.	*
 *									*
 ************************************************************************/
time_t
CvtTimetoValue (char *nstr, char **eptr)
{
	time_t n = 0;
	int base = ANY_RADIX;

	if ( (n = strtoul (nstr, eptr, base)) == 0L) {
	    if (nstr == *eptr) {
		n++;
	    }
	}
#ifdef notdef
	if (nstr == *eptr) {
	    return (n);
	}
#endif /* notdef */
	nstr = *eptr;
	for (;;) {

	    switch (*nstr++) {

		case 'd':
		case 'D':			/* Days */
			n *= SECS_PER_DAY;
			continue;

		case 'h':
		case 'H':			/* Hours */
			n *= SECS_PER_HOUR;
			continue;

		case 'm':
		case 'M':			/* Minutes */
			n *= SECS_PER_MIN;
			continue;

		case 's':
		case 'S':			/* Seconds */
			continue;		/* default */

		case '+':
			n += CvtTimetoValue (nstr, eptr);
			nstr = *eptr;
			continue;

		case '-':
			n -= CvtTimetoValue (nstr, eptr);
			nstr = *eptr;
			continue;

		case '*':
		case 'x':
		case 'X':
			n *= CvtTimetoValue (nstr, eptr);
			nstr = *eptr;
			continue;

		case '/':
			n /= CvtTimetoValue (nstr, eptr);
			nstr = *eptr;
			continue;

		case '%':
			n %= CvtTimetoValue (nstr, eptr);
			nstr = *eptr;
			continue;

		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			nstr--;
			n += CvtTimetoValue (nstr, eptr);
			nstr = *eptr;
			continue;

		case ' ':
		case '\t':
			continue;

		case '\0':
			*eptr = --nstr;
			break;
		default:
			n = 0L;
			*eptr = --nstr;
			break;
	    }
	    return (n);
	}
}

/*
 * Format & append time string to log file buffer.
 */
/*VARARGS*/
void
Ctime (dinfo_t *dip, time_t timer)
{
    char *buf;
    char *bp = dip->di_log_bufptr;

    buf = os_ctime(&timer, dip->di_time_buffer, sizeof(dip->di_time_buffer));
    (void) strcpy (bp, buf);
    bp += strlen(bp);
    dip->di_log_bufptr = bp;
}

/*
 * Record current time of when error occured.
 */
u_long
RecordError(struct dinfo *dip)
{
    (void)time(&dip->di_error_time);
    //LogMsg (efp, logLevelError, (PRT_NOIDENT|PRT_NOLEVEL), "\n");
    LogMsg (efp, logLevelCrit, 0,
	    "Error number %lu occurred on %s",
	    ++dip->di_error_count,
	    os_ctime(&dip->di_error_time, dip->di_time_buffer, sizeof(dip->di_time_buffer)));
    dip->di_end_time = times (&dip->di_etimes);
    Fprintf ("Elapsed time since beginning of pass: ");
    print_time (efp, dip->di_end_time - dip->di_pass_time);
    Fprintf ("Elapsed time since beginning of test: ");
    print_time (efp, dip->di_end_time - dip->di_start_time);
    fflush(efp);
    exit_status = FAILURE;
    return (dip->di_error_count);
}

/*
 * Record current time & record count of when warning occur.
 */
u_long
RecordWarning(dinfo_t *dip, u_long record)
{
    (void)time(&dip->di_error_time);
    Printf ("Warning on record number %lu, occurred at %s", (record + 1),
	    os_ctime(&dip->di_error_time, dip->di_time_buffer, sizeof(dip->di_time_buffer)));
    dip->di_end_time = times (&dip->di_etimes);
    Printf ("Elapsed time since beginning of pass: ");
    print_time (ofp, dip->di_end_time - dip->di_pass_time);
    Printf ("Elapsed time since beginning of test: ");
    print_time (ofp, dip->di_end_time - dip->di_start_time);
    return (dip->di_warning_errors);
}

/*
 * fmtmsg_prefix() - Common function to format the prefix for messages.
 *
 * Inputs:
 *	bp = Pointer to message buffer.
 *
 * Return Value:
 *	The updated buffer pointer.
 */
char *
fmtmsg_prefix(char *bp, int flags, logLevel_t level)
{
    /*
     * All messages include a process ID (for now).
     * 
     * Note: This will change to a thread ID when fully implemented!
     */
#if defined(WIN32)
    if (nate_flag) {
	struct tm time_data;
	struct tm *tmp = &time_data;
	time_t now;
	(void)time(&now);
	/* errno_t localtime_s( struct tm* _tm, const time_t *time ); */
	if ( localtime_s(tmp, &now) == SUCCESS ) {
	    tmp->tm_year += 1900;
	    tmp->tm_mon++;
	    /* NATE Format: yyyymmdd hhmmss [00_script] */
	    if (debug_flag || tDebugFlag) {
	       bp += sprintf (bp, "%04d%02d%02d %02d%02d%02d [%s (p:%d t:%u)] ",
			      tmp->tm_year, tmp->tm_mon, tmp->tm_mday,
			      tmp->tm_hour, tmp->tm_min, tmp->tm_sec,
			      cmdname, GetCurrentProcessId(), GetCurrentThreadId());
	    } else {
	       bp += sprintf (bp, "%04d%02d%02d %02d%02d%02d [%s (%d)] ",
	       tmp->tm_year, tmp->tm_mon, tmp->tm_mday,
	       tmp->tm_hour, tmp->tm_min, tmp->tm_sec,
	       cmdname, GetCurrentProcessId()/*dip->di_process_id*/);
	    }
	}
    } else {
	/*
	 * If multiple threads and debugging, include the thread ID too!
	 */
	if (debug_flag || tDebugFlag) {
	    bp += sprintf (bp, "%s (p:%d t:%u): ", cmdname,
			   GetCurrentProcessId(), GetCurrentThreadId() );
	} else {
	    bp += sprintf (bp, "%s (%d): ", cmdname,
			   GetCurrentProcessId()/*dip->di_process_id*/);
	}
    }
#else /* !defined(WIN32) */
    if (nate_flag) {
	/* struct tm *localtime_r(const time_t *restrict clock, struct tm *restrict res); */
	struct tm time_data;
	struct tm *tmp = &time_data;
	time_t now;
	(void)time(&now);
	if ( localtime_r(&now, tmp) ) {
	    tmp->tm_year += 1900;
	    tmp->tm_mon++;
	    /* NATE Format: yyyymmdd hhmmss [00_script] */
	    if (debug_flag || tDebugFlag) {
		bp += sprintf (bp, "%04d%02d%02d %02d%02d%02d [%s (p:%d t:%u)] ",
			       tmp->tm_year, tmp->tm_mon, tmp->tm_mday,
			       tmp->tm_hour, tmp->tm_min, tmp->tm_sec,
			       cmdname, getpid(), (unsigned int)pthread_self());
	    } else {
		bp += sprintf (bp, "%04d%02d%02d %02d%02d%02d [%s (%d)] ",
			       tmp->tm_year, tmp->tm_mon, tmp->tm_mday,
			       tmp->tm_hour, tmp->tm_min, tmp->tm_sec,
			       cmdname, getpid()/*dip->di_process_id*/);
	    }
	}
    } else {
	/*
	 * Note: pthread_t is NOT always an unsigned long! (FreeBSD is a pointer)
	 */
	if (debug_flag || tDebugFlag) {
	    bp += sprintf (bp, "%s (p:%d t:%u): ", cmdname,
			   getpid(), (unsigned int)pthread_self() );
	} else {
	    bp += sprintf (bp, "%s (%d): ", cmdname, getpid()/*dip->di_process_id*/);
	}
    }
#endif /* defined(WIN32) */

    /*
     * Add an ERROR: prefix to clearly indicate error/critical issues.
     */
    if (!hazard_flag && !(flags & PRT_NOLEVEL)) {
	if ( (level == logLevelCrit) || (level == logLevelError) ) {
	    bp += sprintf(bp, "ERROR: ");
	}
    }
    return (bp);
}

/*
 * Display failure message to stderr & flush output.
 */
/*VARARGS*/
void
LogMsg (FILE *fp, enum logLevel level, int flags, char *fmtstr, ...)
{
    va_list ap;
    char buffer[STRING_BUFFER_SIZE];
    char *bp = buffer;

    if (hazard_flag && !(flags & PRT_NOLEVEL)) {
	bp += sprintf (bp, "RPCLOG%d:", level /*logLevelLog*/);
    }
    if ( !(flags & PRT_NOIDENT) ) {
	bp = fmtmsg_prefix(bp, flags, level);
    }
    va_start(ap, fmtstr);
    bp += vsprintf (bp, fmtstr, ap);
    Fputs (buffer, fp);
    va_end(ap);
    if ( !(flags & PRT_NOFLUSH) ) {
	(void) fflush (fp);
    }
    return;
}

void
Fprintf (char *format, ...)
{
	va_list ap;
	FILE *fp = efp;
	char buffer[STRING_BUFFER_SIZE];
	char *bp = buffer;

	if (hazard_flag) {
	    bp += sprintf (bp, "RPCLOG%d:", logLevelLog);
	} else {
	    bp = fmtmsg_prefix(bp, 0, logLevelLog);
	}
	va_start(ap, format);
	bp += vsprintf (bp, format, ap);
	Fputs (buffer, fp);
	va_end(ap);
	(void) fflush (fp);
	return;
}

/*
 * Same as Fprintf except no identifier or log prefix.
 */
/*VARARGS*/
void
Fprint (char *format, ...)
{
	va_list ap;
	FILE *fp = efp;

	va_start(ap, format);
	vfprintf (fp, format, ap);
	va_end(ap);
}

/*
 * Format & append string to log file buffer.
 */
/*VARARGS*/
void
Lprintf (dinfo_t *dip, char *format, ...)
{
	va_list ap;
	char *bp = dip->di_log_bufptr;

	va_start(ap, format);
	vsprintf (bp, format, ap);
	va_end(ap);
	bp += strlen(bp);
	dip->di_log_bufptr = bp;
}

/*
 * Flush the log buffer and reset the buffer pointer.
 */
void
Lflush(dinfo_t *dip)
{
	FILE *fp = ofp;
	int size;
	if ((size = (dip->di_log_bufptr - dip->di_log_buffer)) > LOG_BUFSIZE) {
	    Fprintf("Oops, we've exceeded the log buffer size, %d > %d!\n", 
		    size,  LOG_BUFSIZE);
	}
	Fputs (dip->di_log_buffer, fp);
	fflush (fp);
	dip->di_log_bufptr = dip->di_log_buffer;
}

/*
 * Display message to stdout & flush output.
 */
/*VARARGS*/
void
Printf (char *format, ...)
{
	va_list ap;
	FILE *fp = ofp;
	char buffer[STRING_BUFFER_SIZE];
	char *bp = buffer;

	if (hazard_flag) {
	    bp += sprintf (bp, "RPCLOG%d:", logLevelLog);
	} else {
	    bp = fmtmsg_prefix(bp, 0, logLevelLog);
	}
	va_start(ap, format);
	bp += vsprintf (bp, format, ap);
	Fputs (buffer, fp);
	va_end(ap);
	(void) fflush (fp);
}

/*
 * Same as Printf except no program name identifier.
 */
/*VARARGS*/
void
Print (char *format, ...)
{
	va_list ap;
	FILE *fp = ofp;

	if (hazard_flag) {
	    fprintf (fp, "RPCLOG%d:", logLevelLog);
	}
	va_start(ap, format);
	vfprintf (fp, format, ap);
	va_end(ap);
}

/*
 * Perror() - Common Function to Print Error Messages.
 *
 * Description:
 *	This reports POSIX style errors only.
 *
 * Implicit Inputs:
 *      format = Pointer to format control string.
 *      ... = Variable argument list.
 *
 * Return Value:
 *      void
 */
/*VARARGS*/
void
Perror(char *format, ...)
{
    char msgbuf[LOG_BUFSIZE];
    va_list ap;

    va_start(ap, format);
    (void) vsprintf(msgbuf, format, ap);
    va_end(ap);
    LogMsg(efp, logLevelError, 0,
	   "%s, errno = %d - %s\n", msgbuf, errno, strerror(errno));
    return;
}

#if defined(WIN32)
/*
 * Windows equivalent...
 *	we need both since POSIX and Windows API's are both used! (yet)
 */
/*VARARGS*/
void
wPerror(char *format, ...)
{
    char msgbuf[LOG_BUFSIZE];
    DWORD error = GetLastError();
    LPVOID emsg = werror_msg(error);
    va_list ap;

    va_start(ap, format);
    (void) vsprintf(msgbuf, format, ap);
    va_end(ap);
    LogMsg(efp, logLevelError, 0, "%s, error = %d - %s\n", msgbuf, error, emsg);
    (void)LocalFree((HLOCAL)emsg);
    return;
}

void
tPerror(DWORD error, char *format, ...)
{
    char msgbuf[LOG_BUFSIZE];
    LPVOID emsg = werror_msg(error);
    va_list ap;

    va_start(ap, format);
    (void) vsprintf(msgbuf, format, ap);
    va_end(ap);
    LogMsg(efp, logLevelError, 0, "%s, error = %d - %s\n", msgbuf, error, emsg);
    (void)LocalFree((HLOCAL)emsg);
    return;
}

#else /* !defined(WIN32) */

void
tPerror(int error, char *format, ...)
{
    char msgbuf[LOG_BUFSIZE];
    va_list ap;

    va_start(ap, format);
    (void) vsprintf(msgbuf, format, ap);
    va_end(ap);
    LogMsg(efp, logLevelError, 0,
	   "%s, errno = %d - %s\n", msgbuf, errno, strerror(error));
    return;
}

#endif /* defined(WIN32) */

/*VARARGS*/
int
Sprintf(char *bufptr, char *msg, ...)
{
	va_list ap;

	va_start(ap, msg);
	(void) vsprintf (bufptr, msg, ap);
	va_end(ap);
	return (strlen (bufptr));
}

int	
vSprintf(char *bufptr, const char *msg, va_list ap)
{
	(void) vsprintf(bufptr, msg, ap);
	return (strlen (bufptr));
}

/************************************************************************
 *									*
 * Fputs()	Common function to Write String to an Output Stream.	*
 *									*
 * Inputs:	str = The string buffer pointer.			*
 *		stream = The file stream to access.			*
 *									*
 * Return Value:							*
 *		Returns 0 / -1 = SUCCESS / FAILURE.			*
 * 									*
 ************************************************************************/
int
Fputs (char *str, FILE *stream)
{
	int status = SUCCESS;

	(void) fputs ((char *) str, stream);
	if (ferror (stream) != 0) {
	    clearerr (stream);
	    status = FAILURE;
	}
	return (status);
}

/*
 * isFsFullOk() - Checks for File System Full Condition.
 *
 * Inputs:
 *	dip = The device information pointer.
 *	op = The operation message.
 *
 * Return Value:
 *	Returns TRUE/FALSE = File System Full / Not FS Full Condition.
 */
bool
isFsFullOk(struct dinfo *dip, char *op)
{
    bool read_mode = (dip->di_mode == READ_MODE);
    /*
     * The limit checks control whether file system full is acceptable.
     *
     * Note: Disk full conditions should only occur on write operations.
     */
#if defined(WIN32)
    DWORD error = GetLastError();
    if ( (error == ERROR_DISK_FULL) &&
	 (dip->di_multiple_files && (dip->di_maxdata_read || dip->di_maxdata_written)) ) {
	if (dip->di_verbose_flag) {
	    Printf("File name: %s\n", dip->di_dname);
	    Printf("WARNING: Disk full (ERROR_DISK_FULL) detected, [file #%lu, record #%lu, %s " FUF " file bytes, " FUF " total bytes]\n",
		   (read_mode) ? (dip->di_files_read + 1) : (dip->di_files_written + 1),
		   (read_mode) ? (dip->di_records_read + 1) : (dip->di_records_written + 1),
		   (read_mode) ? "read" : "wrote",
		   (read_mode) ? dip->di_fbytes_read : dip->di_fbytes_written,
		   (read_mode) ? dip->di_dbytes_read : dip->di_dbytes_written);
	} else if (dip->di_debug_flag || dip->di_fDebugFlag) {
	    LPVOID emsg = werror_msg(error);
	    Printf("File name: %s\n", dip->di_dname);
	    Printf("DEBUG: %s failed, error %d - %s\n", op, error, emsg);
	    (void)LocalFree((HLOCAL)emsg);
	}
	errno = ENOSPC;	    /* Map to Unix equivalent for caller. */
	dip->di_no_space_left = TRUE;
	return(TRUE);
    }
#else /* !defined(WIN32) */
    if ( ((errno == ENOSPC) || (errno == EDQUOT)) &&
	 (dip->di_multiple_files && (dip->di_maxdata_read || dip->di_maxdata_written)) ) {
	if (dip->di_verbose_flag) {
	    Printf("File name: %s\n", dip->di_dname);
	    Printf("WARNING: %s detected, [file #%lu, record #%lu, %s " FUF " file bytes, " FUF " total bytes]\n",
		   (errno == ENOSPC) ? "No space left on device (ENOSPC)" : "Quota exceeded (EDQUOT)",
		   (read_mode) ? (dip->di_files_read + 1) : (dip->di_files_written + 1),
		   (read_mode) ? (dip->di_records_read + 1) : (dip->di_records_written + 1),
		   (read_mode) ? "read" : "wrote",
		   (read_mode) ? dip->di_fbytes_read : dip->di_fbytes_written,
		   (read_mode) ? dip->di_dbytes_read : dip->di_dbytes_written);
	} else if (dip->di_debug_flag || dip->di_fDebugFlag) {
	    Printf("File name: %s\n", dip->di_dname);
	    Printf("DEBUG: %s failed, errno %d - %s\n", op, errno, strerror(errno));
	}
	dip->di_no_space_left = TRUE;
	return(TRUE);
    }
#endif /* defined(WIN32) */
    return (FALSE);
}

/************************************************************************
 *									*
 * is_Eof() - Check For End Of File Condition.				*
 *									*
 * Description:								*
 *	Detect end of file or end of media.  Here's the presumptions:	*
 *									*
 *  For Writes, we expect a errno (count == -1) and (errno == ENOSPC).	*
 *   For Reads, a (count == 0) indicates end of file, while a		*
 *	(count == -1) and (errno == ENOSPC) indicates end of medium.	*
 *									*
 *	Actually, two file marks normally indicates the end of logical	*
 * tape, while (errno == ENOSPC) normally indicates reading past all of	*
 * the recorded data.  Note, some tapes (QIC) only have one file mark.	*
 *									*
 *	Is this confusing or what?  I'm doing the best I can here :-)	*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *		count = The count from the last I/O request.		*
 *		status = Optional pointer to status variable.		*
 *									*
 * Return Value:							*
 *		Returns TRUE / FALSE = End of file / Not Eof.		*
 *									*
 ************************************************************************/
int
is_Eof (struct dinfo *dip, size_t count, int *status)
{
    bool detected_eof = FALSE;
    bool read_mode = (dip->di_mode == READ_MODE);
#if defined(WIN32)
    int error = GetLastError();
#else /* !defined(WIN32) */
    int error = errno;
#endif /* defined(WIN32) */

    /*
     * NOTE: Apparently EOF is not defined by POSIX, since each OS differs!
     *
     * Also NOTE: If this occurs, all the new "no space" logic is screwed!
     */
    if ( (dip->di_mode == WRITE_MODE) && (count == (size_t) 0) ) {
#if defined(BrokenEOF)
	/* Abnormal, but added for Solaris! */
	if (exit_status != FAILURE) exit_status = END_OF_FILE;
	/* Note: Miss messages below... is this still valid? raw disks */
	return (dip->di_end_of_file = TRUE);
#else /* !defined(BrokenEOF) */
	return (FALSE);
#endif /* defined(BrokenEOF) */
    }

    /*
     * Various checks for handling end of file/media, while still
     * trying to be smart about reporting unexpected error codes!
     */
#if defined(SCO) || defined(HP_UX) || defined(AIX)
    if ( (count == (size_t) 0) ||
	 ( ((ssize_t)count == (ssize_t) -1) &&
	   ((errno == ENOSPC) || (errno == ENXIO) || (errno == EDQUOT)) ) ) {
#elif defined(__CYGWIN__)
    if ( (count == (size_t) 0) ||
	 ( ((ssize_t)count == (ssize_t) -1) &&
	   ((errno == ENOSPC) || (errno == EINVAL)) ) ) {
#elif defined(WIN32)
    if ( (count == (size_t) 0) ||
	 ( (count == -1) &&
	   ( ((errno = GetLastError()) == ERROR_DISK_FULL) ||
	      (errno == ERROR_SECTOR_NOT_FOUND)) ) ) {
#else /* !defined(SCO) && !defined(HP_UX) && !defined(AIX) */
    if ( (count == (size_t) 0) ||
	 ( ((ssize_t)count == (ssize_t) -1) &&
	   ((errno == ENOSPC) || (errno == EDQUOT)) ) ) {
#endif /* defined(SCO) || defined(HP_UX) || defined(AIX) */
	large_t data_bytes;
	if (read_mode) {
	    data_bytes = dip->di_dbytes_read;
	    if (count == (size_t) 0) {
		errno = 0;	/* Avoid reporting bogus error message. */
	    }
	} else {
	    data_bytes = dip->di_dbytes_written;
	}
	detected_eof = TRUE;
	(void)isFsFullOk(dip, "eof");
	if (dip->di_debug_flag || dip->di_eDebugFlag) {
	    if (dip->di_multiple_files) {
		Printf("File name: %s\n", dip->di_dname);
		Printf("End of %s detected, count = %d, errno = %d [file #%lu, record #%lu, %s " FUF " file bytes, " FUF " total bytes]\n",
		       (count == 0) ? "file" : "media", count, error,
		       (read_mode) ? (dip->di_files_read + 1) : (dip->di_files_written + 1),
		       (read_mode) ? (dip->di_records_read + 1) : (dip->di_records_written + 1),
		       (read_mode) ? "read" : "wrote", 
		       (read_mode) ? dip->di_fbytes_read : dip->di_fbytes_written,
		       (read_mode) ? dip->di_dbytes_read : dip->di_dbytes_written);
	    } else {
		Printf("End of %s detected, count = %d, errno = %d [file #%lu, record #%lu, %s " FUF " bytes]\n",
		       (count == 0) ? "file" : "media", count, error,
		       (read_mode) ? (dip->di_files_read + 1) : (dip->di_files_written + 1),
		       (read_mode) ? (dip->di_records_read + 1) : (dip->di_records_written + 1),
		       (read_mode) ? "read" : "wrote", 
		       (read_mode) ? dip->di_dbytes_read : dip->di_dbytes_written);
	    }
	}
#if defined(TAPE)
	if (dip->di_dtype->dt_dtype == DT_TAPE) {
	    if (count == (size_t) 0) {
		/* Two file mark's == end of logical tape. */
		if (dip->di_end_of_file) dip->di_end_of_logical = TRUE;
		if (dip->di_end_of_logical) dip->di_end_of_media = TRUE;
	    } else { /* ENOSPC */
		/* Remember, QIC tapes only have one file mark! */
		dip->di_end_of_logical = TRUE;
		dip->di_end_of_media = TRUE;
	    }
	}
#endif /* defined(TAPE) */
	/*
	 * Dup of EOF checks above, but if no data was transferred, then
	 * we report an error!  This is not considered normal.
	 * Yes, I know this is very ugly... needs cleaned up!
	 */
	if ( detected_eof && (data_bytes == (large_t ) 0) && !dip->di_no_space_left ) {
	    Printf ("EOF with no data transferred, count = %d, errno = %d [file #%lu, record #%lu]\n",
		    count, error,
		    (read_mode) ? (dip->di_files_read + 1) : (dip->di_files_written + 1),
		    (read_mode) ? (dip->di_records_read + 1) : (dip->di_records_written + 1));
	    exit_status = FAILURE;
#if defined(WIN32)
	    report_error(dip, (read_mode) ? "ReadFile" : "WriteFile", TRUE);
#else /* !defined(WIN32) */
	    report_error(dip, (read_mode) ? "read" : "write", TRUE);
#endif /* defined(WIN32) */
	    if (status) *status = FAILURE;
	} else {
	    if (exit_status != FAILURE) exit_status = END_OF_FILE;
	}
	return (dip->di_end_of_file = TRUE);
    }
    return (FALSE);
}

bool
is_retryable(dinfo_t *dip, int error_code)
{
    int entry;
    
    /* Note: These retry variable move to dip in threaded dt! */
    for (entry = 0; (entry < dip->di_retry_entries); entry++) {
	if ( (error_code == dip->di_retry_errors[entry]) ||
	     (dip->di_retry_errors[entry] == -1) ) {	/* Any error! */
	    return (TRUE);
	}
    }
    return (FALSE);
}

bool
retry_operation(dinfo_t *dip)
{
    if (dip->di_retry_count++ == dip->di_retry_limit) {
	Fprintf("Exceeded retry limit (%u) for this request!\n", dip->di_retry_limit);
	return (FALSE);
    }
    Printf("Warning: Retrying request after %u second delay, retry #%d\n",
	    dip->di_retry_delay, dip->di_retry_count);
    SleepSecs(dip->di_retry_delay);

    HANDLE_TERMINATE(dip);

    return (TRUE);
}

/*
 * Used to mimic EOF @ BOM when direction is reverse.
 */
void
set_Eof(struct dinfo *dip)
{
    bool read_mode = (dip->di_mode == READ_MODE);

    if (dip->di_debug_flag || dip->di_eDebugFlag) {
	Printf ("%s of media detected [file #%lu, record #%lu, %s " FUF " file bytes]\n",
		(dip->di_io_dir == REVERSE) ? "Beginning" : "End",
		(read_mode) ? (dip->di_files_read + 1) : (dip->di_files_written + 1),
		(read_mode) ? dip->di_records_read : dip->di_records_written,
		(read_mode) ? "read" : "wrote",
		(read_mode) ? dip->di_fbytes_read : dip->di_fbytes_written);
    }
    if (exit_status != FAILURE) exit_status = END_OF_FILE;
    dip->di_end_of_file = TRUE;
    return;
}

void
ReportCompareError (
	struct dinfo	*dip,
	size_t		byte_count,
	u_int		byte_position,
	u_int		expected_data,
	u_int		data_found)
{
    if (hazard_flag) {
	LogMsg (efp, logLevelCrit, 0, "CORRUPTION:\n");
    }
    if (dip->di_history_size) dump_history_data(dip);
    (void) RecordError(dip);
    if (dip->di_dtype->dt_dtype == DT_TAPE) {
	Fprintf ("File #%lu, %s %u in record number %lu\n", (dip->di_files_read + 1),
		compare_error_str, byte_position, (dip->di_records_read + 1));
    } else if (dip->di_multiple_files) {
	Fprintf ("File %s, %s %u in record number %lu\n", dip->di_dname,
		compare_error_str, byte_position, (dip->di_records_read + 1));
    } else {
	Fprintf ("%s %u in record number %lu\n",
		compare_error_str, byte_position, (dip->di_records_read + 1));
    }
    ReportDeviceInfo (dip, byte_count, byte_position, FALSE);
    Fprintf ("Data expected = %#x, data found = %#x, byte count = %lu\n",
				expected_data, data_found, byte_count);
#if defined(SYSLOG)
    if (dip->di_syslog_flag) {
	if (dip->di_dtype->dt_dtype == DT_TAPE) {
	    syslog(LOG_ERR, "(%d) File #%lu, %s %u in record number %lu\n",
		   dip->di_process_id, (dip->di_files_read + 1), compare_error_str,
		   byte_position, (dip->di_records_read + 1));
	} else if (dip->di_multiple_files) {
	    syslog(LOG_ERR, "(%d) File %s, %s %u in record number %lu\n",
		   dip->di_process_id, dip->di_dname, compare_error_str,
		   byte_position, (dip->di_records_read + 1));
	} else {
	    syslog(LOG_ERR, "(%d) %s %u in record number %lu\n",
		   dip->di_process_id, compare_error_str,
		   byte_position, (dip->di_records_read + 1));
	}
	syslog(LOG_ERR, "(%d) Data expected = %#x, data found = %#x, byte count = %u\n",
			dip->di_process_id, expected_data, data_found, (unsigned int)byte_count);
    }
#endif /* defined(SYSLOG) */
}

/*
 * ReportDeviceInfo() - Report Device Information.
 *
 * Inputs:
 *	dip = The device information pointer.
 *	byte_count = The request byte count.
 *	byte_position = Position of failure (DC).
 *	eio_error = Indicates if an EIO error occurred.
 *
 * Return Value:
 *	void
 * 
 * TODO: This code is ancient, overloaded, and clearly needs rewritten.
 * 	 Perhaps one day I'll get around to it, but it's messey as heck!
 */
void
ReportDeviceInfo (
	struct dinfo	*dip,
	size_t		byte_count,
	u_int		byte_position,
	bool		eio_error )
{
    /* With multiple devices, this identification is important! */
    LogMsg (efp, logLevelError, (PRT_NOFLUSH|PRT_NOLEVEL),
	    "Device name: %s\n", dip->di_dname);
#if defined(SCSI)
    if (dip->di_serial_number) {
	LogMsg (efp, logLevelError, (PRT_NOFLUSH|PRT_NOLEVEL),
		"Device serial number: %s\n", dip->di_serial_number);
    } else if (dip->di_device_id) {
	LogMsg (efp, logLevelError, (PRT_NOFLUSH|PRT_NOLEVEL),
		"Device identifier: %s\n", dip->di_device_id);
    }
#endif /* defined(SCSI) */

    /*
     * For disk devices, also report the relative block address.
     */
    if (dip->di_random_access) {
        large_t lba;
	OFF_T current_offset;
	OFF_T starting_offset;
	u_int32 dsize = dip->di_dsize;
	/* Note: This is position in block, not a file offset! */
	u_int32 block_offset = (byte_position % dsize);

#if defined(AIO)
	/*
	 * TODO: This AIO junk needs cleaned up!
	 */
	if (dip->di_aio_flag) {
	    starting_offset = dip->di_current_acb->aio_offset;
	    current_offset = starting_offset;
	} else if (dip->di_mmap_flag) {
	    starting_offset = dip->di_offset;
	    current_offset = starting_offset;
	} else {
	    current_offset = get_position (dip);
	    starting_offset = (current_offset - byte_count);
	}
#else /* !defined(AIO) */
	if (dip->di_mmap_flag) {
	    starting_offset = dip->di_offset;
	    current_offset = starting_offset;
	} else {
	    current_offset = get_position (dip);
	    starting_offset = (current_offset - byte_count);
	}
#endif /* defined(AIO) */

	lba = WhichBlock ((starting_offset + byte_position), dsize);

        dip->di_lba = lba;	/* Only used by trigger script! */
        /*
         * Only save the offset for AIO, since our normal read/write
         * functions maintain the file offset themselves.  If we do
         * this here, our next offset will be incorrect breaking lba
         * values when using IOT pattern (for example).
	 *
	 * Note: di_offset is updated in success case, not on errors!
	 * If incorrectly updated, the new reread logic will fail!
         */
        if (dip->di_aio_flag && eio_error) {
            dip->di_offset = current_offset;
        }
        dip->di_position = block_offset;

	LogMsg (efp, logLevelError, (PRT_NOFLUSH|PRT_NOLEVEL),
		"Relative block number where the error occurred is " LUF ","
                " position " FUF, lba, (starting_offset + byte_position));
	if (block_offset) {
	    LogMsg (efp, logLevelError, (PRT_NOIDENT|PRT_NOLEVEL),
		    " (offset %u)\n", block_offset);
	} else {
	    LogMsg (efp, logLevelError, (PRT_NOIDENT|PRT_NOLEVEL), "\n");
	}
#if defined(SYSLOG)
	if (dip->di_syslog_flag) {
	    char *bp = dip->di_msg_buffer;
	    bp += Sprintf(bp,
			  "(%d) Device name: %s\n",
			   dip->di_process_id, dip->di_dname);
	    syslog(LOG_ERR, dip->di_msg_buffer);
	    bp = dip->di_msg_buffer;
# if defined(SCSI)
	    if (dip->di_serial_number) {
		bp += Sprintf(bp,
			      "(%d) Device serial number: %s\n",
			       dip->di_process_id, dip->di_serial_number);
	    } else if (dip->di_device_id) {
		bp += Sprintf(bp,
			      "(%d) Device identifier: %s\n", 
			      dip->di_process_id, dip->di_device_id);
	    }
# endif /* defined(SCSI) */
	    syslog(LOG_ERR, dip->di_msg_buffer);
	    bp = dip->di_msg_buffer;
	    bp += Sprintf(bp,
		  "(%d) Relative block number where the error occurred is " LUF ","
		  " position " FUF, dip->di_process_id, lba, (starting_offset + byte_position));
	    if (block_offset) {
		bp += Sprintf(bp, " (offset %u)\n", block_offset);
  	    } else {
                bp += Sprintf(bp, "\n");
            }
	    syslog(LOG_ERR, dip->di_msg_buffer);
	}
#endif /* defined(SYSLOG) */

	/*
	 * Seek past the erroring block, so we can continue our I/O.
	 */
	if (eio_error) {
	    current_offset += dsize;
	    if (dip->di_mode == READ_MODE) {
		dip->di_fbytes_read += dsize;
	    } else {
		dip->di_fbytes_written += dsize;
	    }
	    (void) set_position (dip, current_offset, FALSE);

	    /*
	     * When copying data, properly position the output device too.
	     */
	    if ( (dip->di_io_mode != TEST_MODE)		&&
		 (dip != dip->di_output_dinfo)		&&
		 dip->di_output_dinfo->di_random_access ) {
		/*
		 * NOTE: Output device could be at a different offset.
		 */
		struct dinfo *odip = dip->di_output_dinfo;
		OFF_T output_offset = get_position(odip);
		output_offset += dsize;
		if (dip->di_mode == READ_MODE) {
		    dip->di_fbytes_read += dsize;
		} else {
		    dip->di_fbytes_written += dsize;
		}
		(void) set_position (odip, output_offset, FALSE);
	    }
	}
    }
}

/************************************************************************
 *									*
 * ReportLbDataError() - Report Logical Block Data Compare Error.	*
 *									*
 * Inputs:	dip = The device info structure.			*
 *		lba = The starting logical block address.		*
 *		byte_count = The byte count of the last request.	*
 *		byte_position = Data buffer index where compare failed.	*
 *		expected_data = The expected data.			*
 *		data_found = The incorrect data found.			*
 *									*
 * Return Value: Void.							*
 *									*
 ************************************************************************/
void
ReportLbdataError (
	struct dinfo	*dip,
        u_int32		lba,
	u_int32		byte_count,
	u_int32		byte_position,
	u_int32		expected_data,
	u_int32		data_found )
{
    if (hazard_flag) {
	LogMsg (efp, logLevelCrit, 0, "CORRUPTION:\n");
    }
    if (dip->di_history_size) dump_history_data(dip);
    (void) RecordError(dip);
    if (dip->di_dtype->dt_dtype == DT_TAPE) {
	Fprintf ("File #%lu, %s %u in record number %u\n", (dip->di_files_read + 1),
		compare_error_str, byte_position, (dip->di_records_read + 1));
    } else if (dip->di_multiple_files) {
	Fprintf ("File %s, %s %u in record number %u\n", dip->di_dname,
		compare_error_str, byte_position, (dip->di_records_read + 1));
    } else {
	Fprintf ("%s %u in record number %u\n",
		compare_error_str, byte_position, (dip->di_records_read + 1));
    }

    ReportDeviceInfo (dip, byte_count, byte_position, FALSE);

    Fprintf ("Block expected = %u (0x%08x), block found = %u (0x%08x), count = %u\n",
		expected_data, expected_data, data_found, data_found, byte_count);

#if defined(SYSLOG)
    if (dip->di_syslog_flag) {
	if (dip->di_dtype->dt_dtype == DT_TAPE) {
	    syslog(LOG_ERR, "(%d) File #%lu, %s %u in record number %lu\n",
		   dip->di_process_id, (dip->di_files_read + 1), compare_error_str, byte_position,
		   (dip->di_records_read + 1));
	} else if (dip->di_multiple_files) {
	    syslog(LOG_ERR, "(%d) File %s, %s %u in record number %lu\n",
		   dip->di_process_id, dip->di_dname, compare_error_str, byte_position,
		   (dip->di_records_read + 1));
	} else {
	    syslog(LOG_ERR, "(%d) %s %u in record number %lu\n",
		   dip->di_process_id, compare_error_str, byte_position, (dip->di_records_read + 1));
	}
	syslog(LOG_ERR, "(%d) Block expected = %u (0x%08x), block found = %u (0x%08x), count = %u\n",
		dip->di_process_id, expected_data, expected_data, data_found, data_found, byte_count);
    }
#endif /* defined(SYSLOG) */
}

/*
 * Check for all hex characters in string.
 */
int
IS_HexString (char *s)
{
	if ( (*s == '0') &&
	     ((*(s+1) == 'x') || (*(s+1) == 'X')) ) {
	    s += 2;	/* Skip over "0x" or "0X" */
	}
	while (*s) {
	    if ( !isxdigit((int)*s++) ) return (FALSE);
	}
	return (TRUE);
}

/*
 * FmtKeepAlive() - Format Keepalive Message.
 *
 * Special Format Characters:
 *
 *      %b = The bytes read or written.
 *      %B = The total bytes read and written.
 *      %c = The count of records this pass.
 *      %C = The total records for this test.
 *	%d = The device name.
 *	%D = The real device name.
 *      %e = The number of errors.
 *      %E = The error limit.
 *      %f = The files read or written.
 *      %F = The total files read and written.
 *	%h = The host name.
 *	%H = The full host name.
 *      %i = The I/O mode ("read" or "write").
 *      %k = The kilobytes this pass.
 *      %K = The total kilobytes this test.
 *      %l = The logical blocks read or written.
 *      %L = The total blocks read and written.
 *      %m = The megabytes this pass.
 *      %M = The total megabytes this test.
 *	%p = The pass count.
 *	%P = The pass limit.
 *      %r = The records read this pass.
 *      %R = The total records read this test.
 *      %s = The seconds this pass.
 *      %S = The total seconds this test.
 *      %t = The pass elapsed time.
 *      %T = The total elapsed time.
 *	%u = The user (login) name.
 *      %w = The records written this pass.
 *      %W = The total records written this test.
 *
 * Performance Keywords: (upper and lower case, see below)
 *      %bps  = The bytes per second.
 *      %lbps = The blocks per second.
 *      %kbps = The kilobytes per second.
 *      %mbps = The megabytes per second.
 *      %iops = The I/O's per second.
 *      %spio = The seconds per I/O.
 * 
 * File Position Keywords:
 * 	%lba = The current logical block address.
 * 	%offset = The current file offset.
 *
 * Lowercase means per pass stats, while uppercase means total stats.
 *
 * Inputs:
 *	dip = The device information pointer.
 *	keepalivefmt = Keepalive formal control string.
 *	buffer = Buffer for formatted message.
 *
 * Outputs:
 *	Returns SUCCESS or FAILURE.
 */
int
FmtKeepAlive (struct dinfo *dip, char *keepalivefmt, char *buffer)
{
  char    *from = keepalivefmt;
  char    *to = buffer;
  ssize_t length = strlen(keepalivefmt);
#if defined(WIN32)
  int	  len = MAXHOSTNAMELEN;
  DWORD	  size = 256;
#endif /* defined(WIN32) */

  while (length-- > 0) {
    bool full_info = FALSE;
    /*
     * Running out of single characters, use key words for performance.
     */
    if (*from == '%') {
      char *key = (from + 1);
      /*
       * The approach taken is: lower = pass, upper = total
       */
      if (strncasecmp(key, "bps", 3) == 0) {
        int secs;
        large_t bytes;
        bool pass_stats = (strncmp(key, "bps", 3) == 0);
        bytes = GetStatsValue(dip, ST_BYTES, pass_stats, &secs);
        if (secs) {
          to += Sprintf(to, "%.3f", ((double)bytes / (double)secs));
        } else {
          to += Sprintf(to, "0.000");
        }
        length -= 3;
        from += 4;
        continue;
      } else if (strncasecmp(key, "lbps", 4) == 0) {
        int secs;
        large_t blocks;
        bool pass_stats = (strncmp(key, "lbps", 4) == 0);
        blocks = GetStatsValue(dip, ST_BLOCKS, pass_stats, &secs);
        if (secs && dip->di_dsize) {
          to += Sprintf(to, "%.3f", ((double)blocks / (double)secs));
        } else {
          to += Sprintf(to, "0.000");
        }
        length -= 4;
        from += 5;
        continue;
      } else if (strncasecmp(key, "kbps", 4) == 0) {
        int secs;
        large_t bytes;
        bool pass_stats = (strncmp(key, "kbps", 4) == 0);
        bytes = GetStatsValue(dip, ST_BYTES, pass_stats, &secs);
        if (secs) {
          to += Sprintf(to, "%.3f", ((double)bytes / (double)KBYTE_SIZE) / secs);
        } else {
          to += Sprintf(to, "0.000");
        }
        length -= 4;
        from += 5;
        continue;
      } else if (strncasecmp(key, "mbps", 4) == 0) {
        int secs;
        large_t bytes;
        bool pass_stats = (strncmp(key, "mbps", 4) == 0);
        bytes = GetStatsValue(dip, ST_BYTES, pass_stats, &secs);
        if (secs) {
          to += Sprintf(to, "%.3f", ((double)bytes / (double)MBYTE_SIZE) / secs);
        } else {
          to += Sprintf(to, "0.000");
        }
        length -= 4;
        from += 5;
        continue;
      } else if (strncasecmp(key, "iops", 4) == 0) {
        int secs;
        u_long records;
        bool pass_stats = (strncmp(key, "iops", 4) == 0);
        records = (u_long)GetStatsValue(dip, ST_RECORDS, pass_stats, &secs);
        if (secs) {
          to += Sprintf(to, "%.3f", ((double)records / (double)secs));
        } else {
          to += Sprintf(to, "0.000");
        }
        length -= 4;
        from += 5;
        continue;
      } else if (strncasecmp(key, "spio", 4) == 0) {
        int secs;
        u_long records;
        bool pass_stats = (strncmp(key, "spio", 4) == 0);
        records = (u_long)GetStatsValue(dip, ST_RECORDS, pass_stats, &secs);
        if (records) {
          to += Sprintf(to, "%.4f", ((double)secs / (double)records));
        } else {
          to += Sprintf(to, "0.0000");
        }
        length -= 4;
        from += 5;
        continue;
      } else if (strncasecmp(key, "lba", 3) == 0) {
        OFF_T offset;
        offset = (OFF_T)GetStatsValue(dip, ST_OFFSET, FALSE, NULL);
        to += Sprintf(to, "%u", (dip->di_dsize) ? (u_int32)(offset / dip->di_dsize) : 0);
        length -= 3;
        from += 4;
        continue;
      } else if (strncasecmp(key, "offset", 6) == 0) {
        OFF_T offset;
        offset = (OFF_T)GetStatsValue(dip, ST_OFFSET, FALSE, NULL);
        to += Sprintf(to, FUF, offset);
        length -= 6;
        from += 7;
        continue;
      }
    }
    switch (*from) {
      case '%': {
        if (length) {
          switch (*(from + 1)) {
            case 'b': {
              if (dip->di_raw_flag || (dip->di_io_mode == COPY_MODE)) {
                to += Sprintf(to, LUF,
                              (dip->di_dbytes_read + dip->di_dbytes_written));
              } else if (dip->di_mode == READ_MODE) {
                to += Sprintf(to, LUF, dip->di_dbytes_read);
              } else {
                to += Sprintf(to, LUF, dip->di_dbytes_written);
              }
              break;
            }
            case 'B': {
              to += Sprintf(to, LUF,
                    (dip->di_total_bytes + dip->di_dbytes_read + dip->di_dbytes_written));
              break;
            }
            case 'c': {
              if (dip->di_raw_flag || (dip->di_io_mode == COPY_MODE)) {
                to += Sprintf(to, "%lu",
                              (dip->di_records_read + dip->di_records_written));
              } else if (dip->di_mode == READ_MODE) {
                to += Sprintf(to, "%lu", dip->di_records_read);
              } else {
                to += Sprintf(to, "%lu", dip->di_records_written);
              }
              break;
            }
            case 'C': {
              to += Sprintf(to, LUF,
                    (dip->di_total_records + dip->di_total_partial +
                     dip->di_records_read + dip->di_records_written));
              break;
            }
            case 'd': {
              to += Sprintf(to, "%s", dip->di_dname);
              break;
            }
            case 'D': {
              if ( dip->di_device ) { /* Only if known. */
                to += Sprintf(to, "%s", dip->di_device);
              } else {
                struct dtype *dtp = dip->di_dtype;
                to += Sprintf(to, "%s", dtp->dt_type);
              }
              break;
            }
            case 'e': {
              to += Sprintf(to, "%lu", dip->di_total_errors);
			    // TODO: Need per pass vs. total error formats!
	      		    // compare errors not included, so inaccurate!
                            // (dip->di_read_errors + dip->di_write_errors));
              break;
            }
            case 'E': {
              to += Sprintf(to, "%lu", dip->di_error_limit);
              break;
            }
            case 'f': {
              if (dip->di_raw_flag || (dip->di_io_mode == COPY_MODE)) {
                to += Sprintf(to, "%lu",
                              (dip->di_files_read + dip->di_files_written));
              } else if (dip->di_mode == READ_MODE) {
                to += Sprintf(to, "%lu", dip->di_files_read);
              } else {
                to += Sprintf(to, "%lu", dip->di_files_written);
              }
              break;
            }
            case 'F': {
              to += Sprintf(to, LUF,
                    (dip->di_total_files + dip->di_files_read + dip->di_files_written));
              break;
            }
            case 'H':
              full_info = TRUE;
              /* FALL THROUGH */
            case 'h': {
              char *p, hostname[MAXHOSTNAMELEN];
#if defined(WIN32)
	      if ( (GetComputerNameEx(ComputerNameDnsFullyQualified,
				      hostname, &len)) == 0) {
		wPerror("GetComputerNameEx() failed!");
#else /* !defined(WIN32) */
              if ( gethostname(hostname, sizeof(hostname)) ) {
                perror("gethostname()");
#endif /* defined(WIN32) */
                return(FAILURE);
              }
              if ( !full_info ) {
                if ( (p = strchr(hostname, '.')) ) {
                  *p = '\0';
                }
              }
              to += Sprintf(to, "%s", hostname);
              break;
            }
            case 'i': {
              if (dip->di_raw_flag) {
                to += Sprintf(to, "raw");
              } else if (dip->di_mode == READ_MODE) {
                to += Sprintf(to, "read");
              } else {
                to += Sprintf(to, "write");
              }
              break;
            }
            case 'k': {
              if (dip->di_raw_flag || (dip->di_io_mode == COPY_MODE)) {
                to += Sprintf(to, "%.3f",
                              (((double)dip->di_dbytes_read + (double)dip->di_dbytes_written)
                              / (double)KBYTE_SIZE));
              } else if (dip->di_mode == READ_MODE) {
                to += Sprintf(to, "%.3f",
                              ((double)dip->di_dbytes_read / (double)KBYTE_SIZE));
              } else {
                to += Sprintf(to, "%.3f",
                              ((double)dip->di_dbytes_written / (double)KBYTE_SIZE));
              }
              break;
            }
            case 'K': {
              to += Sprintf(to, "%.3f",
                            (((double)dip->di_total_bytes +
                              (double)dip->di_dbytes_read + (double)dip->di_dbytes_written)
                            / (double)MBYTE_SIZE));
              break;
            }
            case 'l': {
              if (dip->di_dsize <= 1) { /* Device without a size, tape, etc. */
                  to += Sprintf(to, "<n/a>");
              } else if (dip->di_raw_flag || (dip->di_io_mode == COPY_MODE)) {
                to += Sprintf(to, LUF,
                              ((dip->di_dbytes_read + dip->di_dbytes_written)
                              / dip->di_dsize));
              } else if (dip->di_mode == READ_MODE) {
                to += Sprintf(to, LUF, (dip->di_dbytes_read / dip->di_dsize));
              } else {
                to += Sprintf(to, LUF, (dip->di_dbytes_written / dip->di_dsize));
              }
              break;
            }
            case 'L': {
              if (dip->di_dsize <= 1) { /* Device without a size, tape, etc. */
                  to += Sprintf(to, "<n/a>");
              } else {
                  to += Sprintf(to, LUF,
              ((dip->di_total_bytes + dip->di_dbytes_read + dip->di_dbytes_written) / dip->di_dsize));
              }
              break;
            }
            case 'm': {
              if (dip->di_raw_flag || (dip->di_io_mode == COPY_MODE)) {
                to += Sprintf(to, "%.3f",
                              (((double)dip->di_dbytes_read + (double)dip->di_dbytes_written)
                              / (double)MBYTE_SIZE));
              } else if (dip->di_mode == READ_MODE) {
                to += Sprintf(to, "%.3f",
                              ((double)dip->di_dbytes_read / (double)MBYTE_SIZE));
              } else {
                to += Sprintf(to, "%.3f",
                              ((double)dip->di_dbytes_written / (double)MBYTE_SIZE));
              }
              break;
            }
            case 'M': {
              to += Sprintf(to, "%.3f",
                            (((double)dip->di_total_bytes +
                              (double)dip->di_dbytes_read + (double)dip->di_dbytes_written)
                            / (double)MBYTE_SIZE));
              break;
            }
            case 'p': {
              to += Sprintf(to, "%lu", dip->di_pass_count);
              break;
            }
            case 'P': {
              to += Sprintf(to, "%lu", dip->di_pass_limit);
              break;
            }
            case 'r': {
              to += Sprintf(to, "%lu", dip->di_records_read);
              break;
            }
            case 'R': {
              to += Sprintf(to, LUF,
                    (dip->di_total_records_read + dip->di_total_partial_reads + dip->di_records_read));
              break;
            }
            case 's': {
              int secs;
              dip->di_end_time = times (&dip->di_etimes);
              secs = ((dip->di_end_time - dip->di_pass_time) / hz);
              to += Sprintf(to, "%d", secs);
              break;
            }
            case 'S': {
              int secs;
              dip->di_end_time = times (&dip->di_etimes);
              secs = ((dip->di_end_time - dip->di_start_time) / hz);
              to += Sprintf(to, "%d", secs);
              break;
            }
            case 't': {
              clock_t at;
              dip->di_end_time = times (&dip->di_etimes);
              at = dip->di_end_time - dip->di_pass_time;
              to = bformat_time(to, at);
              break;
            }
            case 'T': {
              clock_t at;
              dip->di_end_time = times (&dip->di_etimes);
              at = dip->di_end_time - dip->di_start_time;
              to = bformat_time(to, at);
              break;
            }
            case 'u': {
#if defined(WIN32)
	      DWORD size = 256;
	      TCHAR buf[256];
#endif /* !defined(WIN32) */
              char *username = NULL;
             
#if defined(WIN32)
	      GetUserName(buf, &size);
	      username = buf;
#else /* if !defined(WIN32) */
              username = getlogin();
#endif /* !defined(WIN32) */
	      if (username) {
                to += Sprintf(to, "%s", username);
              } else {
#if defined(WIN32)
		Fprintf("GetUserName failed !\n");
#else /*if !defined(WIN32) */
                perror("getlogin()");
#endif /* !defined(WIN32) */
              }
              break;
            }
            case 'w': {
              to += Sprintf(to, "%lu", dip->di_records_written);
              break;
            }
            case 'W': {
              to += Sprintf(to, LUF,
                    (dip->di_total_records_written + dip->di_total_partial_writes + dip->di_records_written));
              break;
            }
            default: {
              *to++ = *from;
              *to++ = *(from + 1);
              break;
            }
          } /* end switch */
          length--;
          from += 2;
          break;
        } else { /* !length */
          *to++ = *from++;
        } /* end if length */
        break;
      } /* end case '%' */
      case '\\': {
        if (length) {
          switch (*(from + 1)) {
            case 'n': {
              to += Sprintf(to, "\n");
              break;
            }
            case 't': {
              to += Sprintf(to, "\t");
              break;
            }
            default: {
              *to++ = *from;
              *to++ = *(from + 1);
              break;
            }
          } /* end switch */
          length--;
          from += 2;
          break;
        } else { /* !length */
          *to++ = *from++;
        } /* end if length */
        break;
      } /* end case '\' */
      default: {
        *to++ = *from++;
        break;
      }
    }
  }
  *to = '\0';       /* NULL terminate! */
  return(SUCCESS);
}

/*
 * GetStatsValue() - Simple function to obtain stats values.
 *
 * Inputs:
 *    dip = The device information pointer.
 *    stv = The stats value to obtain.
 *    pass_stats = Boolean true if pass stats.
 *    secs = Optional pointer to store seconds.
 *
 * Return Value:
 *    Returns the stats value (64 bits).
 */
large_t
GetStatsValue(struct dinfo *dip, stats_value_t stv, bool pass_stats, int *secs)
{
   large_t value;

   switch (stv) {
     case ST_BYTES: {
       if (pass_stats) {
          if (dip->di_raw_flag || (dip->di_io_mode == COPY_MODE)) {
            value = (dip->di_dbytes_read + dip->di_dbytes_written);
          } else if (dip->di_mode == READ_MODE) {
            value = dip->di_dbytes_read;
          } else {
            value = dip->di_dbytes_written;
          }
        } else {
          value = (dip->di_total_bytes + dip->di_dbytes_read + dip->di_dbytes_written);
        }
        break;
     }
     case ST_BLOCKS: {
       value = GetStatsValue(dip, ST_BYTES, pass_stats, secs);
       if (dip->di_dsize) {
         value /= dip->di_dsize; /* Convert to logical blocks. */
       }
       break;
     }
     case ST_FILES: {
       if (pass_stats) {
         if (dip->di_raw_flag || (dip->di_io_mode == COPY_MODE)) {
           value = (dip->di_files_read + dip->di_files_written);
         } else if (dip->di_mode == READ_MODE) {
           value = dip->di_files_read;
         } else {
           value = dip->di_files_written;
         }
       } else {
         value = (dip->di_total_files + dip->di_files_read + dip->di_files_written);
       }
       break;
     }
     case ST_RECORDS: {
       if (pass_stats) {
         if (dip->di_raw_flag || (dip->di_io_mode == COPY_MODE)) {
           value = (dip->di_records_read + dip->di_records_written);
         } else if (dip->di_mode == READ_MODE) {
           value = dip->di_records_read;
         } else {
           value = dip->di_records_written;
         }
       } else {
         value = (dip->di_total_records + dip->di_total_partial +
                  dip->di_records_read + dip->di_records_written);
       }
       break;
     }
     case ST_OFFSET: {
#if defined(AIO)
	if (dip->di_aio_flag && dip->di_current_acb) {
	    value = dip->di_current_acb->aio_offset;
	} else {
	    value = dip->di_offset;
	}
#else /* !defined(AIO) */
	value = dip->di_offset;
#endif /* defined(AIO) */
	break;
     }
     default:
       Fprintf("Invalid stats value request, %d\n", stv);
       value = 0;
       //abort();
   }
   if (secs) {
     dip->di_end_time = times(&dip->di_etimes);
     if (pass_stats) {
       *secs = ((dip->di_end_time - dip->di_pass_time) / hz);
     } else {
       *secs = ((dip->di_end_time - dip->di_start_time) / hz); 
     }
   }
   return (value);
}

/*
 * FmtPrefix() - Format the Prefix String.
 *
 * Special Format Characters:
 *
 *	%d = The device name.
 *	%D = The real device name.
 *	%h = The host name.
 *	%H = The full host name.
 *	%p = The process ID.
 *	%P = The parent process ID.
 *	%s = The device serial number.
 *	%u = The user (login) name.
 *
 * Inputs:
 *	dip = The device information pointer.
 *	prefix = The prefix string.
 *	psize = The prefix string size.
 *
 * Outputs:
 *	dip->di_fprefix_string = The formatted prefix string.
 *	dip->di_fprefix_size = The formatted prefix string size.
 *
 * Return Value:
 *	Returns SUCCESS or FAILURE.
 */
int
FmtPrefix (struct dinfo *dip, char *prefix, int psize)
{
    char	*from = prefix;
    char	*buffer, *to;
    int		length = psize;
#if defined(WIN32)
    int		len = MAXHOSTNAMELEN;
    DWORD	size = 256;
    TCHAR	buf[256];
    char	*username;
#endif /* defined(WIN32) */

    if (dip->di_fprefix_string) {
	free(dip->di_fprefix_string);
	dip->di_fprefix_string = NULL;
    }
#if 0
    /* This looks problematic to Robin! 11/21/2009 */
    if (strstr (from, "%") == NULL) {
        /* See comments below. */
        if (dip->di_io_type != RANDOM_IO) {
	    dip->di_fprefix_string = strdup(prefix_string);
	    dip->di_fprefix_size = prefix_size;
	    return (SUCCESS);
        }
    }
#endif
    buffer = to = Malloc(KBYTE_SIZE);
    while (length--) {
	bool full_info = FALSE;
	switch (*from) {
	    case '%':
		if (length) {
		    switch (*(from + 1)) {
			case 'd': {
			    to += Sprintf(to, "%s", dip->di_dname);
			    break;
			}
			case 'D': {
			    if ( dip->di_device ) { /* Only if known. */
				to += Sprintf(to, "%s", dip->di_device);
			    } else {
				struct dtype *dtp = dip->di_dtype;
				to += Sprintf(to, "%s", dtp->dt_type);
			    }
			    break;
			}
			case 'H':
			    full_info = TRUE;
			    /* FALL THROUGH */
			case 'h': {
			    char *p, hostname[MAXHOSTNAMELEN];
#if defined(WIN32)
			    if (( GetComputerName(hostname, &len)) == 0) {
			        Fprintf("GetComputerName failed!\n");
#else /* !defined(WIN32) */
			    if ( gethostname(hostname, sizeof(hostname)) ) {
				perror("gethostname()");
#endif /* defined(WIN32) */
				return (FAILURE);
			    }
			    if ( !full_info ) {
				if ( (p = strchr(hostname, '.')) ) {
				    *p = '\0';
				}
			    }
			    to += Sprintf(to, "%s", hostname);
			    break;
			}
			case 'p': {
			    pid_t pid = getpid();
			    to += Sprintf(to, "%d", pid);
			    break;
			}
			case 'P': {
#if defined(WIN32)
			    LogMsg (efp,logLevelError,0,
				   "option P currently not supported\n");
			    exit(FAILURE);
#else /* !defined(WIN32) */
			    pid_t ppid = getppid();
			    to += Sprintf(to, "%d", ppid);
#endif /* defined(WIN32) */
			    break;
			}
#if defined(SCSI)
			/* Note: I'd prefer %serial, but not yet! */
			case 's': {
			    if (dip->di_serial_number) {
				to += Sprintf(to, "%s", dip->di_serial_number);
			    }
			    break;
			}
#endif /* defined(SCSI) */
			case 'u': {
#if defined(WIN32)
			    GetUserName(buf, &size);
			    username = buf;
#else /* !defined(WIN32) */
			    char *username = getlogin();
#endif /* defined(WIN32) */
			    if (username) {
				to += Sprintf(to, "%s", username);
			    } else {
#if defined(WIN32)
				Fprintf("GetUserName failed !\n");
#else /* !defined(WIN32) */
				perror("getlogin()");
#endif /* defined(WIN32) */
			    }
			    break;
			}
			default: {
			    *to++ = *from;
			    *to++ = *(from + 1);
			    break;
			}
		    }
		    length--;
		    from += 2;
		    break;
		}
		/* FALLTHROUGH */
	    default: {
		*to++ = *from++;
		break;
	    }
	}
    }
    dip->di_fprefix_size = strlen(buffer) + 1;	/* Include NULL! */
    /*
     * To avoid problems with random I/O, make the prefix string
     * modulo the lba (iot or lbdata) or our 4 byte data pattern.
     * Otherwise, random I/O fails with a partial pattern.
     *
     * NOTE: *Always* roundup, since one pass may use sequential
     * while the next (read-only) pass may use random, we need the
     * prefix/data to match up in both cases!
     */
    dip->di_fprefix_size = roundup(dip->di_fprefix_size, sizeof(u_int32));
    dip->di_fprefix_string = Malloc(dip->di_fprefix_size);
    (void)strcpy(dip->di_fprefix_string, buffer);
    free (buffer);
    return (SUCCESS);
}

/*
 * String copy with special mapping.
 */
int
StrCopy (void *to_buffer, void *from_buffer, size_t length)
{
	u_char *to = (u_char *) to_buffer;
	u_char *from = (u_char *) from_buffer;
	u_char c, key;
	int count = 0;

	while ( length ) {
	    c = *from++; length--;
	    if ( (c != '^') && (c != '\\') ) {
		*to++ = c; count++;
		continue;
	    }
	    if (length == 0) {
		*to++ = c; count++;
		continue;
	    }
	    if (c == '^') {			/* control/X */
		c = *from++; length--;
		*to++ = (c & 037); count++;
		continue;
	    }
	    c = *from++; length--;
	    if      (c == 'a')	key = '\007';	/* alert (bell) */
	    else if (c == 'b')	key = '\b';	/* backspace */
	    else if ( (c == 'e') || (c == 'E') )
				key = '\033';	/* escape */
	    else if (c == 'f')	key = '\f';	/* formfeed */
	    else if (c == 'n')	key = '\n';	/* newline */
	    else if (c == 'r')	key = '\r';	/* return */
	    else if (c == 't')	key = '\t';	/* tab */
	    else if (c == 'v')	key = '\v';	/* vertical tab */
	    else if ( (length >= 2) &&
		      ((c == 'x') || (c == 'X')) ) { /* hex */
		int cnt;
		u_char val = 0;
		for (cnt = 0, key = 0; cnt < 2; cnt++) {
		    c = *from++; count--;
		    if ( isxdigit(c) ) {
			if ( ('c' >= '0') && (c <= '9') )
			    val = (c - '0');
			else if ( ('c' >= 'a') && (c <= 'f') )
			    val = 10 + (c - 'a');
			else if ( ('c' >= 'A') && (c <= 'F') )
			    val = 10 + (c - 'A');
		    } else {
			key = c;
			break;
		    }
		    key = (key << 4) | val;
		}
	    } else if ( (length >= 3) &&
			((c >= '0') && (c <= '7')) ) { /* octal */
		int cnt;
		for (cnt = 0, key = 0; cnt < 3; cnt++) {
		    key = (key << 3) | (c - '0');
		    c = *from++; length--;
		    if (c < '0' || c > '7') break;
		}
	    } else {
		key = c;	/* Nothing special here... */
	    }
	    *to++ = key; count++;
	}
	return (count);
}

/************************************************************************
 *									*
 * stoh() - Convert SCSI bytes to Host short/int/long format.		*
 *									*
 * Description:								*
 *	This function converts SCSI (big-endian) byte ordering to the	*
 * format necessary by this host.					*
 *									*
 * Inputs:	bp = Pointer to SCSI data bytes.			*
 *		size = The conversion size in bytes.			*
 *									*
 * Return Value:							*
 *		Returns a long value with the proper byte ordering.	*
 *									*
 ************************************************************************/
large_t
stoh (unsigned char *bp, size_t size)
{
	large_t value = 0L;

	switch (size) {

	    case sizeof(u_char):
		value = (u_long) bp[0];
		break;

	    case sizeof(u_short):
		value = ( ((u_long)bp[0] << 8) | (u_long)bp[1] );
		break;

	    case 0x03:
		value = ( ((u_long)bp[0] << 16) | ((u_long)bp[1] << 8) |
			  (u_long) bp[2] );
		break;

	    case sizeof(u_int):
		value = ( ((u_long)bp[0] << 24) | ((u_long)bp[1] << 16) |
			  ((u_long)bp[2] << 8) | (u_long)bp[3]);
		break;

	    case 0x05:
		value = ( ((large_t)bp[0] << 32L) | ((large_t)bp[1] << 24) |
			  ((large_t)bp[2] << 16) | ((large_t)bp[3] << 8) |
			  (large_t)bp[4] );
		break;

	    case 0x06:
		value = ( ((large_t)bp[0] << 40L) | ((large_t)bp[1] << 32L) |
			  ((large_t)bp[2] << 24) | ((large_t)bp[3] << 16) |
			  ((large_t)bp[4] << 8) | (large_t)bp[5] );
		break;

	    case 0x07:
		value = ( ((large_t)bp[0] << 48L) | ((large_t)bp[1] << 40L) |
			  ((large_t)bp[2] << 32L) | ((large_t)bp[3] << 24) |
			  ((large_t)bp[4] << 16) | ((large_t)bp[5] << 8) |
			  (large_t)bp[6] );
		break;

	    case sizeof(large_t):
		value = ( ((large_t)bp[0] << 56L) | ((large_t)bp[1] << 48L) |
			  ((large_t)bp[2] << 40L) | ((large_t)bp[3] << 32L) |
			  ((large_t)bp[4] << 24) | ((large_t)bp[5] << 16) |
			  ((large_t)bp[6] << 8) | (large_t)bp[7] );
		break;

	    default:
		Fprintf (bad_conversion_str, size);
		break;

	}
	return (value);
}

/************************************************************************
 *									*
 * htos() - Convert Host short/int/long format to SCSI bytes.		*
 *									*
 * Description:								*
 *	This function converts host values to SCSI (big-endian) byte	*
 * ordering.								*
 *									*
 * Inputs:	bp = Pointer to SCSI data bytes.			*
 *		value = The numeric value to convert.			*
 *		size = The conversion size in bytes.			*
 *									*
 * Return Value:							*
 *		Void.							*
 *									*
 ************************************************************************/
void
htos (unsigned char *bp, large_t value, size_t size)
{
	switch (size) {

	    case sizeof(u_char):
		bp[0] = (u_char) value;
		break;

	    case sizeof(u_short):
		bp[0] = (u_char) (value >> 8);
		bp[1] = (u_char) value;
		break;

	    case 0x03:
		bp[0] = (u_char) (value >> 16);
		bp[1] = (u_char) (value >> 8);
		bp[2] = (u_char) value;
		break;

	    case sizeof(u_int):
		bp[0] = (u_char) (value >> 24);
		bp[1] = (u_char) (value >> 16);
		bp[2] = (u_char) (value >> 8);
		bp[3] = (u_char) value;
		break;

	    case 0x05:
		bp[0] = (u_char) (value >> 32L);
		bp[1] = (u_char) (value >> 24);
		bp[2] = (u_char) (value >> 16);
		bp[3] = (u_char) (value >> 8);
		bp[4] = (u_char) value;
		break;

	    case 0x06:
		bp[0] = (u_char) (value >> 40L);
		bp[1] = (u_char) (value >> 32L);
		bp[2] = (u_char) (value >> 24);
		bp[3] = (u_char) (value >> 16);
		bp[4] = (u_char) (value >> 8);
		bp[5] = (u_char) value;
		break;

	    case 0x07:
		bp[0] = (u_char) (value >> 48L);
		bp[1] = (u_char) (value >> 40L);
		bp[2] = (u_char) (value >> 32L);
		bp[3] = (u_char) (value >> 24);
		bp[4] = (u_char) (value >> 16);
		bp[5] = (u_char) (value >> 8);
		bp[6] = (u_char) value;
		break;

	    case sizeof(large_t):
		bp[0] = (u_char) (value >> 56L);
		bp[1] = (u_char) (value >> 48L);
		bp[2] = (u_char) (value >> 40L);
		bp[3] = (u_char) (value >> 32L);
		bp[4] = (u_char) (value >> 24);
		bp[5] = (u_char) (value >> 16);
		bp[6] = (u_char) (value >> 8);
		bp[7] = (u_char) value;
		break;

	    default:
		Fprintf (bad_conversion_str, size);
		break;

	}
}

enum trigger_type
check_trigger_type(dinfo_t *dip, char *str)
{
    trigger_data_t *tdp = &dip->di_triggers[dip->di_num_triggers];

    if (strcmp(str, "br") == 0) {
        return (TRIGGER_BR);
    } else if (strcmp(str, "bdr") == 0) {
        return (TRIGGER_BDR);
    } else if (strcmp(str, "lr") == 0) {
        return (TRIGGER_LR);
    } else if (strcmp(str, "seek") == 0) {
        return (TRIGGER_SEEK);
    } else if (strncmp(str, "cmd:", 4) == 0) {
	char *strp;
        tdp->td_trigger_cmd = strdup(&str[4]);
	strp = strstr(tdp->td_trigger_cmd, " ");
	/*
	 * Extra args get appended after our trigger arguments.
	 */
	if (strp) {
	    *strp++ = '\0';
	    tdp->td_trigger_args = strp;
	}
        return (TRIGGER_CMD);
    } else {
        LogMsg (efp, logLevelError, 0,
		"Valid trigger types are: br, bdr, lr, seek, or cmd:string\n");
        return (TRIGGER_INVALID);
    }
}

/*
 * ExecuteCommand() - Execute an external OS Command.
 * 
 * Inputs:
 *	dip = The device information pointer.
 * 	cmd = The command line to execute.
 * 
 * Return Value:
 * 	The exit status of the execute command line.
 */ 
int
ExecuteCommand(dinfo_t *dip, char *cmd)
{
    FILE *pipef;
    char cmd_output[STRING_BUFFER_SIZE];
    int status;

    Printf("Executing: %s\n", cmd);
    pipef = popen(cmd, "r");
    if (pipef == NULL) {
	Perror("popen() failed");
	return (FAILURE);
    }
    memset(cmd_output, '\0', sizeof(cmd_output));
    /*
     * Read and log output from the script.
     */
    while (fgets (cmd_output, sizeof(cmd_output), pipef) == cmd_output) {
	Fputs(cmd_output, ofp);
    }
    status = pclose(pipef);
# if !defined(WIN32)
    status = WEXITSTATUS(status);
# endif /* !defined(WIN32) */
    return (status);
}

/*
 * ExecuteBuffered() - Execute Cmd and Return Data.
 * 
 * Inputs:
 *	dip = The device information pointer.
 *	cmd = The command line to execute.
 *	buffer = Buffer for returned data.
 *	bufsize = The buffer size.
 * 
 * Return Value:
 *	The exit status of the execute command line.
 */ 
int
ExecuteBuffered(dinfo_t *dip, char *cmd, char *buffer, int bufsize)
{
    FILE *pipef;
    int status;
    char *bp = buffer;

    if (dip->di_pDebugFlag) {
	Printf("Executing: %s\n", cmd);
    }
    pipef = popen(cmd, "r");
    if (pipef == NULL) {
	if (dip->di_pDebugFlag) {
	    Perror("popen() failed");
	}
	return(FAILURE);
    }
    /*
     * Read and log output from the script.
     */
    while (fgets (bp, bufsize, pipef) == bp) {
	int len = strlen(bp);
	if (dip->di_pDebugFlag) {
	    Fputs(bp, ofp);
	}
	bp += len;
	bufsize -= len;
	if (len <= 0) break;
    }
    status = pclose(pipef);
#if !defined(WIN32)
    status = WEXITSTATUS(status);
#endif /* !defined(WIN32) */
    return(status);
}

/*
 * ExecuteTrigger() - Execute the User Requested Trigger.
 * 
 * Inputs:
 *	dip = The device information pointer.
 *	plus variable argument list for some triggers.
 *	For trigger script, the operation type is passed!
 * 
 * Return Value:
 *	Returns the exit status of the executed trigger.
 */ 
int
ExecuteTrigger (struct dinfo *dip, ...)
{
    char cmd[STRING_BUFFER_SIZE];
    int status = TRIGACT_CONTINUE;
    int i;

  for (i = 0; (i < dip->di_num_triggers); i++) {
      trigger_data_t *tdp = &dip->di_triggers[i];

    switch (tdp->td_trigger) {
        case TRIGGER_NONE:
            return (status);
            /*NOTREACHED*/
            break;

        case TRIGGER_BR:
#if defined(SCSI)
	    if (dip->di_scsi_flag) {
		Printf("Executing SCSI Bus Reset...\n");
		status = os_reset_bus(dip->di_sgp);
	    } else
#endif /* defined(SCSI) */
            {
		(void)sprintf(cmd, "scu -f %s br", dip->di_dname);
		status = ExecuteCommand(dip, cmd);
	    }
            break;

        case TRIGGER_BDR:
#if defined(SCSI)
	    if (dip->di_scsi_flag) {
		Printf("Executing SCSI Bus Device Reset...\n");
		status = os_reset_device(dip->di_sgp);
	    } else
#endif /* defined(SCSI) */
	    {
		(void)sprintf(cmd, "scu -f %s bdr", dip->di_dname);
		status = ExecuteCommand(dip, cmd);
	    }
            break;

	case TRIGGER_LR:
#if defined(SCSI)
	    if (dip->di_scsi_flag) {
		Printf("Executing SCSI LUN Reset...\n");
		status = os_reset_lun(dip->di_sgp);
	    } else
#endif /* defined(SCSI) */
	    {
		(void)sprintf(cmd, "scu -f %s reset lun", dip->di_dname);
		status = ExecuteCommand(dip, cmd);
	    }
	    break;
	
        case TRIGGER_SEEK: {
#if defined(SCSI)
	    if (dip->di_scsi_flag) {
		scsi_generic_t *sgp = dip->di_sgp;
		Printf("Executing Seek(10) to lba %u...\n", dip->di_lba);
		status = Seek10(sgp->fd, sgp->dsf, dip->di_sDebugFlag, dip->di_scsi_errors,
				NULL, &sgp, (unsigned int)dip->di_lba, sgp->timeout);
	    } else
#endif /* defined(SCSI) */
	    {
		(void)sprintf(cmd, "scu -f %s seek lba " LUF,
			      dip->di_dname, dip->di_lba);
		status = ExecuteCommand(dip, cmd);
	    }
            break;
        }
        case TRIGGER_CMD: {
            va_list ap;
            char *op;
	    char *cmdp = cmd;
            va_start(ap, dip);
            op = va_arg(ap, char *);
            va_end(ap);
	    /*
	     * The tester has the option of disabling standard trigger args. Why?
	     */
	    if (dip->di_trigargs_flag) {
		OFF_T offset;
#if defined(AIO)
		if (dip->di_aio_flag && dip->di_current_acb) {
		    offset = dip->di_current_acb->aio_offset;
		} else {
		    offset = dip->di_offset;
		}
#else /* !defined(AIO) */
		offset = dip->di_offset;
#endif /* defined(AIO) */
                /*
		 * Format: cmd dname op dsize offset position lba errno noprogt
		 */
		cmdp += sprintf(
			    cmdp, "%s %s %s %u " FUF " %u " LUF " %d %u",
			    tdp->td_trigger_cmd,
			    dip->di_dname, op, dip->di_dsize,
			    offset, dip->di_position,
			    dip->di_lba, dip->di_errno,
			    ( (dip->di_initiated_time)
			      ? (unsigned)(dip->di_last_alarm_time - dip->di_initiated_time)
			      : 0 ) );
	    } else {
		cmdp += sprintf(cmdp, "%s", tdp->td_trigger_cmd);
	    }
	    /*
	     * Append extra trigger arguments, if requested by the user.
	     */
	    if (tdp->td_trigger_args) {
		cmdp += sprintf(cmdp, " %s", tdp->td_trigger_args);
	    }
	    status = ExecuteCommand(dip, cmd);
            break;
        }

        default:
            LogMsg (efp, logLevelCrit, 0,
                    "Invalid trigger type detected, type = %d\n", tdp->td_trigger);
            terminate(FATAL_ERROR);
            /*NOTREACHED*/
            break;
    }
  } /* end for loop */

    if (status || dip->di_debug_flag) {
	Printf("Trigger exited with status %d!\n", status);
    }
    return (status);
}

#if defined(WIN32)

/*
 * werror_msg() - Return Windows Error Message.
 *
 * Implicit Inputs:
 *	Assume GetLastError() has the last error.
 *
 * Return Value:
 *	A pointer to a dynamically allocated message.
 *	The buffer should be freed via LocalFree().
 */
LPVOID
werror_msg(DWORD error)
{
    LPVOID msgbuf;

    if ( FormatMessage (
		       FORMAT_MESSAGE_ALLOCATE_BUFFER |
		       FORMAT_MESSAGE_FROM_SYSTEM,
		       NULL,
		       error,
		       MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
		       (LPSTR) &msgbuf,
		       0,NULL) == 0) {
	Fprintf("FormatMessage() failed with %d\n", GetLastError());
	return (NULL);
    } else {
	char *bp = strrchr(msgbuf, '\r'); /* Terminated with \r\n */
	if (bp) *bp = '\0';		  /* Just the message please! */
	return (msgbuf);
    }
}

OFF_T
SetFilePtr(HANDLE hf, OFF_T distance, DWORD MoveMethod)
{
    LARGE_INTEGER seek;

    seek.QuadPart = distance;
    seek.LowPart = SetFilePointer (hf, seek.LowPart, &seek.HighPart, MoveMethod);
    if (seek.LowPart == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR) {
	seek.QuadPart = -1;
    }
    return( (OFF_T)seek.QuadPart );
}

/*
 * syslog() - Windows API to Emulate Unix Syslog API.
 *
 * Inputs:
 *	priority = The message priority.
 *	format = Format control string.
 *	(optional arguments ...)
 *
 * Return Value:
 *	void
 */
void
syslog(int priority, char *format, ...)
{
    LPCSTR sourceName = "System";	// The event source name.
    DWORD dwEventID = 999;              // The event identifier.
    WORD cInserts = 1;                  // The count of insert strings.
    HANDLE h; 
    char msgbuf[LOG_BUFSIZE];
    LPCSTR bp = msgbuf;
    va_list ap;

    va_start(ap, format);
    (void) vsprintf(msgbuf, format, ap);
    va_end(ap);

    /*
     * Get a handle to the event log.
     */
    h = RegisterEventSource(NULL,        // Use local computer. 
                            sourceName); // Event source name. 
    if (h == NULL) {
	if (debug_flag) {
	    Fprintf("RegisterEventSource() failed, error %d", GetLastError());
	}
        return;
    }

    /*
     * Report the event.
     */
    if (!ReportEvent(h,           // Event log handle. 
            priority,             // Event type. 
            0,                    // Event category.  
            dwEventID,            // Event identifier. 
            (PSID) 0,             // No user security identifier. 
            cInserts,             // Number of substitution strings. 
            0,                    // No data. 
            &bp,                  // Pointer to strings. 
            NULL))                // No data. 
    {
	if (debug_flag) {
	    Fprintf("ReportEvent() failed, error %d", GetLastError());
	}
    }
    DeregisterEventSource(h); 
    return;
}

#endif /* defined(WIN32) */

/* ========================================================================= */

#if defined(_WIN32)
#  include <windows.h>
#else /* !defined(_WIN32) */
#  include <unistd.h>
#endif /* defined(_WIN32) */

//#define NEED_PAGESIZE	1	/* Define to obtain page size. */

/*
 * This structure is used by the page align malloc/free support code. These
 * "working sets" will contain the malloc-ed address and the page aligned
 * address for the free*() call.
 */
typedef struct mpa_ws {
    struct mpa_ws *next;	/* for the next on the list */
    void *palign_addr;		/* the page aligned address that's used */
    void *malloc_addr;		/* the malloc-ed address to free */
} MPA_WS;

/* Initialized and uninitialized data. */

static pthread_mutex_t malloc_mutex;
static int malloc_mutex_inited = 0;

static MPA_WS mpa_qhead;	/* local Q head for the malloc stuctures */

/*
 * This is a local allocation routine to alloc and return to the caller a
 * system page aligned buffer.  Enough space will be added, one more page, to
 * allow the pointers to be adjusted to the next page boundry.  A local linked
 * list will keep copies of the original and adjusted addresses.  This list 
 * will be used by free_palign() to free the correct buffer.
 *
 * Inputs:
 * 	bytes = The number of bytes to allocate.
 * 	offset = The offset to misalign from page aligned memory.
 *
 * Return Value:
 *	Returns page aligned buffer or NULL if no memory available.
 */
void *
malloc_palign(size_t bytes, int offset)
{
    int error;
    size_t alloc_size;
    MPA_WS *ws;		/* pointer for the working set */
#if defined(NEED_PAGESIZE)
    int page_size;	/* for holding the system's page size */
#if defined(_WIN32)
    SYSTEM_INFO pgsize;
#endif /* defined(_WIN32) */
#endif /* defined(NEED_PAGESIZE) */

    if (!bytes) {
        LogMsg (efp, logLevelDiag, 0,
		"malloc_palign: FIXME -> Trying to allocate %u bytes.\n", bytes);
	return(NULL);
    }
    if ( !malloc_mutex_inited ) {
	error = pthread_mutex_init(&malloc_mutex, NULL);
	if ( error ) {
	    tPerror(error, "pthread_mutex_init() failed!");
	}
	malloc_mutex_inited++;
    }
    /*
     * The space for the working set structure that will go on the queue
     * is allocated first.
     */
    ws = (MPA_WS *)Malloc( sizeof(MPA_WS) );
    if ( ws == (MPA_WS *)NULL ) {
	return( (char *)NULL );	    /* signal above of the failure */
    }

#if defined(NEED_PAGESIZE)

    /* Get the system page size. */

#if defined(_WIN32)
    GetSystemInfo(&pgsize);
    page_size = pgsize.dwPageSize;
#else /* !defined(_WIN32) */
    page_size = getpagesize();	/* system call */
#endif /* defined(_WIN32) */
#endif /* defined(NEED_PAGESIZE) */

    alloc_size = (bytes + page_size + offset);
    /*
     * Using the requested size, from the argument list, and the page size
     * from the system allocate enough space to page align the requested 
     * buffer.  The original request will have the space of one system page
     * added to it.  The pointer will be adjusted.
     */
    ws->malloc_addr = Malloc(alloc_size);
    if ( ws->malloc_addr == NULL ) {
        LogMsg (efp, logLevelCrit, 0,
		"malloc() failed allocating %u bytes.\n", alloc_size);
	exit (ENOMEM);
	/* Reenable this after all callers check for NULL return! */
	//free( ws );		/* not going to be used */
	//return( NULL );		/* signal the failure */
    } else {
	(void)memset(ws->malloc_addr, 0, alloc_size);
    }

    error = pthread_mutex_lock(&malloc_mutex);
    if ( error ) {
	tPerror(error, "pthread_mutex_lock() failed!");
	return (NULL);
    }
    /*
     * Now align the allocated address to a page alignment and offset.
     */
    ws->palign_addr = (void *)( ((ptr_t)ws->malloc_addr + page_size) & ~(page_size-1) );
    ws->palign_addr = (void *)((ptr_t)ws->palign_addr + offset);

    /*
     * Put the working set onto the linked list so that the original malloc-ed
     * buffer can be freeed when the user program is done with it.
     */
    ws->next = mpa_qhead.next;	    /* just put it at the head */
    mpa_qhead.next = ws;

    error = pthread_mutex_unlock(&malloc_mutex);
    if ( error ) {
	tPerror(error, "pthread_mutex_unlock() failed!");
    }

    if (mDebugFlag) {
	Printf("malloc_palign: Allocated buffer at address %p of %u bytes...\n",
	       ws->palign_addr, (bytes + offset));
    }
    return( ws->palign_addr );
}

/*
 * This is a local free routine to return to the system a previously alloc-ed
 * buffer.  A local linked list keeps copies of the original and adjusted
 * addresses.  This list is used by this routine to free the correct buffer.
 *
 * Inputs:
 *	pa_addr = The page aligned buffer to free.
 *
 * Return Value:
 *	void
 */
void
free_palign(void *pa_addr)
{
    int error;
    MPA_WS *p, *q;

    if (mDebugFlag) {
	Printf("Freeing buffer at address %p...\n", pa_addr);
    }

    error = pthread_mutex_lock(&malloc_mutex);
    if ( error ) {
	tPerror(error, "pthread_mutex_lock() failed!");
	/* race noted... */
    }
    /*
     * Walk along the malloc-ed memory linked list, watch for a match on
     * the page aligned address.  If a match is found break out of the loop.
     */
    p = mpa_qhead.next;	    /* set the pointers */
    q = NULL;

    while ( p != NULL ) {
	if ( p->palign_addr == pa_addr ) /* found the buffer */
	    break;
	q = p;		    /* save current */
	p = p->next;		/* get next */
    }

    /*
     * After falling out of the loop the pointers are at the place where
     * some work has to be done, (this could also be at the beginning).
     */
    if ( p != NULL ) {

	/* Where on the list is it, check for making it empty. */

	if ( q == NULL ) {	   /* at the front */
	    mpa_qhead.next = p->next;	/* pop off front */
	} else {		/* inside the list */
	    q->next = p->next;	    /* pop it */
	}

	free( p->malloc_addr );	    /* free the malloc-ed addr */

	/* Now free up the working set, it is not needed any more. */

	free( p );
    } else { /* Should never happen, if we're coded right! */
	Fprintf("Did not find buffer at address %p...\n", pa_addr);
    }
    error = pthread_mutex_unlock(&malloc_mutex);
    if ( error ) {
	tPerror(error, "pthread_mutex_unlock() failed!");
    }
    return;
}

/*
 * dump_history_data() - Dump (saved) History Data.
 *
 * Description:
 *	This function displays previously saved history data.
 *
 * Inputs:
 *	dip = The device information pointer.
 *
 * Return Value:
 *	void
 */
void
dump_history_data(struct dinfo *dip)
{
    history_t *hp = dip->di_history;
    int entries = dip->di_history_entries;
    int i, field_width = 16;
    unsigned char *bp;

    if (entries == 0) {
	Printf("No history entries to report!\n");
	return;
    }
    hp += dip->di_history_index;

    Print("\n");
    Printf("Dumping History Data (%d entries):\n", entries);
    Print("\n");
    /*
     * Report history in reverse order (lastest request first).
     */
    while (entries--) {
	int dsize = 0;
	history_t *php = NULL;
	large_t iolba = NO_LBA;

	hp--;
	if (hp < dip->di_history) {
	    hp += dip->di_history_entries; /* set to end */
	}
	if (dip->di_history_timing && entries) {
	    php = (hp - 1); /* Previous history entry. */
	    if (php < dip->di_history) {
		php += dip->di_history_entries;
	    }
	}
	/*
	 * On error or end of file, display data upto requested size.
	 * This is to handle partial transfers prior to I/O errors.
	 */
	if (hp->hist_transfer_size <= (ssize_t) 0) {
	    dsize = MIN((size_t)dip->di_history_data_size, hp->hist_request_size);
	} else {
	    dsize = MIN(dip->di_history_data_size, hp->hist_transfer_size);
	}
	if (dip->di_random_access) {
	    iolba = (hp->hist_file_offset / dip->di_dsize);
	} else if (dip->di_lbdata_flag || dip->di_iot_pattern) {
	    iolba = make_lbdata (dip, hp->hist_file_offset);
	}
	if (dip->di_history_timing) {
	    /*
	     * Report the time stamp and time between requests.
	     */
	    Print("%10u.%06u ",  hp->hist_timer_info.tv_sec,
				hp->hist_timer_info.tv_usec);
	    if (php) {
		long secs = hp->hist_timer_info.tv_sec;
		long usecs = hp->hist_timer_info.tv_usec;
		if (usecs < php->hist_timer_info.tv_usec) {
		    secs--;
		    usecs += uSECS_PER_SEC;
		}
		Print("(%u.%06u) ", (secs - php->hist_timer_info.tv_sec),
				    (usecs - php->hist_timer_info.tv_usec));
	    }
	}
	/*
	 * For errors or end of file, report the requested size.
	 */
	if (hp->hist_transfer_size <= 0) {
	    Print("Transfer completed with %ld, reporting attempted request size\n",
		  hp->hist_transfer_size);
	    report_record(dip, hp->hist_file_number, hp->hist_record_number,
			  iolba, hp->hist_file_offset, hp->hist_test_mode,
			  NULL, (size_t)hp->hist_request_size);
	} else {
	    report_record(dip, hp->hist_file_number, hp->hist_record_number,
			  iolba, hp->hist_file_offset, hp->hist_test_mode,
			  NULL, hp->hist_transfer_size);
	}
	/*
	 * Display the request data bytes (if any).
	 */
	if (dsize > 0) {
	    Print("Offset\n");
	    for (i = 0, bp = hp->hist_request_data; (i < dsize); ) {
		if ((i % field_width) == (size_t) 0) {
		    if (i) Print("\n");
		    Print("%06d  ", i);
		}
		if (dip->di_iot_pattern) {
		    Print("%08x ", get_lbn(bp));
		    i += sizeof(u_int32);
		    bp += sizeof(u_int32);
		} else {
		    Print("%02x ", *bp);
		    i++; bp++;
		}
	    }
	    if (i) Print("\n");
	}
	if (dsize) Print("\n");
    }
    return;
}

/*
 * save_history_data() - Save History Data.
 *
 * Description:
 *	This function saves the history data for the last request.
 * The data is saved in a circular buffer who's size is determined
 * by the tester via the history=value option.  The amount of data
 * saved, can also be specified via the hdsize=value option, otherwise
 * a default is used (16 at the time of this writing).
 *
 * Inputs:
 *	dip = The device pointer.
 *	test_mode = The test mode. (READ_MODE or WRITE_MODE)
 *	offset = The file offset. (prior to transfer)
 *	buffer = The data buffer.
 *	rsize = The request size. (the request size = full count)
 *	tsize = The transfer size. (the transfer size = returned)
 *
 * Note: Beware, as tsize may be -1 on errors or 0 for end of file,
 *	 but we still wish to record that information in the history.
 *
 * Return Value:
 *	void
 */
void
save_history_data(
    struct dinfo	*dip,
    u_long		file_number,
    u_long		record_number,
    test_mode_t		test_mode,
    OFF_T		offset,
    u_char		*buffer,
    size_t		rsize,
    ssize_t		tsize)
{
    history_t *hp = dip->di_history;
    int dsize = 0;
    int i;

    hp += dip->di_history_index;
    hp->hist_test_mode = test_mode;
    hp->hist_file_number = file_number;
    hp->hist_record_number = record_number;
    hp->hist_file_offset = offset;
    hp->hist_request_size = rsize;
    hp->hist_transfer_size = tsize;
    if (dip->di_history_timing) { /* expensive syscall! */
	(void)gettimeofday(&hp->hist_timer_info, NULL);
    }
    /*DEBUG*/
    //if (dip->di_history_index%2 == 0) hp->hist_transfer_size = FAILURE;
    /*DEBUG*/
     /*
      * On error or end of file, save data upto the requested data size.
      * The reason for this is, some OS's transfer partial data prior to
      * reporting the I/O error.  This data may be on the analyzer.
      */
    if (hp->hist_transfer_size <= (ssize_t) 0) {
	dsize = MIN((size_t)dip->di_history_data_size, hp->hist_request_size);
    } else {
	dsize = MIN((ssize_t)dip->di_history_data_size, hp->hist_transfer_size);
    }
    for (i = 0; (i < dsize); i++) {
	hp->hist_request_data[i] = buffer[i];
    }
    if (dip->di_history_entries < dip->di_history_size) {
	dip->di_history_entries++; /* Count upto max entries. */
    }
    if (++dip->di_history_index == dip->di_history_size) {
	dip->di_history_index = 0;
    }
    return;
}

/*
 * Malloc() - Allocate memory with appropriate error checking.
 *
 * Description:
 *      This function allocates the requested memory, performs the
 * necessary error checking/reporting, and then zeros the allocated
 * memory space.
 *
 * Inputs:
 *	bytes = The number of bytes to allocate.
 * 
 * Return Value:
 *	Returns pointer to buffer allocated, NULL on failure.
 */
void *
Malloc(size_t bytes)
{
    void *bp;

    if (!bytes) {
        LogMsg (efp, logLevelDiag, 0,
		"Malloc: FIXME -> Trying to allocate %u bytes.\n", bytes);
	return(NULL);
    }
    if ( (bp = malloc(bytes)) == NULL) {
        LogMsg (efp, logLevelCrit, 0,
		"malloc() failed allocating %u bytes.\n", bytes);
	exit (ENOMEM);
    }
    memset(bp, '\0', bytes);
    return(bp);
}

void *
Realloc(void *bp, size_t bytes)
{
    if ( (bp = realloc(bp, bytes)) == NULL) {
        LogMsg (efp, logLevelCrit, 0,
		"realloc() failed allocating %u bytes.\n", bytes);
	exit (ENOMEM);
    }
    memset(bp, '\0', bytes);
    return(bp);
}

/* ========================================================================= */
/* Added from spt utilities! */

int DisplayWidth = DEFAULT_WIDTH;
/*
 * Enabled/Disabled Table.
 */
char *endis_table[] = {
	"Disabled",
	"Enabled"
};

/*
 * On/Off Table.
 */
char *onoff_table[] = {
	"Off",
	"On"
};

/*
 * True/False Table:
 */
char *boolean_table[] = {
	"False",
	"True"
};

/*
 * Yes/No Table.
 */
char *yesno_table[] = {
	"No",
	"Yes"
};

/*
 * PrintHeader() - Function to Displays Header Message.
 *
 * Inputs:
 *	header = The header strings to display.
 *
 * Return Value:
 *	void
 */
void
PrintHeader(char *header)
{
	Printf ("\n%s:\n\n", header);
}

/*
 * PrintAscii() - Function to Print an ASCII Field.
 * PrintNumeric() - Function to Print a Numeric Field.
 * PrintDecimal() - Function to Print a Numeric Field in Decimal.
 * PrintHex() - Function to Print a Numeric Field in Hexadecimal.	*
 *
 * Inputs:
 *	field_str = The field name string.
 *	ascii_str = The ASCII string to print.
 *	nl_flag = Flag to control printing newline.
 *
 * Return Value:
 *	void
 */
void
PrintNumeric(char *field_str, uint32_t numeric_value, int nl_flag)
{
	char *printf_str = NUMERIC_FIELD;

	Printf (printf_str, field_str, numeric_value);
	if (nl_flag) Printf ("\n");
}

void
PrintDecimal(char *field_str, uint32_t numeric_value, int nl_flag)
{
	char *printf_str = NUMERIC_FIELD;

	Printf (printf_str, field_str, numeric_value);
	if (nl_flag) Printf ("\n");
}

void
PrintDecHex(char *field_str, uint32_t numeric_value, int nl_flag)
{
	char *printf_str = DEC_HEX_FIELD;

	Printf (printf_str, field_str, numeric_value, numeric_value);
	if (nl_flag) Printf ("\n");
}

void
PrintHex(char *field_str, uint32_t numeric_value, int nl_flag)
{
	char *printf_str = HEX_FIELD;

	Printf (printf_str, field_str, numeric_value);
	if (nl_flag) Printf ("\n");
}

void
PrintHexDec(char *field_str, uint32_t numeric_value, int nl_flag)
{
	char *printf_str = HEX_DEC_FIELD;

	Printf (printf_str, field_str, numeric_value, numeric_value);
	if (nl_flag) Printf ("\n");
}

void
PrintAscii(char *field_str, char *ascii_str, int nl_flag)
{
	int length = strlen(field_str);
	char *printf_str = ((length) ? ASCII_FIELD : EMPTY_FIELD);

	Printf (printf_str, field_str, ascii_str);
	if (nl_flag) Printf ("\n");
}

/*
 * Functions to display quad (64-bit) values.
 */
void
PrintLongLong(char *field_str, uint64_t numeric_value, int nl_flag)
{
	char *printf_str = LNUMERIC_FIELD;

	Printf (printf_str, field_str, numeric_value);
	if (nl_flag) Printf ("\n");
}

void
PrintLongDec(char *field_str, uint64_t numeric_value, int nl_flag)
{
	char *printf_str = LNUMERIC_FIELD;

	Printf (printf_str, field_str, numeric_value);
	if (nl_flag) Printf ("\n");
}

void
PrintLongDecHex(char *field_str, uint64_t numeric_value, int nl_flag)
{
	char *printf_str = LDEC_HEX_FIELD;

	Printf (printf_str, field_str, numeric_value, numeric_value);
	if (nl_flag) Printf ("\n");
}

void
PrintLongHex(char *field_str, uint64_t numeric_value, int nl_flag)
{
	char *printf_str = LHEX_FIELD;

	Printf (printf_str, field_str, numeric_value);
	if (nl_flag) Printf ("\n");
}

void
PrintLongHexDec(char *field_str, uint64_t numeric_value, int nl_flag)
{
	char *printf_str = LHEX_DEC_FIELD;

	Printf (printf_str, field_str, numeric_value, numeric_value);
	if (nl_flag) Printf ("\n");
}

/*
 * Printxxx() - Functions to Print Fields with Context.
 *
 * Inputs:
 *	numeric = Print field as numeric.
 *	field_str = The field name string.
 *	ascii_str = The ASCII string to print.
 *	nl_flag = Flag to control printing newline.
 *
 * Return Value:
 *	void
 */
void
PrintBoolean(
	hbool_t	numeric,
	char	*field_str,
	hbool_t	boolean_flag,
	hbool_t	nl_flag)
{
	if (numeric) {
	    PrintNumeric (field_str, boolean_flag, nl_flag);
	} else {
	    PrintAscii (field_str, boolean_table[(int)boolean_flag], nl_flag);
	}
}

void
PrintEnDis(
	hbool_t	numeric,
	char	*field_str,
	hbool_t	boolean_flag,
	hbool_t	nl_flag)
{
	if (numeric) {
	    PrintNumeric (field_str, boolean_flag, nl_flag);
	} else {
	    PrintAscii (field_str, endis_table[(int)boolean_flag], nl_flag);
	}
}

void
PrintOnOff(
	hbool_t	numeric,
	char	*field_str,
	hbool_t	boolean_flag,
	hbool_t	nl_flag)
{
	if (numeric) {
	    PrintNumeric (field_str, boolean_flag, nl_flag);
	} else {
	    PrintAscii (field_str, onoff_table[(int)boolean_flag], nl_flag);
	}
}

void
PrintYesNo(
	hbool_t	numeric,
	char	*field_str,
	hbool_t	boolean_flag,
	hbool_t	nl_flag)
{
	if (numeric) {
	    PrintNumeric (field_str, boolean_flag, nl_flag);
	} else {
	    PrintAscii (field_str, yesno_table[(int)boolean_flag], nl_flag);
	}
}

void
PrintFields(uint8_t *bptr, int length)
{
    int field_entrys = ((DisplayWidth - FIELD_WIDTH) / 3) - 1;
    int count = 0;

    while (count < length) {
	if (CmdInterruptedFlag == TRUE)	break;
	if ((++count % field_entrys) == 0) {
	    Printf("%02x\n", *bptr++);
	    if (count < length)	PrintAscii("", "", DNL);
	} else {
	    Printf ("%02x ", *bptr++);
	}               
    }                       
    if (count % field_entrys) Printf("\n");
}                                     

void
PrintHAFields(uint8_t *bptr, int length)
{
    int field_entrys;
    int count = 0;
    u_char data;
    u_char *abufp, *abp;

    field_entrys = ((DisplayWidth - FIELD_WIDTH) / 3) - 1;
    field_entrys -= (field_entrys / 3);	/* For ASCII */
    abufp = abp = (u_char *) Malloc (field_entrys + 1);
    if (abufp == NULL) return;
    while (count < length) {
	if (CmdInterruptedFlag == TRUE)	break;
	data = *bptr++;
	Printf ("%02x ", data);
	abp += Sprintf ((char *)abp, "%c", isprint((int)data) ? data : ' ');
	*abp = '\0';
	if ((++count % field_entrys) == 0) {
	    Printf ("\"%s\"\n", abufp); abp = abufp;
	    if (count < length)	PrintAscii("", "", DNL);
	}
    }
    if (abp != abufp) {
	while (count++ % field_entrys) Printf ("   ");
	Printf ("\"%s\"\n", abufp);
    }
    free (abufp);
    return;
}

void
DumpFieldsOffset(uint8_t *bptr, int length)
{
    int field_entrys = 16;
    int count = 0;
    uint8_t data;
    uint8_t *abufp, *abp;
    hbool_t first = True;

    abufp = abp = (uint8_t *)malloc(field_entrys + 1);
    if ( (abufp == NULL) || (length == 0) ) return;
    /*
     * Print offset followed by 'n' hex bytes and ASCII text.
     */
    Printf("Offset  Data\n");
    while (count < length) {
        if (first) {
            Printf("%06d  ", count);
            first = False;
        }
        data = *bptr++;
        Printf ("%02x ", data);
        abp += sprintf((char *)abp, "%c", isprint((int)data) ? data : ' ');
        *abp = '\0';
        if ((++count % field_entrys) == 0) {
            Printf ("\"%s\"\n", abufp);
            first = True;
            abp = abufp;
        }
    }
    if (abp != abufp) {
        while (count++ % field_entrys) Printf ("   ");
        Printf ("\"%s\"\n", abufp);
    }
    free (abufp);
    return;
}

