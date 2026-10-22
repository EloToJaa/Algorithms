import random
import unittest

from Fenwick.Fenwick import Fenwick, count_smaller_after_self


class TestFenwick(unittest.TestCase):
    def test_against_list(self):
        rng = random.Random(7)
        for _ in range(100):
            values = [rng.randrange(-10, 11) for _ in range(rng.randrange(20))]
            tree = Fenwick(values)
            for _ in range(50):
                if values and rng.random() < 0.5:
                    index = rng.randrange(len(values))
                    delta = rng.randrange(-10, 11)
                    tree.add(index, delta)
                    values[index] += delta
                left = rng.randrange(len(values) + 1)
                right = rng.randrange(left, len(values) + 1)
                self.assertEqual(tree.prefix_sum(right), sum(values[:right]))
                self.assertEqual(tree.range_sum(left, right), sum(values[left:right]))

    def test_lower_bound(self):
        rng = random.Random(8)
        for _ in range(200):
            values = [rng.randrange(4) for _ in range(rng.randrange(20))]
            tree = Fenwick(values)
            for target in range(-1, sum(values) + 3):
                expected = next(
                    (c for c in range(len(values) + 1) if sum(values[:c]) >= target),
                    len(values) + 1,
                )
                self.assertEqual(tree.lower_bound(target), expected)

    def test_count_smaller_after_self(self):
        rng = random.Random(9)
        for _ in range(200):
            nums = [rng.randrange(-5, 6) for _ in range(rng.randrange(15))]
            expected = [
                sum(nums[j] < nums[i] for j in range(i + 1, len(nums)))
                for i in range(len(nums))
            ]
            self.assertEqual(count_smaller_after_self(nums), expected)

    def test_examples(self):
        self.assertEqual(count_smaller_after_self([5, 2, 6, 1]), [2, 1, 1, 0])
        self.assertEqual(count_smaller_after_self([-1, -1]), [0, 0])
        tree = Fenwick([1, 0, 2, 3])
        self.assertEqual(tree.lower_bound(2) - 1, 2)
        self.assertEqual(tree.range_sum(1, 3), 2)


if __name__ == "__main__":
    unittest.main()
