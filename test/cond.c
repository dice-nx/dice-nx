/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

main()
{
    int i, j, k;

    if (i == j)
        k = 1;
    else
        k = 2;

    if (i != j)
        k = 1;
    else
        k = 2;

    if (i == j)
        k = 3;
    if (i != j)
        k = 4;
    if (i < j)
        k = 5;
    if (i <= j)
        k = 6;
    if (i > j)
        k = 7;
    if (i >= j)
        k = 8;
    if (i)
        k = 9;
    if (!i)
        k = 10;

    if (!(i == j))
        k = 11;
    else
        k = 12;
}

