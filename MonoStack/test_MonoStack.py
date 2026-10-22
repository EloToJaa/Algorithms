import random
import unittest

from MonoStack.MonoStack import (
    MOD,
    largest_rectangle,
    next_greater,
    previous_smaller,
    sum_subarray_mins,
)


class TestMonoStack(unittest.TestCase):
    def test_against_brute_force(self):
        rng = random.Random(19)
        for _ in range(300):
            n = rng.randrange(12)
            values = [rng.randrange(-3, 4) for _ in range(n)]
            heights = [rng.randrange(5) for _ in range(n)]
            self.assertEqual(
                next_greater(values),
                [
                    next((j for j in range(i + 1, n) if values[j] > values[i]), -1)
                    for i in range(n)
                ],
            )
            self.assertEqual(
                previous_smaller(values),
                [
                    next((j for j in range(i - 1, -1, -1) if values[j] < values[i]), -1)
                    for i in range(n)
                ],
            )
            self.assertEqual(
                largest_rectangle(heights),
                max(
                    (
                        min(heights[i:j]) * (j - i)
                        for i in range(n)
                        for j in range(i + 1, n + 1)
                    ),
                    default=0,
                ),
            )
            self.assertEqual(
                sum_subarray_mins(values),
                sum(min(values[i:j]) for i in range(n) for j in range(i + 1, n + 1))
                % MOD,
            )

    def test_examples(self):
        self.assertEqual(next_greater([2, 1, 2, 4, 3]), [3, 2, 3, -1, -1])
        self.assertEqual(previous_smaller([3, 1, 2, 2, 0]), [-1, -1, 1, 1, -1])
        self.assertEqual(largest_rectangle([2, 1, 5, 6, 2, 3]), 10)
        self.assertEqual(largest_rectangle([2, 4]), 4)
        self.assertEqual(sum_subarray_mins([3, 1, 2, 4]), 17)
        self.assertEqual(sum_subarray_mins([11, 81, 94, 43, 3]), 444)
        self.assertEqual(sum_subarray_mins([2, 2, 2]), 12)


if __name__ == "__main__":
    unittest.main()
