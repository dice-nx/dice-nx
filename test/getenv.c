/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

#include <stdlib.h>

main(ac, av)
short ac;
char *av[];
{
    short i;

    for (i = 1; i < ac; ++i) {
        char *ptr = getenv(av[i]);

        if (ptr == NULL)
            ptr = "<null>";
        printf("ENV: %s = '%s'\n", av[i], ptr);
    }
    return(0);
}

