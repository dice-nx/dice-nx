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
scanf(ctl, ...)
const char *ctl;
{
    int error;
    int cnt;
    va_list va;

    va_start(va, ctl);
    error = _sfmt(ctl, va, fgetc, ungetc, stdin, &cnt);
    va_end(va);
    if (error)
        return(error);
    return(cnt);
}

