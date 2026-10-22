import random
import unittest

from ZeroOneKnapsack.ZeroOneKnapsack import zero_one_knapsack


class TestZeroOneKnapsack(unittest.TestCase):
    def test_against_subsets(self):
        rng = random.Random(3)
        for _ in range(50):
            items = [(rng.randrange(6), rng.randrange(-2, 10)) for _ in range(8)]
            capacity = rng.randrange(15)
            best = 0
            for mask in range(1 << len(items)):
                chosen = [item for i, item in enumerate(items) if mask & (1 << i)]
                if sum(weight for weight, _ in chosen) <= capacity:
                    best = max(best, sum(value for _, value in chosen))
            self.assertEqual(zero_one_knapsack(items, capacity), best)
        self.assertEqual(zero_one_knapsack([(2, 3)], 6), 3)


if __name__ == "__main__":
    unittest.main()
