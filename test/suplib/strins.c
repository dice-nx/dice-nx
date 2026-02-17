/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

#include <stdlib.h>
#include <string.h>

void
strins(d, s)
char *d;
const char *s;
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

