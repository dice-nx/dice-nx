/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <exec/types.h>
#include <libraries/dos.h>
#include <clib/dos_protos.h>
#include <stdio.h>
#include <stdlib.h>

void
sleep(n)
int n;
{
    while (n) {
        Delay(50);
        chkabort();
        --n;
    }
}

