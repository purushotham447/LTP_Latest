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
#if !defined(_DTUNIX_H_)
#define _DTUNIX_H_ 1

/* Note: stdint.h does NOT exist on HP-UX 11.11 (very old now).    */
/*	 Nor does Solaris 8! (sigh) Time to retire these old OS's! */
/*	 But that said, required typedef's are in sys/types.h      */
#include <sys/types.h>

#if defined(__linux__)
#  include <stdint.h>
#  define XFS_DIO_BLOCK_SIZE 4096
#endif /* defined(__linux__) */
#include <poll.h>

#if defined(DEC)
#  define LOG_DIAG_INFO	1
/* Tru64 Unix */
#  if defined(O_DIRECTIO)
#    define O_DIRECT	O_DIRECTIO
#  endif
#endif /* defined(DEC) */

#define HANDLE			int
#define INVALID_HANDLE_VALUE	-1

#define DIRSEP		'/'
#define DEV_PREFIX	"/dev/"		/* Physical device name prefix.	*/
#define DEV_LEN		5		/* Length of device name prefix.*/

#define DEV_DIR_PREFIX		"/dev/"
#define DEV_DIR_LEN		(sizeof(DEV_DIR_PREFIX) - 1)
#define DEV_DEVICE_LEN		128

#if defined(__hpux) || defined(SOLARIS)
#  define DEV_BDIR_PREFIX	"/dev/dsk/"
#  define DEV_BDIR_LEN		(sizeof(DEV_BDIR_PREFIX) - 1)
#  define DEV_RDIR_PREFIX	"/dev/rdsk/"
#  define DEV_RDIR_LEN		(sizeof(DEV_RDIR_PREFIX) - 1)
#endif /* defined(__hpux) || defined(SOLARIS) */

#define TEMP_DIR_NAME		"/var/tmp/"
#define TEMP_DIR_LEN		(sizeof(TEMP_DIR_NAME) - 1)

#define OFF_T		off_t

#define os_delete_file(file)	unlink(file)
#define os_perror		Perror

#define os_sleep(value)		poll(0, 0, (int)(value*1000))
#define os_msleep(value)	poll(0, 0, (int)value)
#define os_usleep(value)	poll(0, 0, (int)(value/1000))

extern char *os_gethostname(void);
extern char *os_getusername(void);
extern char *ConvertBlockToRawDevice(char *block_device);

#endif /* !defined(_DTUNIX_H_) */

