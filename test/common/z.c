/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

int a;
int b;
int c;

main()
{
    xx();
    yy();
    printf("%d %d %d\n", a, b, c);
    a = 4;
    b = 5;
    c = 6;
    printf("%d %d %d\n", a, b, c);
}

