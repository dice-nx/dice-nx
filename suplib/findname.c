/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp.
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

