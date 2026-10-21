# GameConsolOS Desktop Application

GameConsolOS is a C++23 console-style desktop environment that runs as a normal application on Windows and macOS. It does not replace the host operating system kernel.

## Runtime layers

```text
Windows / macOS
  -> SDL3 platform layer
  -> GameConsolOS desktop runtime
  -> Core services
  -> GUI/window manager
  -> XMB-inspired shell
  -> application launcher
```

## Services

- Application registry and launcher
- Process/runtime services
- Virtual filesystem
- Persistent settings
- Notifications
- Clipboard abstraction
- Power-action abstraction
- Unified keyboard/gamepad actions
- Audio service API
- Update/patch manager
- Logging and event bus

## Desktop packaging

CMake creates a Windows GUI executable and a macOS `.app` bundle. CPack is configured for Windows ZIP/NSIS and macOS DragNDrop packaging.

SDL's official CMake documentation supports Visual Studio on Windows and Xcode/macOS builds, including universal macOS architectures. See the SDL CMake documentation for platform-specific toolchain details.

## Controls

Keyboard: arrows navigate, Enter/Space activates, Escape backs out, Q exits.

Gamepad: D-pad navigates, South activates, East backs out.

## Security model

The application runs with the permissions granted by the host operating system. Future privileged features must use explicit platform APIs and should never attempt to bypass Windows or macOS security boundaries.
