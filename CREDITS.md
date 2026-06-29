# Credits & Third-Party Code

irFFB2026 is a fork and evolution of **irFFB** and bundles several third-party
components. This file documents their provenance and licensing.

## irFFB2026

- Copyright (C) 2016 nlp80 and contributors; irFFB2026 by Tom Hogue;
  this fork maintained by ProfessorZ.
- Licensed under the **GNU General Public License v3.0** — see [LICENSE](LICENSE).

## Project lineage

This project is a chain of forks, each building on the last (all GPLv3):

- **irFFB** by **nlp80** — https://github.com/nlp80/irFFB — the original.
- **irFFB2022 / irFFB2026** by **Tom Hogue** — successive rewrites/evolutions
  introducing the Pacejka-based self-aligning-torque model and the low-latency
  360/720 Hz paths.
- **This fork** by **ProfessorZ** — https://github.com/ProfessorZ/irFFB2026 —
  ongoing maintenance and new features (see [CHANGELOG.md](CHANGELOG.md)).

## Vendored third-party code

### iRacing SDK
- Files: `irFFB2026/irsdk_defines.h`, `irFFB2026/irsdk_utils.cpp`,
  `irFFB2026/yaml_parser.h`, `irFFB2026/yaml_parser.cpp`
- Copyright (c) 2013, iRacing.com Motorsport Simulations, LLC.
- License: **BSD 3-Clause** — full text is retained in each file's header.

### vJoy SDK (feeder interface)
- Files: `irFFB2026/vJoyInterface.cpp`, `irFFB2026/vjoyinterface.h`,
  `irFFB2026/public.h`
- Copyright (c) Shaul Eizikovich. Upstream: http://vjoystick.sourceforge.net
- Provided "AS IS" (see the notice in `public.h`).
- **NOTE:** the exact redistribution terms of the bundled vJoy SDK version should
  be confirmed by the maintainer. Linking against the user-installed vJoy SDK
  instead of vendoring this ~2,600-line copy is tracked as future work.

## Acknowledgements

- **@Grok** — assistance with the Pacejka-based FFB rework (per the
  `irFFB2026.cpp` source header).
