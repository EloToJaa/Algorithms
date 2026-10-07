import random
import unittest

from LIS.LIS import lis_length


class TestLIS(unittest.TestCase):
    def test_against_quadratic_dp(self):
        rng = random.Random(2)
        for size in range(50):
            values = [rng.randrange(-5, 6) for _ in range(size)]
            lengths = []
            for index, value in enumerate(values):
                lengths.append(
                    1
                    + max(
                        (lengths[j] for j in range(index) if values[j] < value),
                        default=0,
                    )
                )
            self.assertEqual(lis_length(values), max(lengths, default=0))
        self.assertEqual(lis_length([2, 2, 2]), 1)


if __name__ == "__main__":
    unittest.main()
