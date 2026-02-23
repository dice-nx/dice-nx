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
HYPER(strpbrk)(str, toks)
const char *str;
const char *toks;
{
    char c;

    while (c = *str) {
        const char *p = toks;
        while (*p) {
            if (*p == c)
                return(str);
            ++p;
        }
        ++str;
    }
    return(NULL);
}

