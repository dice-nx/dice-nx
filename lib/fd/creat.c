/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * creat(name, prot)   (prot ignored)
 */

#include <fcntl.h>

#ifndef UnixToAmigaPath
#define UnixToAmigaPath(path)   path
#endif

int
creat(name, mode)
const char *name;
int mode;
{
    return(open(UnixToAmigaPath(name), O_CREAT | O_TRUNC | O_RDWR, mode));
}

