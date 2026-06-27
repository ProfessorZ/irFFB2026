# Changelog

All notable changes to **irFFB2026** are documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project aims to follow [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

The version is defined in a single place — [`irFFB2026/version.h`](irFFB2026/version.h) —
which feeds both the executable's version resource and the About dialog.

## [Unreleased]

### Added
- **FFB / clipping graph**: a scrolling time graph at the bottom of the main
  window plots FFB output level as a percentage of Max Force over the last
  10 minutes, with clipping highlighted in red and a red 100% ceiling line.
  A live readout shows the current output % and the percentage of the window
  spent clipping. Fed from the existing `setFFB` choke-point (peak level +
  clip flag accumulated between samples), sampled once a second by a
  `WM_TIMER` on the main window and drawn with a double-buffered owner-painted
  child control. The history length is a single constant, `FFB_GRAPH_SECONDS`
  in `irFFB2026.cpp` (set to 600 = 10 min; change to 300 for a 5-minute view).

## [1.2.3]

### Fixed
- Clipping percentage always reported 0.00% when Auto Tune was disabled.
  `samples++` was inside the Auto Tune branch so the denominator never
  advanced; moved it to the unconditional clip-detection block.
- Binary `irFFB.rc` was resolved to 0 bytes by a bad binary-file merge,
  stripping all Windows resources (icons, dialogs, menus, version block)
  and producing a non-functional executable. Restored from the correct
  pre-merge commit.
- `firstAfterReacquire` promoted to `std::atomic<bool>` and checked with
  `exchange(false)` to eliminate a data race between the readWheel thread,
  `reacquireDIDevice()`, and the session-start path.

### Added
- **Bidirectional Auto Tune**: after raising Max Force to stop clipping,
  Auto Tune now gradually lowers it back toward your preferred value once
  clipping stays at zero across a cooldown period, recovering wheel feel
  lost during spike events or tyre wear.
- Improved Quick Tips help panel: added sections for Direct Drive Wheel,
  Smoothing, Bumps Intensity, and Damping; rewrote Max Force guidance with
  a tuning-goal framing; fixed the `app.ini` path; added a numbered
  First Time Setup list.

### Changed
- Session start now calls `resetForces()` and sets `firstAfterReacquire`
  so the wheel gets a clean-state reset when joining a new session, fixing
  the "FFB feels weak on entry" issue.
- Settings load now validates values through the existing setters (with
  range-checking) instead of applying them blindly, and falls back to
  defaults for missing or out-of-range values.

## [1.2.2]

### Fixed
- Per-car settings no longer force a vJoy-only "Game" FFB mode when vJoy is
  unavailable. A `=`/`==` typo (`if (vJoyResult = true)`) had made the safe
  fallback to the vJoy-free irFFB 360 Hz mode unreachable.
- Guarded steering-telemetry indexing (`STmaxIdx`) so a missing or zero-sample
  `_ST` telemetry layout can no longer underflow to `-1` or overrun the
  fixed-size shock/force buffers.
- The settings INI is now validated on read: values are range-checked through
  the existing setters and fall back to defaults instead of being applied
  blindly, and a missing/unreadable INI keeps the current settings.
- The slider edit-box subclass is removed on `WM_NCDESTROY`, preventing a
  callback on a stale window handle during shutdown.

### Changed
- Cross-thread FFB state (`ffbMag`, `nearStops`) now uses `std::atomic` with
  explicit memory ordering instead of `volatile`, fixing a real
  visibility/synchronization gap between the telemetry and wheel threads.
- Default setting values are now defined once (`DEFAULT_*` in `irFFB2026.h`)
  and reused across the generic, registry, and per-car read paths.

### Added
- `version.h` as the single source of truth for the application version, wired
  into the `.rc` version resource and the About dialog.
- `LICENSE` (GPLv3), `CHANGELOG.md`, `CREDITS.md`, and build/architecture docs.

## [1.2.1]

- Enhanced FFB for lighter wheel-force settings.
- Pacejka Magic Formula FFB model for self-aligning torque and vertical-load
  effects, ultra-low-latency 360/720 Hz game modes, Auto Tune, SimHub
  integration, and impact-force reduction.
