/*
 * $VER: stddef.h 3.20.0 (23.1.2026)
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992 Obvious Implementations Corp
 */

#ifndef STDDEF_H
#define STDDEF_H

#ifndef NULL
#define NULL    ((void *)0L)
#endif
#ifndef offsetof
#define offsetof(sname,fname)   ((long)&((sname *)0)->fname)
#endif
typedef int ptrdiff_t;
typedef unsigned int size_t;
typedef char wchar_t;

#endif

