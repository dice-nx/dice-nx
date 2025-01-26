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
#include <string.h>
#include "lists.h"

void *
FindName(struct List *list, const char *name)
{
    struct Node *node;

    for (node = list->lh_Head; node->ln_Succ; node = node->ln_Succ) {
        if (node->ln_Name && strcmp(node->ln_Name, name) == 0)
            return((void *)node);
    }
    return(NULL);
}

