/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 */

short Cnt;
short XCnt = 1;

main()
{
    puts("hello world");
    printf("hello #%d\n", Cnt++);
    printf("hello #%d\n", XCnt++);
}

