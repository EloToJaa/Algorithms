import random
import unittest

from PrefixSum.PrefixSum import (
    PrefixSum2D,
    apply_range_additions,
    count_subarrays_with_sum,
    prefix_sums,
    range_sum,
)


class TestPrefixSum(unittest.TestCase):
    def test_against_brute_force(self):
        rng = random.Random(13)
        for _ in range(200):
            n = rng.randrange(10)
            values = [rng.randrange(-4, 5) for _ in range(n)]
            prefix = prefix_sums(values)
            for left in range(n + 1):
                for right in range(left, n + 1):
                    self.assertEqual(
                        range_sum(prefix, left, right), sum(values[left:right])
                    )
            k = rng.randrange(-4, 5)
            self.assertEqual(
                count_subarrays_with_sum(values, k),
                sum(
                    sum(values[i:j]) == k for i in range(n) for j in range(i + 1, n + 1)
                ),
            )
            updates = []
            expected = [0] * n
            for _ in range(rng.randrange(5) if n else 0):
                left = rng.randrange(n)
                right = rng.randrange(left, n)
                delta = rng.randrange(-5, 6)
                updates.append((left, right, delta))
                for i in range(left, right + 1):
                    expected[i] += delta
            self.assertEqual(apply_range_additions(n, updates), expected)

    def test_2d_against_brute_force(self):
        rng = random.Random(17)
        for _ in range(50):
            rows, columns = rng.randrange(1, 6), rng.randrange(1, 6)
            matrix = [
                [rng.randrange(-5, 6) for _ in range(columns)] for _ in range(rows)
            ]
            table = PrefixSum2D(matrix)
            for _ in range(20):
                r1, r2 = sorted(rng.randrange(rows) for _ in range(2))
                c1, c2 = sorted(rng.randrange(columns) for _ in range(2))
                expected = sum(
                    matrix[r][c] for r in range(r1, r2 + 1) for c in range(c1, c2 + 1)
                )
                self.assertEqual(table.sum_region(r1, c1, r2, c2), expected)

    def test_examples(self):
        matrix = [
            [3, 0, 1, 4, 2],
            [5, 6, 3, 2, 1],
            [1, 2, 0, 1, 5],
            [4, 1, 0, 1, 7],
            [1, 0, 3, 0, 5],
        ]
        table = PrefixSum2D(matrix)
        self.assertEqual(table.sum_region(2, 1, 4, 3), 8)
        self.assertEqual(table.sum_region(1, 1, 2, 2), 11)
        self.assertEqual(table.sum_region(1, 2, 2, 4), 12)
        self.assertEqual(count_subarrays_with_sum([1, 1, 1], 2), 2)
        self.assertEqual(count_subarrays_with_sum([1, 2, 3], 3), 2)
        self.assertEqual(
            apply_range_additions(5, [(1, 3, 2), (2, 4, 3), (0, 2, -2)]),
            [-2, 0, 3, 5, 3],
        )
        self.assertEqual(range_sum(prefix_sums([-2, 0, 3, -5, 2, -1]), 0, 3), 1)


if __name__ == "__main__":
    unittest.main()
