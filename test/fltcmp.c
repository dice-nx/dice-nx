/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

3
main()
{
    float x = 1.0;
    float y = 0.0;
    float z = -1.0;
    double a = 1.0;
    double b = 0.0;
    double c = -1.0;

    if (x == 0) puts("x=0");
    if (x <  0) puts("x<0");
    if (x >  0) puts("x>0");
    if (y == 0) puts("y=0");
    if (y <  0) puts("y<0");
    if (y >  0) puts("y>0");
    if (z == 0) puts("z=0");
    if (z <  0) puts("z<0");
    if (z >  0) puts("z>0");

    if (x)
        puts("x!=0");
    if (!x)
        puts("x!=0");
    if (y)
        puts("y!=0");
    if (!y)
        puts("y!=0");
    if (z)
        puts("z!=0");
    if (!z)
        puts("z!=0");

    if (a == 0) puts("a=0");
    if (a <  0) puts("a<0");
    if (a >  0) puts("a>0");
    if (b == 0) puts("b=0");
    if (b <  0) puts("b<0");
    if (b >  0) puts("b>0");
    if (c == 0) puts("c=0");
    if (c <  0) puts("c<0");
    if (c >  0) puts("c>0");

    if (a)
        puts("a!=0");
    if (!a)
        puts("a!=0");
    if (b)
        puts("b!=0");
    if (!b)
        puts("b!=0");
    if (c)
        puts("c!=0");
    if (!c)
        puts("c!=0");
    return(0);
}

