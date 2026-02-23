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

static int
_sgetc(sst)
unsigned char **sst;
{
    unsigned char *ptr = *sst;
    if (*ptr) {
        *sst = ptr + 1;
        return(*ptr);
    }
    return(EOF);
}

static int
_sungetc(c, sst)
int c;
unsigned char **sst;
{
    --*sst;
}

int
sscanf(buf, ctl, ...)
char *buf;
const char *ctl;
{
    char *ptr = buf;
    int error;
    int cnt;
    va_list va;

    va_start(va, ctl);
    error = _sfmt(ctl, va, _sgetc, _sungetc, &ptr, &cnt);
    va_end(va);
    if (error)
        return(error);
    return(cnt);
}

