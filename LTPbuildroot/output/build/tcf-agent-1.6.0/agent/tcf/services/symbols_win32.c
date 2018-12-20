/*******************************************************************************
 * Copyright (c) 2007, 2017 Wind River Systems, Inc. and others.
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
 * Symbols service - Windows version
 */

#include <tcf/config.h>

#if SERVICE_Symbols && (!ENABLE_SymbolsProxy || ENABLE_LineNumbersMux) && ENABLE_PE

#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <tcf/framework/errors.h>
#include <tcf/framework/events.h>
#include <tcf/framework/myalloc.h>
#include <tcf/framework/trace.h>
#include <tcf/services/symbols.h>
#include <tcf/services/stacktrace.h>
#include <tcf/services/memorymap.h>
#include <tcf/services/funccall.h>
#include <system/Windows/tcf/windbgcache.h>
#include <system/Windows/tcf/context-win32.h>
#if ENABLE_SymbolsMux
#define SYM_READER_PREFIX win32_reader_
#include <tcf/services/symbols_mux.h>
#endif

#ifndef MAX_SYM_NAME
#  define MAX_SYM_NAME 2000
#endif

typedef struct TypeInfo {
    char * name;
    unsigned char size;
    unsigned char sign;
    unsigned char real;
} TypeInfo;

static const TypeInfo basic_type_info[] = {
    { "void",                   0,                  0, 0 },
    { "char",                   sizeof(char),       1, 0 },
    { "unsigned char",          sizeof(char),       0, 0 },
    { "signed char",            sizeof(char),       1, 0 },
    { "short",                  sizeof(short),      1, 0 },
    { "unsigned short",         sizeof(short),      0, 0 },
    { "signed short",           sizeof(short),      1, 0 },
    { "short int",              sizeof(short),      1, 0 },
    { "unsigned short int",     sizeof(short),      0, 0 },
    { "signed short int",       sizeof(short),      1, 0 },
    { "int",                    sizeof(int),        1, 0 },
    { "unsigned",               sizeof(int),        0, 0 },
    { "unsigned int",           sizeof(int),        0, 0 },
    { "signed int",             sizeof(int),        1, 0 },
    { "long",                   sizeof(long),       1, 0 },
    { "unsigned long",          sizeof(long),       0, 0 },
    { "signed long",            sizeof(long),       1, 0 },
    { "long int",               sizeof(long),       1, 0 },
    { "unsigned long int",      sizeof(long),       0, 0 },
    { "signed long int",        sizeof(long),       1, 0 },
    { "long long",              sizeof(int64_t),    1, 0 },
    { "unsigned long long",     sizeof(int64_t),    0, 0 },
    { "signed long long",       sizeof(int64_t),    1, 0 },
    { "long long int",          sizeof(int64_t),    1, 0 },
    { "unsigned long long int", sizeof(int64_t),    0, 0 },
    { "signed long long int",   sizeof(int64_t),    1, 0 },
    { "float",                  sizeof(float),      1, 1 },
    { "double",                 sizeof(double),     1, 1 },
    { "long double",            sizeof(long double), 1, 1 },
    { "uint8_t",                1,                  0, 0 },
    { "uint16_t",               2,                  0, 0 },
    { "uint32_t",               4,                  0, 0 },
    { "uint64_t",               8,                  0, 0 },
    { "int8_t",                 1,                  1, 0 },
    { "int16_t",                2,                  1, 0 },
    { "int32_t",                4,                  1, 0 },
    { "int64_t",                8,                  1, 0 },
    { "char16_t",               2,                  0, 0 },
    { "char32_t",               4,                  0, 0 },
    { NULL }
};

#define BST_UNSIGNED 11

struct Symbol {
#if ENABLE_SymbolsMux
    SymbolReader * reader;
#endif
    unsigned magic;
    Context * ctx;
    unsigned frame;
    int sym_class;
    ULONG64 module;
    ULONG index;            /* The symbol index in debug info section */
    const TypeInfo * info;  /* If not NULL, the symbol is basic type */
    const Symbol * base;    /* If not NULL, the symbol is array or pointer with this base type */
    size_t length;
    ContextAddress address;
};

typedef struct SymbolCacheEntry {
    struct SymbolCacheEntry * next;
    ULONG64 pc;
    char name[MAX_SYM_NAME];
    ErrorReport * error;
    int sym_class;
    int frame_relative;
    ULONG64 module;
    ULONG index;
} SymbolCacheEntry;

#define SYMBOL_CACHE_SIZE (4 * MEM_USAGE_FACTOR - 1)

typedef struct ContextExtensionWinSym {
    SymbolCacheEntry ** symbol_cache;
} ContextExtensionWinSym;

static size_t context_extension_offset = 0;

#define EXT(ctx) ((ContextExtensionWinSym *)((char *)(ctx) + context_extension_offset))

static char * tmp_buf = NULL;
static int tmp_buf_size = 0;
static LocationCommands * location_cmds = NULL;

#define SYMBOL_MAGIC 0x34875234

static Symbol * alloc_symbol(void) {
    Symbol * s = (Symbol *)tmp_alloc_zero(sizeof(Symbol));
#if ENABLE_SymbolsMux
    s->reader = &symbol_reader;
#endif
    s->magic = SYMBOL_MAGIC;
    return s;
}

static int get_stack_frame(Context * ctx, int frame, ContextAddress ip, IMAGEHLP_STACK_FRAME * stack_frame) {
    memset(stack_frame, 0, sizeof(IMAGEHLP_STACK_FRAME));
    if (frame == STACK_NO_FRAME) {
        stack_frame->InstructionOffset = ip;
    }
    else if (ctx->parent != NULL) {
        uint64_t v = 0;
        StackFrame * frame_info;
        if (get_frame_info(ctx, frame, &frame_info) < 0) return -1;
        if (read_reg_value(frame_info, get_PC_definition(ctx), &v) < 0) return -1;
        stack_frame->InstructionOffset = v;
    }
    return 0;
}

static int get_sym_info(const Symbol * sym, DWORD index, SYMBOL_INFO ** res) {
    static ULONG64 buffer[(sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR) + sizeof(ULONG64) - 1) / sizeof(ULONG64)];
    SYMBOL_INFO * info = (SYMBOL_INFO *)buffer;
    HANDLE process = get_context_handle(context_get_group(sym->ctx, CONTEXT_GROUP_PROCESS));

    info->SizeOfStruct = sizeof(SYMBOL_INFO);
    info->MaxNameLen = MAX_SYM_NAME;
    if (!SymFromIndex(process, sym->module, index, info)) {
        set_win32_errno(GetLastError());
        return -1;
    }
    *res = info;
    return 0;
}

static int get_type_info(const Symbol * sym, IMAGEHLP_SYMBOL_TYPE_INFO info_tag, void * info) {
    HANDLE process = get_context_handle(context_get_group(sym->ctx, CONTEXT_GROUP_PROCESS));
    if (!SymGetTypeInfo(process, sym->module, sym->index, info_tag, info)) {
        set_win32_errno(GetLastError());
        return -1;
    }
    return 0;
}

static int wchar_to_utf8(WCHAR * str, char ** utf) {
    int len = 0;
    int err = 0;
    if (tmp_buf == NULL) {
        tmp_buf_size = 256;
        tmp_buf = (char *)loc_alloc(tmp_buf_size);
    }
    for (;;) {
        len = WideCharToMultiByte(CP_UTF8, 0, str, -1, tmp_buf, tmp_buf_size - 1, NULL, NULL);
        if (len != 0) break;
        err = GetLastError();
        if (err != ERROR_INSUFFICIENT_BUFFER) {
            set_win32_errno(err);
            return -1;
        }
        tmp_buf_size *= 2;
        tmp_buf = (char *)loc_realloc(tmp_buf, tmp_buf_size);
    }
    tmp_buf[len] = 0;
    *utf = tmp_buf;
    return 0;
}

static void tag2symclass(Symbol * sym, int tag) {
    DWORD dword;
    sym->sym_class = SYM_CLASS_UNKNOWN;
    switch (tag) {
    case SymTagFunction:
        sym->sym_class = SYM_CLASS_FUNCTION;
        break;
    case SymTagData:
        if (get_type_info(sym, TI_GET_DATAKIND, &dword) == 0) {
            if (dword == DataIsConstant) {
                sym->sym_class = SYM_CLASS_VALUE;
                break;
            }
        }
        sym->sym_class = SYM_CLASS_REFERENCE;
        break;
    case SymTagUDT:
    case SymTagEnum:
    case SymTagFunctionType:
    case SymTagPointerType:
    case SymTagArrayType:
    case SymTagBaseType:
    case SymTagTypedef:
    case SymTagBaseClass:
    case SymTagCustomType:
    case SymTagManagedType:
    case SymTagFunctionArgType:
        sym->sym_class = SYM_CLASS_TYPE;
        break;
    }
}

static int is_frame_relative(SYMBOL_INFO * info) {
    return (info->Flags & SYMFLAG_FRAMEREL) || (info->Flags & SYMFLAG_REGREL);
}

static int is_register(SYMBOL_INFO * info) {
    return info->Flags & SYMFLAG_REGISTER;
}

static int syminfo2symbol(Context * ctx, int frame, SYMBOL_INFO * info, Symbol * sym) {
    sym->module = info->ModBase;
    sym->index = info->Index;
    if (is_frame_relative(info) || is_register(info)) {
        if (frame == STACK_NO_FRAME) return 0;
        assert(frame >= 0);
        assert(ctx != ctx->mem);
        sym->frame = frame - STACK_NO_FRAME;
    }
    else {
        assert(sym->frame == 0);
        ctx = ctx->mem;
    }
    sym->ctx = ctx;
    tag2symclass(sym, info->Tag);
    return 1;
}

static int get_type_tag(Symbol * type, DWORD * tag) {
    DWORD dword;
    for (;;) {
        if (get_type_info(type, TI_GET_SYMTAG, &dword) < 0) return -1;
        switch (dword) {
        case SymTagTypedef:
        case SymTagFunction:
        case SymTagData:
        case SymTagFunctionArgType:
            if (get_type_info(type, TI_GET_TYPE, &dword) < 0) return -1;
            type->index = dword;
            continue;
        }
        break;
    }
    type->sym_class = SYM_CLASS_TYPE;
    *tag = dword;
    return 0;
}

const char * symbol2id(const Symbol * sym) {
    static char buf[256];
    assert(sym->magic == SYMBOL_MAGIC);
    if (sym->base) {
        char base[sizeof(buf)];
        assert(sym->ctx == sym->base->ctx);
        assert(sym->sym_class == SYM_CLASS_TYPE);
        strlcpy(base, symbol2id(sym->base), sizeof(base));
        snprintf(buf, sizeof(buf), "@P%" PRIx64 ".%s", (uint64_t)sym->length, base);
    }
    else {
        int i = sym->info ? (int)(sym->info - basic_type_info) + 1 : 0;
        snprintf(buf, sizeof(buf), "@S%" PRIx64 ".%lX.%X.%X.%s",
            (uint64_t)sym->module, sym->index, sym->frame, i, sym->ctx->id);
    }
    return buf;
}

static uint64_t read_hex(const char ** s) {
    uint64_t res = 0;
    const char * p = *s;
    for (;;) {
        if (*p >= '0' && *p <= '9') res = (res << 4) | (*p - '0');
        else if (*p >= 'A' && *p <= 'F') res = (res << 4) | (*p - 'A' + 10);
        else break;
        p++;
    }
    *s = p;
    return res;
}

int id2symbol(const char * id, Symbol ** res) {
    Symbol * sym = NULL;
    Context * ctx = NULL;
    ULONG64 module = 0;
    ULONG index = 0;
    unsigned frame = 0;
    const Symbol * base = NULL;
    const TypeInfo * info = NULL;
    size_t length = 0;
    const char * p;

    if (id != NULL && id[0] == '@' && id[1] == 'P') {
        p = id + 2;
        length = (size_t)read_hex(&p);
        if (*p == '.') p++;
        if (id2symbol(p, (Symbol **)&base)) return -1;
        ctx = base->ctx;
    }
    else if (id != NULL && id[0] == '@' && id[1] == 'S') {
        unsigned idx = 0;
        p = id + 2;
        module = (ULONG64)read_hex(&p);
        if (*p == '.') p++;
        index = (ULONG)read_hex(&p);
        if (*p == '.') p++;
        frame = (unsigned)read_hex(&p);
        if (*p == '.') p++;
        idx = (unsigned)read_hex(&p);
        if (idx) info = basic_type_info + (idx - 1);
        if (*p == '.') p++;
        ctx = id2ctx(p);
    }
    else {
        errno = ERR_INV_CONTEXT;
        return -1;
    }
    if (ctx == NULL) {
        errno = ERR_INV_CONTEXT;
        return -1;
    }
    sym = alloc_symbol();
    sym->ctx = ctx;
    sym->module = module;
    sym->index = index;
    sym->frame = frame;
    sym->base = base;
    sym->info = info;
    sym->length = length;
    if (sym->base || sym->info) {
        sym->sym_class = SYM_CLASS_TYPE;
    }
    else {
        DWORD dword = 0;
        if (get_type_info(sym, TI_GET_SYMTAG, &dword) < 0) return -1;
        tag2symclass(sym, dword);
    }
    *res = sym;
    return 0;
}

int get_symbol_class(const Symbol * sym, int * sym_class) {
    assert(sym->magic == SYMBOL_MAGIC);
    *sym_class = sym->sym_class;
    return 0;
}

int get_symbol_type_class(const Symbol * sym, int * type_class) {
    int res = TYPE_CLASS_UNKNOWN;
    Symbol type = *sym;
    DWORD tag = 0;
    DWORD base = 0;

    assert(sym->magic == SYMBOL_MAGIC);
    if (sym->base) {
        *type_class = sym->length == 0 ? TYPE_CLASS_POINTER : TYPE_CLASS_ARRAY;
        return 0;
    }
    if (sym->info) {
        if (sym->info->real) {
            *type_class = TYPE_CLASS_REAL;
        }
        else if (sym->info->sign) {
            *type_class = TYPE_CLASS_INTEGER;
        }
        else {
            *type_class = TYPE_CLASS_CARDINAL;
        }
        return 0;
    }
    if (get_type_tag(&type, &tag)) return -1;

    switch (tag) {
    case SymTagFunction:
    case SymTagPublicSymbol:
        res = TYPE_CLASS_FUNCTION;
        break;
    case SymTagEnum:
        res = TYPE_CLASS_ENUMERATION;
        break;
    case SymTagFunctionType:
        res = TYPE_CLASS_FUNCTION;
        break;
    case SymTagPointerType:
        res = TYPE_CLASS_POINTER;
        break;
    case SymTagArrayType:
        res = TYPE_CLASS_ARRAY;
        break;
    case SymTagUDT:
        res = TYPE_CLASS_COMPOSITE;
        break;
    case SymTagBaseType:
        if (get_type_info(&type, TI_GET_BASETYPE, &base) < 0) return -1;
        switch (base) {
        case btNoType:
            break;
        case btVoid:
        case btChar:
        case btWChar:
        case btInt:
        case btBool:
        case btLong:
        case btBit:
            res = TYPE_CLASS_INTEGER;
            break;
        case btUInt:
        case btULong:
            res = TYPE_CLASS_CARDINAL;
            break;
        case btFloat:
            res = TYPE_CLASS_REAL;
            break;
        case btBCD:
        case btCurrency:
        case btDate:
        case btVariant:
        case btComplex:
        case btBSTR:
        case btHresult:
            break;
        }
        break;
    }

    *type_class = res;
    return 0;
}

int get_symbol_update_policy(const Symbol * sym, char ** id, int * policy) {
    assert(sym->magic == SYMBOL_MAGIC);
    *id = sym->ctx->id;
    *policy = sym->frame > 0 ? UPDATE_ON_EXE_STATE_CHANGES : UPDATE_ON_MEMORY_MAP_CHANGES;
    return 0;
}

int get_symbol_name(const Symbol * sym, char ** name) {
    WCHAR * ptr = NULL;

    assert(sym->magic == SYMBOL_MAGIC);
    if (sym->base) {
        *name = NULL;
        return 0;
    }
    if (sym->info) {
        *name = sym->info->name;
        return 0;
    }
    *name = NULL;
    if (get_type_info(sym, TI_GET_SYMNAME, &ptr) < 0) ptr = NULL;
    if (ptr != NULL && wcscmp(ptr, L"<unnamed-tag>") == 0) ptr = NULL;
    if (ptr != NULL) {
        if (wchar_to_utf8(ptr, name) < 0) return -1;
        HeapFree(GetProcessHeap(), 0, ptr);
    }
    else {
        DWORD tag = 0;
        Symbol type = *sym;
        if (get_type_tag(&type, &tag)) return -1;
        if (tag == SymTagBaseType) {
            ContextAddress size = 0;
            int type_class = 0;
            unsigned char sign = 0;
            unsigned char real = 0;
            const TypeInfo * p = basic_type_info;
            if (get_symbol_size(&type, &size)) return -1;
            if (get_symbol_type_class(&type, &type_class)) return -1;
            if (type_class == TYPE_CLASS_INTEGER) sign = 1;
            else if (type_class == TYPE_CLASS_REAL) real = sign = 1;
            while (p->name != NULL) {
                if (p->size == size && p->sign == sign && p->real == real) {
                    *name = p->name;
                    break;
                }
                p++;
            }
        }
    }
    return 0;
}

int get_symbol_size(const Symbol * sym, ContextAddress * size) {
    uint64_t res = 0;
    DWORD tag = 0;

    assert(sym->magic == SYMBOL_MAGIC);
    if (sym->base) {
        if (sym->length > 0) {
            if (get_symbol_size(sym->base, size)) return -1;
            *size *= sym->length;
        }
        else {
            *size = sizeof(void *);
        }
        return 0;
    }
    if (sym->info) {
        *size = sym->info->size;
        return 0;
    }
    if (sym->module == 0) {
        set_errno(ERR_OTHER, "Debug info not available");
        return -1;
    }
    if (sym->sym_class == SYM_CLASS_REFERENCE || sym->sym_class == SYM_CLASS_FUNCTION) {
        SYMBOL_INFO * info = NULL;
        if (get_sym_info(sym, sym->index, &info) < 0) return -1;
        res = info->Size;
    }
    else {
        Symbol type = *sym;
        if (get_type_tag(&type, &tag)) return -1;
        if (get_type_info(&type, TI_GET_LENGTH, &res) < 0) return -1;
    }

    *size = (ContextAddress)res;
    return 0;
}

int get_symbol_type(const Symbol * sym, Symbol ** type) {
    assert(sym->magic == SYMBOL_MAGIC);
    if (sym->address) {
        *type = NULL;
        return 0;
    }
    if (!sym->base && !sym->info) {
        DWORD tag = 0;
        DWORD index = 0;
        Symbol * res = alloc_symbol();
        *res = *sym;
        if (get_type_info(sym, TI_GET_SYMTAG, &tag) < 0) return -1;
        switch (tag) {
        case SymTagTypedef:
        case SymTagFunction:
        case SymTagPublicSymbol:
        case SymTagData:
        case SymTagFunctionArgType:
            if (get_type_info(sym, TI_GET_TYPE, &index) < 0) return -1;
            res->sym_class = SYM_CLASS_TYPE;
            res->index = index;
            *type = res;
            return 0;
        }
        assert(sym->sym_class == SYM_CLASS_UNKNOWN || sym->sym_class == SYM_CLASS_TYPE);
    }
    *type = (Symbol *)sym;
    return 0;
}

int get_symbol_base_type(const Symbol * sym, Symbol ** type) {
    DWORD tag = 0;
    DWORD index = 0;
    Symbol * res = NULL;

    assert(sym->magic == SYMBOL_MAGIC);
    if (sym->base) {
        *type = (Symbol *)sym->base;
        return 0;
    }
    if (sym->info) {
        errno = ERR_INV_CONTEXT;
        return -1;
    }
    res = alloc_symbol();
    *res = *sym;
    if (get_type_tag(res, &tag)) return -1;
    if (get_type_info(res, TI_GET_TYPE, &index) < 0) return -1;
    res->index = index;
    *type = res;
    return 0;
}

int get_symbol_index_type(const Symbol * sym, Symbol ** type) {
    DWORD tag = 0;
    DWORD index = 0;
    Symbol * res = alloc_symbol();

    assert(sym->magic == SYMBOL_MAGIC);
    if (sym->base && sym->length) {
        res->ctx = sym->ctx;
        res->sym_class = SYM_CLASS_TYPE;
        res->info = basic_type_info + BST_UNSIGNED;
        assert(res->info->size == sizeof(int));
        assert(res->info->sign == 0);
        assert(res->info->real == 0);
        *type = res;
        return 0;
    }
    if (sym->base || sym->info) {
        errno = ERR_INV_CONTEXT;
        return -1;
    }
    *res = *sym;
    if (get_type_tag(res, &tag)) return -1;
    if (get_type_info(res, TI_GET_ARRAYINDEXTYPEID, &index) < 0) return -1;
    res->index = index;
    *type = res;
    return 0;
}

int get_symbol_container(const Symbol * sym, Symbol ** container) {
    errno = ERR_UNSUPPORTED;
    return -1;
}

int get_symbol_length(const Symbol * sym, ContextAddress * length) {
    DWORD res = 0;
    Symbol type = *sym;
    DWORD tag = 0;

    assert(sym->magic == SYMBOL_MAGIC);
    if (sym->base && sym->length) {
        *length = sym->length;
        return 0;
    }
    if (sym->base || sym->info) {
        errno = ERR_INV_CONTEXT;
        return -1;
    }
    if (get_type_tag(&type, &tag)) return -1;
    switch (tag) {
    case SymTagArrayType:
        if (get_type_info(&type, TI_GET_COUNT, &res) < 0) return -1;
        *length = res;
        return 0;
    }
    errno = ERR_INV_CONTEXT;
    return -1;
}

int get_symbol_lower_bound(const Symbol * sym, int64_t * value) {
    Symbol type = *sym;
    DWORD tag = 0;

    assert(sym->magic == SYMBOL_MAGIC);
    if (sym->base && sym->length) {
        *value = 0;
        return 0;
    }
    if (sym->base || sym->info) {
        errno = ERR_INV_CONTEXT;
        return -1;
    }
    if (get_type_tag(&type, &tag)) return -1;
    switch (tag) {
    case SymTagArrayType:
        /* TODO: Windows array symbol lower bound value */
        *value = 0;
        return 0;
    }
    errno = ERR_INV_CONTEXT;
    return -1;
}

int get_symbol_children(const Symbol * sym, Symbol *** children, int * count) {

    static const DWORD FINDCHILDREN_BUF_SIZE = 64;
    static TI_FINDCHILDREN_PARAMS * params = NULL;
    Symbol ** buf = NULL;

    DWORD cnt = 0;
    Symbol type = *sym;
    DWORD tag = 0;

    assert(sym->magic == SYMBOL_MAGIC);
    if (sym->base || sym->info) {
        *children = NULL;
        *count = 0;
        return 0;
    }
    if (get_type_tag(&type, &tag)) return -1;
    if (get_type_info(&type, TI_GET_CHILDRENCOUNT, &cnt) < 0) return -1;
    if (params == NULL) params = (TI_FINDCHILDREN_PARAMS *)loc_alloc(
        sizeof(TI_FINDCHILDREN_PARAMS) + (FINDCHILDREN_BUF_SIZE - 1) * sizeof(ULONG));

    buf = (Symbol **)tmp_alloc(sizeof(Symbol *) * cnt);

    params->Start = 0;
    while (params->Start < cnt) {
        DWORD i = cnt - (DWORD)params->Start;
        params->Count = i > FINDCHILDREN_BUF_SIZE ? FINDCHILDREN_BUF_SIZE : i;
        if (get_type_info(&type, TI_FINDCHILDREN, params) < 0) return -1;
        for (i = 0; params->Start < cnt; i++) {
            DWORD dword = 0;
            Symbol * x = alloc_symbol();
            *x = *sym;
            x->index = params->ChildId[i];
            if (get_type_info(x, TI_GET_SYMTAG, &dword) < 0) return -1;
            tag2symclass(x, dword);
            buf[params->Start++] = x;
        }
    }

    *children = buf;
    *count = cnt;
    return 0;
}

static RegisterDefinition * find_register(Context * ctx, const char * name) {
    RegisterDefinition * defs = get_reg_definitions(ctx);
    if (defs == NULL) return NULL;
    while (defs->name != NULL) {
        if (strcasecmp(defs->name, name) == 0) return defs;
        defs++;
    }
    return NULL;
}

int get_symbol_flags(const Symbol * sym, SYM_FLAGS * flags) {
    DWORD tag = 0;
    DWORD dword = 0;
    SYMBOL_INFO * info = NULL;

    *flags = 0;
    assert(sym->magic == SYMBOL_MAGIC);
    if (sym->address || sym->base || sym->info) return 0;
    if (get_type_info(sym, TI_GET_SYMTAG, &tag) < 0) return -1;
    if (get_sym_info(sym, sym->index, &info) == 0 && (info->Flags & SYMFLAG_PARAMETER) != 0) *flags |= SYM_FLAG_PARAMETER;
    if (get_type_info(sym, TI_GET_IS_REFERENCE, &dword) == 0 && dword) *flags |= SYM_FLAG_REFERENCE;
    if (tag == SymTagFunctionArgType) *flags |= SYM_FLAG_PARAMETER;
    if (tag == SymTagPublicSymbol) *flags |= SYM_FLAG_EXTERNAL;
    if (tag == SymTagTypedef) *flags |= SYM_FLAG_TYPEDEF;
    if (tag == SymTagEnum) *flags |= SYM_FLAG_ENUM_TYPE;

    return 0;
}

int get_symbol_props(const Symbol * sym, SymbolProperties * props) {
    memset(props, 0, sizeof(SymbolProperties));
    return 0;
}

int get_symbol_frame(const Symbol * sym, Context ** ctx, int * frame) {
    int n = sym->frame + STACK_NO_FRAME;
    if (n == STACK_TOP_FRAME) {
        n = get_top_frame(sym->ctx);
        if (n < 0) return -1;
    }
    *ctx = sym->ctx;
    *frame = n;
    return 0;
}

int get_array_symbol(const Symbol * sym, ContextAddress length, Symbol ** ptr) {
    assert(sym->magic == SYMBOL_MAGIC);
    *ptr = alloc_symbol();
    (*ptr)->ctx = sym->ctx;
    (*ptr)->sym_class = SYM_CLASS_TYPE;
    (*ptr)->base = (Symbol *)sym;
    (*ptr)->length = length;
    return 0;
}

static unsigned symbol_hash(ULONG64 pc, PCSTR name) {
    int i;
    unsigned h = (unsigned)(uintptr_t)pc;
    for (i = 0; name[i]; i++) h += name[i];
    h = h + h / SYMBOL_CACHE_SIZE;
    return h % SYMBOL_CACHE_SIZE;
}

static int find_cache_symbol(Context * ctx, int frame, ULONG64 pc, PCSTR name, Symbol * sym) {
    ContextExtensionWinSym * ext = EXT(ctx->mem);
    if (ext->symbol_cache != NULL) {
        int cnt = 0;
        SymbolCacheEntry * entry = ext->symbol_cache[symbol_hash(pc, name)];
        while (entry != NULL) {
            if (entry->pc == pc && strcmp(entry->name, name) == 0) {
                if (entry->error == NULL) {
                    if (entry->frame_relative) {
                        assert(frame >= 0);
                        sym->frame = frame - STACK_NO_FRAME;
                    }
                    else {
                        ctx = ctx->mem;
                    }
                    sym->ctx = ctx;
                    sym->sym_class = entry->sym_class;
                    sym->module = entry->module;
                    sym->index = entry->index;
                }
                set_error_report_errno(entry->error);
                return 1;
            }
            else if (cnt > 32) {
                while (entry->next) {
                    SymbolCacheEntry * next = entry->next;
                    entry->next = next->next;
                    release_error_report(next->error);
                    loc_free(next);
                }
                return 0;
            }
            entry = entry->next;
            cnt++;
        }
    }
    return 0;
}

static void add_cache_symbol(Context * ctx, ULONG64 pc, PCSTR name, Symbol * sym, int error) {
    unsigned h = symbol_hash(pc, name);
    ContextExtensionWinSym * ext = EXT(ctx->mem);
    SymbolCacheEntry * entry = (SymbolCacheEntry *)loc_alloc_zero(sizeof(SymbolCacheEntry));
    assert(!ctx->mem->exited);
    entry->pc = pc;
    strlcpy(entry->name, name, sizeof(entry->name));
    entry->error = get_error_report(error);
    if (!error) {
        entry->frame_relative = sym->frame > 0;
        entry->sym_class = sym->sym_class;
        entry->module = sym->module;
        entry->index = sym->index;
    }
    if (ext->symbol_cache == NULL) ext->symbol_cache = (SymbolCacheEntry **)loc_alloc_zero(sizeof(SymbolCacheEntry *) * SYMBOL_CACHE_SIZE);
    entry->next = ext->symbol_cache[h];
    ext->symbol_cache[h] = entry;
}

static int set_pe_context(Context * ctx, int frame, ContextAddress ip, HANDLE process, IMAGEHLP_STACK_FRAME * stack_frame) {
    if (get_stack_frame(ctx, frame, ip, stack_frame) < 0) return -1;

    if (!SymSetContext(process, stack_frame, NULL)) {
        DWORD err = GetLastError();
        if (err == ERROR_SUCCESS) {
            /* Don't know why Windows do this */
        }
        else if (err == ERROR_MOD_NOT_FOUND && frame != STACK_NO_FRAME) {
            /* No local symbols data, search global scope */
            if (get_stack_frame(ctx, STACK_NO_FRAME, 0, stack_frame) < 0) return -1;
            if (!SymSetContext(process, stack_frame, NULL)) {
                err = GetLastError();
                if (err != ERROR_SUCCESS) {
                    set_win32_errno(err);
                    return -1;
                }
            }
        }
        else if (err == ERROR_NOT_SUPPORTED) {
            /* Compiled without debug info */
            errno = ERR_SYM_NOT_FOUND;
            return -1;
        }
        else {
            set_win32_errno(err);
            return -1;
        }
    }
    return 0;
}

static int find_pe_symbol_by_name(Context * ctx, int frame, ContextAddress ip, const char * name, Symbol * sym) {
    HANDLE process = get_context_handle(context_get_group(ctx, CONTEXT_GROUP_PROCESS));
    ULONG64 buffer[(sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR) + sizeof(ULONG64) - 1) / sizeof(ULONG64)];
    SYMBOL_INFO * info = (SYMBOL_INFO *)buffer;
    IMAGEHLP_STACK_FRAME stack_frame;
    DWORD err;

    if (set_pe_context(ctx, frame, ip, process, &stack_frame) < 0) return -1;

    memset(info, 0, sizeof(SYMBOL_INFO));
    info->SizeOfStruct = sizeof(SYMBOL_INFO);
    info->MaxNameLen = MAX_SYM_NAME;

    if (find_cache_symbol(ctx, frame, stack_frame.InstructionOffset, name, sym)) return errno ? -1 : 0;

    /* TODO: SymFromName() searches only main executable, need to search DLLs too */
    SetLastError(0);
    if (SymFromName(process, name, info) && info->Tag != SymTagPublicSymbol) {
        if (syminfo2symbol(ctx, frame, info, sym)) {
            add_cache_symbol(ctx, stack_frame.InstructionOffset, name, sym, 0);
            return 0;
        }
    }
    if (stack_frame.InstructionOffset != 0) {
        DWORD64 module = SymGetModuleBase64(process, stack_frame.InstructionOffset);
        if (module != 0 && SymGetTypeFromName(process, module, name, info)) {
            if (syminfo2symbol(ctx, frame, info, sym)) {
                add_cache_symbol(ctx, stack_frame.InstructionOffset, name, sym, 0);
                return 0;
            }
        }
    }
    set_win32_errno(err = GetLastError());
    if (err == 0 || err == ERROR_MOD_NOT_FOUND) {
        add_cache_symbol(ctx, stack_frame.InstructionOffset, name, NULL, ERR_SYM_NOT_FOUND);
        errno = ERR_SYM_NOT_FOUND;
    }
    return -1;
}

static int find_pe_symbol_by_addr(Context * ctx, int frame, ContextAddress addr, Symbol * sym) {
    HANDLE process = get_context_handle(context_get_group(ctx, CONTEXT_GROUP_PROCESS));
    ULONG64 buffer[(sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR) + sizeof(ULONG64) - 1) / sizeof(ULONG64)];
    SYMBOL_INFO * info = (SYMBOL_INFO *)buffer;
    IMAGEHLP_STACK_FRAME stack_frame;
    DWORD err;

    if (set_pe_context(ctx, frame, 0, process, &stack_frame) < 0) return -1;

    memset(info, 0, sizeof(SYMBOL_INFO));
    info->SizeOfStruct = sizeof(SYMBOL_INFO);
    info->MaxNameLen = MAX_SYM_NAME;

    SetLastError(0);
    if (SymFromAddr(process, addr, NULL, info)) {
        if (syminfo2symbol(ctx, frame, info, sym)) return 0;
    }

    set_win32_errno(err = GetLastError());
    if (err == 0 || err == ERROR_MOD_NOT_FOUND || err == ERROR_INVALID_ADDRESS) {
        errno = ERR_SYM_NOT_FOUND;
    }
    return -1;
}

static int find_basic_type_symbol(Context * ctx, const char * name, Symbol * sym) {
    const TypeInfo * p = basic_type_info;
    while (p->name != NULL) {
        if (strcmp(p->name, name) == 0) {
            sym->ctx = ctx->mem;
            sym->sym_class = SYM_CLASS_TYPE;
            sym->info = p;
            return 0;
        }
        p++;
    }
    errno = ERR_SYM_NOT_FOUND;
    return -1;
}

int find_symbol_by_name(Context * ctx, int frame, ContextAddress ip, const char * name, Symbol ** sym) {
    int found = 0;

    *sym = alloc_symbol();
    (*sym)->ctx = ctx;
    if (frame == STACK_TOP_FRAME && (frame = get_top_frame(ctx)) < 0) return -1;
    if (find_pe_symbol_by_name(ctx, frame, ip, name, *sym) >= 0) found = 1;
    else if (get_error_code(errno) != ERR_SYM_NOT_FOUND) return -1;
    if (!found) {
        if (find_basic_type_symbol(ctx, name, *sym) >= 0) found = 1;
        else if (get_error_code(errno) != ERR_SYM_NOT_FOUND) return -1;
    }
    if (!found) {
        errno = ERR_SYM_NOT_FOUND;
        return -1;
    }
    assert(frame >= 0 || (*sym)->ctx == ctx->mem);
    assert((*sym)->ctx == ((*sym)->frame ? ctx : ctx->mem));
    assert((*sym)->frame == ((*sym)->ctx == (*sym)->ctx->mem ? 0u : frame - STACK_NO_FRAME));
    return 0;
}

typedef struct FSISEnumerateSymbolsContext {
    Context * ctx;
    int frame;
    const char * name;
    Symbol * sym;
    unsigned cnt;
} FSISEnumerateSymbolsContext;

static BOOL CALLBACK fsis_enumerate_symbols(SYMBOL_INFO * info, ULONG symbol_size, VOID * user_context) {
    FSISEnumerateSymbolsContext * enum_context = (FSISEnumerateSymbolsContext *)user_context;
    if (strcmp(enum_context->name, info->Name) == 0) {
        Symbol * sym = alloc_symbol();
        if (syminfo2symbol(enum_context->ctx, enum_context->frame, info, sym)) {
            enum_context->sym = sym;
            enum_context->cnt++;
        }
    }
    return TRUE;
}

int find_symbol_in_scope(Context * ctx, int frame, ContextAddress ip, Symbol * scope, const char * name, Symbol ** sym) {
    ContextAddress scope_addr = 0;
    Symbol ** buf = NULL;
    int cnt = 0;
    int i;

    if (scope == NULL) return find_symbol_by_name(ctx, frame, ip, name, sym);

    if (get_symbol_children(scope, &buf, &cnt) < 0) return -1;
    for (i = 0; i < cnt; i++) {
        char * s = NULL;
        if (get_symbol_name(buf[i], &s) < 0) return -1;
        if (s != NULL && strcmp(s, name) == 0) {
            *sym = buf[i];
            return 0;
        }
    }

    if (get_symbol_address(scope, &scope_addr) == 0) {
        ULONG64 buffer[(sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR) + sizeof(ULONG64) - 1) / sizeof(ULONG64)];
        HANDLE process = get_context_handle(context_get_group(ctx, CONTEXT_GROUP_PROCESS));
        SYMBOL_INFO * symbol = (SYMBOL_INFO *)buffer;
        IMAGEHLP_STACK_FRAME stack_frame;
        FSISEnumerateSymbolsContext enum_context;

        symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        symbol->MaxNameLen = MAX_SYM_NAME;

        memset(&stack_frame, 0, sizeof(IMAGEHLP_STACK_FRAME));
        stack_frame.InstructionOffset = scope_addr;

        if (!SymSetContext(process, &stack_frame, NULL)) {
            DWORD err = GetLastError();
            if (err == ERROR_SUCCESS) {
                /* Don't know why Windows do this */
            }
            else {
                set_win32_errno(err);
                return -1;
            }
        }

        memset(&enum_context, 0, sizeof(FSISEnumerateSymbolsContext));
        enum_context.ctx = ctx;
        enum_context.frame = frame;
        enum_context.name = name;

        if (!SymEnumSymbols(process, 0, NULL, fsis_enumerate_symbols, &enum_context)) {
            set_win32_errno(GetLastError());
            return -1;
        }

        if (enum_context.cnt == 1) {
            *sym = enum_context.sym;
            return 0;
        }
    }

    errno = ERR_SYM_NOT_FOUND;
    return -1;
}

int find_symbol_by_addr(Context * ctx, int frame, ContextAddress addr, Symbol ** sym) {
    *sym = alloc_symbol();
    (*sym)->ctx = ctx;
    if (frame == STACK_TOP_FRAME && (frame = get_top_frame(ctx)) < 0) return -1;
    if (find_pe_symbol_by_addr(ctx, frame, addr, *sym) < 0) return -1;
    assert(frame >= 0 || (*sym)->ctx == ctx->mem);
    assert((*sym)->ctx == ((*sym)->frame ? ctx : ctx->mem));
    assert((*sym)->frame == ((*sym)->ctx == (*sym)->ctx->mem ? 0u : frame - STACK_NO_FRAME));
    return 0;
}

int find_next_symbol(Symbol ** sym) {
    /* TODO: find_next_symbol() for Windows */
    errno = ERR_SYM_NOT_FOUND;
    return -1;
}

typedef struct EnumerateSymbolsContext {
    Context * ctx;
    int frame;
    EnumerateSymbolsCallBack * call_back;
    void * args;
} EnumerateSymbolsContext;

static BOOL CALLBACK enumerate_symbols_proc(SYMBOL_INFO * info, ULONG symbol_size, VOID * user_context) {
    EnumerateSymbolsContext * enum_context = (EnumerateSymbolsContext *)user_context;
    Symbol * sym = alloc_symbol();
    if (syminfo2symbol(enum_context->ctx, enum_context->frame, info, sym)) {
        enum_context->call_back(enum_context->args, sym);
    }
    return TRUE;
}

int enumerate_symbols(Context * ctx, int frame, EnumerateSymbolsCallBack * call_back, void * args) {
    ULONG64 buffer[(sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR) + sizeof(ULONG64) - 1) / sizeof(ULONG64)];
    SYMBOL_INFO * symbol = (SYMBOL_INFO *)buffer;
    IMAGEHLP_STACK_FRAME stack_frame;
    EnumerateSymbolsContext enum_context;
    HANDLE process = get_context_handle(context_get_group(ctx, CONTEXT_GROUP_PROCESS));

    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    symbol->MaxNameLen = MAX_SYM_NAME;

    if (frame == STACK_TOP_FRAME) frame = get_top_frame(ctx);
    if (frame == STACK_TOP_FRAME) return -1;
    if (get_stack_frame(ctx, frame, 0, &stack_frame) < 0) return -1;

    if (!SymSetContext(process, &stack_frame, NULL)) {
        DWORD err = GetLastError();
        if (err == ERROR_SUCCESS) {
            /* Don't know why Windows do this */
        }
        else {
            set_win32_errno(err);
            return -1;
        }
    }

    enum_context.ctx = ctx;
    enum_context.frame = frame;
    enum_context.call_back = call_back;
    enum_context.args = args;

    if (!SymEnumSymbols(process, 0, NULL, enumerate_symbols_proc, &enum_context)) {
        set_win32_errno(GetLastError());
        return -1;
    }

    return 0;
}

ContextAddress is_plt_section(Context * ctx, ContextAddress addr) {
    errno = 0;
    return 0;
}

int get_context_isa(Context * ctx, ContextAddress addr, const char ** isa,
        ContextAddress * range_addr, ContextAddress * range_size) {
    *isa = NULL;
    *range_addr = addr;
    *range_size = 1;
    return 0;
}

static LocationExpressionCommand * add_location_command(int op) {
    LocationExpressionCommand * cmd = NULL;
    if (location_cmds->cnt >= location_cmds->max) {
        location_cmds->max += 4;
        location_cmds->cmds = (LocationExpressionCommand *)tmp_realloc(location_cmds->cmds,
            sizeof(LocationExpressionCommand) * location_cmds->max);
    }
    cmd = location_cmds->cmds + location_cmds->cnt++;
    memset(cmd, 0, sizeof(LocationExpressionCommand));
    cmd->cmd = op;
    return cmd;
}

int get_location_info(const Symbol * sym, LocationInfo ** loc) {
    DWORD dword = 0;
    static VARIANT data;
    SYMBOL_INFO * info = NULL;

    assert(sym->magic == SYMBOL_MAGIC);
    *loc = (LocationInfo *)tmp_alloc_zero(sizeof(LocationInfo));
    location_cmds = &(*loc)->value_cmds;

    if (sym->address != 0) {
        add_location_command(SFT_CMD_NUMBER)->args.num = sym->address;
        return 0;
    }

    if (sym->base || sym->info) {
        errno = ERR_INV_CONTEXT;
        return -1;
    }

    if (get_sym_info(sym, sym->index, &info) < 0) return -1;

    if (is_frame_relative(info)) {
        add_location_command(SFT_CMD_FP);
        add_location_command(SFT_CMD_NUMBER)->args.num =
            info->Address - context_word_size(sym->ctx) * 2;
        add_location_command(SFT_CMD_ADD);
        return 0;
    }

    if (is_register(info)) {
        RegisterDefinition * def = NULL;
        /* Register numbers are defined in cvconst.h */
        if (info->Register < 40) {
            static const char * reg_names[] = {
                NULL, "AL", "CL", "DL", "BL", "AH", "CH", "DH", "BH", "AX",
                "CX", "DX", "BX", "SP", "BP", "SI", "DI", "EAX", "ECX", "EDX",
                "EBX", "ESP", "EBP", "ESI", "EDI", "ES", "CS", "SS", "DS", "FS",
                "GS", "IP", "FLAGS", "EIP", "EFLAGS", NULL, NULL, NULL, NULL, NULL,
            };
            def = find_register(sym->ctx, reg_names[info->Register]);
        }
        else if (info->Register >= 328 && info->Register <= 343) {
            static const char * reg_names[] = {
                "RAX", "RBX", "RCX", "RDX", "RSI", "RDI", "RBP", "RSP",
                "R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15"
            };
            def = find_register(sym->ctx, reg_names[info->Register - 328]);
        }
        if (def != NULL) {
            LocationExpressionCommand * cmd = add_location_command(SFT_CMD_PIECE);
            cmd->args.piece.reg = def;
            cmd->args.piece.bit_size = def->size * 8;
            return 0;
        }
        set_errno(ERR_OTHER, "Unknown register index");
        return -1;
    }

    if (get_type_info(sym, TI_GET_OFFSET, &dword) == 0) {
        DWORD bit = 0;
        add_location_command(SFT_CMD_ARG)->args.arg_no = 0;
        add_location_command(SFT_CMD_NUMBER)->args.num = dword;
        add_location_command(SFT_CMD_ADD);
        if (get_type_info(sym, TI_GET_BITPOSITION, &bit) == 0) {
            LocationExpressionCommand * cmd = add_location_command(SFT_CMD_PIECE);
            cmd->args.piece.bit_offs = bit;
            cmd->args.piece.bit_size = info->Size;
        }
        (*loc)->args_cnt = 1;
        return 0;
    }

    if (get_type_info(sym, TI_GET_VALUE, &data) == 0) {
        VARTYPE vt;
        void * data_addr = &data.bVal;
        size_t data_size = 0;
        LocationExpressionCommand * cmd = NULL;

        assert(data_addr == &data.lVal);

        vt = data.vt;
        if (vt & VT_BYREF) {
            data_addr = *(void **)data_addr;
            vt &= ~VT_BYREF;
        }

        switch (vt) {
        /*    VOID           */ case 0:             break;
        /*    CHAR           */ case VT_I1:         data_size = 1; break;
        /*    SHORT          */ case VT_I2:         data_size = 2; break;
        /*    LONG           */ case VT_I4:         data_size = 4; break;
        /*    LONGLONG       */ case VT_I8:         data_size = 8; break;
        /*    INT            */ case VT_INT:        data_size = sizeof(int); break;
        /*    BYTE           */ case VT_UI1:        data_size = 1; break;
        /*    USHORT         */ case VT_UI2:        data_size = 2; break;
        /*    ULONG          */ case VT_UI4:        data_size = 4; break;
        /*    ULONGLONG      */ case VT_UI8:        data_size = 8; break;
        /*    UINT           */ case VT_UINT:       data_size = sizeof(unsigned int); break;
        /*    FLOAT          */ case VT_R4:         data_size = 4; break;
        /*    DOUBLE         */ case VT_R8:         data_size = 8; break;
        /*    VARIANT_BOOL   */ case VT_BOOL:       data_size = sizeof(BOOL); break;
        /*    SCODE          */ case VT_ERROR:      data_size = sizeof(ERROR); break;
        /*    CY             */ case VT_CY:         data_size = sizeof(CY); break;
        /*    DATE           */ case VT_DATE:       data_size = sizeof(DATE); break;
        /*    BSTR           */ case VT_BSTR:       data_size = sizeof(BSTR); break;
        /*    IUnknown *     */ case VT_UNKNOWN:    data_size = sizeof(IUnknown *); break;
        /*    IDispatch *    */ case VT_DISPATCH:   data_size = sizeof(IDispatch *); break;
        /*    SAFEARRAY *    */ case VT_ARRAY:      data_size = sizeof(SAFEARRAY *); break;
        /*    VARIANT        */ case VT_VARIANT:    data_size = sizeof(VARIANT); break;
        /*    DECIMAL        */ case VT_DECIMAL:    data_size = sizeof(DECIMAL); break;
        }

        cmd = add_location_command(SFT_CMD_PIECE);
        cmd->args.piece.bit_size = data_size * 8;
        cmd->args.piece.value = tmp_alloc(data_size);
        memcpy(cmd->args.piece.value, data_addr, data_size);
        return 0;
    }

    add_location_command(SFT_CMD_NUMBER)->args.num = info->Address;
    return 0;
}

int get_stack_tracing_info(Context * ctx, ContextAddress addr, StackTracingInfo ** info) {
    *info = NULL;
    return 0;
}

int get_funccall_info(const Symbol * func,
        const Symbol ** args, unsigned args_cnt, FunctionCallInfo ** res) {
    FunctionCallInfo * info = (FunctionCallInfo *)tmp_alloc_zero(sizeof(FunctionCallInfo));
    Symbol * type = (Symbol *)func;
    DWORD tag = 0;
    DWORD cc = 0;

    assert(func->magic == SYMBOL_MAGIC);
    if (func->base || func->info) {
        errno = ERR_INV_CONTEXT;
        return -1;
    }
    if (get_type_info(func, TI_GET_SYMTAG, &tag) < 0) return -1;
    if (tag == SymTagFunction && get_symbol_type(func, &type) < 0) return -1;
    if (get_type_info(type, TI_GET_CALLING_CONVENTION, &cc) < 0) return -1;
#if defined(__x86_64__)
    info->scope.machine = 62; /* EM_X86_64 */
    info->scope.elf64 = 1;
#else
    info->scope.machine = 3; /* EM_386 */
#endif
    info->scope.os_abi = (uint8_t)cc;
    info->scope.id_type = REGNUM_DWARF;
    info->ctx = func->ctx;
    info->func = func;
    info->args_cnt = args_cnt;
    info->args = args;
    if (get_function_call_location_expression(info) < 0) return -1;
    *res = info;
    return 0;
}

int get_symbol_file_info(Context * ctx, ContextAddress addr, SymbolFileInfo ** res) {
    char * name = NULL;
    IMAGEHLP_MODULEW64 info;
    HANDLE process = get_context_handle(context_get_group(ctx, CONTEXT_GROUP_PROCESS));

    *res = NULL;
    memset(&info, 0, sizeof(info));
    info.SizeOfStruct = sizeof(info);
    if (!SymGetModuleInfoW64(process, addr, &info)) {
        set_win32_errno(GetLastError());
        return -1;
    }
    if (wchar_to_utf8(info.LoadedImageName, &name) < 0) return -1;
    if (info.LoadedImageName[0] != 0) {
        *res = (SymbolFileInfo *)tmp_alloc_zero(sizeof(SymbolFileInfo));
        (*res)->file_name = tmp_strdup(name);
        (*res)->addr = (ContextAddress)info.BaseOfImage;
        (*res)->size = (ContextAddress)info.ImageSize;
    }
    return 0;
}

static void event_context_exited(Context * ctx, void * client_data) {
    unsigned i;
    SymbolCacheEntry ** symbol_cache = EXT(ctx)->symbol_cache;
    if (symbol_cache == NULL) return;
    for (i = 0; i < SYMBOL_CACHE_SIZE; i++) {
        while (symbol_cache[i] != NULL) {
            SymbolCacheEntry * entry = symbol_cache[i];
            symbol_cache[i] = entry->next;
            release_error_report(entry->error);
            loc_free(entry);
        }
    }
    loc_free(symbol_cache);
    EXT(ctx)->symbol_cache = NULL;
}

static void event_module_loaded(Context * ctx, void * client_data) {
    unsigned i;
    SymbolCacheEntry ** symbol_cache = EXT(ctx)->symbol_cache;
    assert(ctx->mem == ctx);
    if (symbol_cache == NULL) return;
    for (i = 0; i < SYMBOL_CACHE_SIZE; i++) {
        SymbolCacheEntry * prev = NULL;
        SymbolCacheEntry * next = symbol_cache[i];
        while (next != NULL) {
            SymbolCacheEntry * entry = next;
            next = next->next;
            if (entry->error) {
                if (prev) prev->next = next;
                else symbol_cache[i] = next;
                release_error_report(entry->error);
                loc_free(entry);
            }
            else {
                prev = entry;
            }
        }
    }
}

static void event_module_unloaded(Context * ctx, void * client_data) {
    unsigned i;
    SymbolCacheEntry ** symbol_cache = EXT(ctx)->symbol_cache;
    if (symbol_cache == NULL) return;
    for (i = 0; i < SYMBOL_CACHE_SIZE; i++) {
        while (symbol_cache[i] != NULL) {
            SymbolCacheEntry * entry = symbol_cache[i];
            symbol_cache[i] = entry->next;
            release_error_report(entry->error);
            loc_free(entry);
        }
    }
}

#if ENABLE_SymbolsMux
static int reader_is_valid(Context * ctx, ContextAddress addr) {
    IMAGEHLP_MODULEW64 info;
    HANDLE process = get_context_handle(context_get_group(ctx, CONTEXT_GROUP_PROCESS));
    memset(&info, 0, sizeof(info));
    info.SizeOfStruct = sizeof(info);
    if (!SymGetModuleInfoW64(process, addr, &info)) return 0;
    return info.LoadedImageName[0] != 0;
}
#endif

void ini_symbols_lib(void) {
    static ContextEventListener ctx_listener = {
        NULL,
        event_context_exited,
    };
    static MemoryMapEventListener map_listener = {
        event_module_loaded,
        NULL,
        event_module_unloaded
    };
    add_context_event_listener(&ctx_listener, NULL);
    add_memory_map_event_listener(&map_listener, NULL);
    SymSetOptions(SymGetOptions() | SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS);
    context_extension_offset = context_extension(sizeof(ContextExtensionWinSym));
#if ENABLE_SymbolsMux
    add_symbols_reader(&symbol_reader);
#endif
}


#endif /* SERVICE_Symbols && (!ENABLE_SymbolsProxy || ENABLE_LineNumbersMux) && ENABLE_PE */
