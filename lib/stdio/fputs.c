/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * fputs.c
 */

#include <stdio.h>
#include <string.h>

int
fputs(ptr, fi)
const char *ptr;
FILE *fi;
{
    fwrite(ptr, strlen(ptr), 1, fi);
    return(fi->sd_Error);
}

