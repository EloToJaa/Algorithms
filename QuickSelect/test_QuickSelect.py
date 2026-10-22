import random
import unittest
from collections import Counter

from QuickSelect.QuickSelect import k_smallest, quick_select, top_k_frequent


class TestQuickSelect(unittest.TestCase):
    def test_against_sorted(self):
        rng = random.Random(3)
        for _ in range(300):
            nums = [rng.randrange(-5, 6) for _ in range(rng.randrange(1, 30))]
            original = nums[:]
            k = rng.randrange(len(nums))
            self.assertEqual(quick_select(nums, k), sorted(nums)[k])
            self.assertEqual(nums, original)

    def test_k_smallest(self):
        rng = random.Random(4)
        for _ in range(300):
            nums = [rng.randrange(-5, 6) for _ in range(rng.randrange(20))]
            k = rng.randrange(-1, len(nums) + 2)
            expected = sorted(nums)[: max(k, 0)]
            self.assertEqual(sorted(k_smallest(nums, k)), expected)

    def test_top_k_frequent(self):
        rng = random.Random(5)
        for _ in range(300):
            nums = [rng.randrange(8) for _ in range(rng.randrange(1, 30))]
            counts = Counter(nums)
            k = rng.randrange(1, len(counts) + 1)
            result = top_k_frequent(nums, k)
            self.assertEqual(len(set(result)), k)
            expected = sorted(counts.values(), reverse=True)[:k]
            self.assertEqual(
                sorted((counts[v] for v in result), reverse=True), expected
            )

    def test_examples(self):
        self.assertEqual(quick_select([3, 2, 1, 5, 6, 4], 6 - 2), 5)
        self.assertEqual(quick_select([3, 2, 3, 1, 2, 4, 5, 5, 6], 9 - 4), 4)
        self.assertEqual(sorted(top_k_frequent([1, 1, 1, 2, 2, 3], 2)), [1, 2])
        self.assertEqual(top_k_frequent([1], 1), [1])
        self.assertEqual(quick_select([7] * 1000, 500), 7)
        with self.assertRaises(IndexError):
            quick_select([], 0)


if __name__ == "__main__":
    unittest.main()
