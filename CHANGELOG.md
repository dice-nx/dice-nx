# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- [README.md](README.md), [CHANGELOG.md](CHANGELOG.md) and [LICENSE](LICENSE),
  replacing three original README files and DICE-LICENSE.TXT. The new files are
  named and formatted according to current standard practice for GitHub-hosted
  projects.
- Support for AmigaOS 3.2.
- `<stdint.h>` header file to allow for the fixed-bit-width types in C99.
- *lbmake* now supports a new `-d filename` option which uses the given filename
  instead of the default `lib.def`.
- *dxmake* is back in the DICE-nx distribution, after it was removed from the
  pre-BSD-relicensing source tree.
- Support for `HUNK_RELOC8D` and `HUNK_RELOC32D` hunk types. This is required to
  be compatible with the `amiga.lib` supplied with the Amiga 3.2 NDK.
- Icons for parts of DICE-nx that the user might reasonably browse with
  Workbench.
- A new Installer script.
- New scripts and tools for generating a binary release (effectively the same as
  the source release, plus the final-stage binaries, minus the propriatory Amiga
  NDK files).


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


### Fixed

- Compiles on Linux, specifically Ubuntu 20.04 and gcc 9.4.0 - also still
  compiles on DragonFly BSD.
- Adds .gitignore files.
- Endian-nes bugs in libtos, enabling the tool to work on little-endian Linux
  hosts.
- A number of "ptr-ptr conversion" warnings.
- A number of UNIX-isms and modern C idioms that had slipped into the code, that
  prevented DICE from compiling itself.
- *dcc* `-mr` option now links with the registered-args linker libraries instead
  of the stack-args version. The old behaviour would cause unexpected linker
  errors when `-mr` was used.


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
    version of the same example.
- *fsovl*, a filesystem compression layer which provided the `ARCH:` virtual
  filesystem, has been removed. DICE used this to support running off floppy
  disk, which is no longer supported by DICE-nx.
- *fmsdisk*, a virtual disk device, is removed. DICE used this in its release
  process to build the floppy disk distribution, which is no longer supported by
  DICE-nx.
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
