/*
 * BUFFER.C
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 2003-2011,2023 The DragonFly Project.
 * This code is derived from software contributed to The DragonFly Project
 * by Matthew Dillon <dillon@backplane.com>
 */

#include "defs.h"

Prototype char *AllocPathBuffer(void);
Prototype void FreePathBuffer(char *);


List PathBufList = { (Node *)&PathBufList.lh_Tail, NULL, (Node *)&PathBufList.lh_Head };

char *
AllocPathBuffer()
{
    Node *node;

    if ((node = RemHead(&PathBufList)) == NULL)
        node = malloc(PBUFSIZE);
    return((char *)node);
}

void
FreePathBuffer(buf)
char *buf;
{
    AddTail(&PathBufList, (Node *)buf);
}

