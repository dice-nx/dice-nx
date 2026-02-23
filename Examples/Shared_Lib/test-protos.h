/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * contains prototypes for the library interface functions ONLY.  This
 * is usually different from <lib-protos.h> in DTMP:SHARTEST/ because
 * the latter will contain prototypes for internal library routines as
 * well as external ones.  TEST-PROTOS.H only contains prototypes for
 * external (interface) routines.
 * 
 * this file could easily be automatically generated but I haven't put
 * together an example of that yet.
 */

#define LibCall __geta4 __regargs

extern LibCall void LockTestLib(void);
extern LibCall void UnLockTestLib(void);
extern LibCall void PostString(const char *);
extern LibCall long GetString(char *, long);

