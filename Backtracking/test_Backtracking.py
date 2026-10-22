import itertools
import random
import unittest

from Backtracking.Backtracking import (
    combination_sum,
    combinations,
    n_queens,
    permutations,
    subsets,
    subsets_with_dup,
    total_n_queens,
)


def brute_subsets(nums: list[int]) -> list[tuple[int, ...]]:
    return [
        chosen
        for size in range(len(nums) + 1)
        for chosen in itertools.combinations(nums, size)
    ]


def is_valid_board(board: list[str]) -> bool:
    n = len(board)
    queens = [row.index("Q") for row in board]
    if any(len(row) != n or row.count("Q") != 1 for row in board):
        return False
    return all(
        queens[a] != queens[b] and abs(queens[a] - queens[b]) != b - a
        for a in range(n)
        for b in range(a + 1, n)
    )


class TestBacktracking(unittest.TestCase):
    def test_against_itertools(self):
        rng = random.Random(7)
        for _ in range(200):
            nums = [rng.randrange(-3, 4) for _ in range(rng.randrange(7))]
            expected = sorted(list(chosen) for chosen in brute_subsets(nums))
            self.assertEqual(sorted(subsets(nums)), expected)

            distinct = sorted({tuple(sorted(c)) for c in brute_subsets(nums)})
            got = subsets_with_dup(nums)
            self.assertEqual(len(got), len(distinct))
            self.assertEqual(sorted(map(tuple, got)), distinct)

            expected = sorted(map(list, itertools.permutations(nums)))
            self.assertEqual(sorted(permutations(nums)), expected)

    def test_combinations(self):
        for n in range(8):
            for k in range(n + 2):
                expected = [list(c) for c in itertools.combinations(range(1, n + 1), k)]
                self.assertEqual(combinations(n, k), expected)

    def test_combination_sum(self):
        rng = random.Random(8)
        for _ in range(200):
            candidates = rng.sample(range(1, 9), rng.randrange(1, 5))
            target = rng.randrange(1, 13)
            expected = sorted(
                list(chosen)
                for size in range(target + 1)
                for chosen in itertools.combinations_with_replacement(
                    sorted(candidates), size
                )
                if sum(chosen) == target
            )
            self.assertEqual(sorted(combination_sum(candidates, target)), expected)

    def test_n_queens(self):
        for n in range(1, 8):
            expected = sum(
                is_valid_board(["." * c + "Q" + "." * (n - c - 1) for c in perm])
                for perm in itertools.permutations(range(n))
            )
            boards = n_queens(n)
            self.assertTrue(all(is_valid_board(board) for board in boards))
            self.assertEqual(len({tuple(board) for board in boards}), expected)
            self.assertEqual(len(boards), expected)
            self.assertEqual(total_n_queens(n), expected)

    def test_examples(self):
        self.assertEqual(
            subsets([1, 2, 3]),
            [[], [1], [1, 2], [1, 2, 3], [1, 3], [2], [2, 3], [3]],
        )
        self.assertEqual(
            subsets_with_dup([1, 2, 2]), [[], [1], [1, 2], [1, 2, 2], [2], [2, 2]]
        )
        self.assertEqual(len(permutations([1, 2, 3])), 6)
        self.assertEqual(combinations(4, 2)[0], [1, 2])
        self.assertEqual(combination_sum([2, 3, 6, 7], 7), [[2, 2, 3], [7]])
        self.assertEqual(
            n_queens(4),
            [[".Q..", "...Q", "Q...", "..Q."], ["..Q.", "Q...", "...Q", ".Q.."]],
        )
        self.assertEqual(total_n_queens(8), 92)


if __name__ == "__main__":
    unittest.main()
