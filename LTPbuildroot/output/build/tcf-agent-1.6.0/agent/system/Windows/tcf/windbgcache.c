/*******************************************************************************
 * Copyright (c) 2008, 2013 Wind River Systems, Inc. and others.
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
 * This module provides access to Windows Portable Executable debug information.
 * Current implementation delegates all its job to DBGHELP.DLL.
 */

#include <tcf/config.h>

#if ENABLE_PE
#  define ENABLE_EnumerateModules (SERVICE_MemoryMap && !ENABLE_ContextProxy)
#else
#  define ENABLE_EnumerateModules 0
#endif

#if ENABLE_PE

#include <assert.h>
#include <stdio.h>
#include <wchar.h>
#include <system/Windows/tcf/windbgcache.h>
#include <system/Windows/tcf/context-win32.h>
#include <tcf/framework/trace.h>
#include <tcf/framework/myalloc.h>
#include <tcf/services/memorymap.h>

/* Require that the user install a later dbghelp API that has all the required features */
#if API_VERSION_NUMBER <= 9
#  error "The dbghelp.h API version must be greater than 9. Install the latest version at \
http://www.microsoft.com/whdc/devtools/debugging/default.mspx \
and rebuild."
#endif

static HINSTANCE dbghelp_dll = NULL;

static wchar_t * pathes[] = {
    L"%\\Microsoft Visual Studio 10.0\\Common7\\IDE\\dbghelp.dll",
    L"%\\Microsoft Visual Studio 9.0\\Common7\\IDE\\dbghelp.dll",
    L"%\\Debugging Tools for Windows (x86)\\dbghelp.dll",
    L"%\\Debugging Tools for Windows\\dbghelp.dll",
    L".\\dbghelp.dll",
    L"dbghelp.dll",
    NULL
};

#if ENABLE_PE

static void event_context_created(Context * ctx, void * client_data) {
    HANDLE handle = NULL;
    WCHAR fnm[_MAX_PATH];
    DWORD w = 0;

    if (ctx->parent != NULL) return;
    handle = get_context_handle(ctx);
    assert(handle != NULL);
    assert(ctx->mem == ctx);

    w = GetModuleFileNameW(NULL, fnm, _MAX_PATH);
    while (w > 0 && fnm[w] != '\\') w--;
    fnm[w] = 0;

    /* Symbol search path could contain "http://msdl.microsoft.com/download/symbols",
       but access to Microsoft debug info server is too slow,
       and dbghelp.dll caching is inadequate
    */

    /* Note: SymInitializeW(..., ..., TRUE) does not work on Windows 7 */
    if (!SymInitializeW(handle, fnm, FALSE)) {
        set_win32_errno(GetLastError());
        trace(LOG_ALWAYS, "SymInitialize() error: %s", errno_to_str(errno));
    }
    if (!SymLoadModule64(handle, get_context_file_handle(ctx),
            NULL, NULL, get_context_base_address(ctx), 0)) {
        set_win32_errno(GetLastError());
        trace(LOG_ALWAYS, "SymLoadModule64() error: %s", errno_to_str(errno));
    }
}

static void event_context_exited(Context * ctx, void * client_data) {
    HANDLE handle = NULL;
    if (ctx->parent != NULL) return;
    handle = get_context_handle(ctx);
    assert(handle != NULL);
    assert(ctx->mem == ctx);
    if (!SymUnloadModule64(handle, get_context_base_address(ctx))) {
        set_win32_errno(GetLastError());
        trace(LOG_ALWAYS, "SymUnloadModule64(0x%Ix,0x%I64x) (context exit) error: %s",
            handle, get_context_base_address(ctx), errno_to_str(errno));
    }
    if (!SymCleanup(handle)) {
        set_win32_errno(GetLastError());
        trace(LOG_ALWAYS, "SymCleanup() error: %s", errno_to_str(errno));
    }
}

static void event_module_loaded(Context * ctx, void * client_data) {
    HANDLE handle = get_context_handle(ctx);
    assert(handle != NULL);
    assert(ctx->mem == ctx);
    if (!SymLoadModule64(handle, get_context_module_handle(ctx),
            NULL, NULL, get_context_module_address(ctx), 0)) {
        set_win32_errno(GetLastError());
        trace(LOG_ALWAYS, "SymLoadModule64() error: %s", errno_to_str(errno));
    }
}

static void event_module_unloaded(Context * ctx, void * client_data) {
    HANDLE handle = get_context_handle(ctx);
    assert(handle != NULL);
    assert(ctx->mem == ctx);
    if (!SymUnloadModule64(handle, get_context_module_address(ctx))) {
#if ENABLE_Trace
        DWORD err = GetLastError();
        /* Workaround:
         * On Windows 7 first few UNLOAD_DLL_DEBUG_EVENT come without matching LOAD_DLL_DEBUG_EVENT,
         * SymUnloadModule64() returns error 0x57 "The parameter is incorrect" for such events.
         * No proper fix is found for this issue. */
        if (err != 0 && err != 0x57) {
            set_win32_errno(err);
            trace(LOG_ALWAYS, "SymUnloadModule64(0x%Ix,0x%I64x) (unload DLL) error: 0x%08I32x %s",
                handle, get_context_module_address(ctx), err, errno_to_str(errno));
        }
#endif
    }
}

static ContextEventListener ctx_listener = {
    event_context_created,
    event_context_exited,
};

static MemoryMapEventListener map_listener = {
    event_module_loaded,
    NULL,
    event_module_unloaded
};

#endif

static void CheckDLLVersion(void) {
    DWORD handle = 0;
    WCHAR fnm[_MAX_PATH];
    BYTE * version_info = NULL;
    DWORD size = GetModuleFileNameW(dbghelp_dll, fnm, _MAX_PATH);
    fnm[size] = 0;
    size = GetFileVersionInfoSizeW(fnm, &handle);
    version_info = (BYTE *)loc_alloc_zero(size);
    if (!GetFileVersionInfoW(fnm, handle, size, version_info)) {
        set_win32_errno(GetLastError());
        trace(LOG_ALWAYS, "Cannot get DBGHELP.DLL version info: %s", errno_to_str(errno));
    }
    else {
        UINT vsfi_len = 0;
        VS_FIXEDFILEINFO * vsfi = NULL;
        VerQueryValueW(version_info, L"\\", (void**)&vsfi, &vsfi_len);
        if (HIWORD(vsfi->dwFileVersionMS) < 6 || HIWORD(vsfi->dwFileVersionMS) == 6 && LOWORD(vsfi->dwFileVersionMS) < 9) {
            char path[_MAX_PATH * 2];
            trace(LOG_ALWAYS, "DBGHELP.DLL version is less then 6.9 - debug services might not work properly");
            if (WideCharToMultiByte(CP_UTF8, 0, fnm, -1, path, sizeof(path), NULL, NULL)) {
                trace(LOG_ALWAYS, "%s", path);
            }
            trace(LOG_ALWAYS, "DBGHELP.DLL version %d.%d.%d.%d",
                HIWORD(vsfi->dwFileVersionMS), LOWORD(vsfi->dwFileVersionMS),
                HIWORD(vsfi->dwFileVersionLS), LOWORD(vsfi->dwFileVersionLS));
        }
    }
    loc_free(version_info);
}

static FARPROC GetProc(char * name) {
    if (dbghelp_dll == NULL) {
        wchar_t ** p = pathes;
        while (dbghelp_dll == NULL && *p != NULL) {
            if (**p == '%') {
                HKEY key;
                if (RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                        L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion",
                        0, KEY_READ, &key) == ERROR_SUCCESS) {
                    wchar_t buf[FILE_PATH_SIZE];
                    DWORD size = sizeof(buf);
                    memset(buf, 0, sizeof(buf));
                    if (RegQueryValueExW(key,
                            L"ProgramFilesDir (x86)",
                            NULL, NULL, (LPBYTE)buf, &size) == ERROR_SUCCESS) {
                        wcsncat(buf, *p + 1, FILE_PATH_SIZE - size / sizeof(wchar_t));
                        dbghelp_dll = LoadLibraryW(buf);
                    }
                    if (dbghelp_dll == NULL) {
                        size = sizeof(buf);
                        memset(buf, 0, sizeof(buf));
                        if (RegQueryValueExW(key,
                                L"ProgramFilesDir",
                                NULL, NULL, (LPBYTE)buf, &size) == ERROR_SUCCESS) {
                            wcsncat(buf, *p + 1, FILE_PATH_SIZE - size / sizeof(wchar_t));
                            dbghelp_dll = LoadLibraryW(buf);
                        }
                    }
                    RegCloseKey(key);
                }
            }
            else {
                dbghelp_dll = LoadLibraryW(*p);
            }
            p++;
        }
        if (dbghelp_dll == NULL) {
            assert(GetLastError() != 0);
            return NULL;
        }
        CheckDLLVersion();
#if ENABLE_PE
        add_context_event_listener(&ctx_listener, NULL);
        add_memory_map_event_listener(&map_listener, NULL);
#endif
    }
    return GetProcAddress(dbghelp_dll, name);
}

#endif

#if ENABLE_PE

BOOL SymInitializeW(HANDLE hProcess, PCWSTR UserSearchPath, BOOL fInvadeProcess) {
    typedef BOOL (FAR WINAPI * ProcType)(HANDLE, PCWSTR, BOOL);
    static ProcType proc = NULL;
    if (proc == NULL) {
        proc = (ProcType)GetProc("SymInitializeW");
        if (proc == NULL) return 0;
    }
    return proc(hProcess, UserSearchPath, fInvadeProcess);
}

DWORD SymGetOptions(void) {
    typedef DWORD (FAR WINAPI * ProcType)(void);
    static ProcType proc = NULL;
    if (proc == NULL) {
        proc = (ProcType)GetProc("SymGetOptions");
        if (proc == NULL) return 0;
    }
    return proc();
}

BOOL SymSetOptions(DWORD Options) {
    typedef BOOL (FAR WINAPI * ProcType)(DWORD);
    static ProcType proc = NULL;
    if (proc == NULL) {
        proc = (ProcType)GetProc("SymSetOptions");
        if (proc == NULL) return 0;
    }
    return proc(Options);
}

BOOL SymGetLineFromName64(HANDLE hProcess, PCSTR ModuleName, PCSTR FileName, DWORD dwLineNumber, PLONG plDisplacement, PIMAGEHLP_LINE64 Line) {
    typedef BOOL (FAR WINAPI * ProcType)(HANDLE, PCSTR, PCSTR, DWORD, PLONG, PIMAGEHLP_LINE64);
    static ProcType proc = NULL;
    if (proc == NULL) {
        proc = (ProcType)GetProc("SymGetLineFromName64");
        if (proc == NULL) return 0;
    }
    return proc(hProcess, ModuleName, FileName, dwLineNumber, plDisplacement, Line);
}

BOOL SymGetLineFromAddr64(HANDLE hProcess, DWORD64 dwAddr, PDWORD pdwDisplacement, PIMAGEHLP_LINE64 Line) {
    typedef BOOL (FAR WINAPI * ProcType)(HANDLE, DWORD64, PDWORD, PIMAGEHLP_LINE64);
    static ProcType proc = NULL;
    if (proc == NULL) {
        proc = (ProcType)GetProc("SymGetLineFromAddr64");
        if (proc == NULL) return 0;
    }
    return proc(hProcess, dwAddr, pdwDisplacement, Line);
}

BOOL SymGetLineNext64(HANDLE hProcess, PIMAGEHLP_LINE64 Line) {
    typedef BOOL (FAR WINAPI * ProcType)(HANDLE, PIMAGEHLP_LINE64);
    static ProcType proc = NULL;
    if (proc == NULL) {
        proc = (ProcType)GetProc("SymGetLineNext64");
        if (proc == NULL) return 0;
    }
    assert(Line != NULL);
    assert(Line->Address != 0);
    return proc(hProcess, Line);
}

BOOL SymGetTypeInfo(HANDLE hProcess, DWORD64 ModBase, ULONG TypeId, IMAGEHLP_SYMBOL_TYPE_INFO GetType, PVOID pInfo) {
    typedef BOOL (FAR WINAPI * ProcType)(HANDLE, DWORD64, ULONG, IMAGEHLP_SYMBOL_TYPE_INFO, PVOID);
    static ProcType proc = NULL;
    if (proc == NULL) {
        proc = (ProcType)GetProc("SymGetTypeInfo");
        if (proc == NULL) return 0;
    }
    return proc(hProcess, ModBase, TypeId, GetType, pInfo);
}

BOOL SymFromIndex(HANDLE hProcess, ULONG64 BaseOfDll, DWORD Index, PSYMBOL_INFO Symbol) {
    typedef BOOL (FAR WINAPI * ProcType)(HANDLE, ULONG64, DWORD, PSYMBOL_INFO);
    static ProcType proc = NULL;
    if (proc == NULL) {
        proc = (ProcType)GetProc("SymFromIndex");
        if (proc == NULL) return 0;
    }
    return proc(hProcess, BaseOfDll, Index, Symbol);
}

BOOL SymFromAddr(HANDLE hProcess, DWORD64 Address, PDWORD64 Displacement, PSYMBOL_INFO Symbol) {
    typedef BOOL (FAR WINAPI * ProcType)(HANDLE, DWORD64, PDWORD64, PSYMBOL_INFO);
    static ProcType proc = NULL;
    if (proc == NULL) {
        proc = (ProcType)GetProc("SymFromAddr");
        if (proc == NULL) return 0;
    }
    return proc(hProcess, Address, Displacement, Symbol);
}

BOOL SymSetContext(HANDLE hProcess, PIMAGEHLP_STACK_FRAME StackFrame, PIMAGEHLP_CONTEXT Context) {
    typedef BOOL (FAR WINAPI * ProcType)(HANDLE, PIMAGEHLP_STACK_FRAME, PIMAGEHLP_CONTEXT);
    static ProcType proc = NULL;
    if (proc == NULL) {
        proc = (ProcType)GetProc("SymSetContext");
        if (proc == NULL) return 0;
    }
    return proc(hProcess, StackFrame, Context);
}

BOOL SymFromName(HANDLE hProcess, PCSTR Name, PSYMBOL_INFO Symbol) {
    typedef BOOL (FAR WINAPI * ProcType)(HANDLE, PCSTR, PSYMBOL_INFO);
    static ProcType proc = NULL;
    if (proc == NULL) {
        proc = (ProcType)GetProc("SymFromName");
        if (proc == NULL) return 0;
    }
    return proc(hProcess, Name, Symbol);
}

BOOL SymEnumSymbols(HANDLE hProcess, ULONG64 BaseOfDll, PCSTR Mask, PSYM_ENUMERATESYMBOLS_CALLBACK EnumSymbolsCallback, PVOID UserContext) {
    typedef BOOL (FAR WINAPI * ProcType)(HANDLE, ULONG64, PCSTR, PSYM_ENUMERATESYMBOLS_CALLBACK, PVOID);
    static ProcType proc = NULL;
    if (proc == NULL) {
        proc = (ProcType)GetProc("SymEnumSymbols");
        if (proc == NULL) return 0;
    }
    return proc(hProcess, BaseOfDll, Mask, EnumSymbolsCallback, UserContext);
}

BOOL SymGetTypeFromName(HANDLE hProcess, ULONG64 BaseOfDll, PCSTR Name, PSYMBOL_INFO Symbol) {
    typedef BOOL (FAR WINAPI * ProcType)(HANDLE, ULONG64, PCSTR, PSYMBOL_INFO);
    static ProcType proc = NULL;
    if (proc == NULL) {
        proc = (ProcType)GetProc("SymGetTypeFromName");
        if (proc == NULL) return 0;
    }
    return proc(hProcess, BaseOfDll, Name, Symbol);
}

DWORD64 SymGetModuleBase64(HANDLE hProcess, ULONG64 Address) {
    typedef DWORD64 (FAR WINAPI * ProcType)(HANDLE, ULONG64);
    static ProcType proc = NULL;
    if (proc == NULL) {
        proc = (ProcType)GetProc("SymGetModuleBase64");
        if (proc == NULL) return 0;
    }
    return proc(hProcess, Address);
}

BOOL SymLoadModule64(HANDLE hProcess, HANDLE hFile, PCSTR ImageName, PCSTR ModuleName, DWORD64 BaseOfDll, DWORD SizeOfDll) {
    typedef BOOL (FAR WINAPI * ProcType)(HANDLE, HANDLE, PCSTR, PCSTR, DWORD64, DWORD);
    static ProcType proc = NULL;
    if (proc == NULL) {
        proc = (ProcType)GetProc("SymLoadModule64");
        if (proc == NULL) return 0;
    }
    return proc(hProcess, hFile, ImageName, ModuleName, BaseOfDll, SizeOfDll);
}

BOOL SymUnloadModule64(HANDLE hProcess, DWORD64 BaseOfDll) {
    typedef BOOL (FAR WINAPI * ProcType)(HANDLE, DWORD64);
    static ProcType proc = NULL;
    if (proc == NULL) {
        proc = (ProcType)GetProc("SymUnloadModule64");
        if (proc == NULL) return 0;
    }
    return proc(hProcess, BaseOfDll);
}

BOOL SymGetModuleInfoW64(HANDLE hProcess, DWORD64 Addr, PIMAGEHLP_MODULEW64 ModuleInfo) {
    typedef BOOL (FAR WINAPI * ProcType)(HANDLE, DWORD64, PIMAGEHLP_MODULEW64);
    static ProcType proc = NULL;
    if (proc == NULL) {
        proc = (ProcType)GetProc("SymGetModuleInfoW64");
        if (proc == NULL) return 0;
    }
    return proc(hProcess, Addr, ModuleInfo);
}

BOOL SymCleanup(HANDLE hProcess) {
    typedef BOOL (FAR WINAPI * ProcType)(HANDLE);
    static ProcType proc = NULL;
    if (proc == NULL) {
        proc = (ProcType)GetProc("SymCleanup");
        if (proc == NULL) return 0;
    }
    return proc(hProcess);
}

#endif

#if ENABLE_EnumerateModules

BOOL LocEnumerateLoadedModulesW64(HANDLE hProcess, PENUMLOADED_MODULES_CALLBACKW64 Callback, PVOID UserContext) {
    typedef BOOL (FAR WINAPI * ProcType)(HANDLE, PENUMLOADED_MODULES_CALLBACKW64, PVOID);
    static ProcType proc = NULL;
    if (proc == NULL) {
        proc = (ProcType)GetProc("EnumerateLoadedModulesW64");
        if (proc == NULL) return 0;
    }
    return proc(hProcess, Callback, UserContext);
}

#endif
