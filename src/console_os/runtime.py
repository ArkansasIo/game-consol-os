"""Small deterministic host-side model of a console frame runtime.

This module is deliberately hardware-independent. It is useful for contract tests
and examples, but it is not a hardware driver or a bootable kernel.
"""

from dataclasses import dataclass
from typing import FrozenSet, Iterable


@dataclass(frozen=True)
class InputState:
    """Immutable set of pressed logical buttons for a single frame."""

    pressed: FrozenSet[str]

    @classmethod
    def from_buttons(cls, buttons: Iterable[str]) -> "InputState":
        normalized = frozenset(button.strip().upper() for button in buttons)
        if any(not button for button in normalized):
            raise ValueError("button names must not be empty")
        return cls(pressed=normalized)

    def is_pressed(self, button: str) -> bool:
        """Check a logical button name case-insensitively."""
        if not button or not button.strip():
            raise ValueError("button name must not be empty")
        return button.strip().upper() in self.pressed


@dataclass(frozen=True)
class FrameSnapshot:
    """Frame data passed to a simulation or application update."""

    frame_number: int
    input_state: InputState


class ConsoleRuntime:
    """Minimal deterministic frame sequencer for host-side testing."""

    def __init__(self) -> None:
        self._frame_number = 0

    @property
    def frame_number(self) -> int:
        return self._frame_number

    def begin_frame(self, buttons: Iterable[str] = ()) -> FrameSnapshot:
        """Create the next frame snapshot and increment the frame counter."""
        state = InputState.from_buttons(buttons)
        self._frame_number += 1
        return FrameSnapshot(frame_number=self._frame_number, input_state=state)

    def reset(self) -> None:
        """Reset the frame counter, primarily for deterministic tests."""
        self._frame_number = 0
