/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * tag'd to here allowing math library to override pfmt.
 */

#include <stdarg.h>
#include <stdio.h>
#include <lib/misc.h>

int
printf(ctl, ...)
const char *ctl;
{
    int error;
    va_list va;

    va_start(va, ctl);
    error = _pfmt(ctl, va, fwrite, stdout);
    va_end(va);
    return(error);      /*  count/error */
}

