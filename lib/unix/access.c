/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * ACCESS.C            Check File Accessibility
 */

#include <exec/types.h>
#include <libraries/dos.h>
#include <clib/dos_protos.h>
#include <stdlib.h>

#ifndef UnixToAmigaPath
#define UnixToAmigaPath(path)   path
#endif

typedef struct FileInfoBlock    FIB;

int
access(name, mode)
const char *name;
int mode;
{
    FIB *fib = malloc(sizeof(FIB));
    int r = -1;

    if (fib) {
        BPTR lock;
        if (lock = Lock(UnixToAmigaPath(name), SHARED_LOCK)) {
            if (Examine(lock, fib)) {
                long prot = fib->fib_Protection;

                r = 0;
                if (mode & 4) {     /*  r   */
                    if (prot & 8)   /*  no read perm    */
                        r = -1;
                }
                if (mode & 2) {     /*  w   */
                    if (prot & 4)   /*  no write perm   */
                        r = -1;
                }
                if (mode & 1) {     /*  x   */
                    if (prot & 2)   /*  no execute perm */
                        r = -1;
                }
            }
            UnLock(lock);
        } else {
            /*
             *  if obj in use we cannot obtain stats.  All we know is
             *  that the obj exists.  We certainly cannot read or write
             *  it at the moment.
             */

            if (IoErr() == ERROR_OBJECT_IN_USE) {
                r = 0;
                if (mode)       /*  anything but existance fails    */
                    r = -1;
            }
        }
        free(fib);
    }
    return(r);
}

