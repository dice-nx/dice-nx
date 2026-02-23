/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <string.h>
#include <errno.h>

int sys_nerr = 18;      /* entries in table */

char *sys_errlist[] = {
    "no error",
    "domain",                   /* EDOM */
    "range",                    /* ERANGE */
    "bad file descriptor",      /* EBADF */
    "no permission",            /* ENOPERM */
    "no memory",                /* ENOMEM */
    "file not found",           /* ENOFILE, ENOENT */
    "no access",                /* EACCES */
    "invalid argument",         /* EINVAL */
    "ran out of descriptors",   /* EMFILE */
    "try again",                /* EAGAIN */
    "connection reset by peer", /* EPEER */
    "broken pipe",              /* EPIPE */
    "file not found",           /* ENOTFND */
    "unknown error",            /* ESTACK */
    "unknown error",            /* ENOTTY */
    "unknown error",            /* ENXIO */
    "file/directory exists",    /* EEXIST */
};


char *
strerror(error)
int error;
{
    if( error < sys_nerr )
        return(sys_errlist[error]);

    return("unknown error");
}
