/*
 * $VER: setjmp.h 3.20.0 (23.1.2026)
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992 Obvious Implementations Corp
 */

#ifndef SETJMP_H
#define SETJMP_H

typedef long jmp_buf[16];

extern __stkargs int setjmp(jmp_buf);
extern __stkargs void longjmp(jmp_buf, int);

#endif

