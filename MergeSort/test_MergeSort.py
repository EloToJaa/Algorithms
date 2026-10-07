import random
import unittest

from MergeSort.MergeSort import merge_sort


class TestMergeSort(unittest.TestCase):
    def test_against_builtin_sort(self):
        rng = random.Random(8)
        samples = [
            [],
            [1],
            [3, 1, 2],
            [1, 1, 1],
            list(range(80)),
            list(range(80, -1, -1)),
        ]
        samples += [
            [rng.randrange(-20, 20) for _ in range(size)] for size in range(100)
        ]
        for values in samples:
            original = values.copy()
            self.assertEqual(merge_sort(values), sorted(values))
            self.assertEqual(values, original)


if __name__ == "__main__":
    unittest.main()
