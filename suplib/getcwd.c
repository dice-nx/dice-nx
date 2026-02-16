/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp.
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
