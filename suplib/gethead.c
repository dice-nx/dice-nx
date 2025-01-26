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
GetHead(struct List *list)
{
    struct Node *node = list->lh_Head;

    if (node->ln_Succ == NULL)
        node = NULL;
    return((void *)node);
}

