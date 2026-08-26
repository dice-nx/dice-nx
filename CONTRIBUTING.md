Contributing code to DICE-nx
============================

Thank you for choosing to contribute to the DICE-nx Git repository :-)

As a small project, our contributing guidelines are pretty small and there
aren't a lot of rules. Nevertheless, the project does require these rules to be
followed.

* All contributions must be licensed under the [BSD 3-clause license](LICENSE).
  If your contribution is not under this license, but it is under a compatible
  license, please include evidence of this.
* You must be the original author of the contribution; if you are not, you must
  be able to prove that you are entitled to contribute the code (this is easy if
  you are incorporating existing BSD-licensed open source code).
* Commit messages must follow the [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/)
  scheme.
* Write updates to [CHANGELOG.md](CHANGELOG.md) following the [Keep a Changelog](https://keepachangelog.com/en/1.1.0/).
  scheme.
* DICE-nx strives to remain compatible with Kickstart 1.3 Amigas. For the core toolchain this is essential, and it is generally expected for the extended set of tools too. Special cases MAY be made for using Kickstart 2.0 or later library calls IF there is good justification and a graceful fallback. For example, using V37+ environment variable DOS library calls as long as the DOS library version is checked and falls back to the V34 `ENVARC:` method. Any PR which changes any existing tool to fail on Kickstart 1.3 will be rejected.
