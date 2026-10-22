"""Two pointers moving inward from opposite ends of an array."""

from collections.abc import Sequence


def pair_with_sum(values: Sequence[int], target: int) -> tuple[int, int] | None:
    """Indices i < j with values[i] + values[j] == target in a sorted array, or None."""
    left, right = 0, len(values) - 1
    while left < right:
        total = values[left] + values[right]
        if total == target:
            return left, right
        if total < target:
            left += 1
        else:
            right -= 1
    return None


def three_sum(values: Sequence[int], target: int = 0) -> list[tuple[int, int, int]]:
    """Unique value triplets a <= b <= c with a + b + c == target, sorted."""
    values = sorted(values)
    result: list[tuple[int, int, int]] = []
    for i in range(len(values) - 2):
        if i and values[i] == values[i - 1]:
            continue
        left, right = i + 1, len(values) - 1
        while left < right:
            total = values[i] + values[left] + values[right]
            if total < target:
                left += 1
            elif total > target:
                right -= 1
            else:
                result.append((values[i], values[left], values[right]))
                left += 1
                while left < right and values[left] == values[left - 1]:
                    left += 1
    return result


def max_area(heights: Sequence[int]) -> int:
    """Largest (j - i) * min(heights[i], heights[j]) over pairs i < j."""
    best, left, right = 0, 0, len(heights) - 1
    while left < right:
        best = max(best, (right - left) * min(heights[left], heights[right]))
        if heights[left] < heights[right]:
            left += 1
        else:
            right -= 1
    return best


def trap(heights: Sequence[int]) -> int:
    """Water trapped between non-negative bars of width one."""
    water, left, right = 0, 0, len(heights) - 1
    left_max = right_max = 0
    while left < right:
        if heights[left] < heights[right]:
            left_max = max(left_max, heights[left])
            water += left_max - heights[left]
            left += 1
        else:
            right_max = max(right_max, heights[right])
            water += right_max - heights[right]
            right -= 1
    return water
