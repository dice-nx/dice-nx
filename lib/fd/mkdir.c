/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <clib/dos_protos.h>
#include <exec/types.h>
#include <libraries/dos.h>
#include <errno.h>

#ifndef UnixToAmigaPath
#define UnixToAmigaPath(path)   path
#endif

int
mkdir(fileName)
const char *fileName;
{
    BPTR lock;
    int error;

    if (lock = CreateDir(UnixToAmigaPath(fileName))) {
        UnLock(lock);
        return(0);
    }
    error = IoErr();
    if (error == ERROR_OBJECT_EXISTS || error == ERROR_DIRECTORY_NOT_EMPTY)
        errno = EEXIST;
    else
        errno = ENOFILE;
    return(-1);
}

