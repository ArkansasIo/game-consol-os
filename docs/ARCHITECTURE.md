# Architecture

## Scope

The project separates a portable console runtime from the machine-specific boot and device layers. The current Python code is a reference model for concepts and tests, not a production kernel.

## Layer model

```text
Game / Homebrew Applications
            |
      Console Runtime API
 (frame, input, resources, logging)
            |
      Kernel Services
 (scheduler, memory, storage, IPC)
            |
     Platform Abstraction
 (clock, display, input, block device)
            |
 Bootloader / Firmware / Hardware
```

## Runtime services

- **Frame clock:** monotonic frame identifiers and elapsed-time measurement. A real backend must use a monotonic hardware timer.
- **Input:** each frame receives an immutable snapshot of current buttons and axes. Device polling belongs in the platform backend.
- **Memory:** define ownership, allocation failure, alignment, and lifetime semantics before exposing APIs to applications.
- **Display:** rendering should target a documented framebuffer or command queue contract. Presentation and synchronization are platform concerns.
- **Storage:** use a versioned filesystem or block-device contract; validate sizes and metadata before trusting them.
- **Logging:** provide bounded messages and log levels. Avoid logging secrets or raw user data.

## Frame lifecycle

1. The platform backend samples devices.
2. The runtime builds an immutable input snapshot.
3. The scheduler advances the simulation.
4. Applications submit rendering work.
5. The display backend presents the frame and records timing.

The host prototype implements only the input snapshot and frame-counter concepts.

## Error handling

Use explicit result values for expected failures (missing device, invalid configuration, capacity exceeded). Reserve panics/exceptions for programmer errors or unrecoverable conditions. Do not report success when a device has not actually initialized.

## Target implementation choices

Before selecting a boot protocol or language runtime, record the target CPU/SoC, memory map, display interface, input hardware, storage device, and emulator. Keep target-specific assumptions in a `platform/<target>/` directory and in target-specific documentation.
