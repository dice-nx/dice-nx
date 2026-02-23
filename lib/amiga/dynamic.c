/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * dynamic function library support
 */

#include <exec/types.h>
#include <clib/dos_protos.h>
#include <dynamic.h>        /*  from dinclude:pd/   */
#include <stdio.h>

__regargs void *
_GetHyperVar(varName)
const char *varName;
{
    void *ptr = GetHyperSymbolTags(varName, TAG_END);
    if (ptr == NULL)
        fhprintf(Output(), "run time variable error: %s\n", varName);
    return(ptr);
}

__regargs void *
_GetHyperFunc(funcName, funcType)
const char *funcName;
const char *funcType;
{
    void *ptr = GetHyperSymbolTags(funcName, DT_TYPE, funcType, TAG_END);
    if (ptr == NULL)
        fhprintf(Output(), "run time function error: %s\n", funcName);
    return(ptr);
}

__regargs
_RelsHyperVar(ptr)
void *ptr;
{
    RelsHyperSymbol(ptr, NULL);
}

__regargs
_RelsHyperFunc(ptr)
void *ptr;
{
    RelsHyperSymbol(ptr, NULL);
}

