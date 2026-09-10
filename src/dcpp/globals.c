/*
 * GLOBALS.C
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Licensed to you under the terms of the 3-clause BSD license.
 * See the LICENSE file at the root of this project for details.
 * Copyright 1992-1997 Obvious Implementations Corp
 *
 * Global state shared across DCPP.  Kept out of main.c so that unit tests,
 * which supply their own main(), can link every other DCPP object.
 */

#include "defs.h"
#include "DCPP_rev.h"

Prototype FILE *Fo;
Prototype char *InFile;
Prototype char *OutFile;
Prototype char *OutName;
Prototype char *DefIncludePath;
Prototype char *DefAmigaDir;
Prototype short DDebug;
Prototype short ExitCode;
Prototype short NoDefaultIncs;
Prototype short UndefSyms;
Prototype short TriGraph;
Prototype short GlobalStringize;
Prototype short SlashSlashOpt;
Prototype short UnixOpt;
Prototype short FFPDef;
Prototype short ForceLineSpec;
Prototype short IncPri;
Prototype short ErrorOpt;
Prototype FILE  *ErrorFi;
Prototype short StripOpt;
Prototype PreCompNode *PreCompBase;
Prototype char VersionId[];
Prototype short AnyPrecomps;

#ifdef _DCC
char VersionId[] = { VERSION, REVISION, 0 };
#else
char VersionId[] = { "" };
#endif

FILE *Fo;
char *InFile;
char *OutFile;
char *OutName;
char *DefIncludePath;
char *DefAmigaDir;
short DDebug;
short ExitCode;
short NoDefaultIncs;
short UndefSyms;
short TriGraph = 1;
short GlobalStringize;
short SlashSlashOpt;
short UnixOpt;
short FFPDef;
short ForceLineSpec;
short AnyPrecomps;
short IncPri = 8;           /*  command line -I options go before defaults */
short ErrorOpt;
FILE  *ErrorFi;
short StripOpt;
PreCompNode *PreCompBase;
