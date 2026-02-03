/*
 * LISTS.C
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 2003-2011,2023 The DragonFly Project.
 * This code is derived from software contributed to The DragonFly Project
 * by Matthew Dillon <dillon@backplane.com>
 */

#include <stdio.h>
#include "lists.h"

void
AddTail(struct List *list, struct Node *node)
{
    node->ln_Succ = (struct Node *)&list->lh_Tail;
    node->ln_Pred = list->lh_TailPred;
    list->lh_TailPred->ln_Succ = node;
    list->lh_TailPred = node;
}

void
AddHead(struct List *list, struct Node *node)
{
    node->ln_Succ = list->lh_Head;
    node->ln_Pred = (struct Node *)&list->lh_Head;
    list->lh_Head->ln_Pred = node;
    list->lh_Head = node;
}

void *
GetHead(struct List *list)
{
    struct Node *node = list->lh_Head;

    if (node->ln_Succ == NULL)
        node = NULL;
    return((void *)node);
}

void *
GetPred(struct Node *node)
{
    struct Node *pred = node->ln_Pred;

    if (pred->ln_Pred == NULL)
        pred = NULL;
    return((void *)pred);
}

void *
GetSucc(struct Node *node)
{
    struct Node *next = node->ln_Succ;

    if (next->ln_Succ == NULL)
        next = NULL;
    return((void *)next);
}

void *
GetTail(struct List *list)
{
    struct Node *node = list->lh_TailPred;

    if (node->ln_Pred == NULL)
        node = NULL;
    return((void *)node);
}

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

void
NewList(struct List *list)
{
    list->lh_Head = (struct Node *)&list->lh_Tail;
    list->lh_Tail = NULL;
    list->lh_TailPred = (struct Node *)&list->lh_Head;
}

void *
RemHead(struct List *list)
{
    struct Node *node = list->lh_Head;
    if (node->ln_Succ) {
        node->ln_Succ->ln_Pred = node->ln_Pred;
        node->ln_Pred->ln_Succ = node->ln_Succ;
        node->ln_Succ = NULL;
        node->ln_Pred = NULL;
    } else {
        node = NULL;
    }
    return((void *)node);
}

void *
Remove(struct Node *node)
{
    node->ln_Succ->ln_Pred = node->ln_Pred;
    node->ln_Pred->ln_Succ = node->ln_Succ;
    node->ln_Succ = NULL;
    node->ln_Pred = NULL;
    return((void *)node);
}

