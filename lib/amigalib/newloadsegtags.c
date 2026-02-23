/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * NewLoadSegTags
 */

#include <exec/types.h>
#include <dos/dosextens.h>
#include <utility/tagitem.h>
#include <clib/dos_protos.h>

typedef struct TagItem   TagItem;

#ifndef HYPER
#define HYPER
#endif

BPTR
HYPER ## NewLoadSegTags(file, tag1, ...)
UBYTE *file;
Tag tag1;
{
    return(NewLoadSeg(file, (TagItem *)&tag1));
}

