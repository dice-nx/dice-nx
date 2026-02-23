/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <stdio.h>
#include <stdlib.h>
#include <ioctl.h>
#include <fcntl.h>
#include <errno.h>

int
fcntl(fd, req, arg)
int fd;
int req;
int arg;
{
    switch(req) {
    case F_DUPFD:
        return(ioctl(fd, IOC_DUP, NULL));
    case F_GETFD:
        arg = -1;
        ioctl(fd, IOF_GET|IOC_CEXEC, &arg);
        return(arg);
    case F_SETFD:
        return(ioctl(fd, IOF_SET|IOC_CEXEC, &arg));
    case F_GETFL:
        arg = -1;
        ioctl(fd, IOF_GET|IOC_MODES, &arg);
        return(arg);
    case F_SETFL:
        return(ioctl(fd, IOF_SET|IOC_MODES, &arg));
    }
    errno = EBADF;
    return(-1);
}


