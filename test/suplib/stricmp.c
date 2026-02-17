/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * (C)Copyright 1990, Matthew Dillon, All Rights Reserved
 */

#include <string.h>
#define CTYPE_NEAR
#include <ctype.h>

#ifndef HYPER
#define HYPER(x) x
#endif

typedef unsigned char ubyte;

int
HYPER(stricmp)(s, d)
const char *s;
const char *d;
{
    while (tolower(*(ubyte *)s) == tolower(*(ubyte *)d)) {
        if (*s == 0)
            return(0);
        ++s;
        ++d;
    }
    if (tolower(*(ubyte *)s) < tolower(*(ubyte *)d))
        return(-1);
    return(1);
}


