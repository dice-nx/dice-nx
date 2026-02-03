/*
 * SUBS.C
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 2003-2011,2023 The DragonFly Project.
 * This code is derived from software contributed to The DragonFly Project
 * by Matthew Dillon <dillon@backplane.com>
 */

#include "defs.h"

int
align(int n)
{
    if (n & 3)
        return(4 - (n & 3));
    return(0);
}

