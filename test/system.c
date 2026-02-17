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

    r = system(av[1]);
    printf("result = %d\n", r);
    return(0);
}
