/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <stdio.h>
#include <stdlib.h>
#include <lib/atexit.h>

int
atexit(func)
void (*func)(void);
{
    AtExit *at = malloc(sizeof(AtExit));

    if (at) {
        at->Next = _ExitBase;
        at->Func = func;
        _ExitBase = at;
        return(0);
    }
    return(-1);
}


