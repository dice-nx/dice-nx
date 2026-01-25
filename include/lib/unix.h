/*
 * $VER: lib/unix.h 3.20.0 (23.1.2026)
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992 Obvious Implementations Corp
 */

#ifndef LIB_UNIX_H
#define LIB_UNIX_H

char *UnixToAmigaPath(char *);
char *AmigaToUnixPath(char *);
int sigcheckchld(void);             /*  private */
void amiga_vfork_sigall(long);      /*  private */

int kill(int, int);
int wait3(union wait *, int, struct rusage *);
int wait(union wait *);
int amiga_dup2(int, int);
int amiga_execseg(char **, struct Segment *, long);
int amiga_execlp(char *, char *, ...);
int amiga_execvp(char *, char **);
int amiga_execl(char *, char *, ...);
int amiga_execv(char *, char **);
int _amiga_vforkc(void);

#endif

