/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <clib/dos_protos.h>
#include <stdio.h>
#include <fcntl.h>
#include <ioctl.h>
#include <errno.h>

long
lseek(fd, offset, whence)
int fd;
long offset;
int whence;
{
    _IOFDS *d;
    int n = -1;

    if (d = __getfh(fd)) {
        if (d->fd_Exec)
            return((*d->fd_Exec)(d->fd_Fh, IOC_SEEK, (void *)offset, (void *)whence));
        n = Seek(d->fd_Fh, offset, whence-1);
        if (n >= 0) {
            if (offset || whence != 1)
                n = Seek(d->fd_Fh, 0L, 0);
            return(n);
        }
    }
    return(n);
}

