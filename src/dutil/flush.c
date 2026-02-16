/*
 * FLUSH.C
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 * 
 *  dumb memory flush
 */

#ifdef AMIGA
#include <exec/types.h>
#include <exec/memory.h>
#include <clib/exec_protos.h>
#include <lib/version.h>
#else
#include <include/lib/version.h>
#endif

IDENT("flush",".3");
DCOPYRIGHT;

int
main(int ac, char **av)
{
#ifdef AMIGA
    char *ptr;

    if (ptr = AllocMem(0x7FFFFFFF, MEMF_PUBLIC)) {
        main(0, NULL);
        FreeMem(ptr, 0x7FFFFFFF);
    }
#endif
    return(0);
}

