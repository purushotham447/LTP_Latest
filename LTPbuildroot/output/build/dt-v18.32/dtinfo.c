/****************************************************************************
 *      								    *
 *      		  COPYRIGHT (c) 1988 - 2013     		    *
 *      		   This Software Provided       		    *
 *      			     By 				    *
 *      		  Robin's Nest Software Inc.    		    *
 *      								    *
 * Permission to use, copy, modify, distribute and sell this software and   *
 * its documentation for any purpose and without fee is hereby granted,     *
 * provided that the above copyright notice appear in all copies and that   *
 * both that copyright notice and this permission notice appear in the      *
 * supporting documentation, and that the name of the author not be used    *
 * in advertising or publicity pertaining to distribution of the software   *
 * without specific, written prior permission.  			    *
 *      								    *
 * THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,        *
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN      *
 * NO EVENT SHALL HE BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL   *
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR    *
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS  *
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF   *
 * THIS SOFTWARE.       						    *
 *      								    *
 ****************************************************************************/
/*
 * Module:      dtinfo.c
 * Author:      Robin T. Miller
 * Date:	September 8, 1993
 *
 * Description:
 *      Setup device and/or system information for 'dt' program.
 */
#include "dt.h"
#if !defined(_QNX_SOURCE)
#  if !defined(sun) && !defined(WIN32)
#    include <sys/ioctl.h>
#  endif /* !defined(sun) */
#endif /* !defined(_QNX_SOURCE) */
#include <sys/stat.h>

/*
 * Modification History:
 *
 * April 24th, 2013 by Robin T. Miller
 * 	For Windows, regardless of I/O type/direction, always setup the disk
 * capacity from the IOCTL_DISK_GET_DRIVE_GEOMETRY_EX DeviceIoControl(). This
 * is required for sequential I/O to avoid attempts to do IO at the end of media,
 * which returns different errors depending on the Windows version. Even the code
 * originally implemented for Windows EOF is unclean for raw disk testing! :-(
 * 
 * April 3rd, 2013 by Robin T. Miller
 *      On Linux, the BLKGETSIZE IOCTL returns blocks as 512 bytes, NOT the disk
 * sector size returned by BLKSSZGET. Now that someone is testing 4k sector blocks,
 * the math done to calculate capacity in bytes is off by a factor of 8, so fixing
 * this bad assumption.
 *      Also, if the real disk size is obtain, and the user has *not* specified a
 * device size, then set the device size to the real device size (not 512 bytes).
 * If the block size is less than the device size, then set this to the device size.
 * 
 * March 2nd, 2013 by Robin T. Miller
 *      On Linux, for disk devices, enable direct I/O to bypass the buffer cache.
 *      This is necessary, since disk devices use the block interface (no raw).
 *      Although binding of disks to raw can be done, much of QA does not do this!
 *      Since I'm tired of getting bit by this myself, DIO is now enabled for disks!
 * 
 * June 25th, 2011 by Robin T. Miller
 *      Honor the user specified device size, rather than overriding it in the
 * OS specific setup functions. The real device size is still saved, however.
 * 
 * June 13th, 2011 by Robin T. Miller
 *      Add Windows logic to automatically obtain the disk type information,
 * via DeviceIoControl() IOCTL_STORAGE_GET_DEVICE_NUMBER, and the disk geometry
 * via IOCTL_DISK_GET_DRIVE_GEOMETRY_EX. This allows us to avoid the seek/read
 * overhead to determine the capacity for random I/O and slices algorithm.
 * 
 * March 14th, 2011 by Robin T. Miller
 *      On Windows, do a case insensitive compare on device names, since
 * case does NOT may on Windows as it does on *nix systems (disks only).
 * 
 * August 23rd, 2010 by Robin T. Miller.
 *      On AIX, only set the user capacity from the actual disk capacity,
 * if the user has not specified a capacity. We were ignoring user capacity.
 * 
 * February 1st, 2010 by Robin T. Miller.
 *      Switch to using GetFileAttributesEx() on Windows so the 64 bit
 * file size can be obtained. Previous stat() method returns only 32 bits
 * for file size (st_size), which limits us to 2GB (signed 32-bit value).
 *
 * November 25th, 2009 by Robin T. Miller.
 *      Added setup_directory_info() for handling multiple directories.
 *
 * October 28th, 2008 by Robin T. Miller.
 *      Added hack to SetupRegularFile() to check for an input file
 * for setting the existing file size versus the user specified size.
 * Previously, the existing was always used which prevented extending,
 * and existing file (nobody reported, but broke my tests!).
 *
 * October 27th, 2008 by Robin T. Miller.
 *      For native, use stat() to find file size of existing file.
 * Note: This needs switched to native GetFileSizeEx() in the future.
 *
 * July 23rd, 2008 by Robin T. Miller.
 *      Add support for a history mechanism. The history entries and data
 * buffer memory is allocated when history=value is specified.
 * Fix bug in SetupRegularFile() when reading existing files with random
 * I/O, use the file size rather than the data limit to avoid premature
 * EOF caused by seeking past the end of file. (this is an old bug!)
 * Create device info fsync_flag so we have one for input and output.
 *
 * October 26th, 2007 by Robin T. Miller.
 *      Automatically detect Windows disks (PhysicalDriveN) names.
 *
 * May 9th, 2007 by Robin T. Miller.
 *      Treat memory mapped files like regular file so important
 * things like lbdata_size get setup accordingly (if not set, false
 * data corruptions occur).
 *
 * January 13th, 2007 by Robin T. Miller
 *      For AIX, implement IOCINFO to obtain device size & capacity.
 *
 * October 20th, 2004 by Robin Miller.
 *      In SetupRegularFile() set user capacity to the max of the
 * data limit or the file size, so repeated random I/O with same
 * random seed, provides the same results when file is re-read.
 *
 * July 7th, 2004 by Robin Miller.
 *      For HP-UX, allow setting the queue depth.
 *
 * March 30th, 2004 by Robin Miller.
 *      Add os_system_device_info() for Linux to try to obtain the
 * sector size and partition capacity.  If this can be obtained for
 * random I/O, then do_random() can be avoided, which is a good thing
 * since it's broken in 2.4 kernels (can't lseek past end of partition).
 *
 * February 27th, 2003 by Robin Miller.
 *      A little more tweaking of the fsync() flag... only enable
 * fsync for block or regular file, not for character (raw) disks.
 *
 * December 5th, 2003 by Robin Miller.
 *      Conditionalize to exclude tty code.
 *
 * November 17th, 2003 by Robin Miller.
 *      Breakup output to stdout or stderr, rather than writing
 * all output to stderr.  If output file is stdout ('-') or a log
 * file is specified, then all output reverts to stderr.
 *
 * June 9th, 2003 by Robin Miller.
 *      Fix problem setting fsync_flag when dtype=disk/block/regular
 * is specified (should do fsync() after writes, but it is *not*).
 *
 * March 13th, 2003 by Robin Miller.
 *      Add support for DIOC_DESCRIBE IOCTL to determine device type,
 * capacity, and block size.
 *
 * March 16th, 2002 by Robin Miller.
 *      In dec_system_device_info() open device with O_NDELAY, incase
 * this is a tape device, we don't want a looong delay during the open.
 *
 * October 4th, 2001 by Robin Miller.
 *      Fix problem with idtype/odtype options were being overridden by
 * dec_system_device_info().  Assume the user is right :-)
 *
 * August 31st, 2001 by Robin Miller.
 *      Add casts to values being used to calculate user capacity, which
 * is in bytes (64 bits), to ensure 32-bit truncation does not occur.
 *
 * June 2nd, 2001 by Robin Miller.
 *      After setting up a "regular" device type, ensure the device
 * defaults also get setup.  Was not setting  min/max/incr defaults.
 *
 * April 13th, 2001 by Robin Miller.
 *      Removed old PTOS conditionalization (Tru64 Unix V4.0+ only now).
 *      If supported, use DEVGETINFO instead of DEVIOCGET for longer
 * device names, and more information.  If max_capacity, set by the user
 * or random I/O and partition 'c' selected, set max capacity returned
 * from the device driver.  For random I/O, prevents lseek/read logic.
 *
 * April 12th, 2001 by Robin Miller.
 *      Delay setting device defaults, until later in setup_device_info().
 * When random I/O is selected, setup device values for a disk device.
 *
 * April 11th, 2001 by Robin Miller.
 *      For Tru64 Unix, if the user specified a device type, don't ovrride
 * it by calling dec_system_device_info().  If the user selected random I/O
 * options, enable random access mode.  Hey, the worse that can happen is
 * they'll get an lseek() error!  This handles special disk devices (LSM).
 *
 * February 6th, 2001 by Robin Miller.
 *      For Cygnus, map //./ and \\.\ directory prefixes to /dev. This
 * is how physical (raw) devices *must* be mounted to work properly.
 * If physical devices aren't mounted, Unix style EOM isn't emulated!
 *      Ensure same processing is performed on existing files and newly
 * created files.  This includes setting the fsync flag appropriately,
 * and setting up the user capacity for random I/O as necessary.
 *
 * February 1st, 2001 by Robin Miller.
 *      Make changes to allow multiple slices to an existing file.
 *
 * January 28th, 2001 by Robin Miller.
 *      Allow dec_system_device_info() to be called prior to the file
 * being opened.  We need device info early on for new slices option.
 *
 * January 25th, 2001 by Robin Miller.
 *      Flag disk devices, via di_random_access boolean flag.  This
 * includes regular files, so seek and report functions work on them.
 *
 * January 24th, 2001 by Robin Miller.
 *      Setup the default device block size from device_size variable,
 * so the user can override this using the "dsize=value" option.  Also,
 * various functions no longer have to check for this field being zero,
 * so perhaps this will help performance too.
 *
 * January 2nd, 2001 by Robin Miller.
 *      Make changes to build using MKS/NuTCracker product.
 *
 * August 22nd, 2000 by Robin Miller.
 *      Update setup_device_defaults() to better set incr and min values,
 * since this function may get called twice on Tru64 Unix systems.
 *
 * July 14th, 2000 by Robin Miller.
 *      Added logic to set file sync flag, if a block device or regular
 * file is used.  Tapes, FIFO's, and other devices do NOT like fsync()!
 *
 * April 2nd, 2000 by Robin Miller.
 *      Only set the random data limit when stat'ing the file,
 * if it's a regular file, since the st_size might not be bytes.
 * On QNX, st_size is the drive capacity, so setup user_capacity
 * to avoid seek/read algorithm in FindCapacity() for random I/O.
 *
 * August 1, 1999 by Robin Miller.
 *      Do a better job in setup_device_defaults() setting up the
 * defaults for min and increment counts.  For disks, this value
 * needs to be modulo the block size, since most disk drivers do
 * not permit non-modulo requests (Tru64 UNIX CAM is exception).
 *
 * December 21, 1998 by Robin Miller.
 *      - for DUNIX, allocate mtget structure for tapes.
 *      - changes for Malloc(), which now clears memory.
 *
 * December 19, 1998 by Robin Miller.
 *      For Steel DUNIX, strip trailing spaces from device names.
 *
 * October 29, 1998 by Robin Miller.
 *      Implement a random I/O data limit, instead of using the normal
 * data limit variable (not good to dual purpose this value).
 *
 * April 29, 1998 by Robin Miller.
 *      Add support for an alternate device directory.
 *
 * October 31, 1993 by Robin Miller.
 *      Enhance device type setup and honor user specified device type.
 *
 * October 29, 1993 by Robin Miller.
 *      Added more checks in setup_device_type() to determine detect
 *      selection of terminal devices (e.g., console device).
 *
 * September 15, 1993 by Robin Miller.
 *      Added stat() of file specified to check for FIFO's and set the
 *      device type appropriately so other checks could be done prior
 *      to opening the device (O_NONBLOCK needs set before open()).
 *
 */

/*
 * Forward References:
 */
void strip_trailing_spaces(char *bp);
static void setup_device_defaults(struct dinfo *dip);
static void SetupRegularFile(struct dinfo *dip, large_t file_size);
#if defined(DEC)
static int SetupDiskAttributes(struct dinfo *dip, int fd);
#endif /* defined(DEC) */
void os_system_device_info(struct dinfo *dip);

/************************************************************************
 *      								*
 * setup_device_type() - Setup the device type. 			*
 *      								*
 * Description: 							*
 *      This function sets up the specific device type to be tested.    *
 * Since each operating system has a different method of identifying    *
 * devices, so this table lookup allows the user to specify the device  *
 * type.  Of course, this could be used to force errors.		*
 *      								*
 * Inputs:      str = Pointer to device type string.    		*
 *      								*
 * Return Value:							*
 *      	Returns pointer to device type table entry or NULL.     *
 *      								*
 ************************************************************************/
struct dtype dtype_table[] = {
	{ "block",      DT_BLOCK	},
	{ "character",  DT_CHARACTER    },
	{ "comm",       DT_COMM 	},
	{ "disk",       DT_DISK 	},
	{ "directory",  DT_DIRECTORY    },
	{ "graphics",   DT_GRAPHICS     },
	{ "memory",     DT_MEMORY       },
	{ "mmap",       DT_MMAP 	},
	{ "network",    DT_NETWORK      },
	{ "pipe",       DT_PIPE 	},
	{ "processor",  DT_PROCESSOR    },
	{ "regular",    DT_REGULAR      },
	{ "socket",     DT_SOCKET       },
	{ "special",    DT_SPECIAL      },
	{ "streams",    DT_STREAMS      },
	{ "tape",       DT_TAPE 	},
	{ "unknown",    DT_UNKNOWN      }
};
int num_dtypes = sizeof(dtype_table) / sizeof(dtype_table[0]);

struct dtype *
setup_device_type (char *str)
{
    int i;
    struct dtype *dtp;

    for (dtp = dtype_table, i = 0; i < num_dtypes; i++, dtp++) {
	if (strcmp(str, dtp->dt_type) == 0) {
	    return (dtp);
	}
    }
    fprintf (efp, "Device type '%s' is invalid, valid entrys are:\n", str);
    for (dtp = dtype_table, i = 0; i < num_dtypes; i++, dtp++) {
	if ( (i % 4) == 0) fprintf (efp, "\n");
	fprintf (efp, "    %-12s", dtp->dt_type);
    }
    fprintf (efp, "\n");
    return ((struct dtype *) 0);
}

/************************************************************************
 *      								*
 * setup_device_defaults() - Setup the device defaults. 		*
 *      								*
 * Description: 							*
 *      This function sets up the specific device type defaults, for    *
 * test parameters which were not specified.    			*
 *      								*
 * Inputs:      dip = The device information pointer.   		*
 *      								*
 * Return Value:							*
 *      	Returns pointer to device type table entry or NULL.     *
 *      								*
 * Note: This function may get called twice!  On Tru64 Unix, after we   *
 *       open the device, the initial device type may get overridden.   *
 *      								*
 ************************************************************************/
static void
setup_device_defaults (struct dinfo *dip)
{
    struct dtype *dtp = dip->di_dtype;

    if ( (dtp->dt_dtype == DT_BLOCK)   ||
	 (dtp->dt_dtype == DT_DISK)    ||
	 (dtp->dt_dtype == DT_MMAP)    ||
	 (dtp->dt_dtype == DT_REGULAR) || dip->di_random_io ) {
	/*
	 * Real device size should already been obtained.
	 */
	if (!dip->di_device_size && dip->di_rdsize) dip->di_device_size = dip->di_rdsize;
	if (!dip->di_device_size) dip->di_device_size = BLOCK_SIZE;
	if (!dip->di_lbdata_size) dip->di_lbdata_size = dip->di_device_size;
	if (dip->di_max_size && !dip->di_user_min) dip->di_min_size = dip->di_device_size;
	if (dip->di_min_size && !dip->di_user_incr) dip->di_incr_count = dip->di_device_size;
	/* Ensure min and incr values are non-zero! */
	if (dip->di_max_size && !dip->di_min_size) dip->di_min_size = dip->di_device_size;
	if (dip->di_min_size && !dip->di_incr_count) dip->di_incr_count = dip->di_device_size;
	if (dip->di_fsalign_flag && dip->di_random_io) {
	    if (!dip->di_random_align) dip->di_random_align = dip->di_device_size;
	}
	if (dip->di_fsync_flag == UNINITIALIZED) {
	    if ( (dtp->dt_dtype == DT_BLOCK)   ||
		 (dtp->dt_dtype == DT_REGULAR) ) {
		dip->di_fsync_flag = TRUE;
	    } else if (dtp->dt_dtype == DT_DISK) {
		/*
		 * Devices identified as DT_DISK should be the
		 * raw (character) device.  Since some OS's,
		 * such as AIX don't like fsync() to disks,
		 * we'll disable it since it really only has
		 * meaning to block or regular (FS) files.
		 */
		dip->di_fsync_flag = FALSE;
	    }
	}
	/*
	 * Additional setup for direct disk testing.
	 */ 
	if (dtp->dt_dtype == DT_DISK) {
	    if (dip->di_block_size < dip->di_device_size) {
		dip->di_block_size = dip->di_device_size;
	    }
#if defined(__linux__)
	    dip->di_open_flags |= O_DIRECT; /* Bypass the buffer cache! */
#endif
	}
    } else {
	if (!dip->di_device_size) dip->di_device_size = 1;
	if (!dip->di_lbdata_size) dip->di_lbdata_size = dip->di_device_size;
	if (dip->di_max_size && !dip->di_user_min) dip->di_min_size = 1;
	if (dip->di_min_size && !dip->di_user_incr) dip->di_incr_count = 1;
	/* Ensure min and incr values are non-zero! */
	if (dip->di_max_size && !dip->di_min_size) dip->di_min_size = 1;
	if (dip->di_min_size && !dip->di_incr_count) dip->di_incr_count = 1;
	dip->di_fsync_flag = FALSE;
    }
    return;
}

/************************************************************************
 *      								*
 * os_system_device_info() - Get OS System Device Information.  	*
 *      								*
 * Description: 							*
 *      This function attempts to obtain device information necessary   *
 * for device specific testing, by using system dependent syscalls.     *
 * Note: This function is called _after_ the device/file is opened.     *
 *      								*
 * Inputs:      dip = The device information pointer.   		*
 *      								*
 * Return Value:							*
 *      	None.   						*
 *      								*
 ************************************************************************/
#if defined(AIX)

#include <sys/devinfo.h>

void
os_system_device_info (struct dinfo *dip)
{
    struct devinfo devinfo;
    struct devinfo *devinfop = &devinfo;
    int fd = dip->di_fd;
    bool temp_fd = FALSE;
    short category;
    int i;
	
    if (fd == NoFd) {
	temp_fd = TRUE;
	if ( (fd = open(dip->di_dname, O_RDONLY)) < 0) {
	    return;
	}
    }

    (void)memset(devinfop, '\0', sizeof(*devinfop));
    if (ioctl (fd, IOCINFO, devinfop) == SUCCESS) {

	switch (devinfop->devtype) {

	    case DD_DISK: { /* Includes LV's! */
		if (devinfop->flags & DF_LGDSK) {
		    dip->di_rdsize = devinfop->un.dk64.bytpsec;
		    if (!dip->di_dsize) dip->di_dsize = dip->di_rdsize;
		    dip->di_capacity = (large_t)
				       ((u_int64_t)devinfop->un.dk64.hi_numblks << 32L) |
					(uint32_t)devinfop->un.dk64.lo_numblks;
		} else {
		    dip->di_rdsize = devinfop->un.dk.bytpsec;
		    if (!dip->di_dsize) dip->di_dsize = dip->di_rdsize;
		    dip->di_capacity = (large_t)devinfop->un.dk.numblks;
		}
		break;
	    }
	    case DD_SCDISK: {
		if (devinfop->flags & DF_LGDSK) {
		    dip->di_rdsize = devinfop->un.scdk64.blksize;
		    if (!dip->di_dsize) dip->di_dsize = dip->di_rdsize;
		    dip->di_capacity = (large_t)
				       ((u_int64_t)devinfop->un.scdk64.hi_numblks << 32L) |
					(uint32_t)devinfop->un.scdk64.lo_numblks;
		} else {
		    dip->di_rdsize = devinfop->un.scdk.blksize;
		    if (!dip->di_dsize) dip->di_dsize = dip->di_rdsize;
		    dip->di_capacity = (large_t)devinfop->un.scdk.numblks;
		}
		break;
	    }
	    case DD_TAPE:
	    case DD_SCTAPE:
		dip->di_dtype = setup_device_type("tape");
		break;

	    default:
		break;
	}

	/*
	 * Common Disk Setup:
	 */
	if ( (devinfop->devtype == DD_DISK) || (devinfop->devtype == DD_SCDISK) ) {
	    if (dip->di_random_io || dip->di_num_slices) {
		if ( !dip->di_max_capacity && !dip->di_user_capacity ) {
		    dip->di_max_capacity = TRUE;
		    dip->di_user_capacity = (dip->di_capacity * (large_t)dip->di_rdsize);
		}
		if (dip->di_debug_flag) {
		    Printf("IOCINFO Capacity: " LUF " blocks, device size %u bytes.\n",
			   dip->di_capacity, dip->di_dsize);
		}
	    }
	    if (dip->di_dsize && !dip->di_user_lbsize && !dip->di_lbdata_size) {
		dip->di_lbdata_size = dip->di_dsize;
	    }
	    dip->di_dtype = setup_device_type("disk");
	}
    }

    if (temp_fd) (void)close(fd);
    return;
}

#endif /* defined(AIX) */

#if defined(DEC)

#include <sys/devio.h>
#include <sys/ioctl.h>
#if defined(DEC)
#  include <sys/ioctl_compat.h>
#  include <io/common/devgetinfo.h>
#endif /* defined(DEC) */

void
os_system_device_info (struct dinfo *dip)
{
    struct devget devget, *devgp = NULL;
    device_info_t devinfo, *devip = NULL;
    int fd = dip->di_fd;
    bool temp_fd = FALSE;
    short category;
    int i, status;

    if (fd == NoFd) {
	temp_fd = TRUE;
	if ( (fd = open (dip->di_dname, (O_RDONLY | O_NDELAY))) < 0) {
	    return;
	}
    }

    /*
     * Attempt to obtain the device information.
     */
    memset(&devinfo, '\0', sizeof(devinfo));
    if (ioctl (fd, DEVGETINFO, (char *) &devinfo) == SUCCESS) {
	devip = &devinfo;
	category = devip->v1.category;
	if ( NEL (devip->v1.device, DEV_UNKNOWN, DEV_STRING_SIZE) ) {
	    dip->di_device = Malloc(DEV_STRING_SIZE + 1);
	    (void) strncpy (dip->di_device, devip->v1.device, DEV_STRING_SIZE);
	} else if ( NEL (devip->v1.dev_name, DEV_UNKNOWN, DEV_STRING_SIZE) ) {
	    dip->di_device = Malloc(DEV_STRING_SIZE + 1);
	    (void) strncpy (dip->di_device, devip->v1.dev_name, DEV_STRING_SIZE);
	}
	if (dip->di_device) {
	    /*
	     * In Steel, device names have trailing spaces. grrr!
	     */
	    for (i = (DEV_STRING_SIZE); i--; ) {
		if ( isspace(dip->di_device[i]) ) {
		    dip->di_device[i] = '\0';
		} else {
		    break;
		}
	    }
	}
    } else { /* Try the old DEVIOCGET IOCTL... */

	memset(&devget, '\0', sizeof(devget));
	if (ioctl (fd, DEVIOCGET, (char *) &devget) < 0) {
	    if (temp_fd) (void)close(fd);
	    return;
	}
	devgp = &devget;
	category = devgp->category;
	if ( NEL (devgp->device, DEV_UNKNOWN, DEV_SIZE) ) {
	    dip->di_device = Malloc(DEV_SIZE + 1);
	    (void) strncpy (dip->di_device, devgp->device, DEV_SIZE);
	} else if ( NEL (devgp->dev_name, DEV_UNKNOWN, DEV_SIZE) ) {
	    dip->di_device = Malloc(DEV_SIZE + 1);
	    (void) strncpy (dip->di_device, devgp->dev_name, DEV_SIZE);
	}
	if (dip->di_device) {
	    /*
	     * In Steel, device names have trailing spaces. grrr!
	     */
	    for (i = (DEV_SIZE); i--; ) {
		if ( isspace(dip->di_device[i]) ) {
		    dip->di_device[i] = '\0';
		} else {
		    break;
		}
	    }
	}
    }

    /*
     * Setup the device type based on the category.
     */
    switch (category) {

	case DEV_TAPE:  		/* Tape category. */
	    dip->di_dtype = setup_device_type("tape");
	    break;

	case DEV_DISK: {		/* Disk category. */
	    /*
	     * If using partition 'c', setup to use the whole capacity.
	     *
	     * Note: Only setup maximum capacity for random I/O, or else
	     * we will inhibit End of Media (EOM) testing.
	     */
	    if (dip->di_random_io || dip->di_num_slices) {
		if (dip->di_dname[strlen(dip->di_dname)-1] == 'c') {
		    if ( !dip->di_max_capacity && !dip->di_user_capacity ) {
			dip->di_max_capacity = TRUE;
		    }
		}
	    }
	    /****************************************************************
	     * Attempt to get disk attributes using DEVGETINFO first, since *
	     * for SCSI disks we get more information, which we plan to use *
	     * one day, and we also get the real block (sector) size.       *
	     ****************************************************************/
	    if (devip && (devip->version == VERSION_1) ) {
		v1_disk_dev_info_t *diskinfo;
		diskinfo = &devip->v1.devinfo.disk;
		dip->di_rdsize = diskinfo->blocksz;
		if (!dip->di_dsize) dip->di_dsize = dip->di_rdsize;
		/*
		 * NOTE: capacity is whole disk, not the open partition,
		 *       so we don't use it unless selected by the user.
		 */
		if (dip->di_max_capacity) {
		    dip->di_capacity = diskinfo->capacity;
		    dip->di_user_capacity = (dip->di_capacity * (large_t)dip->di_rdsize);
		    if (dip->di_debug_flag) {
			Printf("DEVGETINFO Capacity: " LUF " blocks.\n", dip->di_capacity);
		    }
		}
		if (dip->di_dsize && !dip->di_user_lbsize && !dip->di_lbdata_size) {
		    dip->di_lbdata_size = dip->di_dsize;
		}
	    } else {
		(void)SetupDiskAttributes(dip, fd);
	    }
	    dip->di_dtype = setup_device_type("disk");
	    /*
	     * TODO: Need to read disklabel to pickup partition sizes,
	     *       and to check for mounted file systems. More work!
	     */
	    break;
	}

	case DEV_SPECIAL:       	/* Special category. */
	    /*
	     * On Tru64 Unix, LSM volumes are really disks!
	     */
	    if (SetupDiskAttributes(dip, fd) != SUCCESS) {
		dip->di_dtype = setup_device_type("special");
	    }
	    break;

	default:
	    break;
    }
    if (temp_fd) (void)close(fd);
    return;
}

/*
 * SetupDiskAttributes() - Setup Disk Attributes using DEVGETGEOM.
 *
 * Description:
 *      This function is used for disk devices which don't support
 * the newer DEVGETINFO IOCTL, like LSM devices.
 *
 * Inputs:
 *      dip = The device information pointer.
 *      fd = The file descriptor (NoFd == Not open).
 *
 * Outputs:
 *      Returns 0 or -1 for Success/Failure.
 */
static int
SetupDiskAttributes (struct dinfo *dip, int fd)
{
    int status;
    bool temp_fd = FALSE;
    DEVGEOMST devgeom;

    if (fd == NoFd) {
	temp_fd = TRUE;
	if ( (fd = open (dip->di_dname, O_RDONLY)) < 0) {
	    return (FAILURE);
	}
    }

    /*
     * If using partition 'c', setup to use the whole capacity.
     *
     * Note: Only setup maximum capacity for random I/O, or else
     * we will inhibit End of Media (EOM) testing.
     */
    if (dip->di_random_io || dip->di_num_slices) {
	if ( (dip->di_device && EQ(dip->di_device,"LSM")) ||
	     (dip->di_dname[strlen(dip->di_dname)-1] == 'c') ) {
	    if ( !dip->di_max_capacity && !dip->di_user_capacity ) {
		dip->di_max_capacity = TRUE;
	    }
	}
    }

    /*
     * Attempt to obtain the disk geometry.  Works for LSM, etc.
     *
     * NOTE: DEVGETGEOM *fails* on read-only devices (shit!).
     */
    memset(&devgeom, '\0', sizeof(devgeom));
    if ((status = ioctl (fd, DEVGETGEOM, (char *) &devgeom)) == SUCCESS) {
	dip->di_rdsize = devgeom.geom_info.sector_size;
	if (!dip->di_dsize) dip->di_dsize = dip->di_rdsize;
	/*
	 * NOTE: dev_size is whole disk, not the open partition,
	 *       so we don't use it unless selected by the user.
	 */
	if (dip->di_max_capacity) {
	    dip->di_capacity = devgeom.geom_info.dev_size;
	    dip->di_user_capacity = (dip->di_capacity * (large_t)dip->di_rdsize);
	    if (dip->di_debug_flag) {
		Printf("DEVGETGEOM Capacity: " LUF " blocks.\n", dip->di_capacity);
	    }
	}
	if (dip->di_dsize && !dip->di_user_lbsize && !dip->di_lbdata_size) {
	    dip->di_lbdata_size = dip->di_dsize;
	}
	dip->di_dtype = setup_device_type("disk");
    }
    /*
     * TODO: Need to read disklabel to pickup partition sizes,
     *       and to check for mounted file systems. More work!
     */
    if (temp_fd) (void)close(fd);
    return (status);
}

#endif /* defined(DEC) */

#if defined(HP_UX)

#include <sys/diskio.h>
#include <sys/scsi.h>

static int get_queue_depth(dinfo_t *dip, int fd, unsigned int *qdepth);
static int set_queue_depth(dinfo_t *dip, int fd, unsigned int qdepth);

void
os_system_device_info (struct dinfo *dip)
{
    disk_describe_type disk_type, *disktp = &disk_type;
    union inquiry_data inquiry;
    int fd = dip->di_fd;
    bool temp_fd = FALSE;
    short category;
    int i;

    if (fd == NoFd) {
	temp_fd = TRUE;
	if ( (fd = open (dip->di_dname, (O_RDONLY | O_NDELAY))) < 0) {
	    return;
	}
    }

    /*
     * Attempt to obtain the device information.
     */
    memset(disktp, '\0', sizeof(*disktp));
    if (ioctl (fd, DIOC_DESCRIBE, disktp) == SUCCESS) {
	if (disktp->dev_type != UNKNOWN_DEV_TYPE) {
	    size_t size = sizeof(disktp->model_num);
	    dip->di_device = Malloc(size + 1);
	    (void) strncpy (dip->di_device, disktp->model_num, size);
	    /*
	     * Strip trailing spaces from the device name.
	     */
	    for (i = size; i--; ) {
		if ( isspace(dip->di_device[i]) ) {
		    dip->di_device[i] = '\0';
		} else {
		    break;
		}
	    }
	    dip->di_rdsize = disktp->lgblksz;
	    if (!dip->di_dsize) dip->di_dsize = dip->di_rdsize;
	    /*
	     * Only setup capacity for random I/O, since we want to test
	     * end of file conditions on sequential reads and writes.
	     */
	    if (dip->di_random_io || dip->di_num_slices) {
		if ( !dip->di_max_capacity && !dip->di_user_capacity ) {
		    dip->di_max_capacity = TRUE;
		    dip->di_capacity = (disktp->maxsva + 1);
		    dip->di_user_capacity = (dip->di_capacity * (large_t)dip->di_rdsize);
		    if (dip->di_debug_flag) {
			Printf("DIOC_DESCRIBE Capacity: " LUF " blocks (%u byte blocks).\n",
					dip->di_capacity, dip->di_rdsize);
		    }
		}
	    }
	}

	switch (disktp->dev_type) {

	    case CDROM_DEV_TYPE:	/* CDROM device */
	    case DISK_DEV_TYPE: 	/* Disk device */
	    case WORM_DEV_TYPE: 	/* Write once read many optical device */
	    case MO_DEV_TYPE:   	/* Magneto Optical device */
		dip->di_dtype = setup_device_type("disk");
		if (dip->di_qdepth != 0xFFFFFFFF) {
		    (void)set_queue_depth(dip, fd, dip->di_qdepth);
		}       						
		break;

	    case CTD_DEV_TYPE:  	/* Cartridge tape device */
		dip->di_dtype = setup_device_type("tape");
		break;

	    default:
		break;
	}
    } else if (ioctl (fd, SIOC_INQUIRY, &inquiry) == SUCCESS) {
	struct inquiry_2 *inq = (struct inquiry_2 *)&inquiry;
	size_t size = sizeof(inq->product_id);

	if (dip->di_debug_flag) {
	    Printf("SIOC_INQUIRY device type %u\n", inq->dev_type);
	}
	dip->di_device = Malloc(size + 1);
	(void) strncpy (dip->di_device, inq->product_id, size);
	for (i = size; i--; ) {
	    if ( isspace(dip->di_device[i]) ) {
		dip->di_device[i] = '\0';
	    } else {
		break;
	    }
	}

	switch (inq->dev_type) {

	    case SCSI_DIRECT_ACCESS:
	    case SCSI_WORM:
	    case SCSI_CDROM:
	    case SCSI_MO:
		dip->di_dtype = setup_device_type("disk");
		if (dip->di_qdepth != 0xFFFFFFFF) {
		    (void)set_queue_depth(dip, fd, dip->di_qdepth);
		}       						
		break;

	    case SCSI_SEQUENTIAL_ACCESS:
		dip->di_dtype = setup_device_type("tape");
		break;

	    default:
		break;
	}
    }
    if (temp_fd) (void)close(fd);
    return;
}

static int
get_queue_depth(dinfo_t *dip, int fd, unsigned int *qdepth)
{
    struct sioc_lun_limits lun_limits;
    int status;

    (void)memset(&lun_limits, '\0', sizeof(lun_limits));
    if ( (status = ioctl(fd, SIOC_GET_LUN_LIMITS, &lun_limits)) < 0) {
	if (dip->di_debug_flag) {
	    perror("SIOC_SET_LUN_LIMITS failed");
	}
    } else {
	*qdepth = lun_limits.max_q_depth;
    }
    return (status);
}

static int
set_queue_depth(dinfo_t *dip, int fd, unsigned int qdepth)
{
    struct sioc_lun_limits lun_limits;
    int status;

    if (dip->di_debug_flag) {
	unsigned int qd;
	if (get_queue_depth (dip, fd, &qd) == 0) {
	    Printf("Current queue depth is %u\n", qd);
	}
    }
    (void)memset(&lun_limits, '\0', sizeof(lun_limits));
    lun_limits.max_q_depth = qdepth;
    /*
     * For performance testing, allow disabling tags.
     */
    if (qdepth == 0) {
#if defined(SCTL_DISABLE_TAGS)
	lun_limits.flags = SCTL_DISABLE_TAGS;
#else /* !defined(SCTL_DISABLE_TAGS) */
	lun_limits.flags = 0;
#endif /* defined(SCTL_DISABLE_TAGS) */
    } else {
	lun_limits.flags = SCTL_ENABLE_TAGS;
    }
    if ( (status = ioctl(fd, SIOC_SET_LUN_LIMITS, &lun_limits)) < 0) {
	if (dip->di_debug_flag) {
	    perror("SIOC_SET_LUN_LIMITS failed");
	}
    } else if (dip->di_debug_flag) {
	Printf("Queue depth set to %u\n", qdepth);
    }
    return (status);
}

#endif /* defined(HP_UX) */

#if defined(__linux__)

/* Ugly stuff to avoid conflict with Linux BLOCK_SIZE definition. */
#undef BLOCK_SIZE
#include <linux/fs.h>
#undef BLOCK_SIZE
#define BLOCK_SIZE 512

void
os_system_device_info (struct dinfo *dip)
{
    int fd = dip->di_fd;
    bool temp_fd = FALSE;
    unsigned long nr_sects;
    int sect_size;

    if (fd == NoFd) {
	temp_fd = TRUE;
	if ( (fd = open (dip->di_dname, (O_RDONLY | O_NDELAY))) < 0) {
	    return;
	}
    }

    /*
     * Try to obtain the sector size.
     */
    if (ioctl (fd, BLKSSZGET, &sect_size) == SUCCESS) {
	dip->di_rdsize = sect_size;
	if (!dip->di_dsize) dip->di_dsize = dip->di_rdsize;
	if (dip->di_debug_flag) {
	    Printf("BLKSSZGET Sector Size: %u bytes\n", dip->di_dsize);
	}
	dip->di_dtype = setup_device_type("disk");
    }

    /*
     * If this IOCTL succeeds, we will assume it's a disk device.
     *
     * Note: The size returned is for the partition (thank-you!).
     */
    if (ioctl (fd, BLKGETSIZE, &nr_sects) == SUCCESS) {
	if (!dip->di_rdsize) dip->di_rdsize = BLOCK_SIZE;
	/*
	 * Only setup capacity for random I/O, since we want to test
	 * end of file conditions on sequential reads and writes.
	 */
	if (dip->di_random_io || dip->di_num_slices) {
	    if ( !dip->di_max_capacity && !dip->di_user_capacity ) {
		dip->di_max_capacity = TRUE;
		dip->di_capacity = nr_sects;
		dip->di_user_capacity = (dip->di_capacity * (large_t)BLOCK_SIZE);
		if (dip->di_debug_flag) {
		    Printf("BLKGETSIZE Capacity: " LUF " blocks (%u byte blocks).\n",
			   dip->di_capacity, BLOCK_SIZE);
		}
	    }
	}
    }

    if (temp_fd) (void)close(fd);
    return;
}

#endif /* defined(__linux__) */

#if defined(WIN32)

void
os_system_device_info (struct dinfo *dip)
{
    HANDLE      	  fd;
    STORAGE_DEVICE_NUMBER sdn;
    PSTORAGE_DEVICE_NUMBER psdn = &sdn;
    DWORD       	  count;

    if ( (fd = dip->di_fd) == INVALID_HANDLE_VALUE) {
	fd = CreateFile(dip->di_dname, GENERIC_READ, (FILE_SHARE_READ|FILE_SHARE_WRITE), NULL, OPEN_EXISTING, 0, NULL);
	if (fd == INVALID_HANDLE_VALUE) return;
    }

    if (!DeviceIoControl(fd, IOCTL_STORAGE_GET_DEVICE_NUMBER, NULL, 0, psdn, sizeof(*psdn), &count, NULL)) {
	if (dip->di_fd == INVALID_HANDLE_VALUE) {
	    (void)CloseHandle(fd);
	}
	return;
    }
    switch (psdn->DeviceType) {
	case FILE_DEVICE_DISK: {
	    DISK_GEOMETRY_EX  dg;
	    PDISK_GEOMETRY_EX pdg = &dg;
	    if (dip->di_debug_flag) {
		Printf("Device type is %d (FILE_DEVICE_DISK)\n",  psdn->DeviceType);
	    }
	    if (DeviceIoControl(fd, IOCTL_DISK_GET_DRIVE_GEOMETRY_EX, NULL, 0, pdg, sizeof(*pdg), &count, NULL)) {
		dip->di_rdsize = pdg->Geometry.BytesPerSector;
		if (!dip->di_dsize) dip->di_dsize = dip->di_rdsize;
		/*
		 * Only setup capacity for random I/O, since we want to test
		 * end of file conditions on sequential reads and writes.
		 * 
		 * Note: Windows does not return a clean EOF indicator, and some
		 * 	 favors of Windows are *not* returning the expected error,
		 * 	 so, we will *always* try to obtain/setup the disk capacity!
		 */
		if (True || dip->di_random_io || dip->di_num_slices) {
		    dip->di_capacity = (large_t)pdg->DiskSize.QuadPart;
		    dip->di_capacity /= dip->di_rdsize;        /* Capacity in blocks. */
		    if ( !dip->di_max_capacity && !dip->di_user_capacity ) {
			dip->di_max_capacity = TRUE;
			dip->di_user_capacity = (large_t)pdg->DiskSize.QuadPart; /* In bytes! */
		    }
		    if (dip->di_debug_flag) {
			Printf("DISK_GEOMETRY_EX Capacity: " LUF " blocks (%u byte blocks).\n",
			       dip->di_capacity, dip->di_rdsize);
		    }
		}
	    }
	    dip->di_random_access = TRUE;
	    dip->di_dtype = setup_device_type("disk");
	    setup_device_defaults(dip);
	    break;
	}
	default:
	    if (dip->di_debug_flag) {
		Printf("Device type is %d, no special setup performed!\n",  psdn->DeviceType);
	    }
	    break;
    }
    if (dip->di_fd == INVALID_HANDLE_VALUE) {
	(void)CloseHandle(fd);
    }
    return;
}

#endif /* defined(WIN32) */

/*
 * system_device_info() - Setup The Device Information.
 *
 * Description:
 *      This function is called to setup various device information
 * after the device is open'ed.
 *
 * Inputs:
 *      The device information pointer.
 *
 * Return Value:
 *      void
 */
void
system_device_info (struct dinfo *dip)
{
    if (dip->di_dtype == NULL) {
#if defined(WIN32)
	DWORD device_type = GetFileType(dip->di_fd);
	//Printf("Device type = %x\n", device_type);
	if( GetFileType(dip->di_fd) == FILE_TYPE_DISK) {
	    dip->di_random_access = TRUE;
	    dip->di_dtype = setup_device_type("disk");
	    setup_device_defaults(dip);
	} else {
	    dip->di_dtype = setup_device_type("unknown");
	}
#else /* !defined(WIN32) */
	struct stat sb;
	/*
	 * This handles processing of *new* output files.
	 *
	 * Note: Best I can tell, this is already done!
	 */
	if ( (fstat (dip->di_fd, &sb) == SUCCESS) &&
	     ( S_ISREG(sb.st_mode) ) ) {
	    SetupRegularFile (dip, (large_t)sb.st_size);
	} else {
	    dip->di_dtype = setup_device_type("unknown");
	}
#endif /* defined(WIN32) */
    }
    return;
}

/************************************************************************
 *      								*
 * setup_device_info() - Setup Initial Device Information.      	*
 *      								*
 * Description: 							*
 *      This function allocates a device information entry, and does    *
 * the initial setup of certain information based on known options.     *
 * This function is meant to be called prior to opening the device so   *
 * test specific functions are known for initial processing.    	*
 *      								*
 * Inputs:      			    * 
 *  dip = The device information pointer.       	*
 *  dname = The device name.    		    * 
 *  dtype = The device type pointer.    	    * 
 *      								*
 * Return Value:							*
 *      	Returns SUCCESS/FAILURE 		*
 *      								*
 ************************************************************************/
int
setup_device_info (struct dinfo *dip, char *dname, struct dtype *dtp)
{
#if !defined(WIN32)
    struct stat sb;
#endif

    /*
     * The base name is used when generating a new file names when
     * multiple files are requested. In this case, dname will be freed,
     * and reallocated for the newly created file name, thus strdup().
     */
    dip->di_bname = dname;
    dip->di_dname = strdup(dname);
    dip->di_funcs = &generic_funcs;
#if defined(AIO)
    if (dip->di_aio_flag) {
	dip->di_funcs = &aio_funcs;
    }
#endif /* defined(AIO) */
#if defined(MMAP)
    if (dip->di_mmap_flag) {
	dip->di_funcs = &mmap_funcs;
	dtp = setup_device_type("mmap");
    }
#endif /* defined(MMAP) */

    /*
     * Setup the user specified device size (if any).
     */
    if (dip->di_device_size) {
	dip->di_dsize = dip->di_device_size;
    }

#if defined(DEC) || defined(HP_UX) || defined(__linux__) || defined(AIX) || defined(WIN32)
    /*
     * Must do this early on, to set device type and size.
     *
     * TODO: Create stub and remove ugly conditionalization!
     */
    if (dtp == NULL) {
	os_system_device_info (dip);
	dtp = dip->di_dtype;
    }
#endif /* defined(DEC) || defined(HP_UX) || defined(__linux__) || defined(AIX) || defined(WIN32) */

    /*
     * If user specified a device type, don't override it.
     */
    if (dtp == NULL) {
	/*
	 * Determine test functions based on device name.
	 */
#if defined(WIN32)
	if ( (EQL (dname, DEV_PREFIX, DEV_LEN)) ||
	     (EQL (dname, ADEV_PREFIX, ADEV_LEN)) ) {
	    char *dentry;
	    dentry = (dname + DEV_LEN);
	    if (EQL (dname, ADEV_PREFIX, ADEV_LEN)) {
#if (DEV_LEN != ADEV_LEN)
#  error "DEV_LEN != ADEV_LEN"
#endif
		/* Map //./ to \\.\ to ease scripting! */
		strncpy(dname, DEV_PREFIX, DEV_LEN);
		free(dip->di_dname);
		dip->di_dname = strdup(dname);
	    }
#else /* !defined(WIN32) */
	if ( (EQL (dname, DEV_PREFIX, DEV_LEN))   ||
	     (EQL (dname, ADEV_PREFIX, ADEV_LEN)) ||
	     (EQL (dname, NDEV_PREFIX, NDEV_LEN)) ) {
	    char *dentry;
	    if (EQL (dname, DEV_PREFIX, DEV_LEN)) {
		dentry = (dname + DEV_LEN);
	    } else if (EQL (dname, ADEV_PREFIX, ADEV_LEN)) {
		dentry = (dname + ADEV_LEN);
	    } else {
		dentry = (dname + NDEV_LEN);
	    }
#endif /* defined(WIN32) */
#if defined(__CYGWIN__)
	/*
	 * Map //./ or \\.\ to /dev/ prefix for Cygnus raw mounts.
	 */
	{   if (NEL (dname, DEV_PREFIX, DEV_LEN)) {
		char *cygnus_dname = Malloc(strlen(dname)+1);
		(void)strcpy(cygnus_dname, DEV_PREFIX);
		(void)strcat(cygnus_dname, dentry);
		dip->di_dname = strdup(cygnus_dname);
	    }
	}
#endif /* defined(__CYGWIN__) */
	    if ( (EQL (dentry, TAPE_NAME, sizeof(TAPE_NAME)-1)) ||
	 (EQL (dentry, NTAPE_NAME, sizeof(NTAPE_NAME)-1)) ) {
		dtp = setup_device_type("tape");
#if defined(WIN32)
	    } else if ( (EQLC (dentry, DISK_NAME, sizeof(DISK_NAME)-1)) ||
			(EQLC (dentry, RDISK_NAME, sizeof(RDISK_NAME)-1)) ) {
#else /* !defined(WIN32) */
	    } else if ( (EQL (dentry, DISK_NAME, sizeof(DISK_NAME)-1)) ||
			(EQL (dentry, RDISK_NAME, sizeof(RDISK_NAME)-1)) ) {
#endif /* defined(WIN32) */
		dtp = setup_device_type("disk");
#if defined(ADISK_NAME)
	    } else if ( (EQL (dentry, ADISK_NAME, sizeof(ADISK_NAME)-1)) ||
			(EQL (dentry, ARDISK_NAME, sizeof(ARDISK_NAME)-1)) ) {
		dtp = setup_device_type("disk");
#endif /* defined(ADISK_NAME) */
	    } else if ( (EQL (dentry, CDROM_NAME, sizeof(CDROM_NAME)-1)) ||
			(EQL (dentry, RCDROM_NAME, sizeof(RCDROM_NAME)-1)) ) {
		dtp = setup_device_type("disk");
	    }
#if defined(__MSDOS__) || defined(__WIN32__) || defined(_NT_SOURCE) || defined(WIN32)
	    if ( (dtp == NULL) && (IsDriveLetter (dentry)) ) {
		dtp = setup_device_type("block");
	    }
#endif /* defined(__MSDOS__) || defined(__WIN32__) || defined(_NT_SOURCE) */
	}

#if !defined(WIN32)
	if ( (dtp == NULL) &&
	     (strlen(dname) == 1) && (*dname == '-') ) {
	    if (!dip->di_lbdata_size) dip->di_lbdata_size = BLOCK_SIZE;
	    dtp = setup_device_type("pipe");
	}
	if ( (dtp == NULL) &&
	     (stat (dname, &sb) == SUCCESS)) {
	    if ( S_ISBLK(sb.st_mode)) {
		dtp = setup_device_type("block");
	    } else if ( S_ISCHR(sb.st_mode) ) {
		/*
		 * Character devices are NOT treated as disks!
		 */
#if defined(DEC)
		if (SetupDiskAttributes(dip, dip->di_fd) != SUCCESS)
#endif /* defined(DEC) */
		    dtp = setup_device_type("character");
	    } 
	}
#endif /* !defined(WIN32) */
    } /* if (dtp == NULL) */

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* End of device type setup.  Special setup follows. */
    /* - - - - - - - - - - - - - - - - - - - - - - - - - */

    /*
     * Do special setup for certain device types.
     */
    if ( (dip->di_dtype = dtp) ) {
    if ( (dtp->dt_dtype == DT_BLOCK) ||
	 (dtp->dt_dtype == DT_DISK)  || dip->di_random_io ) {
	dip->di_random_access = TRUE;
    }
	setup_device_defaults (dip);
    }
    /*
     * If the device size isn't set, then set it to our default.
     *
     * Note: This size is used for finding disk capacity, random I/O,
     *   variable requests, and reporting failing relative block.
     */
    if ( !dip->di_dsize ) {
	if (!dip->di_device_size) {
	    dip->di_device_size = BLOCK_SIZE;
	}
	dip->di_dsize = dip->di_device_size;
    }
    if (!dip->di_rdsize) dip->di_rdsize = dip->di_dsize;

    /*
     * Note: This handles *existing* input/output files.
     */
#if defined(WIN32)
    if (dtp == NULL) {
	large_t filesize = 0;
	WIN32_FILE_ATTRIBUTE_DATA fad, *fadp = &fad;
	/*
	 * See if the file exists, and what it's size is.
	 */
	if ( GetFileAttributesEx(dname, GetFileExInfoStandard, fadp) ) {
	    if (fadp->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		dip->di_dtype = dtp = setup_device_type("directory");
	    } else { /* Assuming a regular file (for now). */
		if ( (dip->di_dispose_mode == DELETE_FILE) && dip->di_keep_existing && !dip->di_num_procs) {
		    dip->di_dispose_mode = KEEP_FILE;   /* Keep existing files! */
		}
		if (!dip->di_dir && !dip->di_file_limit) {
		    /* Setup the 64-bit file size please! */
		    filesize = (large_t)(((large_t)fadp->nFileSizeHigh << 32L) + fadp->nFileSizeLow);
		}
	    }
	}
	/* Setup for new or existing regular files! */
	if ( !dtp ) {
	    SetupRegularFile (dip, filesize);
	}
#if OldMethod
	DWORD attributes = GetFileAttributes(dname);
	if (attributes != INVALID_FILE_ATTRIBUTES) {
	    dip->di_existing_file = TRUE;
	    if (attributes & FILE_ATTRIBUTE_DIRECTORY) {
		dip->di_dtype = dtp = setup_device_type("directory");
	    } else { /* Assuming a regular file (for now). */
		if ( (dip->di_dispose_mode == DELETE_FILE) && dip->di_keep_existing && !dip->di_num_procs) {
		    dip->di_dispose_mode = KEEP_FILE;   /* Keep existing files! */
		}
	    }
	}
	if (!dtp) { /* No device type yet, so it's not a directory! */
	    /* Note: Windows GetFileSize() requires a handle. */
	    if ( (!dip->di_dir && !dip->di_file_limit) &&
		 (stat (dname, &sb) == SUCCESS) ) {
		/* Note: st_size is only 32 bits! */
		SetupRegularFile (dip, (large_t)sb.st_size);
	    } else {
		SetupRegularFile (dip, (large_t)0);
	    }
	}
#endif /* OldMethod */
    } /* end of (dtp == NULL) */
#else /* !defined(WIN32) */
    if (dtp == NULL) {
	if (stat (dname, &sb) == SUCCESS) {
	    dip->di_existing_file = TRUE;
	    if ( S_ISDIR(sb.st_mode) ) {
		dip->di_dtype = dtp = setup_device_type("directory");
	    } else if ( S_ISREG(sb.st_mode) ) {
		if (dip->di_dir || dip->di_file_limit) {
		    SetupRegularFile (dip, (large_t)0);
		} else {
		    SetupRegularFile (dip, (large_t)sb.st_size);
		}
		/*
		 * TODO: This needs cleaned up! Don't understand logic.
		 */
		if ( (dip->di_dispose_mode == DELETE_FILE) && dip->di_keep_existing && !dip->di_num_procs) {
		    dip->di_dispose_mode = KEEP_FILE;   /* Keep existing files! */
		}
	    }
    # if defined(_QNX_SOURCE)
	    else if ( S_ISBLK(sb.st_mode) ) {
		dip->di_user_capacity = ((large_t)sb.st_size * (large_t)dip->di_dsize);
	    }
    # endif /* defined(_QNX_SOURCE) */
	} else if (errno == ENOENT) {
	    /*
	     * File doesn't exist, assume a regular file will be created,
	     */
	    if (dtp == NULL) {
		SetupRegularFile (dip, (large_t)0);
	    }
	}
    } /* end of (dtp == NULL) */
#endif /* defined(WIN32) */

    if (!dip->di_dtype && dtp) dip->di_dtype = dtp;
    if (!dip->di_dtype && !dtp) {
	dip->di_dtype = dtp = setup_device_type("unknown"); /* Avoid seg faults! */
    }

    if (dip->di_dtype->dt_dtype == DT_DIRECTORY) {
	Printf("Sorry, directories are not supported at this time!\n");
	exit(FAILURE);
    }

    /*
     * Allocate history buffers (if requested).
     */
    if (dip->di_history_size) {
	history_t *hp;
	int entries = 0;
	dip->di_history = Malloc(dip->di_history_size * sizeof(history_t));
	for (hp = dip->di_history;
	     (dip->di_history_data_size && (entries < dip->di_history_size));
	     entries++, hp++) {
	    hp->hist_request_data = Malloc(dip->di_history_data_size);
	}
    }
    if (dip->di_keepalive_time) {
	dip->di_last_keepalive = time((time_t *)0);
    }
    return (SUCCESS);
}

static void
SetupRegularFile (struct dinfo *dip, large_t file_size)
{
    /*
     * If random I/O was selected, and a data or record limit was
     * not specified (i.e. runtime=n), then setup the file size.
     * This is necessary to limit random I/O within file size, or
     * for newly created files setup capacity based on data limit.
     */
    if ( (dip->di_random_io || dip->di_num_slices) &&
	 (dip->di_rdata_limit == (large_t)0) && !dip->di_user_capacity) {
	if (file_size) {
	    /*
	     * If a data limit was specified, then do the following:
	     *  - if reading, set to current file size
	     *    ( very important for reverse or random I/O )
	     *  - if writing, set to max of existing or user size
	     *    ( exceeding the current size allows expansion )
	     */
	    if (dip->di_data_limit == INFINITY) {
		dip->di_user_capacity = file_size;
	    } else {
		/*
		 * This MAX is done, so random I/O to a file can be
		 * duplicated when specifying the same random seed.
		 * If file size is used, and it's less than limit,
		 * then random limit gets set too low so random
		 * offsets are not repeated, thus miscompares!
		 */
		dip->di_user_capacity = MAX(dip->di_data_limit, file_size);
	    }
	} else if (dip->di_data_limit != INFINITY) {
	    dip->di_user_capacity = dip->di_data_limit;
	}
    }
    dip->di_random_access = TRUE;
    dip->di_dtype = setup_device_type("regular");
    setup_device_defaults (dip);
    return;
}

int
setup_directory_info(struct dinfo *dip, char *dir)
{
    int status = SUCCESS;

    if (dir == NULL) return(status);

    /*
     * Setup for multiple directories and/or make the directory unique.
     *
     * When writing files with multiple processes, make the directory
     * name unique, just as we do for regular files.
     */
    dip->di_dir_created = FALSE;
    if (dip->di_mode == WRITE_MODE) {
	if (dip->di_unique_file) {
	    dip->di_dirpath = make_unique_file(dip, dip->di_dir); /* Appends PID. */
	} else {
	    dip->di_dirpath = strdup(dip->di_dir);
	}
	dip->di_existing_file = FALSE;      /* Assume files don't exist. */
	/* Note: Need to add check before creating output files. */

	status = create_directory(dip, dip->di_dirpath);
	if (status == SUCCESS) {
	    dip->di_dir_created = TRUE;     /* Show we created directory. */
	}
	/* Note (status == WARNING) if the directory already exist!*/
    } else {
	struct stat sb;
	/*
	 * For input files, the directory better exist!
	 */
	dip->di_dirpath = strdup(dip->di_dir);
	if ( (status = stat(dip->di_dirpath, &sb)) == FAILURE) {
	    Perror("Can't access '%s'", dip->di_dirpath);
	}
    }
    return (status);
}

void
setup_toplevel_directory(dinfo_t *dip, char *dir)
{
    /*
     * Ensure the top level directory ends with a directory separator.
     * 
     * Note: This is needed for Windows dirve letters and when creating
     * multiple files with multiple processes (and no subdirectories).
     */ 
    if (dir[strlen(dir)-1] != DIRSEP) {
	char *dirp = Malloc(strlen(dir) + 2);
	sprintf(dirp, "%s%c", dir, DIRSEP);
	dip->di_dir = dirp;
    } else {
	dip->di_dir = strdup(dir);
    }
    return;
}

#if defined(SCSI)

void
strip_trailing_spaces(char *bp)
{
    int i = strlen(bp);

    while (i) {
	if (bp[--i] == ' ') {
	    bp[i] = '\0';
	    continue;
	}
	break;
    }
    return;
}

int
init_scsi_info(dinfo_t *dip)
{
    scsi_generic_t *sgp;
    scsi_addr_t *sap;
    inquiry_t *inquiry;
    int error;
    
    sgp = Malloc( sizeof(*sgp) );
    if (sgp == NULL) return (FAILURE);

    sgp->debug = dip->di_sDebugFlag;
    sgp->errlog = dip->di_scsi_errors;
    sap = &sgp->scsi_addr;
    /* Note: Only AIX uses this, but must be -1 for any path! */
    sap->scsi_path  = -1;	/* Indicates no path specified. */
    /*
     * Recovery Parameters:
     */ 
    sgp->recovery_flag  = ScsiRecoveryFlagDefault;
    sgp->recovery_delay = ScsiRecoveryDelayDefault;
    sgp->recovery_limit = ScsiRecoveryRetriesDefault;

    if (dip->di_scsi_dsf) {
	sgp->dsf = dip->di_scsi_dsf;
    } else {
	sgp->dsf = dip->di_dname;
    }
    error = os_open_device(sgp);
    if (error) {
	dip->di_scsi_flag = FALSE;
	free(sgp);
	return (error);
    }

    dip->di_sgp = sgp;
    dip->di_inquiry = inquiry = Malloc(sizeof(*inquiry));
    if (dip->di_inquiry == NULL) return (FAILURE);
    
    sgp->qtag_type  = SG_SIMPLE_Q;
    sgp->sense_length   = RequestSenseDataLength;
    sgp->sense_data = malloc_palign(sgp->sense_length, 0);
    if (sgp->sense_data == NULL) return (FAILURE);
    /*
     * If error reporting is enabled, log errors as warnings (for now).
     */
    sgp->warn_on_error = True;
    
    error = Inquiry(sgp->fd, sgp->dsf, dip->di_sDebugFlag, dip->di_scsi_errors,
		    NULL, &sgp, inquiry, sizeof(*inquiry), 0, 0, dip->di_scsi_timeout);
    if (error) {
	(void)os_close_device(sgp);
	dip->di_scsi_flag = FALSE;	/* Assume *not* a SCSI device! */
	return (error);
    }
    dip->di_vendor_id = Malloc(INQ_VID_LEN + 1);
    dip->di_product_id = Malloc(INQ_PID_LEN + 1);
    dip->di_revision_level = Malloc(INQ_REV_LEN + 1);
    (void)strncpy(dip->di_vendor_id, (char *)inquiry->inq_vid, INQ_VID_LEN);
    (void)strncpy(dip->di_product_id, (char *)inquiry->inq_pid, INQ_PID_LEN);
    (void)strncpy(dip->di_revision_level, (char *)inquiry->inq_revlevel, INQ_REV_LEN);
    /* Remove trailing spaces. */
    strip_trailing_spaces(dip->di_vendor_id);
    strip_trailing_spaces(dip->di_product_id);
    strip_trailing_spaces(dip->di_revision_level);

    error = GetCapacity(sgp, &dip->di_block_length, &dip->di_device_capacity);
    if (dip->di_idt == IDT_DEVICEID) {
	dip->di_device_id  = GetDeviceIdentifier(sgp->fd, sgp->dsf, dip->di_sDebugFlag, dip->di_scsi_errors,
						 NULL, &sgp, inquiry, dip->di_scsi_timeout);
    } else if (dip->di_idt == IDT_SERIALID) {
	dip->di_serial_number = GetSerialNumber(sgp->fd, sgp->dsf, dip->di_sDebugFlag, dip->di_scsi_errors,
						NULL, &sgp, inquiry, dip->di_scsi_timeout);
    } else if (dip->di_idt == IDT_BOTHIDS) {
	dip->di_device_id  = GetDeviceIdentifier(sgp->fd, sgp->dsf, dip->di_sDebugFlag, dip->di_scsi_errors,
						 NULL, &sgp, inquiry, dip->di_scsi_timeout);
	dip->di_serial_number = GetSerialNumber(sgp->fd, sgp->dsf, dip->di_sDebugFlag, dip->di_scsi_errors,
						NULL, &sgp, inquiry, dip->di_scsi_timeout);
    }
    //(void)os_close_device(sgp);
    return(error);
}

/*
 * NOTE: This is temporary, until we merge spt functions into dt!
 */ 
#if defined(WIN32)

static char *spt_path = "X:\\bin\\spt.last.exe";

#else /* !defined(WIN32) */

static char *spt_path = "/usr/software/test/bin/spt.last";

#endif /* defined(WIN32) */

int
unmap_blocks(dinfo_t *dip, large_t starting_block, large_t data_limit)
{
    char cmd[STRING_BUFFER_SIZE];
    int status;
    
    (void)sprintf(cmd, "%s dsf=%s cdb=0x42 starting=" FUF " limit=" FUF " enable=sense,recovery",
		  (dip->di_spt_path) ? dip->di_spt_path : spt_path,
		  dip->di_sgp->dsf, starting_block, data_limit);
    if (dip->di_sDebugFlag) strcat(cmd, " enable=Debug,xdebug,debug");
    status = ExecuteCommand(dip, cmd);
    return (status);
}

#endif /* defined(SCSI) */
