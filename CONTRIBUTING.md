# Contributing to irFFB2026

Thanks for helping improve irFFB2026! A few notes specific to this project.

## Workflow

1. Create a feature branch from the development branch.
2. Make focused changes and build **`Release|Win32`** in Visual Studio 2022
   (see [BUILDING.md](BUILDING.md)).
3. Update [`CHANGELOG.md`](CHANGELOG.md), and bump
   [`irFFB2026/version.h`](irFFB2026/version.h) when releasing.
4. Open a PR describing what changed and how you tested it.

## Testing expectations

There is no automated test suite, and the FFB engine cannot be meaningfully
validated without hardware. **Any change that affects FFB physics, timing, or the
threading/double-buffer hot path must be tested on a real wheel in iRacing** before
it is merged — a clean build is necessary but not sufficient. Mention your test
setup (wheel, car, track) in the PR.

## Source encoding

Several files are not UTF-8 and must keep their encoding (see the *Source
encoding* section of [BUILDING.md](BUILDING.md)). Don't let your editor re-save
`irFFB.rc`/`resource.h` (UTF-16 LE, CRLF) or the Windows-1252 sources as plain
UTF-8 — it silently corrupts non-ASCII characters. Edit the `.rc` via the Visual
Studio resource editor where possible.

## Style

Match the surrounding code. Keep diffs minimal and avoid repo-wide reformatting so
that history and `git blame` stay useful.

## Third-party code

`irsdk_*` / `yaml_parser.*` (iRacing SDK, BSD-3-Clause) and the vJoy SDK files are
vendored — see [CREDITS.md](CREDITS.md). Prefer updating them from upstream rather
than editing in place.
