/*
 * DICE-NX project - https://dice-nx.dev/
 *
 * Copyright 1990 Matthew Dillon
 * Copyright 2023- DICE-NX project contributors
 *
 * Licensed under the BSD-3-Clause License, as written in the LICENSE file
 * at the root of this project.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


/*
 *  STRICMP.C
 */

#include <string.h>
#define CTYPE_NEAR
#include <ctype.h>

#ifndef HYPER
#define HYPER(x) x
#endif

typedef unsigned char ubyte;

int
HYPER(stricmp)(const char *s, const char *d)
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


