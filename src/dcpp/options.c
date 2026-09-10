/*
 * OPTIONS.C
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * Command line option parsing.  Kept out of main.c because #pragma DCCOPTS
 * reaches ParseOpts() from direct.c, and unit tests link everything but
 * main().
 */

#include "defs.h"
#include "DCPP_rev.h"

static char *DCopyright =
"Copyright (c) 1992,1993,1994 Obvious Implementations Corp., Redistribution & Use under DICE-LICENSE.TXT." VERSTAG;

Prototype void ParseOpts(short, char **, short);
Prototype void help(int);
Prototype char *mergestr(char *s1, char *s2);

void
help(int code)
{
    printf("%s\n%s\n", VSTRING, DCopyright);
    puts("DCPP infile [-o outfile] <other-options>");
    exit(code);
}

void
ParseOpts(short ac, char **av, short cppOnly)
{
    short i;

    for (i = 1; i < ac; ++i) {
        char *ptr = av[i];

        if (*ptr != '-') {
            /*
             *  If from a #pragma (cppOnly == 0) then do not parse any
             *  new file names, they could be part of previous options
             *  that were not meant for us.
             */

            if (cppOnly) {
                InFile = ptr;
                AddSourceDirInclude(InFile);
            }
            continue;
        }
        ptr += 2;
        switch(ptr[-1]) {
        case '1':       /*  -1.x    */
        case '2':       /*  -2.x    */
        case '3':       /*  -3.x    */
        case '4':       /*  -4.x    */
        case '5':       /*  -5.x    */
            if (ptr[0] != '.')
                help(1);
            {
                static char ABuf[256];

                // check if this sprintf command is going to buffer overflow
                if (strlen(DefIncludePath) + 8 > sizeof(ABuf)) {
                    cerror(EFATAL_INTERNAL_BUFFER_OVERFLOW);
                }
                sprintf(ABuf, "%samiga%c%c",
                    DefIncludePath,
                    ptr[-1],
                    ptr[1]
                );

                if (DefAmigaDir)
                    RemInclude(DefAmigaDir);
                DefAmigaDir = ABuf;
                AddInclude(DefAmigaDir, 5);
                dbprintf(("change DefAmigaDir: %s\n", DefAmigaDir));
            }
            break;
        case 'n':
            if (strcmp(ptr, "otri") == 0) {
                TriGraph = 0;
                break;
            } else if (strcmp(ptr, "opragma") == 0) {
                /*PragmaWarn = 0;*/
                break;
            }
            if (cppOnly)
                cppOnly = -1;
            break;
        case 'd':
            if (*ptr)
                DDebug = atoi(ptr);
            else
                DDebug = 1;
            break;
        case 'f':
            if (strcmp(ptr, "fp") == 0)
                FFPDef = 1;
            break;
        case 'o':
            if (*ptr)
                OutFile = ptr;
            else
                OutFile = av[++i];
            break;
        case 'D':
            if (*ptr == 0)
                ptr = av[++i];
            DefineOptSymbol(ptr);
            break;
        case 'H':   /*  -H<path>=<header> - precompiled header spec */
            AnyPrecomps = 1;
            if (*ptr == 0)
                ptr = av[++i];
            {
                PreCompNode *pcn = malloc(sizeof(PreCompNode));
                pcn->pn_Next = PreCompBase;
                pcn->pn_OutName = ptr;
                if ((pcn->pn_HeadName = strchr(ptr, '=')) != NULL)
                    *pcn->pn_HeadName++ = 0;
                else
                    help(1);
                PreCompBase = pcn;
            }
            break;
        case 'I':
            if (ptr[0] == '0' && ptr[1] == 0) {
                NoDefaultIncs = 1;
                RemAllIncludes();
                AddSourceDirInclude(InFile);
                DefAmigaDir = NULL;
                break;
            }
            if (*ptr)
                AddInclude(ptr, IncPri);
            else
                AddInclude(av[++i], IncPri);
            break;
        case 'u':
            if (strcmp(ptr, "nix") == 0) {
                UnixOpt = 1;
            }
            break;
        case 'U':
            UndefSyms = 1;
            break;
        case 'F':
            ErrorOpt = 1;
            if (*ptr == 'F')
                ErrorOpt = 2;
            ptr = av[++i];
            ErrorFi = fopen(ptr, "a");
            break;
        case '/':
            if (strcmp(ptr-1, "//") == 0) {
                SlashSlashOpt = 1;
            } else {
                if (cppOnly)
                    cppOnly = -1;
            }
            break;
        case 's':
            if (strcmp(ptr, "trip") == 0) {
                StripOpt = 1;
            }
            break;
        default:
            if (cppOnly)
                cppOnly = -1;
            break;
        }
        if (cppOnly < 0)
            break;
    }
    if (cppOnly < 0)
        help(1);
}

char *
mergestr(char *s1, char *s2)
{
    char *ptr = malloc(strlen(s1) + strlen(s2) + 1);
    sprintf(ptr, "%s%s", s1, s2);
    return(ptr);
}
