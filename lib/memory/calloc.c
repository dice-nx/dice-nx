/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * calloc(elmsize, elms)
 */

#include <stdlib.h>
#include <string.h>

void *
calloc(elmSize, elms)
size_t elmSize;
size_t elms;
{
    void *ptr;
    long bytes = elmSize * elms;

    if (ptr = malloc(bytes))
        clrmem(ptr, bytes);
    return(ptr);
}

