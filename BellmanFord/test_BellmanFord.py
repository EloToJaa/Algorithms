import random
import unittest
from math import inf

from BellmanFord.BellmanFord import bellman_ford


class TestBellmanFord(unittest.TestCase):
    def test_against_floyd_warshall(self):
        rng = random.Random(25)
        for size in range(1, 10):
            for _ in range(20):
                edges = [
                    (v, u, rng.randrange(-5, 8))
                    for v in range(size)
                    for u in range(size)
                    if rng.random() < 0.2
                ]
                matrix = [[inf] * size for _ in range(size)]
                for v in range(size):
                    matrix[v][v] = 0
                for v, u, weight in edges:
                    matrix[v][u] = min(matrix[v][u], weight)
                for k in range(size):
                    for v in range(size):
                        for u in range(size):
                            matrix[v][u] = min(
                                matrix[v][u], matrix[v][k] + matrix[k][u]
                            )
                for start in (0, size - 1):
                    expected = [
                        -inf
                        if any(
                            matrix[start][k] != inf
                            and matrix[k][k] < 0
                            and matrix[k][v] != inf
                            for k in range(size)
                        )
                        else matrix[start][v]
                        for v in range(size)
                    ]
                    distance, parent = bellman_ford(size, edges, start)
                    self.assertEqual(distance, expected)
                    for v in range(size):
                        if expected[v] in (inf, -inf):
                            self.assertIsNone(parent[v])
                            continue
                        if v == start:
                            continue
                        self.assertTrue(
                            any(
                                u == v
                                and a == parent[v]
                                and distance[a] + w == distance[v]
                                for a, u, w in edges
                            )
                        )
                        seen, current = set(), v
                        while current != start:
                            self.assertNotIn(current, seen)
                            seen.add(current)
                            current = parent[current]

    def test_cycle_propagation_and_boundaries(self):
        edges = [(0, 1, 2), (1, 2, -2), (2, 1, 1), (2, 3, 5), (4, 4, -1)]
        self.assertEqual(bellman_ford(5, edges, 0)[0], [0, -inf, -inf, -inf, inf])
        self.assertEqual(bellman_ford(1, [(0, 0, -1)], 0), ([-inf], [None]))
        self.assertEqual(bellman_ford(1, [], 0), ([0], [None]))
        self.assertEqual(
            bellman_ford(2, iter([(0, 1, -(10**100))]), 0)[0], [0, -(10**100)]
        )
        for size, start in ((0, 0), (1, -1), (1, 1)):
            with self.assertRaises(ValueError):
                bellman_ford(size, [], start)


if __name__ == "__main__":
    unittest.main()
