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
 * Module:	dtunix.c
 * Author:	Robin T. Miller
 *
 * Description:
 *	This module contains *unix OS specific functions.
 */
#include "dt.h"

/*
 * SHIT! Another area of incompatability between *nix OS's! :-(
 */
#if defined(__linux__)
# include <mntent.h>
#  define MOUNT_FILE	_PATH_MOUNTED
#elif defined(__hpux)
# include <mntent.h>
#  define MOUNT_FILE	MNT_MNTTAB
#elif defined(SOLARIS)
# include <sys/mnttab.h>
#  define MOUNT_FILE	MNTTAB
#endif /* defined(__linux__) */

#if defined(DEV_BDIR_LEN)

/*
 * ConvertBlockToRawDevice() Convert a Block Device to a Raw Device.
 * 
 * Inputs:
 * 	block_device = Pointer to the block device.
 * 
 * Return Value:
 * 	Returns the raw device or NULL of it's not a block device.
 */ 
char *
ConvertBlockToRawDevice(char *block_device)
{
    char *raw_device = NULL;
    char *p = (block_device + DEV_BDIR_LEN);

    if (strncmp(block_device, DEV_BDIR_PREFIX, DEV_BDIR_LEN) == 0) {
	/* Note: Assumes raw device path is longer than block device! */
	raw_device = Malloc(strlen(block_device) + (DEV_RDIR_LEN - DEV_BDIR_LEN));
	if (raw_device) {
	    (void)sprintf(raw_device, "%s%s", DEV_RDIR_PREFIX, p);
	}
    }
    return (raw_device);
}

#endif /* defined(DEV_BDIR_LEN) */

#if defined(AIX)

#include <sys/mntctl.h>
#include <sys/vmount.h>

#define MNT_BUFFER_SIZE	(32 * KBYTE_SIZE)

hbool_t
FindMountDevice(dinfo_t *dip, char *path, hbool_t debug)
{
    char path_dir[PATH_BUFFER_SIZE];
    char *mounted_match = NULL;
    char *mounted_path = NULL;
    struct vmount *vmp;
    char *mounted, *mounted_over, *vbp;
    hbool_t match = False;
    char *path_dirp = path;
    int entries, size;
    void *buffer;

    if (path[0] != DIRSEP) {
	memset(path_dir, '\0', sizeof(path_dir));
	path_dirp = getcwd(path_dir, sizeof(path_dir));
	if (path_dirp == NULL) return(match);
    }

    buffer = Malloc(MNT_BUFFER_SIZE);
    if (buffer == NULL) return(match);
    if ( (entries = mntctl(MCTL_QUERY, MNT_BUFFER_SIZE, buffer)) < 0) {
	Perror("mntctl() failed");
	free(buffer);
	return(match);
    }
    vbp = buffer;

    while (entries--) {
	vmp = (struct vmount *)vbp;
        mounted = vmt2dataptr(vmp, VMT_OBJECT);
        mounted_over = vmt2dataptr(vmp, VMT_STUB);
	if (debug) {
	    Printf("mounted = %s, mounted_over = %s, type = %d\n", mounted, mounted_over, vmp->vmt_gfstype);
	}
	/*
	 * Loop through all mounted path entries to find the right match!
	 * Multiple matches via: /, /var, /var/tmp, /mnt, /mnt/nfs, etc
	 * So we want the match with the longest string in our path!
	 */
	if (strncmp(mounted_over, path_dirp, strlen(mounted_over)) == 0) {
	    /* Replace with entries matching more of the path. */
	    if (strlen(mounted_over) > strlen(mounted_path)) {
		if (debug) {
		    Printf("Found match! -> %s on %s\n", mounted, mounted_over);
		}
		/* In memory buffer, so just save the pointed. */
		mounted_path = mounted_over;
		mounted_match = mounted;
		match = True;
	    }
	}
	vbp += vmp->vmt_length;
    }
    if (match == True) {
	dip->di_mounted_from_device = strdup(mounted_match);
	dip->di_mounted_on_dir = strdup(mounted_path);
    }
    free(buffer);
    return(match);
}

#elif defined(SOLARIS)

hbool_t
FindMountDevice(dinfo_t *dip, char *path, hbool_t debug)
{
    char mounted_path[LARGE_BUFFER_SIZE];
    char mounted_match[LARGE_BUFFER_SIZE];
    char path_dir[PATH_BUFFER_SIZE];
    struct mnttab mnttab;
    struct mnttab *mnt = &mnttab;
    hbool_t match = False;
    char *path_dirp = path;
    FILE *fp;

    if (path[0] != DIRSEP) {
	memset(path_dir, '\0', sizeof(path_dir));
	path_dirp = getcwd(path_dir, sizeof(path_dir));
	if (path_dirp == NULL) return(match);
    }

    fp = fopen(MOUNT_FILE, "r");
    if (fp == NULL) return (match);

    memset(mounted_path, '\0', sizeof(mounted_path));
    memset(mounted_match, '\0', sizeof(mounted_match));

    while ( getmntent(fp, mnt) == 0 ) {
	if (debug) {
	    Printf("mount point = %s, special = %s, type = %s\n", mnt->mnt_mountp, mnt->mnt_special, mnt->mnt_fstype);
	}
	/*
	 * Loop through all mounted path entries to find the right match!
	 * Multiple matches via: /, /var, /var/tmp, /mnt, /mnt/nfs, etc
	 * So we want the match with the longest string in our path!
	 */
	if (strncmp(mnt->mnt_mountp, path_dirp, strlen(mnt->mnt_mountp)) == 0) {
	    /* Replace with entries matching more of the path. */
	    if (strlen(mnt->mnt_mountp) > strlen(mounted_path)) {
		if (debug) {
		    Printf("Found match! -> %s on %s\n", mnt->mnt_special, mnt->mnt_mountp);
		}
		strcpy(mounted_path, mnt->mnt_mountp);
		strcpy(mounted_match, mnt->mnt_special);
		match = True;
	    }
	}
    }
    if (match == True) {
	dip->di_mounted_from_device = strdup(mounted_match);
	dip->di_mounted_on_dir = strdup(mounted_path);
    }
    (void)fclose(fp);
    return(match);
}

#elif defined(MOUNT_FILE) /* Linux, HP-UX */

hbool_t
FindMountDevice(dinfo_t *dip, char *path, hbool_t debug)
{
    char mounted_path[LARGE_BUFFER_SIZE];
    char mounted_match[LARGE_BUFFER_SIZE];
    char filesystem_type[SMALL_BUFFER_SIZE];
    char filesystem_options[LARGE_BUFFER_SIZE];
    char path_dir[PATH_BUFFER_SIZE];
    struct mntent *mnt;
    hbool_t match = False;
    char *path_dirp = path;
    FILE *fp;

    if (path[0] != DIRSEP) {
	memset(path_dir, '\0', sizeof(path_dir));
	path_dirp = getcwd(path_dir, sizeof(path_dir));
	if (path_dirp == NULL) return(match);
    }

    fp = setmntent(MOUNT_FILE, "r");
    if (fp == NULL) return (match);

    memset(mounted_path, '\0', sizeof(mounted_path));
    memset(mounted_match, '\0', sizeof(mounted_match));

    while ( (mnt = getmntent(fp)) != NULL ) {
	if (debug) {
	    Printf("dir = %s, fsname = %s, type = %s\n", mnt->mnt_dir, mnt->mnt_fsname, mnt->mnt_type);
	}
	/*
	 * Loop through all mounted path entries to find the right match!
	 * Multiple matches via: /, /var, /var/tmp, /mnt, /mnt/nfs, etc
	 * So we want the match with the longest string in our path!
	 */
	if (strncmp(mnt->mnt_dir, path_dirp, strlen(mnt->mnt_dir)) == 0) {
	    /* Replace with entries matching more of the path. */
	    if (strlen(mnt->mnt_dir) > strlen(mounted_path)) {
		if (debug) {
		    Printf("Found match! -> %s on %s\n", mnt->mnt_fsname, mnt->mnt_dir);
		}
		strcpy(mounted_path, mnt->mnt_dir);
		strcpy(mounted_match, mnt->mnt_fsname);
		strcpy(filesystem_type, mnt->mnt_type);
		strcpy(filesystem_options, mnt->mnt_opts);
		match = True;
	    }
	}
    }
    if (match == True) {
	dip->di_mounted_from_device = strdup(mounted_match);
	dip->di_mounted_on_dir = strdup(mounted_path);
	dip->di_filesystem_type = strdup(filesystem_type);
	dip->di_filesystem_options = strdup(filesystem_options);
    }
    (void)endmntent(fp);
    return(match);
}

#else /* We don't have support for this OS! FreeBSD, MacOS (at present). */

hbool_t
FindMountDevice(dinfo_t *dip, char *path, hbool_t debug)
{
    if (debug) {
	Printf("FindMountDevice: Don't know how to find mount device yet!\n");
    }
    return (False);
}

#endif /* defined(SOLARIS */

char *
os_ctime(time_t *timep, char *time_buffer, int timebuf_size)
{
    char *bp;

    bp = ctime_r(timep, time_buffer);
    if (bp == NULL) {
	Perror("ctime_r() failed");
	(int)sprintf(time_buffer, "<no time available>\n");
    }
    return(time_buffer);
}

char *
os_gethostname(void)
{
    char hostname[MAXHOSTNAMELEN];
    if (gethostname(hostname, sizeof(hostname)) == FAILURE) {
	Perror("gethostname() failed");
	return(NULL);
    }
    return ( strdup(hostname) );
}

char *
os_getusername(void)
{
    size_t bufsize = STRING_BUFFER_SIZE;
    char username[STRING_BUFFER_SIZE];

    if (getlogin_r(username, bufsize) != SUCCESS) {
	Perror("getlogin_r() failed");
	return(NULL);
    }
    return ( strdup(username) );
}
