/*
 * $VER: lib/wild.h 3.20.0 (23.1.2026)
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992 Obvious Implementations Corp
 */

#ifndef _LIB_WILD_H
#define _LIB_WILD_H

extern void *_ParseWild(const char *, short)
extern int _CompWild(const char *, void *, void *);
extern void _FreeWild(void *);

#endif
