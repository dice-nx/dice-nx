/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <stdarg.h>
#include <stdio.h>
#include <lib/misc.h>

int
vfprintf(fi, ctl, va)
FILE *fi;
const char *ctl;
va_list va;
{
    int error;

    error = _pfmt(ctl, va, fwrite, fi);
    va_end(va);
    return(error);      /*  count/error */
}

