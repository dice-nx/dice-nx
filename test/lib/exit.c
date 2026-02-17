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
    if (ac == 1) {
        puts("exit <code>");
        exit(1);
    }
    exit(atoi(av[1]));
}
