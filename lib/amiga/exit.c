/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <exec/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <lib/atexit.h>
#include <lib/misc.h>
#include <libraries/dosextens.h>

typedef struct Process Process;

extern long *__MemList;
AtExit *_ExitBase = NULL;

void
exit(code)
int code;
{
    {
        AtExit *eb;
        for (eb = _ExitBase; eb; eb = eb->Next)
            (*eb->Func)();
    }

    fclose(stdin);
    fclose(stdout);
    fclose(stderr);

    /*
     *  stdio
     */

    while (_Iod)
        fclose(_Iod);

    /*
     *  file descriptors
     */

    __closeall();

    /*
     *  low level exit (handles allocated memory & workbench)
     */

    _exit(code);
}

