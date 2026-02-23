/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

/*
 *  TEST.C
 */

#include "test-protos.h"
#include <stdio.h>

main(ac, av)
short ac;
char *av[];
{
    if (ac == 1) {
        char buf[256];
        while (GetString(buf, sizeof(buf)) >= 0)
            printf("GET: %s\n", buf);
    } else {
        short i;

        for (i = 1; i < ac; ++i) {
            PostString(av[i]);
            printf("POSTED: %s\n", av[i]);
        }
    }
    return(0);
}

