/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <exec/types.h>
#include <clib/exec_protos.h>

#include <stdio.h>
#include <fcntl.h>
#include <time.h>

int
pipe(fda)
int *fda;
{
    static short Cnt;
    char baseName[64];
    char buf[64];

    sprintf(baseName, "FIFO:%07lx.%06lx.%04lx", FindTask(NULL) >> 4, time(NULL), Cnt++);

    sprintf(buf, "%s/r", baseName);
    fda[0] = open(buf, O_CREAT|O_TRUNC|O_RDONLY|O_BINARY);

    sprintf(buf, "%s/wmeK", baseName);
    fda[1] = open(buf, O_CREAT|O_TRUNC|O_WRONLY|O_BINARY);

    if (fda[0] < 0 || fda[1] < 0) {
        if (fda[0] >= 0)
            close(fda[0]);
        if (fda[1] >= 0)
            close(fda[1]);
        fda[0] = fda[1] = -1;
        return(-1);
    }
    return(0);
}

