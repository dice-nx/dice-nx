/*
 * DICE-NX project - https://dice-nx.dev/
 *
 * Copyright 1992-1997 Obvious Implementations Corp.
 * Copyright 2023- DICE-NX project contributors
 *
 * Licensed under the BSD-3-Clause License, as written in the LICENSE file
 * at the root of this project.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdlib.h>
#include <string.h>

void
strins(char *d, const char *s)
{
    int len = strlen(s);    /*  # bytes to insert   */
    char *ptr;

    /*
     *  make room
     */

    ptr = d + strlen(d);
    while (ptr >= d) {
        ptr[len] = ptr[0];
        --ptr;
    }

    /*
     *  insert string
     */

    while (*s)
        *++ptr = *s++;
}

