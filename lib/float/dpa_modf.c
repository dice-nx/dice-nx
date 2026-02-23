/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * double frac = modf(double value, double *ip);
 */

#include <math.h>

double
modf(value, ip)
double value;
double *ip;
{
    if (value >= 0.0)
        *ip = floor(value);
    else
        *ip = ceil(value);
    return(value - *ip);
}

