/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <string.h>

typedef unsigned char ubyte;

#ifndef HYPER
#define HYPER(x) x
#endif

char *
HYPER(strncat)(d, s, n)
char *d;
const char *s;
size_t n;
{
    char c;
    char *base= d;

    s;
    n;

    if (n) {
        d += strlen(d);
        while (c = *s) {
            *d = c;
            ++s;
            ++d;
            if (--n == 0)
                break;
        }
    }
    *d = 0;
    return(base);
}

