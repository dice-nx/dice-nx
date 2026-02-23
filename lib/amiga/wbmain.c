/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * Default workbench entry handler does nothing.  Prevents CLI programs
 * from incorrect operation if started as Workbench programs.
 */

int wbmain(void *);
int main(int, char *);

int
wbmain(void *wbmsg)
{
    return(-1);
}
