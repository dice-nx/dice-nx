DICE-nx - a C compiler for Commodore Amiga computers and embedded 68k systems
=============================================================================

This is DICE-nx - a C compiler for Commodore Amiga computers and embedded 68k
systems. DICE-nx includes all the tools needed to build Amiga executables - the
C compiler itself, as well as an assembler, linker and numerous other support
tools. It also has several Amiga-specific features, such as automatic opening
of the common Amiga OS libraries, easy support for ARexx, and more. DICE can
also target embedded systems using 68000 processors.

DICE-nx is a fork of DICE, which was commercial product written by Matt Dillon
in the 1990s. In 2023, Matt re-licensed it under the standard 3-clause BSD
license.

DICE-nx aims to re-start development of DICE, and focusing on its original aim
of providing a fully-featured C compiler for Amiga computers. At this time, the
original 68000-based Amiga series is seeing increased support from
retro-computing enthusiasts, including the restarting of AmigaOS development
with the release of AmigaOS 3.2. DICE-nx aims to provide for this audience,
fully supporting AmigaOS 3.2 and native development on real Amiga hardware, and
a secondary aim of supporting those who want to cross-compile for the Amiga
from cheap and powerful Linux systems.

DICE-nx is currently maintained by Richard Downer, who can be emailed at
[dice@richard.downer.tech](mailto:dice@richard.downer.tech). DICE-nx is not
associated with Matt Dillon or the original DICE project. I have been in
contact with Matt and although he is encouraging of this effort, it is not
endorsed by Matt and bears a slightly different name at Matt's request. Matt's
name appears extensively throughout this repository, but he is not involved in
DICE-nx development or support. Therefore, please direct any questions or
discussions to the above email address or the GitHub repository for DICE-nx.


Signposts
---------

If you're reading this, it's likely that you've landed on the project's GitHub
page. Welcome to DICE-nx :-)

For more general information on DICE-nx, please go to the official website at
[dice-nx.dev](https://dice-nx.dev/).

As DICE-nx is an Amiga project, you'll need an Amiga computer or emulator to
properly use most of the material here. The project favours Amiga tools and
file formats, so this is one of the few Markdown files you'll find in this
project.

For instructions on using this project, start with the AmigaGuide file
[Welcome to DICE-nx](Welcome%20to%20DICE-nx.guide). This is best viewed using the
Multiview tool on AmigaOS, but is just about readable with a plain text viewer
or editor.

Community discussion forums are hosted by [GitHub Discussions](https://github.com/dice-nx/dice-nx/discussions).

Bug reports and feature requests may be made at [the project's issues page](https://github.com/dice-nx/dice-nx/issues).

If you'd like to contribute code to this repository - thank you! Please see the
[contributor's guidelines](CONTRIBUTING.md).

The project's changelog is located in [CHANGELOG.md](CHANGELOG.md).

Instructions on building DICE-nx - starting from a bootstrap on a Linux-based
PC - is in [BUILDING.md](BUILDING.md)
