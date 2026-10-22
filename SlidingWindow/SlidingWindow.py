"""Variable-size sliding windows: grow right, shrink left while invalid."""

from collections import Counter
from collections.abc import Hashable, Iterator, Sequence


def longest_unique_substring(values: Sequence[Hashable]) -> int:
    """Length of the longest window with no repeated value."""
    last: dict[Hashable, int] = {}
    best = left = 0
    for right, value in enumerate(values):
        if last.get(value, -1) >= left:
            left = last[value] + 1
        last[value] = right
        best = max(best, right - left + 1)
    return best


def min_window(text: str, pattern: str) -> str:
    """Shortest substring of text containing pattern with multiplicity, or ""."""
    if not pattern:
        return ""
    need = Counter(pattern)
    missing = len(pattern)
    start, end = 0, -1
    left = 0
    for right, char in enumerate(text):
        if need[char] > 0:
            missing -= 1
        need[char] -= 1
        if missing:
            continue
        while need[text[left]] < 0:
            need[text[left]] += 1
            left += 1
        if end < 0 or right - left < end - start:
            start, end = left, right
        need[text[left]] += 1
        missing += 1
        left += 1
    return text[start : end + 1]


def at_most_k_distinct_windows(
    values: Sequence[Hashable], k: int
) -> Iterator[tuple[int, int]]:
    """Yield (left, right): for each right, the smallest left with <= k distinct."""
    counts: Counter[Hashable] = Counter()
    left = 0
    for right, value in enumerate(values):
        counts[value] += 1
        while len(counts) > k:
            counts[values[left]] -= 1
            if not counts[values[left]]:
                del counts[values[left]]
            left += 1
        yield left, right


def longest_at_most_k_distinct(values: Sequence[Hashable], k: int) -> int:
    """Length of the longest window with at most k distinct values."""
    windows = at_most_k_distinct_windows(values, k)
    return max((right - left + 1 for left, right in windows), default=0)


def count_at_most_k_distinct(values: Sequence[Hashable], k: int) -> int:
    """Number of subarrays with at most k distinct values."""
    windows = at_most_k_distinct_windows(values, k)
    return sum(right - left + 1 for left, right in windows)


def count_exactly_k_distinct(values: Sequence[Hashable], k: int) -> int:
    """Number of subarrays with exactly k distinct values."""
    if k <= 0:
        return 0
    return count_at_most_k_distinct(values, k) - count_at_most_k_distinct(values, k - 1)
