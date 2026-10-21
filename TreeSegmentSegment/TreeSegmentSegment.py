"""Lazy segment tree for inclusive range addition and range sum."""

from collections.abc import Sequence


class RangeAddSum:
    def __init__(self, values: Sequence[int]) -> None:
        self.size = len(values)
        self.tree = [0] * (4 * max(1, self.size))
        self.lazy = [0] * len(self.tree)

        def build(node: int, left: int, right: int) -> None:
            if left == right:
                self.tree[node] = values[left]
                return
            middle = (left + right) // 2
            build(2 * node, left, middle)
            build(2 * node + 1, middle + 1, right)
            self.tree[node] = self.tree[2 * node] + self.tree[2 * node + 1]

        if self.size:
            build(1, 0, self.size - 1)

    def _apply(self, node: int, length: int, value: int) -> None:
        self.tree[node] += length * value
        self.lazy[node] += value

    def _push(self, node: int, left: int, right: int) -> None:
        if left == right or not self.lazy[node]:
            return
        middle = (left + right) // 2
        self._apply(2 * node, middle - left + 1, self.lazy[node])
        self._apply(2 * node + 1, right - middle, self.lazy[node])
        self.lazy[node] = 0

    def update(self, left: int, right: int, value: int) -> None:
        def visit(node: int, start: int, end: int) -> None:
            if end < left or right < start:
                return
            if left <= start and end <= right:
                self._apply(node, end - start + 1, value)
                return
            self._push(node, start, end)
            middle = (start + end) // 2
            visit(2 * node, start, middle)
            visit(2 * node + 1, middle + 1, end)
            self.tree[node] = self.tree[2 * node] + self.tree[2 * node + 1]

        if self.size:
            visit(1, 0, self.size - 1)

    def query(self, left: int, right: int) -> int:
        def visit(node: int, start: int, end: int) -> int:
            if end < left or right < start:
                return 0
            if left <= start and end <= right:
                return self.tree[node]
            self._push(node, start, end)
            middle = (start + end) // 2
            return visit(2 * node, start, middle) + visit(2 * node + 1, middle + 1, end)

        return visit(1, 0, self.size - 1) if self.size else 0
