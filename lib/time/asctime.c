/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <time.h>

char *
asctime(tm)
const struct tm *tm;
{
    static char TBuf[32];

    strftime(TBuf, sizeof(TBuf), "%c\n", tm);
    return(TBuf);
}

