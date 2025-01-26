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

#include <stdlib.h>
#include <unistd.h>
#include <sys/param.h>

#ifdef next
#include <libc.h>

char *
getcwd(char *buf, int maxlen)
{
    char xbuf[MAXPATHLEN];

    if (getwd(xbuf)) {
        strncpy(buf, xbuf, maxlen);
        return(buf);
    } else {
        return(NULL);
    }
}

#endif
