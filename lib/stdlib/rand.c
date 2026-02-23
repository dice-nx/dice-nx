/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <stdlib.h>

int  _RandSeed1 = 0;
int  _RandSeed2 = 0;

static __autoinit void
rand_init()
{
    srand(1);
}

int
rand(void)
{
    _RandSeed1 = ((_RandSeed1 * 13 + 1) ^ (_RandSeed1 >> 9)) + _RandSeed2;
    _RandSeed2 = (_RandSeed2 * _RandSeed1 + 13) ^ (_RandSeed2 >> 13);
    return(_RandSeed1 & RAND_MAX);
}

void
srand(seed)
unsigned int seed;
{
    _RandSeed1 = (seed - 1) ^ 0xAB569834;
    _RandSeed2 = (seed + 1) ^ 0x56F42001;
    rand();
    rand();
    rand();
}

