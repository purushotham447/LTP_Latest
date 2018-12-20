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
 * Module:	dtprocs.c
 * Author:	Robin T. Miller
 * Date:	August 7, 1993
 *
 * Description:
 *	Functions to handle multiple processes for 'dt' program.
 *
 * Modification History:
 *
 * June 14th, 2012 by Robin T. Miller
 * 	Now that we support multiple target devices, add %device so device
 * unique logs can be created that include the last part of the device name.
 * 
 * January 10th, 2012 by Robin T. Miller
 * 	On *nix systems when using multiple slices, ensure the last slice gets
 * any residual bytes. This was expected behaviour, but adjustment was broken!
 * 
 * December 14th, 2006 by Robin T. Miller
 *	Fix bug in Windows await_procs(), where an incorrect variable check
 * kept the oncerr=abort action from taking place. (grrr)
 *
 * October 27th, 2008 by Robin T. Miller.
 *	Honor unique log files for multiple slices and multiple procs.
 *
 * October 9th, 2008 by Robin T. Miller.
 *	Fix oops in start_procs() on Unix systems, to ensure a log file
 * was specified, before re-open'ing stderr, which breaks on AIX.
 *
 * September 30th, 2008 by Robin T. Miller.
 *	Add check for dt_active in abort_procs() which may get called
 * more than once.  This was casuing an invalid handle error.
 *
 * Spetember 11th, 2008 by Robin T. Miller.
 *	Added support for Windows multiple processes and slices).
 *
 * September 8th, 2008 by Robin T. Miller
 *	Removed arming of signal handlers, since this is done sooner in
 * the mainline code, so we don't need it duplicated here (code cleanup).
 *
 * September 6th, 2008 by Robin T. Miller
 *	Add make_unique_file() function in preparation for Windows procs.
 *
 * January 5th, 2007 by Robin T. Miller.
 *	When displaying slice information w/debug enabled, format lba's
 * and block length values as 64-bits (32-bits is limited to 2TB!).
 *
 * August 3rd, 2005 by Robin T. Miller.
 *      Fixed bug in init_slice_info() where the position was not taken
 * into account when calculating the slice resid. We would end up writing
 * too much, and in the case of Hazard, we were destroying the GDID!.
 *
 * April 12th, 2005 by Robin T. Miller
 *	Fixed debug output in setup_slice(), when there was a mismatch
 * between 32 and 64 bit values and format control characters.  Also
 * removed WINDOWS conditionalization, which shouldn't be needed, now
 * that the root cause has been identified and fixed.
 *
 * November 17th, 2003 by Robin Miller.
 *	Breakup output to stdout or stderr, rather than writing
 * all output to stderr.  If output file is stdout ('-') or a log
 * file is specified, then all output reverts to stderr.
 *
 * March 14th, 2003 by Robin Miller.
 *	Added support for testing an individual slice.
 *
 * May 31st, 2001 by Robin Miller.
 *	Update abort_procs() to use max_procs, valid for both multiple
 * processes and slices, and loop through entire process table since
 * some processes may have finished already (use to break out early).
 *	When starting slices with multiple processes, prime the data
 * pattern to ensure each process uses the same pattern in a slice.
 *
 * February 6th, 2001 by Robin Miller.
 *	If doing multiple slices in reverse direction, ensure the data
 * limit gets tot he slice length, or we'll overflow into previous slice.
 *
 * February 1st, 2001 by Robin Miller.
 *	Fix dumb problem starting multiple procs with multiple slices.
 *
 * January 28th, 2001 by Robin Miller.
 *	When aborting processes, send SIGINT instead of SIGTERM, so
 * statistics gets reported (important on long running commands :-).
 *	Added support for multiple slices option.  This sets up each
 * process exercising a different range of blocks (slice) on the disk.
 *
 * January 2nd, 2001 by Robin Miller.
 *      Make changes to build using MKS/NuTCracker product.
 *
 * March 28th, 2000 by Robin Miller.
 *	When creating multiple processes, do a better job determining
 * when a unique device name should be constructed.  Was broken for
 * named piped (FIFO's).
 *
 * May 3, 1999 by Robin Miller.
 *	Allocate more space for unique file names, since the size
 * of pid_t is now 31 bits in Steel.
 *
 * April 8, 1999 by Robin Miller.
 *	Merge in Jeff Detjen's changes for current process count.
 *
 * April 29, 1998 by Robin Miller.
 *	Add support for an alternate device directory.
 *
 * July 17, 1995 by Robin Miller.
 *	Apply a severity priority to child exit status.
 *	Added flag to ensure process abortion occurs only once.
 *
 * July 5, 1995 by Robin Miller.
 *	Properly check for child process exiting as result of a signal.
 *
 * March 28, 1995 by Robin Miller.
 *	Report specific error for "no processes started", and exit with
 *	error status if the system process limit has been exceeded.
 *
 * November 4, 1994 by Robin Miller.
 *	Don't set SIGCHLD signal to SIG_IGN (set to SIG_DFL) or else
 *	waitpid() won't detect any child processes (OSF R1.3 and QNX).
 *	[ Unfortunately, the POSIX standard states "The specification
 *	  of the effects of SIG_IGN on SIGCHLD as implementation defined
 *	  and permits, but does NOT require, the System V effect of
 *	  causing terminating children to be ignored by wait(). Yuck!!! ]
 */
#include "dt.h"
#if !defined(WIN32)
#  include <signal.h>
#  include <strings.h>
#  include <sys/stat.h>
#  include <sys/wait.h>
#endif /* !defined(WIN32) */

#define PROC_ALLOC (sizeof(pid_t) * 3)	/* Extra allocation for PID.	*/

/*
 * Forward References:
 */
static void init_slice_info(struct dinfo *dip, slice_info_t *sip, large_t *data_resid);
static void setup_slice(struct dinfo *dip, slice_info_t *sip);
static void setup_iotuning(dinfo_t *dip, char *cmd);
static void setup_multiprocs(dinfo_t *dip, char *cmd);
static void update_cmd_line(dinfo_t *dip);

#if defined(WIN32)

#define HANDLE_MASK (MAXIMUM_WAIT_OBJECTS - 1)

PROCESS_INFORMATION *start_process(dinfo_t *dip, char *cmd);

/*
 * abort_procs - Abort processes started by the parent.
 */
void
abort_procs(dinfo_t *dip)
{
    int proc_num;
    struct dt_procs *dtp;
    PROCESS_INFORMATION *pip;

    if ((dip->di_ptable == NULL) || dip->di_aborted_processes) return;
    /*
     * Terminate all active processes.
     */
    for (dtp = dip->di_ptable, proc_num = 0; proc_num < dip->di_max_procs; proc_num++, dtp++) {
        pip = dtp->dt_pip;
	if ( !dtp->dt_active ) continue; /* Already reaped status! */
	if (dip->di_debug_flag || dip->di_pDebugFlag) {
	    Printf("Terminating child process %d...\n", pip->dwProcessId);
	}

	/*
	 * I'd rather send a signal like Unix, to have child report
	 * statistics, but Windows does not support a kill() API!
	 */
	if (TerminateProcess(pip->hProcess, ERROR_PROCESS_ABORTED) == 0) {
	    DWORD error = GetLastError();
	    /*
	     * Child thread may be terminating due to signal.
	     */
	    if (error != ERROR_ACCESS_DENIED) {
		Fprintf("Failed to terminate child process %d...\n", pip->dwProcessId);
		report_error(dip, "TerminateProcess() failed", TRUE);
	   }
	}
    }
    dip->di_aborted_processes = TRUE;
    return;
}

void
await_procs(dinfo_t *dip)
{
    DWORD status;
    struct dt_procs *dtp;
    int proc_num = 0, wait_index;
    PROCESS_INFORMATION *pip;
    bool aborted_procs = FALSE;
    DWORD timeoutMs = INFINITE;

    if (dip->di_debug_flag || dip->di_pDebugFlag) {
	timeoutMs = (60 * 1000); /* For debug! */
	Printf("Waiting for %d child processes to complete...\n", dip->di_procs_active);
    }
    /*
     * For dt's oncerror option, we must wait on one process at a time,
     * so we can abort procs if instructed to on child errors.
     */
    while (dip->di_procs_active) {
	/*
	 * Wait for all processes to complete.
	 */
	status = WaitForMultipleObjects((DWORD)dip->di_procs_active, // Number of handles.
					dip->di_proc_handles,// Array of handles.
					FALSE,		     // Wait for any object.
					timeoutMs);          // Timeout in ms (disable).

	if (status == WAIT_FAILED) {
	    report_error(dip, "WaitForMultipleObjects() failed", FALSE);
	    abort_procs(dip);
	    break;
	}
	if (status == WAIT_TIMEOUT) {
	    Printf("Still waiting on %d processes...\n", dip->di_procs_active);
	    Printf("Active PIDs:");
	    for (dtp = dip->di_ptable, proc_num = 0; proc_num < dip->di_max_procs; proc_num++, dtp++) {
		pip = dtp->dt_pip;
		if (dtp->dt_active) {
		    Print(" %d", pip->dwProcessId);
		}
	    }
	    Print("\n");
	    fflush(ofp);
	    continue;
	}
	if ((status & ~HANDLE_MASK) != WAIT_OBJECT_0) {
	    Fprintf("WaitForMultipleObjects returned status %#x\n", status);
	    dip->di_child_status = GetLastError();
	    abort_procs(dip);
	    return;
	}
	wait_index = (status & HANDLE_MASK); /* Handle index - 1 */
	/*
	 * Find the process by searching for its' handle.
	 */
	for (dtp = dip->di_ptable, proc_num = 0; proc_num < dip->di_max_procs; proc_num++, dtp++) {
	    pip = dtp->dt_pip;
	    if (pip->hProcess == dip->di_proc_handles[wait_index]) {
		break;
	    }
	}
	if ( !GetExitCodeProcess( pip->hProcess, &dip->di_child_status ) ) {
	    Fprintf("GetExitCodeProcess failed (%d)\n", GetLastError() );
	    dip->di_child_status = GetLastError();
	}
	if (dip->di_debug_flag || dip->di_pDebugFlag) {
	    Printf("Child process %d, exited with status %d\n",
		    pip->dwProcessId, dip->di_child_status);
	}
	dtp->dt_active = FALSE;
	dtp->dt_status = dip->di_child_status;
        /*
	 * Close process and thread handles.
	 */
	CloseHandle( pip->hProcess );
	CloseHandle( pip->hThread );
	/*
	 * Remove the completed handle from the array to wait upon.
	 */
	for (; (wait_index < dip->di_procs_active); wait_index++) {
	    dip->di_proc_handles[wait_index] = dip->di_proc_handles[wait_index + 1];
	}

	if ( (exit_status == SUCCESS) && (dip->di_child_status != SUCCESS) ) {
	    if ( (dip->di_oncerr_action == ABORT) &&
		 (dip->di_child_status != WARNING) && (dip->di_child_status != END_OF_FILE) ) {
		if (!aborted_procs) {
		    abort_procs(dip);		/* Abort procs on error. */
		    aborted_procs = TRUE;
		}
	    }
	    /*
	    * Save the most sever error for parent exit status.
	    *
	    * Severity Priorities:
	    *			WARNING		(lowest)
	    *			END_OF_FILE
	    *			Signal Number
	    *			FATAL_ERROR	(highest)
	    */
	    if ( ((exit_status == SUCCESS) || (dip->di_child_status == FATAL_ERROR)) ||
		 ((exit_status == WARNING) && (dip->di_child_status > WARNING))      ||
		 ((exit_status == END_OF_FILE) && (dip->di_child_status > WARNING)) ) {
		    exit_status = dip->di_child_status;	/* Set error code for exit. */
	    }
	}
	dip->di_procs_active--;
    } 
    return;
}

/*
 * start_process() - Start a Process.
 *
 * Inputs:
 *	dip = The device information pointer.
 *	cmd = The command line to execute.
 *
 * Return Value:
 *	Returns pointer to process information or NULL on failure.
 */
PROCESS_INFORMATION *
start_process(dinfo_t *dip, char *cmd)
{
    STARTUPINFO si;
    PROCESS_INFORMATION *pip;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    pip = (PROCESS_INFORMATION *)malloc(sizeof(*pip));
    if (pip == NULL) return(pip);
    ZeroMemory( pip, sizeof(*pip) );

    if (dip->di_debug_flag || dip->di_pDebugFlag) {
	    Printf("Command: %s\n", cmd);
    }

    /* Start the child process. */
    if ( !CreateProcess( NULL,	     // No module name (use command line)
		         cmd,        // Command line
		         NULL,       // Process handle not inheritable
		         NULL,       // Thread handle not inheritable
		         FALSE,      // Handle inheritance flag
		         0,          // No creation flags
		         NULL,       // Use parent's environment block
		         NULL,       // Use parent's starting directory 
		         &si,        // Pointer to STARTUPINFO structure
			 pip ) )     // Pointer to PROCESS_INFORMATION structure
    {
        report_error(dip, "CreateProcess failed", TRUE);
        free(pip);
        return(NULL);
    }
    return(pip);
}

static void
setup_iotuning(dinfo_t *dip, char *cmd)
{
    if (dip->di_iotuning_flag && dip->di_iotune_file ) {
	//(void)strcat(cmd, " disable=iotuning");
	;
    }
    return;
}

static void
setup_multiprocs(dinfo_t *dip, char *cmd)
{
    return;
}

pid_t
start_devs(dinfo_t *dip)
{
    struct dt_procs *dtp;
    size_t psize;
    PROCESS_INFORMATION *pip;
    char *devs, *token, *p;
    int proc_num = 0;
    char *dt_path, *dt_cmd;
    char *our_cmd, *bp, *saveptr;

    devs = p = (dip->di_input_file) ? dip->di_input_file : dip->di_output_file;
    dip->di_num_devs = 1;
    /* Count the devices specified. */
    while (p = strchr(p, ',')) {
	dip->di_num_devs++; p++;
    }
    dip->di_max_procs = dip->di_num_devs;
    psize = (dip->di_max_procs * sizeof(*dtp));

    if ((dip->di_ptable = (struct dt_procs *)malloc(psize)) == NULL) {
	report_error(dip, "No memory for proc table", FALSE);
	exit (FATAL_ERROR);
    }
    ZeroMemory(dip->di_ptable, psize);
    our_cmd = (char *)Malloc(LOG_BUFSIZE);
    /* Setup pointers to dt path and dt command line. */
    dt_path = dip->di_dtcmd;
    p = strchr(dt_path, ' ');
    if (!p) {
	Fprintf("We're broken setting up dt's path!\n");
	abort();
    }
    *p = '\0';
    dt_cmd = ++p;

    dip->di_cur_proc = 1;
    dip->di_procs_active = 0;

    /* Remember: strtok() replaces "," with NULL! */
    token = strtok_r(devs, ",", &saveptr);
    /*
     * Start a process for each target device specified.
     */
    for (dtp = dip->di_ptable, proc_num = 0; proc_num < dip->di_max_procs; proc_num++, dtp++) {
	dtp->dt_device = token;
	bp = our_cmd;
	/* Note: Main stripped the device options already. */
	bp += Sprintf(bp, "%s ", dt_path);
	/* More work, but I like the device first on the command line! */
	if (dip->di_input_file) {
	    bp += Sprintf(bp, "if=%s", token);
	} else {
	    bp += Sprintf(bp, "of=%s", token);
	}
	/* Now, add original options. */
	bp += Sprintf(bp, " %s enable=child", dt_cmd);
	setup_iotuning(dip, bp);
	pip = start_process(dip, our_cmd);
	if (pip == NULL) return (-1);
	if (dip->di_debug_flag || dip->di_pDebugFlag) {
	    Printf("Started process %d for %s...\n", pip->dwProcessId, dtp->dt_device);
	}
	dip->di_proc_handles[proc_num] = pip->hProcess;
	dip->di_cur_proc++;
	dtp->dt_pid = dip->di_child_pid = pip->dwProcessId;
	dtp->dt_active = TRUE;
	dtp->dt_pip = pip;
	dip->di_procs_active++;
	token = strtok_r(NULL, ",", &saveptr);	/* Next device please! */
    }
    free(our_cmd);
    return (dip->di_child_pid);
}

pid_t
start_procs(dinfo_t *dip)
{
    struct dt_procs *dtp;
    size_t psize;
    PROCESS_INFORMATION *pip;
    int proc_num = 0;

    dip->di_max_procs = dip->di_num_procs;
    psize = (dip->di_max_procs * sizeof(*dtp));

    if ((dip->di_ptable = (struct dt_procs *)malloc(psize)) == NULL) {
	report_error (dip, "No memory for proc table", FALSE);
	exit (FATAL_ERROR);
    }
    ZeroMemory(dip->di_ptable, psize);

    dip->di_cur_proc = 1;
    dip->di_procs_active = 0;
    (void)strcat(dip->di_dtcmd, " enable=child");
    setup_iotuning(dip, dip->di_dtcmd);
    setup_multiprocs(dip, dip->di_dtcmd);

    /*
     * Spawn specified number of processes.
     */
    for (dtp = dip->di_ptable, proc_num = 0; proc_num < dip->di_max_procs; proc_num++, dtp++) {
	pip = start_process(dip, dip->di_dtcmd);
	if (pip == NULL) return (-1);
	if (dip->di_debug_flag || dip->di_pDebugFlag) {
	    Printf("Started process %d...\n", pip->dwProcessId);
	}
	dip->di_proc_handles[proc_num] = pip->hProcess;
	dip->di_cur_proc++;
	dtp->dt_pid = dip->di_child_pid = pip->dwProcessId;
	dtp->dt_active = TRUE;
	dtp->dt_pip = pip;
	dip->di_procs_active++;
    }
    return (dip->di_child_pid);
}

pid_t
start_slices(dinfo_t *dip)
{
    struct slice_info slice_info;
    slice_info_t *sip = &slice_info;
    struct dt_procs *dtp;
    size_t psize;
    PROCESS_INFORMATION *pip;
    int proc_num = 0;
    large_t data_resid;
    char *cmd = Malloc(LOG_BUFSIZE);

    dip->di_max_procs = dip->di_num_slices;
    psize = (dip->di_max_procs * sizeof(*dtp));

    if ((dip->di_ptable = (struct dt_procs *)malloc(psize)) == NULL) {
	report_error (dip, "No memory for proc table", FALSE);
	exit (FATAL_ERROR);
    }
    memset(dip->di_ptable, '\0', psize);

    init_slice_info(dip, sip, &data_resid);

    dip->di_cur_proc = 1;
    dip->di_procs_active = 0;

    /*
     * Spawn specified number of processes.
     */
    for (dtp = dip->di_ptable, proc_num = 0; proc_num < dip->di_max_procs; proc_num++, dtp++) {
	sip->slice++;
	/* Last slice gets any residual bytes. */
	if ((proc_num + 1) == dip->di_max_procs) {
	    sip->slice_length += data_resid;
	}
	(void)sprintf(cmd, "%s enable=logpid slice=%d", dip->di_dtcmd, sip->slice);
	setup_iotuning(dip, cmd);
	setup_multiprocs(dip, cmd);
	pip = start_process(dip, cmd);
	if (pip == NULL) return (-1);
	dip->di_proc_handles[proc_num] = pip->hProcess;
	dip->di_cur_proc++;
	dtp->dt_pid = dip->di_child_pid = pip->dwProcessId;
	dtp->dt_active = TRUE;
	dtp->dt_pip = pip;
	dip->di_procs_active++;
	if (dip->di_debug_flag || dip->di_pDebugFlag) {
	    Printf ("Started Slice %d, PID %d...\n", sip->slice, dip->di_child_pid);
	}
	if (proc_num < dip->di_max_procs) {
	    sip->slice_position += sip->slice_length;
	}
    }
    return (dip->di_child_pid);
}


#else /* !defined(WIN32) */

/*
 * abort_procs - Abort processes started by the parent.
 */
void
abort_procs(dinfo_t *dip)
{
    struct dt_procs *dtp;
    int procs;
    pid_t pid;

    if ((dip->di_ptable == NULL) || dip->di_aborted_processes)  return;
    /*
     * Force all processes to terminate.
     */
    for (dtp = dip->di_ptable, procs=0; procs < dip->di_max_procs; procs++, dtp++) {
	if ((pid = dtp->dt_pid) == (pid_t) 0) continue;
	if (dip->di_debug_flag || dip->di_pDebugFlag) {
	    Printf("Aborting child process %d via a SIGINT (signal %d)...\n",
								pid, SIGINT);
	}
	if (dtp->dt_active) {
	    int status = kill (pid, SIGINT);
    	    if ( (dip->di_debug_flag || dip->di_pDebugFlag) && (status == FAILURE) ) {
		Perror("DEBUG: Failed to kill PID %d", pid);
	    }
	}
    }
    dip->di_aborted_processes = TRUE;
    return;
}

void
await_procs(dinfo_t *dip)
{
    pid_t wpid;
    struct dt_procs *dtp;
    int procs, status;

    if (dip->di_debug_flag || dip->di_pDebugFlag) {
	Printf ("Waiting for %d child processes to complete...\n", dip->di_procs_active);
    }
    while (1) {
	if ((wpid = waitpid ((pid_t) -1, &dip->di_child_status, 0)) == FAILURE) {
	    if (errno == ECHILD) {
		if (dip->di_procs_active && dip->di_pDebugFlag) {
		    Printf("Processes still active (%d) and ECHILD received!\n",
			   dip->di_procs_active);
		}
		break;				/* No more children... */
	    } else if (errno == EINTR) {
		/* Note: Expect signal handler to abort children! */
		//abort_procs(dip);
		continue;
	    } else {
		report_error (dip, "waitpid", FALSE);
		exit (FATAL_ERROR);
	    }
	}
	/*
	 * Examine the child process status.
	 */
	if ( WIFSTOPPED(dip->di_child_status) ) {
	    Printf ("Child process %d, stopped by signal %d.\n",
					wpid, WSTOPSIG(dip->di_child_status));
	    continue; /* Maybe attached from debugger... */
	} else if ( WIFSIGNALED(dip->di_child_status) ) {
	    status = WTERMSIG(dip->di_child_status);
	    Fprintf ("Child process %d, exiting because of signal %d\n",
							wpid, status);
	} else { /* Process must be exiting... */
	    status = WEXITSTATUS (dip->di_child_status);
	    if (dip->di_debug_flag || dip->di_pDebugFlag) {
		Printf ("Child process %d, exited with status %d\n",
							wpid, status);
	    }
	}

	/*
	 * Update this process' status.
	 */
	for (dtp = dip->di_ptable, procs = 0; procs < dip->di_max_procs; procs++, dtp++) {
	    if (dtp->dt_pid == wpid) {
		dtp->dt_active = FALSE;
		dtp->dt_status = status;
		dip->di_procs_active--;
		break;
	    }
	}

	if ( (exit_status == SUCCESS) && (status != SUCCESS) ) {
	    if ( (dip->di_oncerr_action == ABORT) &&
		 (status != WARNING) && (status != END_OF_FILE) ) {
		abort_procs(dip);		/* Abort procs on error. */
	    }
	    /*
	     * Save the most sever error for parent exit status.
	     *
	     * Severity Priorities:	WARNING		(lowest)
	     *				END_OF_FILE
	     *				Signal Number
	     *				FATAL_ERROR	(highest)
	     */
	    if ( ((exit_status == SUCCESS) || (status == FATAL_ERROR)) ||
		 ((exit_status == WARNING) && (status > WARNING))      ||
		 ((exit_status == END_OF_FILE) && (status > WARNING)) ) {
		exit_status = status;	/* Set error code for exit. */
	    }
	}
    } /* End of while(1)... */
}

pid_t
fork_process(dinfo_t *dip)
{
    pid_t pid;

    if ((pid = fork()) == (pid_t) -1) {
	if (errno == EAGAIN) {
	    if (dip->di_procs_active == 0) {
		LogMsg (efp, logLevelCrit, 0,
			"could NOT start any processes, please check your system...\n");
		exit (FATAL_ERROR);
	    } else {
		Printf (
	"WARNING: system imposed process limit reached, only %d procs started...\n",
								dip->di_procs_active);
	    }
	} else {
	    report_error (dip, "fork", FALSE);
	    abort_procs(dip);
	}
    }
    return (pid);
}

static void
update_cmd_line(dinfo_t *dip)
{
    char *device, *bp, *p;
    char *dt_path, *options, *buffer;
    
    bp = buffer = (char *)Malloc(LOG_BUFSIZE);
    device = (dip->di_input_file) ? dip->di_input_file : dip->di_output_file;
    /* Setup pointers to dt path and dt command line. */
    dt_path = dip->di_dtcmd;
    p = strchr(dt_path, ' ');
    *p = '\0';
    options = ++p;
    /* Note: Main stripped the device options already. */
    bp += Sprintf(bp, "%s ", dt_path);
    if (dip->di_input_file) {
	bp += Sprintf(bp, "if=%s", device);
    } else {
	bp += Sprintf(bp, "of=%s", device);
    }
    /* Now, add original options. */
    bp += Sprintf(bp, " %s", options);
    if (dip->di_debug_flag || dip->di_pDebugFlag) {
	Printf("Command: %s\n", buffer);
    }
    if (dip->di_cmd_line) free(dip->di_cmd_line);
    dip->di_cmd_line = Malloc(strlen(buffer)+1);
    strcpy(dip->di_cmd_line, buffer);
    free(buffer);
    return;
}

static void
setup_iotuning(dinfo_t *dip, char *cmd)
{
    return;
}

static void
setup_multiprocs(dinfo_t *dip, char *cmd)
{
    return;
}

pid_t
start_devs(dinfo_t *dip)
{
    struct dt_procs *dtp;
    size_t psize;
    char *devs, *token, *p, *saveptr;
    int procs;

    devs = p = (dip->di_input_file) ? dip->di_input_file : dip->di_output_file;
    dip->di_num_devs = 1;
    /* Count the devices specified. */
    while (p = strchr(p, ',')) {
	dip->di_num_devs++; p++;
    }
    dip->di_max_procs = dip->di_num_devs;
    psize = (dip->di_max_procs * sizeof(*dtp));

    if ((dip->di_ptable = (struct dt_procs *)malloc(psize)) == NULL) {
	report_error(dip, "No memory for proc table", FALSE);
	exit (FATAL_ERROR);
    }
    memset(dip->di_ptable, 0, psize);
    dip->di_cur_proc = 1;
    dip->di_procs_active = 0;

    /* Remember: strtok() replaces "," with NULL! */
    token = strtok_r(devs, ",", &saveptr);
    /*
     * Start a process for each target device specified.
     */
    for (dtp = dip->di_ptable, procs = 0; procs < dip->di_max_procs; procs++, dtp++) {
	dtp->dt_device = token;
	if ((dip->di_child_pid = fork_process(dip)) == (pid_t) -1) {
	    break;
	} else if (dip->di_child_pid) {		/* Parent process gets the PID. */
	    dip->di_cur_proc++;
	    dtp->dt_pid = dip->di_child_pid;
	    dtp->dt_active = TRUE;
	    dip->di_procs_active++;
	    if (dip->di_debug_flag || dip->di_pDebugFlag) {
		Printf ("Started Process %d for %s...\n", dip->di_child_pid, dtp->dt_device);
	    }
	    token = strtok_r(NULL, ",", &saveptr); /* Next device please! */
	} else {			/* Child process... */
	    dip->di_logpid_flag = TRUE;
	    dip->di_multiple_devs = FALSE;
	    if (dip->di_input_file) {
		dip->di_input_file = dtp->dt_device;
	    } else {
		dip->di_output_file = dtp->dt_device;
	    }
	    dip->di_process_id = getpid();
	    if (dip->di_log_format) {
		dip->di_log_file = dip->di_log_format;	/* Original log file w/format strings. */
	    }
	    setup_iotuning(dip, NULL);	/* Setup IO tuning options. */
	    update_cmd_line(dip);	/* Update the command line (for logging). */
	    make_unique_log(dip);	/* Check & make a unique log. */
	    break;			/* Child process, continue... */
	}
    }
    return (dip->di_child_pid);
}

pid_t
start_procs(dinfo_t *dip)
{
    struct dt_procs *dtp;
    size_t psize;
    int procs;

    dip->di_max_procs = dip->di_num_procs;
    psize = (dip->di_max_procs * sizeof(*dtp));

    if ((dip->di_ptable = (struct dt_procs *)malloc(psize)) == NULL) {
	report_error (dip, "No memory for proc table", FALSE);
	exit (FATAL_ERROR);
    }
    memset(dip->di_ptable, '\0', psize);

    dip->di_cur_proc = 1;
    dip->di_procs_active = 0;

    for (dtp = dip->di_ptable, procs = 0; procs < dip->di_max_procs; procs++, dtp++) {
	if ((dip->di_child_pid = fork_process(dip)) == (pid_t) -1) {
	    break;
	} else if (dip->di_child_pid) {		/* Parent process gets the PID. */
	    dip->di_cur_proc++;
	    dtp->dt_pid = dip->di_child_pid;
	    dtp->dt_active = TRUE;
	    dip->di_procs_active++;
	    if (dip->di_debug_flag || dip->di_pDebugFlag) {
		Printf ("Started Process %d...\n", dip->di_child_pid);
	    }
	} else {			/* Child process... */
	    dip->di_process_id = getpid();
	    if (dip->di_output_file) {
		dip->di_unique_file = TRUE;	/* Create unique file name. */
	    }
	    if (dip->di_log_format) {
		dip->di_log_file = dip->di_log_format;	/* Original log file w/format strings. */
	    }
	    setup_iotuning(dip, NULL);	/* Setup IO tuning options. */
	    setup_multiprocs(dip, NULL);/* Setup multiple process options. */
	    make_unique_log(dip);	/* Check & make a unique log. */
	    break;			/* Child process, continue... */
	}
    }
    return (dip->di_child_pid);
}

pid_t
start_slices(dinfo_t *dip)
{
    struct dt_procs *dtp;
    size_t psize;
    struct slice_info slice_info;
    slice_info_t *sip = &slice_info;
    large_t data_resid;
    int procs;

    dip->di_max_procs = dip->di_num_slices;
    psize = (dip->di_max_procs * sizeof(*dtp));

    if ((dip->di_ptable = (struct dt_procs *)malloc(psize)) == NULL) {
	report_error (dip, "No memory for proc table", FALSE);
	exit (FATAL_ERROR);
    }
    memset(dip->di_ptable, '\0', psize);

    init_slice_info(dip, sip, &data_resid);

    dip->di_cur_proc = 1;
    dip->di_procs_active = 0;

    for (dtp = dip->di_ptable, procs = 0; procs < dip->di_max_procs; procs++, dtp++) {
	sip->slice++;
	/* Last slice gets any residual bytes. */
	if ((procs + 1) == dip->di_max_procs) {
	    sip->slice_length += data_resid;
	}
	if ((dip->di_child_pid = fork_process(dip)) == (pid_t) -1) {
	    break;
	} else if (dip->di_child_pid) {		/* Parent process gets the PID. */
	    dip->di_cur_proc++;
	    dtp->dt_pid = dip->di_child_pid;
	    dtp->dt_active = TRUE;
	    dip->di_procs_active++;
	    if (dip->di_debug_flag || dip->di_pDebugFlag) {
		Printf ("Started Slice %d, PID %d...\n", sip->slice, dip->di_child_pid);
	    }
	    if (procs < dip->di_max_procs) {
		sip->slice_position += sip->slice_length;
	    }
	} else {			/* Child process... */
	    /*
	     * Initialize the starting data pattern for each slice.
	     */
	    dip->di_process_id = getpid();
	    if (dip->di_unique_pattern) {
		dip->di_pattern = data_patterns[(dip->di_cur_proc - 1) % npatterns];
	    }
	    if (dip->di_log_format) {
		dip->di_log_file = dip->di_log_format;	/* Original log file w/format strings. */
	    }
	    setup_iotuning(dip, NULL);	/* Setup IO tuning options. */
	    setup_multiprocs(dip, NULL);/* Setup multiple process options. */
	    make_unique_log(dip);	/* Check & make a unique log. */
	    setup_slice(dip, sip);
	    break;			/* Child process, continue... */
	}
    }
    return (dip->di_child_pid);
}
#endif /* !defined(WIN32) */

void
init_slice(struct dinfo *dip, int slice)
{
    struct slice_info slice_info;
    slice_info_t *sip = &slice_info;
    large_t data_resid;

    init_slice_info(dip, sip, &data_resid);
    sip->slice_position += (sip->slice_length * (slice - 1));
    /*
     * Any residual goes to the last slice.
     */
    if (slice == dip->di_num_slices) {
	sip->slice_length += data_resid;
    }
    sip->slice = slice;
    setup_slice(dip, sip);

    /*
     * Initialize the starting data pattern for each slice.
     */
    if (dip->di_unique_pattern) {
	dip->di_pattern = data_patterns[(slice - 1) % npatterns];
    }
    return;
}

static void
init_slice_info(struct dinfo *dip, slice_info_t *sip, large_t *data_resid)
{
    large_t dlimit = (dip->di_data_limit - dip->di_file_position);
    large_t slice_length;

    sip->slice = 0;
    sip->slice_position = dip->di_file_position;
    slice_length = (dlimit / dip->di_num_slices);
    sip->slice_length = rounddown(slice_length, dip->di_dsize);
    if (sip->slice_length < dip->di_dsize) {
	LogMsg (efp, logLevelCrit, 0,
		"Slice length of " LUF " bytes is too small!\n",
						sip->slice_length);
	exit (FATAL_ERROR);
    }
    *data_resid = (dlimit - (sip->slice_length * dip->di_num_slices));
    *data_resid = rounddown(*data_resid, dip->di_dsize);
    return;
}

static void
setup_slice(struct dinfo *dip, slice_info_t *sip)
{
    dip->di_file_position = sip->slice_position;
    if (dip->di_random_io) {
	dip->di_rdata_limit = (dip->di_file_position + sip->slice_length);
    }
    /*
     * Restrict data limit to slice length or user set limit.
     */
    dip->di_data_limit = MIN(dip->di_data_limit, sip->slice_length);
    if (dip->di_debug_flag || dip->di_Debug_flag || dip->di_pDebugFlag) {
	large_t dlimit = (dip->di_random_io) ? dip->di_rdata_limit : dip->di_data_limit;
	Printf("Slice %d Information:\n"
		"\t\t Start: " FUF " offset (lba " LUF ")\n"
		"\t\t   End: " FUF " offset (lba " LUF ")\n"
		"\t\tLength: " FUF " bytes (" LUF " blocks)\n"
		"\t\t Limit: " FUF " bytes (" LUF " blocks)\n",
		sip->slice,
		dip->di_file_position, (large_t)(dip->di_file_position / dip->di_dsize),
		(dip->di_file_position + sip->slice_length),
		(large_t)((dip->di_file_position + sip->slice_length) / dip->di_dsize),
		sip->slice_length, (large_t)(sip->slice_length / dip->di_dsize),
		dlimit, (large_t)(dlimit / dip->di_dsize));
    }
    dip->di_slice_num = sip->slice;
    return;
}

/*
 * make_unique_file() - Make the File Unique.
 *
 * Description:
 *	This function makes the file name unique by appending the
 * process ID.  An assumption is made that this is a regular file.
 *
 * Inputs:
 *	dip = The device information pointer.
 *	file = The file name.
 *
 * Return Value:
 *	Returns the unique file name.
 */
char *
make_unique_file(dinfo_t *dip, char *file)
{
    char *bp;
    /*
     * Construct unique file name for file system I/O.
     */
    bp = (char *)malloc(strlen(file) + PROC_ALLOC);
    /* Note: We may get called with a top level directory! */
    if (file[strlen(file)-1] == DIRSEP) {
	(void)sprintf(bp, "%s%d", file, dip->di_process_id);
    } else {
	(void)sprintf(bp, "%s-%d", file, dip->di_process_id);
    }
    return (bp);
}

/*
 * This function creates a unique log file name.
 * 
 * Inputs:
 * 	dip = The device information pointer.
 * 
 * Return Value:
 * 	None (void)
 */
void
make_unique_log(dinfo_t *dip)
{
    /*
     * Create a unique log file (if requested).
     */
    if (dip->di_log_file && (dip->di_unique_log || strstr (dip->di_log_file, "%")) ) {
        char logfmt[STRING_BUFFER_SIZE];
        strcpy(logfmt, dip->di_log_file);
        if ( strstr(dip->di_log_file, "%pid") == (char *) 0 ) {
            strcat(logfmt, "-%pid");
        }
        dip->di_log_file = FmtLogFile(dip, logfmt);
	if (freopen (dip->di_log_file, (dip->di_logappend_flag) ? "a" : "w", efp) == NULL) {
	    Perror ("freopen() of %s failed, exiting...\n", dip->di_log_file);
	    exit (FAILURE);
	}
	if (dip->di_header_flag) log_header(dip);
    }
}

/*
 * skip_device_prefix() - Simple Utility Function to skip device prefixes.
 * 
 * Inputs:
 *      device = The device path (may be raw or file system)
 * 
 * Return Value:
 *      Returns the updated device path past device directory prefix.
 */ 
char *
skip_device_prefix(char *device)
{
    if ( EQL(device, DEV_PREFIX, DEV_LEN) ) {
        device += DEV_LEN;
    } else if (EQL(device, ADEV_PREFIX, ADEV_LEN) ) {
        device += ADEV_LEN;
#if defined(NDEV_PREFIX)
    } else if ( EQL(device, NDEV_PREFIX, NDEV_LEN) ) {
        device += NDEV_LEN;
#endif /* defined(NDEV_PREFIX) */
    }
    return (device);
}

/*
 * FmtLogFile() - Format the Log File Name.
 *
 * Special Format Characters:
 *
 * 	%device = The device path.
 * 	%dsf = The device name only.
 *	%iodir = The I/O direction.
 *	%iotype = The I/O type.
 *	%host = The host name.
 *	%pid = The process ID.
 *	%user = The user (login) name.
 *
 * Please Note: For the parent processing multiple devices, the %dsf and
 * %device format strings are omitted, as they are passed to the child for
 * formatting the device name or path in its' log file name.
 *
 * Inputs:
 *	dip = The device information pointer.
 *	logfile = Pointer to the logfile name.
 *
 * Return Value:
 *      Returns a pointer to the formatted log file.
 */
char *
FmtLogFile(dinfo_t *dip, char *logfile)
{
    char	*logname;
    char	*from = logfile;
    char	*buffer, *to;
    int		length = strlen(logfile);
    int		ifs;
    /* TODO: Define this in an include file! */
#if defined(WIN32)
    ifs = '\\';
#else /* !defined(WIN32) */
    ifs = '/';
#endif /* defined(WIN32) */

    buffer = to = Malloc(KBYTE_SIZE);
    while (length--) {
        if (*from == '%') {
            char *key = (from + 1);
	    if (strncasecmp(key, "device", 6) == 0) {
		char *device = (dip->di_input_file) ? dip->di_input_file : dip->di_output_file;
		if (dip->di_multiple_devs) {
		    to += Sprintf(to, "multi-devices");
	      } else {
		    char *dptr, *pptr, *sptr;
		    dptr = strdup(device);
		    pptr = sptr = skip_device_prefix(dptr);
		    /* Replace path delimiter(s) with undersores. */
		    while (sptr = strchr(sptr, ifs)) {
			*sptr++ = '_';
		    }
		    sptr = pptr;
		    /* Replace periods with an underscore too! */
		    while (sptr = strchr(sptr, '.')) {
			*sptr++ = '_';
		  }
		    to += Sprintf(to, "%s", pptr);
		    free(dptr);
		}
                length -= 6;
                from += 7;
                continue;
	    } else if (strncasecmp(key, "dsf", 3) == 0) {
		char *device = (dip->di_input_file) ? dip->di_input_file : dip->di_output_file;
		/* Note: Log file is opened *before* device checks! */
		if (dip->di_multiple_devs) {
		    to += Sprintf(to, "multi-dsfs");
		} else {
		    char *dptr, *pptr, *sptr;
		    dptr = strdup(device);
		    pptr = sptr = skip_device_prefix(dptr);
		    /* Add basename of the device path. */
		    if (sptr = strrchr(pptr, ifs)) {
			sptr++;
		    } else {
			sptr = pptr;
		    }
		    to += Sprintf(to, "%s", sptr);
		    free(dptr);
		}
		length -= 3;
		from += 4;
		continue;
	    } else if (strncasecmp(key, "iodir", 5) == 0) {
                if (dip->di_io_dir == FORWARD) {
                    to += Sprintf(to, "%s", "forward");
                } else {
                    to += Sprintf(to, "%s", "reverse");
                }
                length -= 5;
                from += 6;
                continue;
            } else if (strncasecmp(key, "iotype", 6) == 0) {
                if (dip->di_io_type == SEQUENTIAL_IO) {
                    to += Sprintf(to, "%s", "sequential");
                } else {
                    to += Sprintf(to, "%s", "random");
                }
                length -= 6;
                from += 7;
                continue;
            } else if (strncasecmp(key, "host", 4) == 0) {
                char *p, hostname[MAXHOSTNAMELEN];
#if defined(WIN32)
                DWORD len = MAXHOSTNAMELEN;
		if ( (GetComputerNameEx(ComputerNameDnsFullyQualified,
					    hostname, &len)) == 0) {
		      wPerror("GetComputerNameEx() failed!");
#else /* !defined(WIN32) */
                if ( gethostname(hostname, sizeof(hostname)) ) {
                    Perror("gethostname() failed");
#endif /* defined(WIN32) */
                    return(logfile);
                }
                if (p = strchr(hostname, '.')) {
                    *p = '\0';
                }
                to += Sprintf(to, "%s", hostname);
                length -= 4;
                from += 5;
                continue;
            } else if (strncasecmp(key, "pid", 3) == 0) {
                pid_t pid = getpid();
                to += Sprintf(to, "%d", pid);
                length -= 3;
                from += 4;
                continue;
            } else if (strncasecmp(key, "user", 4) == 0) {
#if defined(WIN32)
                DWORD	size = STRING_BUFFER_SIZE;
                TCHAR	buf[STRING_BUFFER_SIZE];
                char	*username;
                GetUserName(buf, &size);
                username = buf;
#else /* !defined(WIN32) */
                char *username = getlogin();
#endif /* defined(WIN32) */
                if (username) {
                    to += Sprintf(to, "%s", username);
                } else {
#if defined(WIN32)
                    Fprintf("GetUserName failed !\n");
#else /* !defined(WIN32) */
                    Perror("getlogin()");
#endif /* defined(WIN32) */
                    return(logfile);
                }
                length -= 4;
                from += 5;
                continue;
            }
        }
        *to++ = *from++;
    }
    logname = Malloc( strlen(buffer) + 1 );
    (void)strcpy(logname, buffer);
    free (buffer);
    return (logname);
}

/*
 * FmtFilePath() - Format the File Path.
 *
 * Special Format Characters:
 *
 * 	%device = The device path.
 * 	%dsf = The device name only.
 *	%iodir = The I/O direction.
 * 	%iotype = The I/O type.
 * 	%iotune - The default I/O tune file path.
 *	%host = The host name.
 * 	%pid = The process ID.
 * 	%tmpdir = The temporary directory.
 *	%user = The user (login) name.
 *
 * Please Note: For the parent processing multiple devices, the %dsf and
 * %device format strings are omitted, as they are passed to the child for
 * formatting the device name or path in its' log file name.
 *
 * Inputs:
 *	dip = The device information pointer.
 *	filepath = Pointer to the original file path.
 *
 * Return Value:
 *      Returns a pointer to the converted file path.
 */
char *
FmtFilePath(dinfo_t *dip, char *filepath)
{
    char	*filename;
    char	*from = filepath;
    char	*buffer, *to;
    int		length = strlen(filepath);
    int		ifs = DIRSEP;

    buffer = to = Malloc(KBYTE_SIZE);
    while (length--) {
        if (*from == '%') {
            char *key = (from + 1);
	    if (strncasecmp(key, "device", 6) == 0) {
		char *device = (dip->di_input_file) ? dip->di_input_file : dip->di_output_file;
		if (dip->di_multiple_devs) {
		    to += Sprintf(to, "multi-devices");
	      } else {
		    char *dptr, *pptr, *sptr;
		    dptr = strdup(device);
		    pptr = sptr = skip_device_prefix(dptr);
		    /* Replace path delimiter(s) with undersores. */
		    while (sptr = strchr(sptr, ifs)) {
			*sptr++ = '_';
		    }
		    sptr = pptr;
		    /* Replace periods with an underscore too! */
		    while (sptr = strchr(sptr, '.')) {
			*sptr++ = '_';
		  }
		    to += Sprintf(to, "%s", pptr);
		    free(dptr);
		}
                length -= 6;
                from += 7;
                continue;
	    } else if (strncasecmp(key, "dsf", 3) == 0) {
		char *device = (dip->di_input_file) ? dip->di_input_file : dip->di_output_file;
		/* Note: Log file is opened *before* device checks! */
		if (dip->di_multiple_devs) {
		    to += Sprintf(to, "multi-dsfs");
		} else {
		    char *dptr, *pptr, *sptr;
		    dptr = strdup(device);
		    pptr = sptr = skip_device_prefix(dptr);
		    /* Add basename of the device path. */
		    if (sptr = strrchr(pptr, ifs)) {
			sptr++;
		    } else {
			sptr = pptr;
		    }
		    to += Sprintf(to, "%s", sptr);
		    free(dptr);
		}
		length -= 3;
		from += 4;
		continue;
	    } else if (strncasecmp(key, "iodir", 5) == 0) {
                if (dip->di_io_dir == FORWARD) {
                    to += Sprintf(to, "%s", "forward");
                } else {
                    to += Sprintf(to, "%s", "reverse");
                }
                length -= 5;
                from += 6;
                continue;
            } else if (strncasecmp(key, "iotype", 6) == 0) {
                if (dip->di_io_type == SEQUENTIAL_IO) {
                    to += Sprintf(to, "%s", "sequential");
                } else {
                    to += Sprintf(to, "%s", "random");
                }
                length -= 6;
                from += 7;
                continue;
            } else if (strncasecmp(key, "iotune", 6) == 0) {
		to += Sprintf(to, "%s", DEFAULT_IOTUNE_FILE);
                length -= 6;
                from += 7;
                continue;
            } else if (strncasecmp(key, "host", 4) == 0) {
                char *p, *hostname;
		hostname = os_gethostname();
		if (hostname) {
		    if (p = strchr(hostname, '.')) {
			*p = '\0';
		    }
		    to += Sprintf(to, "%s", hostname);
		    free(hostname);
		}
                length -= 4;
                from += 5;
                continue;
            } else if (strncasecmp(key, "pid", 3) == 0) {
                pid_t pid = getpid();
                to += Sprintf(to, "%d", pid);
                length -= 3;
                from += 4;
                continue;
            } else if (strncasecmp(key, "tmpdir", 6) == 0) {
		to += Sprintf(to, "%s", TEMP_DIR_NAME);
                length -= 6;
                from += 7;
                continue;
            } else if (strncasecmp(key, "user", 4) == 0) {
		char *username;
		username = os_getusername();
                if (username) {
                    to += Sprintf(to, "%s", username);
		    free(username);
                }
                length -= 4;
                from += 5;
                continue;
            }
        }
        *to++ = *from++;
    }
    filename = Malloc( strlen(buffer) + 1 );
    (void)strcpy(filename, buffer);
    free (buffer);
    return (filename);
}
