/*
 * COND.C
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 2003-2011,2023 The DragonFly Project.
 * This code is derived from software contributed to The DragonFly Project
 * by Matthew Dillon <dillon@backplane.com>
 */

#include "defs.h"

Prototype int pushIf(IfNode **ifBase, int value);
Prototype int popIf(IfNode **ifBase);
Prototype int elseIf(IfNode **ifBase);

int
pushIf(IfNode **ifBase, int value)
{
    IfNode *ifn = malloc(sizeof(IfNode));

    bzero(ifn, sizeof(IfNode));
    ifn->if_Next = *ifBase;
    *ifBase = ifn;

    if (ifn->if_Next == NULL || ifn->if_Next->if_Value)
        ifn->if_Value = value;
    else
        ifn->if_Value = 0;
    return(ifn->if_Value);
}

int
popIf(IfNode **ifBase)
{
    IfNode *ifn = *ifBase;

    *ifBase = ifn->if_Next;
    free(ifn);
    if ((ifn = *ifBase) == NULL)
        return(1);
    else
        return(ifn->if_Value);
}

int
elseIf(IfNode **ifBase)
{
    IfNode *ifn = *ifBase;

    if (ifn->if_Next == NULL || ifn->if_Next->if_Value) {
        ifn->if_Value = !ifn->if_Value;
    } else {
        assert(ifn->if_Value == 0);
    }
    return(ifn->if_Value);
}


