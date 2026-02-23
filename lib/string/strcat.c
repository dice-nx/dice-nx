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

char *
HYPER(strcat)(d, s)
char *d;
const char *s;
{
    char *base= d;

    while (*d)
        ++d;
    while (*d++ = *s++);
    return(base);
}

