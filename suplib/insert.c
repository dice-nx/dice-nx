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
Insert(struct List *list, struct Node *node, struct Node *lnode)
{
    /*
     *  Insert node after lnode.  If lnode == NULL then insert 
     *  at head of list.
     */

    if (lnode == NULL)
        lnode = (struct Node *)&list->lh_Head;
    node->ln_Pred = lnode;
    node->ln_Succ = lnode->ln_Succ;
    lnode->ln_Succ = node;
    node->ln_Succ->ln_Pred = node;
}

