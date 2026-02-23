/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <clib/dos_protos.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ioctl.h>
#include <errno.h>

int
write(fd, buf, bytes)
int fd;
const void *buf;
unsigned int bytes;
{
    _IOFDS *d;
    int n = -1;

    chkabort();
    if (d = __getfh(fd)) {
        if (d->fd_Flags & (O_WRONLY|O_RDWR|O_APPEND)) {
            if (d->fd_Exec)
                return((*d->fd_Exec)(d->fd_Fh, IOC_WRITE, buf, (void *)bytes));

            if (d->fd_Flags & O_APPEND)
                Seek(d->fd_Fh, 0L, 1);
            n = Write(d->fd_Fh, buf, bytes);
        } else {
            errno = ENOPERM;
        }
    }
    return(n);
}

