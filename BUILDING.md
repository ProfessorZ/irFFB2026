# Building irFFB2026

irFFB2026 is a Windows desktop application (Win32 / DirectInput / vJoy). It is
built with Visual Studio; there is no cross-platform or command-line-only build.

## Prerequisites

- **Visual Studio 2022** with the *Desktop development with C++* workload
  (the project uses the **v143** platform toolset).
- **Windows 10/11 SDK** (the project targets `WindowsTargetPlatformVersion 10.0`).
  This provides `dinput8.lib` and `dxguid.lib`; the legacy DirectX SDK is **not**
  required despite a leftover `$(DXSDK_DIR)` library path on the Win32 configs.
- **C++17** (configured for both Debug and Release).
- *(Optional)* the **vJoy** driver/SDK if you want the "Game FFB" (vJoy) modes.
  The vJoy feeder interface is currently vendored in-tree (`vJoyInterface.cpp`),
  so the app builds without the SDK installed; vJoy is only needed at runtime
  for the Game modes.

## Build

1. Open `irFFB2026.sln` in Visual Studio 2022.
2. Select a configuration. **`Release|Win32`** is the canonical configuration
   (it is the one with per-file build settings authored in the project; note the
   solution maps `Debug|Win32` to the `Debug|x64` project configuration).
3. Build → Build Solution (`Ctrl+Shift+B`).
4. The executable is produced in the standard Visual Studio output folder for the
   chosen configuration (e.g. `Release/irFFB2026.exe`).

## Versioning

The version lives in a single place: [`irFFB2026/version.h`](irFFB2026/version.h).
Update the `IRFFB_VER_*` and `IRFFB_VERSION_STR`/`IRFFB_VERSION_WSTR` fields
together when cutting a release; the `.rc` version resource and the About dialog
both read from it. Record changes in [`CHANGELOG.md`](CHANGELOG.md).

## Source encoding (important)

Some files are **not** UTF-8 and editors must preserve their encoding:

- `irFFB.rc`, `resource.h` — **UTF-16 LE** with **CRLF** line endings.
- `irFFB2026.h`, `settings.cpp`, `vjoyinterface.h` — **Windows-1252**.
- `irFFB2026.cpp` — **UTF-8 with BOM**.

Re-saving these as plain UTF-8 will corrupt non-ASCII characters (en/em dashes in
comments, etc.). Configure your editor to keep the existing encoding, or edit the
`.rc` through the Visual Studio resource editor.
