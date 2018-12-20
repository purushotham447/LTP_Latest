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
 * Module:	dtstats.c
 * Author:	Robin T. Miller
 *
 * Description:
 *	Display statistics information for generic data test program.
 *
 * Modification History:
 *
 * October 6th, 2010 by Robin T. Miller
 * 	Report IOT seed and/or data pattern used during read/write statistics,
 * which is useful when during multiple passes to help with troubleshooting.
 * 
 * August 20th, 2010 by Robin T. Miller
 * 	Modified pass/total stats function to only display the keepalive
 * message if the stats level == STATS_BRIEF. (compatibility)
 * 
 * February 5th, 2009 by Robin T. Miller.
 *	Avoid referencing output_dtype and input_dtype variables, which may
 * not be setup yet (causing a segmentation fault dereferencing null pointer).
 * Save last write statistics to be used in read functions to avoid reading
 * more data than written (avoid false DC).
 *
 * November 9th, 2008 by Robin T. Miller.
 *	When testing large aggregates with slices, when displaying the slice
 * range, ensure the lba calculated from the file offset is not truncated.
 * Display the starting lba as a 64-bit quantity, instead of 32 bits!
 *
 * October 29th, 2007 by Robin T. Miller.
 *	Remove crufty old MS Visual C++ 6.0, Visual C++ 2005 is much better!
 *
 * September 26th, 2007 by Robin T. Miller.
 *	Removed PRT_NOIDENT when logging brief or keepalive stats so the
 * process ID is printed with multiple processes. Needed to identify proc!
 *
 * June 21st, 2007 by Robin T. Miller.
 *	Fix bug introduced in May 2000!  When displaying the exit status,
 * include the exit status variable in the printf()! (my bad)  Also place
 * this message under debug control, so exit due to signals don't alarm!
 *
 * May 16th, 2007 by Robin T. Miller.
 *	When reporting total keeoalive statistics, call init_stats()
 * first so the proper totals are reported (would be doubled previously).
 *
 * June 24th, 2004 by Robin Miller.
 *      Improve data pattern display when multiple passes specified.
 * Previously, insufficent/misleading information was displayed when
 * IOT or lbdata was enabled.
 *
 * December 6th, 2003 by Robin Miller.
 *      Conditionalize to exclude tty code.
 *
 * November 17th, 2003 by Robin Miller.
 *	Breakup output to stdout or stderr, rather than writing
 * all output to stderr.  If output file is stdout ('-') or a log
 * file is specified, then all output reverts to stderr.
 *
 * January 29th, 2002 by Robin Miller.
 *	Display the start and end date/time for per pass statistics.
 *
 * January 24th, 2001 by Robin Miller.
 *	If variable block sizes enabled, display the random seed used.
 *	When using IOT test pattern, display the blocking factor in the
 * total statistics, now that "lbs=" can alter the default size.
 *
 * January 15th, 2001 by Robin Miller.
 *	On Windows, enable display of the system and user times, since
 * this is reported properly by the latest Cygnus DLL (1.1.7-1 used).
 * When testing multiple volumes, display the total volumes completed.
 *
 * January 14th, 2001 by Robin Miller.
 *	Added support for multiple volumes option.
 *
 * January 11th, 2001 by Robin Miller.
 *	Fix problem with displaying 64-bit total tape files count.
 *
 * December 30th, 2000 by Robin Miller.
 *	Make changes to build using MKS/NuTCracker product.
 *
 * November 19th, 2000 by Robin Miller.
 *	When testing with the lbdata option, display both the starting
 * lba and the size used.  On Tru64 Unix, device size should be default.
 *
 * May 5th, 2000 by Robin Miller.
 *	When displaying total statistics, if the total errors is zero,
 * and the exit status is not SUCCESS, then display the exit status to
 * help diagnose improper exit status problems.
 *
 * April 25th, 2000 by Robin Miller.
 *	During multiple passes, display the current pattern read/written,
 * unless using a pattern file.  We used to work this way before we put our
 * data pattern into the pattern buffer (regression).
 *
 * April 18th, 2000 by Robin Miller.
 *	Modified statistics, so each set of stats has a newline prepended
 * which makes the formatting more consistent, and matchs 'scu's output.
 *
 * February 17th, 2000 by Robin Miller.
 *	Reset end of file/logical/media flags at end of pass.
 *
 * December 31st, 1999 by Robin Miller.
 *	Display the type of I/O performed, and if random also display the
 * random seed so the user has the option of specifying this same seed.
 *
 * July 22nd, 1999 by Robin Miller.
 *	Added support for IOT (DJ's) test pattern.
 * 
 * May 3, 1999 by Robin Miller.
 *	Added table wait time for DUNIX systems.
 *
 * April 8, 1999 by Robin Miller.
 *	Merge in Jeff Detjen's changes for table()/sysinfo timing.
 *
 * December 19, 1998 by Robin Miller.
 *	Fix problem reporting total files processed count when we have
 * not completed a pass (exiting prematurely due to error or signal).
 *
 * November 16, 1998 by Robin Miller.
 *	Moved location of where Asynchonous I/O's (AIO's) got reported.
 *
 * November 3, 1998 by Robin Miller.
 *	If asynchronous I/O (AIO) is enabled, display the AIO count used
 * in the total statistics (needed to distiguish from normal sync I/O).
 *
 * May 13, 1997 by Robin Miller.
 *	Report number of I/O's per second (some people desire this).
 *
 * February 18, 1996 by Robin Miller.
 *	Added support for 'copy' and 'verify' statistics.
 *
 * October 27, 1995 by Robin Miller.
 *	Correctly use "hz" variable instead of "HZ" define for clock ticks.
 *	[ NOTE: This could have resulted in wrong performance statistics. ]
 *
 * August 12, 1994 by Robin Miller.
 *	Removed extra "%" character in "Total passes..." printf, which
 *	prevents this line from being formatted and displayed on Gold.
 *
 * October 28, 1993 by Robin Miller.
 *	For multiple processes, display the PID to differentiate output.
 *
 * Septemeber 1, 1993 by Robin Miller.
 *	Display variable record size parameters when enabled.
 *	Properly display unsigned decimal values to prevent negative
 *	values from being displayed.
 *
 * August 13, 1993 by Robin Miller.
 *	Display data pattern for per pass statistics when multiple passes
 *	are selected, since a different pattern is used for each pass.
 *	Also added field width (08) when printing the hex pattern value.
 *
 * August 17, 1993 by Robin Miller.
 *	Display the program start & end times for total statistics.
 *
 * August 5, 1993 by Robin Miller.
 *	Added displaying of tape files processed (if enabled by user).
 *
 * August 4, 1993 by Robin Miller.
 *	Use buffering printing functions to ensure statistics get written
 *	contiguously to the log file (necessary for multiple processes).
 *
 */
#include "dt.h"

static char *stats_names[] = {
	"Copy",			/* COPY_STATS */
	"Read",			/* READ_STATS */
	"Read After Write",	/* RAW_STATS */
	"Write",		/* WRITE_STATS */
	"Total",		/* TOTAL_STATS */
	"Verify"		/* VERIFY_STATS */
};
static char *data_op_str = "Data operation performed: ";

/*
 * Functions to Process Statistics:
 */
void
accumulate_stats(dinfo_t *dip)
{
    dinfo_t *odip = dip->di_output_dinfo;

    if (odip == NULL) return;

    /*
     * Accumlate multiple device statistics (copy/verify).
     */
    dip->di_files_read += odip->di_files_read;
    dip->di_dbytes_read += odip->di_dbytes_read;
    dip->di_vbytes_read += odip->di_vbytes_read;
    dip->di_records_read += odip->di_records_read;
    dip->di_files_written += odip->di_files_written;
    dip->di_dbytes_written += odip->di_dbytes_written;
    dip->di_vbytes_written += odip->di_vbytes_written;
    dip->di_records_written += odip->di_records_written;
    dip->di_volume_records += odip->di_volume_records;

    odip->di_records_processed = (odip->di_full_reads + odip->di_full_writes);
    odip->di_partial_records = (odip->di_partial_reads + odip->di_partial_writes);
    dip->di_records_processed += odip->di_records_processed;
    dip->di_partial_records += odip->di_partial_records;

    return;
}

void
gather_stats(struct dinfo *dip)
{
    /*
     * Gather per pass statistics.
     */
    dip->di_total_files_read += dip->di_files_read;
    dip->di_total_files_written += dip->di_files_written;
    dip->di_total_bytes_read += dip->di_dbytes_read;
    dip->di_total_bytes_written += dip->di_dbytes_written;
    dip->di_total_partial_reads += dip->di_partial_reads;
    dip->di_total_partial_writes += dip->di_partial_writes;
    dip->di_total_records_read += dip->di_full_reads;
    dip->di_total_records_written += dip->di_full_writes;
    /* TODO: Cleanup these two variables. */
    dip->di_records_processed = (dip->di_full_reads + dip->di_full_writes);
    dip->di_partial_records = (dip->di_partial_reads + dip->di_partial_writes);
    /*
     * Save the last data bytes written for handling "file system full".
     */
    dip->di_last_dbytes_written = dip->di_dbytes_written;
    dip->di_last_fbytes_written = dip->di_fbytes_written;
    dip->di_last_vbytes_written = dip->di_vbytes_written;
    if (dip->di_mode == READ_MODE) {
	dip->di_last_files_read = dip->di_files_read;
	if (dip->di_files_read > dip->di_max_files_read) {
	    dip->di_max_files_read = dip->di_files_read;
	}
    } else {
	dip->di_last_files_written = dip->di_files_written;
	if (dip->di_files_written > dip->di_max_files_written) {
	    dip->di_max_files_written = dip->di_files_written;
	}
    }
    dip->di_last_dir_number = dip->di_dir_number;
    dip->di_last_subdir_number = dip->di_subdir_number;
    dip->di_last_subdir_depth = dip->di_subdir_depth;
    return;
}

void
gather_totals(struct dinfo *dip)
{
    /*
     * Gather total (accumulated) statistics:
     */
    dip->di_total_bytes = (dip->di_total_bytes_read + dip->di_total_bytes_written);
    dip->di_total_files = (dip->di_total_files_read + dip->di_total_files_written);
    dip->di_total_records += dip->di_records_processed;
    dip->di_total_partial += dip->di_partial_records;
    dip->di_total_errors += dip->di_error_count;
    return;
}

void
init_stats(struct dinfo *dip)
{
    /*
     * Initialize fields in preparation for the next pass.
     */
    dip->di_error_count = (u_long) 0;
    dip->di_end_of_file = FALSE;
    dip->di_end_of_media = FALSE;
    dip->di_end_of_logical = FALSE;
    dip->di_beginning_of_file = FALSE;
    dip->di_no_space_left = FALSE;
    dip->di_dir_number = (u_long) 0;
    dip->di_subdir_depth = (u_long) 0;
    dip->di_subdir_number = (u_long) 0;
    dip->di_file_number = (u_long) 0;
    dip->di_files_read = (u_long) 0;
    dip->di_dbytes_read = (large_t) 0;
    dip->di_vbytes_read = (large_t) 0;
    dip->di_records_read = (u_long) 0;
    dip->di_files_written = (u_long) 0;
    dip->di_dbytes_written = (large_t) 0;
    dip->di_vbytes_written = (large_t) 0;
    dip->di_records_written = (u_long) 0;
    dip->di_volume_records = (u_long) 0;
    dip->di_full_reads = (u_long) 0;
    dip->di_full_writes = (u_long) 0;
    dip->di_partial_reads = (u_long) 0;
    dip->di_partial_writes = (u_long) 0;
    dip->di_discarded_write_data = (large_t) 0;
    dip->di_maxdata_read = (large_t) 0;
    dip->di_maxdata_written = (large_t) 0;
    dip->di_records_processed = (u_long) 0;
    /*
     * Must free this to force starting at top of tree.
     */
    if (dip->di_subdir) {
	free(dip->di_subdir);
	dip->di_subdir = NULL;
    }
    /* For Copy/Verify, clear the output stats too! */
    if (dip->di_output_dinfo) {
	init_stats(dip->di_output_dinfo);
    }
    return;
}

/************************************************************************
 *									*
 * report_pass() - Report end of pass information.			*
 *									*
 * Inputs:								*
 *	stats_type = Type of statistics to display (read/write/total).	*
 *									*
 ************************************************************************/
void
report_pass(struct dinfo *dip, enum stats stats_type)
{
    gather_stats(dip);		/* Gather the total statistics.	*/
    gather_totals(dip);		/* Update the total statistics. */

    if (dip->di_pstats_flag && (dip->di_stats_level == STATS_FULL) ) {
        if (dip->di_stats_flag) {
	    report_stats(dip, stats_type);
	}
    } else if ( (!dip->di_pstats_flag && dip->di_verbose_flag) || /* compatability */
		(dip->di_pstats_flag && (dip->di_stats_level == STATS_BRIEF)) ) {
	/* Overloaded, need to restructure! */
	if (dip->di_stats_level == STATS_BRIEF) {
	    /*
	     * Note: Empty keepalive setup for monitoring no I/O progress.
	     */
	    if ( (dip->di_user_keepalive && strlen(dip->di_keepalive)) && !dip->di_user_pkeepalive &&
		 (time((time_t *)0) > dip->di_last_alarm_time) ) {
		char alivemsg[STRING_BUFFER_SIZE];
		if (FmtKeepAlive(dip, dip->di_keepalive, alivemsg) == SUCCESS) {
		    LogMsg (ofp, logLevelLog, 0, "%s\n", alivemsg);
		}
	    }
	}
        if ( dip->di_pkeepalive && strlen(dip->di_pkeepalive) ) {
            /* TODO: Make stats type available in FmtKeepAlive()! */
	    Lprintf (dip, "End of %s ", stats_names[(int)stats_type]);
            FmtKeepAlive(dip, dip->di_pkeepalive, dip->di_log_bufptr);
            LogMsg (ofp, logLevelLog, 0, "%s\n", dip->di_log_buffer);
	    dip->di_log_bufptr = dip->di_log_buffer;
        }
    }
    /*
     * Re-initialize the per pass counters and flags.
     */
    init_stats(dip);
    return;
}

/************************************************************************
 *									*
 * report_stats() - Report statistics at end of pass or program.	*
 *									*
 * Inputs:								*
 *	stats_type = Type of statistics to display (read/write/total).	*
 *									*
 ************************************************************************/
void
report_stats(struct dinfo *dip, enum stats stats_type)
{
	double bytes_sec, kbytes_sec, ios_sec, secs_io, msecs_io, Kbytes, Mbytes;
	large_t xfer_bytes, xfer_records;
	unsigned long xfer_partial;
#if defined(WIN32)
	clock_t et;
#else
	clock_t at, et;
#endif
	struct tms *stms, *etms = &dip->di_etimes;
	char pbuf[50];
	char *pinfo = pbuf;

        if (!dip->di_stats_flag || (dip->di_stats_level == STATS_NONE) ) return;

        if ( (stats_type == TOTAL_STATS) && (dip->di_stats_level == STATS_BRIEF) ) {
	    /* Overloaded, need to restructure! */
	    if (dip->di_stats_level == STATS_BRIEF) {
		if ( dip->di_user_keepalive && !dip->di_user_tkeepalive &&
		     (time((time_t *)0) > dip->di_last_alarm_time) ) {
		    if (FmtKeepAlive(dip, dip->di_keepalive, dip->di_log_buffer) == SUCCESS) {
			LogMsg (ofp, logLevelLog, 0, "%s\n", dip->di_log_buffer);
		    }
		}
	    }
            if ( dip->di_tkeepalive && strlen(dip->di_tkeepalive) ) {
		init_stats(dip);	/* Init to get correct totals! */
                if (FmtKeepAlive(dip, dip->di_tkeepalive, dip->di_log_buffer) == SUCCESS) {
                    LogMsg (ofp, logLevelLog, 0, "%s\n", dip->di_log_buffer);
                }
            }
            return;
        }
	dip->di_end_time = times (etms);
	if (dip->di_num_procs || dip->di_num_slices || dip->di_forked_flag || dip->di_logpid_flag) {
	    Lprintf (dip, "\n%s Statistics (%d):\n",
				stats_names[(int)stats_type], dip->di_process_id);
	} else {
	    Lprintf (dip, "\n%s Statistics:\n", stats_names[(int)stats_type]);
	}

	if (stats_type == TOTAL_STATS) {
	    et = dip->di_end_time - dip->di_start_time;	/* Test elapsed time.	*/
	    stms = &dip->di_stimes;			/* Test start times.	*/
	    xfer_bytes = dip->di_total_bytes;		/* Total bytes xferred.	*/
	    xfer_records = dip->di_total_records;	/* Total records xfered	*/
	    xfer_partial = dip->di_total_partial;	/* Total partial records*/
	} else {
	    et = dip->di_end_time - dip->di_pass_time;	/* Pass elapsed time.	*/
	    stms = &dip->di_ptimes;			/* Test pass times.	*/
	    xfer_bytes = dip->di_dbytes_read;		/* Data bytes per pass.	*/
	    xfer_bytes += dip->di_dbytes_written;	/* Data bytes written.	*/
	    xfer_records = dip->di_records_processed;	/* Data records/pass.	*/
	    xfer_partial = dip->di_partial_records;	/* Partial records.	*/
	}

	if (stats_type == TOTAL_STATS) {
	    /*
	     * Display device tested & other device information.
	     */
	    if (dip->di_input_file) {
		//struct dinfo *dip = input_dinfo;
		struct dtype *dtp = dip->di_dtype;
		Lprintf (dip, "%30.30s%s",
				"Input device/file name: ", dip->di_dname);
		if (dtp && (dtp->dt_dtype != DT_UNKNOWN) ) {
		    if (dip->di_device != NULL) {
			Lprintf (dip, " (Device: %s, type=%s)\n",
					dip->di_device, dtp->dt_type);
		    } else {
			Lprintf (dip, " (device type=%s)\n", dtp->dt_type);
		    }
		} else {
		    Lprintf (dip, "\n");
		}
	    } else {
		//struct dinfo *dip = output_dinfo;
		struct dtype *dtp = dip->di_dtype;
		Lprintf (dip, "%30.30s%s",
				"Output device/file name: ", dip->di_dname);
		if (dtp && (dtp->dt_dtype != DT_UNKNOWN) ) {
		    if (dip->di_device != NULL) {
			Lprintf (dip, " (Device: %s, type=%s)\n",
					dip->di_device, dtp->dt_type);
		    } else {
			Lprintf (dip, " (device type=%s)\n", dtp->dt_type);
		    }
		} else {
		    Lprintf (dip, "\n");
		}
	    }
#if defined(SCSI)
	    /* SCSI Information: */
	    if (dip->di_scsi_flag) {
		if (dip->di_scsi_dsf) {
		    Lprintf (dip, "%30.30s%s\n",
			     "SCSI device name: ", dip->di_scsi_dsf);
		}
		if (dip->di_device_capacity) {
		    Lprintf (dip, "%30.30s", "Capacity information: ");
		    Lprintf (dip, "Block Length=%u", dip->di_block_length);
		    Lprintf (dip, ", Capacity=" LUF " (%.3f Mbytes)\n",
			     dip->di_device_capacity,
			     (double)(dip->di_device_capacity * dip->di_block_length) / (double)MBYTE_SIZE );
		}
		if (dip->di_vendor_id && dip->di_product_id && dip->di_revision_level) {
		    Lprintf (dip, "%30.30s", "Inquiry information: ");
		    Lprintf(dip, "Vid=%s, Pid=%s, Rev=%s\n",
			    dip->di_vendor_id, dip->di_product_id, dip->di_revision_level);
		}
	    }
	    if (dip->di_device_id) {
		Lprintf (dip, "%30.30s%s\n",
					"Device identifier: ", dip->di_device_id);
	    }
	    if (dip->di_serial_number) {
		Lprintf (dip, "%30.30s%s\n",
					"Device serial number: ", dip->di_serial_number);
	    }
	    /* For Windows, it's just the drive letter, so we'll omit this (for now). */
# if !defined(WIN32)
	    if (dip->di_mounted_from_device) {
		Lprintf (dip, "%30.30s%s\n",
			 "Mounted from device: ", dip->di_mounted_from_device);
	    }
	    if (dip->di_mounted_on_dir) {
		Lprintf (dip, "%30.30s%s\n",
			 "Mounted on directory: ", dip->di_mounted_on_dir);
	    }
	    if (dip->di_filesystem_type) {
		Lprintf (dip, "%30.30s%s\n",
			 "Filesystem type: ", dip->di_filesystem_type);
	    }
	    if (dip->di_filesystem_options) {
		Lprintf (dip, "%30.30s%s\n",
			 "Filesystem options: ", dip->di_filesystem_options);
	    }
# endif /* defined(WIN32) */
#else /* !defined(SCSI) */
# if !defined(WIN32)
	    if (dip->di_mounted_from_device) {
		Lprintf (dip, "%30.30s%s\n",
			 "Mounted from device: ", dip->di_mounted_from_device);
	    }
# endif /* defined(WIN32) */
#endif /* defined(SCSI) */
	    Lprintf (dip, "%30.30s", "Type of I/O's performed: ");
	    if (dip->di_io_type == RANDOM_IO) {
		Lprintf (dip, "random (rseed=%#x", dip->di_random_seed);
	    } else {
		Lprintf (dip, "sequential (%s",
			(dip->di_io_dir == FORWARD) ? "forward" : "reverse");
		if (dip->di_variable_flag) {
		    Lprintf (dip, ", rseed=%#x", dip->di_random_seed);
		}
	    }
	    if (dip->di_raw_flag) {
		Lprintf (dip, ", read-after-write)\n");
	    } else {
		Lprintf(dip, ")\n");
	    }
	    if (dip->di_io_type == RANDOM_IO) {
		Lprintf (dip, "%30.30s", "Random I/O Parameters: ");
		Lprintf (dip, "position=" FUF ", ralign=%ld, rlimit=" LUF "\n",
			dip->di_file_position, dip->di_random_align, dip->di_rdata_limit);
	    } else if (dip->di_num_slices) {
		Lprintf (dip, "%30.30s", "Slice Range Parameters: ");
		Lprintf (dip, "position=" FUF " (lba " LUF "), limit=" LUF "\n",
		dip->di_file_position, (large_t)(dip->di_file_position / dip->di_dsize), dip->di_data_limit);
	    }

	    if (dip->di_align_offset || dip->di_rotate_flag) {
		Lprintf (dip, "%30.30s", "Buffer alignment options: ");
		if (dip->di_align_offset) {
		    Lprintf (dip, "alignment offset = %d bytes\n", dip->di_align_offset);
		} else {
		    Lprintf (dip, "rotating through 1st %d bytes\n", ROTATE_SIZE);
		}
	    }
	} /* end 'if (stats_type == TOTAL_STATS)' */

	if (dip->di_num_procs) {
	    Lprintf (dip, "%30.30s%d/%d\n",
		     "Current Process Reported: ", dip->di_cur_proc, dip->di_num_procs);
	} else if (dip->di_num_slices) {
	    Lprintf (dip, "%30.30s%d/%d\n",
		     "Current Slice Reported: ", dip->di_slice_num, dip->di_num_slices);
	}

    if (dip->di_io_mode == TEST_MODE) {
	/*
	 * Extra information regarding pattern verification.
	 */
	memset(pinfo, '\0', sizeof(*pinfo));
	if (dip->di_output_file && !dip->di_verify_flag) {
	    pinfo = " (read verify disabled)";
	} else if (!dip->di_compare_flag) {
	    pinfo = " (data compare disabled)";
	} else if (dip->di_incr_pattern) {
	    sprintf(pinfo, " (incrementing 0-255)");
	} else if (dip->di_iot_pattern) {
	    sprintf(pinfo, " (blocking is %u bytes)", (unsigned int)dip->di_lbdata_size);
	} else if (dip->di_pattern_file || dip->di_pattern_string) {
	    sprintf(pinfo, " (first %u bytes)", (unsigned int)sizeof(dip->di_pattern));
	} else if (dip->di_lbdata_flag) {
	    sprintf(pinfo, " (w/lbdata, lba %u, size %u bytes)",
		    dip->di_lbdata_addr, (unsigned int)dip->di_lbdata_size);
	}
	if ( (stats_type == TOTAL_STATS) || (dip->di_pass_limit > 1L) ) {
	    if (dip->di_fprefix_string) {
		Lprintf (dip, "%30.30s%s\n",
			"Data pattern prefix used: ", dip->di_fprefix_string);
	    }
	    if (dip->di_pattern_file) {
		Lprintf (dip, "%30.30s%s (%lu bytes)\n",
			"Data pattern file used: ", dip->di_pattern_file, dip->di_patbuf_size);
	    } else if (dip->di_pattern_string) {
		Lprintf (dip, "%30.30s'%s'%s\n",
				"Data pattern string used: ", dip->di_pattern_string,
				(dip->di_iot_pattern) ? pinfo : "");
	    }
	}
	if (dip->di_iot_pattern && dip->di_unique_pattern && (dip->di_iot_seed_per_pass != IOT_SEED)) {
	    Lprintf (dip, "%30.30s0x%08x\n",
		     "IOT seed value used: ", dip->di_iot_seed_per_pass);
	}
	if (!dip->di_iot_pattern) {
	  if (dip->di_output_file && dip->di_verify_flag) {
	    Lprintf (dip, "%30.30s0x%08x%s\n",
			    "Data pattern read/written: ", dip->di_pattern, pinfo);
	  } else if (dip->di_output_file && !dip->di_verify_flag) {
	    Lprintf (dip, "%30.30s0x%08x%s\n",
			    "Data pattern written: ", dip->di_pattern, pinfo);
	  } else {
	    Lprintf (dip, "%30.30s0x%08x%s\n",
			    "Data pattern read: ", dip->di_pattern, pinfo);
	  }
	}
	if (dip->di_buffer_mode) {
	    Lprintf (dip, "%30.30s%s\n", "File system buffer mode: ", dip->di_bufmode_type);
	}
    } else { /* !TEST_MODE */
	if ( (stats_type == COPY_STATS) ||
	     ((stats_type == TOTAL_STATS) && !dip->di_verify_flag) ) {
	    Lprintf (dip, "%30.30sCopied '%s' to '%s'.\n",
				data_op_str,
				dip->di_dname,
				dip->di_output_dinfo->di_dname);
	} else if ( (stats_type == VERIFY_STATS) ||
		    ((stats_type == TOTAL_STATS) && dip->di_verify_only) ) {
	    Lprintf (dip, "%30.30sVerified '%s' with '%s'.\n",
				data_op_str,
				dip->di_dname,
				dip->di_output_dinfo->di_dname);
	}
    } /* end 'if (dip->di_io_mode == TEST_MDOE)' */
	if (dip->di_min_size) {
	    Lprintf (dip, "%30.30s" LUF " with min=%ld, max=%ld, incr=",
				"Total records processed: ",
				(xfer_records + xfer_partial),
				dip->di_min_size, dip->di_max_size);
	    if (dip->di_variable_flag) {
		Lprintf (dip, "variable\n");
	    } else {
		Lprintf (dip, "%ld\n", dip->di_incr_count);
	    }
	} else {
	    Lprintf (dip, "%30.30s" LUF " @ %ld bytes/record",
				"Total records processed: ",
				xfer_records, dip->di_block_size);
	    if (xfer_partial) {
		Lprintf (dip, ", %lu partial\n", xfer_partial);
	    } else {
		Lprintf (dip, " (%.3f Kbytes)\n",
				((double)dip->di_block_size / (double) KBYTE_SIZE));
	    }
	}
    
	Kbytes = (double) ( (double) xfer_bytes / (double) KBYTE_SIZE);
	Mbytes = (double) ( (double) xfer_bytes / (double) MBYTE_SIZE);
	    
	Lprintf (dip, "%30.30s" LUF " (%.3f Kbytes, %.3f Mbytes)\n",
				"Total bytes transferred: ",
				xfer_bytes, Kbytes, Mbytes);

	/*
	 * Calculate the total clock ticks (hz = ticks/second).
	 */
	if (et) {
	    bytes_sec = ((double)xfer_bytes / ((double)et / (double)hz));
	} else {
	    bytes_sec = 0.0;
	}
        kbytes_sec = (double) ( (double) bytes_sec / (double) KBYTE_SIZE);
	Lprintf (dip, "%30.30s%.0f bytes/sec, %.3f Kbytes/sec\n",
				"Average transfer rates: ",
				bytes_sec, kbytes_sec);
#if defined(AIO)
	if (stats_type == TOTAL_STATS) {
	    if (dip->di_aio_flag) {
		Lprintf(dip, "%30.30s%d\n", "Asynchronous I/O's used: ", dip->di_aio_bufs);
	    }
	}
#endif /* defined(AIO) */

	if (et && xfer_records) {
	    double records = (double)(xfer_records + xfer_partial);
	    double secs = ((double)et / (double)hz);
	    ios_sec = (records / secs);
	    secs_io = (secs / records);
	    msecs_io = ( (secs * MSECS) / records);
	} else {
	    ios_sec = 0.0;
	    secs_io = 0.0;
	    msecs_io = 0.0;
	}
	/* Note: These stats are for all operations, *not* just I/O! Could be misleading!  */
	Lprintf (dip, "%30.30s%.3f\n", "Number I/O's per second: ", ios_sec);
	Lprintf (dip, "%30.30s%.4f (%.2fms)\n", "Number seconds per I/O: ", secs_io, msecs_io);

	if (dip->di_multi_flag || dip->di_volumes_flag) {
	    Lprintf (dip, "%30.30s", "Total volumes completed: ");
	    if (dip->di_volumes_flag) {
		Lprintf (dip, "%d/%d\n", dip->di_multi_volume, dip->di_volume_limit);
	    } else {
		Lprintf (dip, "%d\n", dip->di_multi_volume);
	    }
	}

	Lprintf (dip, "%30.30s", "Total passes completed: ");
	if (dip->di_runtime) {
	    Lprintf (dip, "%lu\n", dip->di_pass_count);
	} else {
	    Lprintf (dip, "%lu/%lu\n", dip->di_pass_count, dip->di_pass_limit);
	}

	if (dip->di_file_limit || dip->di_user_dir_limit || dip->di_user_subdir_limit || dip->di_user_subdir_depth) {
	    u_long max_files, files = dip->di_file_limit;
	    u_long dir_files, sdepth_files, subdir_files;
	    if (files == 0) files++;
	    max_files = files;
	    sdepth_files = (dip->di_user_subdir_depth * files);
	    if (sdepth_files) {
		subdir_files = (dip->di_user_subdir_limit * sdepth_files);
	    } else {
		subdir_files = (dip->di_user_subdir_limit * files);
	    }
	    if (subdir_files) {
		dir_files = (dip->di_user_dir_limit * subdir_files);
	    } else {
		dir_files = (dip->di_user_dir_limit * files);
	    }
	    if (dir_files) {
		max_files += dir_files;
	    } else if (subdir_files) {
		max_files += subdir_files;
	    } else if (sdepth_files) {
		max_files += sdepth_files;
	    }
	    if ((stats_type == TOTAL_STATS) && dip->di_output_file && dip->di_verify_flag) {
		/*
		 * Handle multiple files for both read and write pass.
		 */
		if ( (!dip->di_raw_flag || (dip->di_raw_flag && dip->di_reread_flag)) && (dip->di_total_files > max_files) ) {
		    max_files *= 2;	/* Adjust for read + write passes. */
		}
	    }
	    Lprintf (dip, "%30.30s", "Total files processed: ");
	    if ((stats_type == TOTAL_STATS) && dip->di_pass_count && dip->di_total_files) {
		Lprintf (dip, LUF "/" LUF "\n", dip->di_total_files,
				((large_t)dip->di_pass_count * (large_t)max_files));
	    } else {
		u_long files = (dip->di_files_read + dip->di_files_written);
		Lprintf (dip, "%lu/%lu\n", files, max_files);
	    }
	}

	Lprintf (dip, "%30.30s%lu/%lu",
				"Total errors detected: ",
	    (stats_type == TOTAL_STATS) ? dip->di_total_errors : dip->di_error_count,
						dip->di_error_limit);
	if (stats_type == TOTAL_STATS) {
	    if ( (dip->di_total_errors == 0) && (dip->di_debug_flag || dip->di_Debug_flag) &&
		 (exit_status != SUCCESS) && (exit_status != END_OF_FILE) ) {
		Lprintf (dip, " (exit status is %u! may be a signal?)", exit_status);
	    }
	}
	Lprintf(dip, "\n");

	/*
	 * Report elapsed, user, and system times.
	 */
	Lprintf (dip, "%30.30s", "Total elapsed time: ");
	format_time (dip, et);
#if !defined(WIN32)
	/*
	 * More ugliness for Windows, since the system and
	 * user times are always zero, don't display them.
	 */
	Lprintf (dip, "%30.30s", "Total system time: ");
	at = etms->tms_stime - stms->tms_stime;
	at += etms->tms_cstime - stms->tms_cstime;
	format_time (dip, at);

	Lprintf (dip, "%30.30s", "Total user time: ");
	at = etms->tms_utime - stms->tms_utime;
	at += etms->tms_cutime - stms->tms_cutime;
	format_time (dip, at);
#endif /* !defined(WIN32) */

	Lprintf (dip, "%30.30s", "Starting time: ");
	Ctime(dip, dip->di_program_start);
	dip->di_program_end = time((time_t) 0);
	Lprintf (dip, "%30.30s", "Ending time: ");
	Ctime(dip, dip->di_program_end);
	Lprintf (dip, "\n");
	Lflush(dip);
}
