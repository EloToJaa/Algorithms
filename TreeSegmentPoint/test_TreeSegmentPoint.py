import random
import unittest

from TreeSegmentPoint.TreeSegmentPoint import RangeAddPoint


class TestTreeSegmentPoint(unittest.TestCase):
    def test_random_overlapping_additions(self):
        rng = random.Random(16)
        for size in (1, 3, 8, 15):
            values = [rng.randrange(-20, 20) for _ in range(size)]
            tree = RangeAddPoint(values)
            for _ in range(150):
                left = rng.randrange(size)
                right = rng.randrange(left, size)
                change = rng.randrange(-20, 20)
                tree.update(left, right, change)
                for i in range(left, right + 1):
                    values[i] += change
                self.assertEqual([tree.query(i) for i in range(size)], values)


if __name__ == "__main__":
    unittest.main()
