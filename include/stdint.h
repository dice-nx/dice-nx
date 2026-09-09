/*
 * $VER: stdint.h 3.20.0 (23.1.2026)
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 2023 onwards  Richard Downer and Open Source contributors.
 *
 * Implements ISO C99 Standard: 7.18 Integer types <stdint.h>.
 *
 * DICE has no 64-bit integer type, so the 64-bit exact-width, minimum-width
 * and fastest types are not provided and the greatest-width types are 32
 * bits.  There is no <wchar.h> and no wint_t, so WINT_MIN and WINT_MAX are
 * not defined.
 */

#ifndef _STDINT_H
#define _STDINT_H 1

/* 7.18.1.1  Exact-width integer types */

typedef signed char     int8_t;
typedef unsigned char   uint8_t;
typedef signed short    int16_t;
typedef unsigned short  uint16_t;
typedef signed long     int32_t;
typedef unsigned long   uint32_t;

/* 7.18.1.2  Minimum-width integer types */

typedef signed char     int_least8_t;
typedef unsigned char   uint_least8_t;
typedef signed short    int_least16_t;
typedef unsigned short  uint_least16_t;
typedef signed long     int_least32_t;
typedef unsigned long   uint_least32_t;

/*
 * 7.18.1.3  Fastest minimum-width integer types
 *
 * short is used for the 8- and 16-bit fast types.  On a 68000 the 16-bit
 * data bus makes a long access cost two bus cycles, and 16-bit arithmetic
 * is at least as fast as 32-bit arithmetic on every 68k.
 */

typedef signed short    int_fast8_t;
typedef unsigned short  uint_fast8_t;
typedef signed short    int_fast16_t;
typedef unsigned short  uint_fast16_t;
typedef signed long     int_fast32_t;
typedef unsigned long   uint_fast32_t;

/* 7.18.1.4  Integer types capable of holding object pointers */

typedef signed long     intptr_t;
typedef unsigned long   uintptr_t;

/* 7.18.1.5  Greatest-width integer types */

typedef signed long     intmax_t;
typedef unsigned long   uintmax_t;

/*
 * 7.18.2  Limits of specified-width integer types
 *
 * A minimum is written as (-MAX - 1).  The literal 2147483648 does not fit
 * in a signed long, so it is unsigned long, and negating it does not give a
 * negative value.
 */

#define INT8_MIN            (-127 - 1)
#define INT8_MAX            127
#define UINT8_MAX           255
#define INT16_MIN           (-32767 - 1)
#define INT16_MAX           32767
#define UINT16_MAX          65535
#define INT32_MIN           (-2147483647L - 1)
#define INT32_MAX           2147483647L
#define UINT32_MAX          4294967295UL

#define INT_LEAST8_MIN      (-127 - 1)
#define INT_LEAST8_MAX      127
#define UINT_LEAST8_MAX     255
#define INT_LEAST16_MIN     (-32767 - 1)
#define INT_LEAST16_MAX     32767
#define UINT_LEAST16_MAX    65535
#define INT_LEAST32_MIN     (-2147483647L - 1)
#define INT_LEAST32_MAX     2147483647L
#define UINT_LEAST32_MAX    4294967295UL

#define INT_FAST8_MIN       (-32767 - 1)
#define INT_FAST8_MAX       32767
#define UINT_FAST8_MAX      65535
#define INT_FAST16_MIN      (-32767 - 1)
#define INT_FAST16_MAX      32767
#define UINT_FAST16_MAX     65535
#define INT_FAST32_MIN      (-2147483647L - 1)
#define INT_FAST32_MAX      2147483647L
#define UINT_FAST32_MAX     4294967295UL

#define INTPTR_MIN          (-2147483647L - 1)
#define INTPTR_MAX          2147483647L
#define UINTPTR_MAX         4294967295UL

#define INTMAX_MIN          (-2147483647L - 1)
#define INTMAX_MAX          2147483647L
#define UINTMAX_MAX         4294967295UL

/*
 * 7.18.3  Limits of other integer types
 *
 * ptrdiff_t is int, size_t is unsigned int (<stddef.h>); sig_atomic_t
 * (<signal.h>) and wchar_t (<stddef.h>) are char, which is signed.
 */

#define PTRDIFF_MIN         (-2147483647 - 1)
#define PTRDIFF_MAX         2147483647
#define SIG_ATOMIC_MIN      (-127 - 1)
#define SIG_ATOMIC_MAX      127
#define SIZE_MAX            4294967295U
#define WCHAR_MIN           (-127 - 1)
#define WCHAR_MAX           127

/*
 * 7.18.4  Macros for integer constants
 *
 * The result has the promoted type of the corresponding least type: int
 * for the 8- and 16-bit types, long or unsigned long for the rest.
 */

#define INT8_C(v)           v
#define UINT8_C(v)          v
#define INT16_C(v)          v
#define UINT16_C(v)         v
#define INT32_C(v)          v ## L
#define UINT32_C(v)         v ## UL
#define INTMAX_C(v)         v ## L
#define UINTMAX_C(v)        v ## UL

#endif /* _STDINT_H */
