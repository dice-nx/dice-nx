/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <string.h>

#ifndef HYPER
#define HYPER(x) x
#endif

size_t
HYPER(strcspn)(str, toks)
const char *str;
const char *toks;
{
    const char *ptr;

    if (ptr = strpbrk(str, toks))
        return(ptr - str);
    return(strlen(str));
}

