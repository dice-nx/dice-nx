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
#include <stdlib.h>

extern long *__MemList;

void
free(ptr)
void *ptr;
{
    long **scan = &__MemList;
    long *item;

    if (ptr == NULL)
        return;

    ptr = (void *)((long *)ptr - 2);

    while (item = *scan) {
        if (item == (long *)ptr) {
            *scan = *(long **)item;
            FreeMem(ptr, ((long *)ptr)[1]);
            return;
        }
        scan = (long **)item;
    }
    Wait(0);
}

