"""Disjoint sets with path compression and union by size."""


class DisjointSet:
    def __init__(self, size):
        self.parent = list(range(size))
        self.size = [1] * size

    def find(self, vertex):
        while self.parent[vertex] != vertex:
            self.parent[vertex] = self.parent[self.parent[vertex]]
            vertex = self.parent[vertex]
        return vertex

    def union(self, first, second):
        """Return whether two previously distinct components were joined."""
        first, second = self.find(first), self.find(second)
        if first == second:
            return False
        if self.size[first] > self.size[second]:
            first, second = second, first
        self.parent[first] = second
        self.size[second] += self.size[first]
        return True
