/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <ctype.h>

#define PU  __CF_ISPUNCT
#define XD  __CF_ISXDIGIT
#define IP  __CF_ISPRINT

const unsigned char __CAryb[257] = {
    0,
    0           ,0          ,0          ,0          ,0          ,0          ,0          ,0          ,
    0           ,0          ,0          ,0          ,0          ,0          ,0          ,0          ,
    0           ,0          ,0          ,0          ,0          ,0          ,0          ,0          ,
    0           ,0          ,0          ,0          ,0          ,0          ,0          ,0          ,
    IP          ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,
    IP|PU       ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,
    IP|XD       ,IP|XD      ,IP|XD      ,IP|XD      ,IP|XD      ,IP|XD      ,IP|XD      ,IP|XD      ,
    IP|XD       ,IP|XD      ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,
    IP|PU       ,IP|XD      ,IP|XD      ,IP|XD      ,IP|XD      ,IP|XD      ,IP|XD      ,IP         ,
    IP          ,IP         ,IP         ,IP         ,IP         ,IP         ,IP         ,IP         ,
    IP          ,IP         ,IP         ,IP         ,IP         ,IP         ,IP         ,IP         ,
    IP          ,IP         ,IP         ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,
    IP|PU       ,IP|XD      ,IP|XD      ,IP|XD      ,IP|XD      ,IP|XD      ,IP|XD      ,IP         ,
    IP          ,IP         ,IP         ,IP         ,IP         ,IP         ,IP         ,IP         ,
    IP          ,IP         ,IP         ,IP         ,IP         ,IP         ,IP         ,IP         ,
    IP          ,IP         ,IP         ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,0          ,
    0           ,0          ,0          ,0          ,0          ,0          ,0          ,0          ,
    0           ,0          ,0          ,0          ,0          ,0          ,0          ,0          ,
    0           ,0          ,0          ,0          ,0          ,0          ,0          ,0          ,
    0           ,0          ,0          ,0          ,0          ,0          ,0          ,0          ,
    IP          ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,
    IP|PU       ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,
    IP|PU       ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,
    IP|PU       ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,IP|PU      ,
    IP          ,IP         ,IP         ,IP         ,IP         ,IP         ,IP         ,IP         ,
    IP          ,IP         ,IP         ,IP         ,IP         ,IP         ,IP         ,IP         ,
    IP          ,IP         ,IP         ,IP         ,IP         ,IP         ,IP         ,IP         ,
    IP          ,IP         ,IP         ,IP         ,IP         ,IP         ,IP         ,IP         ,
    IP          ,IP         ,IP         ,IP         ,IP         ,IP         ,IP         ,IP         ,
    IP          ,IP         ,IP         ,IP         ,IP         ,IP         ,IP         ,IP         ,
    IP          ,IP         ,IP         ,IP         ,IP         ,IP         ,IP         ,IP|PU      ,
    IP          ,IP         ,IP         ,IP         ,IP         ,IP         ,IP         ,IP         ,
};

