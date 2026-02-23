/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <stdio.h>

void
setbuf(fi, buf)
FILE *fi;
char *buf;
{
    if (buf)
        setvbuf(fi, buf, _IOFBF, _bufsiz);
    else
        setvbuf(fi, NULL, _IONBF, 0);
}

