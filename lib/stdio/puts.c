/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <stdio.h>
#include <string.h>

int
puts(buf)
const char *buf;
{
    fwrite(buf, 1, strlen(buf), stdout);
    putc('\n', stdout);
    return(stdout->sd_Error);
}

