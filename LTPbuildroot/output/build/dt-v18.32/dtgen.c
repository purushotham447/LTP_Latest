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
 * Module:	dtgen.c
 * Author:	Robin T. Miller
 * Date:	September 8, 1993
 *
 * Description:
 *	Generic test functions for the 'dt' program.
 *
 * Modification History:
 *
 * November 15th, 2012 by Robin T. Miller
 *	For Windows, correct bug when enabling sparse file attribute, and
 * also verify sparse files are supported before trying to enable sparse.
 * For example, my mapped home directory, does NOT support sparse files.
 * If the sparse attribute is already set, also detect this and handle.
 * If setting sparse fails or is not supported, automatically preallocate
 * files, if random I/O options are enabled.
 * Note: This preallocation is to mimic *nix FS's and avoid long noprogs!
 *
 * July 19th, 2012 by Robin T. Miller
 * 	Add support for retryable errors.
 *
 * May 3rd, 2012 by Robin T. Miller
 *    When position or seek options are specified with copy/verify modes,
 * ensure the output file offset is adjusted to match the input device. We
 * really need these to be separate, or consider applying seek to output and
 * skip to input only to match the 'dd' utility? This may break some folks!
 * 
 * January 4th, 2012 by Robin T. Miller
 *	For Windows, when the sparse file attribute is disabled, add a new
 * preallocate method (seek/write at end of file), when random or reverse I/O
 * is enabled, to avoid long no-progress messages. This write is NOT timed,
 * thus allowing NTFS to preallocate data blocks before the writes begin.
 *
 * October 15th, 2011 by Robin T. Miller
 * 	On Linux, disable misalign memory options when direct I/O is selected.
 *
 * June 23rd, 2011, by Robin T. Miller
 * 	Updated validate_opts() to use LogMsg() with severity level that
 * will add "ERROR:" to its' error messages.
 * 	Added sanity check to ensure the data limit is modulo the disk size,
 * to avoid false errors when trying to request a partial block with disks.
 * 
 * March 24th, 2011 by Robin T. Miller
 * 	Add SetupBufferingMode() to setup the various buffering modes.
 * 
 * February 5th, 2011 by Robin T. Miller
 *	Add conditionalization around O_DIRECT use. The version of MacOS I'm
 * compiling on, does not have this flag defined.
 *
 * January 31st, 2011 by Robin T. Miller
 *	Do not change the IOT seed per file per pass, since we have no way to
 * re-read a set of files with the same seed. A prefix string must be used to
 * generate unique data per file per pass. IOT seed is already unique per pass.
 *
 * November 10th, 2010 by Robin T. Miller
 *	When encountering "no space available" failure, break out of the file loop,
 * so we don't lose the state required for read pass, by attempting to write the
 * next file (which will also encounter "no space available". This lead to a false
 * corruption, since we'll try to read more than wr wrote. (sigh)
 *
 * October 11th, 2010 by Robin T. Miller
 *	Updated Windows code so when "flags=direct" is specified, which sets
 * FILE_FLAG_NO_BUFFERING, also add FILE_FLAG_WRITE_THROUGH to ensure metadata
 * is also flushed. See this URL for more information:
 * http://msdn.microsoft.com/en-us/library/aa363858(VS.85).aspx#caching_behavior
 *
 * October 6th, 2010 by Robin T. Miller
 * 	Add sanity check for min=/max= values when variable I/O sizes selected.
 * 
 * October 6th, 2010 by Robin T. Miller
 * 	Modify init_iotdata() calls to pass in the buffer to initialize, which
 * also allows us to optimize IOT pattern generation on writes (avoid extra copy).
 *
 * January 23rd, 2010 by Robin T. Miller
 *	Add support for maxdata= and maxfiles= options to limit the amount of
 * data and files when creating multiple directories and files.
 *
 * December 1st, 2009 by Robin T. Miller
 *	Added support for multiple directories.
 *
 * November 25th, 2009 by Robin T. Miller.
 *	Added support for directory paths (dir=dirpath), and create appropriate
 * device names for each directory and file number (if multiple files specified).
 *
 * November 21st, 2009 by Robin T. Miller
 *	Added support for writing and reading multiple disk files.
 *
 * September 2nd, 2008 by Robin T. Miller.
 *	Added SetSparseFile() function to enable this file attribute for
 * native Windows files, to mimic Unix file behaviour.  If this flag is not
 * set, then writes to large offset force all blocks to be allocated, which
 * causes false long no-progress indications.
 *
 * July 25th, 2008 by Robin T. Miller.
 *	Control fsync() via device info flag instead of using global.
 * This change allows separate control for input and output files, and
 * in particular allows reading from a file and writing to a pipe!
 * Previously, an fsync was attempted to the pipe which would fail.
 *
 * July 15th, 2008 by Robin T. Miller.
 *	Map POSIX O_TRUNC to TRUNCATE_EXISTING disposition flag.
 *
 * June 24th, 2008 by Robin T. Miller.
 *	Add finer grain control over timing individual operations.
 *
 * October 27th, 2007 by Robin T. Miller.
 *	Add support for Windows direct I/O (FILE_FLAG_NO_BUFFERING).
 *
 * May 12th, 2007 by Robin Miller.
 *	Add no I/O progress checks around fsync().
 *
 * May 2nd, 2007 by Robin Miller.
 *	Add call to ExecuteTrigger() when fsync() fails (oversight).
 *
 * January 19th, 2005 by Nagendra Vadlakunta.
 *	Added AIO support for Windows.
 *
 * November 11th, 2004 by Robin Miller.
 *      For Solaris, if Direct I/O (DIO) is enabled, use directio() API
 * after the file is open'ed to enable DIO.
 *
 * June 23rd, 2004 by Robin Miller.
 *      Added support for triggers on corruption.
 *      Allow non-modulo record sizes for regular files.
 *
 * February 27th, 2004 by Robin Miller.
 *      In open_file() pre-format error string for Hazard printing.
 *
 * November 17th, 2003 by Robin Miller.
 *	Breakup output to stdout or stderr, rather than writing
 * all output to stderr.  If output file is stdout ('-') or a log
 * file is specified, then all output reverts to stderr.
 *
 * September 27th, 2003 by Robin Miller.
 *      Added support for AIX.
 *
 * February 21st, 2002 by Robin Miller.
 *	Fix regression introduced by January 29th, 2002 update!
 * When AIO is specified the base buffer is not setup, only the
 * data buffer, so referencing this NULL pointer dumped core.
 *
 * January 29th, 2002 by Robin Miller.
 *	If compare is disabled, initialize the data buffer to be written.
 * This is important to honor the user specified pattern, and to avoid
 * problems writing data to tapes in compressed mode (user may wish to
 * specify a non-repeating data pattern).  In retrospect, it may not
 * be a good idea to use !compare to disable buffer initialization,
 * but changing this now will break too many folks :-)
 *
 * February 24th, 2001 by Robin Miller.
 *	Add conditionalization for QNX RTP (Neutrino).
 *
 * February 6th, 2001 by Robin Miller.
 *	Handle multiple slices to the same output file, by ensuring the
 * file disposition is set to "keep".  Otherwise, the first completing
 * process deletes the in-use file, which is generally not desriable.
 *
 * January 29th, 2001 by Robin Miller.
 *	Added validity checks to ensure transfer counts are modulo the
 * device size, to avoid unexpected failures.
 *
 * January 25th, 2001 by Robin Miller.
 *	Added validate options function for checking options after the
 * device information has been setup (i.e., device size, etc).
 *
 * January 15th, 2001 by Robin Miller.
 *	Add error checks to seek_file() and skip_file() calls.
 *	If reopen failures occur, don't terminate, return the error.
 *
 * January 14th, 2001 by Robin Miller.
 *	Added support for multiple volumes option.
 *
 * January 12th, 2001 by Robin Miller.
 *	When reading multiple tape files, issue a forward space file
 * mark command between tape files.  For systems which don't support
 * tape operations, we'll continue to use the read_eof() method.
 *
 * December 30th, 2000 by Robin Miller.
 *	Make changes to build using MKS/NuTCracker product.
 *
 * November 8th, 2000 by Robin Miller.
 *	Add check for ignoring device close failures.  In this case,
 * the error is displayed as a warning instead of a failure.
 *
 * July 14th, 2000 by Robin Miller.
 *	In flush_file(), control sync'ing of data using fsync flag.
 *
 * May 8th, 2000 by Robin Miller.
 *	Honor the di_closing flag, to avoid a race condition with the
 * close function being called (again) while still closing, from the
 * terminate() routine called by the runtime= alarm, or signals.
 * [ damn, fixed this in 1994, broke it during recent re-write :-) ]
 *
 * April 18th, 2000 by Robin Miller.
 *	Added messages for open/close failures doing EEI reset tests.
 *	Modified calls to report_error() to ensure error count bumped.
 *
 * March 28th, 2000 by Robin Miller.
 *	Modified calls to file position functions which now accept a
 * device information parameter.
 *
 * February 19th, 2000 by Robin Miller.
 *	When EEI resets are enabled, retry open/reopen failures attempts.
 *	Also, if we're processing EEI resets, don't fail on close().
 *
 * February 17th, 2000 by Robin Miller.
 *	Adding better support for multi-volume tape testing.
 *
 * January 22nd, 2000 by Robin Miller.
 *	Added support for Cygwin tape devices for Windows/NT.
 *
 * August 2, 1999 by Robin Miller.
 *	Don't do fsync() to tape devices to avoid errors on Linux.
 *
 * May 27, 1999 by Robin Miller.
 *	Adding support for micro-second delays.
 *
 * February 26, 1999 by Robin Miller.
 *	Adjust the file count AFTER writing a file mark, so our tape
 * repositioning code will work if the Reset occurs during the WFM.
 *
 * December 21, 1998 by Robin Miller.
 *	Updates necessary to match my tape API changes.
 *	Save device/file open flags in device info struct.
 *
 * December 17, 1998 by Robin Miller.
 *	For DUNIX tape devices, clear persistent EEI data after opens.
 *
 * April 28, 1998 by Robin Miller.
 *	For WIN32/NT, or in O_BINARY into open flags to force binary
 *	mode (the default is text mode).
 *
 * April 7, 1998 by Robin Miller.
 *	Fix problem with attempting reopen of stdin/stdout.
 *
 * March 27, 1997 by Ali Eghlima.
 *      Added cluster support, so more than one process or one system
 *      can access a resource. dlm are being used to synchronize all
 *      access.
 *
 * December 9, 1995 by Robin Miller.
 *	Allow writing tape file marks on QNX Operating System.
 *
 * September 23, 1994 by Robin Miller.
 *	Make changes necessary to build on QNX 4.21 release.  This
 *	required changing O_DSYNCH to O_DSYNC, and O_FSYNCH to O_SYNC.
 *
 * May 19, 1994 by Robin Miller.
 *	Altered logic in close_file() & reopen_file() functions to set
 *	the file descriptor to NoFd prior to calling close() to actually
 *	perform the close operation.  This avoids a problem where if the
 *	user types Ctrl/C while the close is in progress, the signal handler
 *	gets invoked immediately after the system call, the fd doesn't
 *	get marked closed, and our termination code then attempts to
 *	close an already closed file descriptor and reports the error:
 *		"dt: 'close' - Bad file number"
 */
#include "dt.h"
#if !defined(WIN32)
#  if defined(_QNX_SOURCE) 
#    include <fcntl.h>
#  else /* !defined(_QNX_SOURCE) */
#    include <sys/file.h>
#  endif /* defined(_QNX_SOURCE) */
#endif /* !defined(WIN32) */

/*
 * Declare the generic (default) test functions.
 */
struct dtfuncs generic_funcs = {
    /*	tf_open,		tf_close,		tf_initialize,	  */
	open_file,		close_file,		initialize,
    /*  tf_start_test,		tf_end_test,				  */
	init_file,		nofunc,
    /*	tf_read_file,		tf_read_data,		tf_cancel_reads,  */
	read_file,		read_data,		nofunc,
    /*	tf_write_file,		tf_write_data,		tf_cancel_writes, */
	write_file,		write_data,		nofunc,
    /*	tf_flush_data,		tf_verify_data,		tf_reopen_file,   */
	flush_file,		verify_data,		reopen_file,
    /*	tf_startup,		tf_cleanup,		tf_validate_opts  */
	nofunc,			nofunc,			validate_opts
};

/*
 * Forward References:
 */
int end_file_processing(struct dinfo *dip);
int process_next_dir(struct dinfo *dip);
int process_next_file(struct dinfo *dip);
int process_next_subdir(struct dinfo *dip);

#if defined(WIN32)
void SetupWindowsFlags(struct dinfo *dip, char *file, int oflags, DWORD *CreationDisposition, DWORD *FileAttributes);
int HandleSparseFile(dinfo_t *dip, DWORD FileAttributes);
int SetSparseFile(dinfo_t *dip, HANDLE hDevice, BOOL is_overlapped);
static int PreAllocateFile(dinfo_t *dip, DWORD FileAttributes);
#endif

/*
 * make_file_name() - Generate a New File Name.
 *
 * Description:
 *	A new file anme is created using the directory path (if any),
 * and the file number.
 *
 * Inputs:
 *	dip = The device information pointer.
 *
 * Outputs:
 *	dip->di_dname points to the new file name.
 *
 * Return Value:
 *	Returns a pointer to the new device name.
 */
char *
make_file_name(struct dinfo *dip)
{
    char path[PATH_BUFFER_SIZE];
    char *bp = path;

    /*
     * Construct new file name with directory path and file number appended.
     */
    if (dip->di_dirpath || dip->di_subdir) {
	/* Start with top level directory. */
	if (dip->di_dirpath) {
	    if (dip->di_dirpath[strlen(dip->di_dirpath)-1] == DIRSEP) {
		bp += sprintf(bp, "%s", dip->di_dirpath);
	    } else {
		bp += sprintf(bp, "%s%c", dip->di_dirpath, DIRSEP);
	    }
	}
	/* Append subdirectory (if any). */
	if (dip->di_subdir) {
	    bp += sprintf(bp, "%s%c", dip->di_subdir, DIRSEP);
	}
	if (dip->di_file_limit) {
	    (void)sprintf(bp, "%s-%08u",
			  dip->di_bname, (dip->di_file_number + 1) );
	} else {
	    (void)sprintf(bp, "%s", dip->di_bname);
	}
    } else {
	if (dip->di_file_limit) {
	    (void)sprintf(path, "%s-%08u", dip->di_bname, (dip->di_file_number + 1) );
	} else {
	    (void)sprintf(path, "%s", dip->di_bname);
	}
    }
    free(dip->di_dname);
    dip->di_dname = strdup(path);
    /*
     * Update the prefix string, *if* it contains the device name.
     */
    if (dip->di_prefix_string && strstr(dip->di_prefix_string, "%d") ) {
	/* Recreate prefix with new file name. */
	(void)FmtPrefix(dip, dip->di_prefix_string, dip->di_prefix_size);
    }
    return (dip->di_dname);
}

/*
 * end_file_processing() - End of File Processing.
 *
 * Inputs:
 *	dip = The device information pointer.
 *
 * Return Value:
 *	Returns SUCCESS/FAILURE = Next File Ready / Preparation Failed.
 */
int
end_file_processing(struct dinfo *dip)
{
    struct dtfuncs *dtf = dip->di_funcs;
    int status;

    /*
     * Remember: AIO close cancels outstanding IO's!
     */
    if (dip->di_mode == WRITE_MODE) {
        (void) (*dtf->tf_flush_data)(dip);
    }
    status = (*dip->di_funcs->tf_close)(dip);
    (void) (*dip->di_funcs->tf_end_test)(dip);
    return (status);
}

/*
 * process_next_dir() - Process The Next Directory.
 *
 * Note: Not used yet, but added for future enhancements.
 *
 * Inputs:
 *	dip = The device information pointer.
 *
 * Return Value:
 *	Returns SUCCESS/FAILURE/WARNING =
 *		Next Directory Ready / Preparation Failed / No More Dirs.
 */
int
process_next_dir(struct dinfo *dip)
{
    char dirpath[PATH_BUFFER_SIZE];
    int status;

    if (dip->di_user_dir_limit && (++dip->di_dir_number < dip->di_user_dir_limit) ) {
	;
    } else {
	return (WARNING);
    }

    /*
     * Track the max levels reached for cleanup purposes.
     */
    if (dip->di_dir_number > dip->di_max_dir_number) {
	dip->di_max_dir_number = dip->di_dir_number;
    }

    /*
     * Create the next top level directory.
     */
    (void)sprintf(dirpath, "%s-%05u", dip->di_dir, dip->di_dir_number);

    if (dip->di_mode == WRITE_MODE) {
	status = create_directory(dip, dirpath);
	if (status == FAILURE) {
	    --dip->di_dir_number;
	    return (FAILURE);
	}
    }
    if (dip->di_dirpath) free(dip->di_dirpath);
    dip->di_dirpath = strdup(dirpath);
    return (SUCCESS);
}

/*
 * process_next_subdir() - Process The Next Sub-Directory.
 *
 * Inputs:
 *	dip = The device information pointer.
 *
 * Return Value:
 *	Returns SUCCESS/FAILURE/WARNING =
 *		Next Directory Ready / Preparation Failed / No More Dirs.
 */
int
process_next_subdir(struct dinfo *dip)
{
    char path[PATH_BUFFER_SIZE];
    char dirpath[PATH_BUFFER_SIZE];
    u_int subdir_number;
    bool processing_subdir_flag = FALSE;
    int status;

    /*
     * Handle both top level directories and subdirectories.
     */
    if ( (dip->di_subdir_depth + 1) > dip->di_user_subdir_depth) {
	if (dip->di_user_subdir_limit && (dip->di_subdir_number < dip->di_user_subdir_limit) ) {
	    if (dip->di_subdir)	free(dip->di_subdir);
	    dip->di_subdir = NULL;	/* Starting new subdirectory. */
	    dip->di_subdir_number++;
	    if (dip->di_user_subdir_depth) dip->di_subdir_depth = 1;
	    subdir_number = dip->di_subdir_number;
	    processing_subdir_flag = TRUE;
	} else {
	    return (WARNING);
	}
    } else {
	if (dip->di_subdir_depth == 0) {
	    dip->di_subdir_number++;
	}
	subdir_number = ++dip->di_subdir_depth;
    }

    /*
     * Track the max levels reached for cleanup purposes.
     */
    if (dip->di_subdir_number > dip->di_max_subdir_number) {
	dip->di_max_subdir_number = dip->di_subdir_number;
    }
    if (dip->di_subdir_depth > dip->di_max_subdir_depth) {
	dip->di_max_subdir_depth = dip->di_subdir_depth;
    }
    dip->di_file_number = 0;

    /*
     * Create directory or next subdirectory.
     *
     * Note: Using short directory names, so we can nest deeper!
     */
    if (dip->di_subdir) {
	size_t sdir_size = (strlen(dip->di_subdir) + strlen(dip->di_dirprefix) + 10);
	if (dip->di_dirpath) sdir_size += strlen(dip->di_dirpath);
	sdir_size += strlen(dip->di_bname);
	/* Sanity check to avoid buffer overuns! */
	if ( sdir_size > PATH_BUFFER_SIZE) {
	    Printf("Subdirectory name (%u) is too long for our path buffer (%u)!\n",
		   sdir_size, PATH_BUFFER_SIZE);
	    return (FAILURE);
	}
	(void)sprintf(path, "%s%c%s%u",
		      dip->di_subdir, DIRSEP, dip->di_dirprefix, subdir_number);
    } else {
	(void)sprintf(path, "%s%u", dip->di_dirprefix, subdir_number);
    }
    if (dip->di_subdir)	free(dip->di_subdir);
    dip->di_subdir = strdup(path);
    if (dip->di_dirpath) {
	(void)sprintf(dirpath, "%s%c%s", dip->di_dirpath, DIRSEP, dip->di_subdir);
    } else {
	(void)sprintf(dirpath, "%s", dip->di_subdir);
    }
    if (dip->di_mode == WRITE_MODE) {
	status = create_directory(dip, dirpath);
	if (status == FAILURE) {
	    if (processing_subdir_flag) {
		--dip->di_subdir_number;
	    } else {
		--dip->di_subdir_depth;
	    }
	    return (FAILURE);
	}
    }
    return (SUCCESS);
}

/*
 * process_next_file() - Process the next file (with files= option).
 *
 * Inputs:
 *	dip = The device information pointer.
 *
 * Return Value:
 *	Returns SUCCESS/FAILURE = Next File Ready / Preparation Failed.
 */
int
process_next_file(struct dinfo *dip)
{
    int status;

    if ( dip->di_output_file && (dip->di_mode == READ_MODE) ) {
	/* Reopen a file written during the write pass. */
	status = (*dip->di_funcs->tf_reopen_file)(dip, dip->di_oflags);
    } else {
	int oflags = 0;
	/*
	 * Handle case where file never got created in previous passes.
	 */
	if ( (dip->di_files_written >= dip->di_max_files_written) && dip->di_pass_count ) {
	    oflags = O_CREAT;	/* Add flag to force initial creation. */
	}
	status = (*dip->di_funcs->tf_open)(dip, (dip->di_oflags | oflags));
#if !defined(WIN32)
	/*
	 * Note: Special handling here, to avoid excessive errors during cleanup!
	 *	 Assumes this is the first file being created in the directory.
	 */
	if ( (status == FAILURE) && (errno == ENAMETOOLONG) && dip->di_subdir_depth) {
	    dip->di_subdir_depth--;	/* Assume we've gone too deep! */
	    (void)remove_current_directory(dip);
	}
#endif /* !defined(WIN32) */
    }
    if (status == FAILURE) return (status);

    /*
     * Reset counters in preparation for the next file.
     */
    if (dip->di_mode == READ_MODE) {
	dip->di_fbytes_read = (large_t) 0;
	dip->di_records_read = (large_t) 0;
    } else {
	dip->di_fbytes_written = (large_t) 0;
	dip->di_records_written = (large_t) 0;
    }

    if (!dip->di_user_pattern) {
	/* Use a different pattern for each file. */
        dip->di_pattern = data_patterns[(dip->di_pattern_index + dip->di_file_number) % npatterns];
        if (dip->di_pattern_buffer) copy_pattern (dip->di_pattern, dip->di_pattern_buffer);
        if (dip->di_debug_flag) {
            Printf ("Using data pattern 0x%08x for file number %u\n",
                    dip->di_pattern, (dip->di_file_number + 1));
        }
    }
    /*
     * Note: We cannot do this per file per pass, since then we have no way to
     * re-read a set of files for a particular pass. Uniqueness per file needs
     * to come from a prefix, at least until block tags (btags) are implemented.
     */
#if 0
     else if (dip->di_iot_pattern && dip->di_unique_pattern) {
	/* Factor the file number into the IOT pattern for uniqueness. */
	dip->di_iot_seed_per_pass = (dip->di_iot_seed * ((dip->di_pass_count + 1) + dip->di_file_number) );
	if (dip->di_debug_flag) {
            Printf ("Using IOT seed 0x%08x for file number %u\n",
                    dip->di_iot_seed_per_pass, (dip->di_file_number + 1));
	}
    }
#endif
    /* This is very important for memory mapped files! */
    (void)(*dip->di_funcs->tf_start_test)(dip);
    return(status);
}

/************************************************************************
 *									*
 * open_file() - Open an input/output file for read/write.		*
 *									*
 * Description:								*
 *	This function does the default (generic) open processing.	*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *		oflags = The device/file open flags.			*
 *									*
 * Return Value:							*
 *		Returns 0 / -1 = SUCCESS / FAILURE.			*
 *									*
 ************************************************************************/
int
open_file (struct dinfo *dip, int oflags)
{
    char *file = dip->di_dname;
    int status = SUCCESS;
#if defined(WIN32)
    DWORD CreationDisposition = 0;
    DWORD FileAttributes = 0;
#endif /* defined(WIN32) */

    if (dip->di_open_delay) {			/* Optional open delay.	*/
	mySleep(dip, dip->di_open_delay);
    }
    /*
     * TODO: Move this to per file initialization function!
     */
    dip->di_end_of_file = FALSE;
    dip->di_end_of_media = FALSE;
    dip->di_end_of_logical = FALSE;
    dip->di_beginning_of_file = FALSE;

    dip->di_errno = 0;
    dip->di_offset = 0L;
    dip->di_position = 0;
    dip->di_lba = 0;

    if ( !dip->di_retrying		           &&
	 ((dip->di_dtype->dt_dtype == DT_MMAP) ||
	  (dip->di_dtype->dt_dtype == DT_REGULAR)) &&
	 (dip->di_dirpath || dip->di_subdir || dip->di_file_limit) ) {
	file = make_file_name(dip);
    }

    if ( (strlen(file) == 1) && (*file == '-') ) {
#if defined(WIN32)
	if (hazard_flag) {
	    Fprintf("option '-' not supported\n");
	    exit(FATAL_ERROR);
	}
#endif /* defined(WIN32) */
	if (dip->di_debug_flag) {
	    Printf ("Dup'ing standard %s...\n",
		(dip->di_ftype == INPUT_FILE) ? "input" : "output");
	}
	if (dip->di_ftype == INPUT_FILE) {
	    dip->di_stdin_flag = TRUE;
#if defined(WIN32)
	    dip->di_fd = GetStdHandle(STD_INPUT_HANDLE);
#else /* !defined(WIN32) */
	    dip->di_fd = dup (fileno(stdin));
#endif /* defined(WIN32) */
	} else {
	    ofp = efp; 		/* Redirect output to stderr. */
	    dip->di_stdout_flag = TRUE;
#if defined(WIN32)
	    dip->di_fd = GetStdHandle(STD_OUTPUT_HANDLE);
#else /* !defined(WIN32) */
	    dip->di_fd = dup (fileno(stdout));
#endif /* defined(WIN32) */
	    dip->di_verify_flag = FALSE;
	}
	if (dip->di_fd < 0) {
#if defined(WIN32)
	    report_error (dip, "GetStdHandle", TRUE);
#else /* !defined(WIN32) */
	    Fprintf ("dup -> ");
	    report_error (dip, file, TRUE);
#endif /* defined(WIN32) */
	    status = FAILURE;
	}
    } else {
#if defined(__WIN32__)
	oflags |= O_BINARY;
#endif /* defined(__WIN32__) */
#if defined(WIN32)
	SetupWindowsFlags(dip, file, oflags, &CreationDisposition, &FileAttributes);
	oflags &= (GENERIC_READ | GENERIC_WRITE | FILE_APPEND_DATA); /* Clear other POSIX flags. */
#else /* !defined(WIN32) */
#  if !defined(SOLARIS) && defined(O_DIRECT)
	if ( (dip->di_mode == READ_MODE) && (dip->di_read_cache_flag == FALSE) ) {
	    oflags |= O_DIRECT;
	} else if ( (dip->di_mode == WRITE_MODE) && (dip->di_write_cache_flag == FALSE) ) {
	    oflags |= O_DIRECT;
	}
#  endif /* !defined(SOLARIS) */
#endif /* defined(WIN32) */

	dip->di_retry_count = 0;
retry:
	if (dip->di_debug_flag) {
#if defined(WIN32)
	    Printf("Opening %s file '%s', open flags = %#x, disposition = %#x, attributes = %#x...\n",
		    (dip->di_ftype == INPUT_FILE) ? "input" : "output",
	        					file, oflags, CreationDisposition, FileAttributes);
#else /* !defined(WIN32) */
	    Printf("Opening %s file '%s', open flags = %#o (%#x)...\n",
		    (dip->di_ftype == INPUT_FILE) ? "input" : "output",
							file, oflags, oflags);
#endif /* defined(WIN32) */
	}
	dip->di_oflags = oflags;
	if (dip->di_noprog_flag && optiming_table[OPEN_OP].opt_timing_flag) {
	    dip->di_optype = OPEN_OP;
	    dip->di_initiated_time = time((time_t *)0);
	}
	if (dip->di_ftype == INPUT_FILE) {
#if defined(WIN32)
	    dip->di_fd = CreateFile (file, oflags, (FILE_SHARE_READ | FILE_SHARE_WRITE),
				     NULL, CreationDisposition, FileAttributes, NULL);
#else /* !defined(WIN32) */
	    dip->di_fd = open (file, oflags);
#endif /* defined(WIN32) */
	} else {
#if defined(WIN32)
	    dip->di_fd = CreateFile (file, oflags, (FILE_SHARE_READ | FILE_SHARE_WRITE),
				     NULL, CreationDisposition, FileAttributes, NULL);
#else /* !defined(WIN32) */
	    dip->di_fd = open (file, oflags, 0666);
#endif /* defined(WIN32) */
	}
	if (dip->di_noprog_flag) {
	    dip->di_optype = NONE_OP;
	    dip->di_initiated_time = (time_t) 0;
	}
	if (dip->di_fd == NoFd) {
            char fmt[STRING_BUFFER_SIZE];
#if defined(WIN32)
	    if ( isFsFullOk(dip, "CreateFile()") ) return(FAILURE);
	    (void)sprintf(fmt, "CreateFile() -> %s", file);
#else /* !defined(WIN32) */
	    if ( isFsFullOk(dip, "open()") ) return(FAILURE);
	    (void)sprintf(fmt, "open -> %s", file);
#endif /* defined(WIN32) */
	    report_error (dip, fmt, TRUE);
	    if ( dip->di_retry_entries &&
		 is_retryable(dip, dip->di_errno) && retry_operation(dip) ) {
		goto retry;
	    }
            (void)ExecuteTrigger(dip, "open");
	    status = FAILURE;
	}
    }
    if ( (status != FAILURE) && dip->di_debug_flag) {
	Printf ("%s file '%s' successfully opened, fd = %d\n",
		(dip->di_ftype == INPUT_FILE) ? "Input" : "Output",
						file, dip->di_fd);
    }

#if defined(SOLARIS)
    if (status == SUCCESS) {
	if (dip->di_dio_flag				      		  	||
	    ((dip->di_mode == READ_MODE) && (dip->di_read_cache_flag == FALSE)) ||
	    ((dip->di_mode == WRITE_MODE) && (dip->di_write_cache_flag == FALSE)) ) {
	    status = SolarisDIO(dip, file, TRUE);
	} else if ( (dip->di_buffer_mode == BUFFERED_IO)			 ||
		    ((dip->di_mode == READ_MODE) && (dip->di_write_cache_flag == FALSE)) ||
		    ((dip->di_mode == WRITE_MODE) && (dip->di_read_cache_flag == FALSE)) ) {
	    status = SolarisDIO(dip, file, FALSE); /* For NFS, DIO is sticky! */
	}
    }
#endif /* defined(SOLARIS) */

#if defined(WIN32)
    if (status == SUCCESS) {
	status = HandleSparseFile(dip, FileAttributes);
    }
#endif /* defined(WIN32) */

    return (status);
}

/************************************************************************
 *									*
 * close_file() - Close an open file descriptor.			*
 *									*
 * Description:								*
 *	This function does the default (generic) close processing.	*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *									*
 * Return Value:							*
 *		Returns 0 / -1 = SUCCESS / FAILURE.			*
 *									*
 ************************************************************************/
int
close_file (struct dinfo *dip)
{
    char *file = dip->di_dname;
    int status = SUCCESS;

    if (dip->di_closing || (dip->di_fd == NoFd)) {
	return (status);		/* Closing or not open. */
    }

    dip->di_closing = TRUE;
    if (dip->di_close_delay) {			/* Optional close delay	*/
	mySleep(dip, dip->di_close_delay);
    }
    dip->di_retry_count = 0;
retry:
    if (dip->di_debug_flag) {
	Printf ("Closing file '%s', fd = %d...\n", file, dip->di_fd);
    }
    if (dip->di_noprog_flag && optiming_table[CLOSE_OP].opt_timing_flag) {
	dip->di_optype = CLOSE_OP;
	dip->di_initiated_time = time((time_t *)0);
    }
#if defined(WIN32)
    if ((CloseHandle (dip->di_fd)) == 0) {
        status = FAILURE;
    }
#else /* !defined(WIN32) */
    status = close (dip->di_fd);
#endif /* defined(WIN32) */
    if (dip->di_noprog_flag) {
	dip->di_optype = NONE_OP;
	dip->di_initiated_time = (time_t) 0;
    }
    if (status == FAILURE) {
	if (dip->di_cerrors_flag) {
#if defined(WIN32)
	    report_error (dip, "CloseHandle", TRUE);
#else /* !defined(WIN32) */
	    report_error (dip, "close", TRUE);
#endif /* defined(WIN32) */
	    if ( dip->di_retry_entries &&
		 is_retryable(dip, dip->di_errno) && retry_operation(dip) ) {
		goto retry;
	    }
            (void)ExecuteTrigger(dip, "close");
	} else if (dip->di_verbose_flag) {
#if defined(WIN32)
	    DWORD error = GetLastError();
	    Printf("Warning, close failed, errno = %d - %s\n", error, werror_msg(error));
#else /* !defined(WIN32) */
	    Printf("Warning, close failed, errno = %d - %s\n", errno, strerror(errno));
#endif /* defined(WIN32) */
	    Printf("Warning, ignoring close failure and continuing...\n");
	    status = SUCCESS;
	}
    }
    dip->di_fd = NoFd;
    dip->di_closing = FALSE;
    return (status);
}

/************************************************************************
 *									*
 * reopen_file() - Close and reopen file descriptor.			*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *		oflags = The device/file open flags.			*
 *									*
 * Return Value:							*
 *		Returns 0 / -1 = SUCCESS / FAILURE.			*
 *									*
 ************************************************************************/
int
reopen_file (struct dinfo *dip, int oflags)
{
    struct dtfuncs *dtf = dip->di_funcs;
    char *file = dip->di_dname;
    int status = SUCCESS;
    char fmt[STRING_BUFFER_SIZE];

#if defined(WIN32)
    DWORD CreationDisposition = 0;
    DWORD FileAttributes = 0;
    SetupWindowsFlags(dip, file, oflags, &CreationDisposition, &FileAttributes);
    if (CreationDisposition == OPEN_ALWAYS) {
	CreationDisposition = OPEN_EXISTING; /* File should already exist! */
    }
    oflags &= (GENERIC_READ | GENERIC_WRITE | FILE_APPEND_DATA); /* Clear other POSIX flags. */
#else /* !defined(WIN32) */
#  if !defined(SOLARIS) && defined(O_DIRECT)
	if ( (dip->di_mode == READ_MODE) && (dip->di_read_cache_flag == FALSE) ) {
	    oflags |= O_DIRECT;
	} else if ( (dip->di_mode == WRITE_MODE) && (dip->di_write_cache_flag == FALSE) ) {
	    oflags |= O_DIRECT;
	}
#  endif /* !defined(SOLARIS) */
#endif /* defined(WIND32) */

    if ( !dip->di_retrying		           &&
	 ((dip->di_dtype->dt_dtype == DT_MMAP)     ||
	  (dip->di_dtype->dt_dtype == DT_REGULAR)) &&
	 (dip->di_dirpath || dip->di_subdir || dip->di_file_limit) ) {
	file = make_file_name(dip);
    }

    /*
     * For stdin or stdout, do not attempt close/open.
     */
    if ( (strlen(file) == 1) && (*file == '-') ) return (status);

    /*
     * For tape, we must close & reopen to get to BOT,
     * an lseek() won't do the trick.
     */
    if (dip->di_fd != NoFd) {			/* If not already closed... */
	status = (*dtf->tf_close)(dip);
    }
    if (dip->di_open_delay) {			/* Optional open delay.	*/
	mySleep(dip, dip->di_open_delay);
    }

    dip->di_end_of_file = FALSE;
    dip->di_end_of_media = FALSE;
    dip->di_end_of_logical = FALSE;
    dip->di_beginning_of_file = FALSE;

    dip->di_errno = 0;
    dip->di_offset = 0L;
    dip->di_position = 0;
    dip->di_lba = 0;

#if defined(__WIN32__)
    oflags |= O_BINARY;
#endif /* defined(__WIN32__) */

    dip->di_retry_count = 0;
retry:
    if (dip->di_debug_flag) {
#if defined(WIN32)
	Printf ("Reopening %s file '%s', open flags = %#x, disposition = %#x, attributes = %#x...\n",
		(dip->di_ftype == INPUT_FILE) ? "input" : "output",
	        					file, oflags, CreationDisposition, FileAttributes);
#else /* !defined(WIN32) */
	Printf ("Reopening file '%s', open flags = %#o (%#x)...\n",
							file, oflags, oflags);
#endif /* defined(WIN32) */
    }

    dip->di_oflags = oflags;
    if (dip->di_noprog_flag && optiming_table[OPEN_OP].opt_timing_flag) {
	dip->di_optype = OPEN_OP;
	dip->di_initiated_time = time((time_t *)0);
    }
#if defined(WIN32)
    dip->di_fd = CreateFile (file, oflags, (FILE_SHARE_READ | FILE_SHARE_WRITE),
       			     NULL, CreationDisposition, FileAttributes, NULL);
#else /* !defined(WIN32) */
    dip->di_fd = open (file, oflags);
#endif /* defined(WIN32) */
    if (dip->di_noprog_flag) {
	dip->di_optype = NONE_OP;
	dip->di_initiated_time = (time_t) 0;
    }
    if (dip->di_fd == NoFd) {
#if defined(WIN32)
	if ( isFsFullOk(dip, "CreateFile()") ) return(FAILURE);
	(void)sprintf(fmt, "CreateFile() -> %s", file);
#else /* !defined(WIN32) */
	if ( isFsFullOk(dip, "open()") ) return(FAILURE);
	(void)sprintf(fmt, "open -> %s", file);
#endif /* defined(WIN32) */
	report_error (dip, fmt, TRUE);
	if ( dip->di_retry_entries &&
	     is_retryable(dip, dip->di_errno) && retry_operation(dip) ) {
	    goto retry;
	}
        (void)ExecuteTrigger(dip, "open");
	return (FAILURE);
    }

    if (dip->di_debug_flag) {
	Printf ("File '%s' successfully reopened, fd = %d\n",
						file, dip->di_fd);
    }

#if defined(SOLARIS)
    if (status == SUCCESS) {
	if (dip->di_dio_flag			       		 	        ||
	    ((dip->di_mode == READ_MODE) && (dip->di_read_cache_flag == FALSE)) ||
	    ((dip->di_mode == WRITE_MODE) && (dip->di_write_cache_flag == FALSE)) ) {
	    status = SolarisDIO(dip, file, TRUE);
	} else if ( (dip->di_buffer_mode == BUFFERED_IO)			 ||
		    ((dip->di_mode == READ_MODE) && (dip->di_write_cache_flag == FALSE)) ||
		    ((dip->di_mode == WRITE_MODE) && (dip->di_read_cache_flag == FALSE)) ) {
	    status = SolarisDIO(dip, file, FALSE); /* For NFS, DIO is sticky! */
	}
    }
#endif /* defined(SOLARIS) */

#if defined(WIN32)
    if (status == SUCCESS) {
	status = HandleSparseFile(dip, FileAttributes);
    }
#endif /* defined(WIN32) */

    return (status);
}

/************************************************************************
 *									*
 * initialize() - Do the default program initialization.		*
 *									*
 * Description:								*
 *	This function does the default (generic) test initialization.	*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *									*
 * Outputs:	Always SUCCESS right now.				*
 *									*
 ************************************************************************/
int
initialize (struct dinfo *dip)
{
    if (!dip->di_data_buffer) {
	dip->di_base_buffer = dip->di_data_buffer =
	    malloc_palign(dip->di_data_size, dip->di_align_offset);
    }
    return (SUCCESS);
}

/************************************************************************
 *									*
 * init_file() - Initial file processing.				*
 *									*
 * Description:								*
 *	This function is used to process options before starting tests.	*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *									*
 * Outputs:	Always SUCCESS right now.				*
 *									*
 ************************************************************************/
int
init_file (struct dinfo *dip)
{
    int status = SUCCESS;
    HANDLE fd = dip->di_fd;

    /*
     * If the lba option is specified, and we're a disk device,
     * then setup a file position to be seek'ed to below.
     */
    if ( dip->di_lbdata_addr && !dip->di_user_position &&
	 ((dip->di_dtype->dt_dtype == DT_DISK) ||
	  (dip->di_dtype->dt_dtype == DT_BLOCK)) ) {
	dip->di_file_position = make_position(dip, dip->di_lbdata_addr);
	if ( (dip->di_io_type == RANDOM_IO) && (dip->di_rdata_limit <= (large_t)dip->di_file_position) ) {
	    LogMsg (efp, logLevelCrit, 0,
		    "Please specify a random data limit > lba file position!\n");
	    exit (FATAL_ERROR);
	}
    }

    /*
     * Seek to specified offset (if requested).
     */
    if (dip->di_file_position) {
	dip->di_last_position = set_position (dip, dip->di_file_position, FALSE);
    }

    /*
     * Seek to specified record (if requested).
     */
    if (dip->di_seek_count) {
	dip->di_last_position = seek_file(dip, fd, dip->di_seek_count, dip->di_block_size, SEEK_CUR);
	if (dip->di_last_position == (OFF_T) FAILURE) return (FAILURE);
	show_position (dip, dip->di_last_position);
    }

    /*
     * Allow seek/position options with copy/verify modes.
     */ 
    if ( dip->di_random_access && 
	 (dip->di_io_mode == COPY_MODE) || (dip->di_io_mode == VERIFY_MODE) ) {
	if (dip->di_ofile_position) {
	    dip->di_last_position = set_position (dip->di_output_dinfo, dip->di_ofile_position, FALSE);
	} else {
	    dip->di_last_position = set_position(dip->di_output_dinfo, dip->di_last_position, FALSE);
	}
	if (dip->di_last_position == (OFF_T) FAILURE) return (FAILURE);
	show_position (output_dinfo, dip->di_last_position);
    }

    /*
     * Skip over input record(s) (if requested).
     */
    if (dip->di_skip_count) {
	status = skip_records (dip, dip->di_skip_count, dip->di_data_buffer, dip->di_block_size);
	if (dip->di_debug_flag && (status != FAILURE)) {
	    Printf ("Successfully skipped %d records.\n", dip->di_skip_count);
	}
    }
    return (status);
}

/************************************************************************
 *									*
 * flush_file() - Flush file data to disk.				*
 *									*
 * Description:								*
 *	This function is used to flush the file data to disk after the	*
 * write pass of each test.						*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *									*
 * Return Value:							*
 *		Returns SUCCESS / FAILURE = Ok / Sync Failed.		*
 *									*
 ************************************************************************/
int
flush_file (struct dinfo *dip)
{
    int status = SUCCESS;
    HANDLE fd = dip->di_fd;

    if (fd == NoFd) return(status);
    /*
     * Ensure data is sync'ed to disk file.
     */
    if ( dip->di_fsync_flag == TRUE ) {
	dip->di_flushing = TRUE;
	dip->di_retry_count = 0;
retry:
	if (dip->di_debug_flag) {
	    Printf ("Flushing data on record #%u to file '%s'...\n",
		    dip->di_records_written, dip->di_dname);
	}
	if (dip->di_noprog_flag && optiming_table[FSYNC_OP].opt_timing_flag) {
	    dip->di_optype = FSYNC_OP;
	    dip->di_initiated_time = time((time_t *)0);
	}
#if defined(_QNX_SOURCE)
	if ((status = fcntl (fd, F_SETFL, O_DSYNC)) < 0) {
 	    report_error(dip, "F_SETFL", TRUE);
	}
#else /* !defined(_QNX_SOURCE) */
#  if defined(WIN32)
	status = SUCCESS;
	if(!FlushFileBuffers(fd)) {
	    status = FAILURE;
	    report_error (dip, "FlushFileBuffers", TRUE);
	}
#  else /* !defined(WIN32) */
	if ((status = fsync ((int)fd)) < 0) {	/* Force data to disk. */
	    report_error (dip, "fsync", TRUE);
	}
#  endif /* defined(WIN32) */
	if (dip->di_noprog_flag) {
	    dip->di_optype = NONE_OP;
	    dip->di_initiated_time = (time_t) 0;
	}
#endif /* !defined(_QNX_SOURCE) */
	if ( (status == FAILURE) && dip->di_retry_entries &&
	     is_retryable(dip, dip->di_errno) && retry_operation(dip) ) {
	    goto retry;
	}
	dip->di_flushing = FALSE;
	if (status) (void)ExecuteTrigger(dip, "fsync");
    }
    return (status);
}

/************************************************************************
 *									*
 * read_file - Read and optionally verify data in the test file.	*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *									*
 * Return Value:							*
 *		Returns SUCCESS/FAILURE = Ok / Error.			*
 *									*
 ************************************************************************/
int
read_file (struct dinfo *dip)
{
    int status;
    struct dtfuncs *dtf = dip->di_funcs;
    u_int files_read = 0;

    dip->di_offset = make_offset(dip, dip->di_lbdata_addr);

    /*
     * Loop reading/comparing data until we've detected end of file
     * or we've reached the data limit or record limit.
     */
    do {					/* Read/compare data. */
	if (dip->di_file_limit && dip->di_fsincr_flag) {
	    dip->di_record_limit = (dip->di_files_read + 1);
	}
	dip->di_fbytes_read = (large_t) 0;
	dip->di_records_read = (large_t) 0;
#if defined(TAPE)
read_some_more:
#endif
	if ((status = (*dtf->tf_read_data)(dip)) == FAILURE) break;
	if (dip->di_terminating) break;

	if (dip->di_volumes_flag && (dip->di_multi_volume >= dip->di_volume_limit) &&
		  (dip->di_volume_records >= dip->di_volume_records)) {
	    break;
	}
#if defined(TAPE)
	/*
	 * Handle reading multiple disk/tapes and multiple files.
	 */
	if (dip->di_end_of_file && dip->di_multi_flag &&
	    (dip->di_dtype->dt_dtype == DT_TAPE) &&
	    ((dip->di_records_read != dip->di_record_limit) &&
	     (dip->di_fbytes_read != dip->di_data_limit)) ) {
	    /* Check for logical end of tape. */
	    (void) (*dtf->tf_cancel_reads)(dip);
	    if ((status = read_eom(dip)) != SUCCESS) break;
	    if ( !dip->di_end_of_file ) goto read_some_more;
	}
#endif /* defined(TAPE) */
	if (dip->di_end_of_file) {
	    files_read++;
	    dip->di_files_read++;
	}
	if ( (dip->di_dtype->dt_dtype == DT_MMAP) ||
	     (dip->di_dtype->dt_dtype == DT_REGULAR) ) {
	    /* Cludge Alert: EOF may not be set with exact data reads. */
	    if (!dip->di_end_of_file) {
		files_read++;
		dip->di_files_read++;
	    }
	    if (dip->di_output_file) {
		if ( (dip->di_dbytes_read == dip->di_last_dbytes_written) ||
		     (dip->di_files_read >= dip->di_last_files_written) ) {
		    if (dip->di_debug_flag || dip->di_eDebugFlag || dip->di_fDebugFlag) {
			if (dip->di_multiple_files) {
			    Printf("DEBUG: File name: %s\n", dip->di_dname);
			}
			Printf("DEBUG: Finished reading files/data after file #%u, bytes read " FUF ", last written " FUF "\n",
			       dip->di_files_read, dip->di_dbytes_read, dip->di_last_dbytes_written);
		    }
		    break;	/* Don't read more files or data than were written (possible ENOSPC). */
		}
	    }
	}

	/*
	 * Don't exceed the max data or files (if specified).
	 */
	if ( dip->di_max_data && (dip->di_maxdata_read >= dip->di_max_data) ) {
	    break;
	}
	if ( dip->di_max_files && (dip->di_files_read == dip->di_max_files) ) {
	    break;
	}
	if ( ( (dip->di_dtype->dt_dtype == DT_TAPE)	 ||
	       (dip->di_dtype->dt_dtype == DT_MMAP)	 ||
	       (dip->di_dtype->dt_dtype == DT_REGULAR) ) &&
	     (dip->di_file_limit && (files_read < dip->di_file_limit)) ) {
	    /*
	     * Normally, we handle EOF conditions on the fly, but when lbdata
	     * or the IOT pattern is enabled, we must cancel outstanding I/O's
	     * so that aio_offset (for LBA) is accurate on subsequent files.
	     */
	    if ((dip->di_lbdata_flag || dip->di_iot_pattern) && (dip->di_dtype->dt_dtype == DT_TAPE)) {
		(void) (*dtf->tf_cancel_reads)(dip);
	    }
	    /*
	     * An exact record or data limit keeps us short of file marks,
	     * so we read and check for an expected end of file here.
	     */
	    if (!dip->di_end_of_file) {
#if defined(TAPE)
		if (dip->di_dtype->dt_dtype == DT_TAPE) {
# if defined(__NUTC__) || defined(__QNXNTO__) || defined(AIX) || defined(WIN32)
		    if ((status = read_eof(dip)) != SUCCESS) break;
# else /* !defined(__NUTC__) && !defined(__QNXNTO__) && !defined(AIX) */
		    status = DoForwardSpaceFile (dip, (daddr_t) 1);
		    if (status != SUCCESS) break;
# endif /* defined(__NUTC__) || defined(__QNXNTO__) || defined(AIX) || defined(WIN32) */
		}
#endif /* defined(TAPE) */
	    }
	    if (files_read < dip->di_file_limit) {
		dip->di_file_number++;
		dip->di_end_of_file = FALSE;
		if ( (dip->di_dtype->dt_dtype == DT_MMAP) ||
		     (dip->di_dtype->dt_dtype == DT_REGULAR) ) {
		    if ( (status = end_file_processing(dip)) == FAILURE) break;
		    status = process_next_file(dip);
		    if (status == FAILURE) break;
		} else {
		    dip->di_fbytes_read = (large_t) 0;
		    dip->di_records_read = (large_t) 0;
		}
		continue;
	    }
	} /* End of file limit check. */
	/*
	 * Process Multiple Directories.
	 */
	if ( (dip->di_dtype->dt_dtype == DT_MMAP) ||
	     (dip->di_dtype->dt_dtype == DT_REGULAR) ) {
	    if ( (status = end_file_processing(dip)) == FAILURE) break;
	    status = process_next_subdir(dip);
	    if (status == SUCCESS) {
		status = process_next_file(dip);
		if (status == FAILURE) break;
		files_read = 0;
		continue;
	    } else {
		break;
	    }
	}
    } while ( !dip->di_end_of_file && (dip->di_error_count < dip->di_error_limit) &&
	      (dip->di_records_read < dip->di_record_limit) &&
	      (dip->di_fbytes_read < dip->di_data_limit) );

    /*
     * We cancel the reads here incase multiple files were being
     * read, so reads continue while we process each file mark.
     */
    if (dip->di_fd != NoFd) {
	(void) (*dtf->tf_cancel_reads)(dip);
    }
    return (status);
}

/************************************************************************
 *									*
 * write_file() - Write data to the test file/device.			*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *									*
 * Return Value:							*
 *		Returns SUCCESS/FAILURE = Ok/Error.			*
 *									*
 ************************************************************************/
int
write_file (struct dinfo *dip)
{
    int status;
    struct dtfuncs *dtf = dip->di_funcs;
    u_int files_written = 0;

    dip->di_offset = make_offset(dip, dip->di_lbdata_addr);

    /*
     * Initialize the data buffer with a pattern if compare is
     * disabled, so we honor the user specified pattern.
     */
    if ((dip->di_io_mode == TEST_MODE) && !dip->di_compare_flag) {
	if (dip->di_iot_pattern) {
	    u_int32 lba = (u_int32) make_lbdata (dip, dip->di_offset);
	    (void)init_iotdata (dip, dip->di_data_buffer, dip->di_block_size, lba, dip->di_lbdata_size);
	} else {
	    fill_buffer (dip, dip->di_data_buffer, dip->di_block_size, dip->di_pattern);
	}
    }

    /*
     * Loop writing data until end of media or data limit reached.
     */
    do {					/* Write data pattern.	*/
	if (dip->di_file_limit && dip->di_fsincr_flag) {
	    dip->di_record_limit = (dip->di_files_written + 1);
	}
	if (dip->di_raw_flag) {
	    dip->di_fbytes_read = (large_t) 0;
	    dip->di_records_read = (large_t) 0;
	}
	dip->di_fbytes_written = (large_t) 0;
	dip->di_records_written = (large_t) 0;
	dip->di_last_write_size = (size_t) 0;
	dip->di_last_write_attempted = (size_t) 0;
	dip->di_last_write_offset = (OFF_T) 0;
	if ((status = (*dtf->tf_write_data)(dip)) == FAILURE) break;
	if (dip->di_terminating) break;

	/*
	 * Handle writing multiple disk/tape files.
	 */
	dip->di_files_written++, files_written++;

	if (dip->di_volumes_flag && (dip->di_multi_volume >= dip->di_volume_limit) &&
		  (dip->di_volume_records >= dip->di_volume_records)) {
	    break;
	}

	/*
	 * Don't exceed the max data or files (if specified).
	 */
	if ( dip->di_max_data && (dip->di_maxdata_written >= dip->di_max_data) ) {
	    break;
	}
	if ( dip->di_max_files && (dip->di_files_written == dip->di_max_files) ) {
	    break;
	}
	if ( ( (dip->di_dtype->dt_dtype == DT_TAPE) ||
	       (dip->di_dtype->dt_dtype == DT_MMAP) ||
	       (dip->di_dtype->dt_dtype == DT_REGULAR) ) &&
	     (dip->di_file_limit && (files_written < dip->di_file_limit)) ) {
	    /*
	     * For tapes, write a file mark for all but last file.
	     * The last file mark(s) are written when closing tape.
	     */
#if !defined(__NUTC__) && !defined(__QNXNTO__) && !defined(AIX) && !defined(WIN32) && defined(TAPE)
            if ( (dip->di_dtype->dt_dtype == DT_TAPE) && (files_written + 1) < dip->di_file_limit) {
                status = DoWriteFileMark (dip, (daddr_t) 1);
                if (status != SUCCESS) break;
            }
#endif /* !defined(__NUTC__) && !defined(__QNXNTO__) && !defined(AIX) && !defined(WIN32) && defined(TAPE) */
            if (files_written < dip->di_file_limit) {
                dip->di_file_number++;
                if ( (dip->di_dtype->dt_dtype == DT_MMAP) ||
		     (dip->di_dtype->dt_dtype == DT_REGULAR) ) {
		    if (dip->di_no_space_left) break;
		    if ( (status = end_file_processing(dip)) == FAILURE) break;
                    status = process_next_file(dip);
		    if (status == FAILURE) break;
                } else {
		    dip->di_fbytes_written = (large_t) 0;
		    dip->di_records_written = (large_t) 0;
		}
                continue;           	/* Write the next file. */
            }
        } /* End of file limit check. */
	/*
	 * Process Multiple Directories.
	 */
	if ( (dip->di_dtype->dt_dtype == DT_MMAP) ||
	     (dip->di_dtype->dt_dtype == DT_REGULAR) ) {
	    if (dip->di_no_space_left) break;
	    if ( (status = end_file_processing(dip)) == FAILURE) break;
	    status = process_next_subdir(dip);
	    if (status == SUCCESS) {
		status = process_next_file(dip);
		if (status == FAILURE) break;
		files_written = 0;
		continue;
	    } else {
		break;
	    }
	}
    } while ( !dip->di_end_of_file && (dip->di_error_count < dip->di_error_limit) &&
              (dip->di_records_written < dip->di_record_limit) &&
              (dip->di_fbytes_written < dip->di_data_limit) );

    return (status);
}

/************************************************************************
 *									*
 * validate_opts() - Generic Validate Option Test Criteria.		*
 *									*
 * Description:								*
 *	This function verifies the options specified are valid for the	*
 * test criteria selected.						*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *									*
 * Return Value:							*
 *		Returns SUCESS / FAILURE = Valid / Invalid Options.	*
 *									*
 ************************************************************************/
int
validate_opts (struct dinfo *dip)
{
    if (dip->di_bypass_flag) return(SUCCESS);
    if (dip->di_dtype == NULL) return(SUCCESS);

    if (dip->di_fd == NoFd) {
	/*
	 * Validation checks *before* the device is open.
	 */
	if (dip->di_min_size && (dip->di_dtype->dt_dtype != DT_REGULAR)) {
	    size_t value;
	    char *emsg = NULL;
	    if (dip->di_dsize > dip->di_min_size) {
		value = dip->di_min_size; emsg = "min size";
	    } else if (dip->di_dsize > dip->di_max_size) {
		value = dip->di_max_size; emsg = "max size";
	    }
	    if (emsg) {
		LogMsg (efp, logLevelCrit, 0,
			"Please specify %s (%u) greater than device size %u of bytes.\n",
			emsg, value, dip->di_dsize);
		return(FAILURE);
	    }
	}
	if (dip->di_variable_flag && ((dip->di_min_size == 0) || (dip->di_max_size == 0)) ) {
	    LogMsg (efp, logLevelCrit, 0,
		    "Please specifiy a min= and max= value with variable I/O sizes!\n");
	    return(FAILURE);
	}
#if defined(O_TRUNC)
	if ( (dip->di_ftype == OUTPUT_FILE) &&
	     (dip->di_num_slices && (dip->di_wopen_flags & O_TRUNC)) ) {
	    if (dip->di_verbose_flag) {
		Printf("Warning: Disabling file truncate flag, not valid with multiple slices!\n");
	    }
	    dip->di_wopen_flags &= ~O_TRUNC;
	}
#endif /* defined(O_TRUNC) */
    } else {
	/*
	 * Validation checks *after* the device is open.
	 */
	if ( (dip->di_dtype->dt_dtype == DT_REGULAR) &&
	     (dip->di_ftype == OUTPUT_FILE)          &&
	     (dip->di_num_slices && (dip->di_dispose_mode != KEEP_FILE)) ) {
	    dip->di_dispose_mode = KEEP_FILE;
	    if (dip->di_verbose_flag) {
		Printf("Warning: Multiple slices to same file, setting dispose=keep!\n");
	    }
	}
	if ( (dip->di_dtype->dt_dtype == DT_REGULAR) &&
	     (dip->di_ftype == OUTPUT_FILE)          &&
	     (dip->di_num_slices && dip->di_delete_per_pass) ) {
	    if (dip->di_verbose_flag) {
		Printf("Warning: Disabling delete per pass flag, not valid with multiple slices!\n");
	    }
	    dip->di_delete_per_pass = FALSE;
	}

	if ( (dip->di_io_dir == REVERSE) || (dip->di_io_type == RANDOM_IO) ) {
	    if ( !dip->di_random_access ) {
		LogMsg (efp, logLevelCrit, 0,
			"Random I/O or reverse direction, is only valid for random access device!\n");
		return(FAILURE);
	    }
	    if ( (dip->di_dtype->dt_dtype == DT_REGULAR) && !dip->di_user_capacity ) {
		LogMsg (efp, logLevelCrit, 0,
			"Please specify a data limit, record count, or capacity for random I/O.\n");
		return(FAILURE);
	    }
	}
	/*
	 * Check for when non-modulo request sizes are not permitted.
	 */
#if defined(__linux__)
	if ( (dip->di_dtype->dt_dtype == DT_REGULAR) && (dip->di_oflags & O_DIRECT) ) {
	    
	    /* Note: This may be true for other OS's too, but I'm not sure which! */
	    if (dip->di_variable_flag && !dip->di_fsalign_flag) {
		if (dip->di_verbose_flag) {
		    Printf("Warning: Enabling FS alignment for variable I/O sizes!\n");
		}
		dip->di_fsalign_flag = TRUE;	/* Avoid false errors due to alignment! */
	    }
	    /*
	     * This is a bandaide to override automation *not* smart about file systems.
	     * Note: We're adjusting a few things we can do safely, but we can't do all!
	     * Also Note: Many other sanity checks are missed by Mickey Mousing this here!
	     */ 
	    if (dip->di_filesystem_type && EQS(dip->di_filesystem_type, "xfs")) {
		if (dip->di_device_size < XFS_DIO_BLOCK_SIZE) {
		    if (dip->di_verbose_flag) {
			Printf("Warning: Setting the device size to %u for XFS filesystem!\n",  XFS_DIO_BLOCK_SIZE);
		    }
		    dip->di_device_size = dip->di_dsize = XFS_DIO_BLOCK_SIZE;
		}
		if (dip->di_min_size < dip->di_dsize) {
		    if (dip->di_verbose_flag) {
			Printf("Warning: Setting the minimum block size to %u for XFS filesystem!\n", dip->di_dsize);
		    }
		    dip->di_min_size = dip->di_dsize;
		}
		if ( (!dip->di_variable_flag && dip->di_incr_count) && (dip->di_incr_count % dip->di_dsize) ) {
		    if (dip->di_verbose_flag) {
			Printf("Warning: Setting the incrment count to %u for XFS filesystem!\n", dip->di_dsize);
		    }
		    dip->di_incr_count = dip->di_dsize;
		}
	    }
	}
        if ( (dip->di_random_access && 
	      (dip->di_dtype->dt_dtype != DT_REGULAR)) || (dip->di_oflags & O_DIRECT) ) {
#elif defined(WIN32)
	if ( (dip->di_random_access && (dip->di_dtype->dt_dtype != DT_REGULAR)) || dip->di_dio_flag) {
#else /* all other OS's */
	if (dip->di_random_access && (dip->di_dtype->dt_dtype != DT_REGULAR) ) {
#endif
	    size_t value;
	    char *emsg = NULL;
	    if (dip->di_block_size % dip->di_dsize) {
		value = dip->di_block_size; emsg = "block size";
	    } else if (dip->di_min_size && (dip->di_min_size % dip->di_dsize)) {
		value = dip->di_min_size; emsg = "min size";
	    } else if (dip->di_max_size && (dip->di_max_size % dip->di_dsize)) {
		value = dip->di_max_size; emsg = "max size";
	    } else if ( (!dip->di_variable_flag && dip->di_incr_count) &&
			(dip->di_incr_count % dip->di_dsize) ) {
		value = dip->di_incr_count; emsg = "incr count";
	    }
	    if (emsg) {
		LogMsg (efp, logLevelCrit, 0,
			"Please specify a %s (%u) modulo the device size of %u bytes!\n",
			emsg, value, dip->di_dsize);
		return(FAILURE);
	    }
	}
	/*
	 * Don't allow non-modulo data limits, since most disk drivers will error 
	 * when the request size is NOT modulo the sector size or DIO is enabled.
	 * For example: 'ReadFile', errno = 87 - The parameter is incorrect.
	 */
#if defined(__linux__)
	/* Note: This is NOT true for NFS and DIO, but how to handle better? */
        if ( (dip->di_dtype->dt_dtype == DT_DISK) || (dip->di_oflags & O_DIRECT) ) {
#elif defined(WIN32)
	if ((dip->di_dtype->dt_dtype == DT_DISK) || dip->di_dio_flag) {
#else /* all other OS's */
	if (dip->di_dtype->dt_dtype == DT_DISK) {
#endif
	    if (dip->di_data_limit &&
		(dip->di_data_limit != INFINITY) && (dip->di_data_limit % dip->di_dsize) ) {
		LogMsg (efp, logLevelCrit, 0,
			"Please specify a data limit (" LUF ") modulo the device size of %u bytes!\n",
			dip->di_data_limit, dip->di_dsize);
		return(FAILURE);
	    }
	}
#if defined(__linux__)
        if ( (dip->di_oflags & O_DIRECT) && (dip->di_align_offset || dip->di_rotate_flag) ) {
	    LogMsg (efp, logLevelWarn, 0,
		    "Linux does NOT support unaligned offsets with direct I/O, disabling misalignments!\n");
	    dip->di_align_offset = 0;
	    dip->di_rotate_flag = FALSE;
	}
#endif /* defined(__linux__) */
    }
    return(SUCCESS);
}

/*
 * SetupBufferingMode() - Setups up the File System Buffering Mode.
 *
 * Inputs:
 * 	dip = Pointer to device information.
 * 	oflags = Pointer to the open flags.
 *
 * Return Value:
 *	void
 */
void
SetupBufferingMode(dinfo_t *dip, int *oflags)
{
    if (dip->di_bufmode_count == 0) return;

    dip->di_buffer_mode = dip->di_buffer_modes[dip->di_bufmode_index];

    switch (dip->di_buffer_mode) {

	case BUFFERED_IO:
	    if (dip->di_debug_flag) {
		Printf("Setting buffering mode to: buffered (cache reads and writes)\n");
	    }
	    dip->di_bufmode_type = "buffered";
#if defined(SOLARIS) || defined(WIN32) || !defined(O_DIRECT)
    	    dip->di_dio_flag = FALSE;
#else /* !defined(SOLARIS) && !defined(WIN32) */
	    *oflags &= ~(O_DIRECT);
#endif /* defined(SOLARIS) || defined(WIN32) */
	    dip->di_read_cache_flag = TRUE;
	    dip->di_write_cache_flag = TRUE;
	    break;

	case UNBUFFERED_IO:
	    if (dip->di_debug_flag) {
		Printf("Setting buffering mode to: unbuffered (aka direct I/O)\n");
	    }
	    dip->di_bufmode_type = "unbuffered";
#if defined(SOLARIS) || defined(WIN32) || !defined(O_DIRECT)
    	    dip->di_dio_flag = TRUE;
#else /* !defined(SOLARIS) && !defined(WIN32) */
	    *oflags |= O_DIRECT;
#endif /* defined(SOLARIS) || defined(WIN32) */
	    dip->di_read_cache_flag = TRUE;
	    dip->di_write_cache_flag = TRUE;
	    break;

	case CACHE_READS:
	    if (dip->di_debug_flag) {
		Printf("Setting buffering mode to: cache reads\n");
	    }
	    dip->di_bufmode_type = "cache reads";
#if defined(SOLARIS) || defined(WIN32) || !defined(O_DIRECT)
    	    dip->di_dio_flag = FALSE;
#else /* !defined(SOLARIS) && !defined(WIN32) */
	    *oflags &= ~(O_DIRECT);
#endif /* defined(SOLARIS) || defined(WIN32) */
	    dip->di_read_cache_flag = TRUE;
	    dip->di_write_cache_flag = FALSE;
	    break;

	case CACHE_WRITES:
	    if (dip->di_debug_flag) {
		Printf("Setting buffering mode to: cache writes\n");
	    }
	    dip->di_bufmode_type = "cache writes";
#if defined(SOLARIS) || defined(WIN32) || !defined(O_DIRECT)
    	    dip->di_dio_flag = FALSE;
#else /* !defined(SOLARIS) && !defined(WIN32) */
	    *oflags &= ~(O_DIRECT);
#endif /* defined(SOLARIS) || defined(WIN32) */
	    dip->di_read_cache_flag = FALSE;
	    dip->di_write_cache_flag = TRUE;
	    break;
	default:
	    LogMsg (efp, logLevelError, 0,
		    "Programming error, illegal buffer mode: %d\n",  dip->di_buffer_mode);
	    exit (FATAL_ERROR);
	    break;
    }
    if (++dip->di_bufmode_index == dip->di_bufmode_count) {
	dip->di_bufmode_index = 0;
    }
    return;
}

#if defined(SOLARIS)
/*
 * SolarisDIO - Enable or disable Direct I/O (DIO) for Solaris FS's.
 *
 * Description:
 *      Sadly, Solaris is an odd ball when it comes to enabling Direct I/O.
 * Solaris does NOT support O_DIRECT like other Unix systems.  Instead, if
 * using UFS, DIO is enabled via the directio() API after the file is open.
 * Furthermore, if Veritas VxFS is used, the directio() API is not supported,
 * so a vendor unique IOCTL must be used to enable DIO.
 *
 * Inputs:
 *      dip = The device information pointer.
 *      file = The file name we're working on.
 *	flag = Flag to control enable/disable.
 *
 * Return Value:
 *      Returns SUCCESS (if enabled) or FAILURE (couldn't enable DIO).
 */
int
SolarisDIO(struct dinfo *dip, char *file, bool flag)
{
    char fmt[STRING_BUFFER_SIZE];
    char *dio_msg = (flag) ? "Enabling" : "Disabling";
    int status;

    if (dip->di_debug_flag) {
        Printf("%s direct I/O via directio() API...\n", dio_msg);
    }
    if ( (status = directio(dip->di_fd, (flag) ? DIRECTIO_ON : DIRECTIO_OFF)) < 0) {
        if (errno == ENOTTY) {
	    if (dip->di_debug_flag || dip->di_fDebugFlag) {
                Printf("%s direct I/O via VX_SETCACHE/VX_DIRECT IOCTL...\n", dio_msg);
            }
            if ( (status = ioctl(dip->di_fd, VX_SETCACHE, (flag) ? VX_DIRECT : 0)) < 0) {
		(void)sprintf(fmt, "VX_DIRECT -> %s", file);
		report_error (dip, fmt, TRUE);
            }
        } else {
            (void)sprintf(fmt, "directio -> %s", file);
            report_error (dip, fmt, TRUE);
        }
    }
    return (status);
}
#endif /* defined(SOLARIS) */

#if defined(WIN32)

/*
 * SetupWindowsFlags() - Setup Native Windows Flags.
 *
 * Inputs:
 *	dip = Device information pointer.
 *	CreateDisposition = Pointer to creation disposition flags.
 *	File Attributes = Pointer to file attributes.
 *	oflags = The POSIX open flags.
 *
 * Return Value:
 *	Void
 */
void
SetupWindowsFlags(struct dinfo *dip, char *file, int oflags, DWORD *CreationDisposition, DWORD *FileAttributes)
{
    *CreationDisposition = 0;
    *FileAttributes = 0;

    if (dip->di_dio_flag					    	    ||
	((dip->di_mode == READ_MODE) && (dip->di_read_cache_flag == FALSE)) ||
	((dip->di_mode == WRITE_MODE) && (dip->di_write_cache_flag == FALSE)) ) {
	*FileAttributes |= (FILE_FLAG_NO_BUFFERING | FILE_FLAG_WRITE_THROUGH);
    }
    if (dip->di_ftype == INPUT_FILE) {
	*CreationDisposition = OPEN_EXISTING;
	*FileAttributes |= FILE_ATTRIBUTE_READONLY;
    } else {
	if (dip->di_dtype && (dip->di_dtype->dt_dtype == DT_REGULAR)) {
	    if (GetFileAttributes(file) == INVALID_FILE_ATTRIBUTES) {
		*CreationDisposition = CREATE_NEW;
	    } else if (oflags & O_TRUNC) {
		*CreationDisposition = TRUNCATE_EXISTING;
	    } else {
		*CreationDisposition = OPEN_ALWAYS;
	    }
	} else {
	    *CreationDisposition = OPEN_EXISTING;
	}
    }
    if ( (dip->di_io_type == RANDOM_IO) || (dip->di_io_dir == REVERSE) ) {
	*FileAttributes |= FILE_FLAG_RANDOM_ACCESS;
    } else if (dip->di_io_dir == FORWARD) {
	*FileAttributes |= FILE_FLAG_SEQUENTIAL_SCAN;
    }
    if (dip->di_aio_flag) {
	*FileAttributes |= FILE_FLAG_OVERLAPPED;
    } else if (*FileAttributes == 0) {
	/* The file does not have other attributes set. */
	*FileAttributes |= FILE_ATTRIBUTE_NORMAL;
    }
    return;
}

int
HandleSparseFile(dinfo_t *dip, DWORD FileAttributes)
{
    int status = SUCCESS;
    BOOL is_overlapped = (FileAttributes & FILE_FLAG_OVERLAPPED) ? TRUE : FALSE;

    if ( (dip->di_mode == WRITE_MODE) &&
	 (dip->di_dtype->dt_dtype == DT_REGULAR) ) {
	/*
	 * Attempt to enable sparse file attribute to mimic *nix OS's.
	 * This avoids wasted space (holes) and avoids long noprog's!
	 */
	if (dip->di_sparse_flag) {
	    status = SetSparseFile(dip, dip->di_fd, is_overlapped);
	    if (status == SUCCESS) return(status);
	    if (status == WARNING) status = SUCCESS;
	}
	/*
	 * If sparse is disabled or failed, preallocate file blocks.
	 */
	if (dip->di_prealloc_flag &&
	    ((dip->di_io_dir == REVERSE) || (dip->di_io_type == RANDOM_IO)) ) {
	    status = PreAllocateFile(dip, FileAttributes);
	    if (status == FAILURE) {
		if ( !isFsFullOk(dip, "WriteFile") ) {
		    report_error (dip, "WriteFile failed", TRUE);
		}
		(void)close_file(dip);
	    }
	}
    }
    return(status);
}

/*
 * SetSparseFile - Set File as Sparse (to mimic Unix behaviour).
 *
 * Description:
 *	This function sets the sparse attribute, which is necessary to
 * avoid allocating all blocks in a file when writing to large offsets
 * and or a file expected to have holes (any seek / write operation).
 * The default on Windows is to allocate all blocks, where on Unix it
 * is to allow holes so all blocks are not allocated.
 *
 * In the Windows case, allocating blocks for say 400m of data can take
 * many seconds, which causes false long no-progress indicators.  The
 * time is actually being spent allocating blocks, not the actual I/O.
 *
 * Inputs:
 *	dip = The device information pointer.
 *	hDevice = The handle to the device.
 *	FileAttributes = The file attributes (we look at overlapped flag)
 *
 * Return Value:
 *	Success / Failure / Warning (sparse not supported).
 */
int
SetSparseFile(dinfo_t *dip, HANDLE hDevice, BOOL is_overlapped)
{
    BOOL	bStatus;
    DWORD	FileAttributes;
    DWORD	BytesReturned;
    OVERLAPPED	Overlapped;
    PCHAR	p, rootvol = NULL;
    DWORD	VolFlags;
    int		status = SUCCESS;

    /*
     * BOOL WINAPI GetVolumeInformation(
     *  _In_opt_   LPCTSTR lpRootPathName,
     *  _Out_opt_  LPTSTR lpVolumeNameBuffer,
     *  _In_       DWORD nVolumeNameSize,
     *  _Out_opt_  LPDWORD lpVolumeSerialNumber,
     *  _Out_opt_  LPDWORD lpMaximumComponentLength,
     *  _Out_opt_  LPDWORD lpFileSystemFlags,
     *  _Out_opt_  LPTSTR lpFileSystemNameBuffer,
     *  _In_       DWORD nFileSystemNameSize
     * );
     */
    if (p = strstr(dip->di_dname, ":\\")) {
	size_t rootvol_size = ((p + 2) - dip->di_dname);
	rootvol = Malloc(rootvol_size + 1);
	(void)strncpy(rootvol, dip->di_dname, rootvol_size);
    }
    bStatus = GetVolumeInformation(rootvol, NULL, 0, NULL,
				   NULL, &VolFlags, NULL, 0);
    if (!bStatus) {
	if (rootvol) {
	    Fprintf("Failed to get volume information for volume '%s'\n", rootvol);
	}
	os_perror("GetVolumeInformation failed for file '%s'", dip->di_dname);
    }

    if (VolFlags & FILE_SUPPORTS_SPARSE_FILES) {
	; 	// File system supports sparse streams
    } else {
	if (dip->di_debug_flag) {
	    Printf("Warning: Sparse files are NOT supported!\n");
	}
	return(WARNING);
    }
    if (rootvol) {
	free(rootvol);
	rootvol = NULL;
    }

    FileAttributes = GetFileAttributes(dip->di_dname);
    if (FileAttributes == INVALID_FILE_ATTRIBUTES) {
	os_perror("GetFileAttributes failed on file '%s'", dip->di_dname);
	return(FAILURE);
    }
    if (FileAttributes & FILE_ATTRIBUTE_SPARSE_FILE) {
	if (dip->di_debug_flag) {
	    Printf("File '%s' is already a sparse file!\n", dip->di_dname);
	}
	return(status);
    }

    if (dip->di_debug_flag) {
        Printf("Enabling sparse file attribute via FSCTL_SET_SPARSE...\n");
    }
    /*
     * Links to information regarding sparse files:
     * http://msdn.microsoft.com/en-us/library/windows/desktop/aa364596(v=vs.85).aspx
     * http://msdn.microsoft.com/en-us/library/windows/desktop/ms684342(v=vs.85).aspx
     * http://msdn.microsoft.com/en-us/library/windows/desktop/aa365564(v=vs.85).aspx
     * http://msdn.microsoft.com/en-us/library/windows/desktop/aa365566(v=vs.85).aspx
     */
    memset(&Overlapped, '\0', sizeof(Overlapped));
    bStatus = DeviceIoControl(
			     hDevice,		// handle to file
			     FSCTL_SET_SPARSE,	// dwIoControlCode
			     NULL,		// lpInBuffer
			     0,			// nInBufferSize
			     NULL,		// lpOutBuffer
			     0,			// nOutBufferSize
			     &BytesReturned,	// number of bytes returned
			     &Overlapped);	// OVERLAPPED structure
    if (!bStatus) {
	DWORD error = GetLastError();
	if (error == ERROR_IO_PENDING) {
	    do {
		bStatus = GetOverlappedResult(hDevice, &Overlapped, &BytesReturned, FALSE);
		if (!bStatus && ( (error = GetLastError()) == ERROR_IO_INCOMPLETE) ) {
		    Sleep(10);
		} else {
		    os_perror("GetOverlappedResult failed");
		    status = FAILURE;
		    break;
		}
	    } while (!bStatus && (error == ERROR_IO_INCOMPLETE));
	} else {
	    Fprintf("Setting sparse file attribute for file '%s' failed!\n", dip->di_dname);
	    os_perror("DeviceIoControl(FSCTL_SET_SPARSE) failed");
	    status = FAILURE;
	}
    } else if (is_overlapped) {
	bStatus = GetOverlappedResult(hDevice, &Overlapped, &BytesReturned, TRUE);
	if (!bStatus) {
	    os_perror("GetOverlappedResult failed");
	    status = FAILURE;
	}
    }
    return(status);
}

static int
PreAllocateFile(dinfo_t *dip, DWORD FileAttributes)
{
    unsigned char *buffer;
    DWORD nbytes = BLOCK_SIZE, written = 0;
    OFF_T pos = (dip->di_data_limit - nbytes), npos;
    BOOL result;
    int status = SUCCESS;

    if (dip->di_data_limit < nbytes) return (status);
    if (pos < 0) pos = (OFF_T) 0;
    if (FileAttributes & FILE_FLAG_NO_BUFFERING) {
	/* Must be block aligned offset! */
	pos = roundup(pos, nbytes);
    }
    /* Windows with unbuffered I/O doesn't care if we're aligned, but some FS's do! */
    buffer = malloc_palign(nbytes, 0);
    if (dip->di_debug_flag) {
	Printf("Preallocating data blocks by writing %u bytes to offset " FUF "...\n",
	       nbytes, pos);
    }
    if (FileAttributes & FILE_FLAG_OVERLAPPED) {
	OVERLAPPED overlap;
	overlap.hEvent = 0;
	overlap.Offset = ((PLARGE_INTEGER)(&pos))->LowPart;
	overlap.OffsetHigh = ((PLARGE_INTEGER)(&pos))->HighPart;
	result = WriteFile(dip->di_fd, buffer, nbytes, NULL, &overlap);
	if ((!result) && (GetLastError() != ERROR_IO_PENDING)) {
	    free_palign(buffer);
	    return (FAILURE);
	}
	result = GetOverlappedResult(dip->di_fd, &overlap, &written, TRUE);
    } else {
	npos = set_position (dip, pos, FALSE);
	/* Note: Above terminates on errors, but needs to change! */
	if (npos == (OFF_T) -1) return (FAILURE);
	if (npos != pos) {
	    Fprintf("ERROR: Wrong seek position, (npos " FUF " != pos " FUF ")!\n",
		    npos, pos);
	    free_palign(buffer);
	    return (FAILURE);
	}
	result = WriteFile(dip->di_fd, buffer, nbytes, &written, NULL);
    }
    free_palign(buffer);
    if (!result) return (FAILURE);
    if (nbytes != written) return (FAILURE);
    return (status);
}

#endif /* defined(WIN32) */
