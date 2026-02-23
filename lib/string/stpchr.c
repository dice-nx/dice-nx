/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <stdio.h>
#include <string.h>

#ifndef HYPER
#define HYPER(x) x
#endif

const char *
HYPER(stpchr)(str, c)
const char *str;
char c;
{
    char cc;

    while (cc = *str) {
        if (cc == c)
            return(str);
        ++str;
    }
    if (cc == c)
        return(str);
    return(NULL);
}

