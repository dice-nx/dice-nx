/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * TMPNAM()
 */

#include <clib/exec_protos.h>
#include <stdio.h>

char *
tmpnam(buf)
char *buf;
{
    static char Buf[L_tmpnam];
    static long i;

    if (buf == NULL)
        buf = Buf;
    sprintf(buf, "T:%08lx-%ld", FindTask(NULL), i++);
    return(buf);
}

