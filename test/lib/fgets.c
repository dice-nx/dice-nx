/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 *
 * test/FGETS.C
 */

#include <stdio.h>

main(ac, av)
char *av[];
{
    FILE *fi;
    char buf[256];

    if (ac == 1) {
        puts("fgets file");
        exit(1);
    }
    if (fi = fopen(av[1], "r")) {
        while (fgets(buf, 256, fi))
            fputs(buf, stdout);
        fclose(fi);
    }
}

