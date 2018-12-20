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
 * Module:	dtaio.c
 * Author:	Robin T. Miller
 * Date:	August 26, 1993 
 *
 * Description:
 *	Functions to handle POSIX Asynchronous I/O requests for 'dt' program.
 */
#if defined(AIO)

#include "dt.h"
#if !defined(WIN32)
#  include <aio.h>
#endif /* !defined(WIN32) */
#include <limits.h>
#include <sys/stat.h>

#if !defined(AIO_PRIO_DFL)
#  define AIO_PRIO_DFL	0		/* Default scheduling priority. */
#endif /* !defined(AIO_PRIO_DFL) */

#if defined(_AIO_AIX_SOURCE)
/*
 * Allows testing with legacy AIX AIO (5.1 and older).
 */
#  define POSIX_4D11
  /*
   * Note: The usage of this field could be dangerous, but we need an
   * aiocb field to ease our port to AIX! (may need to revisit this).
   */
#  define aio_fildes aio_fp
#endif /* defined(_AIO_AIX_SOURCE) */

/*
 * Modification History:
 *
 * March 24th, 2013 by Robin T. Miller
 * 	Move buffer flushing to before write verify, to catch file system full conditions.
 * 	Otherwise, we may try to read/verify data never written in FS buffered mode.
 *
 * July 19th, 2012 by Robin T. Miller
 * 	Add support for retryable errors.
 *
 * November 15th, 2010 by Robin T. Miller
 *	When doing random I/O reads of a short record, due to a short write
 * (likely due to ENOSPC), ensure the transfer size used to generate the random
 * offset matches what was used during the write, or an incorrect offset may be
 * generated which results in a false data corruption.
 *
 * October 31st, 2010 by Robin T. Miller
 *	Add logic to msync (flush) data with user specified frequency.
 *
 * October 6th, 2010 by Robin T. Miller
 * 	Modify init_iotdata() calls to pass in the buffer to initialize, which
 * also allows us to optimize IOT pattern generation on writes (avoid extra copy).
 *
 * February 1st, 2010 by Robin T. Miller
 *	For Windows, detect file system full (ERROR_DISK_FULL) after the
 * WriteFile() API, since unlike POSIX API, the error is returned immediately
 * rather than when the I/O completes.
 *
 * January 23rd, 2010 by Robin T. Miller
 *	Add support for honoring the maxdata= option.
 *
 * March 31st, 2009 by Robin T. Miller.
 *      Add checks for EDQUOT, to treat like ENOSPC, treated like EOF.
 *
 * February 2nd, 2009 by Robin T. Miller.
 *	Add sanity check when closing file, acbs may bot be allocated yet.
 *	Add checks to ensure we do not read more than we wrote in write pass.
 * This sanity check is done for regular files to handle "file system full".
 * Without this check, we'll read more than we wrote, and report a false data
 * corruption (very bad and misleads testers).
 *
 * November 14th, 2008 by Robin T. Miller.
 *	When using the step option in the forward direction to regular files,
 * properly stop I/O when reaching the end position (now works like reverse).
 *
 * November 8th, 2008 by Robin T. Milller.
 *	Fix bug when checking for reverse I/O and step offset. If the step
 * offset was larger than the record size, we'd set EOF prematurely.
 *
 * October 27th, 2008 by Robin T. Miller.
 *	On systems supporting ECANCELED, which should be all POSIX AIO,
 * do not report this error, since I/O being cancelled is expected.
 *
 * July 23rd, 2008 by Robin T. Miller.
 *	When history is enabled, call save_history_data().
 *
 * June 24th, 2008 by Robin T. Miller.
 *	Add finer grain control over timing individual operations.
 *
 * March 11th, 2008 by Robin T. Miller.
 *	Added check for prefill flag to control buffer initialization.
 *
 * October 29th, 2007 by Robin T. Miller.
 *	Enhance Windows AIO implementation to handle end of file/media
 * error conditions properly.  Handle file system ERROR_HANDLE_EOF too!
 *
 * May 12th, 2007 by Robin Miller.
 *	Add no I/O progress checks for AIO's.
 *      Added support for triggers on failures.
 *	Removed WIN32 code from Tru64 EEI specific code.
 *
 * October 16th, 2006 by Robin T. Miller.
 *      Added support for recording a timestamp in each data block.
 *
 * May 1st, 2006 by Robin T. Miller.
 *	Added support for AIX Async I/O.
 *
 * January 19th, 2005 by Nagendra Vadlakunta.
 *	Added AIO support for Windows
 *
 * October 21st, 2004 by Robin Miller.
 *      For variable record lengths, ensure we prime the first size
 * to ensure it meets device size alignment requirements.
 *
 * February 13th, 2004 by Robin Miller.
 *      Factor in the file position when doing reverse I/O, to avoid
 * writing/reading into that area (which is now deemed protected).
 *
 * November 17th, 2003 by Robin Miller.
 *	Breakup output to stdout or stderr, rather than writing
 * all output to stderr.  If output file is stdout ('-') or a log
 * file is specified, then all output reverts to stderr.
 *
 * January 17th, 2003 by Robin Miller.
 *	On HP-UX, accept ENXIO for I/O's pass EOF.
 *
 * November 14th, 2002 by Robin Miller.
 *	On HP-UX, initialize aiocb->aio_sigevent field, or else
 * EINVAL is returned.  aio_sigevent.sigev_notify = SIGEV_NONE;
 *
 * June 25th, 2001 by Robin Miller.
 *	Restructured code associated with Tru64 Unix EEI, so we obtain
 * the EEI status for all tape errors, not just EIO errors.
 *
 * January 26th, 2001 by Robin Miller.
 *	Added support for reverse reading and writing.
 *
 * January 24th, 2001 by Robin Miller.
 *	Add support for variable I/O requests sizes.
 *
 * January 14th, 2001 by Robin Miller.
 *	Added support for multiple volumes option.
 *	Fixed multi-volume write w/lbdata option problem.
 *
 * October 4th, 2000 by Robin Miller.
 *	Update is_Eof() to accept ENXIO for AIO reads @ EOM on
 * SCO UnixWare systems.  All other systems return ENOSPC or zero.
 *
 * May 9th, 2000 by Robin Miller.
 *	Ensure the closing flag gets reset in dtaio_close_file() before
 * calling close_file(), or the file descriptor won't get closed!
 *
 * May 8th, 2000 by Robin Miller.
 *	Honor the di_closing flag, to avoid a race condition with the
 * close function being called again while still closing, from the
 * terminate() routine called by the runtime= alarm, or signals.
 *
 * February 17th, 2000 by Robin Miller.
 *	Adding better support for multi-volume tape testing.  Mainly,
 * make it work with writing multiple tape files, rather than one file.
 *
 * January 6th, 2000 by Robin Miller.
 *	Added support for multi-volume media.
 *	Added a couple missing aio_return() calls.
 *
 * December 30th, 1999 by Robin Miller.
 *	Modify call to do_random() to pass the transfer size.
 *
 * November 10th, 1999 by Robin Miller.
 *	If aio_return() fails, report device information.
 *
 * August 7th, 1999 by Robin Miller.
 *	Minor mods to support AIO on SCO UnixWare 7.1.
 *
 * July 29, 1999 by Robin Miller.
 *	Merge in changes made to compile on FreeBSD.
 *
 * July 22nd, 1999 by Robin Miller.
 *   o	Added support for IOT (DJ's) test pattern.
 *   o	Fixed problem writing wrong starting lba, when lbdata
 *	and random I/O options were enabled.
 * 
 * July 5th, 1999 by Robin Miller.
 *	Cleanup of compilation warnings on Linux.
 *
 * May 27, 1999 by Robin Miller.
 *	Added support for micro-second delays.
 *
 * March 1, 1999 by Robin Miller.
 *	For tapes when Debug is enabled, report the file number.
 *
 * January 13, 1998 by Robin Miller.
 *	Add support for restarting I/O's after EEI reset recovery.
 *	Modified dtaio_waitall() to optionally adjust data/file counts.
 *
 * December 21, 1998 by Robin Miller.
 *	Updates necessary to match tape API changes.
 *
 * November 16, 1998 by Robin Miller.
 *	Added pointer to current AIO control block for error reporting.
 *
 * October 26, 1998 by Robin Miller.
 *   o	Fix incorrect record number displayed when Debug is enabled.
 *   o	Don't exit read/write loops when processing partial records.
 *   o	Fix problem in write function, where short write processing,
 *	caused us not to write sufficent data bytes (actually, the
 *	file loop in write_file() caused dtaio_write_data() to be
 *	called again, and we'd actually end up writing too much!
 *   o	When random I/O and lbdata options are both enabled, use the
 *	file offset seeked to as the starting lbdata address.
 *
 * March 20, 1998 by Robin Miller.
 *	Update counts in dtaio_waitall() for accurate statistics.
 *
 * January 28, 1998 by Robin Miller.
 *	Add dtaio_close() function, to wait for queued I/O's when we're
 *	aborting, to avoid kernel I/O rundown problem, which panic's
 *	the system if we close the CAM disk driver device descriptor,
 *	prior to AIO's completing (fixed in steelos by Anton Verhulst).
 *
 * January 9, 1998 by Robin Miller.
 *	Don't initialize data buffer being written for "disable=compare"
 * which yields better performance.
 *
 * April 3, 1997 by Robin Miller.
 *	Removed use of undocumented AIO_SEEK_CUR in aio_offset.
 *	Also fixed bug where random I/O offset was clobbered, thus
 *	resulting in sequential I/O.
 *
 * February 28, 1996 by Robin Miller.
 *	Added support for copying and verifying device/files.
 *	Modified logic so read errors honor users' error limit.
 *	[ NOTE: Copy and verify operations are done sequentially. ]
 *
 * November 11, 1995 by Robin Miller.
 *	Fix bug with init'ing and performing pad byte verification.
 *	This caused variable length reads with small increment values
 *	to report an (invalid) pad byte data compare error. e.g.:
 *
 *	% dt of=/dev/rmt0h min=10k max=64k incr=1 pattern=incr
 *
 * July 17, 1995 by Robin Miller.
 *	Conditionalize aio_suspend() via "#if defined(POSIX_4D11)" for
 * earlier POSIX drafts so only one copy of this file is necessary.
 * [ NOTE: This is accomplished via -DPOSIX_4D11 in our Makefile. ]
 *
 * July 15, 1995 by Robin Miller.
 *	Fix end of media error handling (ENOSPC), and cleanup code.
 *
 * July 14, 1995 by Robin Miller.
 *	Add logic to allow rotating through 1st ROTATE_SIZE byes of buffers.
 *	[ This option was being silently ignored before, and nobody knew. ]
 *
 * April 15, 1994 by Wayne Casagrande.
 *	Update aiosuspend() interface, which now takes different arguments
 * due to POSIX standard changing.
 *
 * January 20, 1994 by Robin Miller.
 *	When initializing the data buffer, don't do the entire buffer since
 * init'ing large buffer (e.g. 100m) using min, max, and incr options cause
 * excessive paging and VERY poor performance.
 *
 * October 15, 1993 by Robin Miller.
 *	Sorry folks, major screw up on my part.  I forgot to redefine the
 * test function (tf_write_data) field to point a the dtaio_write_data()
 * function, so... synchronous writes were still being done (damn!!!).
 * Also fixed bug when writing to stop looping when end of file reached.
 */

/*
 * Forward References:
 */
static int dtaio_wait(struct dinfo *dip, struct aiocb *acbp);
static int dtaio_waitall(struct dinfo *dip, bool canceling);
static int dtaio_wait_reads(struct dinfo *dip);
static int dtaio_wait_writes(struct dinfo *dip);
static int dtaio_process_read(struct dinfo *dip, struct aiocb *acbp);
static int dtaio_process_write(struct dinfo *dip, struct aiocb *acbp);

#if defined(WIN32)
#  define AIO_NotQed	INVALID_HANDLE_VALUE
#else /* !defined(WIN32) */
#  define AIO_NotQed	-1		/* AIO request not queued flag.	*/
#endif /* defined(WIN32) */

/*
 * Declare the POSIX Asynchronous I/O test functions.
 */
struct dtfuncs aio_funcs = {
    /*	tf_open,		tf_close,		tf_initialize,	  */
	open_file,		dtaio_close_file,	dtaio_initialize,
    /*  tf_start_test,		tf_end_test,				  */
	init_file,		nofunc,
    /*	tf_read_file,		tf_read_data,		tf_cancel_reads,  */
	read_file,		dtaio_read_data,	dtaio_cancel_reads,
    /*	tf_write_file,		tf_write_data,		tf_cancel_writes, */
	write_file,		dtaio_write_data,	nofunc,
    /*	tf_flush_data,		tf_verify_data,		tf_reopen_file,   */
	flush_file,		verify_data,		reopen_file,
    /*	tf_startup,		tf_cleanup,		tf_validate_opts  */
	nofunc,			nofunc,			validate_opts
};

/************************************************************************
 *									*
 * dtaio_close_file() - Close an open file descriptor.			*
 *									*
 * Description:								*
 *	This function does the AIO file descriptor close processing.	*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *									*
 * Return Value:							*
 *		Returns 0 / -1 = SUCCESS / FAILURE.			*
 *									*
 ************************************************************************/
int
dtaio_close_file (struct dinfo *dip)
{
    int status = SUCCESS;

    if (dip->di_closing || (dip->di_fd == NoFd)) {
	return (status);		/* Closing or not open. */
    }
    /*
     * Avoid cancel'ing I/O more than once using the closing flag.
     * We can get called again by alarm expiring or signal handler.
     */
    dip->di_closing = TRUE;
    if (dip->di_acbs) {
	(void) dtaio_cancel (dip);
	status = dtaio_waitall (dip, FALSE);
    }
    dip->di_closing = FALSE;
    return (close_file (dip));
}

/*
 * Allocate and initialize AIO data structures.
 */
int
dtaio_initialize (struct dinfo *dip)
{
    struct aiocb *acbp;
    size_t size = (sizeof(struct aiocb) * dip->di_aio_bufs);
    int index;
    int status = SUCCESS;

    if ( (dip->di_dtype->dt_dtype == DT_TAPE) && dip->di_raw_flag && (dip->di_aio_bufs > 1) ) {
	Printf("Sorry, tapes are limited to 1 AIO with raw option!\n");
	dip->di_aio_bufs = 1;
	size = (sizeof(struct aiocb) * dip->di_aio_bufs);
    }

    dip->di_aio_index = 0;
    dip->di_aio_offset = (OFF_T) 0;
    if (dip->di_acbs == NULL) {
	dip->di_acbs = (struct aiocb *)Malloc(size);
	if (dip->di_rotate_flag) {
	    size_t psize = (dip->di_aio_bufs * sizeof(u_char *));
	    dip->di_aiobufs = (u_char **)Malloc(psize);
	}
    }
    for (index = 0, acbp = dip->di_acbs; index < dip->di_aio_bufs; index++, acbp++) {
	if (acbp->aio_buf == NULL) {
	    acbp->aio_buf = malloc_palign(dip->di_data_size, dip->di_align_offset);
	    if (dip->di_rotate_flag) {
		dip->di_aiobufs[index] = (u_char *) acbp->aio_buf;
	    }
	}
	acbp->aio_fildes = AIO_NotQed;
	acbp->aio_offset = (OFF_T) 0;
	acbp->aio_nbytes = dip->di_block_size;
#if !defined(WIN32)
	acbp->aio_reqprio = AIO_PRIO_DFL;	/* Set default priority. */
#if defined(SCO) || defined(HP_UX)
	/*
	 * Note: The AIO manual recommends setting AIO_RAW, but when
	 *       this is set, EINVAL is returned by aio_read/aio_write!
	 */
#  if defined(SCO)
	acbp->aio_flags = 0;			/* Must be zero to work! */
#  endif /* defined(SCO) */
	acbp->aio_sigevent.sigev_notify = SIGEV_NONE;
#if 0
	acbp->aio_flags = 0; /*AIO_RAW;*/	/* Required on SVR4.2(?) */
	/*
	 * This signaling method did not exist with the first release
	 * of POSIX AIO.  Perhaps I'll add this completion method in
	 * a future release.  Note: Tru64 Unix now supports this too!
	 */
	acbp->aio_sigevent.sigev_signo = /* use with SIGEV_SIGNAL */;
	acbp->aio_sigevent.sigev_notify = SIGEV_CALLBACK;
	acbp->aio_sigevent.sigev_func = my_aio_completion_function;
	acbp->aio_sigevent.sigev_value = acbp;
#endif /* 0 */
#endif /* defined(SCO) || defined(HP_UX) */

#endif /* !defined(WIN32) */
	/*
	 * Use first buffer allocated for initial skip reads, etc.
	 */
	if (index == 0) dip->di_data_buffer = (u_char *) acbp->aio_buf;
    }
    return (status);
}

/*
 * Cancel outstanding I/O on the specified file descriptor.
 */
int
dtaio_cancel (struct dinfo *dip)
{
    int status;

    if (dip->di_debug_flag) {
	Printf ("Canceling IO for fd = %d...\n", dip->di_fd);
	//if (dip->di_fd == NoFd) abort();
    }

    /*
     * Cancel any outstanding AIO's.
     */
#if defined(WIN32)
    /*
     * If the function fails, the return value is zero (0).
     */
    status = SUCCESS;
    if ( !CancelIo(dip->di_fd) ) {
	/* Note: Should NOT need this anymore... had a bug! */
	if ( GetLastError() != ERROR_INVALID_HANDLE) {
	    report_error (dip, "CancelIo", TRUE);
	    status = FAILURE;
	}
    }
#else /* !defined(WIN32) */
    if ((status = aio_cancel (dip->di_fd, (struct aiocb *) 0)) == FAILURE) {
	/*
	 * aio_cancel() returns EBADF if the file descriptor is
         * not valid, which could mean we didn't open device yet.
	 */
#if defined(SOLARIS)
        /* Why is EOVERFLOW being returned? */
	if ( (errno != EBADF) && (errno != EOVERFLOW) ) {
#else /* !defined(SOLARIS) */
	if (errno != EBADF) {
#endif /* defined(SOLARIS) */
	    report_error (dip, "aio_cancel", TRUE);
	}
	return (status);
    }
    if (dip->di_debug_flag) {

	switch (status) {

	    case AIO_ALLDONE:
		Printf ("All requests completed before cancel...\n");
		break;

	    case AIO_CANCELED:
		Printf ("Outstanding requests were canceled...\n");
		break;

	    case AIO_NOTCANCELED:
		Fprintf ("Outstanding (active?) request NOT canceled...\n");
		break;

	    default:
		Fprintf ("Unexpected status of %d from aio_cancel()...\n", status);
		break;
	}
    }
#endif /* defined(WIN32) */
    return (status);
}

int
dtaio_cancel_reads (struct dinfo *dip)
{
    int status;
#if defined(TAPE) && !defined(WIN32)
    struct dtype *dtp = dip->di_dtype;
#endif

    dip->di_aio_data_adjust = dip->di_aio_file_adjust = dip->di_aio_record_adjust = 0L;
    (void) dtaio_cancel (dip);
    status = dtaio_waitall (dip, TRUE);
#if defined(TAPE) && !defined(WIN32) /* no tape support for Windows */ 
    if (dip->di_aio_file_adjust && (dtp->dt_dtype == DT_TAPE) ) {
	daddr_t count = (daddr_t)dip->di_aio_file_adjust;
	/*
	 * Tapes are tricky... we must backup prior to the
	 * last file(s) we processed, then forward space over
	 * its' file mark to be properly positioned (yuck!!!).
	 */
	if (dip->di_end_of_file) count++;
	status = DoBackwardSpaceFile (dip, count);
	if (status == SUCCESS) {
	    status = DoForwardSpaceFile (dip, (daddr_t) 1);
	}
    } else if (dip->di_aio_record_adjust && (dtp->dt_dtype == DT_TAPE) ) {
	/*
	 * If we've read partially into the next file, backup.
	 */
	status = DoBackwardSpaceFile (dip, (daddr_t) 1);
	if (status == SUCCESS) {
	    status = DoForwardSpaceFile (dip, (daddr_t) 1);
	}
    }
#endif /* defined(TAPE) && !defined(WIN32) */
    return (status);
}

static int
dtaio_restart(struct dinfo *dip, struct aiocb *first_acbp)
{
    struct aiocb *acbp = first_acbp;
    int index, error, status = SUCCESS;

    /*
     * Find starting index of this AIO request.
     */
    for (index = 0; index < dip->di_aio_bufs; index++) {
	if (first_acbp == &dip->di_acbs[index]) break;
    }
    if (index == dip->di_aio_bufs) abort(); /* Should NEVER happen! */

    /*
     * Now, wait for and restart all previously active I/O's.
     */
    do {
	/*
	 * Assumes the first request was already waited for!
	 */
	if (dip->di_Debug_flag) {
	    Printf ("Restarting request for acbp at %#lx...\n", acbp);
	}
	if (dip->di_mode == READ_MODE) {
#if defined(WIN32)
	   error = SUCCESS;
	   if ( !ReadFile(acbp->aio_fildes, acbp->aio_buf, acbp->aio_nbytes,
			  NULL, &acbp->overlap) ) error = FAILURE;
#else /* !defined(WIN32) */
#if defined(_AIO_AIX_SOURCE)
	    error = aio_read (acbp->aio_fildes, acbp);
#else /* !defined(_AIO_AIX_SOURCE) */
	    error = aio_read (acbp);
#endif /* defined(_AIO_AIX_SOURCE) */
#endif /* defined(WIN32) */
	    if (error == FAILURE) {
		acbp->aio_fildes = AIO_NotQed;
		report_error (dip, "aio_read", TRUE);
		return (error);
	    }
	} else {
#if defined(WIN32)
	   error = SUCCESS;
	   if ( !WriteFile(acbp->aio_fildes, acbp->aio_buf, acbp->aio_nbytes,
			   NULL, &acbp->overlap) ) error = FAILURE;
#else /* !defined(WIN32) */
#if defined(_AIO_AIX_SOURCE)
	    error = aio_write(acbp->aio_fildes, acbp);
#else /* !defined(_AIO_AIX_SOURCE) */
	    error = aio_write(acbp);
#endif /* defined(_AIO_AIX_SOURCE) */
#endif /* defined(WIN32) */
	    if (error == FAILURE) {
		acbp->aio_fildes = AIO_NotQed;
		report_error (dip, "aio_write", TRUE);
		return (error);
	    }
	}
	if (++index == dip->di_aio_bufs) index = 0;
	if (index == dip->di_aio_index) break;

	acbp = &dip->di_acbs[index];
	if (acbp->aio_fildes == AIO_NotQed) abort();

	error = dtaio_wait (dip, acbp);
#if !defined(WIN32)
	(void) aio_return (acbp);	/* Why is this here? */
#endif /* !defined(WIN32) */

    } while (TRUE);

    return (status);
}

/*
 * dtaio_wait() - Wait for an AIO Request to Complete.
 *
 * Inputs:
 *	dip = The device information pointer.
 *	acbp = The AIO control block to wait for.
 *
 * Return Value:
 *	Returns Success/Failure = acbp done/error waiting.
 */
static int
dtaio_wait (struct dinfo *dip, struct aiocb *acbp)
{
    int status;

    if (dip->di_Debug_flag) {
	Printf ("Waiting for acbp at %#lx to complete...\n", acbp);
    }
    /*
     * Since we always come here to wait for an I/O request, we'll time
     * here rather than when issuing each aio_{read|write} request.
     */
    if (dip->di_noprog_flag && optiming_table[AIOWAIT_OP].opt_timing_flag) {
	dip->di_optype = AIOWAIT_OP;
	dip->di_initiated_time = time((time_t *)0);
    }
    /*
     * TODO: This needs cleaned up!
     * Make Windows functions to mimic AIO API's.
     */
#if defined(WIN32)
    status = SUCCESS;
    acbp->last_error = SUCCESS;
# if defined(TIMER_METHOD)
    if (alarmtime || dip->di_runtime) SleepEx(1, TRUE);	/* Put thread in an alertable state. */
# endif /* defined(TIMER_METHOD) */

    while (!GetOverlappedResult (acbp->aio_fildes, &acbp->overlap, &acbp->bytes_rw, FALSE))  {
	DWORD error = GetLastError();
	if (error == ERROR_IO_INCOMPLETE) {
	    /* Note: Polling is ineffecient (IMO), must be a better way? */
	    Sleep(10); /* Not done yet, wait a while then retry. */
	} else {
	    /*
	     * Later we check bytes_rw to know the status of operation
	     * that's why we are inintializing with FAILURE in case of error
	     * in case of success it will have total bytes read/write.
	     */
	    status = FAILURE;
	    acbp->bytes_rw = status;
	    acbp->last_error = error;
	    //report_error(dip, "GetOverlappedResult", TRUE);
	    break;
	}
    }
#else /* !defined(WIN32) */
    /*
     * Loop waiting for an I/O request to complete.
     */
    while ((status = aio_error (acbp)) == EINPROGRESS) {
#if defined(POSIX_4D11)
#  if defined(_AIO_AIX_SOURCE)
	if ((status = aio_suspend (1, (struct aiocb **)&acbp)) == FAILURE) {
#  else /* !defined(_AIO_AIX_SOURCE) */
	if ((status = aio_suspend (1, (const struct aiocb **)&acbp)) == FAILURE) {
#  endif /* defined(_AIO_AIX_SOURCE) */
#else /* Beyond draft 11... */
	if ((status = aio_suspend ((const struct aiocb **)&acbp,1,NULL)) == FAILURE) {
#endif /* defined(POSIX_4D11) */
	    if (errno != EINTR) {
		report_error (dip, "aio_suspend", TRUE);
		goto done;
	    }
	}
    }
    if ( (status == FAILURE) && !terminating_flag) {
	report_error (dip, "aio_error", TRUE);
    }
done:
#endif /* defined(WIN32) */
    if (dip->di_noprog_flag) {
	dip->di_optype = NONE_OP;
	dip->di_initiated_time = (time_t) 0;
    }
    return (status);
}

static int
dtaio_waitall(struct dinfo *dip, bool canceling)
{
    struct aiocb *acbp;
    register size_t bsize;
    register ssize_t count;
    ssize_t adjust;
    int index, error, status = SUCCESS;

    /*
     * Loop waiting for all I/O requests to complete.
     */
    for (index = 0; index < dip->di_aio_bufs; index++) {
	acbp = &dip->di_acbs[dip->di_aio_index];
	if (++dip->di_aio_index == dip->di_aio_bufs) dip->di_aio_index = 0;
	if (acbp->aio_fildes == AIO_NotQed) continue;
	if ( (error = dtaio_wait (dip, acbp))) {
	    status = error;
	    if (status == FAILURE) {
		acbp->aio_fildes = AIO_NotQed;
		continue;	/* aio_error() failed! */
	    }
	}
#if defined(WIN32)
	/* bytes_rw is bytes read/write in previous operation or FAILURE */
	count = acbp->bytes_rw;
	error = acbp->last_error;
#else /* !defined(WIN32) */
	count = aio_return (acbp);
#endif /* defined(WIN32) */
	acbp->aio_fildes = AIO_NotQed;
	errno = error;
	if ( (count == FAILURE) && !dip->di_closing && !terminating_flag) {
	    /*
	     * End of media is handled below, handle expected errors.
	     */
#if defined(WIN32)
	    if ( (error != ERROR_DISK_FULL) &&
		 (error != ERROR_HANDLE_EOF) &&
		 (error != ERROR_SECTOR_NOT_FOUND) ) {
#elif defined(ECANCELED)
	    if ( (error != ENOSPC) && (error != ENXIO) && (error != EDQUOT) && (error != ECANCELED) ) {
#elif defined(SCO) || defined(HP_UX)
	    if ( (error != ENOSPC) && (error != ENXIO) && (error != EDQUOT) ) {
#else /* !defined(SCO) && !defined(HP_UX) && !defined(AIX) */
	    if ( (error != ENOSPC) && (error != EDQUOT) ) {
#endif /* defined(SCO) || defined(HP_UX) || defined(AIX) */
		dip->di_current_acb = acbp;
		report_error (dip, "dtaio_waitall", TRUE);
		ReportDeviceInfo (dip, acbp->aio_nbytes, 0, (errno == EIO));
		if (dip->di_mode == READ_MODE) {
		    (void)ExecuteTrigger(dip, "read");
		} else {
		    (void)ExecuteTrigger(dip, "write");
		}
		status = FAILURE;
		/* adjust counts below */
	    }
	} else if (error) {
	    count = FAILURE;
	}

	bsize = acbp->aio_nbytes;

	/*
	 * Adjust for short records or no data transferred.
	 */
	if (count == FAILURE) {
	    dip->di_aio_data_bytes -= bsize;
	    dip->di_aio_file_bytes -= bsize;
	} else if ( (adjust = (bsize - count)) ) {
	    if (dip->di_debug_flag) {
		Printf("Adjusting byte counts by %d bytes...\n", adjust);
	    }
	    dip->di_aio_data_bytes -= adjust;
	    dip->di_aio_file_bytes -= adjust;
	}

	/*
	 * Count files or records to adjust after I/O's complete.
	 */
	if ( is_Eof (dip, count, (int *) 0) ) {
	    if (!dip->di_end_of_media) dip->di_aio_file_adjust++;
	} else if (count > (ssize_t) 0) {
	    dip->di_aio_record_adjust++;
	    /*
	     * Adjust counts for total statistics.
	     */
	    if (!canceling) {
		if (dip->di_mode == READ_MODE) {
		    dip->di_dbytes_read += count;
		    dip->di_fbytes_read += count;
		} else {
		    dip->di_dbytes_written += count;
		    dip->di_fbytes_written += count;
		}
		dip->di_aio_data_adjust += count;
		if ((size_t)count == bsize) {
                    if (dip->di_mode == READ_MODE) {
		        dip->di_full_reads++;
                    } else {
                        dip->di_full_writes++;
                    }
		} else {
                    if (dip->di_mode == READ_MODE) {
		        dip->di_partial_reads++;
                    } else {
                        dip->di_partial_writes++;
                    }
		}
	    }
	}
    }
    return (status);
}

/*
 * Function to wait for and process read requests.
 */
static int
dtaio_wait_reads (struct dinfo *dip)
{
    struct aiocb *acbp;
    int index, error, status = SUCCESS;

    /*
     * Loop waiting for all I/O requests to complete.
     */
    for (index = 0; index < dip->di_aio_bufs; index++) {
	acbp = &dip->di_acbs[dip->di_aio_index];
	if (++dip->di_aio_index == dip->di_aio_bufs) dip->di_aio_index = 0;
	if (acbp->aio_fildes == AIO_NotQed) continue;
	
	if ( (error = dtaio_process_read (dip, acbp)) == FAILURE) {
	    status = error;
	}
	if ( dip->di_end_of_file ||
	     (dip->di_records_read >= dip->di_record_limit) || (dip->di_fbytes_read >= dip->di_data_limit) ) {
	    break;
	}
    }
    return (status);
}

/*
 * Function to wait for and process write requests.
 */
static int
dtaio_wait_writes (struct dinfo *dip)
{
    struct aiocb *acbp;
    int index, error, status = SUCCESS;

    /*
     * Loop waiting for all I/O requests to complete.
     */
    for (index = 0; index < dip->di_aio_bufs; index++) {
	acbp = &dip->di_acbs[dip->di_aio_index];
	if (++dip->di_aio_index == dip->di_aio_bufs) dip->di_aio_index = 0;
	if (acbp->aio_fildes == AIO_NotQed) continue;
	
	if ( (error = dtaio_process_write (dip, acbp)) == FAILURE) {
	    status = error;
	    if (dip->di_error_count >= dip->di_error_limit) break;
	}
    }
    return (status);
}

/************************************************************************
 *									*
 * dtaio_read_data() - Read and optionally verify data read.		*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *									*
 * Outputs:	Returns SUCCESS/FAILURE = Ok/Error.			*
 *									*
 ************************************************************************/
int
dtaio_read_data (struct dinfo *dip)
{
    register struct aiocb *acbp;
    int error, status = SUCCESS;
    register size_t bsize, dsize;
    bool check_rwbytes = FALSE;
    bool check_write_limit = FALSE;

    if (dip->di_random_access) {
	if (dip->di_io_dir == REVERSE) {
	    (void)set_position(dip, (OFF_T)dip->di_rdata_limit, FALSE);
	}
	dip->di_aio_lba = get_lba(dip);
	dip->di_aio_offset = get_position(dip);
    } else {
	dip->di_aio_offset = dip->di_offset;
	dip->di_aio_lba = make_lbdata (dip, dip->di_aio_offset);
    }
    dip->di_aio_data_bytes = dip->di_aio_file_bytes = dip->di_aio_record_count = 0;

    if ( dip->di_last_fbytes_written &&
	 (dip->di_dtype->dt_dtype == DT_REGULAR) ) {
	if ( dip->di_files_read == (dip->di_last_files_written - 1) ) {
	    check_write_limit = TRUE;
	    if (dip->di_fDebugFlag) {
		Printf("DEBUG: Limiting data read on file #%d to " FUF " bytes from last written.\n",
		       (dip->di_files_read + 1), dip->di_last_fbytes_written);
	    }
	}
    }

    /*
     * For variable length records, initialize to minimum record size.
     */
    if (dip->di_min_size) {
        if (dip->di_variable_flag) {
            dsize = get_variable (dip);
        } else {
	    dsize = dip->di_min_size;
        }
    } else {
	dsize = dip->di_block_size;
    }

    /*
     * Now read and optionally verify the input records.
     */
    while ( (dip->di_error_count < dip->di_error_limit) &&
	    (dip->di_fbytes_read < dip->di_data_limit) &&
	    (dip->di_records_read < dip->di_record_limit) ) {

	if (dip->di_terminating) break;

	if ( dip->di_max_data && (dip->di_maxdata_read >= dip->di_max_data) ) {
	    break;
	}

	if (dip->di_volumes_flag && (dip->di_multi_volume >= dip->di_volume_limit) &&
		  (dip->di_volume_records >= dip->di_volume_records)) {
	    dip->di_volume_records = dip->di_volume_records;
	    break;
	}

	/*
	 * Two loops are used with AIO.  The inner loop queues requests up
	 * to the requested amount, and the outer loop checks the actual
	 * data processed.  This is done mainly for tapes to handle short
	 * reads & to efficiently handle multiple tape files.
	 */
	while ( (dip->di_error_count < dip->di_error_limit) &&
		(dip->di_aio_record_count < dip->di_record_limit) &&
		(dip->di_aio_file_bytes < dip->di_data_limit) ) {

	    if (dip->di_terminating) break;
	    //HANDLE_TERMINATE(dip);

	    if ( dip->di_max_data &&
		 ((dip->di_aio_file_bytes + dip->di_maxdata_read) >= dip->di_max_data) ) {
		break;
	    }

	    if (dip->di_volumes_flag && (dip->di_multi_volume >= dip->di_volume_limit) &&
		      (dip->di_volume_records >= dip->di_volume_records)) {
		break;
	    }

	    if (dip->di_read_delay) {			/* Optional read delay.	*/
		mySleep(dip, dip->di_read_delay);
	    }

	    /*
	     * If data limit was specified, ensure we don't exceed it.
	     */
	    if ( (dip->di_aio_file_bytes + dsize) > dip->di_data_limit) {
		bsize = (size_t)(dip->di_data_limit - dip->di_aio_file_bytes);
	    } else {
		bsize = dsize;
	    }

	    acbp = &dip->di_acbs[dip->di_aio_index];
	    /*
	     * If requested, rotate the data buffer through ROTATE_SIZE bytes
	     * to force various unaligned buffer accesses.
	     */
	    if (dip->di_rotate_flag) {
		dip->di_data_buffer = dip->di_aiobufs[dip->di_aio_index];
		dip->di_data_buffer += (dip->di_rotate_offset++ % ROTATE_SIZE);
		acbp->aio_buf = dip->di_data_buffer;
	    } else {
		dip->di_data_buffer = (u_char *) acbp->aio_buf;
	    }

	    if (dip->di_io_dir == REVERSE) {
		/*debug*/ if (!dip->di_aio_offset) abort(); /*debug*/
		bsize = (size_t)MIN((dip->di_aio_offset - dip->di_file_position), (OFF_T)bsize);
		dip->di_aio_offset = (OFF_T)(dip->di_aio_offset - bsize);
	    }

            if (dip->di_debug_flag && (bsize != dsize) && !dip->di_variable_flag) {
                Printf ("Record #%lu, Reading a partial record of %lu bytes...\n",
                                    (dip->di_aio_record_count + 1), bsize);
            }

	    if (dip->di_io_type == RANDOM_IO) {
                /*
		 * BEWARE: The size *must* match the write size, or you'll get
		 * a different offset, since the size is used in calculations.
		 */
		acbp->aio_offset = do_random (dip, FALSE, bsize);
	    } else {
		acbp->aio_offset = dip->di_aio_offset;
	    }

	    /*
	     * If we wrote data, ensure we don't read more than we wrote.
	     */
	    if (check_write_limit) {
		if ( (dip->di_aio_file_bytes + bsize) > dip->di_last_fbytes_written) {
		    dsize = bsize;	/* Save the original intended size. */
		    bsize = (size_t)(dip->di_last_fbytes_written - dip->di_aio_file_bytes);
		    check_rwbytes = TRUE;
		    if (bsize == (size_t) 0) {
			break;
		    }
		    check_last_write_info(dip, acbp->aio_offset, bsize, dsize);
		}
	    }

	    acbp->aio_fildes = dip->di_fd;
	    acbp->aio_nbytes = bsize;

	    /*
	     * If we'll be doing a data compare after the read, then
	     * fill the data buffer with the inverted pattern to ensure
	     * the buffer actually gets written into (driver debug mostly).
	     */
	    if ((dip->di_io_mode == TEST_MODE) && dip->di_compare_flag) {
		if (dip->di_prefill_flag) {
		    init_buffer (dip, dip->di_data_buffer, bsize, ~dip->di_pattern);
		}
		init_padbytes (dip->di_data_buffer, bsize, ~dip->di_pattern);
	    }

	    if (dip->di_Debug_flag) {
		large_t iolba = NO_LBA;
                OFF_T iopos = (OFF_T) 0;
		if (dip->di_random_access || dip->di_lbdata_flag || dip->di_iot_pattern) {
                    iopos = (dip->di_volume_bytes + acbp->aio_offset);
		    iolba = make_lbdata(dip, iopos);
		}
		report_record(dip, (dip->di_files_read + 1), (dip->di_aio_record_count + 1),
			iolba, iopos, READ_MODE, (void *)acbp->aio_buf, acbp->aio_nbytes);
	    }

#if defined(WIN32)
	    acbp->overlap.hEvent = 0;
	    acbp->overlap.Offset = ((PLARGE_INTEGER)(&acbp->aio_offset))->LowPart;
	    acbp->overlap.OffsetHigh = ((PLARGE_INTEGER)(&acbp->aio_offset))->HighPart;
	    error = ReadFile(acbp->aio_fildes, acbp->aio_buf, acbp->aio_nbytes,
						NULL, &acbp->overlap);
	    if ( !error && (GetLastError() != ERROR_IO_PENDING) ) {
	    	if (GetLastError() == ERROR_HANDLE_EOF) {
		    /* Messy, but we must handle this here! */
		    acbp->aio_fildes = AIO_NotQed;
		    status = dtaio_wait_reads(dip);
		    dip->di_end_of_file = TRUE;
		    exit_status = END_OF_FILE;
		    break;
		}
		error = FAILURE;
		acbp->aio_fildes = AIO_NotQed;
		report_error (dip, "ReadFile", TRUE);
		return (error);
	    }
#else /* !defined(WIN32) */
# if defined(_AIO_AIX_SOURCE)
	    if ( (error = aio_read (acbp->aio_fildes, acbp)) == FAILURE) {
# else /* !defined(_AIO_AIX_SOURCE) */
	    if ( (error = aio_read (acbp)) == FAILURE) {
# endif /* defined(_AIO_AIX_SOURCE) */
		acbp->aio_fildes = AIO_NotQed;
		report_error (dip, "aio_read", TRUE);
		return (error);
	    }
#endif /* !defined(WIN32) */

	    /*
	     * Must adjust record/data counts here to avoid reading
	     * too much data, even though the reads are incomplete.
	     */
	    dip->di_aio_data_bytes += bsize;
	    dip->di_aio_file_bytes += bsize;
	    dip->di_aio_record_count++;

	    if (dip->di_io_dir == FORWARD) {
		dip->di_aio_offset += bsize;
	    }

	    if (dip->di_step_offset) {
		if (dip->di_io_dir == FORWARD) {
		    dip->di_aio_offset += dip->di_step_offset;
		} else if ((dip->di_aio_offset -= dip->di_step_offset) <= (OFF_T) dip->di_file_position) {
		    dip->di_aio_offset = (OFF_T) dip->di_file_position;
		}
	    }

	    /*
	     * For variable length records, adjust the next record size.
	     */
	    if (dip->di_min_size) {
		if (dip->di_variable_flag) {
		    dsize = get_variable (dip);
		} else {
		    dsize += dip->di_incr_count;
		    if (dsize > dip->di_max_size) dsize = dip->di_min_size;
		}
	    }

	    /*
	     * Always ensure the next control block has completed.
	     */
	    if (++dip->di_aio_index == dip->di_aio_bufs) dip->di_aio_index = 0;

	    /*
	     * Special handling of step option:
	     */
	    if ( (dip->di_io_dir == FORWARD)       &&
		 dip->di_step_offset && dip->di_num_slices &&
		 ((dip->di_aio_offset + (OFF_T)dsize) >= dip->di_end_position) ) {
		break;
	    } else if ( (dip->di_io_dir == REVERSE) && (dip->di_aio_offset == (OFF_T) dip->di_file_position) ) {
		break;
	    }
	    acbp = &dip->di_acbs[dip->di_aio_index];
	    if (acbp->aio_fildes == AIO_NotQed) continue; /* Never Q'ed. */

	    if ( (status = dtaio_process_read (dip, acbp)) == FAILURE) {
		return (status);
	    }
	    //if ( dip->di_end_of_file ) return (status);
	    if ( dip->di_end_of_file ) break;
	}
	/*
	 * We get to this point after we've Q'ed enough requests to
	 * fulfill the requested record and/or data limit.  We now
	 * wait for these Q'ed requests to complete, adjusting the
	 * global transfer statistics appropriately which reflects
	 * the actual data processed.
	 */
	status = dtaio_wait_reads(dip);
	/*
	 * For regular files, if we've read as much as we've written,
	 * then set a fake EOF to stop this read pass.
	 */
	if ( check_rwbytes &&
	     (dip->di_fbytes_read == dip->di_last_fbytes_written) ) {
	    set_Eof(dip);
	}
	if ( dip->di_end_of_file ) break; /* Stop reading at end of file. */

    }
    return (status);
}

/************************************************************************
 *									*
 * dtaio_process_read() - Process AIO reads & optionally verify data.	*
 *									*
 * Description:								*
 *	This function does waits for the requested AIO read request,	*
 * checks the completion status, and optionally verifies the data read.	*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *		acbp = The AIO control block.				*
 *									*
 * Outputs:	Returns SUCCESS/FAILURE/WARNING = Ok/Error/Warning.	*
 *									*
 ************************************************************************/
static int
dtaio_process_read (struct dinfo *dip, struct aiocb *acbp)
{
    struct dtfuncs *dtf = dip->di_funcs;
    register size_t bsize, dsize;
    register ssize_t count;
    ssize_t adjust;
    int error, status = SUCCESS;

    dip->di_retry_count = 0;
retry:
    dip->di_current_acb = acbp;
    error = dtaio_wait (dip, acbp);
#if defined(WIN32)
    /* total bytes read by ReadFile call or FAILURE in case or error */
    count = acbp->bytes_rw;
    error = acbp->last_error;
#else /* !defined(WIN32) */
    count = aio_return (acbp);
#endif /* defined(WIN32) */

    errno = error;
    bsize = acbp->aio_nbytes;

    if (dip->di_history_size) {
	save_history_data(dip,
			  (dip->di_files_read + 1), (dip->di_records_read + 1),
			  READ_MODE, acbp->aio_offset, (u_char *)acbp->aio_buf, bsize, count);
    }

    if (dip->di_volumes_flag && (dip->di_multi_volume >= dip->di_volume_limit) &&
	      (dip->di_volume_records == dip->di_volume_records)) {
	acbp->aio_fildes = AIO_NotQed;
	return (SUCCESS);
    }

    if (count == FAILURE) {
	bool errno_flag;
	/*
	 * End of media is handled below.
	 */
#if defined(SCO) || defined(HP_UX) || defined(AIX)
	if ( (error != ENOSPC) && (error != ENXIO) && (error != EDQUOT) ) {
	    errno_flag = (bool)(error == EIO);
#elif defined(WIN32)
       	if ( (error != ERROR_DISK_FULL) &&
	     (error != ERROR_HANDLE_EOF) &&
	     (error != ERROR_SECTOR_NOT_FOUND) ) {
	    errno_flag = (bool)(error == ERROR_IO_DEVICE);
#else /* !defined(SCO) && !defined(HP_UX) && !defined(AIX) */
	if ( (error != ENOSPC) && (error != EDQUOT) ) {
	    errno_flag = (bool)(error == EIO);
#endif /* defined(SCO) || defined(HP_UX) || defined(AIX) */
	    report_error (dip, "dtaio_process_read", TRUE);
	    if ( dip->di_retry_entries && is_retryable(dip, dip->di_errno) ) {
		ReportDeviceInfo (dip, acbp->aio_nbytes, 0, FALSE);
		if ( retry_operation(dip) ) {
		    error = dtaio_restart(dip, acbp);
		    if (error) {
			acbp->aio_fildes = AIO_NotQed;
			return (error);
		    }
		    goto retry;
		}
	    } else {
		ReportDeviceInfo (dip, acbp->aio_nbytes, 0, errno_flag);
	    }
	    (void)ExecuteTrigger(dip, "read");
	    acbp->aio_fildes = AIO_NotQed;
	    return (FAILURE);
	}
    } else if (error) {
	count = FAILURE;
    }

    acbp->aio_fildes = AIO_NotQed;
    dip->di_data_buffer = (u_char *)acbp->aio_buf;

    if (dip->di_min_size) {
	dsize = bsize;
    } else {
	dsize = dip->di_block_size;
    }

    /*
     * Adjust for short records or no data transferred.
     */
    if (count == FAILURE) {
	dip->di_aio_data_bytes -= bsize;
	dip->di_aio_file_bytes -= bsize;
    } else if ( (adjust = (bsize - count)) ) {
	if (dip->di_debug_flag) {
	    Printf("Adjusting byte counts by %d bytes...\n", adjust);
	}
	dip->di_aio_data_bytes -= adjust;
	dip->di_aio_file_bytes -= adjust;
    }

    /*
     * Process end of file/media conditions and handle multi-volume.
     */
    if ( is_Eof (dip, count, &status) ) {
	if (dip->di_multi_flag) {
	    if ( (dip->di_dtype->dt_dtype == DT_TAPE) &&
		 !dip->di_end_of_logical ) {
		return (status);	/* Expect two file marks @ EOM. */
	    }
	    status = HandleMultiVolume (dip);
	    dip->di_aio_record_count = dip->di_records_read;
	    /*dip->di_aio_file_bytes = dip->di_dbytes_read;*/
	    dip->di_aio_offset = (OFF_T) 0;
	}
	return (status);
    } else {
	dip->di_end_of_file = FALSE;	/* Reset saved end of file state. */
	if (count > (ssize_t) 0) {
	    dip->di_dbytes_read += count;
	    dip->di_fbytes_read += count;
	    dip->di_vbytes_read += count;
	    dip->di_maxdata_read += count;
	    if ((size_t)count == dsize) {
                dip->di_full_reads++;
            } else {
                dip->di_partial_reads++;
	    }
	    dip->di_offset = (acbp->aio_offset + count);
	}
	if ((status = check_read (dip, count, bsize)) == FAILURE) {
	    if (dip->di_error_count >= dip->di_error_limit) return (status);
	} else if (dip->di_io_mode == COPY_MODE) {
	    status = copy_record (dip->di_output_dinfo, dip->di_data_buffer, count);
            dip->di_error_count = dip->di_output_dinfo->di_error_count;	/* HACK! */
	    if ( (dip->di_error_count >= dip->di_error_limit) || dip->di_end_of_file) return (status);
	} else if (dip->di_io_mode == VERIFY_MODE) {
	    status = verify_record (dip->di_output_dinfo, dip->di_data_buffer, count);
            dip->di_error_count = dip->di_output_dinfo->di_error_count;	/* HACK! */
	    if ( (dip->di_error_count >= dip->di_error_limit) || dip->di_end_of_file) return (status);
	}
    }

    /*
     * Verify the data (unless disabled).
     */
    if ( (status != FAILURE) && dip->di_compare_flag && (dip->di_io_mode == TEST_MODE)) {
	ssize_t vsize = count;
	if (dip->di_lbdata_flag || dip->di_iot_pattern) {
	    dip->di_aio_lba = make_lbdata(dip, (dip->di_volume_bytes + acbp->aio_offset));
	    if (dip->di_iot_pattern) {
		dip->di_aio_lba = init_iotdata (dip, dip->di_pattern_buffer, vsize, dip->di_aio_lba, dip->di_lbdata_size);
	    }
	}
	status = (*dtf->tf_verify_data)(dip, dip->di_data_buffer, vsize, dip->di_pattern, &dip->di_aio_lba);
	/*
	 * Verify the pad bytes (if enabled).
	 */
	if ( (status == SUCCESS) && dip->di_pad_check) {
	    (void) verify_padbytes (dip, dip->di_data_buffer, vsize, ~dip->di_pattern, bsize);
	}
    }
    dip->di_records_read++;
    dip->di_volume_records++;

    /*
     * Special handling of step option:
     */
    if ( (dip->di_io_dir == FORWARD)       &&
	 dip->di_step_offset && dip->di_num_slices &&
	 ((acbp->aio_offset + dip->di_step_offset + (OFF_T)dsize) >= dip->di_end_position) ) {
	set_Eof(dip);
    } else if (dip->di_io_dir == REVERSE) {
	if ( (acbp->aio_offset == (OFF_T) dip->di_file_position) ||
	     (dip->di_step_offset && ((acbp->aio_offset - dip->di_step_offset) <= (OFF_T) dip->di_file_position)) ) {
	    set_Eof(dip);
	    dip->di_beginning_of_file = TRUE;
	}
    }
    return (status);
}

/************************************************************************
 *									*
 * dtaio_write_data() - Write specified data to the output file.	*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *									*
 * Outputs:	Returns SUCCESS/FAILURE = Ok/Error.			*
 *									*
 ************************************************************************/
int
dtaio_write_data (struct dinfo *dip)
{
    register struct aiocb *acbp;
    int error, status = SUCCESS;
    register size_t bsize, dsize;
    u_int32 lba = dip->di_lbdata_addr;

    if (dip->di_random_access) {
	if (dip->di_io_dir == REVERSE) {
	    (void)set_position(dip, (OFF_T)dip->di_rdata_limit, FALSE);
	}
	dip->di_aio_lba = lba = get_lba(dip);
	dip->di_aio_offset = get_position(dip);
    } else {
	dip->di_aio_offset = dip->di_offset;
	dip->di_aio_lba = lba = make_lbdata (dip, dip->di_aio_offset);
    }
    dip->di_aio_data_bytes = dip->di_aio_file_bytes = dip->di_aio_record_count = 0;

    /*
     * For variable length records, initialize to minimum record size.
     */
    if (dip->di_min_size) {
        if (dip->di_variable_flag) {
            dsize = get_variable (dip);
        } else {
	    dsize = dip->di_min_size;
        }
    } else {
	dsize = dip->di_block_size;
    }

    /*
     * Now write the specifed number of records.
     */
    while ( (dip->di_error_count < dip->di_error_limit) &&
	    (dip->di_fbytes_written < dip->di_data_limit) &&
	    (dip->di_records_written < dip->di_record_limit) ) {

	if (dip->di_terminating) break;

	if ( dip->di_max_data && (dip->di_maxdata_written >= dip->di_max_data) ) {
	    break;
	}

	if (dip->di_volumes_flag && (dip->di_multi_volume >= dip->di_volume_limit) &&
		  (dip->di_volume_records >= dip->di_volume_records)) {
	    dip->di_volume_records = dip->di_volume_records;
	    break;
	}

	/*
	 * Two loops are used with AIO.  The inner loop queues requests up
	 * to the requested amount, and the outer loop checks the actual
	 * data processed.  This is done to handle short reads, which can
	 * happen frequently with random I/O and large block sizes.
	 */
	while ( (dip->di_error_count < dip->di_error_limit) &&
		(dip->di_aio_record_count < dip->di_record_limit) &&
		(dip->di_aio_file_bytes < dip->di_data_limit) ) {

	    if (dip->di_terminating) break;
	    //HANDLE_TERMINATE(dip);

	    if ( dip->di_max_data &&
		 ((dip->di_aio_file_bytes + dip->di_maxdata_written) >= dip->di_max_data) ) {
		break;
	    }

	    if (dip->di_volumes_flag && (dip->di_multi_volume >= dip->di_volume_limit) &&
		      (dip->di_volume_records >= dip->di_volume_records)) {
		break;
	    }

	    if (dip->di_write_delay) {			/* Optional write delay	*/
		mySleep(dip, dip->di_write_delay);
	    }

	    /*
	     * If data limit was specified, ensure we don't exceed it.
	     */
	    if ( (dip->di_aio_file_bytes + dsize) > dip->di_data_limit) {
		bsize = (size_t)(dip->di_data_limit - dip->di_aio_file_bytes);
	    } else {
		bsize = dsize;
	    }

	    acbp = &dip->di_acbs[dip->di_aio_index];
	    /*
	     * If requested, rotate the data buffer through ROTATE_SIZE bytes
	     * to force various unaligned buffer accesses.
	     */
	    if (dip->di_rotate_flag) {
		dip->di_data_buffer = dip->di_aiobufs[dip->di_aio_index];
		dip->di_data_buffer += (dip->di_rotate_offset++ % ROTATE_SIZE);
		acbp->aio_buf = dip->di_data_buffer;
	    } else {
		dip->di_data_buffer = (u_char *) acbp->aio_buf;
	    }

	    acbp->aio_fildes = dip->di_fd;

	    if (dip->di_io_dir == REVERSE) {
		/*debug*/ if (!dip->di_aio_offset) abort(); /*debug*/
		bsize = (size_t)MIN((dip->di_aio_offset - dip->di_file_position), (OFF_T)bsize);
		dip->di_aio_offset = (OFF_T)(dip->di_aio_offset - bsize);
	    }

            acbp->aio_nbytes = bsize;

            if (dip->di_debug_flag && (bsize != dsize) && !dip->di_variable_flag) {
                Printf ("Record #%lu, Writing a partial record of %d bytes...\n",
                                    (dip->di_aio_record_count + 1), bsize);
            }

	    if (dip->di_io_type == RANDOM_IO) {
		acbp->aio_offset = do_random (dip, FALSE, bsize);
	    } else {
		acbp->aio_offset = dip->di_aio_offset;
	    }

	    if (dip->di_iot_pattern || dip->di_lbdata_flag) {
		lba = make_lbdata (dip, (dip->di_volume_bytes + acbp->aio_offset));
	    }

	    /*
	     * Initialize the data buffer with a pattern.
	     */
	    if ((dip->di_io_mode == TEST_MODE) && dip->di_compare_flag) {
	        if (dip->di_iot_pattern) {
		    lba = init_iotdata (dip, dip->di_data_buffer, bsize, lba, dip->di_lbdata_size);
		} else {
		    fill_buffer (dip, dip->di_data_buffer, bsize, dip->di_pattern);
		}
	    }

	    /*
	     * Initialize the logical block data (if enabled).
	     */
	    if (dip->di_lbdata_flag && dip->di_lbdata_size && !dip->di_iot_pattern) {
		lba = winit_lbdata (dip, (dip->di_volume_bytes + acbp->aio_offset),
					dip->di_data_buffer, bsize, lba, dip->di_lbdata_size);
	    }

#if defined(TIMESTAMP)
            /*
             * If timestamps are enabled, initialize buffer accordingly.
             */
            if (dip->di_timestamp_flag) {
                init_timestamp(dip, dip->di_data_buffer, bsize, dip->di_lbdata_size);
            }
#endif /* defined(TIMESTAMP) */

	    if (dip->di_Debug_flag) {
		large_t iolba = NO_LBA;
                OFF_T iopos = (OFF_T) 0;
		if (dip->di_random_access || dip->di_lbdata_flag || dip->di_iot_pattern) {
                    iopos = (dip->di_volume_bytes + acbp->aio_offset);
		    iolba = make_lbdata(dip, iopos);
		}
		report_record(dip, (dip->di_files_written + 1), (dip->di_aio_record_count + 1),
			iolba, iopos, WRITE_MODE, (void *)acbp->aio_buf, acbp->aio_nbytes);
	    }
#if defined(WIN32)
	    acbp->overlap.hEvent = 0;
	    acbp->overlap.Offset = ((PLARGE_INTEGER)(&acbp->aio_offset))->LowPart;
	    acbp->overlap.OffsetHigh = ((PLARGE_INTEGER)(&acbp->aio_offset))->HighPart;
	    error = WriteFile(acbp->aio_fildes, acbp->aio_buf, acbp->aio_nbytes,
						NULL, &acbp->overlap);
	    if ((!error) && (GetLastError() != ERROR_IO_PENDING)) {
		error = FAILURE;
		acbp->aio_fildes = AIO_NotQed;
		/*
		 * Unlike POSIX AIO, WriteFile() returns ERROR_DISK_FULL
		 * when queuing the request, so handle the condition!
		 */
	    	if ( is_Eof(dip, error, &error) ) {
		    break;	/* Process outstanding requests below. */
		} else {
		    report_error (dip, "WriteFile", TRUE);
		    return (error);
		}
	    }
#else /* !defined(WIN32) */
# if defined(_AIO_AIX_SOURCE)
	    if ( (error = aio_write (acbp->aio_fildes, acbp)) == FAILURE) {
# else /* !defined(_AIO_AIX_SOURCE) */
	    if ( (error = aio_write (acbp)) == FAILURE) {
# endif /* defined(_AIO_AIX_SOURCE) */
		acbp->aio_fildes = AIO_NotQed;
		report_error (dip, "aio_write", TRUE);
		return (error);
	    }
#endif /* defined(WIN32) */
	    /*
	     * Must adjust record/data counts here to avoid writing
	     * too much data, even though the writes are incomplete.
	     */
	    dip->di_aio_data_bytes += bsize;
	    dip->di_aio_file_bytes += bsize;
	    dip->di_aio_record_count++;

	    if (dip->di_io_dir == FORWARD) {
		dip->di_aio_offset += bsize;
	    } 

	    if (dip->di_step_offset) {
		if (dip->di_io_dir == FORWARD) {
		    dip->di_aio_offset += dip->di_step_offset;
		} else if ((dip->di_aio_offset -= dip->di_step_offset) <= (OFF_T) dip->di_file_position) {
		    dip->di_aio_offset = (OFF_T) dip->di_file_position;
		}
	    }

	    /*
	     * For variable length records, adjust the next record size.
	     */
	    if (dip->di_min_size) {
		if (dip->di_variable_flag) {
		    dsize = get_variable (dip);
		} else {
		    dsize += dip->di_incr_count;
		    if (dsize > dip->di_max_size) dsize = dip->di_min_size;
		}
	    }

	    /*
	     * Always ensure the next control block has completed.
	     */
	    if (++dip->di_aio_index == dip->di_aio_bufs) dip->di_aio_index = 0;

	    /*
	     * Special handling of step option:
	     */
	    if ( (dip->di_io_dir == FORWARD)       &&
		 dip->di_step_offset && dip->di_num_slices &&
		 ((dip->di_aio_offset + (OFF_T)dsize) >= dip->di_end_position) ) {
		break;
	    } else if ( (dip->di_io_dir == REVERSE) && (dip->di_aio_offset == (OFF_T) dip->di_file_position) ) {
		break;
	    }
	    acbp = &dip->di_acbs[dip->di_aio_index];
	    if (acbp->aio_fildes == AIO_NotQed) continue; /* Never Q'ed. */

	    if ( (status = dtaio_process_write (dip, acbp)) == FAILURE) {
		return (status);
	    }
	    if (dip->di_end_of_file) break;
	}
	/*
	 * We get to this point after we've Q'ed enough requests to
	 * fulfill the requested record and/or data limit.  We now
	 * wait for these Q'ed requests to complete, adjusting the
	 * global transfer statistics appropriately which reflects
	 * the actual data processed.
	 */
	status = dtaio_wait_writes(dip);

	/*
	 * For regular files encountering premature end of file due
	 * to "file system full" (ENOSPC), then truncate the file at
	 * the last data we wish to process during the read pass.
	 */
	if ( dip->di_discarded_write_data		&&
	     (dip->di_dtype->dt_dtype == DT_REGULAR)	&&
	     (dip->di_io_dir == FORWARD)		&&
	     (dip->di_io_type == SEQUENTIAL_IO)		&&
	     (dip->di_num_slices == 0) ) {
	    (void)truncate_file(dip, dip->di_fbytes_written); 
	}
	     
	if (dip->di_end_of_file) break;
    }
   return (status);
}

/************************************************************************
 *									*
 * dtaio_process_write() - Process AIO write requests.			*
 *									*
 * Description:								*
 *	This function does waits for the requested AIO write request	*
 * and checks the completion status.					*
 *									*
 * Inputs:	dip = The device info pointer.				*
 *		acbp = The AIO control block.				*
 *									*
 * Outputs:	Returns SUCCESS/FAILURE/WARNING = Ok/Error/Partial.	*
 *									*
 ************************************************************************/
static int
dtaio_process_write (struct dinfo *dip, struct aiocb *acbp)
{
    register size_t bsize, dsize;
    register ssize_t count;
    ssize_t adjust;
    int error, status = SUCCESS;

    dip->di_retry_count = 0;
retry:
    dip->di_current_acb = acbp;
    error = dtaio_wait (dip, acbp);
#if defined(WIN32)
    /* total bytes wrote by WriteFile call or FAILURE in case of error */
    count = acbp->bytes_rw; 
    error = acbp->last_error;
#else /* !defined(WIN32) */
    count = aio_return (acbp);
#endif /* defined(WIN32) */

    errno = error;
    bsize = acbp->aio_nbytes;

    if (dip->di_history_size) {
	save_history_data(dip,
			  (dip->di_files_written + 1), (dip->di_records_written + 1),
			  WRITE_MODE, acbp->aio_offset, (u_char *)acbp->aio_buf, bsize, count);
    }

    if (dip->di_volumes_flag && (dip->di_multi_volume >= dip->di_volume_limit) &&
	      (dip->di_volume_records == dip->di_volume_records)) {
	acbp->aio_fildes = AIO_NotQed;
	return (SUCCESS);
    }
    if (count == FAILURE) {
	bool errno_flag;
#if defined(SCO) || defined(HP_UX) || defined(AIX)
	if ( (error != ENOSPC) && (error != ENXIO) && (error != EDQUOT) ) {
	    errno_flag = (bool)(error == EIO);
#elif defined(WIN32)
       	if ( (error != ERROR_DISK_FULL) &&
	     (error != ERROR_HANDLE_EOF) &&
	     (error != ERROR_SECTOR_NOT_FOUND) ) {
	    errno_flag = (bool)(error == ERROR_IO_DEVICE);
#else /* !defined(SCO) && !defined(HP_UX) && !defined(AIX) */
	if ( (error != ENOSPC) && (error != EDQUOT) ) {
	    errno_flag = (bool)(error == EIO);
#endif /* defined(SCO) || defined(HP_UX) || defined(AIX) */
	    report_error (dip, "dtaio_process_write", TRUE);
	    if ( dip->di_retry_entries && is_retryable(dip, dip->di_errno) ) {
		ReportDeviceInfo (dip, acbp->aio_nbytes, 0, FALSE);
		if ( retry_operation(dip) ) {
		    error = dtaio_restart(dip, acbp);
		    if (error) {
			acbp->aio_fildes = AIO_NotQed;
			return (error);
		    }
		    goto retry;
		}
	    } else {
		ReportDeviceInfo (dip, acbp->aio_nbytes, 0, errno_flag);
	    }
            (void)ExecuteTrigger(dip, "write");
	    acbp->aio_fildes = AIO_NotQed;
	    return (FAILURE);
	}
    } else if (error) {
	count = FAILURE;
    }

    acbp->aio_fildes = AIO_NotQed;

    /*
     * Handle ENOSPC special when writes complete out of order:
     *
     * dt: End of media detected, count = -1, errno = 28 [file #1, record #4113]
     *     < Note: Record #4114 was a full record! >
     * dt: WARNING: Record #4115, attempted to write 262144 bytes, wrote only 122880 bytes.
     * dt: End of media detected, count = -1, errno = 28 [file #1, record #4116]
     *
     * This is necessary to avoid false miscompares during the read pass!
     *
     * Note: The data is still written (of course), but we won't verify during reads.
     *       If the file is kept and used for subsequent reads, then that's a problem!
     */
    if ( dip->di_end_of_file && (count != FAILURE) &&
	 (dip->di_dtype->dt_dtype == DT_REGULAR) ) {
	if (dip->di_debug_flag) {
	    Printf("EOF set, discarding record data of %u bytes, offset " FUF "\n",
		   count, acbp->aio_offset);
	}
	dip->di_discarded_write_data += count;
	return (WARNING);
    }

    dsize = bsize;

    /*
     * Adjust for short records or no data transferred.
     */
    if (count == FAILURE) {
	dip->di_aio_data_bytes -= bsize;
	dip->di_aio_file_bytes -= bsize;
    } else if ( (adjust = (bsize - count)) ) {
	dip->di_aio_data_bytes -= adjust;
	dip->di_aio_file_bytes -= adjust;
    }

    /*
     * Note: Don't adjust these counts, if we've hit EOF already.
     */
    if ( (count > (ssize_t) 0) && (dip->di_end_of_file == FALSE) ) {
	dip->di_dbytes_written += count;
	dip->di_fbytes_written += count;
	dip->di_vbytes_written += count;
	dip->di_maxdata_written += count;
    }

    /*
     * Process end of file/media conditions and handle multi-volume.
     */
    if ( is_Eof (dip, count, &status) ) {
	if (dip->di_last_write_size == 0) {
	    dip->di_last_write_size = count;
	    dip->di_last_write_attempted = acbp->aio_nbytes;
	    dip->di_last_write_offset = acbp->aio_offset;
	}
	if (dip->di_multi_flag) {
	    status = HandleMultiVolume (dip);
	    dip->di_aio_record_count = dip->di_records_written;
	    /*dip->di_aio_file_bytes = dip->di_dbytes_written;*/
	    dip->di_aio_offset = (OFF_T) 0;
	}
	return (status);
    }

    if (count > (ssize_t) 0) {
        if ((size_t)count == dsize) {
            dip->di_full_writes++;
        } else {
            dip->di_partial_writes++;
	    /*
	     * After the first partial write to a regular file, we set a
	     * premature EOF, to discard further writes above.  This is
	     * necessary, since subsequent writes may succeed, but our
	     * read pass will try to read this entire record, and report
	     * a false data corruption (so we can't read past this point).
	     */
	    if (dip->di_dtype->dt_dtype == DT_REGULAR) {
		if (count < (ssize_t)bsize) {
		    dip->di_no_space_left = TRUE;
		    if (dip->di_last_write_size == 0) {
			dip->di_last_write_size = count;
			dip->di_last_write_attempted = acbp->aio_nbytes;
			dip->di_last_write_offset = acbp->aio_offset;
		    }
		    set_Eof(dip);
		}
	    }
        }
	dip->di_offset = (acbp->aio_offset + count);
    }
    if ((status = check_write (dip, count, bsize)) == FAILURE) {
	if (dip->di_error_count >= dip->di_error_limit) return (status);
    }

    dip->di_records_written++;
    dip->di_volume_records++;

    /*
     * Flush data *before* verify (required for buffered mode to catch ENOSPC).
     */ 
    if ( dip->di_fsync_frequency && ((dip->di_records_written % dip->di_fsync_frequency) == 0) ) {
	status = (*dip->di_funcs->tf_flush_data)(dip);
	if ( (status == FAILURE) && (dip->di_error_count >= dip->di_error_limit) ) return (status);
    }

    if ( (status != FAILURE) && dip->di_raw_flag) {
	status = write_verify(dip, (u_char *)acbp->aio_buf, count, dsize, acbp->aio_offset);
	if ( (status == FAILURE) && (dip->di_error_count >= dip->di_error_limit) ) {
	    return (status);
	}
    }

    /*
     * Special handling of step option:
     */
    if ( (dip->di_io_dir == FORWARD)       &&
	 dip->di_step_offset && dip->di_num_slices &&
	 ((acbp->aio_offset + dip->di_step_offset + (OFF_T)dsize) >= dip->di_end_position) ) {
	set_Eof(dip);
    } else if (dip->di_io_dir == REVERSE) {
	if ( (acbp->aio_offset == (OFF_T) dip->di_file_position) ||
	     (dip->di_step_offset && ((acbp->aio_offset - dip->di_step_offset) <= (OFF_T) dip->di_file_position)) ) {
	    set_Eof(dip);
	    dip->di_beginning_of_file = TRUE;
	}
    }
    return (status);
}

#endif /* defined(AIO) */
