"""Stable merge sort using one auxiliary buffer."""

from collections.abc import Iterable
from typing import Any, Protocol, TypeVar


class Comparable(Protocol):
    def __le__(self, other: Any, /) -> bool: ...


T = TypeVar("T", bound=Comparable)


def merge_sort(values: Iterable[T]) -> list[T]:
    """Return a sorted copy; leave the input unchanged."""
    result = list(values)
    auxiliary = result.copy()

    def sort(left: int, right: int) -> None:
        if right - left <= 1:
            return
        middle = (left + right) // 2
        sort(left, middle)
        sort(middle, right)
        auxiliary[left:right] = result[left:right]
        first, second = left, middle
        for position in range(left, right):
            if second == right or (
                first < middle and auxiliary[first] <= auxiliary[second]
            ):
                result[position] = auxiliary[first]
                first += 1
            else:
                result[position] = auxiliary[second]
                second += 1

    sort(0, len(result))
    return result
