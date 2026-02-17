/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 *
 * SCAN TEST
 */

#include <stdio.h>

main()
{
    char buf[128];
    char buf2[128];
    int n;
    char c;

    printf("addrs %08lx %08lx ", &c, buf);
    printf("Please enter a line -");
    fflush(stdout);
    n = scanf("%c%s", &c, buf);
    printf("n = %d, c = $%02x result = '%s'\n", n, c, buf);
    printf("char after (nl) = %02x\n", getc(stdin));
    printf("Please enter another line-");
    fflush(stdout);
    if (gets(buf) == NULL) {
        puts("That was EOF!");
    } else {
        int n1, n2;
        printf("addrs %08lx %08lx ", &c, buf2);
        n = sscanf(buf, "%c%s", &c, buf2);
        printf("And this time n =%d, c = $%02x, s = '%s'\n", n, c, buf);

        printf("Now, enter two numbers-");
        fflush(stdout);
        if (gets(buf)) {
            printf("addrs %08lx %08lx ", &n1, &n2);
            n = sscanf(buf, "%d %d", &n1, &n2);
            printf("Result n = %d numbers %d and %d\n", n, n1, n2);
        }
    }
}

