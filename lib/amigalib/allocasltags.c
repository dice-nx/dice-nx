/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * AllocAslRequestTags
 */

#include <exec/types.h>
#include <clib/asl_protos.h>
#include <stdarg.h>

#ifndef HYPER
#define HYPER
#endif

APTR
HYPER ## AllocAslRequestTags(ULONG type, ...)
{
    va_list va;
    va_start(va, type);
    APTR ret = AllocAslRequest(type, (CONST struct TagItem *)va);
    va_end(va);
    return ret;
}

