"""Fenwick tree (binary indexed tree) for point updates and prefix sums."""

from bisect import bisect_left
from collections.abc import Sequence


class Fenwick:
    """Zero-based API over a one-based tree; tree[i] sums values (i - (i & -i), i]."""

    def __init__(self, values: Sequence[int]) -> None:
        """Build in O(n): push each node's partial sum into its parent once."""
        self.n = len(values)
        self.tree = [0, *values]
        for i in range(1, self.n + 1):
            parent = i + (i & -i)
            if parent <= self.n:
                self.tree[parent] += self.tree[i]

    def add(self, index: int, delta: int) -> None:
        """values[index] += delta."""
        i = index + 1
        while i <= self.n:
            self.tree[i] += delta
            i += i & -i

    def prefix_sum(self, count: int) -> int:
        """Sum of values[:count], the first count elements."""
        total = 0
        while count > 0:
            total += self.tree[count]
            count -= count & -count
        return total

    def range_sum(self, left: int, right: int) -> int:
        """Sum of values[left:right] (half-open)."""
        return self.prefix_sum(right) - self.prefix_sum(left)

    def lower_bound(self, target: int) -> int:
        """Smallest count with prefix_sum(count) >= target, or n + 1 if none.

        Requires nonnegative values. The zero-based index of the element
        holding the k-th unit (k >= 1) is lower_bound(k) - 1.
        """
        if target <= 0:
            return 0
        position = 0
        step = 1 << self.n.bit_length()
        while step:
            if position + step <= self.n and self.tree[position + step] < target:
                position += step
                target -= self.tree[position]
            step >>= 1
        return position + 1


def count_smaller_after_self(nums: Sequence[int]) -> list[int]:
    """result[i] is the number of j > i with nums[j] < nums[i]."""
    ranks = sorted(set(nums))
    counts = Fenwick([0] * len(ranks))
    result = [0] * len(nums)
    for i in range(len(nums) - 1, -1, -1):
        rank = bisect_left(ranks, nums[i])
        result[i] = counts.prefix_sum(rank)
        counts.add(rank, 1)
    return result
