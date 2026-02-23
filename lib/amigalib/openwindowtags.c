/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * OpenWindowTags
 */

#include <exec/types.h>
#include <intuition/intuition.h>
#include <clib/intuition_protos.h>

#ifndef HYPER
#define HYPER
#endif

typedef struct TagItem  TagItem;
typedef struct Window   Window;

Window *
HYPER ## OpenWindowTags(nw, tag1, ...)
struct NewWindow *nw;
Tag tag1;
{
    return(OpenWindowTagList(nw, (TagItem *)&tag1));
}

