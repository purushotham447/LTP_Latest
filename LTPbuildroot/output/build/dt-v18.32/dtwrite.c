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
 * Module:	dtwrite.c
 * Author:	Robin T. Miller
 *
 * Description:
 *	Write routines for generic data test program.
 */
#include "dt.h"
#if !defined(_QNX_SOURCE) && !defined(WIN32)
#  include <sys/file.h>
#endif /* !defined(_QNX_SOURCE) && !defined(WIN32) */

/*
 * Modification History:
 *
 * March 24th, 2013 by Robin T. Miller
 * 	Move buffer flushing to before write verify, to catch file system full conditions.
 * 	Otherwise, we may try to read/verify data never written in FS buffered mode.
 *
 * March 1st, 2013 by Robin T. Miller
 * 	On Linux, when using the step=value option, if we attempt to set a file position
 * past the disk capacity, we receive an EINVAL and was reporting this error and terminating.
 * Note: Other Unix OS's allow the file offset to be set, then fail on the next read/write,
 * with a ENOSPC or read count of zero for EOF. Yet another Linux oddity, sucks!
 * 
 * July 19th, 2012 by Robin T. Miller
 * 	Add support for retryable errors.
 *
 * October 15th, 2011 by Robin T. Miller
 * 	Optimize read-after-write pattern comparisons to avoid CPU overhead.
 *
 * October 13th, 2011 by Robin T. Miller
 * 	Modified write_verify() used when read-after-write (raw) option is
 * selected, to use common verification functions which also ties into the
 * corruption analysis. This also fixes a bug (false corruption) when AIO
 * timestamps, and random I/O are used together (timestamps overwritten).
 * 
 * November 10th, 2010 by Robin T. Miller
 *	When writing multiple files, report the file name on short writes.
 *
 * October 31st, 2010 by Robin T. Miller
 *	Add logic to fsync (flush) data with user specified frequency.
 *
 * October 6th, 2010 by Robin T. Miller
 * 	Modify init_iotdata() calls to pass in the buffer to initialize, which
 * also allows us to optimize IOT pattern generation on writes (avoid extra copy).
 *
 * January 23rd, 2010 by Robin T. Miller
 *	Add support for honoring the maxdata= option.
 *
 * December 1st, 2009 by Robin T. Miller
 *	Fix bug when detecting partial writes and setting EOF, since there
 * are two types of partial: dt idea of partial is when a full request size
 * is not written, due to the data limit.  The other more important one is
 * when the requested write size comes back as a partial, which is the key
 * when we wish to break out and stop writing on file systems, assuming a
 * "file system full" condition is forthcoming.
 *
 * November 14th, 2008 by Robin T. Miller.
 *	When using the step option in the forward direction to regular files,
 * properly stop I/O when reaching the end position (now works like reverse).
 *	Correct bug introduced when adding special handling of partial writes.
 * Logic added to write_record() set the EOF flag prematurely on partial writes,
 * which caused 1) the write verify (raw) of last record to be omitted, and
 * 2) when variable I/O was enabled the calls to get_variable() differed between
 * writes and reads now noticed with multiple files since seed isn't reinit'ed.
 * The net result of #2, was a false data corruption during the read pass, since
 * a different number of bytes were getting read *after* the first file.
 *
 * July 23rd, 2008 by Robin T. Miller.
 *	When history is enabled, call save_history_data().
 *
 * June 24th, 2008 by Robin T. Miller.
 *	Add finer grain control over timing individual operations.
 *
 * October 16th, 2006 by Robin T. Miller.
 *      Added support for recording a timestamp in each data block.
 *
 * May 16th, 2006 by Robin Miller.
 *	Added support for no I/O progress being made.
 *
 * October 21st, 2004 by Robin Miller.
 *      For variable record lengths, ensure we prime the first size
 * to ensure it meets device size alignment requirements.
 *
 * June 23rd, 2004 by Robin Miller.
 *      Added support for triggers on corruption.
 *
 * February 13th, 2004 by Robin Miller.
 *      Factor in the file position when doing reverse I/O, to avoid
 * writing into that area (which is now deemed protected).
 *
 * November 17th, 2003 by Robin Miller.
 *	Breakup output to stdout or stderr, rather than writing
 * all output to stderr.  If output file is stdout ('-') or a log
 * file is specified, then all output reverts to stderr.
 *
 * September 27th, 2003 by Robin Miller.
 *      Added support for AIX.
 *
 * June 25th, 2001 by Robin Miller.
 *	Restructured code associated with Tru64 Unix EEI, so we obtain
 * the EEI status for all tape errors, not just EIO errors.
 *
 * February 24th, 2001 by Robin Miller.
 *	Add conditionalization for QNX RTP (Neutrino).
 *
 * January 26th, 2001 by Robin Miller.
 *	Added support for reverse writing.
 *
 * January 24th, 2001 by Robin Miller.
 *	Add support for variable I/O requests sizes.
 *
 * January 14th, 2001 by Robin Miller.
 *	Added support for multiple volumes option.
 *
 * December 30th, 2000 by Robin Miller.
 *	Make changes to build using MKS/NuTCracker product.
 *
 * March 28th, 2000 by Robin Miller.
 *	Modified calls to file position functions which now accept a
 * device information parameter.
 *
 * February 18th, 2000 by Robin Miller.
 *	Fix a problem where the records written value was not updated
 * when the data limit was reached first.
 *
 * January 22nd, 2000 by Robin Miller.
 *	Added support for Cygwin tape devices for Windows/NT.
 *
 * January 6th, 2000 by Robin Miller.
 *	Added support for multi-volume media.
 *
 * January 1st, 2000 by Robin Miller.
 *	Added read after write support.
 *
 * December 30th, 1999 by Robin Miller.
 *	Modify call to do_random() to pass the transfer size.
 *	Fix lbdata problem when using step option (wrong lba).
 *
 * July 22nd, 1999 by Robin Miller.
 *	Added support for IOT (DJ's) test pattern.
 * 
 * May 27, 1999 by Robin Miller.
 *	Added support for micro-second delays.
 *
 * March 1, 1999 by Robin Miller.
 *	For tapes when Debug is enabled, report the file number.
 *
 * January 18, 1999 by Robin Miller.
 *	Modified logic in check_write() of partial record writes, so
 * these warnings can be turned off by "disable=verbose".  This change
 * is also consistent with logic done in check_read().
 *
 * December 21, 1998 by Robin Miller.
 *	Add hooks to handle tape device resets (DUNIX specific).
 *
 * October 26, 1998 by Robin Miller.
 *	When random I/O and lbdata options are both enabled, use the
 * file offset seeked to as the starting lbdata address.
 *
 * January 9, 1998 by Robin.
 *	Don't initialize data buffer being written for "disable=compare"
 * which yields better performance.
 *
 * September 6, 1996 by Robin Miller.
 *	Modified write_record() to properly check write errors!.
 *
 * February 28, 1996 by Robin Miller.
 *	Added function for copying records to device or file.
 *	Modified logic so write errors honor users' error limit.
 *
 * February 23, 1996 by Robin Miller.
 *	Only report partial record warning for sequential I/O testing.
 *	Random I/O can position us towards the end of media often, and
 *	partial transfers are likely especially with large block sizes.
 *
 * July 15, 1995 by Robin Miller.
 *	Fix end of media error handling (ENOSPC), and cleanup code.
 *
 * September 17, 1993 by Robin Miller.
 *	Report record number on warning errors (for debug).
 *
 * September 4, 1993 by Robin Miller.
 *	Moved memory mapped I/O logic to seperate module.
 *
 * Septemeber 1, 1993 by Robin Miller.
 *	Add ability to write variable record sizes.
 *
 * August 31, 1993 by Robin Miller.
 *	Rotate starting data buffer address through sizeof(long).
 *
 * August 27, 1993 by Robin MIller.
 *	Added support for DEC OSF/1 POSIX Asynchronous I/O (AIO).
 *
 * August 18, 1992 by Robin Miller.
 *	If "step=" option was specified, then seek that many bytes
 *	before the next write request (for disks).
 *
 * September 11, 1992 by Robin Miller.
 *	Ensure data limit specified by user is not exceeded, incase
 *	the block size isn't modulo the data limit.
 *
 * September 5, 1992 by Robin Miller.
 *	Initial port to QNX 4.1 Operating System.
 *
 * August 21, 1990 by Robin Miller.
 *	Changed exit status so scripts can detect and handle errors
 *	based on the exit code.  If not success, fatal error, or end
 *	of file/tape, the exit code is the error number (errno).
 *
 * August 7, 1990 by Robin Miller.
 *	If "skip=n" option is specified, then skip that many records
 *	before starting to write.  The "skip=n" option skips records
 *	by reading, while "seek=n" seeks past records (for disks).
 */

/************************************************************************
 *									*
 * write_data() - Write specified data to the output file.		*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *									*
 * Outputs:	Returns SUCCESS/FAILURE = Ok/Error.			*
 *									*
 ************************************************************************/
int
write_data (struct dinfo *dip)
{
    register ssize_t count;
    register size_t bsize, dsize;
    int status = SUCCESS;
    bool partial = FALSE;
    u_int32 lba;

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
    if (dip->di_random_access) {
	if (dip->di_io_dir == REVERSE) {
	    (void)set_position(dip, (OFF_T)dip->di_rdata_limit, FALSE);
	}
	lba = get_lba(dip);
	dip->di_offset = get_position(dip);
    } else {
	lba = make_lbdata (dip, dip->di_offset);
    }

    /*
     * Now write the specifed number of records.
     */
    while ( (dip->di_error_count < dip->di_error_limit) &&
	    (dip->di_fbytes_written < dip->di_data_limit) &&
	    (dip->di_records_written < dip->di_record_limit) ) {

	if (dip->di_terminating) break;
	//HANDLE_TERMINATE(dip);

	if ( dip->di_max_data && (dip->di_maxdata_written >= dip->di_max_data) ) {
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
	if ( (dip->di_fbytes_written + dsize) > dip->di_data_limit) {
	    bsize = (size_t)(dip->di_data_limit - dip->di_fbytes_written);
	} else {
	    bsize = dsize;
	}

	if (dip->di_io_dir == REVERSE) {
	    bsize = MIN((size_t)(dip->di_offset - dip->di_file_position), bsize);
	    dip->di_offset = set_position(dip, (OFF_T)(dip->di_offset - bsize), FALSE);
	} else if (dip->di_io_type == RANDOM_IO) {
	    dip->di_offset = do_random (dip, TRUE, bsize);
	}

        if (dip->di_debug_flag && (bsize != dsize) && !dip->di_variable_flag) {
            Printf ("Record #%lu, Writing a partial record of %lu bytes...\n",
                                    (dip->di_records_written + 1), bsize);
        }

	if (dip->di_iot_pattern || dip->di_lbdata_flag) {
	    lba = make_lbdata (dip, (OFF_T)(dip->di_volume_bytes + dip->di_offset));
	}

	/*
	 * If requested, rotate the data buffer through ROTATE_SIZE
	 * bytes to force various unaligned buffer accesses.
	 */
	if (dip->di_rotate_flag) {
	    dip->di_data_buffer = (dip->di_base_buffer + (dip->di_rotate_offset++ % ROTATE_SIZE));
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
	    lba = init_lbdata (dip, dip->di_data_buffer, bsize, lba, dip->di_lbdata_size);
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
	    if (dip->di_random_access) {
                iopos = get_position(dip);
		iolba = (iopos / dip->di_dsize);
	    } else if (dip->di_lbdata_flag || dip->di_iot_pattern) {
                iopos = (OFF_T)(dip->di_volume_bytes + dip->di_offset);
		iolba = make_lbdata (dip, iopos);
	    }
            report_record(dip, (dip->di_files_written + 1), (dip->di_records_written + 1),
				iolba, iopos, WRITE_MODE, dip->di_data_buffer, bsize);
	}

	dip->di_retry_count = 0;
	do {
	    count = write_record (dip, dip->di_data_buffer, bsize, dsize, &status);
	} while (status == RETRYABLE);

	if (dip->di_end_of_file) break;	/* Stop writing at end of file. */
	if (status == FAILURE) {
	    if (dip->di_error_count >= dip->di_error_limit) break;
	} else {
	    partial = (count < (ssize_t)bsize) ? TRUE : FALSE;
	}

	/*
	 * If we had a partial transfer, perhaps due to an error, adjust
	 * the logical block address in preparation for the next request.
	 */
	if (dip->di_iot_pattern && ((size_t)count < bsize)) {
	    size_t resid = (bsize - count);
	    lba -= howmany(resid, dip->di_lbdata_size);
	}

	dip->di_records_written++;
	dip->di_volume_records++;

	/*
	 * Flush data *before* verify (required for buffered mode to catch ENOSPC).
	 */ 
	if ( dip->di_fsync_frequency && ((dip->di_records_written % dip->di_fsync_frequency) == 0) ) {
	    status = (*dip->di_funcs->tf_flush_data)(dip);
	    if ( (status == FAILURE) && (dip->di_error_count >= dip->di_error_limit) ) break;
	}

	if ( (count > (ssize_t) 0) && dip->di_raw_flag) {
	    status = write_verify(dip, dip->di_data_buffer, count, dsize, dip->di_offset);
	    if ( (status == FAILURE) && (dip->di_error_count >= dip->di_error_limit) ) break;
	}

	/*
	 * After the first partial write to a regular file, we set a
	 * premature EOF, to avoid any further writes. This logic is
	 * necessary, since subsequent writes may succeed, but our
	 * read pass will try to read an entire record, and will report
	 * a false data corruption, depending on the data pattern and
	 * I/O type, so we cannot read past this point to be safe.
	 * Note: A subsequent write may return ENOSPC, but not always!
	 */
	if ( partial && (dip->di_dtype->dt_dtype == DT_REGULAR) ) {
	    dip->di_last_write_size = count;
	    dip->di_last_write_attempted = dsize;
	    dip->di_last_write_offset = dip->di_offset;
	    dip->di_no_space_left = TRUE;
	    set_Eof(dip);
	    break;
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

	if (dip->di_io_dir == FORWARD) {
	    dip->di_offset += count;	/* Maintain our own position too! */
	} else if ( (dip->di_io_type == SEQUENTIAL_IO) &&
		    (dip->di_offset == (OFF_T) dip->di_file_position) ) {
	    set_Eof(dip);
	    dip->di_beginning_of_file = TRUE;
	    break;
	}

	if (dip->di_step_offset) {
	    if (dip->di_io_dir == FORWARD) {
		dip->di_offset = incr_position (dip, dip->di_step_offset, TRUE);
		/* Linux returns EINVAL when seeking too far! */
		if (dip->di_offset == (OFF_T)-1) {
		    set_Eof(dip);
		    break;
		}
		if ( dip->di_num_slices &&
		     ((dip->di_offset + (OFF_T)dsize) >= dip->di_end_position) ) {
		    set_Eof(dip);
    		    break;
		}
	    } else if ((dip->di_offset -= dip->di_step_offset) <= (OFF_T) dip->di_file_position) {
		set_Eof(dip);
		dip->di_beginning_of_file = TRUE;
		break;
	    }
	}
    }
    return (status);
}

/************************************************************************
 *									*
 * check_write() - Check status of last write operation.		*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *		count = Number of bytes written.			*
 *		size  = Number of bytes expected.			*
 *									*
 * Outputs:	Returns SUCCESS/FAILURE/WARNING = Ok/Error/Warning	*
 *									*
 ************************************************************************/
int
check_write (struct dinfo *dip, ssize_t count, size_t size)
{
    int status = SUCCESS;

    if ((size_t)count != size) {
	if (count == FAILURE) {
	    bool errno_flag;
#if defined(WIN32)
	    report_error (dip, "WriteFile", TRUE);
	    errno_flag = (bool)((errno=GetLastError()) == ERROR_IO_DEVICE);
#else /* !defined(WIN32) */
	    report_error (dip, "write", TRUE);
	    errno_flag = (bool)(errno == EIO);
#endif /* defined(WIN32) */
	    if ( dip->di_retry_entries && is_retryable(dip, dip->di_errno) ) {
		ReportDeviceInfo (dip, 0, 0, FALSE);
		if ( retry_operation(dip) ) {
		    return (RETRYABLE);
		}
	    } else {
		ReportDeviceInfo (dip, 0, 0, errno_flag);
	    }
            (void)ExecuteTrigger(dip, "write");
	} else {
	    /*
	     * For writes at end of file or writes at end of block
	     * devices, we'll write less than the requested count.
	     * In this case, we'll treat this as a warning since
	     * this is to be expected.
	     *
	     * NOTE:  The raw device should be used for disks.
	     */
	    if ( (dip->di_debug_flag || dip->di_verbose_flag || ((size_t)count > size)) &&
		 (dip->di_io_mode == TEST_MODE) ) {
		if (dip->di_multiple_files) {
		    Printf(
	    "WARNING: File %s, record #%lu, attempted to write %lu bytes, wrote only %lu bytes.\n",
				dip->di_dname, (dip->di_records_written + 1), size, count);
		} else {
		    Printf(
	    "WARNING: Record #%lu, attempted to write %lu bytes, wrote only %lu bytes.\n",
					    (dip->di_records_written + 1), size, count);
		}
	    }
	    if ((size_t)count < size) {	/* Partial write is a warning. */
		dip->di_warning_errors++;
		return (WARNING);
	    }
	    ReportDeviceInfo (dip, count, 0, FALSE);
	}
	(void)RecordError(dip);
	dip->di_write_errors++;
	status = FAILURE;
    }
    return (status);
}

/************************************************************************
 *									*
 * copy_record() - Copy record to device or file.			*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *		buffer = The data buffer to write.			*
 *		bsize = The number of bytes to write.			*
 *									*
 * Outputs:	Returns SUCCESS/FAILURE/WARNING = Ok/Error/Warning	*
 *									*
 ************************************************************************/
int
copy_record (	struct dinfo	*dip,
		u_char		*buffer,
		size_t		bsize )
{
    ssize_t count;
    int status;

    dip->di_retry_count = 0;
    do {
	count = write_record (dip, buffer, bsize, bsize, &status);
    } while (status == RETRYABLE);
    /* TODO: Get this into write_record() where it belongs! */
    if (count > (ssize_t) 0) {
	dip->di_records_written++;
    }
    return (status);
}

/************************************************************************
 *									*
 * write_record() - Write record to device or file.			*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *		buffer = The data buffer to write.			*
 *		bsize = The number of bytes to write.			*
 *		dsize = The users' requested size.			*
 *		status = Pointer to status variable.			*
 *									*
 * Outputs:	status = SUCCESS/FAILURE/WARNING = Ok/Error/Warning	*
 *		Return value is number of bytes from write() request.	*
 * 		The status may also be RETRYABLE for retryable errors.	* 
 *									*
 ************************************************************************/
ssize_t
write_record(
	struct dinfo	*dip,
	u_char		*buffer,
	size_t		bsize,
	size_t		dsize,
	int		*status )
{
    ssize_t count;

retry:
    *status = SUCCESS;
    if (dip->di_noprog_flag && optiming_table[WRITE_OP].opt_timing_flag) {
	dip->di_optype = WRITE_OP;
	dip->di_initiated_time = time((time_t *)0);
    }
#if defined(WIN32)
    if (!WriteFile (dip->di_fd, buffer, bsize, &count, NULL)) { count = FAILURE; }
#else /* !defined(WIN32) */
    count = write (dip->di_fd, buffer, bsize);
#endif /* defined(WIN32) */
    if (dip->di_noprog_flag) {
	dip->di_optype = NONE_OP;
	dip->di_initiated_time = (time_t) 0;
    }

    if (dip->di_history_size) {
	save_history_data(dip,
			  (dip->di_files_written + 1), (dip->di_records_written + 1),
			  WRITE_MODE, dip->di_offset, buffer, bsize, count);
    }

    if ( is_Eof (dip, count, status) ) {
	dip->di_last_write_size = count;
	dip->di_last_write_offset = dip->di_offset;
	if (dip->di_multi_flag) {
	    *status = HandleMultiVolume (dip);
	    dip->di_offset = (OFF_T) 0;
	    if (*status == SUCCESS) goto retry;
	}
    } else {
	if (count > (ssize_t) 0) {
	    dip->di_dbytes_written += count;
	    dip->di_fbytes_written += count;
	    dip->di_vbytes_written += count;
	    dip->di_maxdata_written += count;
	    if ((size_t)count == dsize) {
		dip->di_full_writes++;
	    } else {
		dip->di_partial_writes++;
	    }
	}
	*status = check_write (dip, count, bsize);
    }
    return (count);
}

/************************************************************************
 *									*
 * write_verify() - Verify the record just written.			*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *		buffer = The data buffer written.			*
 *		bsize = The number of bytes written.			*
 *		dsize = The users' requested size.			*
 *		pos = The starting device/file position.		*
 *									*
 * Outputs:	status = SUCCESS/FAILURE/WARNING = Ok/Error/Warning	*
 *									*
 ************************************************************************/
int
write_verify(
	struct dinfo	*dip,
	u_char		*buffer,
	size_t		bsize,
	size_t		dsize,
	OFF_T		pos )
{
    u_char *vbuffer = dip->di_verify_buffer;
    ssize_t count;
    u_int32 lba = 0;
    int status = SUCCESS;

    if (dip->di_read_delay) {			/* Optional read delay.	*/
	mySleep(dip, dip->di_read_delay);
    }

    if (dip->di_dtype->dt_dtype == DT_TAPE) {
#if !defined(__NUTC__) && !defined(__QNXNTO__) && !defined(AIX) && !defined(WIN32) && defined(TAPE)
	status = DoBackwardSpaceRecord(dip, 1);
	if (status) return (status);
#endif /* !defined(__NUTC__) && !defined(__QNXNTO__) && !defined(AIX) && !defined(WIN32) && defined(TAPE) */
    } else { /* assume random access */
	OFF_T npos = set_position (dip, pos, FALSE);
	if (npos != pos) {
	    Fprintf("ERROR: Wrong seek position, (npos " FUF " != pos)" FUF "!\n",
						npos, (pos - bsize));
	    return (FAILURE);
	}
    }
    if (dip->di_iot_pattern || dip->di_lbdata_flag) {
	lba = make_lbdata(dip, (OFF_T)(dip->di_volume_bytes + pos));
    }

    if (dip->di_rotate_flag) {
	vbuffer = (dip->di_verify_buffer + ((dip->di_rotate_offset -1) % ROTATE_SIZE));
    }

    /*
     * If we'll be doing a data compare after the read, then
     * fill the verify buffer with the inverted pattern to ensure
     * the buffer actually gets written into (driver debug mostly).
     */
    if ((dip->di_io_mode == TEST_MODE) && dip->di_compare_flag) {
	if (dip->di_prefill_flag) {
	    init_buffer (dip, vbuffer, bsize, ~dip->di_pattern);
	}
	init_padbytes (vbuffer, bsize, ~dip->di_pattern);
#if 0
	/* 
	 * We don't need to initialize this buffer, since we're using the
	 * read and  write buffers below to verify the data pattern.
	 * 
	 * Note: When doing large transfers (1m), this saves CPU time!
	 */
	if (dip->di_iot_pattern) {
	    lba = init_iotdata (dip, dip->di_pattern_buffer, bsize, lba, dip->di_lbdata_size);
	}
#endif	
    }

    if (dip->di_Debug_flag) {
	large_t iolba = NO_LBA;
        OFF_T iopos = (OFF_T) 0;
	if (dip->di_random_access) {
            iopos = get_position(dip);
	    iolba = (iopos / dip->di_dsize);
	} else if (dip->di_lbdata_flag || dip->di_iot_pattern) {
            iopos = (OFF_T)(dip->di_volume_bytes + pos);
	    iolba = make_lbdata (dip, iopos);
	}
	report_record(dip, (dip->di_files_read + 1), (dip->di_records_read + 1),
			iolba, iopos, READ_MODE, vbuffer, bsize);
    }

    dip->di_retry_count = 0;
    do {
	count = read_record (dip, vbuffer, bsize, dsize, &status);
    } while (status == RETRYABLE);
    if (dip->di_end_of_file) {
#if defined(WIN32)
	report_error (dip, "ReadFile", TRUE);
#else /* !defined(WIN32) */
	report_error (dip, "read", TRUE);
#endif /* defined(WIN32) */
	ReportDeviceInfo (dip, 0, 0, FALSE);
	(void)RecordError(dip);
	if (dip->di_dtype->dt_dtype != DT_TAPE) {
	    (void) set_position (dip, pos, FALSE);
	}
	return (FAILURE);
    }

    /*
     * Verify the data (unless disabled).
     */
    if ( (status != FAILURE) && dip->di_compare_flag && (dip->di_io_mode == TEST_MODE) ) {
	register ssize_t vsize = count;

	/*
	 * Normally the buffers are exact, but with random I/O and timestamps
	 * enabled, overwrites will (occasionally) cause miscompares with AIO.
	 * 
	 * Note: This only works for IOT or patterns without a prefix string.
	 */
        if (memcmp(buffer, vbuffer, vsize) != 0) { /* optimization! */
	    if (dip->di_iot_pattern || !dip->di_prefix_string) {
		u_char *pptr = dip->di_pattern_bufptr;
		u_char *pend = dip->di_pattern_bufend;
		u_char *pbase = dip->di_pattern_buffer;
		size_t psize = dip->di_patbuf_size;
		/*
		 * Note: This Mickey Mouse setup is required so we can use the existing
		 * verification functions which handle timestamps, corruption analysis,
		 * and retry logic employed in the standard read/verify data paths.
		 */
		dip->di_pattern_buffer = dip->di_pattern_bufptr = buffer;
		dip->di_pattern_bufend = (buffer + vsize);
		dip->di_patbuf_size = vsize;
		status = (*dip->di_funcs->tf_verify_data)(dip, vbuffer, vsize, dip->di_pattern, &lba);
		dip->di_pattern_bufptr = pptr;
		dip->di_pattern_bufend = pend;
		dip->di_pattern_buffer = pbase;
		dip->di_patbuf_size = psize;
	    } else {
		/* 
		 * Note: This method fails w/AIO and overwriting timestamps! 
		 */
		if (dip->di_lbdata_flag) {
		    status = verify_lbdata(dip, buffer, vbuffer, vsize, &lba);
		}
		if (status == SUCCESS) {
		    status = verify_buffers(dip, buffer, vbuffer, vsize);
		}
		if ( (status != SUCCESS)   && dip->di_retryDC_flag &&
		     dip->di_random_access && !dip->di_retrying) {
		    (void)verify_reread(dip, vbuffer, vsize, dip->di_pattern, &lba);
		}
	    }
	}
	/*
	 * Verify the pad bytes (if enabled).
	 */
	if ( (status == SUCCESS) && dip->di_pad_check) {
	    (void) verify_padbytes (dip, vbuffer, vsize, ~dip->di_pattern, bsize);
	}
    }

    /*
     * We expect to read as much as we wrote, or else we've got a problem!
     */
    if ((size_t)count < bsize) {
	/* check_read() reports info regarding the short record read. */
	ReportDeviceInfo (dip, count, 0, FALSE);
	(void)RecordError(dip);
	status = FAILURE;
	if (dip->di_dtype->dt_dtype != DT_TAPE) {
	    (void) set_position (dip, pos, FALSE);
	}
    }
    dip->di_records_read++;
    return (status);
}
