/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * Return system clock
 */

#include <time.h>
#include <clib/dos_protos.h>

clock_t
clock()
{
    unsigned long v[3];
    clock_t t;

    DateStamp((struct DateStamp *)v);
    t = v[0] * (1440 * 60 * 50) + v[1] * (60 * 50) + v[2];
    return(t);
}

