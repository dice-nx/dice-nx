/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * Internal routine to check for ^C
 */

#define SysBase_DECLARED

#include <exec/types.h>
#include <exec/tasks.h>
#include <exec/execbase.h>
#include <libraries/dos.h>
#include <clib/exec_protos.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

typedef int (*fptr)(void);

static int brk(void);

/*
 *  _SigIntFunc() is set by signal() if SIGINT is something other than the
 *  default.  The reason for this is so the signal code is not included in
 *  the executable unless explicitly called.
 */

extern struct ExecBase *SysBase;
extern __near short _AbortLockout;
static int (*_BrkFunc)(void) = brk;
void (*_SigIntFunc)(int);

void
chkabort(void)
{
    struct Task *task = SysBase->ThisTask;

    if (_AbortLockout == 0) {
        ++_AbortLockout;
        if (task->tc_SigRecvd & SIGBREAKF_CTRL_C) {
            SetSignal(0, SIGBREAKF_CTRL_C);
            if ((*_BrkFunc)()) {
                write(2, "^C\n", 3);
                exit(EXIT_FAILURE);
            }
        }
        --_AbortLockout;
    }
}

static int
brk()
{
    if (_SigIntFunc) {
        (*_SigIntFunc)(SIGINT);     /*  func might exit     */
        return(0);                  /*  do not exit         */
    }
    return(1);
}

fptr
onbreak(func)
fptr func;
{
    fptr old = _BrkFunc;

    if (func == NULL) {
        _BrkFunc = brk;
    } else {
        _BrkFunc = func;
    }
    return(old);
}

