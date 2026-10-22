import random
import unittest
from collections import deque

from TreeDP.TreeDP import (
    max_independent_set,
    max_path_sum,
    sum_of_distances,
    tree_diameter,
)


def random_tree(rng: random.Random, n: int) -> list[tuple[int, int]]:
    labels = list(range(n))
    rng.shuffle(labels)
    edges = []
    for i in range(1, n):
        a, b = labels[i], labels[rng.randrange(i)]
        edges.append((a, b) if rng.random() < 0.5 else (b, a))
    rng.shuffle(edges)
    return edges


def bfs_parents(n: int, edges: list[tuple[int, int]], source: int) -> list[int]:
    graph: list[list[int]] = [[] for _ in range(n)]
    for a, b in edges:
        graph[a].append(b)
        graph[b].append(a)
    parent = [-2] * n
    parent[source] = -1
    queue = deque([source])
    while queue:
        vertex = queue.popleft()
        for neighbor in graph[vertex]:
            if parent[neighbor] == -2:
                parent[neighbor] = vertex
                queue.append(neighbor)
    return parent


def path(parent: list[int], target: int) -> list[int]:
    vertices = []
    while target >= 0:
        vertices.append(target)
        target = parent[target]
    return vertices


class TestTreeDP(unittest.TestCase):
    def test_against_brute_force(self):
        rng = random.Random(9)
        for _ in range(200):
            n = rng.randrange(1, 10)
            edges = random_tree(rng, n)
            values = [rng.randrange(-10, 11) for _ in range(n)]
            paths = [
                path(bfs_parents(n, edges, source), target)
                for source in range(n)
                for target in range(n)
            ]
            self.assertEqual(tree_diameter(n, edges), max(len(p) - 1 for p in paths))
            self.assertEqual(
                max_path_sum(values, edges),
                max(sum(values[v] for v in p) for p in paths),
            )
            self.assertEqual(
                sum_of_distances(n, edges),
                [sum(len(paths[s * n + t]) - 1 for t in range(n)) for s in range(n)],
            )
            adjacent = {(a, b) for a, b in edges} | {(b, a) for a, b in edges}
            best = 0
            for mask in range(1 << n):
                chosen = [v for v in range(n) if mask >> v & 1]
                if any((a, b) in adjacent for a in chosen for b in chosen):
                    continue
                best = max(best, sum(values[v] for v in chosen))
            self.assertEqual(max_independent_set(values, edges), best)

    def test_examples(self):
        self.assertEqual(tree_diameter(3, [(0, 1), (0, 2)]), 2)
        edges = [(0, 1), (1, 2), (2, 3), (1, 4), (4, 5)]
        self.assertEqual(tree_diameter(6, edges), 4)
        self.assertEqual(
            max_path_sum([-10, 9, 20, 15, 7], [(0, 1), (0, 2), (2, 3), (2, 4)]), 42
        )
        self.assertEqual(max_path_sum([-3], []), -3)
        self.assertEqual(
            max_independent_set([3, 2, 3, 3, 1], [(0, 1), (0, 2), (1, 3), (2, 4)]), 7
        )
        self.assertEqual(
            sum_of_distances(6, [(0, 1), (0, 2), (2, 3), (2, 4), (2, 5)]),
            [8, 12, 6, 10, 10, 10],
        )
        self.assertEqual(sum_of_distances(1, []), [0])
        self.assertEqual(tree_diameter(1, []), 0)

    def test_deep_path(self):
        n = 100_000
        edges = [(i, i + 1) for i in range(n - 1)]
        self.assertEqual(tree_diameter(n, edges), n - 1)
        self.assertEqual(sum_of_distances(n, edges)[0], n * (n - 1) // 2)


if __name__ == "__main__":
    unittest.main()
