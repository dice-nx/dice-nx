/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

#include <stdio.h>

main()
{
    char buf[128];
    printf("%c\n", 'a');
    printf("hi mom 43 == %d, + 1 == %ld!\n", 43, 44);
    sprintf(buf, "hi mom 43 == %3ld, + 1 == %3ld!\n", 43, 44);
    puts(buf);
    puts("test");
    printf("Foo %s on you %s\n", "abc", "def");
    printf("%%04d (26): %04d\n", 26);
    printf("left just '%-15s'\n", "Fooo");
}

