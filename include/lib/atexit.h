/*
 * $VER: lib/atexit.h 3.20.0 (23.1.2026)
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992 Obvious Implementations Corp
 */

#ifndef _LIB_ATEXIT_H
#define _LIB_ATEXIT_H

typedef struct AtExit {
    struct  AtExit *Next;
    void (*Func)(void);
} AtExit;

extern AtExit *_ExitBase;

#endif

