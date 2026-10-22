"""Randomized quickselect with three-way partitioning, plus top-k helpers."""

import random
from collections import Counter
from collections.abc import Hashable, Sequence
from typing import Any, Protocol, TypeVar


class Comparable(Protocol):
    def __lt__(self, other: Any, /) -> bool: ...


T = TypeVar("T", bound=Comparable)
H = TypeVar("H", bound=Hashable)


def _select(values: list[T], k: int) -> T:
    """Rearrange values in place so values[k] is the k-th smallest and
    values[:k] holds no larger elements; requires 0 <= k < len(values)."""
    low, high = 0, len(values)
    while True:
        pivot = values[random.randrange(low, high)]
        # Dutch flag: [low, lt) < pivot, [lt, i) == pivot, (gt, high) > pivot.
        lt, i, gt = low, low, high - 1
        while i <= gt:
            if values[i] < pivot:
                values[lt], values[i] = values[i], values[lt]
                lt += 1
                i += 1
            elif pivot < values[i]:
                values[gt], values[i] = values[i], values[gt]
                gt -= 1
            else:
                i += 1
        if k < lt:
            high = lt
        elif k > gt:
            low = gt + 1
        else:
            return pivot


def quick_select(nums: Sequence[T], k: int) -> T:
    """Return the k-th smallest (zero-based) element without mutating nums."""
    if not 0 <= k < len(nums):
        raise IndexError("k out of range")
    return _select(list(nums), k)


def k_smallest(nums: Sequence[T], k: int) -> list[T]:
    """Return the k smallest elements in no particular order."""
    if k <= 0:
        return []
    if k >= len(nums):
        return list(nums)
    values = list(nums)
    _select(values, k - 1)
    return values[:k]


def top_k_frequent(nums: Sequence[H], k: int) -> list[H]:
    """Return k most frequent distinct values; ties are broken arbitrarily."""
    buckets: list[list[H]] = [[] for _ in range(len(nums) + 1)]
    for value, count in Counter(nums).items():
        buckets[count].append(value)
    result: list[H] = []
    for bucket in reversed(buckets):
        for value in bucket:
            if len(result) == k:
                return result
            result.append(value)
    return result
