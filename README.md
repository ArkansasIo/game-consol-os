# Game Consol OS

A modular, homebrew-friendly game console OS application framework. It now includes a **C++23 desktop application** that runs as a normal resizable window on Windows and macOS, plus the Python reference runtime and reusable OS/UI services.

> Status: host desktop application / OS-shell prototype. This is not a bootable replacement kernel for Windows or macOS.

## Desktop application

`GameConsolOS` runs **inside the host operating system** as a normal desktop application. It does not replace Windows or macOS. The same C++23 UI/runtime code is built for both platforms through CMake and SDL3.

The desktop layer provides:

- Native OS window creation through SDL3.
- Hardware-accelerated SDL renderer selection.
- High-DPI/resizable window support.
- Keyboard navigation with arrow keys, Enter/Space, Escape, and Q.
- Gamepad/D-pad/A-B style navigation through SDL3 gamepad input.
- Desktop font loading with `GAMECONSOL_FONT` override.
- XMB-inspired horizontal console shell.
- Games / Media / Library / Store / Profile / Settings navigation.
- Headless CI smoke-test mode with `--headless`.

SDL3 is used as the portability layer so the application can share one C++ implementation across Windows and macOS; CMake supports generating native build systems and application bundles/installers across platforms. citeturn0search0turn0search1

## Windows

Install Visual Studio 2022+ with C++ desktop development and CMake, then:

```powershell
cmake -S . -B build -A x64
cmake --build build --config Release
.\build\Release\game_consol_demo.exe
```

For CI/headless validation:

```powershell
.\build\Release\game_consol_demo.exe --headless
```

## macOS

Install Xcode Command Line Tools and CMake:

```bash
cmake -S . -B build -G Xcode -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
open build/Release/game_consol_demo.app
```

CMake supports the Xcode generator on Apple platforms and can generate macOS application bundles. citeturn0search8

## C++23 framework

The project contains reusable layers for:

- `gameos::core::Kernel`
- `gameos::core::EventBus`
- `gameos::core::ProcessManager`
- `gameos::core::VirtualFileSystem`
- `gameos::core::Logger`
- `gameos::core::ConfigStore`
- `gameos::update::UpdateManager`
- `gameos::gui::Scene`
- `gameos::gui::Widget`
- `gameos::gui::WindowManager`
- `gameos::platform::DesktopApp`
- `gameos::platform::DesktopRenderer`
- `console::ui::XmbShell`

See [`docs/FRAMEWORK.md`](docs/FRAMEWORK.md), [`docs/DESKTOP_APP.md`](docs/DESKTOP_APP.md), and [`docs/AAA_UI.md`](docs/AAA_UI.md).

## Build and test

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
ctest --test-dir build --output-on-failure
./build/game_consol_demo --headless
```

The build fetches SDL3 and SDL_ttf at configure time. The repository pins the SDL3 release used by the desktop build rather than depending on a locally installed copy.

## Python reference prototype

```bash
python -m unittest discover -s tests -v
python examples/run_demo.py
```

## Repository layout

- `include/console_ui/` — public C++23 console UI API.
- `src/console_ui/` — C++23 shell implementation.
- `include/gameos/` — OS, update, GUI, and desktop public APIs.
- `src/gameos/` — OS services and desktop implementation.
- `src/main.cpp` — desktop application entry point.
- `tests/cpp/` — C++ tests.
- `docs/` — architecture and implementation documentation.
- `.github/workflows/ci.yml` — Python and C++ CI.

## Important distinction

This project is an **OS-style shell/application environment**, not a kernel that boots instead of Windows or macOS. The desktop build runs on top of the host OS. A future dedicated-hardware target can reuse the core abstractions behind a different platform layer.

## License

No license has been declared yet. Until one is added, all rights remain with the repository owner; do not assume this project is open-source licensed for redistribution.
