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

void setUp(void) {}
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

/* dcpp-protos.h declares main(int, char **), so match it */
int main(int ac, char **av)
{
    InitCpp();

    UNITY_BEGIN();
    RUN_TEST(test_constant_arithmetic);
    RUN_TEST(test_defined_macro);
    RUN_TEST(test_macro_value_is_substituted);
    return UNITY_END();
}
