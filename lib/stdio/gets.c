/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * buf = gets(buf)
 */

#include <stdio.h>

char *
gets(buf)
char *buf;
{
    int c;
    int cnt = 0;
    char *base = buf;

    while ((c = getc(stdin)) != EOF) {
        *buf++ = c;
        if (c != '\n' && cnt < BUFSIZ) {
            ++cnt;
            continue;
        }
        buf[-1] = 0;
        return(base);
        break;
    }
    if (buf == base)
        return(NULL);
    buf[0] = 0;
    return(base);
}

