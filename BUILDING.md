Building DICE
=============

DICE-nx is self hosting - that is, you can use DICE-nx to build DICE-nx. Of course, this opens up the problem of how do you build DICE-nx from source if you *don't* already have DICE-nx - for that, we need to *bootstrap* DICE-nx. The bootstrap phase uses a different starting point, such as a PC running Linux, to build just enough of DICE-nx that can then be used to build itself fully.

There are two supported ways to bootstrap DICE-nx:

* An IA32 or IA64 PC running Linux or BSD with the GNU C Compiler and related developer tools; or
* An older version of DICE on an Amiga.

The object of the bootstrap process is to have just enough of DICE-nx in the `bin1` and `dlib1` directories to be able to build DICE-nx fully.

The bootstrap process is stage 1 of a full DICE-nx re-build; stage 2 and 3 are documented further on in this document.


Bootstrapping on a PC
---------------------

### Getting the Amiga NDK

You will require the Amiga NDK (Native Developer Kit) 3.2.

The NDKs still remain under copyright, so they cannot be included in DICE. You must source the NDK
yourself. NDK 3.2 is available with the purchase of AmigaOS 3.2 from Hyperion Entertainment.

### Prerequisites

* A working C compiler
* GNU make
* The `mkdep` command (see: https://command-not-found.com/mkdep)
* AmigaOS NDK 3.2

### Install essential files from the NDK

Execute this command:

```bash
./build/install-ndk32.sh <LOCATION OF NDK3.2 FILES>
```

### Build procedure

Execute this command:

```bash
make stage1
```

### Transfer to the Amiga

Use whatever mechanism you prefer to transfer the DICE-nx distribution with new `bin1` and `dlib1` folders to a real Amiga for the next stages of the build. There are many options here, many of them depending on the specifics of your Amiga, so we won't cover that here.

You may find the script `./build/export-to-amiga.sh` helpful - it will bundle up the contents of the DICE-nx distribution, with the `bin1` and `dlib1` directories, into an LhA file (the de facto standard archive format for the Amiga) which can be transferred and unpacked on a real Amiga.

Note that at this stage, the `bin1-bootstrap` and `dlib1-bootstrap` folders are no longer required and can be deleted.


Bootstrapping on an Amiga from a previous version of DICE
---------------------------------------------------------

In the location where you have the DICE-nx distribution unpacked:

* Make directories called `bin1` and `dlib1`
* Copy the contents of the `bin` directory from the previous version of DICE into this new `bin1` directory.
* Copy the contents of the `dlib` directory from the previous version of DICE into this new `dlib1` directory.


Building stages 2 and 3
-----------------------

We have already seen stage 1, but to get to a fully-rebuilt distribution of DICE-nx requires these further stages, both of which take place on an Amiga (either real or emulated):

**Stage 2** takes the stage 1 output and repeats the build process, this time using AmigaOS and DICE-nx itself to build another basic version of DICE-nx.

**Stage 3** repeats stage 2, but this time builds the full suite of tools and libraries to make a full Amiga binary distribution of DICE C.

The stage 2 and 3 build is largely automated by scripts, but some manual steps are needed.

The procedure is as follows:

First of all, if you have a previous version of DICE or DICE-nx installed, edit `S:User-Startup` to comment out or remove the setup for DICE / DICE-nx, then reboot.

Assign `DCC:` to the directory containing DICE-nx. For example:

```
Assign DCC: DH1/DICE-nx
```

Then, initiate the build:

```
Cd DCC:
Execute build/MakeAmiga-Sequence
```

This script will do the following:

1. Build a feature-complete compiler (i.e. with floating point support) and core tools, using the
   compiler and tools produced in stage 1.
1. Build a feature-complete set of the core libraries (i.e. with floating point support) using that
   newly-built compiler and tools.
1. Re-build the compiler and tools again, using the newly-built libraries, so that we have a set of
   feature-complete libraries, and a feature-complete compiler and core tools built against those
   libraries. That will be the stage 2 build completed.
1. Build the libraries again using the stage 2 artifacts, this time building the comprehensive set
   of libraries: small and large data models, stack-based and register-based OS calls, with and
   without profiling, and OS libraries for all available and recognised NDKs.
1. Build the compiler and tools again, but this time build all the supported tools instead of just
   the core set. This will be stage 3 complete, and a fully supported compiler, tools and
   libraries.


Known limitations and future improvements
-----------------------------------------

The first host for the build must be a Linux or BSD PC on an Intel x86-64 CPU, due to assumptions
about byte ordering. It should be relatively easy to fix this though.

It would be nice to use the excellent [vamos tool by Christian Vogelgsang](https://github.com/cnvogelg/amitools/blob/master/docs/vamos.md),
but DICE currently relies on many OS calls not currently supported by vamos. It should be possible
to implement the missing OS calls, but I'm not ready to do this just yet. In the mean time, just
use a real Amiga, or emulate one using WinUAE or a similar tool.
