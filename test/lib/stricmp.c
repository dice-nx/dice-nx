/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

main(ac, av)
char *av[];
{
    if (ac != 3) {
        puts("stricmp s1 s2");
        exit(1);
    }
    printf("result %d\n", stricmp(av[1], av[2]));
    printf("result (ni-3) %d\n", strnicmp(av[1], av[2]), 3);
    return(0);
}
