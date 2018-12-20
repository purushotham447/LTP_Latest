/*******************************************************************************
 * Copyright (c) 2007, 2014 Wind River Systems, Inc. and others.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 * The Eclipse Public License is available at
 * http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 * http://www.eclipse.org/org/documents/edl-v10.php.
 * You may elect to redistribute this code under either of these licenses.
 *
 * Contributors:
 *     Wind River Systems - initial API and implementation
 *******************************************************************************/

/*
 * This module handles process/thread OS contexts and their state machine.
 */

#include <tcf/config.h>

#if defined(_WIN32) || defined(__CYGWIN__)

#if ENABLE_DebugContext && !ENABLE_ContextProxy

#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <psapi.h>
#include <tcf/framework/context.h>
#include <tcf/framework/events.h>
#include <tcf/framework/errors.h>
#include <tcf/framework/trace.h>
#include <tcf/framework/myalloc.h>
#include <tcf/framework/waitpid.h>
#include <tcf/framework/signames.h>
#include <tcf/services/symbols.h>
#include <tcf/services/breakpoints.h>
#include <tcf/services/memorymap.h>
#include <tcf/services/runctrl.h>
#if ENABLE_ContextMux
#include <tcf/framework/context-mux.h>
#endif
#include <system/Windows/tcf/context-win32.h>
#if defined(__CYGWIN__)
#  include <system/Cygwin/tcf/regset.h>
#else
#  include <system/Windows/tcf/regset.h>
#endif
#include <system/Windows/tcf/windbgcache.h>

#define BREAK_TIMEOUT 100000

#define EXCEPTION_WX86_SINGLE_STEP 0x4000001e
#define EXCEPTION_WX86_BREAKPOINT 0x4000001f

#ifndef CONTEXT_ALL
#define CONTEXT_ALL CONTEXT_FULL
#endif

#if defined(_M_IX86)
#  define reg_ip Eip
#  define reg_sp Esp
typedef DWORD REGWORD;
#elif defined(_M_AMD64)
#  define reg_ip Rip
#  define reg_sp Rsp
typedef DWORD64 REGWORD;
#endif

typedef struct ContextExtensionWin32 {
    pid_t               pid;
    HANDLE              handle;
    DEBUG_EVENT         debug_event;
    EXCEPTION_DEBUG_INFO suspend_reason;
    int                 stop_pending;
    int                 start_pending;
    REG_SET *           regs;               /* copy of context registers, updated when context stops */
    ErrorReport *       regs_error;         /* if not NULL, 'regs' is invalid */
    int                 regs_dirty;         /* if not 0, 'regs' is modified and needs to be saved before context is continued */
    int                 trace_flag;
    uint8_t             step_opcodes[4];
    SIZE_T              step_opcodes_len;
    ContextAddress      step_opcodes_addr;
    struct DebugState * debug_state;
} ContextExtensionWin32;

static size_t context_extension_offset = 0;

#define EXT(ctx) ((ContextExtensionWin32 *)((char *)(ctx) + context_extension_offset))

typedef struct DebugState {
    int                 error;
    int                 state;
    DWORD               process_id;
    DWORD               debug_thread_id;
    HANDLE              debug_thread;
    HANDLE              debug_thread_semaphore;
    HANDLE              debug_event_inp;
    HANDLE              debug_event_out;
    DWORD               ini_thread_id;
    HANDLE              ini_thread_handle;
    DWORD               main_thread_id;
    HANDLE              main_thread_handle;
    /* Note that while reporting debug events, all threads within the reporting process are frozen. */
    int                 reporting_debug_event;
    int                 break_posted;
    HANDLE              break_thread;
    LPVOID              break_thread_code;
    DWORD               break_thread_id;
    unsigned            break_event_generation;
    unsigned            debug_event_generation;
    HANDLE              file_handle;
    DWORD64             base_address;
    int                 wow64;
    HANDLE              module_handle;
    DWORD64             module_address;
    ContextAttachCallBack * attach_callback;
    void *              attach_data;
    int                 attach_mode;
    int                 detach;
    /* NtContinue() changes Dr6 and Dr7, so HW breakpoints should be disabled until NtContinue() is done */
    int                 ok_to_use_hw_bp;
    /* Array of threads pending attachment */
    DWORD *             pending_thrs;
    unsigned            max_pending_thrs_cnt;
    unsigned            pending_thrs_cnt;
} DebugState;

#define DEBUG_STATE_INIT            0
#define DEBUG_STATE_PRS_CREATED     1
#define DEBUG_STATE_PRS_ATTACHED    2

typedef struct DebugEvent {
    DebugState * debug_state;
    DEBUG_EVENT win32_event;
    DWORD continue_status;
} DebugEvent;

static OSVERSIONINFOEX os_version;

#define MAX_EXCEPTION_HANDLERS 8
static ContextExceptionHandler * exception_handlers[MAX_EXCEPTION_HANDLERS];
static unsigned exception_handler_cnt = 0;

static MemoryErrorInfo mem_err_info;

#include <tcf/framework/pid-hash.h>

#define EXCEPTION_DEBUGGER_IO 0x406D1388

const char * context_suspend_reason(Context * ctx) {
    ContextExtensionWin32 * ext = EXT(ctx);
    DWORD exception_code = ext->suspend_reason.ExceptionRecord.ExceptionCode;
    static char buf[64];

    if (exception_code == 0) return REASON_USER_REQUEST;
    if (ext->suspend_reason.dwFirstChance) {
        if (exception_code == EXCEPTION_SINGLE_STEP) return REASON_STEP;
        if (exception_code == EXCEPTION_BREAKPOINT) return "Break Instruction";
        snprintf(buf, sizeof(buf), "Exception %#lx", (unsigned long)exception_code);
    }
    else {
        snprintf(buf, sizeof(buf), "Unhandled exception %#lx", (unsigned long)exception_code);
    }
    return buf;
}

static int get_signal_index(Context * ctx) {
    ContextExtensionWin32 * ext = EXT(ctx);
    DWORD exception_code = ext->suspend_reason.ExceptionRecord.ExceptionCode;

    if (exception_code == 0) return 0;
    return get_signal_from_code(exception_code);
}

static const char * win32_debug_event_name(int event) {
    switch (event) {
    case CREATE_PROCESS_DEBUG_EVENT:
        return "CREATE_PROCESS_DEBUG_EVENT";
    case CREATE_THREAD_DEBUG_EVENT:
        return "CREATE_THREAD_DEBUG_EVENT";
    case EXCEPTION_DEBUG_EVENT:
        return "EXCEPTION_DEBUG_EVENT";
    case EXIT_PROCESS_DEBUG_EVENT:
        return "EXIT_PROCESS_DEBUG_EVENT";
    case EXIT_THREAD_DEBUG_EVENT:
        return "EXIT_THREAD_DEBUG_EVENT";
    case LOAD_DLL_DEBUG_EVENT:
        return "LOAD_DLL_DEBUG_EVENT";
    case OUTPUT_DEBUG_STRING_EVENT:
        return "OUTPUT_DEBUG_STRING_EVENT";
    case UNLOAD_DLL_DEBUG_EVENT:
        return "UNLOAD_DLL_DEBUG_EVENT";
    }
    return "Unknown";
}

static int log_error(const char * fn, int ok) {
    int err;
    if (ok) return 0;
    assert(is_dispatch_thread());
    err = set_win32_errno(GetLastError());
    trace(LOG_ALWAYS, "context: %s: %s", fn, errno_to_str(errno));
    return err;
}

static void get_registers(Context * ctx) {
    ContextExtensionWin32 * ext = EXT(ctx);

    if (ctx->stopped && ext->regs->ContextFlags) return;

    assert(!ctx->exited);
    assert(context_has_state(ctx));

    ext->regs->ContextFlags = CONTEXT_ALL;
    if (GetThreadContext(ext->handle, ext->regs) == 0) {
        ext->regs_error = get_error_report(log_error("GetThreadContext", 0));
    }
    else {
        ext->trace_flag = (ext->regs->EFlags & 0x100) != 0;
        trace(LOG_CONTEXT, "context: get regs OK: ctx %#lx, id %s, PC %#lx",
            ctx, ctx->id, ext->regs->reg_ip);
    }
}

static DWORD event_win32_context_stopped(Context * ctx) {
    ContextExtensionWin32 * ext = EXT(ctx);
    DebugState * debug_state = EXT(ctx->mem)->debug_state;
    ContextAddress exception_addr = (ContextAddress)ext->suspend_reason.ExceptionRecord.ExceptionAddress;
    DWORD exception_code = ext->suspend_reason.ExceptionRecord.ExceptionCode;
    DWORD continue_status = DBG_CONTINUE;

    assert(is_dispatch_thread());
    assert(!ctx->exited);
    assert(!ctx->stopped);
    assert(ext->handle != NULL);
    assert(ctx->parent != NULL);

    ext->stop_pending = 0;
    ext->start_pending = 0;

    trace(LOG_CONTEXT, "context: stopped: ctx %#lx, id %s, exception %#lx",
        ctx, ctx->id, exception_code);

    if (SuspendThread(ext->handle) == (DWORD)-1) {
        DWORD err = GetLastError();
        ctx->exiting = 1;
        if (err == ERROR_ACCESS_DENIED) {
            /* Already exited */
            return DBG_CONTINUE;
        }
        log_error("SuspendThread", 0);
        return DBG_EXCEPTION_NOT_HANDLED;
    }

    if (ext->regs_error) {
        release_error_report(ext->regs_error);
        ext->regs_error = NULL;
    }
    memset(ext->regs, 0, sizeof(REG_SET));

    ctx->signal = get_signal_index(ctx);
    sigset_clear(&ctx->pending_signals);
    ctx->stopped = 1;
    ctx->stopped_by_bp = 0;
    ctx->stopped_by_cb = NULL;
    if (exception_code == 0) {
        ctx->stopped_by_exception = 0;
    }
    else if (ext->suspend_reason.dwFirstChance) {
        int cb_found = 0;
        ctx->stopped_by_exception = 0;
        switch (exception_code) {
        case EXCEPTION_SINGLE_STEP:
        case EXCEPTION_WX86_SINGLE_STEP:
            get_registers(ctx);
            if (!ext->regs_error) {
                cpu_bp_on_suspend(ctx, &cb_found);
                if (ext->step_opcodes_len > 0 && ext->step_opcodes[0] == 0x9c && ext->step_opcodes_addr != ext->regs->reg_ip) {
                    /* PUSHF instruction: need to clear trace flag from top of the stack */
                    SIZE_T bcnt = 0;
                    ContextAddress buf = 0;
                    assert(ext->regs->EFlags & 0x100);
                    assert(ext->step_opcodes_addr == ext->regs->reg_ip - 1);
                    if (!ReadProcessMemory(EXT(ctx->mem)->handle, (LPCVOID)ext->regs->reg_sp, &buf, sizeof(ContextAddress), &bcnt) || bcnt != sizeof(ContextAddress)) {
                        log_error("ReadProcessMemory", 0);
                    }
                    else {
                        assert(buf & 0x100);
                        buf &= ~0x100;
                        if (!WriteProcessMemory(EXT(ctx->mem)->handle, (LPVOID)ext->regs->reg_sp, &buf, sizeof(ContextAddress), &bcnt) || bcnt != sizeof(ContextAddress)) {
                            log_error("WriteProcessMemory", 0);
                        }
                    }
                }
                if (!cb_found && ext->step_opcodes_len == 0) {
                    continue_status = DBG_EXCEPTION_NOT_HANDLED;
                }
                else if (is_breakpoint_address(ctx, ext->regs->reg_ip)) {
                    ctx->stopped_by_bp = 1;
                }
            }
            else {
                continue_status = DBG_EXCEPTION_NOT_HANDLED;
            }
            ext->step_opcodes_len = 0;
            ext->step_opcodes_addr = 0;
            break;
        case EXCEPTION_BREAKPOINT:
        case EXCEPTION_WX86_BREAKPOINT:
            get_registers(ctx);
            if (!ext->regs_error && is_breakpoint_address(ctx, exception_addr)) {
                ext->regs->reg_ip = exception_addr;
                ext->regs_dirty = 1;
                ctx->stopped_by_bp = 1;
                if (!debug_state->ok_to_use_hw_bp) {
                    debug_state->ok_to_use_hw_bp = 1;
                    send_context_changed_event(ctx->mem);
                    memory_map_event_mapping_changed(ctx->mem);
                }
            }
            else {
                continue_status = DBG_EXCEPTION_NOT_HANDLED;
            }
            break;
        case EXCEPTION_DEBUGGER_IO:
            trace(LOG_ALWAYS, "Debugger IO request %#lx",
                ext->suspend_reason.ExceptionRecord.ExceptionInformation[0]);
            break;
        default:
            continue_status = DBG_EXCEPTION_NOT_HANDLED;
            break;
        }
        if (continue_status == DBG_EXCEPTION_NOT_HANDLED) {
            unsigned i;
            for (i = 0; i < exception_handler_cnt; i++) {
                if (exception_handlers[i](ctx, &ext->suspend_reason)) {
                    continue_status = DBG_CONTINUE;
                }
            }
        }
        if (continue_status == DBG_EXCEPTION_NOT_HANDLED) {
            int intercept = 1;
            ctx->stopped_by_exception = 1;
            if (ctx->signal) {
                sigset_set(&ctx->pending_signals, ctx->signal, 1);
                if (sigset_get(&ctx->sig_dont_pass, ctx->signal)) {
                    continue_status = DBG_CONTINUE;
                }
                if (sigset_get(&ctx->sig_dont_stop, ctx->signal)) {
                    intercept = 0;
                }
            }
            if (intercept) ctx->pending_intercept = 1;
        }
    }
    else {
        ctx->stopped_by_exception = 1;
        if (!ctx->mem->exiting) ctx->pending_intercept = 1;
        continue_status = DBG_EXCEPTION_NOT_HANDLED;
    }
    send_context_stopped_event(ctx);
    return continue_status;
}

static void event_win32_context_started(Context * ctx) {
    ContextExtensionWin32 * ext = EXT(ctx);
    trace(LOG_CONTEXT, "context: started: ctx %#lx, id %s", ctx, ctx->id);
    assert(ctx->stopped);
    ext->stop_pending = 0;
    send_context_started_event(ctx);
}

static int win32_resume(Context * ctx, int step);

static void event_win32_context_exited(Context * ctx, int detach) {
    ContextExtensionWin32 * ext = EXT(ctx);
    LINK * l = NULL;
    trace(LOG_CONTEXT, "context: exited: ctx %#lx, id %s", ctx, ctx->id);
    assert(!ctx->exited);
    context_lock(ctx);
    ctx->exiting = 1;
    ext->stop_pending = 0;
    if (ctx->stopped) event_win32_context_started(ctx);
    l = ctx->children.next;
    while (l != &ctx->children) {
        Context * c = cldl2ctxp(l);
        l = l->next;
        assert(c->parent == ctx);
        if (!c->exited) event_win32_context_exited(c, detach);
    }
    release_error_report(ext->regs_error);
    loc_free(ext->regs);
    ext->regs_error = NULL;
    ext->regs = NULL;
    send_context_exited_event(ctx);
    if (ext->handle != NULL) {
        while (detach && ctx->parent != NULL && ResumeThread(ext->handle) > 0) {}
        if (!detach) {
            if (ctx->mem != ctx) {
                log_error("CloseHandle", CloseHandle(ext->handle));
            }
            else if (os_version.dwMajorVersion <= 5) {
                /* Bug in Windows XP: ContinueDebugEvent() does not close exited process handle */
                log_error("CloseHandle", CloseHandle(ext->handle));
            }
        }
        ext->handle = NULL;
    }
    if (ext->debug_state != NULL && ext->debug_state->file_handle != NULL) {
        log_error("CloseHandle", CloseHandle(ext->debug_state->file_handle));
        ext->debug_state->file_handle = NULL;
    }
    ext->debug_state = NULL;
    context_unlock(ctx);
}

static DWORD WINAPI remote_thread_func(LPVOID args) {
    return 0;
}

static void post_break_process_event(Context * ctx);

static void break_process_event(void * args) {
    Context * ctx = (Context *)args;
    ContextExtensionWin32 * ext = EXT(ctx);

    if (ext->debug_state != NULL) {
        LINK * l;
        int cnt = 0;
        DebugState * debug_state = ext->debug_state;

        assert(debug_state->break_posted);
        debug_state->break_posted = 0;
        if (!ctx->exited && debug_state->break_thread == NULL && ext->debug_state->detach == 0) {
            for (l = ctx->children.next; l != &ctx->children; l = l->next) {
                Context * c  = cldl2ctxp(l);
                if (EXT(c)->stop_pending) {
                    assert(!c->stopped);
                    assert(!c->exited);
                    cnt++;
                }
            }
            if (cnt > 0) {
                if (debug_state->break_event_generation != debug_state->debug_event_generation) {
                    /* Target state changed after break request was posted. Re-post the request. */
                    post_break_process_event(ctx);
                }
                else {
                    const SIZE_T buf_size = 0x100;
                    SIZE_T size = 0;
                    int error = 0;

                    for (l = ctx->children.next; l != &ctx->children; l = l->next) {
                        SuspendThread(EXT(cldl2ctxp(l))->handle);
                    }

                    trace(LOG_CONTEXT, "context: creating remote thread in process %#lx, id %s", ctx, ctx->id);
                    if (debug_state->break_thread_code == NULL) {
                        debug_state->break_thread_code = VirtualAllocEx(ext->handle,
                            NULL, buf_size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
                        error = log_error("VirtualAllocEx", debug_state->break_thread_code != NULL);
                    }

                    if (!error) error = log_error("WriteProcessMemory", WriteProcessMemory(ext->handle,
                        debug_state->break_thread_code, (LPCVOID)remote_thread_func, buf_size, &size) && size == buf_size);

                    if (!error) error = log_error("CreateRemoteThread", (debug_state->break_thread = CreateRemoteThread(ext->handle,
                        0, 0, (DWORD (WINAPI*)(LPVOID))debug_state->break_thread_code, NULL, 0, &debug_state->break_thread_id)) != NULL);

                    if (error) {
                        debug_state->break_thread = NULL;
                        debug_state->break_thread_id = 0;
                    }
                }
            }
        }
    }
    context_unlock(ctx);
}

static void post_break_process_event(Context * ctx) {
    ContextExtensionWin32 * ext = EXT(ctx);
    DebugState * debug_state = ext->debug_state;

    assert(ctx->parent == NULL);
    assert(!debug_state->break_posted);
    context_lock(ctx);
    post_event_with_delay(break_process_event, ctx, BREAK_TIMEOUT);
    debug_state->break_event_generation = debug_state->debug_event_generation;
    debug_state->break_posted = 1;
}

static int win32_resume(Context * ctx, int step) {
    Context * prs = ctx->parent;
    ContextExtensionWin32 * ext = EXT(ctx);
    ContextExtensionWin32 * prs_ext = EXT(prs);
    DebugState * debug_state = prs_ext->debug_state;
    int cpu_bp_step = 0;

    assert(ctx->stopped);
    assert(!ctx->exited);

    if (debug_state->reporting_debug_event) {
        debug_state->reporting_debug_event++;
    }

    if (cpu_bp_on_resume(ctx, &cpu_bp_step) < 0) return -1;
    if (cpu_bp_step) step = 1;
    if (skip_breakpoint(ctx, step)) return 0;

    /* Update CPU trace flag */
    if (debug_state->detach) step = 0;
    if (!step && ext->trace_flag) {
        get_registers(ctx);
        ext->regs->EFlags &= ~0x100;
        ext->regs_dirty = 1;
    }
    else if (step && !ext->trace_flag) {
        get_registers(ctx);
        ext->regs->EFlags |= 0x100;
        ext->regs_dirty = 1;
    }

    /* Flash registers if dirty */
    if (ext->regs_dirty) {
        assert(ext->regs->ContextFlags);
        if (ext->regs_error) {
            trace(LOG_ALWAYS, "Can't resume thread, registers copy is invalid: ctx %#lx, id %s", ctx, ctx->id);
            errno = set_error_report_errno(ext->regs_error);
            return -1;
        }
        if (SetThreadContext(ext->handle, ext->regs) == 0) {
            errno = log_error("SetThreadContext", 0);
            return -1;
        }
        ext->trace_flag = (ext->regs->EFlags & 0x100) != 0;
        ext->regs_dirty = 0;
    }

    if (ext->trace_flag) {
        get_registers(ctx);
        if (ext->regs_error) {
            set_error_report_errno(ext->regs_error);
            return -1;
        }
        ext->step_opcodes_addr = ext->regs->reg_ip;
        if (!ReadProcessMemory(prs_ext->handle, (LPCVOID)ext->regs->reg_ip, &ext->step_opcodes,
                sizeof(ext->step_opcodes), &ext->step_opcodes_len) || ext->step_opcodes_len == 0) {
            errno = log_error("ReadProcessMemory", 0);
            return -1;
        }
    }
    if (debug_state->reporting_debug_event && !debug_state->detach) {
        ext->start_pending = 1;
    }
    else {
        ext->start_pending = 0;
        for (;;) {
            DWORD cnt = ResumeThread(ext->handle);
            if (cnt == (DWORD)-1) {
                errno = log_error("ResumeThread", 0);
                return -1;
            }
            if (cnt <= 1) break;
        }
    }

    event_win32_context_started(ctx);
    return 0;
}

static int win32_terminate(Context * ctx) {
    LINK * l;
    ContextExtensionWin32 * ext = EXT(ctx);
    DebugState * debug_state = ext->debug_state;

    if (debug_state->reporting_debug_event) {
        debug_state->reporting_debug_event++;
    }

    trace(LOG_CONTEXT, "context: terminating process %#lx, id %s", ctx, ctx->id);
    if (!ctx->exiting) {
        if (!TerminateProcess(ext->handle, 1)) {
            errno = log_error("TerminateProcess", 0);
            return -1;
        }
        ctx->exiting = 1;
        for (l = ctx->children.next; l != &ctx->children; l = l->next) {
            Context * c = cldl2ctxp(l);
            if (!c->stopped) continue;
            c->exiting = 1;
            event_win32_context_started(c);
        }
    }

    return 0;
}

static void add_pending_thread(DebugState * state, DWORD thread) {
    if (state->pending_thrs_cnt >= state->max_pending_thrs_cnt) {
        state->max_pending_thrs_cnt += 10;
        state->pending_thrs = (DWORD *)
        loc_realloc(state->pending_thrs, state->max_pending_thrs_cnt * sizeof(DWORD));
    }
    state->pending_thrs[state->pending_thrs_cnt++] = thread;
}

static void remove_pending_thread(DebugState * state, DWORD thread) {
    unsigned i;
    for (i = 0; i < state->pending_thrs_cnt; i++) {
        if (state->pending_thrs[i] == thread) {
            state->pending_thrs_cnt--;
            for (; i < state->pending_thrs_cnt; i++) {
                state->pending_thrs[i] = state->pending_thrs[i+1];
            }
            break;
        }
    }
}

static Context * add_thread(Context * prs, pid_t pid, DWORD thread, DebugState * state) {
    Context * ctx;
    ContextExtensionWin32 * ext = NULL;
    ext = EXT(ctx = create_context(pid2id(thread, pid)));
    ext->regs = (REG_SET *)loc_alloc_zero(sizeof(REG_SET));
    ext->pid = thread;
    ext->handle = OpenThread(THREAD_ALL_ACCESS, FALSE, thread);
    ext->debug_state = state;
    ctx->mem = prs;
    ctx->big_endian = prs->big_endian;
    ctx->reg_access |= REG_ACCESS_RD_RUNNING;
    (ctx->parent = prs)->ref_count++;
    list_add_last(&ctx->cldl, &prs->children);
    link_context(ctx);
    send_context_created_event(ctx);
    return ctx;
}

static void debug_event_handler(DebugEvent * debug_event) {
    DebugState * debug_state = debug_event->debug_state;
    DEBUG_EVENT * win32_event = &debug_event->win32_event;
    Context * prs = context_find_from_pid(win32_event->dwProcessId, 0);
    Context * ctx = context_find_from_pid(win32_event->dwThreadId, 1);
    ContextExtensionWin32 * ext = NULL;

    assert(ctx == NULL || ctx->parent == prs);

    switch (win32_event->dwDebugEventCode) {
    case CREATE_PROCESS_DEBUG_EVENT:
        if (debug_state->state == DEBUG_STATE_INIT) {
            debug_state->state = DEBUG_STATE_PRS_CREATED;
            debug_state->main_thread_id = win32_event->dwThreadId;
            debug_state->main_thread_handle = win32_event->u.CreateProcessInfo.hThread;
            debug_state->file_handle = win32_event->u.CreateProcessInfo.hFile;
            debug_state->base_address = (uintptr_t)win32_event->u.CreateProcessInfo.lpBaseOfImage;
#if defined(_AMD64_)
            {
                BOOL wow64 = FALSE;
                IsWow64Process(win32_event->u.CreateProcessInfo.hProcess, &wow64);
                debug_state->wow64 = wow64;
            }
#endif
            assert(prs == NULL);
            assert(ctx == NULL);
            ext = EXT(prs = create_context(pid2id(win32_event->dwProcessId, 0)));
            prs->mem = prs;
            prs->mem_access |= MEM_ACCESS_INSTRUCTION;
            prs->mem_access |= MEM_ACCESS_DATA;
            prs->mem_access |= MEM_ACCESS_USER;
            prs->big_endian = big_endian_host();
            ext->pid = win32_event->dwProcessId;
            ext->handle = win32_event->u.CreateProcessInfo.hProcess;
            ext->debug_state = debug_state;
            assert(ext->handle != NULL);
            link_context(prs);
            send_context_created_event(prs);
        }
        else {
            /* This looks like a bug in Windows XP: */
            /* 1. according to the documentation, we should get only one CREATE_PROCESS_DEBUG_EVENT. */
            /* 2. if we don't suspend second process, debugee crashes. */
            assert(debug_state->ini_thread_handle == NULL);
            debug_state->ini_thread_id = win32_event->dwThreadId;
            debug_state->ini_thread_handle = win32_event->u.CreateProcessInfo.hThread;
            SuspendThread(debug_state->ini_thread_handle);
            CloseHandle(win32_event->u.CreateProcessInfo.hFile);
            ResumeThread(debug_state->main_thread_handle);
        }
        break;
    case CREATE_THREAD_DEBUG_EVENT:
        assert(prs != NULL);
        assert(ctx == NULL);
        if (debug_state->break_thread_id == win32_event->dwThreadId) break;
        if (debug_state->state < DEBUG_STATE_PRS_ATTACHED) {
            if (debug_state->ini_thread_handle == NULL) {
                debug_state->ini_thread_id = win32_event->dwThreadId;
                debug_state->ini_thread_handle = win32_event->u.CreateProcessInfo.hThread;
                break;
            }
            add_pending_thread(debug_state, win32_event->dwThreadId);
            break;
        }
        ext = EXT(ctx = add_thread(prs, win32_event->dwProcessId, win32_event->dwThreadId, debug_state));
        debug_event->continue_status = event_win32_context_stopped(ctx);
        if (debug_state->detach) ctx->exiting = 1;
        ext->debug_event = *win32_event;
        break;
    case EXCEPTION_DEBUG_EVENT:
        if (debug_state->state == DEBUG_STATE_PRS_CREATED && (
                win32_event->u.Exception.ExceptionRecord.ExceptionCode == EXCEPTION_BREAKPOINT ||
                win32_event->u.Exception.ExceptionRecord.ExceptionCode == EXCEPTION_WX86_BREAKPOINT)) {
            if (debug_state->ini_thread_handle != NULL) ResumeThread(debug_state->ini_thread_handle);
            debug_state->state = DEBUG_STATE_PRS_ATTACHED;
            ext = EXT(ctx = create_context(pid2id(debug_state->main_thread_id, win32_event->dwProcessId)));
            ext->regs = (REG_SET *)loc_alloc_zero(sizeof(REG_SET));
            ext->pid = debug_state->main_thread_id;
            ext->handle = OpenThread(THREAD_ALL_ACCESS, FALSE, debug_state->main_thread_id);
            ext->debug_state = debug_state;
            ctx->mem = prs;
            ctx->big_endian = prs->big_endian;
            ctx->reg_access |= REG_ACCESS_RD_RUNNING;
            (ctx->parent = prs)->ref_count++;
            list_add_last(&ctx->cldl, &prs->children);
            link_context(ctx);
            send_context_created_event(ctx);
            if ((debug_state->attach_mode & CONTEXT_ATTACH_NO_STOP) == 0) {
                ctx->pending_intercept = 1;
            }
            debug_event->continue_status = event_win32_context_stopped(ctx);
            ext->debug_event = *win32_event;

            if (debug_state->pending_thrs_cnt != 0) {
                unsigned i;
                for (i = 0; i < debug_state->pending_thrs_cnt; i++) {
                    Context * thread;
                    thread = add_thread(prs, win32_event->dwProcessId, debug_state->pending_thrs[i], debug_state);
                    thread->pending_intercept = ctx->pending_intercept;
                    event_win32_context_stopped(thread);
                    EXT(thread)->debug_event = *win32_event;
                }
                debug_state->pending_thrs_cnt = 0;
            }
            if (debug_state->attach_callback != NULL) {
                debug_state->attach_callback(0, prs, debug_state->attach_data);
                debug_state->attach_callback = NULL;
                debug_state->attach_data = NULL;
            }
        }
        else if (ctx == NULL || ctx->exiting) {
            debug_event->continue_status = DBG_EXCEPTION_NOT_HANDLED;
        }
        else {
            assert(prs != NULL);
            assert(!ctx->exited);
            if (ctx->stopped) {
                DWORD exception_code = win32_event->u.Exception.ExceptionRecord.ExceptionCode;
                if (cpu_bp_get_capabilities(context_get_group(ctx, CONTEXT_GROUP_BREAKPOINT)) != 0) {
                    if (exception_code == EXCEPTION_SINGLE_STEP && win32_event->u.Exception.dwFirstChance) {
                        /* This event appears to be caused by a hardware breakpoint.
                         * It is safe to ignore the event - the breakpoint will be triggered again
                         * when the context resumed. */
                        debug_event->continue_status = DBG_CONTINUE;
                        break;
                    }
                }
                trace(LOG_ALWAYS, "context: already stopped, id %s, exception 0x%08x", ctx->id, exception_code);
                debug_event->continue_status = DBG_CONTINUE;
                break;
            }
            ext = EXT(ctx);
            memcpy(&ext->suspend_reason, &win32_event->u.Exception, sizeof(EXCEPTION_DEBUG_INFO));
            debug_event->continue_status = event_win32_context_stopped(ctx);
            ext->debug_event = *win32_event;
        }
        break;
    case EXIT_THREAD_DEBUG_EVENT:
        assert(prs != NULL);
        if (debug_state->pending_thrs_cnt) remove_pending_thread(debug_state, win32_event->dwThreadId);
        if (ctx && !ctx->exited) event_win32_context_exited(ctx, 0);
        if (debug_state->ini_thread_id == win32_event->dwThreadId) {
            debug_state->ini_thread_id = 0;
            debug_state->ini_thread_handle = NULL;
        }
        else if (debug_state->break_thread_id == win32_event->dwThreadId) {
            ext = EXT(prs);
            log_error("CloseHandle", CloseHandle(debug_state->break_thread));
            debug_state->break_thread = NULL;
            debug_state->break_thread_id = 0;
        }
        break;
    case EXIT_PROCESS_DEBUG_EVENT:
        assert(prs != NULL);
        if (ctx && !ctx->exited) event_win32_context_exited(ctx, 0);
        event_win32_context_exited(prs, 0);
        prs = NULL;
        if (debug_state->attach_callback != NULL) {
            int error = set_win32_errno(win32_event->u.ExitProcess.dwExitCode);
            debug_state->attach_callback(error, NULL, debug_state->attach_data);
            debug_state->attach_callback = NULL;
            debug_state->attach_data = NULL;
        }
        break;
    case LOAD_DLL_DEBUG_EVENT:
        assert(prs != NULL);
        debug_state->module_handle = win32_event->u.LoadDll.hFile;
        debug_state->module_address = (uintptr_t)win32_event->u.LoadDll.lpBaseOfDll;
        memory_map_event_module_loaded(prs);
        if (debug_state->module_handle != NULL) {
            log_error("CloseHandle", CloseHandle(debug_state->module_handle));
        }
        debug_state->module_handle = NULL;
        debug_state->module_address = 0;
        break;
    case UNLOAD_DLL_DEBUG_EVENT:
        assert(prs != NULL);
        debug_state->module_address = (uintptr_t)win32_event->u.UnloadDll.lpBaseOfDll;
        memory_map_event_module_unloaded(prs);
        debug_state->module_address = 0;
        break;
    case RIP_EVENT:
        trace(LOG_ALWAYS, "System debugging error: debuggee pid %d, error type %d, error code %d",
            win32_event->dwProcessId, win32_event->u.RipInfo.dwType, win32_event->u.RipInfo.dwError);
        break;
    }
}

static void continue_debug_event(void * args) {
    DebugEvent * debug_event = (DebugEvent *)args;
    DebugState * debug_state = debug_event->debug_state;
    Context * prs = context_find_from_pid(debug_state->process_id, 0);

    assert(debug_state->reporting_debug_event);
    if (debug_state->reporting_debug_event > 1) {
        debug_state->reporting_debug_event = 1;
        post_event(continue_debug_event, debug_event);
        return;
    }

    trace(LOG_WAITPID, "check suspend requests, process ID %u", debug_state->process_id);

    if (prs != NULL && !prs->exited) {
        LINK * l;
        for (l = prs->children.next; l != &prs->children; l = l->next) {
            Context * ctx = cldl2ctxp(l);
            ContextExtensionWin32 * ext = EXT(ctx);
            if (ctx->stopped || ctx->exited) {
                ext->stop_pending = 0;
                ext->start_pending = 0;
                continue;
            }
            if (debug_state->break_thread_id == debug_event->win32_event.dwThreadId &&
                    debug_event->win32_event.dwDebugEventCode == CREATE_THREAD_DEBUG_EVENT) {
                memset(&ext->suspend_reason, 0, sizeof(ext->suspend_reason));
                event_win32_context_stopped(ctx);
                ext->debug_event = debug_event->win32_event;
            }
        }
    }

    trace(LOG_WAITPID, "continue debug event, process ID %u", debug_state->process_id);
    log_error("SetEvent", SetEvent(debug_state->debug_event_inp));
    log_error("WaitForSingleObject", WaitForSingleObject(debug_state->debug_event_out, INFINITE) != WAIT_FAILED);
    debug_state->reporting_debug_event = 0;

    if (prs != NULL && !prs->exited && debug_state->break_thread_id == 0) {
        LINK * l;
        for (l = prs->children.next; l != &prs->children; l = l->next) {
            Context * ctx = cldl2ctxp(l);
            ContextExtensionWin32 * ext = EXT(ctx);
            if (ext->start_pending) {
                for (;;) {
                    DWORD cnt = ResumeThread(ext->handle);
                    if (cnt <= 1) break;
                }
                ext->start_pending = 0;
            }
        }
    }

    log_error("SetEvent", SetEvent(debug_state->debug_event_inp));
}

static void early_debug_event_handler(void * x) {
    DebugEvent * debug_event = (DebugEvent *)x;
    DebugState * debug_state = debug_event->debug_state;
    DEBUG_EVENT * win32_event = &debug_event->win32_event;

    if (win32_event->dwDebugEventCode == EXCEPTION_DEBUG_EVENT) {
        trace(LOG_WAITPID, "%s, process %d, thread %d, code %#lx",
            win32_debug_event_name(win32_event->dwDebugEventCode),
            win32_event->dwProcessId, win32_event->dwThreadId,
            win32_event->u.Exception.ExceptionRecord.ExceptionCode);
    }
    else {
        trace(LOG_WAITPID, "%s, process %d, thread %d",
            win32_debug_event_name(win32_event->dwDebugEventCode),
            win32_event->dwProcessId, win32_event->dwThreadId);
    }

    debug_state->debug_event_generation++;
    debug_state->reporting_debug_event = 1;
    debug_event_handler(debug_event);
    post_event(continue_debug_event, debug_event);
}

static void debugger_detach_handler(void * x) {
    LINK * l = NULL;
    DebugState * debug_state = (DebugState *)x;
    Context * prs = context_find_from_pid(debug_state->process_id, 0);

    assert(debug_state->detach);
    assert(debug_state->break_thread == NULL);
    for (l = prs->children.next; l != &prs->children; l = l->next) {
        Context * ctx = cldl2ctxp(l);
        assert(ctx->exiting);
        if (ctx->stopped) win32_resume(ctx, 0);
    }
    if (prs != NULL && !prs->exited) event_win32_context_exited(prs, 1);

    log_error("SetEvent", SetEvent(debug_state->debug_event_inp));
}

static void debugger_exit_handler(void * x) {
    DebugState * debug_state = (DebugState *)x;
    Context * prs = context_find_from_pid(debug_state->process_id, 0);

    trace(LOG_WAITPID, "debugger thread %d exited, debuggee pid %d", debug_state->debug_thread_id, debug_state->process_id);

    log_error("WaitForSingleObject", WaitForSingleObject(debug_state->debug_thread, INFINITE) != WAIT_FAILED);
    log_error("CloseHandle", CloseHandle(debug_state->debug_thread));
    log_error("CloseHandle", CloseHandle(debug_state->debug_event_inp));
    log_error("CloseHandle", CloseHandle(debug_state->debug_event_out));

    if (prs != NULL && !prs->exited) event_win32_context_exited(prs, 0);

    loc_free(debug_state->pending_thrs);
    loc_free(debug_state);
}

static DWORD WINAPI debugger_thread_func(LPVOID x) {
    DebugState * debug_state = (DebugState *)x;
    DebugEvent debug_event;
    unsigned timeout_cnt = 0;

    if (DebugActiveProcess(debug_state->process_id) == 0) {
        debug_state->error = GetLastError();
        trace(LOG_ALWAYS, "Can't attach to a process: error %d", debug_state->error);
        ReleaseSemaphore(debug_state->debug_thread_semaphore, 1, 0);
        return 0;
    }

    trace(LOG_WAITPID, "debugger thread %d started", GetCurrentThreadId());
    ReleaseSemaphore(debug_state->debug_thread_semaphore, 1, 0);

    memset(&debug_event, 0, sizeof(debug_event));

    debug_event.debug_state = debug_state;

    for (;;) {
        DEBUG_EVENT * win32_event = &debug_event.win32_event;

        memset(win32_event, 0, sizeof(DEBUG_EVENT));
        if (WaitForDebugEvent(win32_event, 400) == 0) {
            /* If we detach with debug events pending,
             * the events will be sent to inferior and it will crash.
             * Wait until no more debug events found. */
            if (debug_state->detach && timeout_cnt >= 5) {
                post_event(debugger_detach_handler, debug_state);
                WaitForSingleObject(debug_state->debug_event_inp, INFINITE);
                if (!DebugActiveProcessStop(debug_state->process_id)) {
                    trace(LOG_ALWAYS, "DebugActiveProcessStop() error %d", GetLastError());
                }
                break;
            }
            if (GetLastError() == ERROR_SEM_TIMEOUT) {
                timeout_cnt++;
                continue;
            }
            trace(LOG_ALWAYS, "WaitForDebugEvent() error %d", GetLastError());
            break;
        }

        timeout_cnt = 0;
        assert(debug_state->process_id == win32_event->dwProcessId);
        debug_event.continue_status = DBG_CONTINUE;

        post_event(early_debug_event_handler, &debug_event);
        WaitForSingleObject(debug_state->debug_event_inp, INFINITE);
        if (ContinueDebugEvent(win32_event->dwProcessId, win32_event->dwThreadId, debug_event.continue_status) == 0) {
            trace(LOG_ALWAYS, "Can't continue debug event: process %d, thread %d: error %d",
                win32_event->dwProcessId, win32_event->dwThreadId, GetLastError());
        }
        SetEvent(debug_state->debug_event_out);
        WaitForSingleObject(debug_state->debug_event_inp, INFINITE);

        if (win32_event->dwDebugEventCode == EXIT_PROCESS_DEBUG_EVENT) break;
        if (win32_event->dwDebugEventCode == RIP_EVENT) break;
    }

    post_event(debugger_exit_handler, debug_state);
    return 0;
}

int context_attach(pid_t pid, ContextAttachCallBack * done, void * data, int mode) {
    int error = 0;
    DebugState * debug_state = (DebugState *)loc_alloc_zero(sizeof(DebugState));

    assert(done != NULL);
    assert((mode & CONTEXT_ATTACH_SELF) == 0);
    debug_state->process_id = pid;
    debug_state->attach_callback = done;
    debug_state->attach_data = data;
    debug_state->attach_mode = mode;

    debug_state->debug_event_inp = CreateEvent(NULL, 0, 0, NULL);
    if (debug_state->debug_event_inp == NULL) error = log_error("CreateEvent", 0);

    if (!error) {
        debug_state->debug_event_out = CreateEvent(NULL, 0, 0, NULL);
        if (debug_state->debug_event_out == NULL) error = log_error("CreateEvent", 0);
    }

    if (!error) {
        debug_state->debug_thread_semaphore = CreateSemaphore(NULL, 0, 1, NULL);
        if (debug_state->debug_thread_semaphore == NULL) error = log_error("CreateSemaphore", 0);
    }

    if (!error) {
        debug_state->debug_thread = CreateThread(NULL, 0, debugger_thread_func, debug_state, 0, &debug_state->debug_thread_id);
        if (debug_state->debug_thread == NULL) error = log_error("CreateThread", 0);
    }

    if (!error) {
        error = log_error("WaitForSingleObject", WaitForSingleObject(debug_state->debug_thread_semaphore, INFINITE) != WAIT_FAILED);
    }

    if (!error) {
        error = log_error("CloseHandle", CloseHandle(debug_state->debug_thread_semaphore));
        debug_state->debug_thread_semaphore = NULL;
    }

#ifndef _WIN64
    if (!error && debug_state->error == 50) {
        error = set_errno(ERR_UNSUPPORTED, "Cannot attach 64-bit proceess with 32-bit agent");
    }
#endif

    if (!error) {
        error = set_win32_errno(debug_state->error);
    }

    if (error) {
        if (debug_state->debug_thread) log_error("WaitForSingleObject", WaitForSingleObject(debug_state->debug_thread, INFINITE) != WAIT_FAILED);
        if (debug_state->debug_thread) log_error("CloseHandle", CloseHandle(debug_state->debug_thread));
        if (debug_state->debug_event_inp) log_error("CloseHandle", CloseHandle(debug_state->debug_event_inp));
        if (debug_state->debug_event_out) log_error("CloseHandle", CloseHandle(debug_state->debug_event_out));
        if (debug_state->debug_thread_semaphore) log_error("CloseHandle", CloseHandle(debug_state->debug_thread_semaphore));
        loc_free(debug_state);
        errno = error;
        return -1;
    }

    add_waitpid_process(pid);
    return 0;
}

int context_has_state(Context * ctx) {
    return ctx != NULL && ctx->parent != NULL;
}

int context_stop(Context * ctx) {
    ContextExtensionWin32 * ext = EXT(ctx);
    DebugState * debug_state = EXT(ctx->parent)->debug_state;

    trace(LOG_CONTEXT, "context:%s suspending ctx %#lx id %s",
        ctx->pending_intercept ? "" : " temporary", ctx, ctx->id);
    assert(context_has_state(ctx));
    assert(!ctx->stopped);
    assert(!ctx->exited);
    if (debug_state->reporting_debug_event) {
        debug_state->reporting_debug_event++;
    }
    else if (!debug_state->break_posted) {
        post_break_process_event(ctx->parent);
    }
    ext->stop_pending = 1;
    return 0;
}

int context_continue(Context * ctx) {
    assert(is_dispatch_thread());
    assert(context_has_state(ctx));
    assert(ctx->stopped);
    assert(!ctx->exited);

    trace(LOG_CONTEXT, "context: resuming ctx %#lx, id %s", ctx, ctx->id);
    return win32_resume(ctx, 0);
}

int context_single_step(Context * ctx) {
    assert(is_dispatch_thread());
    assert(context_has_state(ctx));
    assert(ctx->stopped);
    assert(!ctx->exited);

    trace(LOG_CONTEXT, "context: single step ctx %#lx, id %s", ctx, ctx->id);
    return win32_resume(ctx, 1);
}

static int context_terminate(Context * ctx) {
    assert(is_dispatch_thread());
    assert(!context_has_state(ctx));
    assert(!ctx->exited);

    trace(LOG_CONTEXT, "context: terminate ctx %#lx, id %s", ctx, ctx->id);
    return win32_terminate(ctx);
}

static int context_detach(Context * ctx) {
    LINK * l;
    ContextExtensionWin32 * ext = EXT(ctx);
    DebugState * debug_state = ext->debug_state;
    assert(ctx->parent == NULL);
    trace(LOG_CONTEXT, "context: detach ctx %#lx id %s", ctx, ctx->id);
    debug_state->detach = 1;
    unplant_breakpoints(ctx);
    ctx->exiting = 1;
    for (l = ctx->children.next; l != &ctx->children; l = l->next) {
        Context * c = cldl2ctxp(l);
        if (!c->exited) c->exiting = 1;
    }
    return 0;
}

int context_resume(Context * ctx, int mode, ContextAddress range_start, ContextAddress range_end) {
    switch (mode) {
    case RM_RESUME:
        return context_continue(ctx);
    case RM_STEP_INTO:
        return context_single_step(ctx);
    case RM_TERMINATE:
        return context_terminate(ctx);
    case RM_DETACH:
        return context_detach(ctx);
    }
    errno = ERR_UNSUPPORTED;
    return -1;
}

int context_can_resume(Context * ctx, int mode) {
    switch (mode) {
    case RM_RESUME:
        return 1;
    case RM_STEP_INTO:
        return context_has_state(ctx);
    case RM_TERMINATE:
    case RM_DETACH:
        return ctx != NULL && ctx->parent == NULL;
    }
    return 0;
}

int context_read_mem(Context * ctx, ContextAddress address, void * buf, size_t size) {
    ContextExtensionWin32 * ext = EXT(ctx = ctx->mem);
    SIZE_T bcnt = 0;

    trace(LOG_CONTEXT,
        "context: read memory ctx %#lx, id %s, address %#lx, size %d",
        ctx, ctx->id, address, (int)size);
    assert(is_dispatch_thread());
    mem_err_info.error = 0;
    if (ReadProcessMemory(ext->handle, (LPCVOID)address, buf, size, &bcnt) == 0 || bcnt != size) {
        DWORD error = GetLastError();
        size_t size_error = 1;
        if (error == 0x3e6 || bcnt >= size) {
            /* Bug in Windows 7: invalid bcnt */
            bcnt = 0;
        }
        if (size > 1) {
            size_t size_next = size;
            /* Check if a smaller block is readable */
            while (bcnt == 0) {
                if (size_next <= 1) break;
                size_next /= 2;
                if (ReadProcessMemory(ext->handle,
                    (LPCVOID)address, buf, size_next, NULL)) bcnt = size_next;
            }
            /* Find upper bound of the readable memory */
            while (bcnt < size) {
                if (!ReadProcessMemory(ext->handle, (LPCVOID)(address + bcnt),
                        (char *)buf + bcnt, 1, NULL)) {
                    error = GetLastError();
                    break;
                }
                bcnt++;
            }
        }
        if (check_breakpoints_on_memory_read(ctx, address, buf, bcnt) < 0) return -1;
        /* Find number of unreadable bytes */
        while (size_error < 0x100 && bcnt + size_error < size) {
            if (ReadProcessMemory(ext->handle, (LPCVOID)(address + bcnt + size_error),
                    (char *)buf + bcnt + size_error, 1, NULL)) break;
            if (error != GetLastError()) break;
            size_error++;
        }
        mem_err_info.error = set_win32_errno(error);
        mem_err_info.size_valid = bcnt;
        mem_err_info.size_error = size_error;
        return -1;
    }
    return check_breakpoints_on_memory_read(ctx, address, buf, size);
}

int context_write_mem(Context * ctx, ContextAddress address, void * buf, size_t size) {
    ContextExtensionWin32 * ext = EXT(ctx = ctx->mem);
    SIZE_T bcnt = 0;

    trace(LOG_CONTEXT,
        "context: write memory ctx %#lx, id %s, address %#lx, size %d",
        ctx, ctx->id, address, (int)size);
    assert(is_dispatch_thread());
    mem_err_info.error = 0;
    if (check_breakpoints_on_memory_write(ctx, address, buf, size) < 0) return -1;
    if (WriteProcessMemory(ext->handle, (LPVOID)address, buf, size, &bcnt) == 0 || bcnt != size) {
        mem_err_info.error = set_win32_errno(GetLastError());
        mem_err_info.size_valid = bcnt;
        mem_err_info.size_error = 1;
    }
    if (FlushInstructionCache(ext->handle, (LPCVOID)address, bcnt) == 0) {
        mem_err_info.error = 0;
        errno = log_error("FlushInstructionCache", 0);
        return -1;
    }
    if (mem_err_info.error) {
        errno = mem_err_info.error;
        return -1;
    }
    return 0;
}

#if ENABLE_ExtendedMemoryErrorReports
int context_get_mem_error_info(MemoryErrorInfo * info) {
    if (mem_err_info.error == 0) {
        set_errno(ERR_OTHER, "Extended memory error info not available");
        return -1;
    }
    *info = mem_err_info;
    return 0;
}
#endif

int context_write_reg(Context * ctx, RegisterDefinition * def, unsigned offs, unsigned size, void * buf) {
    ContextExtensionWin32 * ext = EXT(ctx);

    assert(is_dispatch_thread());
    assert(offs + size <= def->size);

    get_registers(ctx);
    if (ext->regs_error) {
        set_error_report_errno(ext->regs_error);
        return -1;
    }
    if (memcmp((uint8_t *)ext->regs + def->offset + offs, buf, size) == 0) return 0;
    memcpy((uint8_t *)ext->regs + def->offset + offs, buf, size);
    ext->regs_dirty = 1;
    return 0;
}

int context_read_reg(Context * ctx, RegisterDefinition * def, unsigned offs, unsigned size, void * buf) {
    ContextExtensionWin32 * ext = EXT(ctx);

    assert(is_dispatch_thread());
    assert(offs + size <= def->size);

    get_registers(ctx);
    if (ext->regs_error) {
        set_error_report_errno(ext->regs_error);
        return -1;
    }
    memcpy(buf, (uint8_t *)ext->regs + def->offset + offs, size);
    return 0;
}

unsigned context_word_size(Context * ctx) {
    ContextExtensionWin32 * ext = EXT(ctx->mem);
    if (ext->debug_state->wow64) return 4;
    return sizeof(void *);
}

int context_get_canonical_addr(Context * ctx, ContextAddress addr,
        Context ** canonical_ctx, ContextAddress * canonical_addr,
        ContextAddress * block_addr, ContextAddress * block_size) {
    /* Direct mapping, page size is irrelevant */
    ContextAddress page_size = 0x100000;
    assert(is_dispatch_thread());
    *canonical_ctx = ctx->mem;
    if (canonical_addr != NULL) *canonical_addr = addr;
    if (block_addr != NULL) *block_addr = addr & ~(page_size - 1);
    if (block_size != NULL) *block_size = page_size;
    return 0;
}

Context * context_get_group(Context * ctx, int group) {
    static Context * cpu_group = NULL;
    switch (group) {
    case CONTEXT_GROUP_INTERCEPT:
        return ctx;
    case CONTEXT_GROUP_CPU:
        if (cpu_group == NULL) {
            cpu_group = create_context("CPU");
            ini_cpu_disassembler(cpu_group);
        }
        return cpu_group;
    }
    return ctx->mem;
}

int context_get_supported_bp_access_types(Context * ctx) {
    return cpu_bp_get_capabilities(ctx);
}

int context_plant_breakpoint(ContextBreakpoint * bp) {
    DebugState * debug_state = EXT(bp->ctx->mem)->debug_state;
    if (debug_state->ok_to_use_hw_bp) return cpu_bp_plant(bp);
    errno = ERR_UNSUPPORTED;
    return -1;
}

int context_unplant_breakpoint(ContextBreakpoint * bp) {
    return cpu_bp_remove(bp);
}

static void add_map_region(MemoryMap * map, DWORD64 addr, ULONG size, char * file) {
    MemoryRegion * r = NULL;
    if (map->region_cnt >= map->region_max) {
        map->region_max += 8;
        map->regions = (MemoryRegion *)loc_realloc(map->regions, sizeof(MemoryRegion) * map->region_max);
    }
    r = map->regions + map->region_cnt++;
    memset(r, 0, sizeof(MemoryRegion));
    r->addr = (ContextAddress)addr;
    r->size = (ContextAddress)size;
    r->file_name = loc_strdup(file);
}

static void add_module_info(MemoryMap * map, PCWSTR ModuleName, DWORD64 ModuleBase, ULONG ModuleSize) {
    static char * fnm_buf = NULL;
    static int fnm_max = 0;
    int fnm_len = 0;
    int fnm_err = 0;

    if (fnm_buf == NULL) {
        fnm_max = 256;
        fnm_buf = (char *)loc_alloc(fnm_max);
    }
    for (;;) {
        fnm_len = WideCharToMultiByte(CP_UTF8, 0, ModuleName, -1, fnm_buf, fnm_max - 1, NULL, NULL);
        if (fnm_len != 0) break;
        fnm_err = GetLastError();
        if (fnm_err != ERROR_INSUFFICIENT_BUFFER) {
            set_win32_errno(fnm_err);
            trace(LOG_ALWAYS, "Can't get module name: %s", errno_to_str(errno));
            return;
        }
        fnm_max *= 2;
        fnm_buf = (char *)loc_realloc(fnm_buf, fnm_max);
    }
    fnm_buf[fnm_len] = 0;

    add_map_region(map, ModuleBase, ModuleSize, fnm_buf);
}

int context_get_memory_map(Context * ctx, MemoryMap * map) {
    DWORD mods_len = 0;
    DWORD mods_max = 0x1000;
    HMODULE * mods = (HMODULE *)tmp_alloc(mods_max);
    ContextExtensionWin32 * ext = NULL;
    unsigned i;

    ctx = ctx->mem;
    assert(!ctx->exited);
    ext = EXT(ctx);
    for (;;) {
        if (!EnumProcessModules(ext->handle, mods, mods_max, &mods_len)) {
            set_win32_errno(GetLastError());
            return -1;
        }
        if (mods_len <= mods_max) break;
        mods_max *= 2;
        mods = (HMODULE *)tmp_realloc(mods, mods_max);
    }
    for (i = 0; i < mods_len / sizeof(HMODULE); i++) {
        MODULEINFO info;
        WCHAR name[MAX_PATH];
        if (!GetModuleFileNameExW(ext->handle, mods[i], name, sizeof(name) / sizeof(WCHAR))) {
            set_win32_errno(GetLastError());
            return -1;
        }
        memset(&info, 0, sizeof(info));
        if (!GetModuleInformation(ext->handle, mods[i], &info, sizeof(info))) {
            set_win32_errno(GetLastError());
            return -1;
        }
        add_module_info(map, name, (uintptr_t)info.lpBaseOfDll, info.SizeOfImage);
    }
    return 0;
}

#if ENABLE_ContextBreakpointCapabilities
int context_get_breakpoint_capabilities(Context * ctx, const char *** names, const char *** values, int * cnt) {
    static const char * n[1];
    static const char * v[1];
    n[0] = "MaxHardwareBreakpoints";
    v[0] = "4";
    *names = n;
    *values = v;
    *cnt = 1;
    return 0;
}
#endif

#if ENABLE_ExtendedBreakpointStatus
int context_get_breakpoint_status(ContextBreakpoint * bp, const char *** names, const char *** values, int * cnt) {
    static const char * n[1];
    static const char * v[1];
    char * tmp = (char *)tmp_alloc(32);
    snprintf(tmp, 32, "\"dr%u\"", bp->id);
    n[0] = "Register";
    v[0] = tmp;
    *names = n;
    *values = v;
    *cnt = 1;
    return 0;
}
#endif

#if ENABLE_ContextISA
int context_get_isa(Context * ctx, ContextAddress addr, ContextISA * isa) {
    ContextExtensionWin32 * ext = EXT(ctx->mem);
    memset(isa, 0, sizeof(ContextISA));
    isa->max_instruction_size = 15;
    if (ext->debug_state->wow64) {
        isa->def = "386";
    }
    else {
#if defined(_M_IX86)
        isa->def = "386";
#elif defined(_M_AMD64)
        isa->def = "X86_64";
#else
        isa->def = NULL;
#endif
    }
#if SERVICE_Symbols
    if (get_context_isa(ctx, addr, &isa->isa, &isa->addr, &isa->size) < 0) return -1;
#endif
    return 0;
}
#endif

#if ENABLE_ContextMemoryProperties
int context_get_memory_properties(Context * ctx, const char *** names, const char *** values, int * cnt) {
    static const char * prop_names[] = { "AddressableUnitSize", "DefaultWordSize" };
    static const char * prop_values[] = { "1", "4" };
    *names = prop_names;
    *values = prop_values;
    *cnt = 2;
    return 0;
}
#endif

#if ENABLE_ContextExtraProperties
int context_get_extra_properties(Context * ctx, const char *** names, const char *** values, int * cnt) {
    *cnt = 0;
    return 0;
}
#endif

HANDLE get_context_handle(Context * ctx) {
    ContextExtensionWin32 * ext = EXT(ctx);
    return ext->handle;
}

HANDLE get_context_file_handle(Context * ctx) {
    ContextExtensionWin32 * ext = EXT(ctx);
    return ext->debug_state->file_handle;
}

DWORD64 get_context_base_address(Context * ctx) {
    ContextExtensionWin32 * ext = EXT(ctx);
    return ext->debug_state->base_address;
}

HANDLE get_context_module_handle(Context * ctx) {
    ContextExtensionWin32 * ext = EXT(ctx);
    return ext->debug_state->module_handle;
}

DWORD64 get_context_module_address(Context * ctx) {
    ContextExtensionWin32 * ext = EXT(ctx);
    return ext->debug_state->module_address;
}

void add_context_exception_handler(ContextExceptionHandler * h) {
    assert(exception_handler_cnt < MAX_EXCEPTION_HANDLERS);
    exception_handlers[exception_handler_cnt++] = h;
}

static void eventpoint_at_main(Context * ctx, void * args) {
    DebugState * debug_state = EXT(ctx->mem)->debug_state;
    if ((debug_state->attach_mode & CONTEXT_ATTACH_NO_MAIN) == 0) {
        suspend_debug_context(ctx);
    }
}

static void waitpid_listener(int pid, int exited, int exit_code, int signal, int event_code, int syscall, void * args) {
}

void init_contexts_sys_dep(void) {
    context_extension_offset = context_extension(sizeof(ContextExtensionWin32));
    ini_context_pid_hash();
    add_waitpid_listener(waitpid_listener, NULL);
    memset(&os_version, 0, sizeof(os_version));
    os_version.dwOSVersionInfoSize = sizeof(os_version);
    GetVersionEx((OSVERSIONINFO *)&os_version);
    create_eventpoint("main", NULL, eventpoint_at_main, NULL);
}

#endif  /* if ENABLE_DebugContext */
#endif /* defined(_WIN32) || defined(__CYGWIN__) */
