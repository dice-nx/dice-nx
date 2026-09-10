/*
 * MAIN.C
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * DCPP inputfile <options>
 */

#include "defs.h"

/*
 * Only main() lives here, so that unit tests can supply their own and link
 * the rest of DCPP.  Shared globals are in globals.c, option parsing in
 * options.c.
 */

Prototype int main(int, char **);

char Prefix[64];


int _DiceCacheEnable = 1;

int _bufsiz = 8192;

int
main(ac, av)
int ac;
char *av[];
{
    FILE *fi;

    if (ac == 1)
        help(1);

    {
        char *ptr;
        char *p2;

        if ((ptr = strrchr(av[0], '/')) || (ptr = strrchr(av[0], ':')))
            ++ptr;
        else
            ptr = av[0];
        if ((p2 = strchr(ptr, '_')) == NULL)
            p2 = ptr;
        else
            ++p2;
        sprintf(Prefix, "%.*s", (int)(p2 - ptr), ptr);
    }

#ifdef AMIGA
    DefIncludePath = mergestr(Prefix, "dinclude:");
#else
    if (getenv("DINCLUDE")) {
        DefIncludePath = getenv("DINCLUDE");
    } else {
        DefIncludePath = mergestr(INSTDIR, Prefix);
        DefIncludePath = mergestr(DefIncludePath, "include/");
    }
#endif
    DefAmigaDir = mergestr(DefIncludePath, "amiga");
    dbprintf(("DefAmigaDir: %s\n", DefAmigaDir));
    dbprintf(("DefIncludePath: %s\n", DefIncludePath));

    InitPrecomp();
    InitCpp();

    AddInclude(DefIncludePath, 5);
    AddInclude(mergestr(DefIncludePath, "pd"), 5);
    AddInclude(DefAmigaDir, 5);

    ParseOpts(ac, av, 1);

    IncPri = 10;     /*  any #pragma -I options go before everything */

    if (InFile == NULL)
        cerror(EFATAL_INPUT_FILE_REQUIRED);

    fi = fopen(InFile, "r");
    if (fi == NULL) {
        ErrorOpenFailed(InFile, 0);
        exit(20);
    }

    if (OutFile) {
        Fo = fopen(OutFile, "w+");
        if (Fo == NULL)
            cerror(EFATAL_CANT_CREATE_FILE, OutFile);
        OutName = OutFile;
    } else {
        Fo = stdout;
    }

    InitDefines(InFile);
    InitDirective();

    cpp(0, 0, InFile, fi, NULL, 0);

    fclose(Fo);
    if (ExitCode > 5) {
        if (OutName)
            remove(OutName);
    }
    return(ExitCode);
}

#ifdef NOTDEF

extern int32_t *__MemList;

void
du(ptr)
int32_t *ptr;
{
    char buf[64];

    sprintf(buf, "%08lx %08lx %d\n", ptr, ptr[0], ptr[1]);
    Write(Output(), buf, strlen(buf));
}

#endif
