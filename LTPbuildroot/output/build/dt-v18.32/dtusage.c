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
 * Module:	dtusage.c
 * Author:	Robin T. Miller
 *
 * Description:
 *	Display usage information for generic data test program.
 *
 * Modification History:
 *
 * July 2nd, 2008 by Robin T. Miller
 *	Change display of dump_limit to 32-bits to see correct default.
 *
 * December 23rd, 2004 by Robin Miller.
 *      Add help text for statistics control level.
 *
 * December 21st, 2004 by Robin Miller.
 *      Add help text for keepalive format control characters.
 *
 * December 5th, 2003 by Robin Miller.
 *      Conditionalize help text for tty options.
 *
 * March 15th, 2003 by Robin Miller.
 *	Add displaying of prefix string if specified.
 *
 * January 24th, 2001 by Robin Miller.
 *	Add help text for variable I/O requests sizes.
 *
 * December 30th, 2000 by Robin Miller.
 *	Make changes to build using MKS/NuTCracker product.
 *
 * May 8th, 2000 by Robin Miller.
 *	Add dtversion() to display just the version string.
 *
 * August 6th, 1999 by Robin Miller.
 *	Better parameterizing of "long long" printf formatting.
 *
 * July 29th, 1999 by Robin Miller.
 *	Merge in changes made to compile on FreeBSD.
 *
 * July 24th, 1999 by Robin Miller.
 *	Bumped major version number to 12.x due to pattern=iot support.
 *
 * December 21, 1998 by Robin Miller.
 *	Bump of major version number to 11.x due to tape reset support.
 *
 * March 27, 1997 by Ali Eghlima.
 *	Document "munsa={cr,cw,pr,pw,ex}" option.  MUti-Node Simultaneous
 *	Access (MUNSA) is used in a cluster system when accessing shared
 *	resources.  The Distributed Lock Manager (DLM) is used to control
 *	access to a resource and to synchronize all access.
 *
 * February 21, 1996 by Robin Miller.
 *	Document iotype={random,sequential} options.
 *
 * December 19, 1995 by Robin Miller
 *      Conditionalize for Linux Operating System.
 *
 * November 19, 1995 by Robin Miller.
 *	Describe logical block data options (lba=, lbs=, enable=lbdata).
 *
 * July 26, 1995 by Robin Miller.
 *	Added AIO bug fixes/enhancements, special pattern string mapping,
 *	corrected data dumping/add dump limit, reporting of lba on disk
 *	devices, child signal bug fix/error control, additional stats...
 *	So, it's finally time for a new version string -> V8.0 (enjoy).
 *
 * September 23, 1994 by Robin Miller.
 *      Change O_DSYNCH to O_DSYNC, and O_FSYNCH to O_SYNC.
 *
 * December 7, 1993 by Robin Miller.
 *	Ported to SunOS 5.1 (Solaris).
 *
 * September 1, 1993 by Robin Miller.
 *	Added description of "min=", "max=", & "incr=" parameters.
 *	Finally added version and date identifiers for tracking.
 *	V1.0=Sun/3 (disk & tape), V2.0=Sun/386i (tty support),
 *	V3.0=Sun/Sparc (mmap files), V4.0=Ultrix, V5.0=DEC OSF/1,
 *	V6.0=QNX (POSIX support),
 *	V7.0=(procs, files, step, runtime, AIO, variable records).
 *
 * August 31, 1993 by Robin Miller.
 *	Added description of "align=rotate" & "pattern=incr" options.
 *
 * August 30, 1993 by Robin Miller.
 *	Added description of AIO options: enable=aio & aios=value
 *
 * August 17, 1993 by Robin Miller.
 *	Added text to describe "runtime=" option & format.
 *
 * August 5, 1993 by Robin Miller.
 *	Add text to describe "files=value" option (for tapes).
 *
 * August 3, 1993 by Robin Miller.
 *	Add text to describe "procs=value" option.
 *
 * September 19, 1992 by Robin Miller.
 *	Add text to describe "enable/disable=flush" tty option.
 *
 * September 17, 1992 by Robin Miller.
 *	Add text to describe "pattern=string" option, and to describe
 *	how to override the default decimal radix numeric input.
 *
 * September 11, 1992 by Robin Miller.
 *	Display help text to stdout instead of stderr so output can be
 *	easily piped to a pager.
 */
#include "dt.h"
#include <fcntl.h>

/*
 * dtusage()/dthelp() - Display valid options for dt program.
 */
#define P	printf
#define D	Fprint

char *version_str = "Date: September 19th, 2013, Version: 18.32, Author: Robin T. Miller";

void
dtusage(void)
{
    D ("Usage: %s options...\n", cmdname);
    D (" Type '%s help' for a list of valid options.\n", cmdname);
    exit (FATAL_ERROR);
}

void
dtversion(void)
{
    P ("    --> %s <--\n", version_str);
    exit (SUCCESS);
}

void
dthelp(dinfo_t *dip)
{
    static char *enabled_str = "enabled";
    static char *disabled_str = "disabled";

    P ("Usage: %s options...\n", cmdname);
    P ("\n    Where options are:\n");
    P ("\tif=filename      The input file to read.\n");
    P ("\tof=filename      The output file to write.\n");
#if defined(SCSI)
    P ("\tsdsf=filename    The SCSI device special file.\n");
#endif /* defined(SCSI) */
    P ("\tpf=filename      The data pattern file to use.\n");
    P ("\tdir=dirpath      The directory path for files.\n");
    P ("\tdirp=string      The directory prefix for subdirs.\n");
#if not_implemented_yet
    P ("\tdirs=value       The number of directories.\n");
#endif
    P ("\tsdirs=value      The number of subdirectories.\n");
    P ("\tdepth=value      The subdirectory depth.\n");
    P ("\tbs=value         The block size to read/write.\n");
    P ("    or");
    P ("\tbs=random        Random size between 512 and 256k.\n");
    P ("\tlog[tu]=filename The log file name to write.\n");
    P ("\t                 t=truncate, u=unique (w/pid)\n");
#if defined(AIO)
    P ("\taios=value       Set number of AIO's to queue.\n");
#endif /* defined(AIO) */
#if !defined(_QNX_SOURCE)
    P ("\talarm=time       The keepalive alarm time.\n");
    P ("\tkeepalive=string The keepalive message string.\n");
    P ("\tkeepalivet=time  The keepalive message frequency.\n");
    P ("\tpkeepalive=str   The pass keepalive message string.\n");
    P ("\ttkeepalive=str   The totals keepalive message string.\n");
    P ("\talign=offset     Set offset within page aligned buffer.\n");
    P ("    or\talign=rotate     Rotate data address through sizeof(ptr).\n");
#endif /* !defined(_QNX_SOURCE) */
    P ("\tcapacity=value   Set the device capacity in bytes.\n");
    P ("    or\tcapacity=max     Set maximum capacity from disk driver.\n");
    P ("\tbufmodes={buffered,unbuffered,cachereads,cachewrites}\n");
    P ("\t                 Set one or more buffering modes (Default: none)\n");
    P ("\tboff=string      Set the buffer offsets to: dec or hex (Default: %s)\n",
					    (dip->di_boff_format == DEC_FMT) ? "dec" : "hex");
    P ("\tdfmt=string      Set the data format to: byte or word (Default: %s)\n",
    					    (dip->di_data_format == BYTE_FMT) ? "byte" : "word");
    P ("\tdispose=mode     Set file dispose to: {delete, keep, or keeponerror}.\n");
    P ("\tdlimit=value     Set the dump data buffer limit.\n");
    P ("\tdtype=string     Set the device type being tested.\n");
    P ("\tidtype=string    Set input device type being tested.\n");
    P ("\todtype=string    Set output device type being tested.\n");
    P ("\tdsize=value      Set the device block (sector) size.\n");
    P ("\terrors=value     The number of errors to tolerate.\n");
    P ("\tfiles=value      Set number of disk/tape files to process.\n");
    P ("\tffreq=value      The frequency (in records) to flush buffers.\n");
    P ("\tmaxfiles=value   The maximum files for all directories.\n");
    P ("\tflow=type        Set flow to: none, cts_rts, or xon_xoff.\n");
/*  P ("\thz=value         Set number of clock ticks per second.\n");	*/
    P ("\tincr=value       Set number of record bytes to increment.\n");
    P ("    or\tincr=variable    Enables variable I/O request sizes.\n");
    P ("\tiodir=direction  Set I/O direction to: {forward or reverse}.\n");
    P ("\tiomode=mode      Set I/O mode to: {copy, test, or verify}.\n");
    P ("\tiotype=type      Set I/O type to: {random or sequential}.\n");
    P ("\tiotpass=value    Set the IOT pattern for specified pass.\n");
    P ("\tiotseed=value    Set the IOT pattern block seed value.\n");
    P ("\tiotune=filename  Set I/O tune delay parameters via file.\n");
    P ("\thistory=value    Set the number of history request entries.\n");
    P ("\thdsize=value     Set the history data size (bytes to save).\n");
    P ("\tmin=value        Set the minumum record size to transfer.\n");
    P ("\tmax=value        Set the maximum record size to transfer.\n");
    P ("\tlba=value        Set starting block used w/lbdata option.\n");
    P ("\tlbs=value        Set logical block size for lbdata option.\n");
    P ("\tlimit=value      The number of bytes to transfer.\n");
    P ("\tmaxdata=value    The maximum data limit (all files).\n");
    P ("\tflags=flags      Set open flags:   {excl,sync,...}\n");
    P ("\toflags=flags     Set output flags: {append,trunc,...}\n");
    P ("\tmaxbad=value     Set maximum bad blocks to display.\n");
    P ("\toncerr=action    Set child error action: {abort or continue}.\n");
#if !defined(WIN32)
    P ("\tnice=value       Apply the nice value to alter our priority.\n");
#endif
    P ("\tnoprogt=value    Set the no progress time (in seconds).\n");
    P ("\tnoprogtt=value   Set the no progress trigger time (secs).\n");
    P ("\tnotime=optype    Disable timing of specified operation type.\n");
#if defined(_QNX_SOURCE)
    P ("\tparity=string    Set parity to: {even, odd, mark, space, or none}.\n");
#else /* !defined(_QNX_SOURCE) */
    P ("\tparity=string    Set parity to: {even, odd, or none}.\n");
#endif /* defined(_QNX_SOURCE) */
    P ("\tpasses=value     The number of passes to perform.\n");
    P ("\tpattern=value    The 32 bit hex data pattern to use.\n");
    P ("    or\tpattern=iot      Use DJ's IOT test pattern.\n");
    P ("    or\tpattern=incr     Use an incrementing data pattern.\n");
    P ("    or\tpattern=string   The string to use for the data pattern.\n");
    P ("\tposition=offset  Position to offset before testing.\n");
    P ("\toposition=offset The output file position (copy/verify).\n");
    P ("\tprefix=string    The data pattern prefix string.\n");
    P ("\tprocs=value      The number of processes to create.\n");
#if defined(HP_UX)
    P ("\tqdepth=value     Set the queue depth to specified value.\n");
#endif /* defined(HP_UX) */
    P ("\tralign=value     The random I/O offset alignment.\n");
    P ("\trlimit=value     The random I/O data byte limit.\n");
    P ("\trseed=value      The random number generator seed.\n");
    P ("\trecords=value    The number of records to process.\n");
    P ("\truntime=time     The number of seconds to execute.\n");
    P ("\tslice=value      The specific disk slice to test.\n");
    P ("\tslices=value     The number of disk slices to test.\n");
    P ("\tskip=value       The number of records to skip past.\n");
    P ("\tseek=value       The number of records to seek past.\n");
    P ("\tstep=value       The number of bytes seeked after I/O.\n");
    P ("\tstats=level      The stats level: {brief, full, or none}\n");
    P ("\tstopon=filename  Watch for file existance, then stop.\n");
    P ("\ttrigger=type     The trigger to execute during errors.\n");
    P ("\tvolumes=value    The number of volumes to process.\n");
    P ("\tvrecords=value   The record limit for the last volume.\n");
    P ("\tenable=flag      Enable one or more of the flags below.\n");
    P ("\tdisable=flag     Disable one or more of the flags below.\n");

    P ("\n    Retry Related Options:\n");
    P ("\tretry_error=value     The error code to retry.\n");
    P ("\tretry_delay=value     The retry delay.              (Def: %u)\n",
						dip->di_retry_delay);
    P ("\tretry_limit=value     The retry limit.              (Def: %u)\n",
						dip->di_retry_limit);
    P ("\n    Error Strings Accepted:\n");
#if defined(WIN32)
    P ("\tERROR_UNEXP_NET_ERR (%d), ", ERROR_UNEXP_NET_ERR);
    P ("ERROR_NETNAME_DELETED (%d)\n", ERROR_NETNAME_DELETED);
    P ("\tERROR_BUSY (%d), ", ERROR_BUSY);
    P ("ERROR_SEM_TIMEOUT (%d)\n", ERROR_SEM_TIMEOUT);
    P ("\tERROR_VC_DISCONNECTED (%d), ", ERROR_VC_DISCONNECTED);
    P ("ERROR_IO_DEVICE (%d)\n", ERROR_IO_DEVICE);
#else /* !defined(WIN32) */
    P ("\tEIO (%d), ", EIO);
    P ("ENXIO (%d), ", ENXIO);
    P ("EBUSY (%d), ", EBUSY);
    P ("ENODEV (%d), ", ENODEV);
    P ("ESTALE (%d)\n", ESTALE);
#endif /* defined(WIN32) */
    P ("\t    OR\n");
    P ("\tretry_error='*' or -1 to retry all errors.\n");

#if defined(SCSI)
    P ("\n    SCSI Specific Options:\n");
    P ("\tscsi_timeout=value    The SCSI timeout (in ms).     (Def: %ums)\n",
       dip->di_scsi_timeout);
    P ("\tunmap_freq=value      The SCSI unmap frequency.     (Def: %u)\n",
       dip->di_unmap_frequency);
#endif /* defined(SCSI) */

    P ("\n    Flags to enable/disable:\n");
#if defined(AIO)
    P ("\taio              POSIX Asynchronous I/O.    (Default: %s)\n",
				(dip->di_aio_flag) ? enabled_str : disabled_str);
#endif /* defined(AIO) */
    P ("\tcerrors          Report close errors.       (Default: %s)\n",
				(dip->di_cerrors_flag) ? enabled_str : disabled_str);
    P ("\tcompare          Data comparison.           (Default: %s)\n",
				(dip->di_compare_flag) ? enabled_str : disabled_str);
    P ("\tcoredump         Core dump on errors.       (Default: %s)\n",
				(core_dump) ? enabled_str : disabled_str);
    P ("\tdeleteperpass    Delete files per pass.     (Default: %s)\n",
			 	(dip->di_delete_per_pass) ? enabled_str : disabled_str);
    P ("\tdebug            Debug output.              (Default: %s)\n",
				(dip->di_debug_flag) ? enabled_str : disabled_str);
    P ("\tDebug            Verbose debug output.      (Default: %s)\n",
				(dip->di_Debug_flag) ? enabled_str : disabled_str);
    P ("\tedebug           End of file debug.         (Default: %s)\n",
				(dip->di_eDebugFlag) ? enabled_str : disabled_str);
    P ("\tfdebug           File operations debug.     (Default: %s)\n",
				(dip->di_fDebugFlag) ? enabled_str : disabled_str);
    P ("\tmdebug           Memory related debug.      (Default: %s)\n",
				(dip->di_mDebugFlag) ? enabled_str : disabled_str);
    P ("\tmntdebug         Mount device lookup debug. (Default: %s)\n",
				(dip->di_mDebugFlag) ? enabled_str : disabled_str);
    P ("\tpdebug           Process related debug.     (Default: %s)\n",
				(dip->di_pDebugFlag) ? enabled_str : disabled_str);
    P ("\trdebug           Random debug output.       (Default: %s)\n",
				(dip->di_rDebugFlag) ? enabled_str : disabled_str);
    P ("\ttdebug           Timer debug output.        (Default: %s)\n",
				(dip->di_tDebugFlag) ? enabled_str : disabled_str);
    P ("\tdump             Dump data buffer.          (Default: %s)\n",
				(dip->di_dump_flag) ? enabled_str : disabled_str);
    P ("\tdumpall          Dump all blocks.           (Default: %s)\n",
				(dip->di_dumpall_flag) ? enabled_str : disabled_str);
    P ("\teof              EOF/EOM exit status.       (Default: %s)\n",
				(eof_status_flag) ? enabled_str : disabled_str);
    P ("\tfsalign          File system align.         (Default: %s)\n",
				(dip->di_fsalign_flag) ? enabled_str : disabled_str);
    P ("\tfunique          Unique output file.        (Default: %s)\n",
        			(dip->di_unique_file) ? enabled_str : disabled_str);
    P ("\tfsincr           File size incrementing.    (Default: %s)\n",
				(dip->di_fsincr_flag) ? enabled_str : disabled_str);
    P ("\tfsync            Controls file sync'ing.    (Default: %s)\n",
				(dip->di_fsync_flag == UNINITIALIZED) ? "runtime"
				: (dip->di_fsync_flag) ? enabled_str : disabled_str);
    P ("\theader           Log file header.           (Default: %s)\n",
				(dip->di_header_flag) ? enabled_str : disabled_str);
    P ("\thdump            History dump.              (Default: %s)\n",
				(dip->di_history_timing) ? enabled_str : disabled_str);
    P ("\thtiming          History timing.            (Default: %s)\n",
				(dip->di_history_timing) ? enabled_str : disabled_str);
    P ("\tlbdata           Logical block data.        (Default: %s)\n",
				(dip->di_lbdata_flag) ? enabled_str : disabled_str);
    P ("\tlogpid           Log process ID.            (Default: %s)\n",
        			(dip->di_logpid_flag) ? enabled_str : disabled_str);
    P ("\tlooponerror      Loop on error.             (Default: %s)\n",
        			(dip->di_loop_on_error) ? enabled_str : disabled_str);
    P ("\tmicrodelay       Microsecond delays.        (Default: %s)\n",
				(dip->di_micro_flag) ? enabled_str : disabled_str);
#if defined(MMAP)
    P ("\tmmap             Memory mapped I/O.         (Default: %s)\n",
				(dip->di_mmap_flag) ? enabled_str : disabled_str);
#endif /* defined(MMAP) */
    P ("\tmountlookup      Mount device lookup.       (Default: %s)\n",
				(dip->di_mount_lookup) ? enabled_str : disabled_str);
    P ("\tmulti            Multiple volumes.          (Default: %s)\n",
				(dip->di_multi_flag) ? enabled_str : disabled_str);
    P ("\tnoprog           No progress check.         (Default: %s)\n",
				(dip->di_noprog_flag) ? enabled_str : disabled_str);
    P ("\tprefill          Prefill read buffer.       (Default: %s)\n",
				(dip->di_prefill_flag) ? enabled_str : disabled_str);
    P ("\tpstats           Per pass statistics.       (Default: %s)\n",
				(dip->di_pstats_flag) ? enabled_str : disabled_str);
    P ("\traw              Read after write.          (Default: %s)\n",
				(dip->di_raw_flag) ? enabled_str : disabled_str);
    P ("\treread           Re-read after raw.         (Default: %s)\n",
				(dip->di_reread_flag) ? enabled_str : disabled_str);
    P ("\treadcache        Read cache control.        (Default: %s)\n",
				(dip->di_read_cache_flag) ? enabled_str : disabled_str);
    P ("\twritecache       Write cache control.       (Default: %s)\n",
				(dip->di_write_cache_flag) ? enabled_str : disabled_str);
    P ("\tretryDC          Retry data corruptions.    (Default: %s)\n",
				(dip->di_retryDC_flag) ? enabled_str : disabled_str);
    P ("\tsighup           Hangup signal control.     (Default: %s)\n",
				(sighup_flag) ? enabled_str : disabled_str);   
#if defined(WIN32)
    P ("\tsparse           Sparse file attribute.     (Default: %s)\n",
				(dip->di_sparse_flag) ? enabled_str : disabled_str);   
    P ("\tprealloc         Preallocate w/o sparse.    (Default: %s)\n",
				(dip->di_prealloc_flag) ? enabled_str : disabled_str);   
#endif /* defined(WIN32) */
#if defined(SCSI)
    P ("\tscsi             SCSI operations.           (Default: %s)\n",
				(dip->di_scsi_flag) ? enabled_str : disabled_str);
    P ("\tsdebug           SCSI debug output.         (Default: %s)\n",
				(dip->di_sDebugFlag) ? enabled_str : disabled_str);
    P ("\tserrors          SCSI error logging.        (Default: %s)\n",
				(dip->di_scsi_errors) ? enabled_str : disabled_str);
    P ("\tunmap            SCSI unmap per pass.       (Default: %s)\n",
				(dip->di_unmap_flag) ? enabled_str : disabled_str);
#endif /* defined(SCSI) */
    P ("\tstats            Display statistics.        (Default: %s)\n",
				(dip->di_stats_flag) ? enabled_str : disabled_str);
#if defined(SYSLOG)
    P ("\tsyslog           Log errors to syslog.      (Default: %s)\n",
				(dip->di_syslog_flag) ? enabled_str : disabled_str);
#endif /* defined(SYSLOG) */
#if defined(TIMESTAMP)
    P ("\ttimestamp        Timestamp each block.      (Default: %s)\n",
				(dip->di_timestamp_flag) ? enabled_str : disabled_str);
#endif /* defined(TIMESTAMP) */
    P ("\ttrigargs         Trigger cmd arguments.     (Default: %s)\n",
				(dip->di_trigargs_flag) ? enabled_str : disabled_str);
    P ("\tunique           Unique pattern.            (Default: %s)\n",
				(dip->di_unique_pattern) ? enabled_str : disabled_str);
    P ("\tverbose          Verbose output.            (Default: %s)\n",
				(dip->di_verbose_flag) ? enabled_str : disabled_str);
    P ("\tverify           Verify data written.       (Default: %s)\n",
				(dip->di_verify_flag) ? enabled_str : disabled_str);
    P ("\n");
    P ("      Example: enable=debug disable=compare,pstats\n");
    P ("\n    Common Open Flags:\n");
    P ("\tnone                  Clear all user set flags.\n");
#if defined(O_EXCL)
    P ("\texcl (O_EXCL)         Exclusive open. (don't share)\n");
#endif /* defined(O_EXCL) */
#if defined(O_NDELAY)
    P ("\tndelay (O_NDELAY)     Non-delay open. (don't block)\n");
#endif /* defined(O_NDELAY) */
#if defined(O_NONBLOCK)
    P ("\tnonblock (O_NONBLOCK) Non-blocking open/read/write.\n");
#endif /* defined(O_NONBLOCK) */
#if defined(O_CACHE)
    P ("\tcache (O_CACHE)       Attempt to keep data in file system cache.\n");
#endif /* defined(O_CACHE) */
#if defined(O_DIRECT)
    P ("\tdirect (O_DIRECT)     Direct disk access. (don't cache data).\n");
#endif /* defined(O_DIRECT) */
#if defined(SOLARIS)
    P ("\tdirect (directio())   Direct disk access. (don't cache data).\n");
#endif /* defined(SOLARIS) */
#if defined(WIN32)
    P ("\tdirect (NO_BUFFERING) Direct disk access. (don't cache data).\n");
#endif /* !defined(WIN32) */
#if defined(O_FSYNC)
    P ("\tfsync (O_FSYNC)       Sync both read/write data with disk file.\n");
#endif /* defined(O_FSYNC) */
#if defined(O_RSYNC)
    P ("\trsync (O_RSYNC)       Synchronize read operations.\n");
#endif /* defined(O_RSYNC) */
#if defined(O_SYNC)
    P ("\tsync (O_SYNC)         Sync updates for data/file attributes.\n");
#endif /* defined(O_SYNC) */
#if defined(O_LARGEFILE)
    P ("\tlarge (O_LARGEFILE)   Enable large (64-bit) file system support.\n");
#endif /* defined(O_LARGEFILE) */
    P ("\n    Output Open Flags:\n");
    P ("\tnone                  Clear all user set flags.\n");
#if defined(O_APPEND)
    P ("\tappend (O_APPEND)     Append data to end of existing file.\n");
#endif /* defined(O_APPEND) */
#if defined(O_DEFER)
    P ("\tdefer (O_DEFER)       Defer updates to file during writes.\n");
#endif /* defined(O_DEFER) */
#if defined(O_DSYNC)
    P ("\tdsync (O_DSYNC)       Sync data to disk during write operations.\n");
#endif /* defined(O_DSYNC) */
#if defined(O_TRUNC)
    P ("\ttrunc (O_TRUNC)       Truncate an existing file before writing.\n");
#endif /* defined(O_TRUNC) */
#if defined(O_TEMP)
    P ("\ttemp (O_TEMP)         Temporary file, try to keep data in cache.\n");
#endif /* defined(O_TEMP) */
    P ("\n    Delays (Values are seconds, unless microdelay enabled):\n");
    P ("\todelay=value     Delay before opening the file.    (Default: %u)\n",
							DEFAULT_OPEN_DELAY);
    P ("\tcdelay=value     Delay before closing the file.    (Default: %u)\n",
							DEFAULT_CLOSE_DELAY);
    P ("\tedelay=value     Delay between multiple passes.    (Default: %u)\n",
							DEFAULT_END_DELAY);
    P ("\trdelay=value     Delay before reading each record. (Default: %u)\n",
							DEFAULT_READ_DELAY);
    P ("\tsdelay=value     Delay before starting the test.   (Default: %u)\n",
							DEFAULT_START_DELAY);
    P ("\ttdelay=value     Delay before child terminates.    (Default: %u)\n",
							dip->di_term_delay);
    P ("\twdelay=value     Delay before writing each record. (Default: %u)\n",
							DEFAULT_WRITE_DELAY);
    P ("\n");
    P ("\tcdelay, edelay, rdelay, sdelay, and wdelay accept 'random'.\n");
    P ("\n    Numeric Input:\n");
    P ("\tFor options accepting numeric input, the string may contain any\n");
    P ("\tcombination of the following characters:\n");
    P ("\n\tSpecial Characters:\n");
    P ("\t    w = words (%u bytes)", (unsigned int)sizeof(int));
    P ("            q = quadwords (%u bytes)\n", (unsigned int)sizeof(large_t));
    P ("\t    b = blocks (512 bytes)         k = kilobytes (1024 bytes)\n");
    P ("\t    m = megabytes (1048576 bytes)  p = page size (%d bytes)\n", page_size);
    P ("\t    g = gigabytes (%ld bytes)\n", GBYTE_SIZE);
    P ("\t    t = terabytes (" LDF " bytes)\n", TBYTE_SIZE);
    P ("\t    d = device size (set via dsize=value option)\n");
    P ("\t    inf or INF = infinity (" LUF " bytes)\n", INFINITY);
    P ("\n\tArithmetic Characters:\n");
    P ("\t    + = addition                   - = subtraction\n");
    P ("\t    * or x = multiplcation         / = division\n");
    P ("\t    %% = remainder\n");
    P ("\n\tBitwise Characters:\n");
    P ("\t    ~ = complement of value       >> = shift bits right\n");
    P ("\t   << = shift bits left            & = bitwise 'and' operation\n");
    P ("\t    | = bitwise 'or' operation     ^ = bitwise exclusive 'or'\n\n");
    P ("\tThe default base for numeric input is decimal, but you can override\n");
    P ("\tthis default by specifying 0x or 0X for hexadecimal conversions, or\n");
    P ("\ta leading zero '0' for octal conversions.  NOTE: Evaluation is from\n");
    P ("\tright to left without precedence, and parenthesis are not permitted.\n");

    P ("\n    Keepalive Format Control:\n");
    P ("\t    %%b = The bytes read or written.   %%B = Total bytes read and written.\n");
    P ("\t    %%c = Record count for this pass.  %%C = Total records for this test.\n");
    P ("\t    %%d = The device name.             %%D = The real device name.\n");
    P ("\t    %%e = The number of errors.        %%E = The error limit.\n");
    P ("\t    %%f = The files read or written.   %%F = Total files read and written.\n");
    P ("\t    %%h = The host name.               %%H = The full host name.\n");
    P ("\t    %%k = The kilobytes this pass.     %%K = Total kilobytes for this test.\n");
    P ("\t    %%l = Blocks read or written.      %%L = Total blocks read and written.\n");
    P ("\t    %%m = The megabytes this pass.     %%M = Total megabytes for this test.\n");
    P ("\t    %%p = The pass count.              %%P = The pass limit.\n");
    P ("\t    %%r = Records read this pass.      %%R = Total records read this test.\n");
    P ("\t    %%s = The seconds this pass.       %%S = The total seconds this test.\n");
    P ("\t    %%t = The pass elapsed time.       %%T = The total elapsed time.\n");
    P ("\t    %%i = The I/O mode (read/write)    %%u = The user (login) name.\n");
    P ("\t    %%w = Records written this pass.   %%W = Total records written this test.\n");
    P ("\n    Performance Keywords:\n");
    P ("\t    %%bps  = The bytes per second.     %%lbps = Logical blocks per second.\n");
    P ("\t    %%kbps = Kilobytes per second.     %%mbps = The megabytes per second.\n");
    P ("\t    %%iops = The I/O's per second.     %%spio = The seconds per I/O.\n");
    P ("\n    File Position Keywords:\n");
    P ("\t    %%lba = The current logical block. %%offset = The current file offset.\n");
    P ("\n");
    P ("      Lowercase means per pass stats, while uppercase means total stats.\n");
    P ("\n");
    P ("      Default: %s\n", keepalive0);
    P ("                     or if pass statistics summary is disabled:\n");
    P ("               %s\n", keepalive1);

    P ("\n    Log File Format Keywords:\n");
    P ("\t    %%dsf    = The device name.      %%device = The device path.\n");
    P ("\t    %%iodir  = The I/O direction.    %%iotype = The I/O type.\n");
    P ("\t    %%host   = The host name.        %%pid    = The process ID.\n");
    P ("\t    %%user   = The user name.\n");
    P ("\n");
    P ("      Example: log=dt_%%host_%%user_%%iodir_%%iotype-%%pid.log\n");

    P ("\n    I/O Tune File Format Keywords:\n");
    P ("\t    %%iotune = The I/O tune path.    %%tmpdir = The temporary directory.\n");
    P ("\t    %%host   = The host name.        %%user   = The user (login) name.\n");
    P ("\n");
    P ("      Example: iotune=%%iotune OR %%tmpdir%%host_MyIOtune_file\n");

    P ("\n    Pattern String Input:\n");
    P ("\t    \\\\ = Backslash   \\a = Alert (bell)   \\b = Backspace\n");
    P ("\t    \\f = Formfeed    \\n = Newline        \\r = Carriage Return\n");
    P ("\t    \\t = Tab         \\v = Vertical Tab   \\e or \\E = Escape\n");
    P ("\t    \\ddd = Octal Value    \\xdd or \\Xdd = Hexadecimal Value\n");
  
    P ("\n    Prefix Format Control:\n");
    P ("\t    %%d = The device name.           %%D = The real device name.\n");
    P ("\t    %%h = The host name.             %%H = The full host name.\n");
    P ("\t    %%p = The process ID.            %%P = The parent PID.\n");
    P ("\t    %%s = The device serial number.  %%u = The user name.\n");
    P ("\n");
    P ("      Example: prefix=\"%%u@%%h (pid %%p)\"\n");

    P ("\n    Time Input:\n");
    P ("\t    d = days (%d seconds),      h = hours (%d seconds)\n",
						SECS_PER_DAY, SECS_PER_HOUR);
    P ("\t    m = minutes (%d seconds),      s = seconds (the default)\n\n",
								SECS_PER_MIN);
    P ("\tArithmetic characters are permitted, and implicit addition is\n");
    P ("\tperformed on strings of the form '1d5h10m30s'.\n");

    P ("\n    Trigger Types:\n");
    P ("\t    br = Execute a bus reset.\n");
    P ("\t    bdr = Execute a bus device reset.\n");
    P ("\t    lr = Execute a device lun reset.\n");
    P ("\t    seek = Issue a seek to the failing lba.\n");
    P ("\t    cmd:string = Execute command with these args:\n");
    P ("\t      string dname op dsize offset position lba errno noprogt\n");
    P ("\t      args following cmd:string get appended to above args.\n");

    /*
     * Display the program defaults.
     */
    P ("\n    Defaults:\n");
    P ("\terrors=%u", DEFAULT_ERROR_LIMIT);
    P (", files=%u", DEFAULT_FILE_LIMIT);
    P (", passes=%u", DEFAULT_PASS_LIMIT);
    P (", records=%u", 0);
    P (", bs=%u", (unsigned int)BLOCK_SIZE);
    P (", log=stderr\n");

    P ("\tpattern=%#x", DEFAULT_PATTERN);
    P (", dispose=delete");
    P (", align=%d (page aligned)\n", dip->di_align_offset);

#if defined(AIO)
    P ("\taios=%d", dip->di_aio_bufs);
    P (", dlimit=%u", (unsigned int)dip->di_dump_limit);
#else /* !defined(AIO) */
    /*
     * dump_limit is defined as size_t, which is either 32 or 64 bits,
     * which poses a problem during display. Note: Should be 32 bits!
     * Workaround via a cast, since our default is a small value. :-)
     */
    P ("\tdlimit=%u", (unsigned int)dip->di_dump_limit);
#endif /* defined(AIO) */
    P (", oncerr=%s", (dip->di_oncerr_action == ABORT) ? "abort" : "continue");
    P (", volumes=%d, vrecords=%lu\n", dip->di_volume_limit, dip->di_volume_records);
    P ("\tiodir=%s", (dip->di_io_dir == FORWARD) ? "forward" : "reverse");
    P (", iomode=%s", (dip->di_io_mode == TEST_MODE) ? "test" :
			(dip->di_io_mode == COPY_MODE) ? "copy" : "verify");
    P (", iotype=%s", (dip->di_io_type == RANDOM_IO) ? "random" : "sequential");
    P (", stats=%s\n", (dip->di_stats_level == STATS_BRIEF) ? "brief" :
                       (dip->di_stats_level == STATS_FULL) ? "full" : "none");
    P ("\tiotseed=0x%08x, hdsize=%d", dip->di_iot_seed, dip->di_history_data_size);
    P (", maxbad=%u\n", dip->di_max_bad_blocks);
    P ("\n    --> %s <--\n", version_str);

    exit (SUCCESS);
    /*NOTREACHED*/
}
