import random
import unittest

from TreeSegmentSegment.TreeSegmentSegment import RangeAddSum


class TestTreeSegmentSegment(unittest.TestCase):
    def test_random_overlapping_additions_and_sums(self):
        rng = random.Random(17)
        for size in (1, 3, 8, 15):
            values = [rng.randrange(-20, 20) for _ in range(size)]
            tree = RangeAddSum(values)
            for _ in range(150):
                left = rng.randrange(size)
                right = rng.randrange(left, size)
                if rng.random() < 0.5:
                    change = rng.randrange(-20, 20)
                    tree.update(left, right, change)
                    for i in range(left, right + 1):
                        values[i] += change
                else:
                    self.assertEqual(
                        tree.query(left, right), sum(values[left : right + 1])
                    )


if __name__ == "__main__":
    unittest.main()
