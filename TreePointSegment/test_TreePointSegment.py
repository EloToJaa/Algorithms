import random
import unittest

from TreePointSegment.TreePointSegment import PointRangeMax


class TestTreePointSegment(unittest.TestCase):
    def test_random_assignments_and_maxima(self):
        rng = random.Random(15)
        for size in (1, 3, 8, 15):
            values = [rng.randrange(-20, 0) for _ in range(size)]
            tree = PointRangeMax(values)
            for _ in range(150):
                if rng.random() < 0.5:
                    index, value = rng.randrange(size), rng.randrange(-50, 50)
                    values[index] = value
                    tree.update(index, value)
                else:
                    left = rng.randrange(size)
                    right = rng.randrange(left, size)
                    self.assertEqual(
                        tree.query(left, right), max(values[left : right + 1])
                    )


if __name__ == "__main__":
    unittest.main()
