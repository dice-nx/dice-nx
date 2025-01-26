/*
 * DICE-NX project - https://dice-nx.dev/
 *
 * Copyright 1992-1997 Obvious Implementations Corp.
 * Copyright 2023- DICE-NX project contributors
 *
 * Licensed under the BSD-3-Clause License, as written in the LICENSE file
 * at the root of this project.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 *  SUPLIB/STRING.H
 */

extern int stricmp(const char *, const char *);
extern int strnicmp(const char *, const char *, int);
extern void strins(char *, const char *);
extern char *LocatePath(const char *envvar, const char *fname);

