/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * AslRequestTags
 */

#include <exec/types.h>
#include <clib/asl_protos.h>
#include <stdarg.h>

#ifndef HYPER
#define HYPER
#endif

typedef struct TagItem   TagItem;

BOOL
HYPER ## AslRequestTags( APTR requester, ... )
{
    va_list va;
    va_start(va, requester);
    BOOL ret = AslRequest(requester, (TagItem *)va);
    va_end(va);
    return ret;
}

