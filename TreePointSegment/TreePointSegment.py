"""Iterative segment tree for point assignment and inclusive range maximum."""

from math import inf


class PointRangeMax:
    def __init__(self, values):
        self.size = len(values)
        self.base = 1 << max(0, (self.size - 1).bit_length())
        self.tree = [-inf] * (2 * self.base)
        self.tree[self.base : self.base + self.size] = values
        for node in range(self.base - 1, 0, -1):
            self.tree[node] = max(self.tree[2 * node], self.tree[2 * node + 1])

    def update(self, index, value):
        node = self.base + index
        self.tree[node] = value
        node //= 2
        while node:
            self.tree[node] = max(self.tree[2 * node], self.tree[2 * node + 1])
            node //= 2

    def query(self, left, right):
        left, right = left + self.base, right + self.base
        result = -inf
        while left <= right:
            if left & 1:
                result = max(result, self.tree[left])
                left += 1
            if not right & 1:
                result = max(result, self.tree[right])
                right -= 1
            left //= 2
            right //= 2
        return result
