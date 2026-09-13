/*
 * Unit tests for <stdint.h>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 2025- Open Source Contributors
 *
 * Verifies that the typedefs and limit macros in <stdint.h> agree with the
 * compiler's actual type sizes and arithmetic.  Each test is traceable to a
 * clause of the C99 standard (ISO/IEC 9899:1999 ss7.18).
 *
 * Two classes of bug in <stdint.h> cannot be caught by runtime tests:
 *
 *   1. Missing unsigned suffixes (e.g. UINTPTR_MAX defined as 4294967295
 *      instead of 4294967295UL).  At runtime both produce the same bit
 *      pattern 0xFFFFFFFF, so comparisons pass.  In the C90 preprocessor,
 *      an unsuffixed 4294967295 overflows signed long and evaluates to -1,
 *      which corrupts any #if expression that uses the macro (this is what
 *      caused Unity to misdetect pointer width as 16 bits).
 *
 *   2. Signed minimum literals written as (-2147483648) instead of
 *      (-2147483647L - 1).  In C90, 2147483648 does not fit in signed long
 *      so it is given type unsigned long.  Negating an unsigned value wraps:
 *      -(2147483648UL) = 2147483648UL = 0x80000000.  Cast to int32_t on a
 *      two's complement machine this is -2147483648, so runtime tests pass
 *      accidentally.  In the preprocessor, the macro evaluates as a large
 *      positive unsigned value, not as a negative signed value.
 *
 * Both classes are caught below by compile-time #if/#error checks, which
 * exercise the preprocessor arithmetic that runtime tests cannot reach.
 */

#include "unity.h"
#include <stdint.h>

/*
 * ============================================================
 * Compile-time checks (preprocessor arithmetic)
 *
 * These fire as #error at compile time, before any test runs.
 * They test properties that are invisible to runtime comparison.
 * ============================================================
 */

/* --- Unsigned suffix checks ---
 * A correctly suffixed unsigned max must be > 0 in preprocessor arithmetic.
 * Without the UL/U suffix, e.g. 4294967295 overflows signed long to -1,
 * making the macro appear negative.
 */
#if (UINT8_MAX < 0)
#error "UINT8_MAX evaluates as negative in the preprocessor - missing U suffix"
#endif

#if (UINT16_MAX < 0)
#error "UINT16_MAX evaluates as negative in the preprocessor - missing U suffix"
#endif

#if (UINT32_MAX < 0)
#error "UINT32_MAX evaluates as negative in the preprocessor - missing UL suffix"
#endif

#if (UINT_LEAST8_MAX < 0)
#error "UINT_LEAST8_MAX evaluates as negative in the preprocessor - missing U suffix"
#endif

#if (UINT_LEAST16_MAX < 0)
#error "UINT_LEAST16_MAX evaluates as negative in the preprocessor - missing U suffix"
#endif

#if (UINT_LEAST32_MAX < 0)
#error "UINT_LEAST32_MAX evaluates as negative in the preprocessor - missing UL suffix"
#endif

#if (UINT_FAST8_MAX < 0)
#error "UINT_FAST8_MAX evaluates as negative in the preprocessor - missing U suffix"
#endif

#if (UINT_FAST16_MAX < 0)
#error "UINT_FAST16_MAX evaluates as negative in the preprocessor - missing U suffix"
#endif

#if (UINT_FAST32_MAX < 0)
#error "UINT_FAST32_MAX evaluates as negative in the preprocessor - missing UL suffix"
#endif

#if (UINTPTR_MAX < 0)
#error "UINTPTR_MAX evaluates as negative in the preprocessor - missing UL suffix"
#endif

#if (UINTMAX_MAX < 0)
#error "UINTMAX_MAX evaluates as negative in the preprocessor - missing UL suffix"
#endif

/* --- Signed minimum checks ---
 * A correctly formed signed minimum must be < 0 in preprocessor arithmetic.
 * (-2147483648) is unsafe: 2147483648 exceeds signed long range in C90, so
 * it is given type unsigned long, and negating it wraps to 2147483648UL,
 * which is positive.  The safe form (-2147483647L - 1) stays negative.
 */
#if (INT32_MIN > 0)
#error "INT32_MIN evaluates as positive in the preprocessor - use (-2147483647L - 1)"
#endif

#if (INT_LEAST32_MIN > 0)
#error "INT_LEAST32_MIN evaluates as positive in the preprocessor - use (-2147483647L - 1)"
#endif

#if (INT_FAST32_MIN > 0)
#error "INT_FAST32_MIN evaluates as positive in the preprocessor - use (-2147483647L - 1)"
#endif

#if (INTPTR_MIN > 0)
#error "INTPTR_MIN evaluates as positive in the preprocessor - use (-2147483647L - 1)"
#endif

#if (INTMAX_MIN > 0)
#error "INTMAX_MIN evaluates as positive in the preprocessor - use (-2147483647L - 1)"
#endif

void setUp(void) {}
void tearDown(void) {}

/* ============================================================
 * 7.18.1.1  Exact-width integer types: sizes
 * ============================================================ */

void test_int8_t_is_one_byte(void)
{
    TEST_ASSERT_EQUAL_INT(1, (int)sizeof(int8_t));
}

void test_uint8_t_is_one_byte(void)
{
    TEST_ASSERT_EQUAL_INT(1, (int)sizeof(uint8_t));
}

void test_int16_t_is_two_bytes(void)
{
    TEST_ASSERT_EQUAL_INT(2, (int)sizeof(int16_t));
}

void test_uint16_t_is_two_bytes(void)
{
    TEST_ASSERT_EQUAL_INT(2, (int)sizeof(uint16_t));
}

void test_int32_t_is_four_bytes(void)
{
    TEST_ASSERT_EQUAL_INT(4, (int)sizeof(int32_t));
}

void test_uint32_t_is_four_bytes(void)
{
    TEST_ASSERT_EQUAL_INT(4, (int)sizeof(uint32_t));
}

/* ============================================================
 * 7.18.1.1  Exact-width integer types: signedness
 * ============================================================ */

void test_int8_t_is_signed(void)
{
    int8_t x = -1;
    TEST_ASSERT_LESS_THAN_INT(0, (int)x);
}

void test_uint8_t_is_unsigned(void)
{
    /* All bits set must produce a positive value, not wrap to -1 */
    uint8_t x = (uint8_t)(-1);
    TEST_ASSERT_GREATER_THAN_INT(0, (int)x);
}

void test_int16_t_is_signed(void)
{
    int16_t x = -1;
    TEST_ASSERT_LESS_THAN_INT(0, (int)x);
}

void test_uint16_t_is_unsigned(void)
{
    uint16_t x = (uint16_t)(-1);
    TEST_ASSERT_GREATER_THAN_INT(0, (int)x);
}

void test_int32_t_is_signed(void)
{
    int32_t x = -1L;
    TEST_ASSERT_LESS_THAN_INT(0, (int)(x >> 16));
}

void test_uint32_t_is_unsigned(void)
{
    uint32_t x = (uint32_t)(-1L);
    TEST_ASSERT_GREATER_THAN_INT(0, (int)(x >> 16));
}

/* ============================================================
 * 7.18.2.1  Limits of exact-width integer types (ss7.18.2.1)
 * ============================================================ */

void test_int8_max(void)
{
    TEST_ASSERT_EQUAL_INT8(127, INT8_MAX);
}

void test_int8_min(void)
{
    TEST_ASSERT_EQUAL_INT8(-128, INT8_MIN);
}

void test_uint8_max(void)
{
    TEST_ASSERT_EQUAL_UINT8(255U, UINT8_MAX);
}

void test_int16_max(void)
{
    TEST_ASSERT_EQUAL_INT16(32767, INT16_MAX);
}

void test_int16_min(void)
{
    TEST_ASSERT_EQUAL_INT16(-32768, INT16_MIN);
}

void test_uint16_max(void)
{
    TEST_ASSERT_EQUAL_UINT16(65535U, UINT16_MAX);
}

void test_int32_max(void)
{
    TEST_ASSERT_EQUAL_INT32(2147483647L, INT32_MAX);
}

void test_int32_min(void)
{
    /* Safe form: avoid overflowing the literal 2147483648 */
    TEST_ASSERT_EQUAL_INT32((-2147483647L - 1), INT32_MIN);
}

void test_uint32_max(void)
{
    TEST_ASSERT_EQUAL_UINT32(4294967295UL, UINT32_MAX);
}

/* ============================================================
 * 7.18.1.1  Max values match computed all-bits-set
 * ============================================================ */

void test_uint8_max_is_all_bits_set(void)
{
    uint8_t all_bits = (uint8_t)(-1);
    TEST_ASSERT_EQUAL_UINT8(all_bits, UINT8_MAX);
}

void test_uint16_max_is_all_bits_set(void)
{
    uint16_t all_bits = (uint16_t)(-1);
    TEST_ASSERT_EQUAL_UINT16(all_bits, UINT16_MAX);
}

void test_uint32_max_is_all_bits_set(void)
{
    uint32_t all_bits = (uint32_t)(-1L);
    TEST_ASSERT_EQUAL_UINT32(all_bits, UINT32_MAX);
}

/* ============================================================
 * 7.18.1.3  Pointer-holding integer types: sizes
 * ============================================================ */

void test_intptr_t_size_is_four_bytes(void)
{
    /* 68000 uses 32-bit addresses */
    TEST_ASSERT_EQUAL_INT(4, (int)sizeof(intptr_t));
}

void test_uintptr_t_size_is_four_bytes(void)
{
    TEST_ASSERT_EQUAL_INT(4, (int)sizeof(uintptr_t));
}

void test_intptr_t_same_size_as_pointer(void)
{
    TEST_ASSERT_EQUAL_INT((int)sizeof(void *), (int)sizeof(intptr_t));
}

void test_uintptr_t_same_size_as_pointer(void)
{
    TEST_ASSERT_EQUAL_INT((int)sizeof(void *), (int)sizeof(uintptr_t));
}

/* ============================================================
 * 7.18.1.3  Pointer round-trip through intptr_t / uintptr_t
 * ============================================================ */

void test_intptr_t_round_trips_pointer(void)
{
    int x = 42;
    intptr_t p = (intptr_t)&x;
    int *q = (int *)p;
    TEST_ASSERT_EQUAL_PTR(&x, q);
    TEST_ASSERT_EQUAL_INT(42, *q);
}

void test_uintptr_t_round_trips_pointer(void)
{
    int x = 99;
    uintptr_t p = (uintptr_t)&x;
    int *q = (int *)p;
    TEST_ASSERT_EQUAL_PTR(&x, q);
    TEST_ASSERT_EQUAL_INT(99, *q);
}

/* ============================================================
 * 7.18.2.4  Limits of pointer-holding integer types
 * ============================================================ */

void test_intptr_max(void)
{
    TEST_ASSERT_EQUAL_INT32(2147483647L, INTPTR_MAX);
}

void test_intptr_min(void)
{
    TEST_ASSERT_EQUAL_INT32((-2147483647L - 1), INTPTR_MIN);
}

void test_uintptr_max(void)
{
    TEST_ASSERT_EQUAL_UINT32(4294967295UL, UINTPTR_MAX);
}

void test_uintptr_max_is_all_bits_set(void)
{
    uintptr_t all_bits = (uintptr_t)(-1L);
    TEST_ASSERT_EQUAL_UINT32(all_bits, UINTPTR_MAX);
}

/* ============================================================
 * 7.18.1.5  Greatest-width integer types
 * ============================================================ */

void test_intmax_t_size(void)
{
    /* DICE does not support 64-bit integers; intmax_t is 32-bit */
    TEST_ASSERT_EQUAL_INT(4, (int)sizeof(intmax_t));
}

void test_uintmax_t_size(void)
{
    TEST_ASSERT_EQUAL_INT(4, (int)sizeof(uintmax_t));
}

void test_intmax_max(void)
{
    TEST_ASSERT_EQUAL_INT32(2147483647L, INTMAX_MAX);
}

void test_intmax_min(void)
{
    TEST_ASSERT_EQUAL_INT32((-2147483647L - 1), INTMAX_MIN);
}

void test_uintmax_max(void)
{
    TEST_ASSERT_EQUAL_UINT32(4294967295UL, UINTMAX_MAX);
}

/* ============================================================
 * 7.18.1.2  Minimum-width types: minimum sizes
 * ============================================================ */

void test_int_least8_t_minimum_size(void)
{
    TEST_ASSERT_GREATER_OR_EQUAL_INT(1, (int)sizeof(int_least8_t));
}

void test_uint_least8_t_minimum_size(void)
{
    TEST_ASSERT_GREATER_OR_EQUAL_INT(1, (int)sizeof(uint_least8_t));
}

void test_int_least16_t_minimum_size(void)
{
    TEST_ASSERT_GREATER_OR_EQUAL_INT(2, (int)sizeof(int_least16_t));
}

void test_uint_least16_t_minimum_size(void)
{
    TEST_ASSERT_GREATER_OR_EQUAL_INT(2, (int)sizeof(uint_least16_t));
}

void test_int_least32_t_minimum_size(void)
{
    TEST_ASSERT_GREATER_OR_EQUAL_INT(4, (int)sizeof(int_least32_t));
}

void test_uint_least32_t_minimum_size(void)
{
    TEST_ASSERT_GREATER_OR_EQUAL_INT(4, (int)sizeof(uint_least32_t));
}

/* ============================================================
 * 7.18.2.2  Limits of minimum-width types
 * ============================================================ */

void test_int_least8_max(void)
{
    TEST_ASSERT_EQUAL_INT8(127, INT_LEAST8_MAX);
}

void test_int_least8_min(void)
{
    TEST_ASSERT_EQUAL_INT8(-128, INT_LEAST8_MIN);
}

void test_uint_least8_max(void)
{
    TEST_ASSERT_EQUAL_UINT8(255U, UINT_LEAST8_MAX);
}

void test_int_least16_max(void)
{
    TEST_ASSERT_EQUAL_INT16(32767, INT_LEAST16_MAX);
}

void test_int_least16_min(void)
{
    TEST_ASSERT_EQUAL_INT16(-32768, INT_LEAST16_MIN);
}

void test_uint_least16_max(void)
{
    TEST_ASSERT_EQUAL_UINT16(65535U, UINT_LEAST16_MAX);
}

void test_int_least32_max(void)
{
    TEST_ASSERT_EQUAL_INT32(2147483647L, INT_LEAST32_MAX);
}

void test_int_least32_min(void)
{
    TEST_ASSERT_EQUAL_INT32((-2147483647L - 1), INT_LEAST32_MIN);
}

void test_uint_least32_max(void)
{
    TEST_ASSERT_EQUAL_UINT32(4294967295UL, UINT_LEAST32_MAX);
}

/* ============================================================
 * 7.18.1.3  Fast types: minimum sizes
 * ============================================================ */

void test_int_fast8_t_minimum_size(void)
{
    TEST_ASSERT_GREATER_OR_EQUAL_INT(1, (int)sizeof(int_fast8_t));
}

void test_uint_fast8_t_minimum_size(void)
{
    TEST_ASSERT_GREATER_OR_EQUAL_INT(1, (int)sizeof(uint_fast8_t));
}

void test_int_fast16_t_minimum_size(void)
{
    TEST_ASSERT_GREATER_OR_EQUAL_INT(2, (int)sizeof(int_fast16_t));
}

void test_uint_fast16_t_minimum_size(void)
{
    TEST_ASSERT_GREATER_OR_EQUAL_INT(2, (int)sizeof(uint_fast16_t));
}

void test_int_fast32_t_minimum_size(void)
{
    TEST_ASSERT_GREATER_OR_EQUAL_INT(4, (int)sizeof(int_fast32_t));
}

void test_uint_fast32_t_minimum_size(void)
{
    TEST_ASSERT_GREATER_OR_EQUAL_INT(4, (int)sizeof(uint_fast32_t));
}

/* ============================================================
 * 7.18.2.3  Limits of fast types
 * ============================================================ */

void test_int_fast8_max(void)
{
    TEST_ASSERT_EQUAL_INT8(127, INT_FAST8_MAX);
}

void test_int_fast8_min(void)
{
    TEST_ASSERT_EQUAL_INT8(-128, INT_FAST8_MIN);
}

void test_uint_fast8_max(void)
{
    TEST_ASSERT_EQUAL_UINT8(255U, UINT_FAST8_MAX);
}

void test_int_fast16_max(void)
{
    TEST_ASSERT_EQUAL_INT16(32767, INT_FAST16_MAX);
}

void test_int_fast16_min(void)
{
    TEST_ASSERT_EQUAL_INT16(-32768, INT_FAST16_MIN);
}

void test_uint_fast16_max(void)
{
    TEST_ASSERT_EQUAL_UINT16(65535U, UINT_FAST16_MAX);
}

void test_int_fast32_max(void)
{
    TEST_ASSERT_EQUAL_INT32(2147483647L, INT_FAST32_MAX);
}

void test_int_fast32_min(void)
{
    TEST_ASSERT_EQUAL_INT32((-2147483647L - 1), INT_FAST32_MIN);
}

void test_uint_fast32_max(void)
{
    TEST_ASSERT_EQUAL_UINT32(4294967295UL, UINT_FAST32_MAX);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_int8_t_is_one_byte);
    RUN_TEST(test_uint8_t_is_one_byte);
    RUN_TEST(test_int16_t_is_two_bytes);
    RUN_TEST(test_uint16_t_is_two_bytes);
    RUN_TEST(test_int32_t_is_four_bytes);
    RUN_TEST(test_uint32_t_is_four_bytes);

    RUN_TEST(test_int8_t_is_signed);
    RUN_TEST(test_uint8_t_is_unsigned);
    RUN_TEST(test_int16_t_is_signed);
    RUN_TEST(test_uint16_t_is_unsigned);
    RUN_TEST(test_int32_t_is_signed);
    RUN_TEST(test_uint32_t_is_unsigned);

    RUN_TEST(test_int8_max);
    RUN_TEST(test_int8_min);
    RUN_TEST(test_uint8_max);
    RUN_TEST(test_int16_max);
    RUN_TEST(test_int16_min);
    RUN_TEST(test_uint16_max);
    RUN_TEST(test_int32_max);
    RUN_TEST(test_int32_min);
    RUN_TEST(test_uint32_max);

    RUN_TEST(test_uint8_max_is_all_bits_set);
    RUN_TEST(test_uint16_max_is_all_bits_set);
    RUN_TEST(test_uint32_max_is_all_bits_set);

    RUN_TEST(test_intptr_t_size_is_four_bytes);
    RUN_TEST(test_uintptr_t_size_is_four_bytes);
    RUN_TEST(test_intptr_t_same_size_as_pointer);
    RUN_TEST(test_uintptr_t_same_size_as_pointer);
    RUN_TEST(test_intptr_t_round_trips_pointer);
    RUN_TEST(test_uintptr_t_round_trips_pointer);
    RUN_TEST(test_intptr_max);
    RUN_TEST(test_intptr_min);
    RUN_TEST(test_uintptr_max);
    RUN_TEST(test_uintptr_max_is_all_bits_set);

    RUN_TEST(test_intmax_t_size);
    RUN_TEST(test_uintmax_t_size);
    RUN_TEST(test_intmax_max);
    RUN_TEST(test_intmax_min);
    RUN_TEST(test_uintmax_max);

    RUN_TEST(test_int_least8_t_minimum_size);
    RUN_TEST(test_uint_least8_t_minimum_size);
    RUN_TEST(test_int_least16_t_minimum_size);
    RUN_TEST(test_uint_least16_t_minimum_size);
    RUN_TEST(test_int_least32_t_minimum_size);
    RUN_TEST(test_uint_least32_t_minimum_size);
    RUN_TEST(test_int_least8_max);
    RUN_TEST(test_int_least8_min);
    RUN_TEST(test_uint_least8_max);
    RUN_TEST(test_int_least16_max);
    RUN_TEST(test_int_least16_min);
    RUN_TEST(test_uint_least16_max);
    RUN_TEST(test_int_least32_max);
    RUN_TEST(test_int_least32_min);
    RUN_TEST(test_uint_least32_max);

    RUN_TEST(test_int_fast8_t_minimum_size);
    RUN_TEST(test_uint_fast8_t_minimum_size);
    RUN_TEST(test_int_fast16_t_minimum_size);
    RUN_TEST(test_uint_fast16_t_minimum_size);
    RUN_TEST(test_int_fast32_t_minimum_size);
    RUN_TEST(test_uint_fast32_t_minimum_size);
    RUN_TEST(test_int_fast8_max);
    RUN_TEST(test_int_fast8_min);
    RUN_TEST(test_uint_fast8_max);
    RUN_TEST(test_int_fast16_max);
    RUN_TEST(test_int_fast16_min);
    RUN_TEST(test_uint_fast16_max);
    RUN_TEST(test_int_fast32_max);
    RUN_TEST(test_int_fast32_min);
    RUN_TEST(test_uint_fast32_max);

    return UNITY_END();
}
