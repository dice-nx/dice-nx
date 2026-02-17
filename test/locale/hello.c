/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

#include <lib/ilocale.h>

main(ac, av)
char *av[];
{
    int r = SetCatalog(av[1], "hello.catalog");

    if (r < 0)
        puts("couldn't open locale");
    else if (r > 0)
        puts("couldn't open catalog in locale");

    puts("Hello world");
    puts("This is a test");
    puts("This is not in the catalog");
    return(0);
}

