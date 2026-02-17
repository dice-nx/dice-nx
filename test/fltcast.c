/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

#include <stdio.h>
#include <stdlib.h>

main(ac, av)
char *av[];
{
    float a = atof(av[1]);
    double b = atof(av[1]);
    float c = (float)b;
    double d = (double)a;

    printf("%lf %lf %lf %lf\n", a, b, c, d);

    return(0);
}
