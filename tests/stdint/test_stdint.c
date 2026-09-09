/*
 * Unit tests for <stdint.h>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 2025- Open Source Contributors
 *
 * Verifies that the typedefs and macros in <stdint.h> agree with the
 * compiler's actual type sizes and arithmetic.  Each test is traceable to a
 * clause of the C99 standard (ISO/IEC 9899:1999 ss7.18).
 *
 * Two classes of bug in <stdint.h> are invisible to a test that compares
 * values after a cast, so they are checked with #if/#error as well:
 *
 *   1. A missing unsigned suffix, e.g. UINT32_MAX defined as 4294967295
 *      instead of 4294967295UL.  In C90 the unsuffixed constant is still
 *      unsigned long, because it does not fit in long, so this is mostly a
 *      matter of hygiene; the #if checks exist because dcpp once evaluated
 *      every constant as signed and reported these macros as negative
 *      (which also made Unity detect a 16-bit pointer from UINTPTR_MAX).
 *
 *   2. A signed minimum written as (-2147483648) instead of
 *      (-2147483647L - 1).  2147483648 does not fit in long, so it is
 *      unsigned long, and negating it gives 2147483648UL, a positive value.
 *      Cast to int32_t this is INT32_MIN again, so a runtime comparison of
 *      the cast value passes.  The #if checks and the runtime signedness
 *      tests below see the real type of the macro.
 */

#include "unity.h"
#include <stdint.h>
#include <stddef.h>
#include <signal.h>

/*
 * ============================================================
 * Compile-time checks (preprocessor arithmetic)
 * ============================================================
 */

/* Every unsigned maximum must be non-negative in the preprocessor */
#if (UINT8_MAX < 0) || (UINT16_MAX < 0) || (UINT32_MAX < 0)
#error "an exact-width unsigned maximum evaluates as negative"
#endif

#if (UINT_LEAST8_MAX < 0) || (UINT_LEAST16_MAX < 0) || (UINT_LEAST32_MAX < 0)
#error "a minimum-width unsigned maximum evaluates as negative"
#endif

#if (UINT_FAST8_MAX < 0) || (UINT_FAST16_MAX < 0) || (UINT_FAST32_MAX < 0)
#error "a fast unsigned maximum evaluates as negative"
#endif

#if (UINTPTR_MAX < 0) || (UINTMAX_MAX < 0) || (SIZE_MAX < 0)
#error "UINTPTR_MAX, UINTMAX_MAX or SIZE_MAX evaluates as negative"
#endif

/* Every signed minimum must be negative in the preprocessor */
#if (INT8_MIN >= 0) || (INT16_MIN >= 0) || (INT32_MIN >= 0)
#error "an exact-width signed minimum evaluates as non-negative"
#endif

#if (INT_LEAST8_MIN >= 0) || (INT_LEAST16_MIN >= 0) || (INT_LEAST32_MIN >= 0)
#error "a minimum-width signed minimum evaluates as non-negative"
#endif

#if (INT_FAST8_MIN >= 0) || (INT_FAST16_MIN >= 0) || (INT_FAST32_MIN >= 0)
#error "a fast signed minimum evaluates as non-negative"
#endif

#if (INTPTR_MIN >= 0) || (INTMAX_MIN >= 0) || (PTRDIFF_MIN >= 0) \
    || (SIG_ATOMIC_MIN >= 0) || (WCHAR_MIN >= 0)
#error "INTPTR_MIN, INTMAX_MIN, PTRDIFF_MIN, SIG_ATOMIC_MIN or WCHAR_MIN evaluates as non-negative"
#endif

/* Minimum and maximum must agree */
#if (INT8_MIN != -INT8_MAX - 1) || (INT16_MIN != -INT16_MAX - 1) \
    || (INT32_MIN != -INT32_MAX - 1) || (INTPTR_MIN != -INTPTR_MAX - 1) \
    || (INTMAX_MIN != -INTMAX_MAX - 1) || (PTRDIFF_MIN != -PTRDIFF_MAX - 1)
#error "a signed minimum is not -maximum - 1"
#endif

/* Unity infers its pointer width from this comparison (unity_internals.h) */
#if (UINTPTR_MAX <= 0xFFFF)
#error "UINTPTR_MAX compares as a 16-bit value"
#endif

#if (UINTPTR_MAX != 0xFFFFFFFF) || (UINTMAX_MAX != 0xFFFFFFFF) || (SIZE_MAX != 0xFFFFFFFF)
#error "UINTPTR_MAX, UINTMAX_MAX or SIZE_MAX is not 32 bits"
#endif

/* 7.18.4  The constant macros must be usable in #if */
#if (INT8_C(127) != INT8_MAX) || (UINT8_C(255) != UINT8_MAX) \
    || (INT16_C(32767) != INT16_MAX) || (UINT16_C(65535) != UINT16_MAX) \
    || (INT32_C(2147483647) != INT32_MAX) || (UINT32_C(4294967295) != UINT32_MAX) \
    || (INTMAX_C(2147483647) != INTMAX_MAX) || (UINTMAX_C(4294967295) != UINTMAX_MAX)
#error "a constant macro does not produce the matching maximum"
#endif

#if (INT32_C(-2147483647) - 1 != INT32_MIN) || (INTMAX_C(-2147483647) - 1 != INTMAX_MIN)
#error "a constant macro does not produce the matching minimum"
#endif

#if (UINT32_C(0) - 1 < 0) || (UINTMAX_C(0) - 1 < 0)
#error "UINT32_C or UINTMAX_C does not produce an unsigned constant"
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
 * 7.18.2.1  Limits of exact-width integer types
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
 * 7.18.2  Signed minimums are negative through the compiler
 *
 * A minimum written as (-2147483648) is a positive unsigned long, and
 * only looks right after a cast to int32_t.  These comparisons see the
 * macro's real type.
 * ============================================================ */

void test_exact_width_minimums_are_negative(void)
{
    TEST_ASSERT_TRUE(INT8_MIN < 0);
    TEST_ASSERT_TRUE(INT16_MIN < 0);
    TEST_ASSERT_TRUE(INT32_MIN < 0);
}

void test_least_width_minimums_are_negative(void)
{
    TEST_ASSERT_TRUE(INT_LEAST8_MIN < 0);
    TEST_ASSERT_TRUE(INT_LEAST16_MIN < 0);
    TEST_ASSERT_TRUE(INT_LEAST32_MIN < 0);
}

void test_fast_minimums_are_negative(void)
{
    TEST_ASSERT_TRUE(INT_FAST8_MIN < 0);
    TEST_ASSERT_TRUE(INT_FAST16_MIN < 0);
    TEST_ASSERT_TRUE(INT_FAST32_MIN < 0);
}

void test_pointer_and_greatest_minimums_are_negative(void)
{
    TEST_ASSERT_TRUE(INTPTR_MIN < 0);
    TEST_ASSERT_TRUE(INTMAX_MIN < 0);
}

void test_minimums_are_negated_maximum_minus_one(void)
{
    TEST_ASSERT_TRUE(INT8_MIN == -INT8_MAX - 1);
    TEST_ASSERT_TRUE(INT16_MIN == -INT16_MAX - 1);
    TEST_ASSERT_TRUE(INT32_MIN == -INT32_MAX - 1);
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
 * 7.18.1.4  Pointer-holding integer types: sizes
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
 * 7.18.1.4  Pointer round-trip through intptr_t / uintptr_t
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
 *
 * The fast types may be wider than their minimum, so the limits are
 * checked against the range of the typedef, not against fixed values.
 * ============================================================ */

void test_int_fast8_limits_match_type(void)
{
    TEST_ASSERT_GREATER_OR_EQUAL_INT(127, INT_FAST8_MAX);
    TEST_ASSERT_EQUAL_INT32(INT_FAST8_MAX, (int_fast8_t)INT_FAST8_MAX);
    TEST_ASSERT_EQUAL_INT32(-INT_FAST8_MAX - 1, INT_FAST8_MIN);
    TEST_ASSERT_EQUAL_INT32(INT_FAST8_MIN, (int_fast8_t)INT_FAST8_MIN);
}

void test_uint_fast8_max_is_all_bits_set(void)
{
    TEST_ASSERT_EQUAL_UINT32((uint_fast8_t)(-1), UINT_FAST8_MAX);
}

void test_int_fast16_limits_match_type(void)
{
    TEST_ASSERT_GREATER_OR_EQUAL_INT(32767, INT_FAST16_MAX);
    TEST_ASSERT_EQUAL_INT32(INT_FAST16_MAX, (int_fast16_t)INT_FAST16_MAX);
    TEST_ASSERT_EQUAL_INT32(-INT_FAST16_MAX - 1, INT_FAST16_MIN);
    TEST_ASSERT_EQUAL_INT32(INT_FAST16_MIN, (int_fast16_t)INT_FAST16_MIN);
}

void test_uint_fast16_max_is_all_bits_set(void)
{
    TEST_ASSERT_EQUAL_UINT32((uint_fast16_t)(-1), UINT_FAST16_MAX);
}

void test_int_fast32_limits_match_type(void)
{
    TEST_ASSERT_EQUAL_INT32(2147483647L, INT_FAST32_MAX);
    TEST_ASSERT_EQUAL_INT32(INT_FAST32_MAX, (int_fast32_t)INT_FAST32_MAX);
    TEST_ASSERT_EQUAL_INT32((-2147483647L - 1), INT_FAST32_MIN);
    TEST_ASSERT_EQUAL_INT32(INT_FAST32_MIN, (int_fast32_t)INT_FAST32_MIN);
}

void test_uint_fast32_max_is_all_bits_set(void)
{
    TEST_ASSERT_EQUAL_UINT32((uint_fast32_t)(-1L), UINT_FAST32_MAX);
}

/* ============================================================
 * 7.18.3  Limits of other integer types
 * ============================================================ */

void test_ptrdiff_limits_match_type(void)
{
    TEST_ASSERT_TRUE(PTRDIFF_MIN < 0);
    TEST_ASSERT_TRUE(PTRDIFF_MAX > 0);
    TEST_ASSERT_TRUE(PTRDIFF_MIN == -PTRDIFF_MAX - 1);
    TEST_ASSERT_TRUE(PTRDIFF_MAX == (ptrdiff_t)PTRDIFF_MAX);
    TEST_ASSERT_TRUE(PTRDIFF_MIN == (ptrdiff_t)PTRDIFF_MIN);
    TEST_ASSERT_TRUE(PTRDIFF_MAX + 1 < 0);
}

void test_size_max_matches_type(void)
{
    TEST_ASSERT_TRUE(SIZE_MAX > 0);
    TEST_ASSERT_TRUE(SIZE_MAX == (size_t)(-1));
    TEST_ASSERT_TRUE(SIZE_MAX + 1 == 0);
}

void test_sig_atomic_limits_match_type(void)
{
    TEST_ASSERT_TRUE(SIG_ATOMIC_MIN < 0);
    TEST_ASSERT_TRUE(SIG_ATOMIC_MAX > 0);
    TEST_ASSERT_TRUE(SIG_ATOMIC_MIN == -SIG_ATOMIC_MAX - 1);
    TEST_ASSERT_TRUE(SIG_ATOMIC_MAX == (sig_atomic_t)SIG_ATOMIC_MAX);
    TEST_ASSERT_TRUE(SIG_ATOMIC_MIN == (sig_atomic_t)SIG_ATOMIC_MIN);
    TEST_ASSERT_TRUE((sig_atomic_t)(SIG_ATOMIC_MAX + 1) < 0);
}

void test_wchar_limits_match_type(void)
{
    TEST_ASSERT_TRUE(WCHAR_MIN < 0);
    TEST_ASSERT_TRUE(WCHAR_MAX > 0);
    TEST_ASSERT_TRUE(WCHAR_MIN == -WCHAR_MAX - 1);
    TEST_ASSERT_TRUE(WCHAR_MAX == (wchar_t)WCHAR_MAX);
    TEST_ASSERT_TRUE(WCHAR_MIN == (wchar_t)WCHAR_MIN);
    TEST_ASSERT_TRUE((wchar_t)(WCHAR_MAX + 1) < 0);
}

/* ============================================================
 * 7.18.4  Macros for integer constants
 *
 * The result has the promoted type of the least type: int for the 8- and
 * 16-bit macros, long or unsigned long for the 32-bit and greatest ones.
 * ============================================================ */

void test_int8_c_and_uint8_c(void)
{
    TEST_ASSERT_EQUAL_INT(127, INT8_C(127));
    TEST_ASSERT_EQUAL_INT(255, UINT8_C(255));
    /* promoted to int, so -1 stays below it and a subtraction goes negative */
    TEST_ASSERT_TRUE(-1 < INT8_C(0));
    TEST_ASSERT_TRUE(-1 < UINT8_C(0));
    TEST_ASSERT_TRUE(UINT8_C(0) - 1 < 0);
}

void test_int16_c_and_uint16_c(void)
{
    TEST_ASSERT_EQUAL_INT(32767, INT16_C(32767));
    TEST_ASSERT_EQUAL_INT(65535, UINT16_C(65535));
    TEST_ASSERT_TRUE(-1 < INT16_C(0));
    TEST_ASSERT_TRUE(-1 < UINT16_C(0));
    TEST_ASSERT_TRUE(UINT16_C(0) - 1 < 0);
}

void test_int32_c_and_uint32_c(void)
{
    TEST_ASSERT_EQUAL_INT32(INT32_MAX, INT32_C(2147483647));
    TEST_ASSERT_EQUAL_INT32(INT32_MIN, INT32_C(-2147483647) - 1);
    TEST_ASSERT_EQUAL_UINT32(UINT32_MAX, UINT32_C(4294967295));
    /*
     * unsigned long: -1 converts to UINT32_MAX, and a subtraction wraps.
     * dc1 gives a constant below 65536 a narrower type whatever its suffix,
     * and the comparison then promotes to int, so a larger value is used.
     */
    TEST_ASSERT_TRUE(-1 < INT32_C(65536));
    TEST_ASSERT_FALSE(-1 < UINT32_C(65536));
    TEST_ASSERT_TRUE(UINT32_C(0) - 1 > 0);
    TEST_ASSERT_TRUE(UINT32_C(0) - 1 == UINT32_MAX);
}

void test_intmax_c_and_uintmax_c(void)
{
    TEST_ASSERT_EQUAL_INT32(INTMAX_MAX, INTMAX_C(2147483647));
    TEST_ASSERT_EQUAL_INT32(INTMAX_MIN, INTMAX_C(-2147483647) - 1);
    TEST_ASSERT_EQUAL_UINT32(UINTMAX_MAX, UINTMAX_C(4294967295));
    TEST_ASSERT_TRUE(-1 < INTMAX_C(65536));
    TEST_ASSERT_FALSE(-1 < UINTMAX_C(65536));
    TEST_ASSERT_TRUE(UINTMAX_C(0) - 1 > 0);
    TEST_ASSERT_TRUE(UINTMAX_C(0) - 1 == UINTMAX_MAX);
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

    RUN_TEST(test_exact_width_minimums_are_negative);
    RUN_TEST(test_least_width_minimums_are_negative);
    RUN_TEST(test_fast_minimums_are_negative);
    RUN_TEST(test_pointer_and_greatest_minimums_are_negative);
    RUN_TEST(test_minimums_are_negated_maximum_minus_one);

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
    RUN_TEST(test_int_fast8_limits_match_type);
    RUN_TEST(test_uint_fast8_max_is_all_bits_set);
    RUN_TEST(test_int_fast16_limits_match_type);
    RUN_TEST(test_uint_fast16_max_is_all_bits_set);
    RUN_TEST(test_int_fast32_limits_match_type);
    RUN_TEST(test_uint_fast32_max_is_all_bits_set);

    RUN_TEST(test_ptrdiff_limits_match_type);
    RUN_TEST(test_size_max_matches_type);
    RUN_TEST(test_sig_atomic_limits_match_type);
    RUN_TEST(test_wchar_limits_match_type);

    RUN_TEST(test_int8_c_and_uint8_c);
    RUN_TEST(test_int16_c_and_uint16_c);
    RUN_TEST(test_int32_c_and_uint32_c);
    RUN_TEST(test_intmax_c_and_uintmax_c);

    return UNITY_END();
}
