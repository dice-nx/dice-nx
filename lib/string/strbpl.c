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

int
HYPER(strbpl)(av, max, sary)
char **av;
int max;
const char *sary;
{
    int i;

    for (i = 0; i < max; ++i) {
        if (*sary == 0) {
            *av++ = NULL;
            return(i);
        }
        *av++ = sary;
        while (*sary)
            ++sary;
        ++sary;
    }
    return(-1);
}

