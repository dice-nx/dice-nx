/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <stdio.h>

long
ftell(fi)
FILE *fi;
{
    long n = fi->sd_Offset;

    if (!(fi->sd_Flags & __SIF_FILE))
        return(EOF);

    if (fi->sd_WLeft >= 0)
        return(n + (fi->sd_WPtr - fi->sd_WBuf));
    else if (fi->sd_RLeft >= 0) {
        if (fi->sd_UC >= 0)
            --n;
        return(n - fi->sd_RLeft);
    }
    return(n);
}

