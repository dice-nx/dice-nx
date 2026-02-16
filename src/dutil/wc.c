/*
 * WC.C
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * Count chars, words, and lines in a file or files or, if no files
 * specified, from stdin.
 *
 * WC [file ... ]
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef AMIGA
#include <lib/version.h>
#else
#include <include/lib/version.h>
#endif

IDENT("wc",".2");
DCOPYRIGHT;

int32_t t_chars, t_words, t_lines;

void wc(FILE *);

main(ac, av)
int   ac;
char **av;
{
    int   i;
    int   maxlen = 10;

    Ident;
    DCopyright;

#ifndef unix
    expand_args(ac, av, &ac, &av);
#endif

    for (i = 1; i < ac; ++i) {
        int len = strlen(av[i]);
        if (maxlen < len)
            maxlen = len;
    }

    for (i = 1; i < ac; ++i) {
        FILE *fi;

        if (fi = fopen(av[i], "r")) {
            printf ("%-*s ", maxlen, av[i]);
            fflush(stdout);
            wc(fi);
            fclose(fi);
        } else {
            printf ("error: %s\n", av[i]);
        }
    }
    printf ("\n%*s %8ld %8ld %8ld\n", maxlen, "TOTAL", t_chars, t_words, t_lines);
    return(0);
}

void
wc(fi)
FILE *fi;
{
    int l_chars = 0, l_words = 0, l_lines = 0;
    char buf[256];
    char *ptr;

    while (fgets(buf, sizeof(buf), fi)) {
        l_chars += strlen(buf);

        ++l_lines;

        ptr = buf;
        while (*ptr) {
            while (*ptr == ' ')
                ++ptr;
            if (*ptr) {
                while (*ptr && *ptr != ' ')
                    ++ptr;
                ++l_words;
            }
        }
    }
    printf ("%8ld %8ld %8ld\n", l_chars, l_words, l_lines);
    t_chars += l_chars;
    t_words += l_words;
    t_lines += l_lines;
}

