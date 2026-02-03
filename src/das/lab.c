/*
 * LAB.C
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include "defs.h"

Prototype   Label   *LabHash[LSIZE];

Prototype int   labhash(char *);
Prototype Label *GetLabelByName(char *);
Prototype Label *FindLabel(char *);

Label   *LabHash[LSIZE];

int
labhash(str)
char *str;
{
    register int32_t hv = 0x1B465D8;

    while (*str) {
        hv = (hv >> 23) ^ (hv << 5) ^ (ubyte)*str;
        ++str;
    }
    return(hv & LMASK);
}

Label *
GetLabelByName(name)
char *name;
{
    int32_t i = labhash(name);
    Label **plab;
    Label *lab;

    for (plab = LabHash + i; (lab = *plab) != NULL; plab = &lab->HNext) {
        if (strcmp(lab->Name, name) == 0)
            return(lab);
    }
    lab = AllocStructure(Label);
    lab->HNext = *plab;
    lab->Name = name;
    lab->XDefLink = (void *)-1L;
    *plab = lab;
    return(lab);
}

Label *
FindLabel(name)
char *name;
{
    int32_t i = labhash(name);
    Label *lab;

    for (lab = LabHash[i]; lab; lab = lab->HNext) {
        if (strcmp(lab->Name, name) == 0)
            return(lab);
    }
    return(lab);
}

