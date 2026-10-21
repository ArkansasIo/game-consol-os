# AAA Console UI Architecture

## Visual direction

The interface uses a **horizontal media-bar / XMB-inspired interaction model**: large centered tiles, neighboring items partially visible, smooth focus transitions, persistent context information, and controller-first navigation.

This is an original implementation and does not copy proprietary PlayStation assets, logos, fonts, source code, or UI artwork.

## C++23 API

The public API is in `include/console_ui/UI.hpp`.

### Core components

- `Application` — owns the top-level console shell.
- `XmbShell` — navigation model, focus state, screen transitions and activation callbacks.
- `UiItem` — data-driven menu item descriptor.
- `UiTheme` — colors, panel styling and focus treatment.
- `Animation` — frame-independent easing and transition timing.
- `InputRouter` — maps controller/application input to semantic navigation events.
- `IRenderer` — renderer abstraction for Vulkan, Direct3D, OpenGL, or a future console backend.

## Navigation model

```text
                 LEFT / RIGHT
                       <>
                        |
        +-------+ +----------+ +-------+
        | Media | |  Games   | | Store |
        +-------+ +----------+ +-------+
                        |
                  CONFIRM / BACK
```

The shell supports wrapping horizontal navigation and skips disabled items.

## Rendering pipeline

```text
Controller Input
      |
 InputRouter
      |
 XmbShell state machine
      |
 Animation / focus interpolation
      |
 IRenderer
      |
 GPU backend
      |
 Display
```

The renderer interface intentionally contains no Vulkan/D3D-specific types. That keeps the console UI API portable.

## Planned AAA systems

1. GPU-backed compositor.
2. HDR-aware color pipeline.
3. 4K/8K UI scaling profiles.
4. Variable refresh-rate presentation synchronization.
5. Controller glyph abstraction.
6. Texture atlas and asynchronous asset streaming.
7. UI sound event bus and haptic event API.
8. User profiles and presence widgets.
9. Game-card metadata and live activity panels.
10. Accessibility scaling, high-contrast and reduced-motion modes.
11. Localization and right-to-left layout support.
12. Screenshot/video capture integration.

These are architectural targets, not claims that the current scaffold implements them.
