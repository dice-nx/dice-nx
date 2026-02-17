/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

main(ac, av)
char *av[];
{
    long r;
    long n = 1;

    if (ac == 1) {
        puts("exec_dcc prg [args [repeat]]");
        exit(1);
    }
    if (ac == 4)
        n = atoi(av[3]);
    while (n--) {
        if (ac == 2)
            r = exec_dcc(av[1], "");
        else
            r = exec_dcc(av[1], av[2]);
        printf("result %d\n", r);
    }
}

