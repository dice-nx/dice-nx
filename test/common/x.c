/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

int a;
extern int b;
extern int c;

xx()
{
    a = 1;
    printf("%d %d %d\n", a, b, c);
}
