/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp.
 */

#include <stdio.h>
#include "lists.h"

void *
GetSucc(struct Node *node)
{
    struct Node *next = node->ln_Succ;

    if (next->ln_Succ == NULL)
        next = NULL;
    return((void *)next);
}

