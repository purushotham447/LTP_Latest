#ifndef LIBSCSI_H
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
#define LIBSCSI_H

/*
 * These defines handle byte and bit ordering, used by many data structures
 * defined and used by Scu. While it's understood bit fields are not portable
 * these defines allow this nice (IMHO) feature to be utilized.  -Robin
 *
 * _LITTLE_ENDIAN / _BIG_ENDIAN:
 *  The natural byte order of the processor.  A pointer to an int points
 *  to the least/most significant byte of that int.
 *
 * _BITFIELDS_HIGH_TO_LOW_ / _BITFIELDS_LOW_TO_HIGH_:
 *  The C compiler assigns bit fields from the high/low to the low/high end
 *  of an int (most to least significant vs. least to most significant).
 */
#if defined(__hpux) || defined(__sparc) || defined(_AIX)
#  define _BIG_ENDIAN_    1
#  define _BITFIELDS_HIGH_TO_LOW_
#else /* !defined(__hpux) && !defined(__sparc) && !defined(_AIX) */
#  define _LITTLE_ENDIAN_ 1
#  define _BITFIELDS_LOW_TO_HIGH_
#endif /* defined(__hpux) || defined(__sparc) || defined(_AIX) */

#include "common.h"

/*
 * Local Defines:
 */
#define BITMASK(v)   (1L << v)          /* Convert value to bit mask.   */
#define ISSET(m,v)   (m & BITMASK(v))   /* Test bit set in bit mask.    */
#define ISCLR(m,v)   ((m & BITMASK(v)) == 0) /* Test bit clear in bit mask. */
#undef LTOB
#define LTOB(a,b)    ((a>>(b*8))&0xff)  /* Obtain byte from a long.     */
#define ALL_DEVICE_TYPES        0xffffU /* Supported for all devices.   */

#define MAX_CDB     64                  /* Maximum size of CDB.         */

#define ScsiRecoveryDelayDefault	2
#define ScsiRecoveryRetriesDefault	60
#define ScsiRecoveryFlagDefault		True

/*
 * Define Masks	for SCSI Group Codes.
 */
#define	SCSI_GROUP_0		0x00	/* SCSI	Group Code 0.		*/
#define	SCSI_GROUP_1		0x20	/* SCSI	Group Code 1.		*/
#define	SCSI_GROUP_2		0x40	/* SCSI	Group Code 2.		*/
#define	SCSI_GROUP_3		0x60	/* SCSI	Group Code 3.		*/
#define	SCSI_GROUP_4		0x80	/* SCSI	Group Code 4.		*/
#define	SCSI_GROUP_5		0xA0	/* SCSI	Group Code 5.		*/
#define	SCSI_GROUP_6		0xC0	/* SCSI	Group Code 6.		*/
#define	SCSI_GROUP_7		0xE0	/* SCSI	Group Code 7.		*/
#define	SCSI_GROUP_MASK		0xE0	/* SCSI	Group Code mask.	*/

/*
 * SCSI Address:
 *
 * Notes:
 *  General purpose for all OS's.
 *  Only Tru64 Unix (CAM) required b/t/l for SPT.
 */
typedef struct scsi_address {
    int scsi_bus;                       /* The bus number.                  */
    int scsi_chan;                      /* The channel number.              */
    int scsi_target;                    /* The target ID number.            */
    int scsi_lun;                       /* The Logical Unit Number.         */
    int scsi_path;                      /* The path number (for MPIO).      */
} scsi_addr_t;

typedef enum scsi_data_dir {
    scsi_data_none  = 0,                /* No data to be transferred.       */
    scsi_data_read  = 1,                /* Reading data from the device.    */
    scsi_data_write = 2                 /* Writing data to the device.      */
} scsi_data_dir_t;

/* Predefined I/O Types: */
typedef enum scsi_io_type {
    scsi_read6_cdb	= 0x08,
    scsi_read10_cdb	= 0x28,
    scsi_read16_cdb	= 0x88,
    scsi_write6_cdb	= 0x0A,
    scsi_write10_cdb	= 0x2A,
    scsi_write16_cdb	= 0x8A,
    scsi_writev16_cdb	= 0x8E
} scsi_io_type_t;

/*
 * Optional SCSI Generic Control Flags:
 */
#define SG_INIT_ASYNC 0x01              /* Enable async mode (if possible). */
#define SG_INIT_SYNC  0x02              /* Initiate sync data transfers.    */
#define SG_INIT_WIDE  0x04              /* Initiate wide data transfers.    */
#define SG_NO_DISC    0x08              /* Disable disconnects.             */
#define SG_DIRECTIO   0x10              /* Enable direct I/O (no buffering).*/
#define SG_ADAPTER    0x20              /* Send SCSI CDB via HBA driver.    */

/*
 * Advanced Flags: (not currently implemented)
 * REVISIT: On AIX, there are others (I think).
 */
#define SG_ACA_Q      0x100             /* ACA task attribute.              */

#define SG_Q_CLEAR    0x2000            /* Clear adapter queue.             */
#define SG_Q_RESUME   0x4000            /* Resume queuing to device.        */
#define SG_CLEAR_ACA  0x8000            /* Clear ACA task request.          */

/*
 * Advanced Operations: (only supported on AIX at present)
 *
 * Note: These values match what AIX expects (at present).
 */
typedef enum scsi_qtag {
    SG_NO_Q      = 0,                   /* Don't use tagged queuing.        */
    SG_SIMPLE_Q  = 1,                   /* Simple queuing.                  */
    SG_HEAD_OF_Q = 2,                   /* Place at head of device queue.   */
    SG_ORDERED_Q = 3,                   /* Ordered queuing.                 */
    SG_HEAD_HA_Q = 4			/* Head of HA queue (Solaris has).  */ 
} scsi_qtag_t;

typedef struct scsi_generic {
    HANDLE        fd;                   /* Device file descriptor.          */
    HANDLE        afd;                  /* Adapter file descriptor.         */
    char          *dsf;                 /* Device special file.             */
    char          *adsf;                /* Adapter device special file.     */
    hbool_t       dopen;		/* Open device and adapter files.   */
    unsigned int  flags;                /* Command control flags.           */
    unsigned int  sflags;               /* OS SCSI specific flags.          */
    scsi_addr_t   scsi_addr;            /* The SCSI address information.    */
    scsi_qtag_t   qtag_type;            /* The queue tag message type.      */
    char          *iface;               /* The interface name (cciss, etc). */
    hbool_t       error;                /* Indicates SCSI error occurred.   */
    hbool_t       errlog;               /* Controls logging messages.       */
    hbool_t       debug;                /* Enable debugging information.    */
    hbool_t       verbose;              /* Enable verbose infomormation.    */
    unsigned char cdb[MAX_CDB];         /* Command descriptor block.        */
    unsigned char cdb_size;             /* The CDB size.                    */
    char          *cdb_name;            /* The SCSI opcode name.            */
    unsigned int  scsi_status;          /* The SCSI status code.            */
    enum scsi_data_dir data_dir;        /* The SCSI data direction.         */
    void          *data_buffer;         /* Pointer to data buffer.          */
    unsigned int  data_length;          /* User data buffer length.         */
    unsigned int  data_resid;           /* Residual data not transferred.   */
    unsigned int  data_transferred;	/* The actual data transferred.     */
    unsigned int  data_dump_limit;	/* The data byte dump limit (debug).*/
    void          *sense_data;          /* Pointer to request sense data.   */
    unsigned int  sense_length;         /* Request sense buffer length.     */
    unsigned int  sense_resid;          /* Residual sense not transferred.  */
    unsigned int  sense_status;         /* Request sense SCSI status.       */
    hbool_t       sense_valid;          /* True if sense data is valid.     */
    unsigned int  timeout;              /* Command timeout in millisecs.    */
    unsigned int  aux_info;             /* Auxillary information (if any).  */
    unsigned int  duration;             /* Time taken by the command.       */
    unsigned int  host_status;          /* Addl host status (if any).       */
    unsigned int  driver_status;        /* Addl driver status (if any).     */
    unsigned int  os_error;		/* The OS specific error code.      */
    hbool_t       warn_on_error;	/* Reporting warning on errors.     */
    void	  *opaque;		/* Opaque pointer for the caller.   */
    /*
     * This allows overriding the internal libExecuteCdb() function!
     */ 
    int		  (*execute_cdb)(void *opaque, struct scsi_generic *sgp);
					/* Optional execute function.	    */
    /* Recovery Parameters */
    hbool_t	recovery_flag;		/* The recovery control flag.	*/
    uint32_t	recovery_delay;		/* The recovery delay (in secs)	*/
    uint32_t	recovery_limit;		/* The recovery retry limit.	*/
    uint32_t	recovery_retries;	/* The recovery retries.	*/
} scsi_generic_t;

/*
 * SCSI Status Codes:
 */
#define SCSI_GOOD                  0x00 /* Command successfully completed.*/
#define SCSI_CHECK_CONDITION       0x02 /* Error, exception, or abnormal condition. */
#define SCSI_CONDITION_MET         0x04 /* Requested operation satisifed. */
#define SCSI_BUSY                  0x08 /* The target is BUSY.            */
#define SCSI_INTERMEDIATE          0x10 /* Linked commands successfully completed. */
#define SCSI_INTER_COND_MET        0x14 /* Intermediate-Condition met.    */
#define SCSI_RESERVATION_CONFLICT  0x18 /* Target reservation conflict.   */
#define SCSI_COMMAND_TERMINATED    0x22 /* Terminated by Terminate I/O Message. */
#define SCSI_QUEUE_FULL            0x28 /* Command tag queue is full.     */
#define SCSI_ACA_ACTIVE            0x30 /* ACA Active.                    */
#define SCSI_TASK_ABORTED          0x40 /* Task aborted.                  */

#define RequestSenseDataLength  255   /* Maximum Request Sense data size. */

/*
 * Error Code Definitions:
 */
#define ECV_IMED_ERR_CODE       0x70  /* Immediate error occurred.        */
#define ECV_DEFER_ERR_CODE      0x71  /* Deferred error (this good).      */
#define ECV_VENDOR_SPECIFIC     0x7f  /* Vendor specific sense data.      */

/*
 * Sense Key Codes:
 */
#define SKV_NOSENSE             0x0   /* No error or no sense info.       */
#define SKV_RECOVERED           0x1   /* Recovered error (success).       */
#define SKV_NOT_READY           0x2   /* Unit is not ready.               */
#define SKV_MEDIUM_ERROR        0x3   /* Nonrecoverable error.            */
#define SKV_HARDWARE_ERROR      0x4   /* Nonrecoverable hardware error.   */
#define SKV_ILLEGAL_REQUEST     0x5   /* Illegal CDB parameter.           */
#define SKV_UNIT_ATTENTION      0x6   /* Target has been reset.           */
#define SKV_DATA_PROTECT        0x7   /* Unit is write protected.         */
#define SKV_BLANK_CHECK         0x8   /* A no-data condition occured.     */
#define SKV_VENDOR_SPECIFIC	0x9   /* Vendor specific condition.	  */
#define SKV_COPY_ABORTED        0xA   /* Copy command aborted.            */
#define SKV_ABORTED_CMD         0xB   /* Target aborted cmd, retry.       */
#define SKV_EQUAL               0xC   /* Vendor unique, not used.         */
#define SKV_VOLUME_OVERFLOW     0xD   /* Physical end of media detect.    */
#define SKV_MISCOMPARE          0xE   /* Source & medium data differ.     */
#define SKV_RESERVED            0xF   /* This sense key is reserved.      */

/*
 * Additional Sense Code/Qualifiers:
 */
/* Valid with SKV_NOT_READY */
#define ASC_NOT_READY		0x04  /* The device is Not Ready.	  */
/* Valid with SKV_UNIT_ATTENTION */
#define ASC_RECOVERED_DATA	0x17  /* Recovered data. (success)        */
#define ASC_POWER_ON_RESET	0x29  /* A power on reset condition.      */
#define ASC_PARAMETERS_CHANGED	0x2A  /* Parameters changed condition.    */

/*
 * Generic Request Sense Data:
 */
typedef struct scsi_sense {
#if defined(_BITFIELDS_LOW_TO_HIGH_)
  unsigned char error_code  : 7,      /* Error code.                  [0] */
                info_valid  : 1;      /* Information fields valid.        */
#elif defined(_BITFIELDS_HIGH_TO_LOW_)
  unsigned char info_valid  : 1,      /* Information fields valid.        */
                error_code  : 7;      /* Error code.                  [0] */
#else
#error "bitfield ordering is NOT defined!"
#endif /* defined(_BITFIELDS_LOW_TO_HIGH_) */
  unsigned char obsolete;	      /* Obsolete (was Segment number.[1] */
#if defined(_BITFIELDS_LOW_TO_HIGH_)
  unsigned char sense_key   : 4,      /* Sense key.                   [2] */
                            : 1,      /* Reserved.                        */
            illegal_length  : 1,      /* Illegal length indicator.        */
            end_of_medium   : 1,      /* End of medium.                   */
            file_mark       : 1;      /* Tape filemark detected.          */
#elif defined(_BITFIELDS_HIGH_TO_LOW_)
  unsigned char file_mark   : 1,      /* Tape filemark detected.          */
              end_of_medium : 1,      /* End of medium.                   */
            illegal_length  : 1,      /* Illegal length indicator.        */
                            : 1,      /* Reserved.                        */
                  sense_key : 4;      /* Sense key.                   [2] */
#else
#error "bitfield ordering is NOT defined!"
#endif /* defined(_BITFIELDS_LOW_TO_HIGH_) */
  unsigned char info_bytes[4];        /* Information bytes (MSB).   [3-6] */
  unsigned char addl_sense_len;       /* Additional sense length.     [7] */
  unsigned char cmd_spec_info[4];     /* Command specific info.    [8-11] */
  unsigned char asc;                  /* Additional sense code.      [12] */
  unsigned char asq;                  /* Additional sense qualifier. [13] */
  unsigned char fru_code;             /* Field replaceable unit.     [14] */
  unsigned char sense_key_specific[3];/* Sense key specific info. [15-17] */
  unsigned char addl_sense[RequestSenseDataLength-18]; /* Pad to max [18]*/
} scsi_sense_t;

/*
 * Illegal Request Sense Specific Data:
 */
typedef struct scsi_sense_illegal_request {
#if defined(_BITFIELDS_LOW_TO_HIGH_)
    uint8_t bit_pointer     : 3,	/* Bit in error of the byte.	*/
	    bpv             : 1,	/* Bit pointer field valid.	*/
	    reserved_b4_b5  : 2,	/* 2 bits reserved.		*/
	    c_or_d          : 1,	/* Error is in cmd or data.	*/
	    sksv            : 1;	/* Sense key specific valid.	*/
#elif defined(_BITFIELDS_HIGH_TO_LOW_)
    uint8_t sksv            : 1,	/* Sense key specific valid.	*/
	    c_or_d          : 1,	/* Error is in cmd or data.	*/
	    reserved_b4_b5  : 2,	/* 2 bits reserved.		*/
	    bpv             : 1,	/* Bit pointer field valid.	*/
	    bit_pointer     : 3;	/* Bit in error of the byte.	*/
#else
#       error "bitfield ordering is NOT defined!"
#endif /* defined(_BITFIELDS_LOW_TO_HIGH_) */
        uint8_t field_ptr1;             /* MSB of field pointer.	*/
        uint8_t field_ptr0;             /* LSB of field pointer.	*/
} scsi_sense_illegal_request_t;

/*
 * Copy Aborted Sense Specific Data:
 */ 
typedef struct scsi_sense_copy_aborted {
#if defined(_BITFIELDS_LOW_TO_HIGH_)
    uint8_t bit_pointer     : 3,	/* Bit in error of the byte.	*/
	    bpv             : 1,	/* Bit pointer field valid.	*/
	    sd		    : 1,	/* Segment descriptor.		*/
	    reserved_b4	    : 1,	/* Reserved bit.		*/
	    c_or_d          : 1,	/* Error is in cmd or data.	*/
	    sksv            : 1;	/* Sense key specific valid.	*/
#elif defined(_BITFIELDS_HIGH_TO_LOW_)
    uint8_t sksv            : 1,	/* Sense key specific valid.	*/
	    c_or_d          : 1,	/* Error is in cmd or data.	*/
	    reserved_b4	    : 1,	/* Reserved bit.		*/
	    sd		    : 1,	/* Segment descriptor.		*/
	    bpv             : 1,	/* Bit pointer field valid.	*/
	    bit_pointer     : 3;	/* Bit in error of the byte.	*/
#else
#       error "bitfield ordering is NOT defined!"
#endif /* defined(_BITFIELDS_LOW_TO_HIGH_) */
        uint8_t field_ptr1;             /* MSB of field pointer.	*/
        uint8_t field_ptr0;             /* LSB of field pointer.	*/
} scsi_sense_copy_aborted_t;

/*
 * Additional Sense Code Table Entry Format:
 */
struct sense_entry {
    unsigned char sense_code;		/* Additional sense code.	*/
    unsigned char sense_qualifier;	/* Sense code qualifier.	*/
    char	*sense_message;		/* Error message text.		*/
};

#include "scsilib.h"                  /* OS specific declarations. */

extern int ExecuteCdb(scsi_generic_t *sgp);
extern hbool_t libIsRetriable(scsi_generic_t *sgp);
extern int libExecuteCdb(scsi_generic_t *sgp);
extern void libReportIoctlError(scsi_generic_t *sgp, hbool_t warn_on_error);
extern void libReportScsiError(scsi_generic_t *sgp, hbool_t warn_on_error);
extern int Inquiry(HANDLE fd, char *dsf, hbool_t debug, hbool_t errlog,
                   scsi_addr_t *sap, scsi_generic_t **sgpp,
                   void *data, unsigned int len, unsigned char page,
		   unsigned int sflags, unsigned int timeout);
extern char *GetDeviceIdentifier(HANDLE fd, char *dsf, hbool_t debug, hbool_t errlog,
                                 scsi_addr_t *sap, scsi_generic_t **sgpp,
				 void *inqp, unsigned int timeout);
extern char *GetSerialNumber(HANDLE fd, char *dsf, hbool_t debug, hbool_t errlog,
                             scsi_addr_t *sap, scsi_generic_t **sgpp,
			     void *inqp, unsigned int timeout);
typedef enum id_type {
  IDT_NONE, IDT_DEVICEID, IDT_SERIALID
} idt_t;
#define IDT_BOTHIDS IDT_NONE
extern idt_t GetUniqueID(HANDLE fd, char *dsf, hbool_t debug,
			 char **identifier, idt_t idt,
			 hbool_t errlog, unsigned int timeout);
extern int GetCapacity(scsi_generic_t *sgp, u_int32 *device_size, large_t *device_capacity);
extern int ReadCapacity10(HANDLE fd, char *dsf, hbool_t debug, hbool_t errlog,
			  scsi_addr_t *sap, scsi_generic_t **sgpp,
			  void *data, unsigned int len,
			  unsigned int sflags, unsigned int timeout);
extern int ReadCapacity16(HANDLE fd, char *dsf, hbool_t debug, hbool_t errlog,
			  scsi_addr_t *sap, scsi_generic_t **sgpp,
			  void *data, unsigned int len,
			  unsigned int sflags, unsigned int timeout);
extern int TestUnitReady(HANDLE fd, char *dsf, hbool_t debug, hbool_t errlog,
                         scsi_addr_t *sap, scsi_generic_t **sgpp, unsigned int timeout);
extern int Seek10(HANDLE fd, char *dsf, hbool_t debug, hbool_t errlog,
		  scsi_addr_t *sap, scsi_generic_t **sgpp,
		  unsigned int lba, unsigned int timeout);

extern int GvaPage( HANDLE fd, char *dsf, hbool_t debug, hbool_t errlog,
		    scsi_addr_t *sap, scsi_generic_t **sgpp,
		    void *data, unsigned int len,
		    unsigned char page, unsigned char revision,
		    unsigned int sflags, unsigned int timeout);
extern char *GetFilerHostName(scsi_generic_t *sgp);
extern char *GetVdiskPath(scsi_generic_t *sgp);
extern char *GetVdiskVolume(scsi_generic_t *sgp, hbool_t cmode);
extern char *GetVdiskIgroup(scsi_generic_t *sgp);
extern char *GetVdiskLunType(scsi_generic_t *sgp);
extern char *GetOntapRevision(scsi_generic_t *sgp);
extern int FaultInject(HANDLE fd, char *dsf, hbool_t debug, hbool_t errlog,
		       scsi_addr_t *sap, scsi_generic_t **sgpp,
		       unsigned char count,
		       unsigned char event, unsigned char sub_event,
		       unsigned char *value,
		       unsigned char sflags, unsigned int timeout);
extern int fiPanicThisNode(scsi_generic_t *sgp);
extern int fiPanicAllNodes(scsi_generic_t *sgp);
extern int fiDumpRASTrace(scsi_generic_t *sgp);
extern int HealthCheck(HANDLE fd, char *dsf, hbool_t debug, hbool_t errlog,
		       scsi_addr_t *sap, scsi_generic_t **sgpp,
		       void *data, unsigned int len,
		       unsigned char sflags, unsigned int timeout);

#if 0
#define StoH(fptr)		stoh(fptr, sizeof(fptr))
#define HtoS(fptr,val)		htos(fptr, (ulong64)val, sizeof(fptr))

/*
 * Until we get common includes sorted out, duplicate desirable API's here!
 */
extern void *Malloc(size_t size);
extern void *malloc_palign(size_t size, int offset);
extern void free_palign(void *pa_addr);
extern ulong64 stoh(unsigned char *bp, size_t size);
extern void htos(u_char *bp, ulong64 value, size_t size);
extern int GetCdbLength (unsigned char opcode);

extern void Fprintf(char *format, ...);
extern void Fprint(char *format, ...);
extern void Printf(char *format, ...);
extern void Print(char *format, ...);
extern void Perror(char *format, ...);
#if defined(WIN32)
extern void wPerror(char *format, ...);
# define os_perror wPerror
#endif /* defined(WIN32) */
#endif /* 0 */

/* scsidata.c */

extern void DumpCdbData(scsi_generic_t *sgp);
extern void DumpSenseData(scsi_generic_t *sgp, scsi_sense_t *sdp);
extern void print_scsi_status(unsigned char scsi_status, unsigned char sense_key, unsigned char asc, unsigned char ascq);
extern char *ScsiAscqMsg(unsigned char asc, unsigned char asq);
extern char *SenseKeyMsg(unsigned char sense_key);
extern char *SenseCodeMsg(unsigned char error_code);
extern int LookupSenseKey(char *sense_key_name);
extern char *ScsiStatus(unsigned char scsi_status);
extern int LookupScsiStatus(char *status_name);

#endif /* LIBSCSI_H */
