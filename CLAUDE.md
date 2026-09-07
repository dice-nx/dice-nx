# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

DICE-nx is a C compiler suite for Commodore Amiga computers and embedded 68k systems — a BSD-licensed fork of Matt Dillon's DICE from the 1990s, now maintained by Richard Downer. It targets AmigaOS (with first-class support for AmigaOS 3.2 / NDK 3.2) and is **self-hosting**: DICE-nx builds itself, using its own `dmake` build tool and `DMakefile`s throughout.

This is an Amiga project. It favours Amiga file formats: documentation is largely AmigaGuide (`.guide`) and plain-text `.DOC` files, and `.info` files are Amiga icon files — never delete or "clean up" `.info` files or other odd-looking artifacts (`.DICE` project files, `_UAEFSDB.___`, etc.).

## Building

Full details are in [Welcome to DICE-nx.guide](Welcome to DICE-nx.guide). The build has three stages; only stage 1 runs on a PC.

**Stage 1 (bootstrap, Linux/BSD x86-64 only):**

```bash
./build/install-ndk32.sh <path-to-NDK3.2-files>   # one-time: install Amiga NDK headers (not in repo, copyrighted)
make stage1                                        # GNU make wrapper around dmake; see top-level Makefile
```

Stage 1 works like this (see the top-level `Makefile`):
1. `src/dmake` is built first with the host compiler via its own GNU `Makefile`, into `bin1-bootstrap/`.
2. That `dmake` builds `suplib/` and the core tools with the host `cc` (`CROSS_COMPILE=1`), also into `bin1-bootstrap/`.
3. (stage1b) The freshly built cross-`dcc` builds the core C runtime libraries from `lib/` into `dlib1/`.
4. (stage1c) The tools are rebuilt against those libraries into `bin1/` — real Amiga binaries.

Intermediate objects go to `/tmp/dtmp/`. `make clean` removes `bin1`, `bin1-bootstrap`, `dlib1`, and `/tmp/dtmp`.

**Stages 2 and 3 run on an Amiga (real or emulated — vamos does not work):** transfer the tree (`./build/export-to-amiga.sh` bundles it as an LhA archive), `Assign DCC:` to the directory, then `Execute build/MakeAmiga-Sequence`. These stages rebuild the compiler with itself and then build the full library matrix (data models, register/stack args, profiling, per-NDK OS libs) and full tool set. Amiga-side changes cannot be verified from this Linux checkout.

## The dmake build system

Everything except the initial `src/dmake` bootstrap is driven by `dmake` reading `DMakefile`s. dmake has its own syntax, distinct from GNU make: `.include`, `.ifdef`/`.else`/`.endif`, `.ifos AmigaOS` for OS-conditional rules, `%(left)`/`%(right)` in rules, and collection expansion like `$(SRCS:"*.c":"*.o")`. See `src/dmake/dmake.doc` for the reference.

`DMakefile.inc` at the repo root sets the shared build variables. Key switch: `CROSS_COMPILE` selects host `cc` (with `-DCROSS_COMPILE -DNO_ASM -DINTELBYTEORDER`) versus `dcc`. When editing tool sources, code guarded by `CROSS_COMPILE` is what runs during the PC bootstrap; unguarded Amiga-specific code (OS calls, `#ifdef AMIGA`) only compiles on the Amiga side.

## Amiga OS compatibility

**All Amiga code must work on Kickstart 1.3 (V34).** A library function marked "V36" or later is only permitted when a graceful degradation is present: a V34 path that leaves the feature working, if more crudely, on 1.3. NDK 3.2 headers are what we compile against, but V34 is the runtime floor — a function existing in the headers says nothing about it existing on the machine the code has to run on. A feature that silently does nothing under 1.3 is a bug, not a degradation.

The NDK `clib` headers mark the boundary explicitly, e.g. `include/amiga32/clib/dos_protos.h` has a `/*--- functions in V36 or higher (Release 2.0) ---*/` line, with everything below it needing a fallback. Check there before using an OS call you have not used in this tree before. Common V36+ traps: `SetVar`/`GetVar`/`DeleteVar` (and therefore environment variables at all), `SystemTagList`/`System`, `RunCommand`, `FindSegment`, `NameFromLock`, `ReadArgs`, `AllocDosObject`, `CreateNewProc`, `Printf`/`PutStr`. The 1.3 equivalents are usually clumsier — `ENV:` files instead of variables, `Execute()` instead of `System()`, `Lock`/`Examine`/`ParentDir` walked by hand instead of `NameFromLock`.

Guard both ways: `#if INCLUDE_VERSION >= 36` at compile time, and at runtime the version of the library that owns the call — `DOSBase->dl_lib.lib_Version` for dos.library, not `SysBase`. `SetEnvVar()` in `src/dmake/run.c` and `lib/unix/setenv.c` are the pattern to copy. Pick the runtime threshold to match whatever reads the result back: dmake tests for 37 rather than 36 because `getenv()` only consults dos variables from 37 up.

## Character set

Amiga uses ISO-8859-1 character set. Do not write characters outside of this set to files.

## Amiga filesystem paths

The Amiga filesystem namespace differs from both Unix and Windows — relevant when generating or reasoning about paths in C source, `DMakefile`s, or Amiga docs/examples:

- Like Windows, the namespace is divided into volumes, with a fully-qualified path starting with the volume identifier and a colon — but the identifier is a string (`DH0:`, `SD1:`, `CD0:`), not a single letter.
- Paths are built up with `/` as the separator.
- A leading `/` does **not** mean the volume root. `VOLNAME:` gives the root of that volume; `:` alone means the root of the current volume.
- There is no `.` operator for the current directory — CLI commands use `""` (an empty string) instead.
- There is no `..` operator — each additional leading `/` walks up one more parent directory.

Examples: `SYS:` is the boot volume's root; `SYS:S/User-Startup` is the file `User-Startup` in the `S` directory at the root of the boot volume; `:src/test.c` is `src/test.c` from the current volume's root; `/lib/string.c` is `lib/string.c` in the parent of the current directory; `//Makefile` is `Makefile` two levels up.

## Layout and architecture

The compiler is a classic multi-pass pipeline of separate executables, orchestrated by the `dcc` driver:

- `src/dcc` — compiler driver/frontend: parses options, runs the passes, handles Amiga specifics (auto-opening OS libraries, etc.)
- `src/dcpp` — C preprocessor
- `src/dc1` — the compiler proper: lexer, parser, semantics, and 68k code generation (`gen*.c`, `asm*.c`)
- `src/das` — 68k assembler
- `src/dlink` — linker
- `src/dobj` — object-file inspection/manipulation tool

Supporting tools, each in its own `src/` subdirectory: `dmake` (make tool; the only component that also builds with host GNU make), `dutil` (many small single-file utilities, split into `core` and full sets — see `src/dutil/DMakefile`), `dme` (text editor), `dd` (debugger), `derror` (error lookup), `dicehelp` (help system), `dicecache` (resident cache library speeding up compiles), and the GUI tools `vmake`/`vopts`/`vsuck` sharing code in `vcommon`.

Other significant directories:

- `suplib/` — support library of common routines linked into the tools themselves (lists, hashing, I/O wrappers); built first
- `lib/` — source for the C runtime libraries shipped with the compiler (`stdio`, `stdlib`, `string`, `amiga`, `rexx`, `float`, …), built into `dlib/`
- `include/` — the C headers shipped with the compiler (this is DICE's own libc headers, not host headers); NDK headers get installed under here by `install-ndk32.sh`
- `dlib/` — prebuilt/output runtime libraries; `bin1/`, `dlib1/`, `bin1-bootstrap/` — bootstrap outputs (git-ignored working artifacts of stage 1)
- `config/` — compiler configuration, e.g. `dice.errors` message catalogue
- `doc/` — user documentation (`COMPILER.DOC`, `EXTENSIONS.DOC`, `REGARGS.DOC`, …); `Welcome to DICE-nx.guide` is the top-level user entry point
- `test/` — ad-hoc C test programs exercising compiler features; there is no automated test harness. Changes are properly verified by transferring the build to a real or emulated Amiga and exercising it there — a PC-side `make stage1` plus compiling files from `test/` is only a first-pass sanity check.

Version headers: each tool has a `*_rev.h` with its version; bump via the `uprev` convention when releasing (see `src/dutil/uprev.c`).

## Prototypes and makeproto

Prefer function prototypes over old-style declarations. A prototype for a function meant to be called from other source units is written in the `.c` file itself, on a single line, prefixed with `Prototype` (a macro defined per-subproject as `#define Prototype extern`, e.g. `src/dlink/defs.h`):

```c
Prototype int ExtArgsEnv(short, char ***, char *);
```

Each subproject's `DMakefile` runs `makeproto` to scan its `.c` files for these `Prototype` lines and generate a shared header of prototypes for that subproject — don't hand-write that generated header.

## Conventions

- Refer to [CONTRIBUTING.md](CONTRIBUTING.md) for coding and Git requirements.
- Keep commit message bodies short: one paragraph is fine, and a second only for a complex or unusual change. Detail belongs in the code, the docs or the issue, not in `git log`.
- Do **not** add a `Claude-Session:` trailer to commit messages, in this repo or in any other repo worked on from this project (e.g. the amitools checkout). The session link is not resolvable by other contributors and embeds a session identifier permanently into shared history. A `Co-Authored-By:` trailer is fine and should be kept.
- Much of the code carries Matt Dillon / DragonFly Project copyright headers — leave these intact.
- The dialect is C90. Some early-1990s K&R-style C can be found - when you're working on a function or file that uses K&R-style declarations, progressively upgrade those to C90 syntax as part of your changes. Don't go out of your way to modernise untouched code elsewhere in the same file.
- Indent C source (and similar files) with 4 spaces, not tabs.
- New C source files start with this header (adapt the comment syntax for other languages):

  ```c
  /*
   * <Short description of the file>
   *
   * SPDX-License-Identifier: BSD-3-Clause
   *
   * Licensed to you under the terms of the 3-clause BSD license.
   * See the LICENSE file at the root of this project for details.
   * Copyright <year>- Open Source Contributors
   *
   * <Extended description of the file, if appropriate>
   */
  ```
