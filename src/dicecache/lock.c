/*
 * LOCK.C
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 */

#include "defs.h"

#ifdef NOTDEF
/*
 *  library interface
 */

Prototype LibCall void LockHDDB(void);
Prototype LibCall void UnLockHDDB(void);

/*
 *  library local
 */

LibCall void
LockHDDB(void)
{
    ObtainSemaphore(&SemLock);
}

LibCall void
UnLockHDDB(void)
{
    ReleaseSemaphore(&SemLock);
}

#endif
