/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * tmpfile()       - create a temporary file that is deleted on
 * close
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *
tmpfile()
{
    char *name;
    FILE *fi;

    if (name = strdup(tmpnam(NULL))) {
        if (fi = fopen(name, "wb+C"))
            return(fi);
        free(name);
    }
    return(NULL);
}

