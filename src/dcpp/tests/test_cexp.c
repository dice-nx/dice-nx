/*
 * Unit tests for the DCPP #if expression evaluator (cexp.c)
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 2026- Open Source Contributors
 *
 * Linked against every DCPP object except main.c, so ParseIfExp() runs
 * with the real symbol table and macro expansion behind it.
 */

#include "unity.h"
#include "defs.h"

/*
 * Evaluate expr as the body of a #if.  Macro expansion walks the include
 * stack, so stand in for the source file that cpp() would have pushed.
 */
static int32_t
EvalIf(char *expr, short *pundef)
{
    static Include inc;
    int32_t len = (int32_t)strlen(expr);

    memset(&inc, 0, sizeof(inc));
    inc.FileName = "test_cexp";
    inc.LineNo   = 1;
    inc.IsFile   = 1;
    inc.MaxIndex = len;
    inc.Base     = expr;
    PushBase = &inc;

    return ParseIfExp(expr, pundef, len, 1);
}

/*
 * Define a macro from #define-style text, e.g. "NAME(a, b) a ## b".
 */
static void
Define(char *text)
{
    do_define(text, (int)strlen(text), NULL);
}

/*
 * ParseIfExp() returns only the value, so a test of a constant's type
 * compares it with 0: an unsigned operand makes "x < 0" false.
 */
#define ASSERT_IF(expected, expr)                                   \
    do {                                                            \
        short undef_;                                               \
        TEST_ASSERT_EQUAL_INT32_MESSAGE(expected, EvalIf(expr, &undef_), expr); \
        TEST_ASSERT_EQUAL_INT_MESSAGE(0, undef_, expr);             \
    } while (0)

void setUp(void)
{
    ExitCode = 0;
}

void tearDown(void) {}

void test_constant_arithmetic(void)
{
    short undef;

    TEST_ASSERT_EQUAL_INT32(7, EvalIf("1 + 2 * 3", &undef));
    TEST_ASSERT_EQUAL_INT(0, undef);
}

void test_defined_macro(void)
{
    short undef;

    DefineSimpleSymbol("TEST_CEXP_DEFINED", "1", 0);
    TEST_ASSERT_EQUAL_INT32(1, EvalIf("defined(TEST_CEXP_DEFINED)", &undef));
    TEST_ASSERT_EQUAL_INT32(0, EvalIf("defined(TEST_CEXP_NOT_DEFINED)", &undef));
}

void test_macro_value_is_substituted(void)
{
    short undef;

    DefineSimpleSymbol("TEST_CEXP_VALUE", "40", 0);
    TEST_ASSERT_EQUAL_INT32(42, EvalIf("TEST_CEXP_VALUE + 2", &undef));
}

/* ============================================================
 * Constants: long, then unsigned long (C90 6.1.3.2)
 * ============================================================ */

void test_constant_that_fits_in_long_is_signed(void)
{
    ASSERT_IF(0, "2147483647 < 0");
    ASSERT_IF(0, "2147483647L < 0");
    ASSERT_IF(0, "0x7FFFFFFF < 0");
    ASSERT_IF(0, "017777777777 < 0");
    ASSERT_IF(1, "-1 < 0");
    ASSERT_IF(1, "-1L < 0");
}

/* This is the case that made UINT32_MAX in <stdint.h> compare as -1 */
void test_decimal_constant_above_long_max_is_unsigned(void)
{
    ASSERT_IF(0, "2147483648 < 0");
    ASSERT_IF(0, "4294967295 < 0");
    ASSERT_IF(0, "4294967295L < 0");
    ASSERT_IF(0, "4294967295U < 0");
    ASSERT_IF(0, "4294967295UL < 0");
    ASSERT_IF(0, "4294967295ul < 0");
    ASSERT_IF(0, "4294967295LU < 0");
}

void test_hex_and_octal_constant_with_bit_31_is_unsigned(void)
{
    ASSERT_IF(0, "0x80000000 < 0");
    ASSERT_IF(0, "0xFFFFFFFF < 0");
    ASSERT_IF(0, "020000000000 < 0");
    ASSERT_IF(0, "037777777777 < 0");
}

void test_decimal_hex_and_octal_forms_agree(void)
{
    ASSERT_IF(1, "4294967295UL == 0xFFFFFFFF");
    ASSERT_IF(1, "4294967295UL == 037777777777");
    ASSERT_IF(1, "2147483648 == 0x80000000");
}

void test_u_suffix_makes_small_constant_unsigned(void)
{
    ASSERT_IF(0, "0U - 1 < 0");
    ASSERT_IF(1, "0U - 1 > 0");
    ASSERT_IF(1, "1u - 2 > 0");
    ASSERT_IF(1, "-1 > 0U");
    ASSERT_IF(0, "-1 < 1U");
    /* L alone does not make a constant unsigned */
    ASSERT_IF(1, "0L - 1 < 0");
}

void test_suffix_is_not_read_past_end_of_expression(void)
{
    static char text[] = "1U";

    /* the macro body is "1": the U after it is outside the text */
    DefineSymbol("TEST_CEXP_BOUNDED", 17, 0, -1, NULL, NULL, text, 0, 0, 1);
    ASSERT_IF(1, "TEST_CEXP_BOUNDED - 2 < 0");
}

/* ============================================================
 * Constants that do not fit in 32 bits
 * ============================================================ */

void test_too_large_decimal_constant_warns_and_saturates(void)
{
    ASSERT_IF(1, "4294967296 == 4294967295");
    TEST_ASSERT_EQUAL_INT(5, ExitCode);
}

void test_too_large_hex_constant_warns_and_saturates(void)
{
    ASSERT_IF(1, "0x100000000 == 0xFFFFFFFF");
    TEST_ASSERT_EQUAL_INT(5, ExitCode);
}

void test_too_large_octal_constant_warns_and_saturates(void)
{
    ASSERT_IF(1, "040000000000 == 037777777777");
    TEST_ASSERT_EQUAL_INT(5, ExitCode);
}

void test_largest_32_bit_constants_do_not_warn(void)
{
    ASSERT_IF(1, "4294967295 == 0xFFFFFFFF");
    ASSERT_IF(1, "037777777777 == 0xffffffff");
    TEST_ASSERT_EQUAL_INT(0, ExitCode);
}

/* ============================================================
 * Binary operators: an unsigned operand makes the operation unsigned
 * ============================================================ */

void test_unsigned_division_and_remainder(void)
{
    ASSERT_IF(0x7FFFFFFF, "0xFFFFFFFF / 2");
    ASSERT_IF(5, "0xFFFFFFFF % 10");
    ASSERT_IF(0x7FFFFFFF, "-2 / 2U");
    ASSERT_IF(1, "0xFFFFFFFF / 2 > 0");
}

void test_signed_division_and_remainder_unchanged(void)
{
    ASSERT_IF(-4, "-8 / 2");
    ASSERT_IF(-1, "-7 % 3");
    ASSERT_IF(1, "-1 * -1");
    ASSERT_IF(-6, "2 - 8");
}

void test_division_by_zero_is_undefined(void)
{
    short undef;

    EvalIf("1 / 0", &undef);
    TEST_ASSERT_EQUAL_INT(1, undef);
    EvalIf("0xFFFFFFFF % 0", &undef);
    TEST_ASSERT_EQUAL_INT(1, undef);
}

void test_unsigned_right_shift_is_logical(void)
{
    ASSERT_IF(1, "0x80000000 >> 31");
    ASSERT_IF(0x7FFFFFFF, "4294967295U >> 1");
    ASSERT_IF(0, "0x80000000 >> 32");
}

void test_signed_right_shift_is_arithmetic(void)
{
    ASSERT_IF(-4, "-8 >> 1");
    ASSERT_IF(-1, "-1 >> 31");
    ASSERT_IF(-1, "-1 >> 32");
    ASSERT_IF(0, "1 >> 32");
}

void test_shift_type_is_the_left_operand(void)
{
    /* an unsigned count does not make a signed value unsigned */
    ASSERT_IF(-4, "-8 >> 1U");
    ASSERT_IF(1, "(-8 >> 1U) < 0");
    ASSERT_IF(1, "(1U << 31) > 0");
}

void test_left_shift(void)
{
    ASSERT_IF(16, "1 << 4");
    ASSERT_IF(-2147483647L - 1, "1 << 31");
    ASSERT_IF(0, "1 << 32");
}

void test_unsigned_comparison(void)
{
    ASSERT_IF(1, "0xFFFFFFFF > 1");
    ASSERT_IF(1, "0xFFFFFFFF >= 1");
    ASSERT_IF(0, "0xFFFFFFFF < 1");
    ASSERT_IF(0, "0xFFFFFFFF <= 1");
    ASSERT_IF(1, "-1 == 0xFFFFFFFF");
}

void test_signed_comparison_unchanged(void)
{
    ASSERT_IF(1, "-1 < 1");
    ASSERT_IF(1, "-2 <= -2");
    ASSERT_IF(0, "-1 > 0");
    ASSERT_IF(1, "-2147483647 - 1 < 0");
}

void test_bitwise_operators_keep_unsignedness(void)
{
    ASSERT_IF(0, "(0xFFFFFFFF & 0xFFFFFFFF) < 0");
    ASSERT_IF(0, "(0U | 0x80000000) < 0");
    ASSERT_IF(0, "(1U ^ -1) < 0");
    ASSERT_IF(1, "(1 & 3) == 1");
}

void test_additive_operators_keep_unsignedness(void)
{
    ASSERT_IF(0, "0xFFFFFFFF + 0 < 0");
    ASSERT_IF(0, "2U * -1 < 0");
    ASSERT_IF(1, "0xFFFFFFFF + 1 == 0");
}

/* The result of a comparison or logical operator is a signed int */
void test_comparison_and_logical_results_are_signed(void)
{
    ASSERT_IF(1, "(1U < 2) - 2 < 0");
    ASSERT_IF(1, "(1U == 1U) - 2 < 0");
    ASSERT_IF(1, "(1U && 1U) - 2 < 0");
    ASSERT_IF(1, "(0U || 1U) - 2 < 0");
    ASSERT_IF(1, "!0U - 2 < 0");
    ASSERT_IF(1, "defined(TEST_CEXP_NOT_DEFINED) - 1 < 0");
}

/* ============================================================
 * Unary operators keep the operand's type
 * ============================================================ */

void test_negated_unsigned_constant_stays_unsigned(void)
{
    ASSERT_IF(1, "-(2147483648) > 0");
    ASSERT_IF(1, "-2147483648 > 0");
    ASSERT_IF(1, "-1U > 0");
    ASSERT_IF(1, "-1U == 0xFFFFFFFF");
}

void test_complement_keeps_signedness(void)
{
    ASSERT_IF(1, "~0U > 0");
    ASSERT_IF(1, "~0 < 0");
    ASSERT_IF(-1, "~0");
}

void test_parentheses_keep_signedness(void)
{
    ASSERT_IF(0, "(4294967295) < 0");
    ASSERT_IF(0, "((0xFFFFFFFF)) / 2 < 0");
    ASSERT_IF(1, "(-1) < 0");
}

/* ============================================================
 * Macro expansion keeps the type of the expanded value
 * ============================================================ */

void test_macro_expansion_keeps_unsignedness(void)
{
    DefineSimpleSymbol("TEST_CEXP_UMAX", "4294967295UL", 0);
    DefineSimpleSymbol("TEST_CEXP_UZERO", "0U", 0);
    DefineSimpleSymbol("TEST_CEXP_UMAX2", "TEST_CEXP_UMAX", 0);

    ASSERT_IF(0, "TEST_CEXP_UMAX < 0");
    ASSERT_IF(0x7FFFFFFF, "TEST_CEXP_UMAX / 2");
    ASSERT_IF(0, "TEST_CEXP_UMAX + 1");
    ASSERT_IF(1, "TEST_CEXP_UZERO - 1 > 0");
    ASSERT_IF(0, "TEST_CEXP_UMAX2 < 0");
}

void test_function_macro_argument_keeps_unsignedness(void)
{
    Define("TEST_CEXP_HALF(x) ((x) / 2)");
    DefineSimpleSymbol("TEST_CEXP_UMAX", "4294967295UL", 0);

    ASSERT_IF(0x7FFFFFFF, "TEST_CEXP_HALF(TEST_CEXP_UMAX)");
    ASSERT_IF(0x7FFFFFFF, "TEST_CEXP_HALF(0xFFFFFFFF)");
    ASSERT_IF(-4, "TEST_CEXP_HALF(-8)");
}

/* Mirrors the <stdint.h> minimum form, which must stay negative */
void test_signed_minimum_form_stays_negative(void)
{
    DefineSimpleSymbol("TEST_CEXP_INT32_MIN", "(-2147483647L - 1)", 0);

    ASSERT_IF(1, "TEST_CEXP_INT32_MIN < 0");
    ASSERT_IF(-2147483647L - 1, "TEST_CEXP_INT32_MIN");
}

/* ============================================================
 * The ## operator in a macro used in #if
 * ============================================================ */

void test_paste_argument_with_suffix(void)
{
    Define("TEST_CEXP_UL(v) v ## UL");

    ASSERT_IF(0, "TEST_CEXP_UL(4294967295) < 0");
    ASSERT_IF(1, "TEST_CEXP_UL(1) - 2 > 0");
    ASSERT_IF(1, "TEST_CEXP_UL(0) - 1 == 0xFFFFFFFF");
    TEST_ASSERT_EQUAL_INT(0, ExitCode);
}

void test_paste_two_arguments(void)
{
    Define("TEST_CEXP_CAT(a, b) a ## b");

    ASSERT_IF(1234, "TEST_CEXP_CAT(12, 34)");
    ASSERT_IF(1234, "TEST_CEXP_CAT(12,34) + 0");
    TEST_ASSERT_EQUAL_INT(0, ExitCode);
}

void test_paste_literal_prefix_to_argument(void)
{
    Define("TEST_CEXP_HEX(v) 0x ## v");

    ASSERT_IF(255, "TEST_CEXP_HEX(FF)");
    ASSERT_IF(0, "TEST_CEXP_HEX(FFFFFFFF) < 0");
    TEST_ASSERT_EQUAL_INT(0, ExitCode);
}

void test_paste_chain(void)
{
    Define("TEST_CEXP_CAT3(a, b, c) a ## b ## c");

    ASSERT_IF(123, "TEST_CEXP_CAT3(1, 2, 3)");
    TEST_ASSERT_EQUAL_INT(0, ExitCode);
}

void test_paste_inside_larger_expression(void)
{
    Define("TEST_CEXP_ULP1(v) (v ## UL + 1)");

    ASSERT_IF(0, "TEST_CEXP_ULP1(4294967295)");
    ASSERT_IF(1, "TEST_CEXP_ULP1(1) == 2");
    TEST_ASSERT_EQUAL_INT(0, ExitCode);
}

/* dcpp-protos.h declares main(int, char **), so match it */
int main(int ac, char **av)
{
    InitCpp();

    UNITY_BEGIN();
    RUN_TEST(test_constant_arithmetic);
    RUN_TEST(test_defined_macro);
    RUN_TEST(test_macro_value_is_substituted);

    RUN_TEST(test_constant_that_fits_in_long_is_signed);
    RUN_TEST(test_decimal_constant_above_long_max_is_unsigned);
    RUN_TEST(test_hex_and_octal_constant_with_bit_31_is_unsigned);
    RUN_TEST(test_decimal_hex_and_octal_forms_agree);
    RUN_TEST(test_u_suffix_makes_small_constant_unsigned);
    RUN_TEST(test_suffix_is_not_read_past_end_of_expression);

    RUN_TEST(test_too_large_decimal_constant_warns_and_saturates);
    RUN_TEST(test_too_large_hex_constant_warns_and_saturates);
    RUN_TEST(test_too_large_octal_constant_warns_and_saturates);
    RUN_TEST(test_largest_32_bit_constants_do_not_warn);

    RUN_TEST(test_unsigned_division_and_remainder);
    RUN_TEST(test_signed_division_and_remainder_unchanged);
    RUN_TEST(test_division_by_zero_is_undefined);
    RUN_TEST(test_unsigned_right_shift_is_logical);
    RUN_TEST(test_signed_right_shift_is_arithmetic);
    RUN_TEST(test_shift_type_is_the_left_operand);
    RUN_TEST(test_left_shift);
    RUN_TEST(test_unsigned_comparison);
    RUN_TEST(test_signed_comparison_unchanged);
    RUN_TEST(test_bitwise_operators_keep_unsignedness);
    RUN_TEST(test_additive_operators_keep_unsignedness);
    RUN_TEST(test_comparison_and_logical_results_are_signed);

    RUN_TEST(test_negated_unsigned_constant_stays_unsigned);
    RUN_TEST(test_complement_keeps_signedness);
    RUN_TEST(test_parentheses_keep_signedness);

    RUN_TEST(test_macro_expansion_keeps_unsignedness);
    RUN_TEST(test_function_macro_argument_keeps_unsignedness);
    RUN_TEST(test_signed_minimum_form_stays_negative);

    RUN_TEST(test_paste_argument_with_suffix);
    RUN_TEST(test_paste_two_arguments);
    RUN_TEST(test_paste_literal_prefix_to_argument);
    RUN_TEST(test_paste_chain);
    RUN_TEST(test_paste_inside_larger_expression);

    return UNITY_END();
}
