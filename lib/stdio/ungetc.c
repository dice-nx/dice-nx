/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <stdio.h>

int
ungetc(c, fi)
int c;
FILE *fi;
{
    if (fi->sd_UC < 0) {
        fi->sd_UC = c;
        return(c);
    }
    return(EOF);
}

