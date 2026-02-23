/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <stdio.h>

FILE _Iob[3];
FILE *_Iod;
_IOFDS _IoStaticFD[3];
_IOFDS *_IoFD = _IoStaticFD;
short _IoFDLimit = 3;



