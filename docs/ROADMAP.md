# Roadmap

## Milestone 0 — Repository foundation

- [x] Establish project scope and subsystem boundaries.
- [x] Add a host-runnable reference model.
- [x] Add unit tests and CI.
- [ ] Choose and document an explicit license.
- [ ] Choose the first target: emulator, development board, or custom hardware.

## Milestone 1 — Runtime contracts

- [ ] Define stable C ABI or Rust trait interfaces for clock, input, display, storage, and logging.
- [ ] Add versioned configuration and capability discovery.
- [ ] Add structured error codes and diagnostics.
- [ ] Specify memory ownership and resource lifecycle rules.

## Milestone 2 — Emulated platform

- [ ] Select a suitable emulator and document setup.
- [ ] Add a minimal boot image and serial logging.
- [ ] Add a timer interrupt and exception/interrupt handling.
- [ ] Add emulator smoke tests that verify boot and shutdown.
- [ ] Add framebuffer output and keyboard/controller input.

## Milestone 3 — Kernel services

- [ ] Physical/virtual memory plan and allocator tests.
- [ ] Cooperative scheduler first; preemption only after interrupt and synchronization designs are validated.
- [ ] Process/task isolation and IPC contract.
- [ ] Storage driver and crash-safe metadata format.
- [ ] Diagnostics shell with read-only initial commands.

## Milestone 4 — Game runtime

- [ ] Frame clock and fixed-step simulation support.
- [ ] Controller mapping profiles and hot-plug handling.
- [ ] Asset package format with bounds checking and versioning.
- [ ] Audio and video output interfaces.
- [ ] Developer SDK sample application.

## Milestone 5 — Hardening and releases

- [ ] Fuzz parsers and filesystem metadata.
- [ ] Add memory/resource leak checks where supported.
- [ ] Reproducible build instructions and signed release checksums.
- [ ] Document recovery mode and safe update/rollback.
- [ ] Publish compatibility matrix and release checklist.

## Exit criteria for a bootable prototype

A milestone is complete only when its tests are repeatable and evidence is attached to the release or CI run. A host-side unit test is not proof of bootability on real hardware.
