/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

struct Foo {
    char a[1026];
};

fubar()
{
    int i = 0;
    struct Foo *a = 0;
    struct Foo *b = 0;

    if (a[i] == b[i])
        a = 1;
}

