# GameConsolOS C++23 Framework

## Runtime

`Kernel` owns subsystem startup, frame ticks, shutdown ordering, and panic reporting. Subsystems implement `ISubsystem`, so platform services can be replaced without changing the GUI layer.

## OS services

- `ProcessManager`: process IDs and Running/Suspended/Stopped lifecycle.
- `EventBus`: topic-based application and system events.
- `VirtualFileSystem`: application data root and file access.
- `Logger`: diagnostics to file and stderr.
- `ConfigStore`: persistent key/value settings.

## GUI API

`WindowManager -> Scene -> Widget -> Canvas -> renderer backend` is the primary retained-mode UI path. `Label` and `Button` are the first reusable controls. The existing `console_ui::XmbShell` remains the console home/navigation shell.

The `Canvas` contract deliberately hides GPU details so a future Vulkan, Direct3D 12, Metal, OpenGL, or software renderer can be selected per platform.

## Update / patch API

`UpdateManifest` describes an update and its payload files. `UpdateManager` supports validation, staging, application and rollback primitives. A production updater must add cryptographic signature verification, trusted-key management, hash verification, crash-safe version slots and anti-downgrade policy before consuming network-delivered packages.

## Next implementation layer

1. Native Win32/Linux/macOS platform abstraction.
2. SDL3 or native controller/gamepad backend.
3. Vulkan/D3D12 renderer and shader pipeline.
4. Texture atlas, font rasterization, HDR compositor and post-processing.
5. UI audio/haptics event service.
6. Package manager with signed manifests and delta patches.
7. Secure boot/update chain for a dedicated hardware target.
8. Application sandbox and capability permissions.
