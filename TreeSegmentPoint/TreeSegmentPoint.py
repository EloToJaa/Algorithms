"""Segment tree for inclusive range addition and point lookup."""


class RangeAddPoint:
    def __init__(self, values):
        self.size = len(values)
        self.base = 1 << max(0, (self.size - 1).bit_length())
        self.tree = [0] * (2 * self.base)
        self.tree[self.base : self.base + self.size] = values

    def update(self, left, right, value):
        left, right = left + self.base, right + self.base
        while left <= right:
            if left & 1:
                self.tree[left] += value
                left += 1
            if not right & 1:
                self.tree[right] += value
                right -= 1
            left //= 2
            right //= 2

    def query(self, index):
        node = self.base + index
        result = 0
        while node:
            result += self.tree[node]
            node //= 2
        return result
