"""One-based binary min and max heaps with sift-up and sift-down."""

from collections.abc import Iterable
from typing import Any, Generic, Protocol, TypeVar, cast


class Comparable(Protocol):
    def __lt__(self, other: Any, /) -> bool: ...
    def __gt__(self, other: Any, /) -> bool: ...


T = TypeVar("T", bound=Comparable)


class MinHeap(Generic[T]):
    def __init__(self, values: Iterable[T] = ()) -> None:
        self.heap: list[T] = [cast(T, None)]  # index 0 is unused
        for value in values:
            self.insert(value)

    def _before(self, first: T, second: T) -> bool:
        return first < second

    def insert(self, value: T) -> None:
        self.heap.append(value)
        index = len(self.heap) - 1
        while index > 1 and self._before(self.heap[index], self.heap[index // 2]):
            self.heap[index], self.heap[index // 2] = (
                self.heap[index // 2],
                self.heap[index],
            )
            index //= 2

    def _sift_down(self) -> None:
        index = 1
        while 2 * index < len(self.heap):
            child = 2 * index
            if child + 1 < len(self.heap) and self._before(
                self.heap[child + 1], self.heap[child]
            ):
                child += 1
            if not self._before(self.heap[child], self.heap[index]):
                return
            self.heap[index], self.heap[child] = self.heap[child], self.heap[index]
            index = child

    def top(self) -> T:
        return self.heap[1]

    def remove(self) -> T:
        """Remove and return the root; requires a nonempty heap."""
        value = self.top()
        last = self.heap.pop()
        if not self.empty():
            self.heap[1] = last
            self._sift_down()
        return value

    def replace(self, value: T) -> T:
        """Replace the root; requires a nonempty heap."""
        previous = self.top()
        self.heap[1] = value
        self._sift_down()
        return previous

    def size(self) -> int:
        return len(self.heap) - 1

    def empty(self) -> bool:
        return self.size() == 0


class MaxHeap(MinHeap[T]):
    def _before(self, first: T, second: T) -> bool:
        return first > second
