/*
 * $VER: stdint.h 3.20.0 (23.1.2026)
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 2023 onwards  Richard Downer and Open Source contributors.
 *
 * Implements ISO C99 Standard: 7.18 Integer types <stdint.h> - at least in
 * part, as DICE does not support 64-bit integers.
 *
 * TODO: 7.18.3 Limits of other integer types
 * TODO: 7.18.4 Macros for integer constants
 */

#ifndef _STDINT_H
#define _STDINT_H 1

typedef signed char     int8_t;
typedef unsigned char   uint8_t;
typedef signed short    int16_t;
typedef unsigned short  uint16_t;
typedef signed long     int32_t;
typedef unsigned long   uint32_t;

#define INT8_MIN        (-128)
#define INT8_MAX        127
#define UINT8_MAX       255
#define INT16_MIN       (-32768)
#define INT16_MAX       32767
#define UINT16_MAX      65535
#define INT32_MIN       (-2147483648)
#define INT32_MAX       2147483647
#define UINT32_MAX      4294967295UL

typedef signed char     int_least8_t;
typedef unsigned char   uint_least8_t;
typedef signed short    int_least16_t;
typedef unsigned short  uint_least16_t;
typedef signed long     int_least32_t;
typedef unsigned long   uint_least32_t;

#define INT_LEAST8_MIN        (-128)
#define INT_LEAST8_MAX        127
#define UINT_LEAST8_MAX       255
#define INT_LEAST16_MIN       (-32768)
#define INT_LEAST16_MAX       32767
#define UINT_LEAST16_MAX      65535
#define INT_LEAST32_MIN       (-2147483648)
#define INT_LEAST32_MAX       2147483647
#define UINT_LEAST32_MAX      4294967295UL

/*
 * On 68020+, the 32-bit bus makes long loads no more expensive than short
 * loads, and using long avoids sign-extension overhead in arithmetic.
 * On 68000, the 16-bit bus means a long load costs two bus cycles, so short
 * is preferred for fast8/fast16 to minimise memory bandwidth.
 */
#if defined(__MC68K__) && __MC68K__ >= 68020
typedef signed long     int_fast8_t;
typedef unsigned long   uint_fast8_t;
typedef signed long     int_fast16_t;
typedef unsigned long   uint_fast16_t;
#define INT_FAST8_MIN        (-2147483648)
#define INT_FAST8_MAX        2147483647
#define UINT_FAST8_MAX       4294967295UL
#define INT_FAST16_MIN       (-2147483648)
#define INT_FAST16_MAX       2147483647
#define UINT_FAST16_MAX      4294967295UL
#else
typedef signed short    int_fast8_t;
typedef unsigned short  uint_fast8_t;
typedef signed short    int_fast16_t;
typedef unsigned short  uint_fast16_t;
#define INT_FAST8_MIN        (-32768)
#define INT_FAST8_MAX        32767
#define UINT_FAST8_MAX       65535U
#define INT_FAST16_MIN       (-32768)
#define INT_FAST16_MAX       32767
#define UINT_FAST16_MAX      65535U
#endif
typedef signed long     int_fast32_t;
typedef unsigned long   uint_fast32_t;

#define INT_FAST32_MIN       (-2147483648)
#define INT_FAST32_MAX       2147483647
#define UINT_FAST32_MAX      4294967295UL

typedef signed long     intptr_t;
typedef unsigned long   uintptr_t;

#define INTPTR_MIN       (-2147483648)
#define INTPTR_MAX       2147483647
#define UINTPTR_MAX      4294967295UL

typedef signed long     intmax_t;
typedef unsigned long   uintmax_t;

#define INTMAX_MIN       (-2147483648)
#define INTMAX_MAX       2147483647
#define UINTMAX_MAX      4294967295UL

#endif /* _STDINT_H */
