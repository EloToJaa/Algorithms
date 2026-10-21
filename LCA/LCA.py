"""Lowest common ancestors using binary lifting on a connected tree."""

from collections.abc import Sequence


class LCA:
    def __init__(self, graph: Sequence[Sequence[int]], root: int = 0) -> None:
        size = len(graph)
        self.depth = [0] * size
        parent = [root] * size
        seen = {root}
        stack = [root]
        while stack:
            vertex = stack.pop()
            for neighbor in graph[vertex]:
                if neighbor in seen:
                    continue
                seen.add(neighbor)
                parent[neighbor] = vertex
                self.depth[neighbor] = self.depth[vertex] + 1
                stack.append(neighbor)
        self.up = [parent]
        for _ in range(1, max(1, size.bit_length())):
            previous = self.up[-1]
            self.up.append([previous[previous[v]] for v in range(size)])

    def query(self, first: int, second: int) -> int:
        if self.depth[first] < self.depth[second]:
            first, second = second, first
        difference = self.depth[first] - self.depth[second]
        for level in range(len(self.up)):
            if difference & (1 << level):
                first = self.up[level][first]
        if first == second:
            return first
        for ancestors in reversed(self.up):
            if ancestors[first] == ancestors[second]:
                continue
            first, second = ancestors[first], ancestors[second]
        return self.up[0][first]
