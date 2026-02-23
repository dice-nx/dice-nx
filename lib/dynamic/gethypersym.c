/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * GetHyperSymbolTags()
 */

#include <clib/dynamic_protos.h>

void *
GetHyperSymbolTags(symName, tag1, ...)
const char *symName;
Tag tag1;
{
    return(GetHyperSymbol(symName, (struct TagItem *)&tag1));
}

