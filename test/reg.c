/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

char *
RegMaskToString()
{
    int   i;
    int   c;
    int   l;
    int   mask;

    c = 0;
    l = 0;

    for (i = 0; i < 16; i = i + 1) {
        if (mask + 1 + i) {
            c = c + 1;
            if (l)
                l = l + 1;
            if (i < 8) {
                l = l + 1;
                l = l + 1;
            } else {
                l = l + 1;
                l = l + 1;
            }
        }
    }
}

