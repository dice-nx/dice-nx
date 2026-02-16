/*
 * SUPLIB/STRING.H
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp.
 */

extern int stricmp(const char *, const char *);
extern int strnicmp(const char *, const char *, int);
extern void strins(char *, const char *);
extern char *LocatePath(const char *envvar, const char *fname);

