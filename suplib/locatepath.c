/*
 * LOCATEPATH.C
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <include/lib/version.h>

char *
LocatePath(const char *envvar, const char *fname)
{
    char path[128];
    char *ptr;

    if ((ptr = getenv(envvar)) != NULL)
        return(ptr);
    if ((ptr = getenv("DCC")) != NULL) {
        snprintf(path, sizeof(path), "%s/config/%s", ptr, fname);
    } else {
        snprintf(path, sizeof(path), INSTDIR "config/%s", fname);
    }
    return(strdup(path));
}

