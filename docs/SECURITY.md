# Security and Safe Development

## Trust boundaries

Treat application packages, saved data, controller events, asset files, storage metadata, and host/emulator input as untrusted. Validate lengths, versions, offsets, counts, and arithmetic before allocating memory or reading data.

## Development requirements

- Do not run downloaded game packages or firmware with elevated privileges.
- Keep test ROMs, proprietary firmware, and personal saves out of the repository unless redistribution rights are clear.
- Do not store access tokens, signing keys, passwords, or private configuration in source control.
- Build external parsers with bounded input sizes and fuzz malformed data.
- Use least privilege for CI permissions; only grant write permissions to workflows that require them.
- Pin third-party actions to reviewed immutable commit SHAs for release-grade workflows.
- Produce checksums for release artifacts and document their provenance.

## Failure handling

Device initialization failure should leave the affected subsystem unavailable rather than returning a fabricated success state. A failed storage write must be reported to the caller. Avoid silently ignoring corrupted metadata or unsupported versions.

## Responsible scope

This repository is an OS/runtime scaffold. It does not include proprietary console keys, firmware extraction instructions, or mechanisms to bypass platform security controls.
