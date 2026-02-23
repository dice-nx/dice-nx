/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * Search the path for a command name
 */

#include <exec/types.h>
#include <exec/execbase.h>
#include <libraries/dos.h>
#include <libraries/dosextens.h>
#include <clib/dos_protos.h>
#include <stdio.h>
#include <lib/bcpl.h>
#include <lib/misc.h>

typedef struct CommandLineInterface CLI;
typedef struct Process Process;

typedef struct LockList {
    BPTR    NextPath;
    BPTR    PathLock;
} LockList;

extern struct ExecBase *SysBase;

long
_SearchPath(cmd)
char *cmd;
{
    CLI *cli;
    LockList *ll;

    if (SysBase->ThisTask->tc_Node.ln_Type != NT_PROCESS)
        return(0);
    if ((cli = BTOC(((Process *)SysBase->ThisTask)->pr_CLI, CLI)) == NULL)
        return(0);

    ll = BTOC(cli->cli_CommandDir, LockList);

    while (ll) {
        if (ll->PathLock) {
            long oldLock = CurrentDir(ll->PathLock);
            long lock;

            if (lock = Lock(cmd, SHARED_LOCK)) {
                CurrentDir(oldLock);
                return(lock);
            }
            CurrentDir(oldLock);
        }
        ll = BTOC(ll->NextPath, LockList);
    }
    return(0);
}


