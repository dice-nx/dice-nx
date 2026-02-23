/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <exec/types.h>
#include <exec/memory.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define buf ((long *)vbuf)

void *
realloc(vbuf, bytes)
void *vbuf;
size_t bytes;
{
    void *ptr = NULL;
    int copy;

    if (bytes <= 0 && buf) {
        free(buf);
        return(NULL);
    }
    if (buf) {
        copy = buf[-1] - 8;
        if (bytes <= copy)
            return(buf);
    }
    ptr = malloc(bytes);
    if (ptr && buf) {
        movmem(buf, ptr, copy);
        free(buf);
    }
    return(ptr);
}
