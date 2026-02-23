/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <exec/types.h>
#include <exec/libraries.h>
#include <dos/dos.h>
#include <clib/dos_protos.h>

#ifndef UnixToAmigaPath
#define UnixToAmigaPath(path)   path
#endif

extern struct DosLibrary *DOSBase;

int
symlink(fileName, linkName)
char *fileName;
char *linkName;
{
    int r = -1;

    if (DOSBase->dl_lib.lib_Version >= 37) {
        if (MakeLink(UnixToAmigaPath(linkName), (long)UnixToAmigaPath(fileName), 1))
            r = 0;
    }
    return(r);
}

