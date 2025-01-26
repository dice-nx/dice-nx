/*
 * DICE-NX project - https://dice-nx.dev/
 *
 * Copyright 1992-1997 Obvious Implementations Corp.
 * Copyright 2023- DICE-NX project contributors
 *
 * Licensed under the BSD-3-Clause License, as written in the LICENSE file
 * at the root of this project.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "lists.h"

void *
Remove(struct Node *node)
{
    node->ln_Succ->ln_Pred = node->ln_Pred;
    node->ln_Pred->ln_Succ = node->ln_Succ;
    node->ln_Succ = NULL;
    node->ln_Pred = NULL;
    return((void *)node);
}

