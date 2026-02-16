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
GetTail(struct List *list)
{
    struct Node *node = list->lh_TailPred;

    if (node->ln_Pred == NULL)
        node = NULL;
    return((void *)node);
}

