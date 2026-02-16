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
GetPred(struct Node *node)
{
    struct Node *pred = node->ln_Pred;

    if (pred->ln_Pred == NULL)
        pred = NULL;
    return((void *)pred);
}

