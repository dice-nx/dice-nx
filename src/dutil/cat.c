/*
 * CAT.C
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include <stdio.h>
#include <stdlib.h>

#include "cat_rev.h"
static const char *DCopyright = \
    "Copyright (c) 1992-2023 Obvious Implementations Corp., 2023- Open Source contributors. Redistribution & Use under BSD License." \
    VERSTAG;

int _DiceCacheEnable = 1;

main(ac, av)
int   ac;
char **av;
{
    int   i;
    char buf[256];

    DCopyright;         /* references so GNU-C does not complain */

#ifdef AMIGA
    expand_args(ac, av, &ac, &av);
#endif

    for (i = 1; i < ac; ++i) {
        FILE *fi = fopen(av[i], "r");
        if (fi == NULL) {
            fprintf(stderr, "Unable to open %s\n", av[i]);
            continue;
        }
        while (fgets(buf, sizeof(buf), fi))
            fputs(buf, stdout);
        fclose(fi);
    }
    if (ac == 1) {
        short c;
        while ((c = getc(stdin)) != EOF)
            putc(c, stdout);
    }
    return(0);
}

