/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <exec/types.h>
#include <exec/memory.h>
#include <clib/exec_protos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern long *__MemList;

void *
malloc(bytes)
size_t bytes;
{
    long *ptr;

    if (bytes == 0)
        return(NULL);

    ptr = AllocMem(bytes + 8, MEMF_PUBLIC);
    if (ptr) {
        ptr[0] = (long)__MemList;
        __MemList = ptr;
        ptr[1] = bytes + 8;
        ptr += 2;
    } else {
        errno = ENOMEM;
    }
    return((void *)ptr);
}

