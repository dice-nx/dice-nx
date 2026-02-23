/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include "defs.h"

Prototype void InitC(void);
Prototype void UnInitC(void);

Prototype SignalSemaphore SemLock;
Prototype List            StrList;

SignalSemaphore SemLock;
List            StrList;

void
InitC(void)
{
    NewList(&StrList);
    InitSemaphore(&SemLock);
}

void
UnInitC(void)
{
    Node *node;

    while (node = RemHead(&StrList))
        FreeMem(node, sizeof(Node) + strlen(node->ln_Name) + 1);
}

