/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 *  float frac = fmodf(float value, float *ip);
 *
 *  (converts to either _ffpmodf() or _spmodf()), this file converts
 *  to _ffpmodf().
 */

#ifndef _FFP_FLOAT
#define _FFP_FLOAT
#endif

#ifdef _SP_FLOAT
#undef _SP_FLOAT
#endif

#include <math.h>

float
fmodf(value, ip)
float value;
float *ip;
{
    if (value >= 0.0)
        *ip = ffloor(value);
    else
        *ip = fceil(value);
    return(value - *ip);
}

