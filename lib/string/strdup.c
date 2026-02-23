/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <string.h>
#include <stdlib.h>

char *
strdup(s)
const char *s;
{
    int len = strlen(s);
    char *d;

    if (d = malloc(len + 1))
        strcpy(d, s);
    return(d);
}

