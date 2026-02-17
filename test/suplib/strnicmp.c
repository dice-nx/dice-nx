/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * (C)Copyright 1990, Matthew Dillon, All Rights Reserved
 */

#include <string.h>
#include <ctype.h>

#ifndef HYPER
#define HYPER(x) x
#endif

typedef unsigned char ubyte;

int
HYPER(strnicmp)(s, d, n)
const char *s;
const char *d;
int n;
{
    ubyte c;

    if (n == 0)
        return(0);

    while (tolower(c = *s) == tolower(*(ubyte *)d)) {
        if (c == 0 || --n == 0)
            return(0);
        ++s;
        ++d;
    }
    if (tolower(c) < tolower(*(ubyte *)d))
        return(-1);
    return(1);
}

