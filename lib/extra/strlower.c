/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * Convert string to lower case
 */

#ifndef HYPER
#define HYPER(x) x
#endif

char *
HYPER(strlower)(str)
char *str;
{
    char c;
    char *base = str;

    while (c = *str) {
        if (c >= 'A' && c <= 'Z')
            *str = c + ('a' - 'A');
        ++str;
    }
    return(base);
}


