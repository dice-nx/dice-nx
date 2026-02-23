/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <stdio.h>
#include <fcntl.h>

int
fputc(c, fi)
unsigned char c;
FILE *fi;
{
    unsigned char cc = c;

    if (fi == NULL)
        return(-1);
    if (fi->sd_Flags & __SIF_WRITE) {
        if (fi->sd_WLeft <= 0) {
            if (fi->sd_BufSiz == 0) {               /*  unbuffered  */
                if (write(fi->sd_Fd, &cc, 1) != 1)
                    fi->sd_Error = EOF;
                ++fi->sd_Offset;
                if (fi->sd_Error < 0)
                    return(fi->sd_Error);
                return(c);
            }
            if (fflush(fi))                         /*  not unbuffered */
                return(EOF);
        }
        *fi->sd_WPtr++ = c;
        --fi->sd_WLeft;
        if (c == '\n' && (fi->sd_Flags & __SIF_IOLBF))
            fflush(fi);
    } else {
        fi->sd_Error = EOF;
    }
    if (fi->sd_Error < 0)
        return(fi->sd_Error);
    return(c);
}

