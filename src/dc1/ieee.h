/*
 * DC1/IEEE.H
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * IEEE*() calls
 */

#define float   int32_t

extern __stkargs double IEEEDPFlt(int32_t);
extern __stkargs double IEEEDPAdd(double, double);
extern __stkargs double IEEEDPMul(double, double);
extern __stkargs double IEEEDPDiv(double, double);
extern __stkargs double IEEEDPPow(double, double);
extern __stkargs double IEEEDPNeg(double);

extern __stkargs float  IEEESPFlt(int32_t);
extern __stkargs float  IEEESPAdd(float, float);
extern __stkargs float  IEEESPMul(float, float);
extern __stkargs float  IEEESPDiv(float, float);
extern __stkargs float  IEEESPPow(float, float);
extern __stkargs float  IEEESPNeg(float);

