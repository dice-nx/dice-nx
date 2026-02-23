/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <string.h>

char *
strtok(cmd, toks)
char *cmd;
const char *toks;
{
    static char *Cmd;
    char *ptr;

    if (cmd == NULL) {
        cmd = Cmd;
        if (cmd == NULL)
            return(NULL);
    }

    /*
     *  skip whitespace
     */

    while (*cmd && strchr(toks, *cmd))
        ++cmd;

    if (*cmd == 0)
        return(NULL);

    if (ptr = strpbrk(cmd, toks))
        *ptr++ = 0;
    Cmd = ptr;
    return(cmd);
}

