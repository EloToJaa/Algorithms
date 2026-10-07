"""Lazy segment tree for inclusive range addition and range sum."""


class RangeAddSum:
    def __init__(self, values):
        self.size = len(values)
        self.tree = [0] * (4 * max(1, self.size))
        self.lazy = [0] * len(self.tree)

        def build(node, left, right):
            if left == right:
                self.tree[node] = values[left]
                return
            middle = (left + right) // 2
            build(2 * node, left, middle)
            build(2 * node + 1, middle + 1, right)
            self.tree[node] = self.tree[2 * node] + self.tree[2 * node + 1]

        if self.size:
            build(1, 0, self.size - 1)

    def _apply(self, node, length, value):
        self.tree[node] += length * value
        self.lazy[node] += value

    def _push(self, node, left, right):
        if left == right or not self.lazy[node]:
            return
        middle = (left + right) // 2
        self._apply(2 * node, middle - left + 1, self.lazy[node])
        self._apply(2 * node + 1, right - middle, self.lazy[node])
        self.lazy[node] = 0

    def update(self, left, right, value):
        def visit(node, start, end):
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

    def query(self, left, right):
        def visit(node, start, end):
            if end < left or right < start:
                return 0
            if left <= start and end <= right:
                return self.tree[node]
            self._push(node, start, end)
            middle = (start + end) // 2
            return visit(2 * node, start, middle) + visit(2 * node + 1, middle + 1, end)

        return visit(1, 0, self.size - 1) if self.size else 0
