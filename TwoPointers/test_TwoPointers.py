import random
import unittest
from itertools import combinations

from TwoPointers.TwoPointers import max_area, pair_with_sum, three_sum, trap


def brute_trap(heights):
    return sum(
        max(0, min(max(heights[: i + 1]), max(heights[i:])) - height)
        for i, height in enumerate(heights)
    )


class TestTwoPointers(unittest.TestCase):
    def test_against_brute_force(self):
        rng = random.Random(7)
        for _ in range(300):
            values = [rng.randrange(-6, 7) for _ in range(rng.randrange(10))]
            heights = [rng.randrange(8) for _ in range(rng.randrange(10))]
            target = rng.randrange(-8, 9)
            ordered = sorted(values)
            pair = pair_with_sum(ordered, target)
            pairs = list(combinations(range(len(ordered)), 2))
            if pair is None:
                self.assertFalse(
                    any(ordered[i] + ordered[j] == target for i, j in pairs)
                )
            else:
                i, j = pair
                self.assertTrue(i < j and ordered[i] + ordered[j] == target)
            self.assertEqual(
                three_sum(values, target),
                sorted({t for t in combinations(ordered, 3) if sum(t) == target}),
            )
            self.assertEqual(
                max_area(heights),
                max(
                    (
                        (j - i) * min(heights[i], heights[j])
                        for i, j in combinations(range(len(heights)), 2)
                    ),
                    default=0,
                ),
            )
            self.assertEqual(trap(heights), brute_trap(heights))

    def test_examples(self):
        self.assertEqual(pair_with_sum([2, 7, 11, 15], 9), (0, 1))
        self.assertIsNone(pair_with_sum([1, 2], 4))
        self.assertEqual(three_sum([-1, 0, 1, 2, -1, -4]), [(-1, -1, 2), (-1, 0, 1)])
        self.assertEqual(three_sum([0, 0, 0, 0]), [(0, 0, 0)])
        self.assertEqual(max_area([1, 8, 6, 2, 5, 4, 8, 3, 7]), 49)
        self.assertEqual(trap([0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]), 6)
        self.assertEqual(trap([4, 2, 0, 3, 2, 5]), 9)


if __name__ == "__main__":
    unittest.main()
