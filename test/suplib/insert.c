/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 *
 * Insert node after lnode.  If lnode == NULL then insert
 * at head of list.
 */

#include <stdio.h>
#include <suplib/lists.h>

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

