/*
 * $VER: stdarg.h 3.20.0 (23.1.2026)
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992 Obvious Implementations Corp
 */

#ifndef STDARG_H
#define STDARG_H

#ifndef STDIO_H
typedef void *va_list;
#endif

#define va_arg(valist,typename) ((valist = (void *)((char *)valist + sizeof(typename))), (*(typename *)((char *)(valist) - sizeof(typename))))
#define va_start(valist,right)  (valist = (void*)((char *)&right + sizeof(right)))
#define va_end(valist)
#define va_copy(dest,src) (dest = src)

#endif
