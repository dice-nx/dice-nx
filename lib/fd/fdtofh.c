/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <stdio.h>
#include <fcntl.h>
#include <ioctl.h>
#include <errno.h>

void *
fdtofh(fd)
int fd;
{
    _IOFDS *d;

    if (d = __getfh(fd)) {
        if (d->fd_Exec)
            return(NULL);
        return((void *)d->fd_Fh);
    }
    return(NULL);
}

