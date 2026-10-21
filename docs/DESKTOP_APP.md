# GameConsolOS Desktop Application

## Purpose

GameConsolOS is currently designed to run **on top of a host operating system**. The Windows and macOS builds are ordinary desktop applications. They do not replace the host kernel, modify the host bootloader, or require a custom boot image.

## Architecture

```text
Windows / macOS
      │
      ▼
   SDL3 platform layer
      │
      ├── Window
      ├── Keyboard
      ├── Gamepad
      ├── High-DPI
      └── Renderer
      │
      ▼
 gameos::platform::DesktopApp
      │
      ├── gameos::core
      ├── gameos::update
      ├── gameos::gui
      └── console::ui::XmbShell
      │
      ▼
 DesktopRenderer
      │
      └── SDL3 hardware renderer
```

SDL3 provides the cross-platform desktop/window and input boundary. CMake generates the native build environment; on macOS it can generate an Xcode application bundle and on Windows it can generate Visual Studio projects. citeturn0search0turn0search8

## Controls

| Input | Action |
|---|---|
| Left / Right | Change shell item |
| Up / Down | Navigate semantic direction |
| Enter / Space | Activate |
| Escape | Back |
| Q | Quit |
| Gamepad D-pad | Navigate |
| Gamepad South button | Activate |
| Gamepad East button | Back |

## Font selection

The renderer searches for a platform font automatically. For deterministic development or packaging, set:

```text
GAMECONSOL_FONT=/path/to/font.ttf
```

Windows example:

```powershell
$env:GAMECONSOL_FONT="C:\Windows\Fonts\segoeui.ttf"
```

macOS example:

```bash
export GAMECONSOL_FONT="/System/Library/Fonts/Supplemental/Arial.ttf"
```

## Windows build

```powershell
cmake -S . -B build -A x64
cmake --build build --config Release
.\build\Release\game_consol_demo.exe
```

## macOS build

```bash
cmake -S . -B build -G Xcode
cmake --build build --config Release
open build/Release/game_consol_demo.app
```

## Headless mode

CI and automated validation should use:

```text
./game_consol_demo --headless
```

Headless mode does not create a desktop window. It initializes the application state, advances one frame, and exits successfully.

## Packaging direction

The next packaging layer should produce:

- Windows `.exe` plus installer package.
- macOS `.app` plus signed/notarized distribution package.
- Versioned application data directories.
- User configuration migration.
- Crash-safe update slots.
- Signed update manifests and payload verification.

The update manager in the repository is only the local lifecycle primitive; it is not yet a complete secure distribution system.
