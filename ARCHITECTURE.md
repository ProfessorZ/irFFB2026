# Architecture

A high-level map of how irFFB2026 turns iRacing telemetry into wheel force
feedback. The bulk of the engine lives in `irFFB2026/irFFB2026.cpp`.

## Threads

irFFB2026 runs three cooperating threads:

1. **Main / telemetry thread** (`wWinMain`) — pumps the Win32 message loop and,
   each telemetry tick, reads the iRacing SDK (steering torque, slip, yaw, shock
   velocities, etc.), computes the FFB via a Pacejka-style self-aligning-torque +
   vertical-load model, and publishes the result into a double buffer.
2. **`readWheelThread`** — polls the DirectInput wheel, applies damping/velocity
   filtering, and writes the computed force to the device effect. Used for the
   `IRFFB` (non-vJoy) modes.
3. **`directFFBThread`** — for the vJoy "Game" modes; consumes the published
   buffer and emits the interpolated 360/720 Hz signal.

## Shared state and the double buffer

The force samples (`yawForce`, `ffbForce`, `suspForceST`) are stored in
double-buffered arrays indexed by `activeBuffer` (`std::atomic<int>`):

- The writer fills the **back** buffer (`1 - activeBuffer`) and then publishes it
  with `activeBuffer.store(writeBuf, memory_order_release)`.
- Consumers read `activeBuffer.load(memory_order_acquire)` and use that index.

That release/acquire pair establishes the happens-before relationship that makes
the buffer contents safely visible across threads. Other cross-thread control
values (`ffbMag`, `nearStops`) are `std::atomic` with explicit memory ordering.
**Preserve this protocol when editing the hot path.**

## FFB model

Forces are derived from a simplified Pacejka Magic Formula: self-aligning torque
from slip/load for oversteer/understeer feel, plus vertical-load/shock terms for
bumps and weight transfer, layered on top of iRacing's native signal and
interpolated at 360/720 Hz with spike filtering and high-G impact reduction. Tuning
constants currently live inline in `irFFB2026.cpp`.

## Settings persistence

- **Registry** (`HKCU\Software\irFFB2026\Settings`): FFB device GUID, start-minimised
  flag, and the generic/default settings.
- **INI** (`Documents\irFFB2026.ini`): per-car / per-track settings, one line per
  combo. Defaults come from the `DEFAULT_*` constants in `irFFB2026.h`; values are
  range-validated on load (see `Settings::readSettingsForCar`).

## UI

Raw Win32: controls are created directly (`combo`, `slider`, `checkbox`) with the
window procedure routing messages by control. The layout uses fixed pixel
coordinates and is not yet DPI-aware (tracked as future work).

The **FFB / clipping graph** at the bottom is an owner-painted child window
(`ffbGraphProc`, class `irFFBGraphClass`) showing a scrolling history of FFB
output level (% of Max Force) with clipping highlighted. The FFB hot path
(`setFFB`) accumulates a peak level and a clip flag into two atomics
(`ffbGraphPeak` / `ffbGraphClip`); a 1 Hz `WM_TIMER` on the main window reads-
and-resets them into a ring buffer (UI thread only) and repaints. History length
is the `FFB_GRAPH_SECONDS` constant (default 600 s).
