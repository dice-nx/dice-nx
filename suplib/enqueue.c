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

void
Enqueue(struct List *list, struct Node *node)
{
    struct Node *scan;

    for (scan = list->lh_Head; scan->ln_Succ; scan = scan->ln_Succ) {
        if (node->ln_Pri > scan->ln_Pri)
            break;
    }
    /*
     *  Insert before scan.  scan might point to &lh_Tail
     */

    node->ln_Succ = scan;
    node->ln_Pred = scan->ln_Pred;
    scan->ln_Pred = node;
    node->ln_Pred->ln_Succ = node;
}

