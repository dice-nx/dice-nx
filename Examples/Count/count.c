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
    long i;

    if (ac == 1) {
        puts("count <startvalue>");
        exit(1);
    }
    for (i = atoi(av[1]); i; --i)
        printf("%d\n", i);
    return(0);
}

