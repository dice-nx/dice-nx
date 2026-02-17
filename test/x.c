/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

#include <stdio.h>

main(ac, av)
char *av[];
{
    short i;
    for (i = 1; i < 1000; ++i)
        puts("hello world");
    return(0);
}

