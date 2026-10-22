import random
import unittest
from itertools import combinations, combinations_with_replacement

from ClassicDP.ClassicDP import (
    coin_change,
    coin_change_ordered_ways,
    coin_change_ways,
    min_path_sum,
    rob,
    rob_circular,
    unique_paths_with_obstacles,
    word_break,
)


def brute_rob(nums: list[int], circular: bool) -> int:
    n = len(nums)
    best = 0
    for size in range(n + 1):
        for chosen in combinations(range(n), size):
            if any(b - a == 1 for a, b in zip(chosen, chosen[1:], strict=False)):
                continue
            if (
                circular
                and n > 1
                and size > 1
                and chosen[0] == 0
                and chosen[-1] == n - 1
            ):
                continue
            best = max(best, sum(nums[i] for i in chosen))
    return best


def multisets(coins: list[int], amount: int) -> list[tuple[int, ...]]:
    return [
        chosen
        for size in range(amount + 1)
        for chosen in combinations_with_replacement(coins, size)
        if sum(chosen) == amount
    ]


def sequences(coins: list[int], amount: int) -> int:
    if amount == 0:
        return 1
    return sum(sequences(coins, amount - c) for c in coins if c <= amount)


def all_paths(grid: list[list[int]], i: int = 0, j: int = 0) -> list[list[int]]:
    """Every right/down path as its list of cell values (obstacles allowed)."""
    rows, cols = len(grid), len(grid[0])
    if i == rows - 1 and j == cols - 1:
        return [[grid[i][j]]]
    result = []
    if i + 1 < rows:
        result += [[grid[i][j]] + path for path in all_paths(grid, i + 1, j)]
    if j + 1 < cols:
        result += [[grid[i][j]] + path for path in all_paths(grid, i, j + 1)]
    return result


def brute_word_break(text: str, words: list[str]) -> bool:
    if not text:
        return True
    return any(
        text.startswith(word) and brute_word_break(text[len(word) :], words)
        for word in words
        if word
    )


class TestClassicDP(unittest.TestCase):
    def test_house_robber(self):
        rng = random.Random(1)
        for _ in range(300):
            nums = [rng.randrange(10) for _ in range(rng.randrange(9))]
            self.assertEqual(rob(nums), brute_rob(nums, False))
            self.assertEqual(rob_circular(nums), brute_rob(nums, True))

    def test_coin_change(self):
        rng = random.Random(2)
        for _ in range(300):
            coins = rng.sample(range(1, 8), rng.randrange(1, 4))
            amount = rng.randrange(13)
            found = multisets(coins, amount)
            fewest = min((len(chosen) for chosen in found), default=-1)
            self.assertEqual(coin_change(coins, amount), fewest)
            self.assertEqual(coin_change_ways(coins, amount), len(found))
            self.assertEqual(
                coin_change_ordered_ways(coins, amount), sequences(coins, amount)
            )

    def test_grids(self):
        rng = random.Random(3)
        for _ in range(300):
            rows, cols = rng.randrange(1, 5), rng.randrange(1, 5)
            values = [[rng.randrange(10) for _ in range(cols)] for _ in range(rows)]
            obstacles = [
                [int(rng.random() < 0.25) for _ in range(cols)] for _ in range(rows)
            ]
            self.assertEqual(min_path_sum(values), min(map(sum, all_paths(values))))
            free = sum(not any(path) for path in all_paths(obstacles))
            self.assertEqual(unique_paths_with_obstacles(obstacles), free)

    def test_word_break(self):
        rng = random.Random(4)
        for _ in range(300):
            words = [
                "".join(rng.choice("ab") for _ in range(rng.randrange(1, 4)))
                for _ in range(rng.randrange(4))
            ]
            text = "".join(rng.choice("ab") for _ in range(rng.randrange(9)))
            self.assertEqual(word_break(text, words), brute_word_break(text, words))

    def test_examples(self):
        self.assertEqual(rob([2, 7, 9, 3, 1]), 12)
        self.assertEqual(rob_circular([2, 3, 2]), 3)
        self.assertEqual(rob_circular([1, 2, 3, 1]), 4)
        self.assertEqual(coin_change([1, 2, 5], 11), 3)
        self.assertEqual(coin_change([2], 3), -1)
        self.assertEqual(coin_change_ways([1, 2, 5], 5), 4)
        self.assertEqual(coin_change_ordered_ways([1, 2, 3], 4), 7)
        self.assertEqual(
            unique_paths_with_obstacles([[0, 0, 0], [0, 1, 0], [0, 0, 0]]), 2
        )
        self.assertEqual(min_path_sum([[1, 3, 1], [1, 5, 1], [4, 2, 1]]), 7)
        self.assertTrue(word_break("leetcode", ["leet", "code"]))
        self.assertFalse(word_break("catsandog", ["cats", "dog", "sand", "and", "cat"]))


if __name__ == "__main__":
    unittest.main()
