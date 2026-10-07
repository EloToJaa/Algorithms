import random
import unittest

from Mo.Mo import distinct_counts


class TestMo(unittest.TestCase):
    def test_against_sets(self):
        rng = random.Random(9)
        for size in range(1, 30):
            values = [rng.randrange(-3, 5) for _ in range(size)]
            queries = [
                (left, rng.randrange(left, size))
                for left in rng.choices(range(size), k=35)
            ]
            self.assertEqual(
                distinct_counts(values, queries),
                [len(set(values[left : right + 1])) for left, right in queries],
            )
        self.assertEqual(distinct_counts([], []), [])


if __name__ == "__main__":
    unittest.main()
