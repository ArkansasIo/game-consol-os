"""Run a short demonstration of the host-side frame model."""

from console_os import ConsoleRuntime


def main() -> None:
    runtime = ConsoleRuntime()
    input_sequence = [
        ("A",),
        ("A", "START"),
        (),
    ]

    for buttons in input_sequence:
        frame = runtime.begin_frame(buttons)
        pressed = ", ".join(sorted(frame.input_state.pressed)) or "(none)"
        print(f"frame={frame.frame_number:03d} input={pressed}")


if __name__ == "__main__":
    main()
