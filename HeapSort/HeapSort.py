"""In-place heap sort with bottom-up heapify on a zero-based max heap."""

from collections.abc import Iterable
from typing import Any, Protocol, TypeVar


class Comparable(Protocol):
    def __lt__(self, other: Any, /) -> bool: ...


T = TypeVar("T", bound=Comparable)


def _sift_down(values: list[T], index: int, size: int) -> None:
    while 2 * index + 1 < size:
        child = 2 * index + 1
        if child + 1 < size and values[child] < values[child + 1]:
            child += 1
        if not values[index] < values[child]:
            return
        values[index], values[child] = values[child], values[index]
        index = child


def heap_sort(values: Iterable[T]) -> list[T]:
    """Return a sorted copy; leave the input unchanged."""
    result = list(values)
    for index in range(len(result) // 2 - 1, -1, -1):
        _sift_down(result, index, len(result))
    # Move the current maximum behind the shrinking heap.
    for end in range(len(result) - 1, 0, -1):
        result[0], result[end] = result[end], result[0]
        _sift_down(result, 0, end)
    return result
