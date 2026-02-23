/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * times four years plus one day for leap year)
 */

#include <time.h>
#include <clib/dos_protos.h>
#include <lib/misc.h>

time_t
time(pt)
time_t *pt;
{
    time_t t;
    unsigned long v[3];

    DateStamp((struct DateStamp *)v);

    /*  days                 mins         ticks */

    t = v[0] * (1440 * 60) + v[1] * 60 + v[2] / 50 + _TimeCompensation;
    if (pt)
        *pt = t;
    return(t);
}

