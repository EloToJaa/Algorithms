"""Prefix sums, 2D rectangle sums, subarray-sum counting, and difference arrays."""

from collections import Counter
from collections.abc import Iterable, Sequence
from itertools import accumulate


def prefix_sums(values: Sequence[int]) -> list[int]:
    """prefix[i] is the sum of values[:i]; length is len(values) + 1."""
    return list(accumulate(values, initial=0))


def range_sum(prefix: Sequence[int], left: int, right: int) -> int:
    """Sum of the half-open range values[left:right]."""
    return prefix[right] - prefix[left]


class PrefixSum2D:
    def __init__(self, matrix: Sequence[Sequence[int]]) -> None:
        """table[i][j] is the sum of matrix[:i][:j] (top-left i x j block)."""
        columns = len(matrix[0]) if matrix else 0
        self.table = [[0] * (columns + 1) for _ in range(len(matrix) + 1)]
        for i, row in enumerate(matrix):
            for j, value in enumerate(row):
                self.table[i + 1][j + 1] = (
                    value
                    + self.table[i][j + 1]
                    + self.table[i + 1][j]
                    - self.table[i][j]
                )

    def sum_region(self, row1: int, col1: int, row2: int, col2: int) -> int:
        """Sum of the inclusive rectangle rows row1..row2, columns col1..col2."""
        t = self.table
        return (
            t[row2 + 1][col2 + 1]
            - t[row1][col2 + 1]
            - t[row2 + 1][col1]
            + t[row1][col1]
        )


def count_subarrays_with_sum(values: Iterable[int], k: int) -> int:
    """Number of nonempty contiguous subarrays summing to k."""
    seen = Counter({0: 1})
    total = count = 0
    for value in values:
        total += value
        count += seen[total - k]
        seen[total] += 1
    return count


def apply_range_additions(
    size: int, updates: Iterable[tuple[int, int, int]]
) -> list[int]:
    """Start from zeros and add delta to every index in each inclusive [left, right]."""
    diff = [0] * (size + 1)
    for left, right, delta in updates:
        diff[left] += delta
        diff[right + 1] -= delta
    return list(accumulate(diff[:size]))
