/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <stdio.h>

int
fsetpos(fp, pos)
FILE *fp;
const fpos_t *pos;
{
    if (fseek(fp, *pos, 0) < 0)
        return(EOF);
    return(0);
}

