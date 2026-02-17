/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

typedef struct {
    char buf[48];
} Foo;

main()
{
    short *a;
    Foo *f;
    char i;
    short j;
    long k;
    unsigned char l;
    unsigned short m;
    unsigned long n;

    a[i] = 1;
    a[j] = 1;
    a[k] = 1;
    a[l] = 1;
    a[m] = 1;
    a[n] = 1;

    f[i] = 1;
    f[j] = 1;
    f[k] = 1;
    f[l] = 1;
    f[m] = 1;
    f[n] = 1;
}

