/****************************************************************************
 *									    *
 *			  COPYRIGHT (c) 2006 - 2013			    *
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
 * Module:	libscsi.c
 * Author:	Robin T. Miller
 * Date:	March 24th, 2005
 *
 * Description:
 *	This module contains common SCSI functions, which are meant to be
 * a front-end to calling the underlying OS dependent SCSI functions,
 * when appropriate, to send a SCSI CDB (Command Descriptor Block).
 * 
 * Modification History:
 * 
 * January 23rd, 2013 by Robin T. Miller
 * 	Update libExecuteCdb() to allow a user defined execute CDB function.
 * 	Added command retries, including OS specific error recovery.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>

#include "libscsi.h"
#include "scsi_opcodes.h"

/*
 * Local Declarations:
 */

/*
 * Common Text Strings:
 */
#if 0
static char *bad_conversion_str =
"Warning: unexpected conversion size of %d bytes.\n";
#endif

/*
 * Forward Declarations:
 */ 
scsi_generic_t *init_scsi_generic(void);

/* ======================================================================== */

scsi_generic_t *
init_scsi_generic(void)
{
    scsi_generic_t *sgp;
    sgp = Malloc(sizeof(*sgp));
    if (sgp == NULL) return (NULL);
    sgp->fd = INVALID_HANDLE_VALUE;
    sgp->sense_length = RequestSenseDataLength;
    sgp->sense_data   = malloc_palign(sgp->sense_length, 0);
    /*
     * Recovery Parameters:
     */ 
    sgp->recovery_flag  = ScsiRecoveryFlagDefault;
    sgp->recovery_delay = ScsiRecoveryDelayDefault;
    sgp->recovery_limit = ScsiRecoveryRetriesDefault;
    return (sgp);
}

hbool_t
libIsRetriable(scsi_generic_t *sgp)
{
    hbool_t retriable = False;

    if (sgp->recovery_retries++ < sgp->recovery_limit) {
	/*
	 * Try OS specific first, then check for common retriables.
	 */ 
	retriable = os_is_retriable(sgp);
	if (retriable == False) {
	    scsi_sense_t *ssp = sgp->sense_data;
	    if (sgp->debug == True) {
		print_scsi_status(sgp->scsi_status, ssp->sense_key, ssp->asc, ssp->asq);
	    }
	    if ( (sgp->scsi_status == SCSI_BUSY) ||
		 (sgp->scsi_status == SCSI_QUEUE_FULL) ) {
		retriable = True;
	    } else if (sgp->scsi_status == SCSI_CHECK_CONDITION) {
		if (ssp->sense_key == SKV_UNIT_ATTENTION) {
		    if (ssp->asc != ASC_RECOVERED_DATA) {
			retriable = True;
		    }
		} else if ( (ssp->sense_key == SKV_NOT_READY) &&
			    (ssp->asc == ASC_NOT_READY) ) {
		    /* Lots of reasons, but we retry them all! */
		    /* Includes:
		     * "Logical unit is in process of becoming ready"
		     * "Logical unit not ready, space allocation in progress"
		     * Note: We'll be more selective, if this becomes an issue!
		     */ 
		    retriable = True;
		}
	    }
	}
    }
    return (retriable);
}

/* ======================================================================== */

/*
 * libExecuteCdb() = Execute a SCSI Command Descriptor Block (CDB).
 *
 * Inputs:
 *  sgp = Pointer to SCSI generic pointer.
 *
 * Return Value:
 *      Returns 0/-1 for Success/Failure.
 */
int
libExecuteCdb(scsi_generic_t *sgp)
{
    int error;
    hbool_t retriable;

    /*
     * Allow user to define their own execute CDB function.
     */
    if (sgp->execute_cdb && sgp->opaque) {
	error = (*sgp->execute_cdb)(sgp->opaque, sgp);
	return (error);
    }

    sgp->recovery_retries = 0;
    do {
	retriable = False;
	/*
	 * Ensure the sense data is cleared for emiting status.
	 */
	memset(sgp->sense_data, '\0', sgp->sense_length);
	/* Clear these too, since IOCTL may fail so never get updated! */
	sgp->os_error = 0;		/* The system call error (if any). */
	sgp->scsi_status = sgp->driver_status = sgp->host_status = sgp->data_resid = 0;

	/*
	 * Call OS dependent SCSI Pass-Through (spt) function.
	 */
	error = os_spt(sgp);
	if ( ((error == FAILURE) || (sgp->error == True)) && sgp->recovery_flag) {
	    if (sgp->recovery_retries == sgp->recovery_limit) {
		Fprintf("Exceeded retry limit (%u) for this request!\n", sgp->recovery_limit);
	    } else {
		retriable = libIsRetriable(sgp);
		if (retriable == True) {
		    (void)os_sleep(sgp->recovery_delay);
		    if (sgp->errlog == True) {
			/* Folks wish to see the actual error too! */
			if (error == FAILURE) {		/* The system call failed! */
			    libReportIoctlError(sgp, True);
			} else {
			    libReportScsiError(sgp, True);
			}
			Fprintf("Warning: Retrying %s after %u second delay, retry #%u...\n",
			       sgp->cdb_name, sgp->recovery_delay, sgp->recovery_retries);
		    }
		}
	    }
	}
    } while (retriable == True);

    if (error == FAILURE) {		/* The system call failed! */
	if (sgp->errlog == True) {
	    libReportIoctlError(sgp, sgp->warn_on_error);
	}
    } else if ( (sgp->error == True) && (sgp->errlog == True) ) { /* SCSI error. */
	libReportScsiError(sgp, sgp->warn_on_error);
    }

    if (sgp->error == True) {
        error = FAILURE;      /* Tell caller we've had an error! */
    }
    return (error);
}

void
libReportIoctlError(scsi_generic_t *sgp, hbool_t warn_on_error)
{
    if (sgp->errlog == True) {
	time_t error_time = time((time_t *) 0);
	Fprintf("%s: Error occurred on %s",
		(warn_on_error == True) ? "Warning" : "ERROR",
		ctime(&error_time));
	Fprintf("%s failed on device %s\n", sgp->cdb_name, sgp->dsf);
    }
    return;
}

void
libReportScsiError(scsi_generic_t *sgp, hbool_t warn_on_error)
{
    time_t error_time = time((time_t *) 0);
    char *host_msg = os_host_status_msg(sgp);
    char *driver_msg = os_driver_status_msg(sgp);
    scsi_sense_t *ssp = sgp->sense_data;
    char *ascq_msg = ScsiAscqMsg(ssp->asc, ssp->asq);

    Fprintf("%s: Error occurred on %s",
	    (warn_on_error == True) ? "Warning" : "ERROR",
	    ctime(&error_time));
    Fprintf("%s failed on device %s\n", sgp->cdb_name, sgp->dsf);
    Fprintf("SCSI Status = %#x (%s)\n", sgp->scsi_status, ScsiStatus(sgp->scsi_status));
    if (host_msg && driver_msg) {
	Fprintf("Host Status = %#x (%s), Driver Status = %#x (%s)\n",
	       sgp->host_status, host_msg, sgp->driver_status, driver_msg);
    } else if (host_msg || driver_msg) {
	if (host_msg) {
	    Fprintf("Host Status = %#x (%s)\n", sgp->host_status, host_msg);
	}
	if (driver_msg) {
	    Fprintf("Driver Status = %#x (%s)\n", sgp->driver_status, driver_msg);
	}
    } else if (sgp->host_status || sgp->driver_status) {
	Fprintf("Host Status = %#x, Driver Status = %#x\n",
	       sgp->host_status, sgp->driver_status);
    }
    Fprintf("Sense Key = %d = %s, Sense Code/Qualifier = (%#x, %#x)",
	   ssp->sense_key, SenseKeyMsg(ssp->sense_key),
	   ssp->asc, ssp->asq);
    if (ascq_msg) {
      Fprint(" - %s\n", ascq_msg);
    } else {
      Fprint("\n");
    }
    fflush(stderr);
    if (sgp->debug && ssp->error_code) {
	DumpSenseData(sgp, ssp);
    }
    return;
}

/* ======================================================================== */

/*
 * NOTE: These API's were written a long time ago, with the ability to invoke
 * them without defining SCSI structures, for ease of use. Since then, I have
 * found it easier (and more efficient) to expose structs to external callers.
 * Removing the optional sg allocation and initialization makes this cleaner!
 */

#include "inquiry.h"

/* ======================================================================== */

/*
 * Declarations/Definitions for Inquiry Command:
 */
#define InquiryName           "Inquiry"
#define InquiryOpcode         0x12
#define InquiryCdbSize        6
#define InquiryTimeout        (30 * MSECS)

/*
 * Inquiry Command Descriptor Block:
 */
struct Inquiry_CDB {
	u_char	opcode;			/* Operation Code.		[0] */
#if defined(_BITFIELDS_LOW_TO_HIGH_)
	u_char	evpd	: 1,		/* Enable Vital Product Data.	[1] */
			: 4,		/* Reserved.			    */
		lun	: 3;		/* Logical Unit Number.		    */
#elif defined(_BITFIELDS_HIGH_TO_LOW_)
	u_char	lun	: 3,		/* Logical Unit Number.		    */
			: 4,		/* Reserved.			    */
		evpd	: 1;		/* Enable Vital Product Data.	[1] */
#else
#	error "bitfield ordering is NOT defined!"
#endif /* defined(_BITFIELDS_LOW_TO_HIGH_) */
	u_char	pgcode	: 8;		/* EVPD Page Code.		[2] */
	u_char		: 8;		/* Reserved.			[3] */
	u_char	alclen;			/* Allocation Length.		[4] */
#if defined(_BITFIELDS_LOW_TO_HIGH_)
	u_char	link	: 1,		/* Link.			[5] */
		flag	: 1,		/* Flag.			    */
			: 4,		/* Reserved.			    */
		vendor	: 2;		/* Vendor Unique.		    */
#elif defined(_BITFIELDS_HIGH_TO_LOW_)
	u_char	vendor	: 2,		/* Vendor Unique.		    */
			: 4,		/* Reserved.			    */
		flag	: 1,		/* Flag.			    */
		link	: 1;		/* Link.			[5] */
#else
#	error "bitfield ordering is NOT defined!"
#endif /* defined(_BITFIELDS_LOW_TO_HIGH_) */
};

/*
 * Inquiry() - Send a SCSI Inquiry Command.
 *
 * Inputs:
 *  fd     = The file descriptor to issue bus reset to.
 *  dsf    = The device special file (raw or "sg" for Linux).
 *  debug  = Flag to control debug output.
 *  errlog = Flag to control error logging. (True logs error)
 *                                          (False suppesses)
 *  sap    = Pointer to SCSI address (optional).
 *  sgpp   = Pointer to scsi generic pointer (optional).
 *  data   = Buffer for received Inquiry data.
 *  len    = The length of the data buffer.
 *  page   = The Inquiry VPD page (if any).
 *  flags  = OS specific SCSI flags (if any).
 *  timeout = The timeout value (in ms).
 *
 * Return Value:
 *  Returns the status from the IOCTL request which is:
 *    0 = Success, -1 = Failure
 *
 * Note:  If the caller supplies a SCSI generic pointer, then
 * it's the callers responsibility to free this structure, along
 * with the data buffer and sense buffer.  This capability is
 * provided so the caller can examine SCSI status, sense data,
 * and data transfers, to make (more) intelligent decisions.
 */
int
Inquiry(HANDLE fd, char *dsf, hbool_t debug, hbool_t errlog,
	scsi_addr_t *sap, scsi_generic_t **sgpp,
	void *data, unsigned int len, unsigned char page,
	unsigned int sflags, unsigned int timeout)
{
    scsi_generic_t *sgp;
    struct Inquiry_CDB *cdb; 
    int error;

    /*
     * Setup and/or allocate a SCSI generic data structure.
     */
    if (sgpp && *sgpp) {
	sgp = *sgpp;
    } else {
	sgp = init_scsi_generic();
    }
    if (sgp->fd == INVALID_HANDLE_VALUE) {
	sgp->fd     = fd;
	sgp->dsf    = dsf;
    }
    memset(sgp->cdb, 0, sizeof(sgp->cdb));
    if (data && len) memset(data, 0, len);
    cdb             = (struct Inquiry_CDB *)sgp->cdb;
    cdb->opcode     = InquiryOpcode;
    if (page) {
	cdb->pgcode = page;
	cdb->evpd   = 1;
    }
    cdb->alclen     = len;
    sgp->cdb_size   = InquiryCdbSize;
    sgp->cdb_name   = InquiryName;
    sgp->data_dir   = scsi_data_read;
    sgp->data_buffer= data;
    sgp->data_length= len;
    sgp->errlog     = errlog;
    sgp->iface      = NULL;
    sgp->sflags     = sflags;
    sgp->timeout    = (timeout) ? timeout : InquiryTimeout;
    sgp->debug	    = debug;
    /*
     * If a SCSI address was specified, do a structure copy.
     */
    if (sap) {
	sgp->scsi_addr = *sap;	/* Copy the SCSI address info. */
    }
    
    error = libExecuteCdb(sgp);

    /*
     * If the user supplied a pointer, send the SCSI generic data
     * back to them for further analysis.
     */
    if (sgpp) {
	if (*sgpp == NULL) {
	    *sgpp = sgp;	/* Return the generic data pointer. */
	}
    } else {
	free_palign(sgp->sense_data);
	free(sgp);
    }
    return(error);
}

/* ======================================================================== */

/*
 * GetDeviceIdentifier() - Gets Inquiry Device ID Page.
 *
 * Inputs:
 *  fd     = The file descriptor.
 *  dsf    = The device special file (raw or "sg" for Linux).
 *  debug  = Flag to control debug output.
 *  errlog = Flag to control error logging. (True logs error)
 *                                          (False suppesses)
 *  sap    = Pointer to SCSI address (optional).
 *  sgpp   = Pointer to SCSI generic pointer (optional).
 *  inqp   = Pointer to device Inquiry data.
 *  timeout = The timeout value (in ms).
 *
 * Return Value:
 *    Returns NULL of no device ID page or it's invalid.
 *    Otherwise, returns a pointer to a malloc'd buffer w/ID.
 */
char *
GetDeviceIdentifier(HANDLE fd, char *dsf, hbool_t debug, hbool_t errlog,
		    scsi_addr_t *sap, scsi_generic_t **sgpp,
		    void *inqp, unsigned int timeout)
{
    inquiry_t *inquiry = inqp;
    inquiry_page_t inquiry_data;  
    inquiry_page_t *inquiry_page = &inquiry_data;
    inquiry_header_t *inqh = &inquiry_page->inquiry_hdr;
    inquiry_ident_descriptor_t *iid;
    unsigned char page = INQ_DEVICE_PAGE;
    size_t page_length;
    char *bp = NULL;
    int status;
    /* Identifiers in order of precedence: (the "Smart" way :-) */
    /* REMEMBER:  The lower values have *higher* precedence!!! */
    enum pidt {
	REGEXT, REG, EXT_V, EXT_0, EUI64, TY1_VID, BINARY, ASCII, NONE
    };
    enum pidt pid_type = NONE;	/* Precedence ID type. */

    status = Inquiry(fd, dsf, debug, errlog, NULL, NULL,
		     inquiry_page, sizeof(*inquiry_page), page, 0, timeout);

    if (status != SUCCESS) return(NULL);

    /*
     * Note: The extra check is for non-compliant SCSI devices.
     */
    if ( (inqh->inq_page_code != page) ||
	 (inqh->inq_dtype != inquiry->inq_dtype) ) {
	return(NULL);
    }

    page_length = (size_t) inquiry_page->inquiry_hdr.inq_page_length;
    iid = (inquiry_ident_descriptor_t *)inquiry_page->inquiry_page_data;

    /*
     * Snarf'ed out of CAM's configuration logic (ccfg.c).
     *
     * Notes:
     *	- We loop through ALL descriptors, enforcing the precedence
     *	  order defined above (see enum pidt).  This is because some
     *	  devices return more than one identifier.
     *	- This logic differs from CAM ccfg code slightly, as it
     *	  accepts unknown BINARY device ID's, which I think is Ok.
     */
    while ( (ssize_t)page_length > 0 ) {
	unsigned char *fptr = (unsigned char *)iid + sizeof(*iid);

	switch (iid->iid_code_set) {
	    
	    case IID_CODE_SET_ASCII: {
		    /* Only accept Vendor ID's of Type 1. */
		    if ( (pid_type > TY1_VID) &&
			 (iid->iid_ident_type == IID_ID_TYPE_T10_VID) ) {
			int id_len = iid->iid_ident_length + sizeof(inquiry->inq_pid);
			if (bp) {
			    free(bp) ; bp = NULL;
			};
			bp = (char *)Malloc(id_len + 1);
			if (bp == NULL)	return(NULL);
			pid_type = TY1_VID;
			memcpy(bp, inquiry->inq_pid, sizeof(inquiry->inq_pid));
			memcpy((bp + sizeof(inquiry->inq_pid)), fptr, iid->iid_ident_length);
		    }
		    /* Continue looping looking for IEEE identifier. */
		    break;
		}
		/*
		 * This is the preferred (unique) identifier.
		 */
	    case IID_CODE_SET_BINARY: {

		    switch (iid->iid_ident_type) {
			
			case IID_ID_TYPE_NAA: {
				enum pidt npid_type;
				int i = 0;

				/*
				 * NAA is the high order 4 bits of the 1st byte.
				 */
				switch ( (*fptr >> 4) & 0xF) {
				    /* TODO: Add defines for NAA definitions! */
				    case 0x6:	  /* IEEE Registered */
					npid_type = REGEXT;
					break;
				    case 0x5:	  /* IEEE Registered Extended */
					npid_type = REG;
					break;
				    case 0x2:	  /* ???? */
					npid_type = EXT_V;
					break;
				    case 0x1:	  /* ???? */
					npid_type = EXT_0;
					break;
				    default:
					/* unrecognized */
					npid_type = BINARY;
					break;
				}
				/*
				 * If the previous precedence ID is of lower priority,
				 * that is a higher value, then make this pid the new.
				 */
				if ( (pid_type > npid_type) ) {
				    int blen = (iid->iid_ident_length * 3);
				    char *bptr;
				    pid_type = npid_type; /* Set the new precedence type */
				    if (bp) {
					free(bp) ; bp = NULL;
				    };
				    bptr = bp = (char *)Malloc(blen);
				    if (bp == NULL) return(NULL);

				    /* Format as: xxxx-xxxx... */
				    while (i < (int)iid->iid_ident_length) {
					bptr += sprintf(bptr, "%02x", fptr[i++]);
					if (( (i % 2) == 0) &&
					    (i < (int)iid->iid_ident_length) ) {
					    bptr += sprintf(bptr, "-");
					}
				    }
				}
				break;
			    }
			case IID_ID_TYPE_EUI64: {
				int blen, i = 0;
				char *bptr;

				if ( (pid_type <= EUI64) ) {
				    break;
				}
				pid_type = EUI64;
				blen = (iid->iid_ident_length * 3);
				if (bp) {
				    free(bp) ; bp = NULL;
				};
				bptr = bp = (char *)Malloc(blen);
				if (bp == NULL)	return(NULL);

				/* Format as: xxxx-xxxx... */
				while (i < (int)iid->iid_ident_length) {
				    bptr += sprintf(bptr, "%02x", fptr[i++]);
				    if (( (i % 2) == 0) &&
					(i < (int)iid->iid_ident_length) ) {
					bptr += sprintf(bptr, "-");
				    }
				}
				break;
			    }
			default: {
				if (debug) {
				    Fprintf("Unknown identifier %#x\n", iid->iid_ident_type);
				}
				break;
			    }
		    } /* switch (iid->iid_ident_type) */
		} /* case IID_CODE_SET_BINARY */

	    default:
		break;

	} /* switch (iid->iid_code_set) */

	page_length -= iid->iid_ident_length + sizeof(*iid);
	iid = (inquiry_ident_descriptor_t *)((long) iid + iid->iid_ident_length + sizeof(*iid));

    } /* while ( (ssize_t)page_length > 0 ) */

    /* NOTE: Caller MUST free allocated buffer! */
    return(bp);
}

/*
 * GetSerialNumber() - Gets Inquiry Serial Number Page.
 *
 * Inputs:
 *  fd     = The file descriptor.
 *  dsf    = The device special file (raw or "sg" for Linux).
 *  errlog = Flag to control error logging. (True logs error)
 *                                          (False suppesses)
 *  sap    = Pointer to SCSI address (optional).
 *  sgpp   = Pointer to SCSI generic pointer (optional).
 *  inqp   = Pointer to device Inquiry data.
 *  timeout = The timeout value (in ms).
 *
 * Return Value:
 *    Returns NULL if no serial number page or it's invalid.
 *    Otherwise, returns a pointer to a malloc'd buffer w/serial #.
 */
char *
GetSerialNumber(HANDLE fd, char *dsf, hbool_t debug, hbool_t errlog,
		scsi_addr_t *sap, scsi_generic_t **sgpp,
		void *inqp, unsigned int timeout)
{
    inquiry_t *inquiry = inqp;
    inquiry_page_t inquiry_data;  
    inquiry_page_t *inquiry_page = &inquiry_data;
    inquiry_header_t *inqh = &inquiry_page->inquiry_hdr;
    unsigned char page = INQ_SERIAL_PAGE;
    size_t page_length;
    char *bp;
    int status;

    status = Inquiry(fd, dsf, debug, errlog, NULL, sgpp,
		     inquiry_page, sizeof(*inquiry_page), page, 0, timeout);

    if (status != SUCCESS) return(NULL);

    /*
     * Note: The extra check is for non-compliant SCSI devices.
     */
    if ( (inqh->inq_page_code != page) ||
	 (inqh->inq_dtype != inquiry->inq_dtype) ) {
	return(NULL);
    }

    page_length = (size_t) inquiry_page->inquiry_hdr.inq_page_length;
    bp = (char *) Malloc (page_length + 1);
    if (bp == NULL) return(NULL);
    strncpy (bp, (char *)inquiry_page->inquiry_page_data, page_length);
    bp[page_length] = '\0';
    /* NOTE: Caller MUST free allocated buffer! */
    return(bp);
}

/*
 * GetUniqueID - Get The Devices' Unique ID.
 *
 * Description:
 *  This function returns a unique identifer for this device.
 * We attemp to obtain the Inquiry Device ID page first, then
 * if that fails we attempt to obtain the serial num,ber page.
 *
 * Inputs:
 *  fd     = The file descriptor.
 *  dsf    = The device special file (raw or "sg" for Linux).
 *  identifier = Pointer to buffer to return identifier.
 *  idt    = The ID type(s) to attempt (IDT_BOTHIDS, IDT_DEVICEID, IDT_SERIALID)
 *  debug  = Flag to control debug output.
 *  errlog = Flag to control error logging. (True logs error)
 *                                          (False suppesses)
 *  timeout = The timeout value (in ms).
 *
 * Returns:
 *  Returns IDT_NONE and set identifier ptr to NULL if an error occurs.
 *  Returns IDT_DEVICEID if identifier points to an actual device ID.
 *  Returns IDT_SERIALID if identifier points to a manufactured identifier,
 *    using Inquiry vendor/product info and serial number page.
 *
 * Note: The identifier is dynamically allocated, so the caller is
 * responsible to free that memory, when it's no longer desired.
 */
idt_t
GetUniqueID(HANDLE fd, char *dsf, hbool_t debug,
	    char **identifier, idt_t idt,
	    hbool_t errlog, unsigned int timeout)
{
    inquiry_t inquiry_data;
    inquiry_t *inquiry = &inquiry_data;
    char *serial_number;
    int status;

    *identifier = NULL;
    /*
     * Start off by requesting the standard Inquiry data.
     */
    status = Inquiry(fd, dsf, debug, errlog, NULL, NULL,
		     inquiry, sizeof(*inquiry), 0, 0, timeout);
    if (status != SUCCESS) {
	return(IDT_NONE);
    }

    if ( (idt == IDT_BOTHIDS) || (idt == IDT_DEVICEID) ) {
	/*
	 * The preferred ID, is from Inquiry Page 0x83 (Device ID).
	 */
	if (*identifier = GetDeviceIdentifier(fd, dsf, debug, errlog,
					      NULL, NULL, inquiry, timeout)) {
	    return(IDT_DEVICEID);
	}
    }

    if ( (idt == IDT_BOTHIDS) || (idt == IDT_SERIALID) ) {
	/*
	 * The less preferred WWID, is the serial number prepended with
	 * the vendor and product names to attempt uniqueness.
	 */
	if (serial_number = GetSerialNumber(fd, dsf, debug, errlog,
					    NULL, NULL, inquiry, timeout)) {
	    *identifier = Malloc(MAX_INQ_LEN + INQ_VID_LEN + INQ_PID_LEN);
	    *identifier[0] = '\0';
	    (void)strncpy(*identifier, (char *)inquiry->inq_vid, INQ_VID_LEN);
	    (void)strncat(*identifier, (char *)inquiry->inq_pid, INQ_PID_LEN);
	    (void)strcat(*identifier, serial_number);
	    (void)free(serial_number);
	    return(IDT_SERIALID);
	}
    }
    return(IDT_NONE);
}

/* ======================================================================== */

/*
 * Declarations/Definitions for Read Capacity(10) Command:
 */
#define ReadCapacity10Name	"Read Capacity(10)"
#define ReadCapacity10Opcode	0x25
#define ReadCapacity10CdbSize	10 
#define ReadCapacity10Timeout	(30 * MSECS)

typedef struct ReadCapacity10_CDB {
    uint8_t opcode;
    uint8_t reserved_byte1;
    uint8_t lba[4];
    uint8_t reserved_byte7;
    uint8_t reserved1_byte8;
#if defined(_BITFIELDS_LOW_TO_HIGH_)
    uint8_t pmi     :1,		/* Partial medium indicator             */
                    :7;		/* 7 bits reserved                      */
#elif defined(_BITFIELDS_HIGH_TO_LOW_)
    uint8_t         :7,		/* 7 bits reserved                      */
            pmi     :1;		/* Partial medium indicator             */
#else
#       error "bitfield ordering is NOT defined!"
#endif /* defined(_BITFIELDS_LOW_TO_HIGH_) */
    uint8_t control;
} ReadCapacity10_CDB_t;

typedef struct ReadCapacity10_data {
    uint8_t last_block[4];
    uint8_t block_length[4];
} ReadCapacity10_data_t;

/*
 * ReadCapacity10() - Issue Read Capacity (10) Command.
 *
 * Inputs:
 *  fd     = The file descriptor to issue bus reset to.
 *  dsf    = The device special file (raw or "sg" for Linux).
 *  debug  = Flag to control debug output.
 *  errlog = Flag to control error logging. (True logs error)
 *                                          (False suppesses)
 *  sap    = Pointer to SCSI address (optional).
 *  sgpp   = Pointer to SCSI generic pointer (optional).
 *  data   = Buffer for received capacity data.
 *  len    = The length of the data buffer.
 *  sflags = OS specific SCSI flags (if any).
 *  timeout = The timeout value (in ms).
 *
 * Return Value:
 *  Returns the status from the IOCTL request which is:
 *    0 = Success, -1 = Failure
 *
 * Note:  If the caller supplies a SCSI generic pointer, then
 * it's the callers responsibility to free this structure, along
 * with the data buffer and sense buffer.  This capability is
 * provided so the caller can examine SCSI status, sense data,
 * and data transfers, to make (more) intelligent decisions.
 */
int
ReadCapacity10(HANDLE fd, char *dsf, hbool_t debug, hbool_t errlog,
	       scsi_addr_t *sap, scsi_generic_t **sgpp,
	       void *data, unsigned int len,
	       unsigned int sflags, unsigned int timeout)
{
    scsi_generic_t *sgp;
    int error;

    /*
     * Setup and/or allocate a SCSI generic data structure.
     */
    if (sgpp && *sgpp) {
	sgp = *sgpp;
    } else {
	sgp = init_scsi_generic();
    }
    if (sgp->fd == INVALID_HANDLE_VALUE) {
	sgp->fd     = fd;
	sgp->dsf    = dsf;
    }
    memset(sgp->cdb, 0, sizeof(sgp->cdb));
    if (data && len) memset(data, 0, len);
    sgp->cdb[0]     = ReadCapacity10Opcode;
    sgp->cdb_size   = ReadCapacity10CdbSize;
    sgp->cdb_name   = ReadCapacity10Name;
    sgp->data_dir   = scsi_data_read;
    sgp->data_buffer= data;
    sgp->data_length= len;
    sgp->errlog     = errlog;
    sgp->iface      = NULL;
    sgp->timeout    = (timeout) ? timeout : ReadCapacity10Timeout;
    sgp->debug	    = debug;
    /*
     * If a SCSI address was specified, do a structure copy.
     */
    if (sap) {
	sgp->scsi_addr = *sap;	/* Copy the SCSI address info. */
    }

    error = libExecuteCdb(sgp);

    /*
     * If the user supplied a pointer, send the SCSI generic data
     * back to them for further analysis.
     */
    if (sgpp) {
	if (*sgpp == NULL) {
	    *sgpp = sgp;	/* Return the generic data pointer. */
	}
    } else {
	free_palign(sgp->sense_data);
	free(sgp);
    }
    return(error);
}

/* ======================================================================== */

/*
 * Declarations/Definitions for Read Capacity(16) Command:
 */
#define ReadCapacity16Name	"Read Capacity(16)"
#define ReadCapacity16Opcode	0x9e
#define ReadCapacity16Subcode	0x10
#define ReadCapacity16CdbSize	16 
#define ReadCapacity16Timeout	(30 * MSECS)

typedef struct ReadCapacity16_CDB {
    uint8_t opcode;
    uint8_t service_action;
    uint8_t lba[8];
    uint8_t allocation_length[4];
    uint8_t flags;
    uint8_t control;
} ReadCapacity16_CDB_t;

typedef struct ReadCapacity16_data {
    uint8_t last_block[8];
    uint8_t block_length[4];
    uint8_t protection_info;
    uint8_t logical_blocks_per_physical_block;
    uint8_t lowest_aligned[2];
    uint8_t reserved[16];
} ReadCapacity16_data_t;

/*
 * ReadCapacity16() - Issue Read Capacity (16) Command.
 *
 * Inputs:
 *  fd     = The file descriptor to issue bus reset to.
 *  dsf    = The device special file (raw or "sg" for Linux).
 *  debug  = Flag to control debug output.
 *  errlog = Flag to control error logging. (True logs error)
 *                                          (False suppesses)
 *  sap    = Pointer to SCSI address (optional).
 *  sgpp   = Pointer to SCSI generic pointer (optional).
 *  data   = Buffer for received capacity data.
 *  len    = The length of the data buffer.
 *  sflags = OS specific SCSI flags (if any).
 *  timeout = The timeout value (in ms).
 *
 * Return Value:
 *  Returns the status from the IOCTL request which is:
 *    0 = Success, -1 = Failure
 *
 * Note:  If the caller supplies a SCSI generic pointer, then
 * it's the callers responsibility to free this structure, along
 * with the data buffer and sense buffer.  This capability is
 * provided so the caller can examine SCSI status, sense data,
 * and data transfers, to make (more) intelligent decisions.
 */
int
ReadCapacity16(HANDLE fd, char *dsf, hbool_t debug, hbool_t errlog,
	       scsi_addr_t *sap, scsi_generic_t **sgpp,
	       void *data, unsigned int len,
	       unsigned int sflags, unsigned int timeout)
{
    scsi_generic_t *sgp;
    ReadCapacity16_CDB_t *cdb;
    int error;

    /*
     * Setup and/or allocate a SCSI generic data structure.
     */
    if (sgpp && *sgpp) {
	sgp = *sgpp;
    } else {
	sgp = init_scsi_generic();
    }
    if (sgp->fd == INVALID_HANDLE_VALUE) {
	sgp->fd     = fd;
	sgp->dsf    = dsf;
    }
    memset(sgp->cdb, 0, sizeof(sgp->cdb));
    if (data && len) memset(data, 0, len);
    cdb = (ReadCapacity16_CDB_t *)sgp->cdb;
    cdb->opcode     = ReadCapacity16Opcode;
    cdb->service_action = ReadCapacity16Subcode;
    HtoS(cdb->allocation_length,  len);
    sgp->cdb_size   = ReadCapacity16CdbSize;
    sgp->cdb_name   = ReadCapacity16Name;
    sgp->data_dir   = scsi_data_read;
    sgp->data_buffer= data;
    sgp->data_length= len;
    sgp->errlog     = errlog;
    sgp->iface      = NULL;
    sgp->timeout    = (timeout) ? timeout : ReadCapacity16Timeout;
    sgp->debug	    = debug;
    /*
     * If a SCSI address was specified, do a structure copy.
     */
    if (sap) {
	sgp->scsi_addr = *sap;	/* Copy the SCSI address info. */
    }

    error = libExecuteCdb(sgp);

    /*
     * If the user supplied a pointer, send the SCSI generic data
     * back to them for further analysis.
     */
    if (sgpp) {
	if (*sgpp == NULL) {
	    *sgpp = sgp;	/* Return the generic data pointer. */
	}
    } else {
	free_palign(sgp->sense_data);
	free(sgp);
    }
    return(error);
}

/* ======================================================================== */

int
GetCapacity(scsi_generic_t *sgp, u_int32 *device_size, large_t *device_capacity)
{
    ReadCapacity16_data_t ReadCapacity16_data;
    ReadCapacity16_data_t *rcdp = &ReadCapacity16_data;
    int status;
    
    /*
     * 16byte CDB may fail on some disks, but 10-byte should succeed!
     */ 
    status = ReadCapacity16(sgp->fd, sgp->dsf, sgp->debug,
			    FALSE, NULL, NULL,
			    rcdp, sizeof(*rcdp), 0, 0);
    if (status == SUCCESS) {
	*device_size = (uint32_t)StoH(rcdp->block_length);
	*device_capacity = StoH(rcdp->last_block) + 1;
    } else {
	ReadCapacity10_data_t ReadCapacity10_data;
	ReadCapacity10_data_t *rcdp = &ReadCapacity10_data;
	status = ReadCapacity10(sgp->fd, sgp->dsf, sgp->debug,
				TRUE, NULL, NULL,
				rcdp, sizeof(*rcdp), 0, 0);
	if (status == SUCCESS) {
	    *device_size = (uint32_t)StoH(rcdp->block_length);
	    *device_capacity = StoH(rcdp->last_block) + 1;
	}
    }
    if ( (status == SUCCESS) && sgp->debug) {
	Printf("Device: %s, Device Size: %u bytes, Capacity: " LUF " blocks\n",
	        sgp->dsf, *device_size, *device_capacity);
    }
    return (status);
}

/* ======================================================================== */

/*
 * Declarations/Definitions for Test Unit Ready Command:
 */
#define TestUnitReadyName     "Test Unit Ready"
#define TestUnitReadyOpcode   0
#define TestUnitReadyCdbSize  6
#define TestUnitReadyTimeout  (30 * MSECS)

/*
 * TestUnitReady() - Send a SCSI Test Unit Teady (tur).
 *
 * Inputs:
 *  fd     = The file descriptor to issue bus reset to.
 *  dsf    = The device special file (raw or "sg" for Linux).
 *  debug  = Flag to control debug output.
 *  errlog = Flag to control error logging. (True logs error)
 *                                          (False suppesses)
 *  sap    = Pointer to SCSI address (optional).
 *  sgpp   = Pointer to scsi generic pointer (optional).
 *  timeout = The timeout value (in ms).
 *
 * Return Value:
 *  Returns the status from the IOCTL request which is:
 *    0 = Success, -1 = Failure
 *
 * Note:  If the caller supplies a SCSI generic pointer, then
 * it's the callers responsibility to free this structure, along
 * with the data buffer and sense buffer.  This capability is
 * provided so the caller can examine SCSI status, sense data,
 * and data transfers, to make (more) intelligent decisions.
 */
int
TestUnitReady(HANDLE fd, char *dsf, hbool_t debug, hbool_t errlog,
	      scsi_addr_t *sap, scsi_generic_t **sgpp, unsigned int timeout)
{
    scsi_generic_t *sgp;
    int error;

    /*
     * Setup and/or allocate a SCSI generic data structure.
     */
    if (sgpp && *sgpp) {
	sgp = *sgpp;
    } else {
	sgp = init_scsi_generic();
    }
    if (sgp->fd == INVALID_HANDLE_VALUE) {
	sgp->fd     = fd;
	sgp->dsf    = dsf;
    }
    memset(sgp->cdb, 0, sizeof(sgp->cdb));
    sgp->cdb[0]     = TestUnitReadyOpcode;
    sgp->cdb_size   = TestUnitReadyCdbSize;
    sgp->cdb_name   = TestUnitReadyName;
    sgp->data_dir   = scsi_data_none;
    sgp->data_buffer= NULL;
    sgp->data_length= 0;
    sgp->errlog     = errlog;
    sgp->iface      = NULL;
    sgp->timeout    = (timeout) ? timeout : TestUnitReadyTimeout;
    sgp->debug	    = debug;
    /*
     * If a SCSI address was specified, do a structure copy.
     */
    if (sap) {
	sgp->scsi_addr = *sap;	/* Copy the SCSI address info. */
    }

    error = libExecuteCdb(sgp);

    /*
     * If the user supplied a pointer, send the SCSI generic data
     * back to them for further analysis.
     */
    if (sgpp) {
	if (*sgpp == NULL) {
	    *sgpp = sgp;	/* Return the generic data pointer. */
	}
    } else {
	free_palign(sgp->sense_data);
	free(sgp);
    }
    return(error);
}

/* ======================================================================== */

/*
 * Declarations/Definitions for Seek(10) Command:
 */
#define Seek10Name     "Seek(10)"
#define Seek10Opcode   0x2B
#define Seek10CdbSize  10
#define Seek10Timeout  (30 * MSECS)

typedef struct Seek10_CDB {
        u_char  opcode;         /* Operation Code.			[0] */
#if defined(_BITFIELDS_LOW_TO_HIGH_)
        u_char          :5,     /* 5 bits reserved                      [1] */
                lun     :3;     /* Logical unit number                      */
#elif defined(_BITFIELDS_HIGH_TO_LOW_)
        u_char  lun     :3,     /* Logical unit number                  [1] */
                        :5;     /* 5 bits reserved                          */
#else
#       error "bitfield ordering is NOT defined!"
#endif /* defined(_BITFIELDS_LOW_TO_HIGH_) */
	u_char	lba[4];		/* The logical block address.	      [2-5] */
	u_char	reserved[3];	/* Reserved.			      [6-8] */
        u_char  control;        /* The control byte                     [9] */
} Seek10_CDB_t;

/*
 * Seek10() - Send a Seek LBA Command.
 *
 * Inputs:
 *  fd     = The file descriptor to issue bus reset to.
 *  dsf    = The device special file (raw or "sg" for Linux).
 *  debug  = Flag to control debug output.
 *  errlog = Flag to control error logging. (True logs error)
 *                                          (False suppesses)
 *  sap    = Pointer to SCSI address (optional).
 *  sgpp   = Pointer to scsi generic pointer (optional).
 *  lba    = The logical block address.
 *  timeout = The timeout value (in ms).
 *
 * Return Value:
 *  Returns the status from the IOCTL request which is:
 *    0 = Success, -1 = Failure
 */
int
Seek10(HANDLE fd, char *dsf, hbool_t debug, hbool_t errlog,
       scsi_addr_t *sap, scsi_generic_t **sgpp,
       unsigned int lba, unsigned int timeout)
{
    scsi_generic_t *sgp;
    Seek10_CDB_t *cdb;
    int error;

    /*
     * Setup and/or allocate a SCSI generic data structure.
     */
    if (sgpp && *sgpp) {
	sgp = *sgpp;
    } else {
	sgp = init_scsi_generic();
    }
    if (sgp->fd == INVALID_HANDLE_VALUE) {
	sgp->fd     = fd;
	sgp->dsf    = dsf;
    }
    memset(sgp->cdb, 0, sizeof(sgp->cdb));
    cdb		    = (Seek10_CDB_t *)sgp->cdb;
    cdb->opcode	    = Seek10Opcode;
    HtoS(cdb->lba, lba);
    sgp->cdb_size   = Seek10CdbSize;
    sgp->cdb_name   = Seek10Name;
    sgp->data_dir   = scsi_data_none;
    sgp->data_buffer= NULL;
    sgp->data_length= 0;
    sgp->errlog     = errlog;
    sgp->iface      = NULL;
    sgp->timeout    = (timeout) ? timeout : Seek10Timeout;
    sgp->debug	    = debug;
    /*
     * If a SCSI address was specified, do a structure copy.
     */
    if (sap) {
	sgp->scsi_addr = *sap;	/* Copy the SCSI address info. */
    }

    error = libExecuteCdb(sgp);

    /*
     * If the user supplied a pointer, send the SCSI generic data
     * back to them for further analysis.
     */
    if (sgpp) {
	if (*sgpp == NULL) {
	    *sgpp = sgp;	/* Return the generic data pointer. */
	}
    } else {
	free_palign(sgp->sense_data);
	free(sgp);
    }
    return(error);
}

/* ======================================================================== */
/* Utility Functions: */

#if 0
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
ulong64
stoh(unsigned char *bp, size_t size)
{
    ulong64 value = 0L;

    switch (size) {
	
	case sizeof(unsigned char):
	    value = (ulong64) bp[0];
	    break;

	case sizeof(unsigned short):
	    value = ( ((ulong64)bp[0] << 8) | (ulong64)bp[1] );
	    break;

	case 0x03:
	    value = ( ((uint32_t)bp[0] << 16) | ((uint32_t)bp[1] << 8) |
		      (uint32_t) bp[2] );
	    break;

	case sizeof(unsigned int):
	    value = ( ((uint32_t)bp[0] << 24) | ((uint32_t)bp[1] << 16) |
		      ((uint32_t)bp[2] << 8)  | (uint32_t)bp[3]);
	    break;

	case 0x05:
	    value = ( ((ulong64)bp[0] << 32L) | ((ulong64)bp[1] << 24) |
		      ((ulong64)bp[2] << 16)  | ((ulong64)bp[3] << 8) |
		      (ulong64)bp[4] );       
	    break;

	case 0x06:
	    value = ( ((ulong64)bp[0] << 40L) | ((ulong64)bp[1] << 32L) |
		      ((ulong64)bp[2] << 24)  | ((ulong64)bp[3] << 16) |
		      ((ulong64)bp[4] << 8)   | (ulong64)bp[5] );
	    break;

	case 0x07:
	    value = ( ((ulong64)bp[0] << 48L) | ((ulong64)bp[1] << 40L) |
		      ((ulong64)bp[2] << 32L) | ((ulong64)bp[3] << 24) |
		      ((ulong64)bp[4] << 16)  | ((ulong64)bp[5] << 8) |
		      (ulong64)bp[6] );       
	    break;

	case sizeof(ulong64):
	    /*
	     * NOTE: Compiler dependency? If I don't cast each byte
	     * below to ulong64, the code generated simply ignored the
	     * bytes [0-3] and sign extended bytes [4-7].  Strange.
	     */
	    value = ( ((ulong64)bp[0] << 56L) | ((ulong64)bp[1] << 48L) |
		      ((ulong64)bp[2] << 40L) | ((ulong64)bp[3] << 32L) |
		      ((ulong64)bp[4] << 24)  | ((ulong64)bp[5] << 16) |
		      ((ulong64)bp[6] << 8)   | (ulong64)bp[7] );
	    break;

	default:
	    Fprintf (bad_conversion_str, size);
	    break;

    }
    return(value);
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
htos (unsigned char *bp, ulong64 value, size_t size)
{
    switch (size) {
	
	case sizeof(unsigned char):
	    bp[0] = (unsigned char) value;
	    break;

	case sizeof(unsigned short):
	    bp[0] = (unsigned char) (value >> 8);
	    bp[1] = (unsigned char) value;
	    break;

	case 0x03:
	    bp[0] = (unsigned char) (value >> 16);
	    bp[1] = (unsigned char) (value >> 8);
	    bp[2] = (unsigned char) value;
	    break;

	case sizeof(uint32_t):
	    bp[0] = (unsigned char) (value >> 24);
	    bp[1] = (unsigned char) (value >> 16);
	    bp[2] = (unsigned char) (value >> 8);
	    bp[3] = (unsigned char) value;
	    break;

	case 0x05:
	    bp[0] = (unsigned char) (value >> 32L);
	    bp[1] = (unsigned char) (value >> 24);
	    bp[2] = (unsigned char) (value >> 16);
	    bp[3] = (unsigned char) (value >> 8);
	    bp[4] = (unsigned char) value;
	    break;

	case 0x06:
	    bp[0] = (unsigned char) (value >> 40L);
	    bp[1] = (unsigned char) (value >> 32L);
	    bp[2] = (unsigned char) (value >> 24);
	    bp[3] = (unsigned char) (value >> 16);
	    bp[4] = (unsigned char) (value >> 8);
	    bp[5] = (unsigned char) value;
	    break;

	case 0x07:
	    bp[0] = (unsigned char) (value >> 48L);
	    bp[1] = (unsigned char) (value >> 40L);
	    bp[2] = (unsigned char) (value >> 32L);
	    bp[3] = (unsigned char) (value >> 24);
	    bp[4] = (unsigned char) (value >> 16);
	    bp[5] = (unsigned char) (value >> 8);
	    bp[6] = (unsigned char) value;
	    break;

	case sizeof(ulong64):
	    bp[0] = (unsigned char) (value >> 56L);
	    bp[1] = (unsigned char) (value >> 48L);
	    bp[2] = (unsigned char) (value >> 40L);
	    bp[3] = (unsigned char) (value >> 32L);
	    bp[4] = (unsigned char) (value >> 24);
	    bp[5] = (unsigned char) (value >> 16);
	    bp[6] = (unsigned char) (value >> 8);
	    bp[7] = (unsigned char) value;
	    break;

	default:
	    Fprintf (bad_conversion_str, size);
	    break;

    }
}
#endif /* 0 */

/*
 * scmn_cdb_length() - Calculate the Command Descriptor Block length.
 *
 * Description:
 *	This function is used to determine the SCSI CDB length.  This
 * is done by checking the command group code.  The command specified
 * is expected to be the actual SCSI command byte, not a psuedo command
 * byte.  There should be tables for vendor specific commands, since
 * there is no way of determining the length of these commands.
 *
 * Inputs:
 *	opcode = The SCSI operation code.
 *
 * Return Value:
 *	Returns the CDB length.
 */
int
GetCdbLength(unsigned char opcode)
{
    int cdb_length = 0;

    /*
     * Calculate the size of the SCSI command.
     */
    switch (opcode & SCSI_GROUP_MASK) {
	
	case SCSI_GROUP_0:
	    cdb_length = 6;	    /* 6 byte CDB. */
	    break;

	case SCSI_GROUP_1:
	case SCSI_GROUP_2:
	    cdb_length = 10;	    /* 10 byte CDB. */
	    break;

	case SCSI_GROUP_5:
	    cdb_length = 12;	    /* 12 byte CDB. */
	    break;

	case SCSI_GROUP_3:
	    cdb_length = 0;	    /* Reserved group. */
	    break;

	case SCSI_GROUP_4:
	    cdb_length = 16;	    /* 16 byte CDB. */
	    break;

	case SCSI_GROUP_6:
	case SCSI_GROUP_7:
	    cdb_length = 10;	    /* Vendor unique. */
	    break;
    }
    return(cdb_length);
}
