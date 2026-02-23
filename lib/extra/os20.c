/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * OS20.C
 */

#include <exec/types.h>
#include <exec/libraries.h>
#include <clib/dos_protos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern struct Library *SysBase;

void
OS2_0()
{
    char *str = "Runs under 2.0 only\n";

    if (SysBase->lib_Version < 36) {
        Write(Output(), str, strlen(str));
        exit(1);
    }
}

