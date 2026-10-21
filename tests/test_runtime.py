import unittest

from console_os import ConsoleRuntime, InputState


class InputStateTests(unittest.TestCase):
    def test_button_names_are_case_insensitive(self):
        state = InputState.from_buttons(["a", "Start"])
        self.assertTrue(state.is_pressed("A"))
        self.assertTrue(state.is_pressed("start"))
        self.assertFalse(state.is_pressed("B"))

    def test_duplicate_buttons_are_normalized(self):
        state = InputState.from_buttons(["A", "a", " A "])
        self.assertEqual(state.pressed, frozenset({"A"}))

    def test_empty_button_name_is_rejected(self):
        with self.assertRaises(ValueError):
            InputState.from_buttons(["A", "  "])

    def test_empty_query_is_rejected(self):
        with self.assertRaises(ValueError):
            InputState.from_buttons(["A"]).is_pressed(" ")


class ConsoleRuntimeTests(unittest.TestCase):
    def test_frames_increase_monotonically(self):
        runtime = ConsoleRuntime()
        first = runtime.begin_frame(["A"])
        second = runtime.begin_frame(["B"])
        self.assertEqual((first.frame_number, second.frame_number), (1, 2))
        self.assertTrue(first.input_state.is_pressed("A"))
        self.assertFalse(first.input_state.is_pressed("B"))

    def test_reset_restarts_frame_counter(self):
        runtime = ConsoleRuntime()
        runtime.begin_frame()
        runtime.reset()
        self.assertEqual(runtime.frame_number, 0)
        self.assertEqual(runtime.begin_frame().frame_number, 1)


if __name__ == "__main__":
    unittest.main()
