/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

#include <stdio.h>

char buf[256];

main(ac, av)
char *av[];
{
    short i;

    for (i = 1; i < ac; ++i) {
        puts(av[i]);
    }
    puts("input:");
    gets(buf);
    puts(buf);
}

