/*
 * SYMS.h
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#define SHASH   1024
#define SMASK   (SHASH-1)

#define SF_UNDEF    0x01    /*  already counted this symbol as being undefined */

typedef struct Symbol {
    struct Symbol *Next;    /*  hash link       */
    char    *Name;          /*  name of symbol  */
    short   Flags;
    Module  *DefMod;        /*  ptr to module       */
    int32_t    *DefPtr;     /*  ptr to symbol entry */
    int32_t    ComSize;     /*  if common, else 0   */
} Symbol;

extern Symbol *FindSymbol();

