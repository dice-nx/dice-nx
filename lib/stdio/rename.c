/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <clib/dos_protos.h>
#include <stdio.h>
#include <errno.h>

int
rename(s, d)
const char *s;
const char *d;
{
    if (Rename(s, d))
        return(0);
    errno = ENOFILE;
    return(-1);
}

