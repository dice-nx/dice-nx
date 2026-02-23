/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <stddef.h>
#include <string.h>

#ifndef HYPER
#define HYPER(x) x
#endif

char *
HYPER(strrchr)(toks, c)
const char *toks;
int c;
{
    const char *ptr = toks + strlen(toks);

    while (ptr > toks && *ptr != (char)c)
        --ptr;
    if (*ptr == (char)c)
        return(ptr);
    return(NULL);
}

