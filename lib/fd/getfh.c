/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

_IOFDS *
__getfh(ifd)
int ifd;
{
    _IOFDS *d;
    short fd = ifd;

    if(ifd == (int)stdin)d = &_IoStaticFD[0];
    else if (ifd == (int)stdout)d = &_IoStaticFD[1];
    else if (ifd == (int)stderr)d = &_IoStaticFD[2];
    else if ((unsigned)fd >= _IoFDLimit) {
        errno = EBADF;
        return(NULL);
    }
    else d = _IoFD + fd;

    if ((d->fd_Flags & O_ISOPEN) == 0) {
        errno = EBADF;
        return(NULL);
    }
    return(d);
}


