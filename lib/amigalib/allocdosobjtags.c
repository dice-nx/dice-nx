/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * AllocDosObjectTags
 */

#include <exec/types.h>
#include <utility/tagitem.h>
#include <clib/dos_protos.h>

#ifndef HYPER
#define HYPER
#endif

typedef struct TagItem   TagItem;

APTR
HYPER ## AllocDosObjectTags(type, tag1, ...)
unsigned long type;
Tag tag1;
{
    return(AllocDosObject(type, (TagItem *)&tag1));
}

