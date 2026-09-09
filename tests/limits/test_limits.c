/*
 * Unit tests for <limits.h>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 2026- Open Source Contributors
 *
 * Verifies that the limit macros in <limits.h> agree with the compiler's
 * types (ISO/IEC 9899:1990 ss5.2.4.2.1).  The #if checks exercise the
 * preprocessor, which sees the macros before any cast can hide their type.
 */

#include "unity.h"
#include <limits.h>

#if (SCHAR_MIN >= 0) || (CHAR_MIN >= 0) || (SHRT_MIN >= 0) || (INT_MIN >= 0) || (LONG_MIN >= 0)
#error "a signed minimum evaluates as non-negative in the preprocessor"
#endif

#if (UCHAR_MAX < 0) || (USHRT_MAX < 0) || (UINT_MAX < 0) || (ULONG_MAX < 0)
#error "an unsigned maximum evaluates as negative in the preprocessor"
#endif

#if (SCHAR_MIN != -SCHAR_MAX - 1) || (SHRT_MIN != -SHRT_MAX - 1) \
    || (INT_MIN != -INT_MAX - 1) || (LONG_MIN != -LONG_MAX - 1)
#error "a minimum is not -maximum - 1"
#endif

#if (UINT_MAX != 0xFFFFFFFF) || (ULONG_MAX != 0xFFFFFFFF) || (UINT_MAX / 2 != INT_MAX)
#error "an unsigned maximum has the wrong value"
#endif

#if (CHAR_BIT != 8) || (MB_LEN_MAX < 1)
#error "CHAR_BIT or MB_LEN_MAX has the wrong value"
#endif

void setUp(void) {}
void tearDown(void) {}

/* Every minimum must be negative through the compiler, not only in #if */

void test_schar_min_is_negative(void)
{
    TEST_ASSERT_TRUE(SCHAR_MIN < 0);
}

void test_char_min_is_negative(void)
{
    /* char is signed in DICE */
    TEST_ASSERT_TRUE(CHAR_MIN < 0);
    TEST_ASSERT_EQUAL_INT(SCHAR_MIN, CHAR_MIN);
    TEST_ASSERT_EQUAL_INT(SCHAR_MAX, CHAR_MAX);
}

void test_shrt_min_is_negative(void)
{
    TEST_ASSERT_TRUE(SHRT_MIN < 0);
}

void test_int_min_is_negative(void)
{
    TEST_ASSERT_TRUE(INT_MIN < 0);
}

void test_long_min_is_negative(void)
{
    TEST_ASSERT_TRUE(LONG_MIN < 0);
}

/* Minimum macros must be usable as operands of unary minus */

void test_minimums_are_parenthesised(void)
{
    TEST_ASSERT_EQUAL_INT(128, -SCHAR_MIN);
    TEST_ASSERT_EQUAL_INT(32768, -SHRT_MIN);
    TEST_ASSERT_EQUAL_INT(INT_MAX, -(INT_MIN + 1));
    TEST_ASSERT_EQUAL_INT32(LONG_MAX, -(LONG_MIN + 1));
}

/* Limits must match the width of the types */

void test_char_limits_match_type(void)
{
    TEST_ASSERT_EQUAL_INT(SCHAR_MAX, (signed char)SCHAR_MAX);
    TEST_ASSERT_EQUAL_INT(SCHAR_MIN, (signed char)SCHAR_MIN);
    TEST_ASSERT_EQUAL_UINT(UCHAR_MAX, (unsigned char)-1);
}

void test_short_limits_match_type(void)
{
    TEST_ASSERT_EQUAL_INT(SHRT_MAX, (short)SHRT_MAX);
    TEST_ASSERT_EQUAL_INT(SHRT_MIN, (short)SHRT_MIN);
    TEST_ASSERT_EQUAL_UINT(USHRT_MAX, (unsigned short)-1);
}

void test_int_limits_match_type(void)
{
    TEST_ASSERT_EQUAL_INT(INT_MAX, (int)INT_MAX);
    TEST_ASSERT_EQUAL_INT(INT_MIN, (int)INT_MIN);
    TEST_ASSERT_EQUAL_UINT32(UINT_MAX, (unsigned int)-1);
    TEST_ASSERT_EQUAL_INT(INT_MAX, (int)(UINT_MAX >> 1));
}

void test_long_limits_match_type(void)
{
    TEST_ASSERT_EQUAL_INT32(LONG_MAX, (long)LONG_MAX);
    TEST_ASSERT_EQUAL_INT32(LONG_MIN, (long)LONG_MIN);
    TEST_ASSERT_EQUAL_UINT32(ULONG_MAX, (unsigned long)-1);
    TEST_ASSERT_EQUAL_INT32(LONG_MAX, (long)(ULONG_MAX >> 1));
}

void test_unsigned_maximums_are_unsigned(void)
{
    TEST_ASSERT_TRUE(UINT_MAX > 0);
    TEST_ASSERT_TRUE(ULONG_MAX > 0);
    TEST_ASSERT_TRUE(UINT_MAX + 1 == 0);
    TEST_ASSERT_TRUE(ULONG_MAX + 1 == 0);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_schar_min_is_negative);
    RUN_TEST(test_char_min_is_negative);
    RUN_TEST(test_shrt_min_is_negative);
    RUN_TEST(test_int_min_is_negative);
    RUN_TEST(test_long_min_is_negative);
    RUN_TEST(test_minimums_are_parenthesised);
    RUN_TEST(test_char_limits_match_type);
    RUN_TEST(test_short_limits_match_type);
    RUN_TEST(test_int_limits_match_type);
    RUN_TEST(test_long_limits_match_type);
    RUN_TEST(test_unsigned_maximums_are_unsigned);

    return UNITY_END();
}
