import random
import unittest
from collections import Counter

from SlidingWindow.SlidingWindow import (
    count_at_most_k_distinct,
    count_exactly_k_distinct,
    longest_at_most_k_distinct,
    longest_unique_substring,
    min_window,
)


def subarrays(values):
    return [
        values[i:j] for i in range(len(values)) for j in range(i + 1, len(values) + 1)
    ]


def brute_min_window(text, pattern):
    need = Counter(pattern)
    candidates = [window for window in subarrays(text) if not need - Counter(window)]
    return min(candidates, key=len, default="")


class TestSlidingWindow(unittest.TestCase):
    def test_against_brute_force(self):
        rng = random.Random(3)
        for _ in range(300):
            text = "".join(rng.choice("abcd") for _ in range(rng.randrange(12)))
            pattern = "".join(rng.choice("abcd") for _ in range(rng.randrange(1, 4)))
            k = rng.randrange(5)
            windows = subarrays(text)
            self.assertEqual(
                longest_unique_substring(text),
                max((len(w) for w in windows if len(set(w)) == len(w)), default=0),
            )
            result = min_window(text, pattern)
            self.assertEqual(len(result), len(brute_min_window(text, pattern)))
            self.assertTrue(not result or not Counter(pattern) - Counter(result))
            self.assertIn(result, text)
            self.assertEqual(
                longest_at_most_k_distinct(text, k),
                max((len(w) for w in windows if len(set(w)) <= k), default=0),
            )
            self.assertEqual(
                count_at_most_k_distinct(text, k),
                sum(len(set(w)) <= k for w in windows),
            )
            self.assertEqual(
                count_exactly_k_distinct(text, k),
                sum(len(set(w)) == k for w in windows),
            )

    def test_examples(self):
        self.assertEqual(longest_unique_substring("abcabcbb"), 3)
        self.assertEqual(longest_unique_substring("pwwkew"), 3)
        self.assertEqual(min_window("ADOBECODEBANC", "ABC"), "BANC")
        self.assertEqual(min_window("a", "aa"), "")
        self.assertEqual(longest_at_most_k_distinct("eceba", 2), 3)
        self.assertEqual(longest_at_most_k_distinct([1, 2, 3, 2, 2], 2), 4)
        self.assertEqual(count_exactly_k_distinct([1, 2, 1, 2, 3], 2), 7)
        self.assertEqual(count_exactly_k_distinct([1, 2, 1, 3, 4], 3), 3)


if __name__ == "__main__":
    unittest.main()
