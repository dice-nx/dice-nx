/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <stdio.h>

int
fgetpos(fp, pos)
FILE *fp;
fpos_t *pos;
{
    *pos = ftell(fp);
    if (*pos < 0)
        return(EOF);
    return(0);
}

