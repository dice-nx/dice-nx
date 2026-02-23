/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * buf = fgets(buf, siz, fi)
 */

#include <stdio.h>

char *
fgets(buf, siz, fi)
char *buf;
int siz;
FILE *fi;
{
    char *base = buf;

    siz -= 2;   /*  room for \n and \0  */

    /*
     *  do a quick-scan of already-buffered chars to boost efficiency.
     *  Only handles best case.  Note that if RLeft is > 0 then __SIF_READ
     *  must be set so we don't bother to check.
     */

    if (fi && fi->sd_UC < 0 && fi->sd_RLeft > 0) {
        char *ptr = fi->sd_RPtr;
        int i = 0;

        for (i = 0; i < fi->sd_RLeft && i < siz && *ptr != '\n'; ++i)
            buf[i] = *ptr++;
        if (*ptr == '\n' && i < siz && i < fi->sd_RLeft) {
            buf[i++] = *ptr;
            fi->sd_RLeft -= i;
            fi->sd_RPtr += i;
            buf[i++] = 0;
            return(buf);
        }
    }
    if (fi) {
        int cnt = 0;
        int c;

        while ((c = getc(fi)) != EOF) {
            *buf++ = c;
            if (c != '\n' && cnt < siz) {
                ++cnt;
                continue;
            }
            break;
        }
    }
    if (buf == base)
        return(NULL);
    *buf = 0;
    return(base);
}

