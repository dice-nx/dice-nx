/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * PRINTF.C    dos.library var-args interface to VPrintf()
 */

#include <stdio.h>
#include <stdarg.h>
#include <exec/types.h>
#include <clib/dos_protos.h>

LONG
Printf( CONST_STRPTR ctl, ... )
{
    va_list va;
    int n;

    va_start(va, ctl);
    n = VPrintf(ctl, va);
    va_end(va);
    return(n);
}

