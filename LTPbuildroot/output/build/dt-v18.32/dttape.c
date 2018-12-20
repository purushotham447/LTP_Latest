#if defined(TAPE)
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
 * Module:	dttape.c
 * Author:	Robin T. Miller
 * Date:	August 20, 1993
 *
 * Description:
 *	This file contains the tape support functions.
 *
 * Modification History:
 *
 * June 24th, 2008 by Robin T. Miller.
 *	Add finer grain control over timing individual operations.
 *
 * August 23rd, 2007 by Robin T. Miller.
 *	Add no progress timing support.
 *
 * August 16th, 2005 by W Liu
 *      Changed for Mac Darwin
 *
 * April 24th, 2006 by Robin T. Miller.
 *	Added support for AIX tape operations.
 *
 * June 23rd, 2004 by Robin Miller.
 *      Added support for triggers on corruption.
 *
 * November 17th, 2003 by Robin Miller.
 *	Breakup output to stdout or stderr, rather than writing
 * all output to stderr.  If output file is stdout ('-') or a log
 * file is specified, then all output reverts to stderr.
 *
 * February 23rd, 2002 by Robin Miller.
 *      Make porting changes for HP-UX IA64.
 *
 * June 25th, 2001 by Robin Miller.
 *	Restructured code associated with Tru64 Unix EEI, so we obtain
 * the EEI status for all tape errors, not just EIO errors.
 *
 * January 15th, 2001 by Robin Miller.
 *	On errors, do not terminate() if the error limit is exceeded.
 * This way the caller can handle the failure (may expect an error :-).
 *
 * February 17th, 2000 by Robin Miller.
 *	For each tape operation, when debug is enabled, also report the
 * file and record numbers.
 *
 * January 22nd, 2000 by Robin Miller.
 *	Added support for Cygwin tape devices for Windows/NT.
 *
 * August 5th, 1999 by Robin Miller.
 *	Added tape commands for SCO UnixWare 7.
 *
 * July 29, 1999 by Robin Miller.
 *	Merge in changes made to compile on FreeBSD.
 *
 * February 25, 1999 by Robin Miller.
 *	Add support for multiple reset conditions.
 *
 * December 21, 1998 by Robin Miller.
 *	Add device information parameter to all tape functions.
 *
 * December 19, 1998 by Robin Miller.
 *	For DUNIX, display extended error information (if enabled).
 *
 * <date unknown>, by Robin Miller.
 *	Add DoWriteFileMark() function for QNX 4.22 Operating System.
 *
 */

#include "dt.h"

#if defined(_QNX_SOURCE)
#  include <sys/qioctl.h>
#elif defined(SCO) || defined(AIX)
#  include <sys/ioctl.h>
#  include <sys/tape.h>
#elif defined(__WIN32__)
#  include <sys/mtio.h>
#else /* !defined(_QNX_SOURCE) && !defined(SCO) */
#  include <sys/ioctl.h>
#  include <sys/mtio.h>
#endif /* defined(_QNX_SOURCE) */

#if !defined(_QNX_SOURCE) && !defined(SCO) && !defined(AIX)
/************************************************************************
 *									*
 * DoMtOp()	Setup & Do a Magtape Operation.				*
 *									*
 * Inputs:	dip = The device information.				*
 *		cmd = The magtape command to issue.			*
 *		count = The command count (if any).			*
 *		msg = The error message for failures.			*
 *									*
 * Return Value:							*
 *		Returns 0 / -1 = SUCCESS / FAILURE.			*
 *									*
 ************************************************************************/
int
DoMtOp (dinfo_t *dip, short cmd, daddr_t count, caddr_t msgp)
{
    struct mtop Mtop;
    struct mtop *mtop = &Mtop;

    mtop->mt_op = cmd;

    /*
     * Setup the 'mt' command count (if any).
     */
    if ((mtop->mt_count = count) < 0) {
	 mtop->mt_count = 1;
    }

    if (dip->di_debug_flag) {
	Printf(
	"Issuing '%s', count = %d (%#x) [file #%lu, record #%lu]\n",
			msgp,  mtop->mt_count, mtop->mt_count,
		(dip->di_mode == READ_MODE) ?
		 (dip->di_files_read + 1) : (dip->di_files_written + 1),
		(dip->di_mode == READ_MODE) ?
		 dip->di_records_read : dip->di_records_written);
    }
    return (DoIoctl (dip, MTIOCTOP, (caddr_t) mtop, msgp));
}

/************************************************************************
 *									*
 * DoXXXXX()	Setup & Do Specific Magtape Operations.			*
 *									*
 * Description:								*
 *	These functions provide a simplistic interface for issuing	*
 * magtape commands from within the program.  They all take 'count'	*
 * as an argument, except for those which do not take a count.		*
 *									*
 * Inputs:	fd = The file descriptor.				*
 *		count = The command count (if any).			*
 *									*
 * Return Value:							*
 *		Returns 0 / -1 = SUCCESS / FAILURE.			*
 *									*
 ************************************************************************/
int
DoForwardSpaceFile (dinfo_t *dip, daddr_t count)
{
	short cmd = MTFSF;
	return (DoMtOp (dip, cmd, count, "forward space file"));
}

int
DoBackwardSpaceFile (dinfo_t *dip, daddr_t count)
{
	short cmd = MTBSF;
	return (DoMtOp (dip, cmd, count, "backward space file"));
}

int
DoForwardSpaceRecord (dinfo_t *dip, daddr_t count)
{
	short cmd = MTFSR;
	return (DoMtOp (dip, cmd, count, "forward space record"));
}

int
DoBackwardSpaceRecord (dinfo_t *dip, daddr_t count)
{
	short cmd = MTBSR;
	return (DoMtOp (dip, cmd, count, "backward space record"));
}

int
DoRewindTape (dinfo_t *dip)
{
	short cmd = MTREW;
	return (DoMtOp (dip, cmd, (daddr_t) 0, "rewind tape"));
}

int
DoTapeOffline (dinfo_t *dip)
{
	short cmd = MTOFFL;
	return (DoMtOp (dip, cmd, (daddr_t) 0, "tape offline"));
}

#if !defined(OSFMK) && !defined(HP_UX) && !defined(AIX)
int
DoRetensionTape (dinfo_t *dip)
{
#if defined(FreeBSD) && !defined(MacDarwin)
	short cmd = MTRETENS;
#else /* !defined(FreeBSD) || defined(MacDarwin) */
	short cmd = MTRETEN;
#endif /* defined(FreeBSD) */
	return (DoMtOp (dip, cmd, (daddr_t) 0, "retension tape"));
}
#endif /* !defined(OSFMK) && !defined(HP_UX) && !defined(AIX) */

#if defined(__osf__)			/* Really DEC specific. */

int
DoSpaceEndOfData (dinfo_t *dip)
{
	short cmd = MTSEOD;
	return (DoMtOp (dip, cmd, (daddr_t) 0, "space to end of data"));
}

int
DoEraseTape (dinfo_t *dip)
{
	short cmd = MTERASE;
	return (DoMtOp (dip, cmd, (daddr_t) 0, "erase tape"));
}

int
DoTapeOnline (dinfo_t *dip)
{
	short cmd = MTONLINE;
	return (DoMtOp (dip, cmd, (daddr_t) 0, "tape online"));
}

int
DoLoadTape (dinfo_t *dip)
{
	short cmd = MTLOAD;
	return (DoMtOp (dip, cmd, (daddr_t) 0, "load tape"));
}

int
DoUnloadTape (dinfo_t *dip)
{
	short cmd = MTUNLOAD;
	return (DoMtOp (dip, cmd, (daddr_t) 0, "unload tape"));
}

#endif /* defined(__osf__) */

#if defined(sun)

int
DoSpaceEndOfData (dinfo_t *dip)
{
	short cmd = MTEOM;
	return (DoMtOp (dip, cmd, (daddr_t) 0, "space to end of data"));
}

#endif /* defined(sun) */

int
DoWriteFileMark (dinfo_t *dip, daddr_t count)
{
	short cmd = MTWEOF;
	return (DoMtOp (dip, cmd, count, "write file mark"));
}

/************************************************************************
 *									*
 * DoIoctl()	Do An I/O Control Command.				*
 *									*
 * Description:								*
 *	This function issues the specified I/O control command to the	*
 * device driver.							*
 *									*
 * Inputs:	dip = The device information.				*
 *		cmd = The I/O control command.				*
 *		argp = The command argument to pass.			*
 *		msgp = The message to display on errors.		*
 *									*
 * Return Value:							*
 *		Returns 0 / -1 = SUCCESS / FAILURE.			*
 *									*
 ************************************************************************/
int
DoIoctl (dinfo_t *dip, int cmd, caddr_t argp, caddr_t msgp)
{
    int status;

    if (dip->di_noprog_flag && optiming_table[IOCTL_OP].opt_timing_flag) {
	dip->di_optype = IOCTL_OP;
	dip->di_initiated_time = time((time_t *)0);
    }
    status = ioctl (dip->di_fd, cmd, argp);
    if (dip->di_noprog_flag) {
	dip->di_optype = NONE_OP;
	dip->di_initiated_time = (time_t) 0;
    }
    if (status == FAILURE) {
        dip->di_errno = errno;
	perror (msgp);
	(void)RecordError(dip);
        ExecuteTrigger(dip, msgp);
    }
    return (status);
}

#elif defined(AIX)

int
DoForwardSpaceFile (dinfo_t *dip, daddr_t count)
{
	int cmd = STFSF;
	return (DoMtOp (dip, cmd, count, "forward space file"));
}

int
DoBackwardSpaceFile (dinfo_t *dip, daddr_t count)
{
	int cmd = STRSF;
	return (DoMtOp (dip, cmd, count, "backward space file"));
}

int
DoForwardSpaceRecord (dinfo_t *dip, daddr_t count)
{
	int cmd = STFSR;
	return (DoMtOp (dip, cmd, count, "forward space record"));
}

int
DoBackwardSpaceRecord (dinfo_t *dip, daddr_t count)
{
	int cmd = STRSR;
	return (DoMtOp (dip, cmd, count, "backward space record"));
}

int
DoRewindTape (dinfo_t *dip)
{
	int cmd = STREW;
	return (DoMtOp (dip, cmd, 0, "rewind tape"));
}

int
DoRetensionTape (dinfo_t *dip)
{
	int cmd = STRETEN;
	return (DoMtOp (dip, cmd, 0, "retension tape"));
}

int
DoSpaceEndOfData (dinfo_t *dip)
{
    	errno = EINVAL;
	return (FAILURE);
}

int
DoEraseTape (dinfo_t *dip)
{
	int cmd = STERASE;
	return (DoMtOp (dip, cmd, 0, "erase tape"));
}

int
DoWriteFileMark (dinfo_t *dip, daddr_t count)
{
	int cmd = STWEOF;
	return (DoMtOp (dip, cmd, count, "write file mark"));
}

/************************************************************************
 *									*
 * DoMtOp()	Setup & Do a Magtape Operation.				*
 *									*
 * Inputs:	dip = The device information.				*
 *		cmd = The magtape command to issue.			*
 *		count = The command count (if any).			*
 *		msg = The error message for failures.			*
 *									*
 * Return Value:							*
 *		Returns 0 / -1 = SUCCESS / FAILURE.			*
 *									*
 ************************************************************************/
int
DoMtOp (dinfo_t *dip, short cmd, daddr_t count, caddr_t msgp)
{
    struct stop Stop;
    struct stop *stop = &Stop;
    int status;

    stop->st_op = cmd;

    /*
     * Setup the 'mt' command count (if any).
     */
    if ((stop->st_count = count) < 0) {
	 stop->st_count = 1;
    }

    if (dip->di_debug_flag) {
	Printf(
	"Issuing '%s', count = %d (%#x) [file #%lu, record #%lu]\n",
			msgp,  stop->st_count, stop->st_count,
		(dip->di_mode == READ_MODE) ?
		 (dip->di_files_read + 1) : (dip->di_files_written + 1),
		(dip->di_mode == READ_MODE) ?
		 dip->di_records_read : dip->di_records_written);
    }
    if (dip->di_noprog_flag && optiming_table[IOCTL_OP].opt_timing_flag) {
	dip->di_optype = IOCTL_OP;
	dip->di_initiated_time = time((time_t *)0);
    }
    status = ioctl (dip->di_fd, STIOCTOP, stop);
    if (dip->di_noprog_flag) {
	dip->di_optype = NONE_OP;
	dip->di_initiated_time = (time_t) 0;
    }
    if (status == FAILURE) {
        dip->di_errno = errno;
	perror (msgp);
	(void)RecordError(dip);
        ExecuteTrigger(dip, msgp);
    }
    return (status);
}

#elif defined(_QNX_SOURCE)
/************************************************************************
 *									*
 * DoXXXXX()	Setup & Do Specific Magtape Operations.			*
 *									*
 * Description:								*
 *	These functions provide a simplistic interface for issuing	*
 * magtape commands from within the program.  They all take 'count'	*
 * as an argument, except for those which do not take a count.		*
 *									*
 * Inputs:	dip = The device information.				*
 *		count = The command count (if any).			*
 *									*
 * Return Value:							*
 *		Returns 0 / -1 = SUCCESS / FAILURE.			*
 *									*
 ************************************************************************/
int
DoForwardSpaceFile (dinfo_t *dip, daddr_t count)
{
	int cmd = T_SEEK_FM;
	return (DoIoctl (dip, cmd, count, "forward space file"));
}

int
DoForwardSpaceRecord (dinfo_t *dip, daddr_t count)
{
	int cmd = T_SKIP_FWD_A_BLOCK;
	return (DoIoctl (dip, cmd, count, "forward space record"));
}

int
DoBackwardSpaceRecord (dinfo_t *dip, daddr_t count)
{
	int cmd = T_SKIP_BWD_A_BLOCK;
	return (DoIoctl (dip, cmd, count, "backward space record"));
}

int
DoRewindTape (dinfo_t *dip)
{
	int cmd = T_BOT;
	return (DoIoctl (dip, cmd, 0, "rewind tape"));
}

int
DoRetensionTape (dinfo_t *dip)
{
	int cmd = T_RETENSION;
	return (DoIoctl (dip, cmd, 0, "retension tape"));
}

int
DoSpaceEndOfData (dinfo_t *dip)
{
	int cmd = T_SEEK_EOD;
	return (DoIoctl (dip, cmd, 0, "space to end of data"));
}

int
DoEraseTape (dinfo_t *dip)
{
	int cmd = T_ERASE;
	return (DoIoctl (dip, cmd, 0, "erase tape"));
}

int
DoWriteFileMark (dinfo_t *dip, daddr_t count)
{
	int cmd = T_WRITE_FM;
	return (DoIoctl (dip, cmd, count, "write file mark"));
}

int
DoIoctl (dinfo_t *dip, int cmd, int count, caddr_t msgp)
{
    QIC02_MSG_STRUCT qic02ms;
    int status;

    if (dip->di_debug_flag) {
	Printf ("Issuing '%s', count = %d (%#x)\n",
		msgp,  count, count);
    }
    memset(&qic02ms, '\0', sizeof(qic02ms));
    qic02ms.Header.Command = (unsigned short)cmd;

    while (count--) {
	if (dip->di_noprog_flag && optiming_table[IOCTL_OP].opt_timing_flag) {
	    dip->di_optype = IOCTL_OP;
	    dip->di_initiated_time = time((time_t *)0);
	}
	status = qnx_ioctl (dip->di_fd,
			    QCTL_RAW_CMD,
			    &qic02ms, sizeof (QIC02_HEADER_STRUCT),
			    &qic02ms, sizeof (QIC02_MSG_STRUCT));
	if (dip->di_noprog_flag) {
	    dip->di_optype = NONE_OP;
	    dip->di_initiated_time = (time_t) 0;
	}
	if (status == FAILURE) {
	    perror (msgp);
	    if (RecordError(dip) >= dip->di_error_limit) {
		return(FAILURE);
	    }
	}
    }
    return(status);
}

#elif defined(SCO)

int
DoForwardSpaceFile (dinfo_t *dip, daddr_t count)
{
	int cmd = T_SFF;
	return (DoIoctl (dip, cmd, count, "forward space file"));
}

int
DoBackwardSpaceFile (dinfo_t *dip, daddr_t count)
{
	int cmd = T_SFB;
	return (DoIoctl (dip, cmd, count, "backward space file"));
}

int
DoForwardSpaceRecord (dinfo_t *dip, daddr_t count)
{
	int cmd = T_SBF;
	return (DoIoctl (dip, cmd, count, "forward space record"));
}

int
DoBackwardSpaceRecord (dinfo_t *dip, daddr_t count)
{
	int cmd = T_SBB;
	return (DoIoctl (dip, cmd, count, "backward space record"));
}

int
DoRewindTape (dinfo_t *dip)
{
	int cmd = T_RWD;
	return (DoIoctl (dip, cmd, 0, "rewind tape"));
}

int
DoRetensionTape (dinfo_t *dip)
{
	int cmd = T_RETENSION;
	return (DoIoctl (dip, cmd, 0, "retension tape"));
}

int
DoSpaceEndOfData (dinfo_t *dip)
{
	int cmd = T_EOD;
	return (DoIoctl (dip, cmd, 0, "space to end of data"));
}

int
DoEraseTape (dinfo_t *dip)
{
	int cmd = T_ERASE;
	return (DoIoctl (dip, cmd, 0, "erase tape"));
}

int
DoWriteFileMark (dinfo_t *dip, daddr_t count)
{
	int cmd = T_WRFILEM;
	return (DoIoctl (dip, cmd, count, "write file mark"));
}

int
DoIoctl (dinfo_t *dip, int cmd, int count, caddr_t msgp)
{
    int status;

    if (dip->di_debug_flag) {
	Printf ("Issuing '%s', count = %d (%#x)\n",
		msgp,  count, count);
    }
    if (dip->di_noprog_flag && optiming_table[IOCTL_OP].opt_timing_flag) {
	dip->di_optype = IOCTL_OP;
	dip->di_initiated_time = time((time_t *)0);
    }
    status = ioctl (dip->di_fd, cmd, count);
    if (dip->di_noprog_flag) {
	dip->di_optype = NONE_OP;
	dip->di_initiated_time = (time_t) 0;
    }
    if (status == FAILURE) {
	perror (msgp);
	(void)RecordError(dip);
    }
    return(status);
}

#endif /* defined(SCO) */

#endif /* defined(TAPE) */
