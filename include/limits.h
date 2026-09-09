/*
 * $VER: limits.h 3.20.0 (23.1.2026)
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992 Obvious Implementations Corp
 */

#ifndef LIMITS_H
#define LIMITS_H

#define CHAR_BIT    8
#define CHAR_MAX    SCHAR_MAX
#define CHAR_MIN    SCHAR_MIN
#define SHRT_MAX    32767
#define SHRT_MIN    (-32767 - 1)
#define INT_MAX     2147483647
#define INT_MIN     (-2147483647 - 1)
#define LONG_MAX    2147483647L
#define LONG_MIN    (-2147483647L - 1)

#ifndef MB_LEN_MAX
#define MB_LEN_MAX      2       /*  also set in stdlib.h    */
#endif

#define SCHAR_MAX   127
#define SCHAR_MIN   (-127 - 1)
#define UCHAR_MAX   0xFF
#define UINT_MAX    4294967295U
#define ULONG_MAX   4294967295UL
#define USHRT_MAX   0xFFFF

#endif

