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
* Prefer [Simplified Technical English](https://www.asd-ste100.org) for commit messages, code comments, text emitted by the programs, etc. Documentation, etc. may use a less formal, more verbose form.
* For any non-trivial user-facing changes, write updates to [CHANGELOG.md](CHANGELOG.md) following the [Keep a Changelog](https://keepachangelog.com/en/1.1.0/) scheme.
* DICE-nx strives to remain compatible with Kickstart 1.3 Amigas. For the core toolchain this is essential, and it is generally expected for the extended set of tools too. Special cases MAY be made for using Kickstart 2.0 or later library calls IF there is good justification and a graceful fallback. For example, using V37+ environment variable DOS library calls as long as the DOS library version is checked and falls back to the V34 `ENVARC:` method. Any PR which changes any existing tool to fail on Kickstart 1.3 will be rejected.

Use of LLMs and Generative AI
-----------------------------

This project is willing to accept contributions that have used LLM-based generative AI ("gen AI" henceforth) tools such as Claude Code and GitHub Copilot, providing that these contributions are made by a *skilled software developer* using such tools to *assist* them - not as a *substitute* for being a skilled software developer.

Gen AI tools can be very helpful for a project such as this - written for a niche platform (Amiga) in a language and programming style from several decades ago. These can help developers study and understand the existing code, and can iterate on work such as fixing bugs very fast.

These are tools, and not replacements for a skilled developer. You will be expected to take ownership of your contributions - you should understand them, and be able to answer questions about them (without delegating your answer back to gen AI tools). You should be clear about where gen AI was used in your contribution, and should **thoroughly** review anything written by gen AI in your contributions to the project.

Here are some examples of acceptable ("good") and unacceptable ("bad") behaviours:

* Intention:
  * GOOD: you have a specific task you want to achieve, and you use the gen AI tool to help you achieve it.
  * BAD: you want to make a contribution but don't care what it is, so you ask a gen AI tool to find something to do and do it.
* Skill:
  * GOOD: a skilled developer who knows C, compiler fundamentals, and the Amiga computer system, and uses gen AI tools to improve their productivity.
  * BAD: someone who does not know these and relies on gen AI tools as a substitute for their own learning.
* Understanding:
  * GOOD: a skilled developer who will make the time and effort to understand what the gen AI tool has done.
  * BAD: a "vibe coder" who will drive a gen AI tool, but without the skills and/or effort to understand the output.
* Ownership:
  * GOOD: the contributor takes ownership of the contribution and is able to justify it and answer questions about it.
  * BAD: the contributor delegates reviewer's questions back to the gen AI tool; blames AI for errors.
* Human in the loop:
  * GOOD: the developer is in control - the tools are used with intention by the developer, and review comments and questions are answered by the developer.
  * BAD: the human has handed off control to the tool - review comments and questions are answered by the tool without human involvement.
* Disclosure:
  * GOOD: the contributor is open and clear about their use of gen AI tools in commit metadata and PR details.
  * BAD: the contributor seeks to minimise or hide their use of gen AI tools.

PRs and other contributions where gen AI is used (or strongly suspected to be used) but these rules and guidelines are not adhered to will be rejected. Contributors will be given the opportunity to respond, but in the event of a continuing disagreement, the decision of the project owner is final.
