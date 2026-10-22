import random
import unittest

from UnboundedKnapsack.UnboundedKnapsack import unbounded_knapsack


def brute_force(items: list[tuple[int, int]], capacity: int) -> int:
    best = 0  # stopping is always allowed
    for weight, value in items:
        if weight <= capacity:
            best = max(best, value + brute_force(items, capacity - weight))
    return best


class TestUnboundedKnapsack(unittest.TestCase):
    def test_against_recursion(self):
        rng = random.Random(4)
        for _ in range(100):
            items = [(rng.randrange(1, 7), rng.randrange(-2, 10)) for _ in range(4)]
            capacity = rng.randrange(14)
            self.assertEqual(
                unbounded_knapsack(items, capacity), brute_force(items, capacity)
            )

    def test_examples(self):
        self.assertEqual(unbounded_knapsack([(2, 3)], 7), 9)
        self.assertEqual(unbounded_knapsack([(3, 4), (4, 5), (2, 3)], 7), 10)
        self.assertEqual(unbounded_knapsack([], 5), 0)


if __name__ == "__main__":
    unittest.main()
