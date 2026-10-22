"""Monotonic stack: nearest greater/smaller neighbours and their applications."""

from collections.abc import Sequence

MOD = 10**9 + 7


def next_greater(values: Sequence[int]) -> list[int]:
    """Index of the nearest strictly greater value to the right, or -1."""
    result = [-1] * len(values)
    stack: list[int] = []  # indices with non-increasing values
    for i, value in enumerate(values):
        while stack and values[stack[-1]] < value:
            result[stack.pop()] = i
        stack.append(i)
    return result


def previous_smaller(values: Sequence[int]) -> list[int]:
    """Index of the nearest strictly smaller value to the left, or -1."""
    result = [-1] * len(values)
    stack: list[int] = []  # indices with strictly increasing values
    for i, value in enumerate(values):
        while stack and values[stack[-1]] >= value:
            stack.pop()
        if stack:
            result[i] = stack[-1]
        stack.append(i)
    return result


def largest_rectangle(heights: Sequence[int]) -> int:
    """Largest axis-aligned rectangle in a histogram of non-negative bars."""
    best = 0
    stack: list[int] = []
    for i in range(len(heights) + 1):
        height = heights[i] if i < len(heights) else -1
        while stack and heights[stack[-1]] >= height:
            top = heights[stack.pop()]
            left = stack[-1] if stack else -1
            best = max(best, top * (i - left - 1))
        stack.append(i)
    return best


def sum_subarray_mins(values: Sequence[int], mod: int = MOD) -> int:
    """Sum of min(values[l..r]) over all subarrays, modulo mod."""
    total = 0
    stack: list[int] = []
    for i in range(len(values) + 1):
        while stack and (i == len(values) or values[stack[-1]] >= values[i]):
            j = stack.pop()
            left = stack[-1] if stack else -1  # previous strictly smaller
            total += values[j] * (j - left) * (i - j)  # i: next smaller or equal
        stack.append(i)
    return total % mod
