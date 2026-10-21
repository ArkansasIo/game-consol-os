# Game Consol OS

A modular, homebrew-friendly game console operating-system project. The repository now includes a **C++23 console UI framework** with an original horizontal media-bar/XMB-inspired interaction model, alongside the Python reference runtime.

> Status: early scaffold. The project does not yet contain a bootable console OS image or physical-console hardware drivers.

## Goals

- Define a deterministic kernel/runtime boundary for a game console.
- Provide a controller-first C++23 UI API suitable for an AAA-style console shell.
- Keep hardware-specific graphics code behind a renderer interface.
- Provide input, frame timing, memory, logging, and storage abstractions.
- Make the reference implementation testable on a developer workstation.
- Document the path from host simulation to emulator or physical hardware.

## C++23 UI prototype

The UI lives under `include/console_ui/` and `src/console_ui/`.

It provides:

- `XmbShell` horizontal navigation and focus management.
- `UiItem`, `UiTheme`, `UiTransform`, and screen descriptors.
- Controller-oriented `InputRouter` semantic input.
- `Animation` with linear, ease-out-cubic, and ease-in-out-cubic easing.
- `IRenderer` abstraction for Vulkan, Direct3D, OpenGL, or a future console GPU backend.
- `Application` that builds the initial Games / Media / Library / Store / Profile / Settings shell.

The visual direction is **XMB-inspired**, not a reproduction of proprietary PlayStation source code, artwork, fonts, logos, or assets.

See [`docs/AAA_UI.md`](docs/AAA_UI.md) for the architecture and planned AAA systems.

### Build C++23 UI

Requirements: CMake 3.24+ and a C++23 compiler.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
ctest --test-dir build --output-on-failure
./build/game_consol_demo
```

## Python reference prototype

Requirements: Python 3.11+

```bash
python -m unittest discover -s tests -v
python examples/run_demo.py
```

## Repository layout

- `include/console_ui/` — public C++23 console UI API.
- `src/console_ui/` — C++23 implementation.
- `src/main.cpp` — host UI demonstration entry point.
- `tests/cpp/` — C++ UI tests.
- `docs/AAA_UI.md` — AAA/XMB-inspired UI design.
- `docs/ARCHITECTURE.md` — subsystem boundaries and runtime model.
- `docs/ROADMAP.md` — staged implementation plan.
- `docs/SECURITY.md` — trust boundaries and safe development practices.
- `src/console_os/` — Python host-side reference model.
- `examples/` — Python demonstration.
- `.github/workflows/ci.yml` — Python and C++ CI.

## Design principles

1. **Portability:** hardware access belongs in platform backends, not game-facing APIs.
2. **Determinism:** frame timing, navigation, and input snapshots should be reproducible in tests.
3. **Explicit ownership:** allocation and resource lifetimes must be documented.
4. **Fail safely:** invalid configuration or unsupported devices should return errors, not silently corrupt state.
5. **Incremental bring-up:** host model first, renderer backend next, emulator next, then target hardware.

## Roadmap

See [docs/ROADMAP.md](docs/ROADMAP.md). The next major milestone is a C++23 target-specific kernel/runtime skeleton plus a real GPU renderer backend.

## License

No license has been declared yet. Until one is added, all rights remain with the repository owner; do not assume this project is open-source licensed for redistribution.
