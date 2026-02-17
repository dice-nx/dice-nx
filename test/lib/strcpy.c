/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

void
strcpy(d, s)
char *d;
char *s;
{
    while (*s) {
        *d = *s;
        ++s;
        ++d;
    }
    *d = 0;
}


