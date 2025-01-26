/*
 * DICE-NX project - https://dice-nx.dev/
 *
 * Copyright 1992-1997 Obvious Implementations Corp.
 * Copyright 2023- DICE-NX project contributors
 *
 * Licensed under the BSD-3-Clause License, as written in the LICENSE file
 * at the root of this project.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * LOCATEPATH.C
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

