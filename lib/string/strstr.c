/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * STRSTR.C        find one string in another
 */

#include <string.h>
#include <errno.h>

#ifndef HYPER
#define HYPER(x) x
#endif

char *
HYPER(strstr)(s1, s2)
const char *s1;
const char *s2;
{
    short len2 = strlen(s2);

    if (len2 == 0)
        return(s1);

    while (*s1) {
        if (*s1 == *s2 && strncmp(s1, s2, len2) == 0)
            return(s1);
        ++s1;
    }
    return(NULL);
}

