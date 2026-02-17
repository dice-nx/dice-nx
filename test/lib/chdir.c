/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

main(ac, av)
char *av[];
{
    short i;

    for (i = 1; i < ac; ++i) {
        int r = chdir(av[i]);
        if (r < 0)
            printf("Can't chdir %s\n", av[i]);
        Execute("cd", 0, 0);
    }
    return(0);
}
