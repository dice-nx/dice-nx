/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

int b;
extern int a;
extern int c;

yy()
{
    b = 2;
    printf("%d %d %d\n", a, b, c);
}
