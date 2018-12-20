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
 * Module:	dtread.c
 * Author:	Robin T. Miller
 *
 * Description:
 *	Read routines for generic data test program.
 */
#include "dt.h"
#if !defined(_QNX_SOURCE) && !defined(WIN32)
#  include <sys/file.h>
#endif /* !defined(_QNX_SOURCE) && !defined(WIN32) */
#include <sys/stat.h>

/*
 * Modification History:
 *
 * March 1st, 2013 by Robin T. Miller
 * 	On Linux, when using the step=value option, if we attempt to set a file position
 * past the disk capacity, we receive an EINVAL and was reporting this error and terminating.
 * Note: Other Unix OS's allow the file offset to be set, then fail on the next read/write,
 * with a ENOSPC or read count of zero for EOF. Yet another Linux oddity, sucks!
 * 
 * January 3rd, 2013 by Robin T. Miller
 * 	Updated FindCapacity() (again), to avoid overwriting the user specified data
 * limit. Previously, the max capacity got set basically ignoring the users' limit.
 * Note: This issue existed since the non-threaded dt used two variables for data limit,
 * 1) for the data limit set by capacity, and 2) one used for limit data in I/O loops.
 * FWIW: This function needs a rewrite, evidenced by too many updates and resulting bugs!
 * 
 * October 15th, 2012 by Robin T. Miller
 *	Fix (newly introduced 18.xx) bug in FindCapacity(), where the random data
 * limit was being set to the calculated data limit, rather than the whole capacity.
 * This occurred using a record count without a data limit, but the random IO range
 * should be the capacity, *not* this smaller data limit limiting random IO offsets.
 * Note: This bug was never reported and never released, I found it in dt.staging!
 *
 * July 19th, 2012 by Robin T. Miller
 * 	Add support for retryable errors.
 *
 * June 13th, 2011 by Robin T. Miller
 * 	Updated FindCapacity() to include ERROR_IO_DEVICE as a valid read error,
 * to continue algorithm to determine the capacity via seek/read logic. This is
 * seen on my internal C: disk, but not other iSCSI SAN attached disks.
 * Note: dtinfo has been updated to use Windows Device controls to obtain the
 * sector size and capacity, so this logic shouldn't get used unless capacity=max
 * to force this code path (overrides OS capacity, when it's deemed incorrect).
 * 
 * March 14th, 2011 by Robin T. Miller
 * 	Make FindCapacity() more resilient, by handling seek errors in addition
 * to its' read logic. For example, a 32m LUN on Linux returns EINVAL when trying
 * to seek to offset 250m (sigh), and the original seek API's would terminate.
 * 
 * February 3rd, 2011 by Robin T. Miller
 *	Don't save the read history, if we're retrying a read after miscompare.
 *
 * November 15th, 2010 by Robin T. Miller
 *	When doing random I/O reads of a short record, due to a short write
 * (likely due to ENOSPC), ensure the transfer size used to generate the random
 * offset matches what was used during the write, or an incorrect offset may be
 * generated which results in a false data corruption.
 *
 * November 10th, 2010 by Robin T. Miller
 *	When writing multiple files, report the file name on short reads.
 *
 * October 6th, 2010 by Robin T. Miller
 * 	Modify init_iotdata() calls to pass in the buffer to initialize.
 *
 * January 23rd, 2010 by Robin T. Miller
 *	Add support for honoring the maxdata= option.
 *
 * February 2nd, 2009 by Robin T. Miller.
 *	Add checks to ensure we do not read more than we wrote in write pass.
 * This sanity check is done for regular files to handle "file system full".
 * Without this check, we'll read more than we wrote, and report a false data
 * corruption (very bad and misleads testers).
 *
 * November 14th, 2008 by Robin T. Miller.
 *	When using the step option in the forward direction to regular files,
 * properly stop I/O when reaching the end position (now works like reverse).
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
 * October 30th, 2007 by Robin T. Miller.
 *	On Windows, if handle opened with overlapped I/O (via aio), then
 * ensure FindCapacity() opens another handle for its' seek/reads!
 *
 * October 29th, 2007 by Robin T. Miller.
 *	Remove crufty old MS Visual C++ 6.0, Visual C++ 2005 is much better!
 *
 * October 27th, 2007 by Robin T. Miller.
 *	Add check for ERROR_SECTOR_NOT_FOUND when calculating the capacity
 * on native Windows.  This seems like a strange error to me, correct?
 *
 * October 24th, 2007 by Robin T. Miller.
 *	For Windows Cygwin emulation, expect EINVAL for reads past EOM.
 *
 * October 16th, 2006 by Robin T. Miller.
 *      Added support for recording a timestamp in each data block.
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
 * reading into that area (which is now deemed protected).
 *
 * November 17th, 2003 by Robin Miller.
 *	Breakup output to stdout or stderr, rather than writing
 * all output to stderr.  If output file is stdout ('-') or a log
 * file is specified, then all output reverts to stderr.
 *
 * October 8th, 2003 by Robin Miller.
 *	On AIX, accept ENXIO for I/O's pass EOF.
 *
 * March 4th, 2003 by Robin Miller.
 *      Add EOF support for older SunOS release.  This means reads
 * past EOF return EIO, but continue on this to find real capacity.
 *
 * November 20th, 2002 by Robin Miller.
 *	Updated FindCapacity() to expect ENXIO for reads past EOM.
 *
 * June 25th, 2001 by Robin Miller.
 *	Restructured code associated with Tru64 Unix EEI, so we obtain
 * the EEI status for all tape errors, not just EIO errors.
 *
 * January 28th, 2001 by Robin Miller.
 *	Allow FindCapacity() to be called prior to the file being opened
 * The device capacity is necessary early on for the new slices option.
 *
 * January 26th, 2001 by Robin Miller.
 *	Added support for reverse reading.
 *
 * January 24th, 2001 by Robin Miller.
 *	Add support for variable I/O requests sizes.
 *
 * January 14th, 2001 by Robin Miller.
 *	Added support for multiple volumes option.
 *
 * January 2nd, 2001 by Robin Miller.
 *	Remove check for block or character device in FindCapacity(), since
 * that check is already done in mainline code, so it's a duplicate check.
 *
 * December 30th, 2000 by Robin Miller.
 *	Make changes to build using MKS/NuTCracker product.
 *
 * October 2nd, 2000 by Robin Miller.
 *	Update FindCapacity() to accept ENXIO for reads at EOM on
 * SCO UnixWare systems.
 *
 * April 2nd, 2000 by Robin Miller.
 *	Updated FindCapacity(): printf -> Fprintf so messages go to
 * log file, and add/change casts on large_t values (nothing big :-).
 *
 * March 28th, 2000 by Robin Miller.
 *	Modified calls to file position functions which now accept a
 * device information parameter.
 *
 * March 27th, 2000 by Robin Miller.
 *	Modified FindCapacity() to continue on read() errors, to handle
 * broken Linux ATAPI (IDE) driver, which returns EIO on errors past the
 * end of media (damn!).
 *
 * February 18th, 2000 by Robin Miller.
 *	Fix a problem where the records read value was not updated
 * when the data limit was reached first.
 *
 * February 17th, 2000 by Robin Miller.
 *	Adding better support for multi-volume tape testing.  Mainly,
 * make it work with writing multiple tape files, rather than one file.
 *
 * January 17th, 2000 by Robin Miller.
 *	Added checks @ EOF with/multi-volume enabled, so Copy/Verify
 * operations properly prompt for the next volume.  This allows 'dt'
 * to be used as a general purpose multi-volume tool w/other utilities.
 *
 * January 6th, 2000 by Robin Miller.
 *	Added support for multi-volume media.
 *
 * December 30th, 1999 by Robin Miller.
 *	Modify call to do_random() to pass the transfer size.
 *	Fix lbdata problem when using step option (wrong lba).
 *
 * August 6th, 1999 by Robin Miller.
 *      Better parameterizing of "long long" printf formatting.
 *
 * July 22nd, 1999 by Robin Miller.
 *	Added support for IOT (DJ's) test pattern.
 * 
 * May 27, 1999 by Robin Miller.
 *	Adding support for micro-second delays.
 *
 * March 1, 1999 by Robin Miller.
 *	For tapes when Debug is enabled, report the file number.
 *
 * December 21, 1998 by Robin Miller.
 *	Add hooks to handle tape device resets (DUNIX specific).
 *
 * October 29, 1998 by Robin Miller.
 *	Implement a random I/O data limit, instead of using the normal
 * data limit variable (not good to dual purpose this value).
 *
 * October 26, 1998 by Robin Miller.
 *	When random I/O and lbdata options are both enabled, use the
 * file offset seeked to as the starting lbdata address.
 *
 * April 28, 1998 by Robin Miller.
 *	For WIN32/NT, or in O_BINARY into open flags to force binary
 *	mode (the default is text mode).
 *
 * February 29, 1996 by Robin Miller.
 *	Added FindCapacity() function to obtain capacity for random
 *	access devices.  Must set limits for random I/O.
 *
 * February 28, 1996 by Robin Miller.
 *	Added support for copying and verifying device/files.
 *	Modified logic so read errors honor users' error limit.
 *
 * February 23, 1996 by Robin Miller.
 *	Only report partial record warning for sequential I/O testing.
 *	Random I/O can position us towards the end of media often, and
 *	partial transfers are likely especially with large block sizes.
 *
 * November 11, 1995 by Robin Miller.
 *	Fix bug with init'ing and performing pad byte verification.
 *	This caused variable length reads with small increment values
 *	to report an (invalid) pad byte data compare error. e.g.:
 *
 *	% dt of=/dev/rmt0h min=10k max=64k incr=1 pattern=incr
 *
 * July 15, 1995 by Robin Miller.
 *	Fix end of media error handling (ENOSPC), and cleanup code.
 *
 * January 20, 1994 by Robin Miller.
 *	When initializing the data buffer, don't do the entire buffer since
 * init'ing large buffer (e.g. 100m) using min, max, and incr options cause
 * excessive paging and VERY poor performance.
 *
 * September 17, 1993 by Robin Miller.
 *	Report record number on warning errors (for debug).
 *
 * September 4, 1993 by Robin Miller.
 *	Moved memory mapped I/O logic to seperate module.
 *
 * Septemeber 1, 1993 by Robin Miller.
 *	Add ability to read variable record sizes.
 *
 * August 31, 1993 by Robin Miller.
 *	Rotate starting data buffer address through sizeof(long).
 *
 * August 27, 1993 by Robin MIller.
 *	Added support for DEC OSF/1 POSIX Asynchronous I/O (AIO).
 *
 * August 18, 1992 by Robin Miller.
 *	If "step=" option was specified, then seek that many bytes
 *	before the next read request (for disks).
 *
 * August 10, 1993 by Robin Miller.
 *	Added initializing and checking of buffer pad bytes to ensure
 *	data corruption does *not* occur at the end of read buffers.
 *
 * August 5, 1993 by Robin Miller.
 *	Added support for reading multiple tape files.
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
 *	If "seek=n" option is specified, then seek that many records
 *	before starting to read.  The "skip=n" option skips records
 *	by reading, while "seek=n" seeks past records.
 */

void
check_last_write_info(dinfo_t *dip, OFF_T offset, size_t bsize, size_t dsize)
{
    /*
     * SANITY CHECK: Make sure the read offset matches the last write offset.
     *		     Would rather die now, than report a false data corruption!
     */
    if ( (dip->di_last_write_offset != offset) ||
	 ((ssize_t)dip->di_last_write_size > 0) && (dip->di_last_write_size != bsize) ) {
	Fprintf("Programming ERROR: Incorrect random I/O offset or size for last write!\n");
	Fprintf("Expected offset/attempted/actual: " FUF "/%d/%d\n",
		dip->di_last_write_offset, (int)dip->di_last_write_attempted,
		(int)dip->di_last_write_size);
	Fprintf("Current offset/attempting/actual: " FUF "/%d/%d\n",
		offset, (int)dsize, (int)bsize);
	if (dip->di_history_size) {
	    dump_history_data(dip);
	}
	terminate(exit_status = FAILURE);
    }
    return;
}
/************************************************************************
 *									*
 * read_data() - Read and optionally verify data read.			*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *									*
 * Outputs:	Returns SUCCESS/FAILURE = Ok/Error.			*
 *									*
 ************************************************************************/
int
read_data (struct dinfo *dip)
{
    register ssize_t count;
    register size_t bsize, dsize;
    int status = SUCCESS;
    struct dtfuncs *dtf = dip->di_funcs;
    bool check_rwbytes = FALSE;
    bool check_write_limit = FALSE;
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
     * Now read and optionally verify the input records.
     */
    while ( (dip->di_error_count < dip->di_error_limit) &&
	    (dip->di_fbytes_read < dip->di_data_limit) &&
	    (dip->di_records_read < dip->di_record_limit) ) {

	if (dip->di_terminating) break;
	//HANDLE_TERMINATE(dip);

	if ( dip->di_max_data && (dip->di_maxdata_read >= dip->di_max_data) ) {
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
	if ( (dip->di_fbytes_read + dsize) > dip->di_data_limit) {
	    bsize = (size_t)(dip->di_data_limit - dip->di_fbytes_read);
	} else {
	    bsize = dsize;
	}


	if (dip->di_io_dir == REVERSE) {
	    bsize = MIN((size_t)(dip->di_offset - dip->di_file_position), bsize);
	    dip->di_offset = set_position(dip, (OFF_T)(dip->di_offset - bsize), FALSE);
	} else if (dip->di_io_type == RANDOM_IO) {
	    /*
	     * BEWARE: The size *must* match the write size, or you'll get
	     * a different offset, since the size is used in calculations.
	     */
	    dip->di_offset = do_random (dip, TRUE, bsize);
	}

	/*
	 * If we wrote data, ensure we don't read more than we wrote.
	 */
	if (check_write_limit) {
	    if ( (dip->di_fbytes_read + bsize) > dip->di_last_fbytes_written) {
		dsize = bsize;	/* Save the original intended size. */
		bsize = (size_t)(dip->di_last_fbytes_written - dip->di_fbytes_read);
		check_rwbytes = TRUE;
		if (bsize == (size_t) 0) {
		    set_Eof(dip);
		    break;
		}
		check_last_write_info(dip, dip->di_offset, bsize, dsize);
	    }
	}

        if (dip->di_debug_flag && (bsize != dsize) && !dip->di_variable_flag) {
            Printf ("Record #%lu, Reading a partial record of %lu bytes...\n",
                                    (dip->di_records_read + 1), bsize);
        }

	if (dip->di_iot_pattern || dip->di_lbdata_flag) {
	    lba = make_lbdata (dip, (OFF_T)(dip->di_volume_bytes + dip->di_offset));
	}

	/*
	 * If requested, rotate the data buffer through ROTATE_SIZE bytes
	 * to force various unaligned buffer accesses.
	 */
	if (dip->di_rotate_flag) {
	    dip->di_data_buffer = (dip->di_base_buffer + (dip->di_rotate_offset++ % ROTATE_SIZE));
	}

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
	    if (dip->di_iot_pattern) {
		lba = init_iotdata (dip, dip->di_pattern_buffer, bsize, lba, dip->di_lbdata_size);
	    }
	}

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
	    report_record(dip, (dip->di_files_read + 1), (dip->di_records_read + 1),
				iolba, iopos, READ_MODE, dip->di_data_buffer, bsize);
	}

	dip->di_retry_count = 0;
	do {
	    count = read_record (dip, dip->di_data_buffer, bsize, dsize, &status);
	} while (status == RETRYABLE);
	if (dip->di_end_of_file) break;		/* Stop reading at end of file. */

	if (status == FAILURE) {
	    if (dip->di_error_count >= dip->di_error_limit) break;
	} else if (dip->di_io_mode == COPY_MODE) {
	    status = copy_record (dip->di_output_dinfo, dip->di_data_buffer, count);
            dip->di_error_count = dip->di_output_dinfo->di_error_count;	/* HACK! */
	    if ( (dip->di_error_count >= dip->di_error_limit) || dip->di_end_of_file) break;
	} else if (dip->di_io_mode == VERIFY_MODE) {
	    status = verify_record (dip->di_output_dinfo, dip->di_data_buffer, count);
	    /* TODO: Need to cleanup multiple device support! */
	    /* For now, propagate certain information to reader. */
	    if (dip->di_output_dinfo->di_error_count) {
		dip->di_error_count = dip->di_output_dinfo->di_error_count;	/* HACK! */
	    }
	    if (dip->di_output_dinfo->di_end_of_file) {
		dip->di_end_of_file = dip->di_output_dinfo->di_end_of_file;	/* HACK! */
	    }
	    if ( (dip->di_error_count >= dip->di_error_limit) || dip->di_end_of_file) break;
	}

	/*
	 * Verify the data (unless disabled).
	 */
	if ( (status != FAILURE) && dip->di_compare_flag && (dip->di_io_mode == TEST_MODE) ) {
	    ssize_t vsize = count;
	    status = (*dtf->tf_verify_data)(dip, dip->di_data_buffer, vsize, dip->di_pattern, &lba);
	    /*
	     * Verify the pad bytes (if enabled).
	     */
	    if ( (status == SUCCESS) && dip->di_pad_check) {
		(void) verify_padbytes (dip, dip->di_data_buffer, vsize, ~dip->di_pattern, bsize);
	    }
	}

	/*
	 * If we had a partial transfer, perhaps due to an error, adjust
	 * the logical block address in preparation for the next request.
	 */
	if (dip->di_iot_pattern && ((size_t)count < bsize)) {
	    size_t resid = (bsize - count);
	    lba -= howmany(resid, dip->di_lbdata_size);
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

	dip->di_records_read++;
	dip->di_volume_records++;

	if (dip->di_io_dir == FORWARD) {
	    dip->di_offset += count;	/* Maintain our own position too! */
	} else if ( (dip->di_io_type == SEQUENTIAL_IO) &&
		    (dip->di_offset == (OFF_T) dip->di_file_position) ) {
	    set_Eof(dip);
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
		break;
	    }
	}

	/*
	 * For regular files, if we've read as much as we've written,
	 * then set a fake EOF to stop this read pass.
	 */
	if ( check_rwbytes &&
	     (dip->di_fbytes_read == dip->di_last_fbytes_written) ) {
	    set_Eof(dip);
	    break;
	}
    }
    return (status);
}

/************************************************************************
 *									*
 * check_read() - Check status of last read operation.			*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *		count = Number of bytes read.				*
 *		size  = Number of bytes expected.			*
 *									*
 * Outputs:	Returns SUCCESS/FAILURE/WARNING = Ok/Error/Warning	*
 *									*
 ************************************************************************/
int
check_read (struct dinfo *dip, ssize_t count, size_t size)
{
    int status = SUCCESS;

    if ((size_t)count != size) {
	if (count == FAILURE) {
	    bool errno_flag;
#if defined(WIN32)
	    report_error (dip, "ReadFile", TRUE);
	    errno_flag = (bool)((errno=GetLastError()) == ERROR_IO_DEVICE);
#else /* !defined(WIN32) */
	    report_error (dip, "read", TRUE);
	    errno_flag = (bool)(errno == EIO);
#endif /* defined(WIN32) */
	    if ( dip->di_retry_entries && is_retryable(dip, dip->di_errno) ) {
		ReportDeviceInfo (dip, 0, 0, FALSE);
		if ( retry_operation(dip) ) {
		    return (RETRYABLE);
		}
	    } else {
		ReportDeviceInfo (dip, 0, 0, errno_flag);
		if (!dip->di_retrying) {
		    (void)ExecuteTrigger(dip, "read");
		}
	    }
	} else {
	    /*
	     * For reads at end of file or reads at end of block
	     * devices, we'll read less than the requested count.
	     * In this case, we'll treat this as a warning since
	     * this is to be expected.  In the case of tape, the
	     * next read will indicate end of tape (in my driver).
	     *
	     * NOTE:  The raw device should be used for disks.
	     */
	    if ( (dip->di_debug_flag || dip->di_verbose_flag || ((size_t)count > size)) &&
		 (dip->di_io_mode == TEST_MODE) ) {
		if (dip->di_multiple_files) {
		    Printf(
	    "WARNING: File %s, record #%lu, attempted to read %lu bytes, read only %lu bytes.\n",
				dip->di_dname, (dip->di_records_read + 1), size, count);
		} else {
		    Printf(
	    "WARNING: Record #%lu, attempted to read %lu bytes, read only %lu bytes.\n",
						    (dip->di_records_read + 1), size, count);
		}
	    }
	    if ((size_t)count < size) {	/* Partial read is a warning. */
		dip->di_warning_errors++;
		return (WARNING);
	    }
	    ReportDeviceInfo (dip, count, 0, FALSE);
	}
	(void)RecordError(dip);
	dip->di_read_errors++;
	status = FAILURE;
    }
    return (status);
}

/*
 * This function is envoked when reading multiple tape files, to
 * position past an expected file mark.  This is especially important
 * when using the lbdata or iot options, since encountering an expected
 * EOF throws off the offset being maintained, resulting in an lba error.
 */
int
read_eof(struct dinfo *dip)
{
    ssize_t count;
    size_t bsize = dip->di_block_size;
    int status = SUCCESS;

    if (dip->di_debug_flag) {
	Printf("Processing end of file... [file #%lu, record #%lu]\n",
			(dip->di_files_read + 1), (dip->di_records_read + 1));
    }
    dip->di_eof_processing = TRUE;
    dip->di_retry_count = 0;
    do {
	count = read_record (dip, dip->di_data_buffer, bsize, bsize, &status);
    } while (status == RETRYABLE);
    dip->di_eof_processing = FALSE;
    if (!dip->di_end_of_file) {
	Fprintf("ERROR: File %lu, Record %lu, expected EOF was NOT detected!\n",
		(dip->di_files_read + 1), (dip->di_records_read + 1));
	ReportDeviceInfo (dip, count, 0, FALSE);
	(void)RecordError(dip);
	dip->di_read_errors++;
	status = FAILURE;
    }
    return (status);
}

/*
 * This function is called after EOF is detected, to read the next record
 * which checks for reaching the end of logical tape (i.e. two successive
 * file marks).  For multi-volume tapes, the user will be prompted for the
 * next volume via read_record(), and the end of file flag gets reset when
 * the tape is re-open'ed.
 */
int
read_eom(struct dinfo *dip)
{
    ssize_t count;
    size_t bsize = dip->di_block_size;
    int status = SUCCESS;

    if (dip->di_debug_flag) {
	Printf("Processing end of media... [file #%lu, record #%lu]\n",
			(dip->di_files_read + 1), (dip->di_records_read + 1));
    }
    dip->di_eom_processing = TRUE;
    do {
	count = read_record (dip, dip->di_data_buffer, bsize, bsize, &status);
    } while (status == RETRYABLE);
    dip->di_eom_processing = FALSE;

    if (dip->di_multi_flag) {
	if (dip->di_end_of_file) {
	    Fprintf("ERROR: File %lu, Record %lu, expected EOM was NOT detected!\n",
			(dip->di_files_read + 1), (dip->di_records_read + 1));
	    ReportDeviceInfo (dip, count, 0, FALSE);
	    (void)RecordError(dip);
	    return (FAILURE);
	}
    } else if ( !dip->di_end_of_logical ) {
	Fprintf("ERROR: File %lu, Record %lu, expected EOM was NOT detected!\n",
		(dip->di_files_read + 1), (dip->di_records_read + 1));
	ReportDeviceInfo (dip, count, 0, FALSE);
	(void)RecordError(dip);
	dip->di_read_errors++;
	return (FAILURE);
    }
    return (SUCCESS);	/* We don't care about the read status! */
}

/************************************************************************
 *									*
 * read_record() - Read record from device or file.			*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *		buffer = The data buffer to read into.			*
 *		bsize = The number of bytes read.			*
 *		dsize = The users' requested size.			*
 *		status = Pointer to status variable.			*
 *									*
 * Outputs:	status = SUCCESS/FAILURE/WARNING = Ok/Error/Warning	*
 *		Return value is number of bytes from read() request.	*
 * 		The status may also be RETRYABLE for retryable errors.	* 
 *									*
 ************************************************************************/
ssize_t
read_record (	struct dinfo	*dip,
		u_char		*buffer,
		size_t		bsize,
		size_t		dsize,
		int		*status )
{
    ssize_t count;

retry:
    *status = SUCCESS;
    if (dip->di_noprog_flag && optiming_table[READ_OP].opt_timing_flag) {
	dip->di_optype = READ_OP;
	dip->di_initiated_time = time((time_t *)0);
    }
#if defined(WIN32)
   if (!ReadFile (dip->di_fd, buffer, bsize, &count, NULL)) { count = FAILURE; }
#else /* !defined(WIN32) */
    count = read (dip->di_fd, buffer, bsize);
#endif /* defined(WIN32) */
    if (dip->di_noprog_flag) {
	dip->di_optype = NONE_OP;
	dip->di_initiated_time = (time_t) 0;
    }
    if (dip->di_history_size && !dip->di_retrying) {
	save_history_data(dip,
			  (dip->di_files_read + 1), (dip->di_records_read + 1),
			  READ_MODE, dip->di_offset, buffer, bsize, count);
    }

    if ( is_Eof (dip, count, status) ) {
	if (dip->di_multi_flag &&
	    (!dip->di_stdin_flag || (dip->di_ftype == OUTPUT_FILE)) ) {
	    if ( (dip->di_dtype->dt_dtype == DT_TAPE) &&
		 !dip->di_end_of_logical ) {
		return (count);	/* Expect two file marks @ EOM. */
	    }
	    *status = HandleMultiVolume (dip);
	    dip->di_offset = (OFF_T) 0;
	    if ( !dip->di_eof_processing && !dip->di_eom_processing ) {
		if (*status == SUCCESS) goto retry;
	    }
	}
	return (count);	/* Stop reading at end of file. */
    }

    if ( dip->di_eof_processing || dip->di_eom_processing ) {
	return (count);
    }
    dip->di_end_of_file = FALSE;	/* Reset saved end of file state. */

    /*
     * If something was read, adjust counts and statistics.
     */
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
    }

    *status = check_read (dip, count, bsize);

    return (count);
}

/************************************************************************
 *									*
 * verify_record() - Verify record with selected output device/file.	*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *		buffer = The data buffer to compare.			*
 *		bsize = The number of bytes read.			*
 *									*
 * Outputs:	Returns SUCCESS/FAILURE/WARNING = Ok/Error/Warning	*
 *									*
 ************************************************************************/
int
verify_record (	struct dinfo	*dip,
		u_char		*buffer,
		size_t		bsize )
{
    struct dtfuncs *dtf = dip->di_funcs;
    ssize_t count;
    int status;
    u_int32 lba = dip->di_lbdata_addr;

    /*
     * TODO: Re-write this using the verify buffer (when I have time).
     */
    dip->di_retry_count = 0;
    do {
	count = read_record (dip, dip->di_pattern_buffer, bsize, bsize, &status);
    } while (status == RETRYABLE);
    if ( (status == FAILURE) || dip->di_end_of_file) return (status);

    /*
     * I realize this is real ugly, but I wanted to use existing code.
     */
    dip->di_patbuf_size = count;
    dip->di_pattern_bufptr = dip->di_pattern_buffer;
    dip->di_pattern_bufend = dip->di_pattern_buffer + count;

    status = (*dtf->tf_verify_data)(dip, buffer, count, dip->di_pattern, &lba);
    /* TODO: Get this into read_record() where it belongs! */
    dip->di_records_read++;
    return (status);
}

/************************************************************************
 *									*
 * FindCapacity() - Find capacity of a random access device.	        * 
 * 								        * 
 * Description:							        * 
 * 	This function is called anytime the disk capacity is required,	*
 * which includes random I/O and multiple slices. If a capacity exists	*
 * from user defined or OS obtained, use this value, otherwise use a	*
 * series of seek/reads to find the disk capacity.			*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *									*
 * Outputs:	Fills in device capacity and data limit on success.	*
 *									*
 * Return Value: Returns SUCCESS/FAILURE/WARNING = Ok/Error/Warning	*
 *									*
 ************************************************************************/
int
FindCapacity (struct dinfo *dip)
{
    register u_int32 dsize = dip->di_rdsize;
    OFF_T	lba, max_seek = (MAX_SEEK - dsize), offset;
    long	adjust = ((250 * MBYTE_SIZE) / dsize);
    int		attempts = 0;
    ssize_t	count, last = 0;
    u_char	*buffer;
    HANDLE	fd, saved_fd = NoFd;
    int		status = SUCCESS;
    bool	temp_fd = FALSE;

#if defined(DEBUG)
    Printf("FindCapacity: rdsize = %u\n", dip->di_rdsize);
    Printf("FindCapacity: data_limit = " LUF "\n", dip->di_data_limit);
    Printf("FindCapacity: rdata_limit = " LUF "\n", dip->di_rdata_limit);
    Printf("FindCapacity: user_capacity = " LUF "\n", dip->di_user_capacity);
    Printf("FindCapacity: num_slices = %u, slice_num = %d\n",  dip->di_num_slices,  dip->di_slice_num);
#endif    
    /*
     * Use the user specified capacity (if specified).
     * 
     * Note: The user_capacity will be set from the OS specific API's for disks,
     * or with the current file size (if it already exists) for regular files.
     */
    if (dip->di_user_capacity) {
	lba = (OFF_T)(dip->di_user_capacity / dsize);
	goto set_capacity;
    } else if (dip->di_data_limit && (dip->di_data_limit != INFINITY) ) {
	goto set_random_limit;
    }

    if (dip->di_debug_flag || dip->di_Debug_flag || dip->di_rDebugFlag) {
	Printf ("Attempting to calculate capacity via seek/read algorithm...\n");
    }
    /*
     * If the device is open in write mode, open another file descriptor for reading.
     *
     * TODO: We should have OS specific open functions. (clean this mess up!)
     */
#if defined(WIN32)
    if ( dip->di_aio_flag || (dip->di_fd == NoFd) || (dip->di_mode == WRITE_MODE) ) {
#else /* !defined(WIN32) */
    if ( (dip->di_fd == NoFd) || (dip->di_mode == WRITE_MODE) ) {
#endif /* defined(WIN32) */
	temp_fd = TRUE;
	saved_fd = dip->di_fd;
#if defined(WIN32)
	if ( (fd = CreateFile (dip->di_dname, GENERIC_READ,
			       (FILE_SHARE_READ | FILE_SHARE_WRITE), NULL,
			       OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == NoFd) {
#elif defined(__WIN32__)
	if ( (fd = open (dip->di_dname, (O_RDONLY|O_BINARY))) < 0) {
#else /* !defined(__WIN32__) */
	if ( (fd = open (dip->di_dname, O_RDONLY)) < 0) {
#endif /* defined(__WIN32__) */
	    Fprintf("Failed to open device '%s' for reading!\n", dip->di_dname);
#if defined(WIN32)
	    report_error (dip, "FindCapacity() CreateFile", FALSE);
#else /* !defined(WIN32) */
	    report_error (dip, "FindCapacity() open", FALSE);
#endif /* defined(WIN32) */
	    return (FAILURE);
	}
	dip->di_fd = fd;
    }

    buffer = (u_char *) malloc (dsize);
    if (buffer == NULL) return (FAILURE);
    /*
     * Algorithm:
     *	There maybe a better may, but this works...
     */
    lba = adjust;
    adjust /= 2;

    while (TRUE) {

	if (dip->di_terminating) break;
	//HANDLE_TERMINATE(dip);

	attempts++;
#if defined(DEBUG)
	Printf("lba = " LUF ", adjust = %lu\n", lba, adjust);
#endif
	/*
	 * We cannot seek past the maximum allowable file position,
	 * otherwise lseek() fails, and 'dt' exits.  So, we must
	 * limit seeks appropriately, and break out of this loop
	 * if we hit the upper seek limit.
	 */
	if ( (OFF_T)(lba * dsize) < (OFF_T) 0 ) {
	    lba = (max_seek / dsize);
	}
	offset = set_position (dip, (OFF_T)(lba * dsize), TRUE);
	/*
	 * If seek fails, probably too big, adjust below and retry.
	 */
	if (offset == (OFF_T) -1) {
	    count = -1;
	} else {
#if defined(WIN32)
	    if (!ReadFile(dip->di_fd, buffer, dsize, &count, NULL)) {
		count = FAILURE;
	    }
#else /* !defined(WIN32) */
	    count = read (dip->di_fd, buffer, dsize);
#endif /* defined(WIN32) */
	}
	if (count == dsize) {
	    if (lba == (OFF_T)(max_seek / dsize)) break;
	    lba += adjust;
	    if (adjust == 1) break;
	    /*
	     * This is a mess, since each OS returns different errors
	     * for seek/read past end of media, damn!  In general, the
	     * ENOSPC should be returns for writes only, while a read
	     * should return 0 for EOF.  ENXIO/EIO/EINVAL are those
	     * expected for different OS's, so maybe clean this up?
	     */
#if defined(SCO) || defined(HP_UX) || defined(AIX)
	} else if ( (count == 0) ||
		    ( (count < 0) &&
		      ((errno == ENOSPC) || (errno == ENXIO)) ) ) {
#elif defined(BrokenEOF)
	} else if ( (count == 0) ||
		    ( (count < 0) &&
		      ((errno == ENOSPC) || (errno == EIO)) ) ) {
#elif defined(__CYGWIN__) || defined(__linux__)
	} else if ( (count == 0) ||
		    ( (count < 0) && (errno == EINVAL) ) ) {
#elif defined(WIN32)
	} else if ( (count == 0) ||
		    ( (count < 0) && 
		      ( ((errno = GetLastError()) == ERROR_DISK_FULL)   ||
		        (errno == ERROR_SECTOR_NOT_FOUND)		||
			(errno == ERROR_IO_DEVICE) ) ) ) { 
#else /* !defined(SCO) && !defined(HP_UX) && !defined(AIX) */
	} else if ( (count == 0) ||
		    ( (count < 0) && (errno == ENOSPC) ) ) {
#endif /* defined(SCO) || defined(HP_UX) || defined(AIX) */
	    if (last) adjust /= 2;
	    if (!adjust) adjust++;
	    lba -= adjust;
	} else {
#if defined(WIN32)
	    report_error (dip, "FindCapacity() ReadFile", FALSE);
#else /* !defined(WIN32) */
	    report_error (dip, "FindCapacity() read", FALSE);
#endif /* defined(WIN32) */
	    status = FAILURE;
	    break;
	}
	last = count;
    }
    free (buffer);
    if (temp_fd) {
#if defined(WIN32)
	CloseHandle(dip->di_fd);
#else /* !defined(WIN32) */
	(void) close (dip->di_fd);
#endif /* defined(WIN32) */
	dip->di_fd = saved_fd;
    } else {
	(void) set_position (dip, (OFF_T) 0, FALSE);
    }

    /*
     * If the read failed, set the lba to the last successful read,
     * and continue.  Won't be perfect, but at least we can run.
     * Note: Workaround for problem seen on Linux w/ATAPI CD-ROM's.
     */
    if (status == FAILURE) {
#if 1
#if defined(DEBUG)
	Printf("failed, last good lba was " LUF ", adjust was %ld\n",
							 lba, adjust);
#endif /* defined(DEBUG) */
	lba -= adjust;
	exit_status = SUCCESS;
#else
	return (status);	/* Return the failure! */
#endif
    }

#if defined(DEBUG)
    Printf ("read attempts was %d, the max lba is " LUF "\n", attempts, lba);
#endif /* defined(DEBUG) */

set_capacity:
    dip->di_capacity = lba;
    dip->di_storage_size = (large_t)(lba * dsize);
    /* Hack Alert: The actual user specified data limit is reset later! */
    dip->di_data_limit = dip->di_storage_size;
    if (!dip->di_record_limit) dip->di_record_limit = INFINITY;

set_random_limit:
    /*
     * The proper data limit is necessary for random I/O processing.
     */
    if (dip->di_random_io) {
	if ( (dip->di_rdata_limit == (large_t)0) || (dip->di_rdata_limit > dip->di_data_limit) ) {
	    dip->di_rdata_limit = dip->di_data_limit;
	}
	if (dip->di_debug_flag || dip->di_Debug_flag || dip->di_rDebugFlag || (status == FAILURE)) {
	    Printf ("Random data limit set to " LUF " bytes (%.3f Mbytes), " LUF " blocks.\n",
		dip->di_rdata_limit, ((double)dip->di_rdata_limit/(double)MBYTE_SIZE), (dip->di_rdata_limit / dsize));
	}
	if (dip->di_rdata_limit <= (large_t)dip->di_file_position) {
	    LogMsg (efp, logLevelCrit, 0,
		    "Please specify a random data limit (" LUF ") > file position (" FUF ")!\n",
		    dip->di_rdata_limit, dip->di_file_position);
	    exit (FATAL_ERROR);
	}
    } else if (dip->di_debug_flag || dip->di_Debug_flag || (status == FAILURE)) {
	    Printf ("Data limit set to " LUF " bytes (%.3f Mbytes), " LUF " blocks.\n",
		dip->di_data_limit, ((double)dip->di_data_limit/(double)MBYTE_SIZE),
				     (dip->di_data_limit / dsize));
	if ((large_t)dip->di_file_position > dip->di_data_limit) {
	    LogMsg (efp, logLevelCrit, 0,
		    "Please specify a file position (" FUF ") < media capacity (" LUF ")!\n",
		    dip->di_file_position, dip->di_data_limit);
	    exit (FATAL_ERROR);
	}
    }
    return (SUCCESS);
}
