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
vprintf(ctl, va)
const char *ctl;
va_list va;
{
    int error;

    error = _pfmt(ctl, va, fwrite, stdout);
    return(error);      /*  count/error     */
}

