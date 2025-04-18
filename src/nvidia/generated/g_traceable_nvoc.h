
#ifndef _G_TRACEABLE_NVOC_H_
#define _G_TRACEABLE_NVOC_H_

// Version of generated metadata structures
#ifdef NVOC_METADATA_VERSION
#undef NVOC_METADATA_VERSION
#endif
#define NVOC_METADATA_VERSION 2

#include "nvoc/runtime.h"
#include "nvoc/rtti.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * SPDX-FileCopyrightText: Copyright (c) 2011-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#pragma once
#include "g_traceable_nvoc.h"

#ifndef __ANCI_TRACEABLE_H__
#define __ANCI_TRACEABLE_H__

#include "core/core.h"
#include "nvoc/object.h"


// Private field names are wrapped in PRIVATE_FIELD, which does nothing for
// the matching C source file, but causes diagnostics to be issued if another
// source file references the field.
#ifdef NVOC_TRACEABLE_H_PRIVATE_ACCESS_ALLOWED
#define PRIVATE_FIELD(x) x
#else
#define PRIVATE_FIELD(x) NVOC_PRIVATE_FIELD(x)
#endif


// Metadata with per-class RTTI
struct NVOC_METADATA__OBJTRACEABLE;


struct OBJTRACEABLE {

    // Metadata starts with RTTI structure.
    union {
         const struct NVOC_METADATA__OBJTRACEABLE *__nvoc_metadata_ptr;
         const struct NVOC_RTTI *__nvoc_rtti;
    };

    // Ancestor object pointers for `staticCast` feature
    struct OBJTRACEABLE *__nvoc_pbase_OBJTRACEABLE;    // traceable
};


// Metadata with per-class RTTI
struct NVOC_METADATA__OBJTRACEABLE {
    const struct NVOC_RTTI rtti;
};

#ifndef __NVOC_CLASS_OBJTRACEABLE_TYPEDEF__
#define __NVOC_CLASS_OBJTRACEABLE_TYPEDEF__
typedef struct OBJTRACEABLE OBJTRACEABLE;
#endif /* __NVOC_CLASS_OBJTRACEABLE_TYPEDEF__ */

#ifndef __nvoc_class_id_OBJTRACEABLE
#define __nvoc_class_id_OBJTRACEABLE 0x6305d2
#endif /* __nvoc_class_id_OBJTRACEABLE */

// Casting support
extern const struct NVOC_CLASS_DEF __nvoc_class_def_OBJTRACEABLE;

#define __staticCast_OBJTRACEABLE(pThis) \
    ((pThis)->__nvoc_pbase_OBJTRACEABLE)

#ifdef __nvoc_traceable_h_disabled
#define __dynamicCast_OBJTRACEABLE(pThis) ((OBJTRACEABLE*) NULL)
#else //__nvoc_traceable_h_disabled
#define __dynamicCast_OBJTRACEABLE(pThis) \
    ((OBJTRACEABLE*) __nvoc_dynamicCast(staticCast((pThis), Dynamic), classInfo(OBJTRACEABLE)))
#endif //__nvoc_traceable_h_disabled

NV_STATUS __nvoc_objCreateDynamic_OBJTRACEABLE(OBJTRACEABLE**, Dynamic*, NvU32, va_list);

NV_STATUS __nvoc_objCreate_OBJTRACEABLE(OBJTRACEABLE**, Dynamic*, NvU32);
#define __objCreate_OBJTRACEABLE(ppNewObj, pParent, createFlags) \
    __nvoc_objCreate_OBJTRACEABLE((ppNewObj), staticCast((pParent), Dynamic), (createFlags))

#undef PRIVATE_FIELD


void objTraverseCaptureState_IMPL(struct Object *pObj);
#define objTraverseCaptureState(p) objTraverseCaptureState_IMPL(staticCast((p), Object))

#endif // __ANCI_TRACEABLE_H__

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _G_TRACEABLE_NVOC_H_
