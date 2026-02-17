/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

#include <stdlib.h>
#include <libc.h>
#include <sys/param.h>

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

