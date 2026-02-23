/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <string.h>

#ifndef HYPER
#define HYPER(x) x
#endif

typedef unsigned char ubyte;

int
HYPER(strcmp)(s, d)
const char *s;
const char *d;
{
    while (*(ubyte *)s == *(ubyte *)d) {
        if (*s == 0)
            return(0);
        ++s;
        ++d;
    }
    if (*(ubyte *)s < *(ubyte *)d)
        return(-1);
    return(1);
}

