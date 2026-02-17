/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

#include <sys/types.h>

fd_set  fdr;

main()
{
    int n;
    char buf[256];

    puts("READY");

    for (;;) {
        FD_SET(0, &fdr);
        n = select(1, &fdr, NULL, NULL, NULL);
        printf("RESULT %d\n", n);
        n = read(0, buf, sizeof(buf));
        if (n <= 0)
            break;
        printf("TEXT: (%d) %*.*s\n", n, n, n, buf);
    }
    puts("DONE");
    return(0);
}

