"""Choose / recurse / un-choose templates: subsets, permutations, combinations, N-Queens."""

from collections.abc import Sequence


def subsets(nums: Sequence[int]) -> list[list[int]]:
    """All 2^n subsets in DFS (lexicographic by index) order."""
    result: list[list[int]] = []
    path: list[int] = []

    def go(start: int) -> None:
        result.append(path[:])
        for i in range(start, len(nums)):
            path.append(nums[i])
            go(i + 1)
            path.pop()

    go(0)
    return result


def subsets_with_dup(nums: Sequence[int]) -> list[list[int]]:
    """Distinct subsets of a multiset; each subset is sorted."""
    values = sorted(nums)
    result: list[list[int]] = []
    path: list[int] = []

    def go(start: int) -> None:
        result.append(path[:])
        for i in range(start, len(values)):
            # Equal values may start this level only once.
            if i > start and values[i] == values[i - 1]:
                continue
            path.append(values[i])
            go(i + 1)
            path.pop()

    go(0)
    return result


def permutations(nums: Sequence[int]) -> list[list[int]]:
    """All n! orderings of nums (positions treated as distinct)."""
    result: list[list[int]] = []
    path: list[int] = []
    used = [False] * len(nums)

    def go() -> None:
        if len(path) == len(nums):
            result.append(path[:])
            return
        for i, value in enumerate(nums):
            if used[i]:
                continue
            used[i] = True
            path.append(value)
            go()
            path.pop()
            used[i] = False

    go()
    return result


def combinations(n: int, k: int) -> list[list[int]]:
    """All k-element increasing lists drawn from 1..n (LeetCode 77 values)."""
    result: list[list[int]] = []
    path: list[int] = []

    def go(start: int) -> None:
        if len(path) == k:
            result.append(path[:])
            return
        # Stop early when too few values remain to fill the path.
        for value in range(start, n - (k - len(path)) + 2):
            path.append(value)
            go(value + 1)
            path.pop()

    go(1)
    return result


def combination_sum(candidates: Sequence[int], target: int) -> list[list[int]]:
    """Multisets of distinct positive candidates summing to target; each is sorted."""
    values = sorted(candidates)
    result: list[list[int]] = []
    path: list[int] = []

    def go(start: int, remaining: int) -> None:
        if remaining == 0:
            result.append(path[:])
            return
        for i in range(start, len(values)):
            if values[i] > remaining:
                break
            path.append(values[i])
            go(i, remaining - values[i])  # i, not i + 1: reuse allowed
            path.pop()

    go(0, target)
    return result


def n_queens(n: int) -> list[list[str]]:
    """All boards placing n non-attacking queens; rows are strings of '.' and 'Q'."""
    result: list[list[str]] = []
    queens: list[int] = []
    cols: set[int] = set()
    diagonals: set[int] = set()  # row - col
    anti_diagonals: set[int] = set()  # row + col

    def go(row: int) -> None:
        if row == n:
            result.append(["." * c + "Q" + "." * (n - c - 1) for c in queens])
            return
        for col in range(n):
            if col in cols or row - col in diagonals or row + col in anti_diagonals:
                continue
            cols.add(col)
            diagonals.add(row - col)
            anti_diagonals.add(row + col)
            queens.append(col)
            go(row + 1)
            queens.pop()
            cols.remove(col)
            diagonals.remove(row - col)
            anti_diagonals.remove(row + col)

    go(0)
    return result


def total_n_queens(n: int) -> int:
    """Number of N-Queens solutions using column/diagonal bitmasks."""
    full = (1 << n) - 1

    def go(cols: int, left: int, right: int) -> int:
        if cols == full:
            return 1
        count = 0
        free = full & ~(cols | left | right)
        while free:
            bit = free & -free
            free ^= bit
            # Diagonal attacks shift one column per row.
            count += go(cols | bit, (left | bit) << 1 & full, (right | bit) >> 1)
        return count

    return go(0, 0, 0)
