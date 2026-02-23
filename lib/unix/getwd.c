/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char *
getwd(buf)
char *buf;
{
    char *path;

    if (path = getcwd(buf, 256))
        return(path);
    strcpy(buf, strerror(errno));
    return(NULL);
}

