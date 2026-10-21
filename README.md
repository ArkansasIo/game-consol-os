# Game Consol OS

A modular, homebrew-friendly game console operating-system project. The initial milestone is a **host-runnable reference kernel** with clear interfaces for a future bare-metal or emulator target.

> Status: early scaffold. This repository does not yet contain a bootable console OS image or hardware drivers.

## Goals

- Define a small, deterministic kernel/runtime boundary for a game console.
- Keep hardware-specific code behind platform interfaces.
- Provide input, frame timing, memory, logging, and storage abstractions.
- Make the reference implementation testable on a developer workstation.
- Document the path from host simulation to emulator or physical hardware.

## Current prototype

The Python reference model demonstrates a frame loop and input snapshot. It is not a hardware emulator and does not access physical devices.

### Requirements

- Python 3.11+

### Run

```bash
python -m unittest discover -s tests -v
python examples/run_demo.py
```

## Repository layout

- `docs/ARCHITECTURE.md` — subsystem boundaries and runtime model.
- `docs/ROADMAP.md` — staged implementation plan.
- `docs/SECURITY.md` — trust boundaries and safe development practices.
- `src/console_os/` — host-side reference model.
- `examples/` — executable demonstration.
- `tests/` — unit tests.
- `.github/workflows/ci.yml` — automated checks.

## Design principles

1. **Portability:** hardware access belongs in platform backends, not game-facing APIs.
2. **Determinism:** frame timing and input snapshots should be reproducible in tests.
3. **Explicit ownership:** allocation and resource lifetimes must be documented.
4. **Fail safely:** invalid configuration or unsupported devices should return errors, not silently corrupt state.
5. **Incremental bring-up:** host model first, then emulator, then target hardware.

## Roadmap

See [docs/ROADMAP.md](docs/ROADMAP.md). The next major milestone is a C or Rust target-specific kernel skeleton and emulator-backed boot test.

## License

No license has been declared yet. Until one is added, all rights remain with the repository owner; do not assume this project is open-source licensed for redistribution.
