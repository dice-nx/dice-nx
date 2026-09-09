# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## Unreleased

### Added

### Changed

### Fixed

- Fix unterminated string buffer in dc1 error handling routine (#28)
- dupdate change to support wildcards broke Kickstart 1.3 compatibility

### Removed


## 3.20.0

### Added

- [README.md](README.md), [CHANGELOG.md](CHANGELOG.md) and [LICENSE](LICENSE),
  replacing three original README files and DICE-LICENSE.TXT. The new files are
  named and formatted according to current standard practice for GitHub-hosted
  projects.
- Support for AmigaOS 3.2.
- `<stdint.h>` header file to allow for the fixed-bit-width types in C99.
- *lbmake* now supports a new `-d filename` option which uses the given filename
  instead of the default `lib.def`.
- The older version of *dmake* is replaced with the newer, BSD-licensed *dxmake*
  which was forked out of DICE. This has been renamed back to *dmake*, so
  existing Amiga workloads now have the tool they are used to but updated with
  newer features.
- Support for `HUNK_RELOC8D` and `HUNK_RELOC32D` hunk types. This is required to
  be compatible with the `amiga.lib` supplied with the Amiga 3.2 NDK.
- Icons for parts of DICE-nx that the user might reasonably browse with
  Workbench.
- A new Installer script.
- New scripts and tools for generating a binary release (effectively the same as
  the source release, plus the final-stage binaries, minus the propriatory Amiga
  NDK files).
- *dupdate*'s `.DistFile` control file now accepts AmigaDOS wildcard patterns
  (eg. `#?.o no`) on the `no` (exclude) lines, matching every entry in that
  directory that fits the pattern instead of only an exact name.
- *dupdate*'s `.DistFile` control file also accepts comments: any line whose
  first character is `;` is ignored.
- `asprintf()` in the C library, allocating the result buffer to fit rather than
  writing into a caller-supplied one.
- *uprev* accepts three-part version numbers, and the full version number can be
  overridden with a command line argument.
- A "Welcome to DICE-nx" AmigaGuide document, which is now the top-level entry
  point for users. All of the instructions for building DICE-nx have been moved
  into it.
- *dme*, *vmake*/*vopts* and *dd* build and ship again, having been left out of
  or broken in the build.
- The Amiga-side stages can be bootstrapped with an existing DICE 3.16 install,
  as an alternative to cross-building stage 1 on a PC.


### Changed

- Major overhaul of the build system, to allow a bootstrap build on common Linux
  PC configurations, followed by stage 2 and stage 3 builds on a real Amiga.
- All Amiga prototype, pragma, etc. header files removed. I couldn't be certain
  that they are not derived from the Amiga NDKs. They should be unnecessary
  anyway, instead provided externally at build time.
- Tabs to spaces. I realise this may upset some people, but DICE source code is
  consistent that the indentation is 4 spaces - but that every 8 spaces gets
  collapsed into a single tab. This style of identation is uncommon these days
  and VSCode (and likely many other IDEs and editors) does not handle it
  cleanly.
- `ulib.def` is now generated programmatically from `lib.def`.
- On non-Amiga builds, use the `DLIB` environment variable as a substitute for
  the `DLIB:` assign used on Amigas.
- *dsearch* and *du* are now in the `dutil` directory.
- Revised the code and macros which embedded version data into executables.
- This fork of DICE is now known as DICE-nx, and the tools, documentation and
  distribution have been renamed to match.
- *libtos* only prints errors now. Its progress and diagnostic output is behind
  a debug gate.


### Fixed

- Compiles on Linux, specifically Ubuntu 26.04 and gcc 15.2.0.
- Adds .gitignore files.
- Endian-nes bugs in libtos, enabling the tool to work on little-endian Linux
  hosts.
- A number of "ptr-ptr conversion" warnings.
- A number of UNIX-isms and modern C idioms that had slipped into the code, that
  prevented DICE from compiling itself.
- *dcc* `-mr` option now links with the registered-args linker libraries instead
  of the stack-args version. The old behaviour would cause unexpected linker
  errors when `-mr` was used.
- Some variable expansions in dmake did not work ([#13](https://github.com/dice-nx/dice-nx/issues/13)).
  Thanks [@Hagbard-Celin](https://github.com/Hagbard-Celin) for this bugfix!
- Bugs in the OS1.3 version of `system()` ([#21](https://github.com/dice-nx/dice-nx/issues/21)).
  Thanks [@Hagbard-Celin](https://github.com/Hagbard-Celin) for this bugfix!
- *das* crashed with an address error (guru 80000003) on 68000 and 68010
  machines due to an internal allocator bug that would hand out pointers to
  non-word-aligned addresses.
- *das* silently overflowed its 256-byte object-emission scratch buffer, and
  produced a corrupt object file, when a section name, symbol name or source
  filename was longer than 247 characters. It now reports this as a fatal error.
- Fixed a number of memory allocations in *das* that did not check the allocation succeeded
- *dcc* was built without ARexx support, because of incorrect preprocessor
  directives.
- *das* would occasionally fail with errors about a `LEXIDX` keyword in its
  input. A debugging `printf` in *dc1* was writing to stdout, which *dc1*
  redirects to the assembly file it passes on to *das*.
- *Dice-Startup* did not set `DCCOPTS` on AmigaOS 2.04, which rejected the `/M`
  in the script's `.key`. It now uses `/A`.
- *uprev* wrote two-digit years as, for example, "126". It now writes a correct
  four-digit year.


### Removed

- Support for the NDKs for prior versions of AmigaOS. Only 3.2 is supported at
  this time.
- Support for the floppy disk distribution and running DICE-nx from disk. Only
  hard drive installs are currently supported.
- "Registered" and "commercial" feature gates removed - all features are now
  available in all builds.
- The `-CTOD` option for generating "D Language" bindings. It's not even clear
  what "D Language" is, but it is not relevant for Amiga DICE-nx.
- Quadword (64-bit integers) - this is not supported on the Amiga. I suspect it
  was added in support of the `-CTOD` option which is now gone, so no loss here.
  Some code remains but `#ifdef`ed out, as 64-bit support on the Amiga would be
  nice to have in future.
- *lbmake* no longer recognises the `LIBDEF` environment variable. Instead, use
  the new `-d FILENAME` command line option.
- *dicecache* is no longer integrated into the build. This means that the C
  compiler suite no longer recognises or uses dicecache.library. This may be
  reinstated in future.
- a number of duplicated (or slightly diverged) files:
  - `src/alib`, which appears to duplicate files in `lib`;
  - duplicates of the tools in the `src/dutil` directory;
  - `src/shared_lib` is moved to Examples where it replaces the slightly-earlier
    version of the same example;
  - the `Visual` and `UpRev` examples, which duplicate the versions in `src`.
- *fsovl*, a filesystem compression layer which provided the `ARCH:` virtual
  filesystem, has been removed. DICE used this to support running off floppy
  disk, which is no longer supported by DICE-nx.
- *fmsdisk*, a virtual disk device, is removed. DICE used this in its release
  process to build the floppy disk distribution, which is no longer supported by
  DICE-nx.
- *patch* and *wbrun*. Comments in the *patch* source suggest it came from
  Emacs, which would make it GPL and incompatible with this project's license,
  and *wbrun* is copyright The Software Distillery, which Matt was part of but
  is not named as an author of. Neither is part of the core project, so removing
  them to be safe has little impact.
- The sample printer driver in Examples, which is derived from the Commodore
  Amiga NDK 1.3 and is marked there as copyrighted and proprietary.
- `About_Dice`, superseded by the newer documents.
- Third-party contributions, such as DME macros and supplementary utilities. I
  cannot be certain that their authors are happy for their contributions to be
  relicensed as BSD, so to be safe they have been removed.
- The `master` directory, which DICE used to make releases. DICE-nx prefers to
  keep the source and binary distributions very similar. Useful things in
  `master` were moved elsewhere, and the leftovers deleted.


## [1.15] - 2023-10-17

### Changed

- Change the primary copyright to the BSD license.
  Note that this distribution may still contain a few Commodore files
  and other files that Commodore made freely distributable, and I
  can't 100% vouch for those.  But all the C code and header files
  outside of the Commodore .fd files were written by Matthew Dillon,
  John Toebes, or Bryce Nesbitt.

### Fixed

- Do some cleanups so the dice suite compiles cleanly.  Mostly related
  to uses of sprintf() and strncpy() and such.  Includes a fix or
  two for cases that I don't think the compiler even hits (at least
  not in its original Amiga version).


## [1.14] - 2015-12-28

### Added

- Port DICE to 64-bit unix environments.  For the most part a shitload of
  cases where I assumed that 'long' (in the Amiga days) meant 32-bits.  Of
  course, it isn't on a 64-bit DragonFlyBSD, other BSD, or linux.

### Fixed

- Don't crash dobj on bad opcodes.
- Translate longs and quads with -CDTOD from machine-native C.
