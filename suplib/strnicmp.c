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
 *  STRNICMP.C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef HYPER
#define HYPER(x) x
#endif

typedef unsigned char ubyte;

int
HYPER(strnicmp)(const char *s, const char *d, int n)
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

