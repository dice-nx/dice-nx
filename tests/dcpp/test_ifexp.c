/*
 * Unit tests for integer arithmetic in dcpp #if expressions
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 2026- Open Source Contributors
 *
 * The preprocessor evaluates #if in C90 arithmetic: a constant is long or
 * unsigned long (both 32 bits in DICE), and an operation with an unsigned
 * operand is done unsigned.  Every check here is a #error, so the test is
 * the build; the one runtime test only records that the build got this far.
 */

#include "unity.h"

/* Constants that fit in a signed long are signed */
#if (2147483647 < 0) || (2147483647L < 0) || (0x7FFFFFFF < 0) || (017777777777 < 0)
#error "in-range constant evaluates as negative"
#endif

#if !(-1 < 0) || !(-2147483647 - 1 < 0)
#error "negative constant evaluates as non-negative"
#endif

/* Constants with bit 31 set are unsigned long, with or without a suffix */
#if (2147483648 < 0) || (2147483648U < 0) || (2147483648L < 0) || (2147483648UL < 0)
#error "2147483648 evaluates as negative"
#endif

#if (4294967295 < 0) || (4294967295U < 0) || (4294967295L < 0) || (4294967295UL < 0)
#error "4294967295 evaluates as negative"
#endif

#if (0x80000000 < 0) || (0xFFFFFFFF < 0) || (020000000000 < 0) || (037777777777 < 0)
#error "hex or octal constant with bit 31 set evaluates as negative"
#endif

#if (4294967295UL != 0xFFFFFFFF) || (4294967295UL != 037777777777)
#error "decimal, hex and octal forms of the same value differ"
#endif

/* A U suffix makes a small constant unsigned, and the other operand follows */
#if !(-1 > 0U) || (-1 < 1U) || !(0U - 1 > 0)
#error "U suffix does not make the expression unsigned"
#endif

/* Division, remainder and right shift are unsigned when an operand is */
#if (0xFFFFFFFF / 2 != 0x7FFFFFFF) || (0xFFFFFFFF % 10 != 5) \
    || (4294967295U >> 1 != 2147483647) || (0x80000000 >> 31 != 1)
#error "unsigned division, remainder or shift evaluates as signed"
#endif

/* Signed arithmetic is unchanged */
#if (-8 / 2 != -4) || (-8 >> 1 != -4) || (-1 >> 31 != -1) \
    || (1 << 31 != -2147483647 - 1) || (-1 * -1 != 1)
#error "signed arithmetic is wrong"
#endif

/* Unary minus and complement keep the operand's type */
#if !(-(2147483648) > 0) || !(-2147483648 > 0) || !(~0U > 0) || (~0 > 0) || !(-1U > 0)
#error "unary operator changes signedness"
#endif

/* The result of a comparison or logical operator is a signed int */
#if ((1U < 2) - 2 > 0) || ((1U && 1) - 2 > 0) || (!0U - 2 > 0)
#error "comparison or logical result is unsigned"
#endif

/* Operands that come from macro expansion keep their type */
#define IFEXP_UMAX      4294967295UL
#define IFEXP_HALF(x)   ((x) / 2)
#if (IFEXP_UMAX < 0) || (IFEXP_HALF(IFEXP_UMAX) != 2147483647) || (IFEXP_UMAX + 1 != 0)
#error "macro-expanded operand loses its type"
#endif

#define IFEXP_UL(v)     v ## UL
#if (IFEXP_UL(4294967295) < 0) || (IFEXP_UL(1) - 2 < 0)
#error "## in a macro used in #if does not make an unsigned constant"
#endif

void setUp(void) {}
void tearDown(void) {}

void test_preprocessor_checks_passed(void)
{
    TEST_ASSERT_TRUE(1);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_preprocessor_checks_passed);
    return UNITY_END();
}
