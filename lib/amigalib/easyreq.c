/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * EasyRequest(Window, easyStruct, IDCMP_ptr, ArgList)
 */

#include <exec/types.h>
#include <intuition/intuition.h>
#include <clib/intuition_protos.h>
#include <stdarg.h>

LONG
EasyRequest(win, es, idcmp_ptr, ...)
struct Window *win;
struct EasyStruct *es;
ULONG *idcmp_ptr;
{
   long  tmp;
   va_list va;
   va_start(va,idcmp_ptr);
   tmp = EasyRequestArgs(win, es, idcmp_ptr, va);
   va_end(va);
   return(tmp);
}

