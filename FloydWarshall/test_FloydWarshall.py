import random
import unittest
from math import inf

from FloydWarshall.FloydWarshall import (
    floyd_warshall,
    negative_cycle_vertices,
    reconstruct_path,
)


def bellman_ford_row(
    n: int, edges: list[tuple[int, int, int]], source: int
) -> list[float]:
    """Distances from source; extra rounds spread -inf from negative cycles."""
    dist: list[float] = [inf] * n
    dist[source] = 0
    for _ in range(n - 1):
        for u, v, w in edges:
            if dist[u] < inf and dist[u] + w < dist[v]:
                dist[v] = dist[u] + w
    for _ in range(n):
        for u, v, w in edges:
            if dist[u] < inf and dist[u] + w < dist[v]:
                dist[v] = -inf
    return dist


class TestFloydWarshall(unittest.TestCase):
    def test_against_bellman_ford(self):
        rng = random.Random(12)
        for _ in range(300):
            n = rng.randrange(1, 7)
            edges = [
                (rng.randrange(n), rng.randrange(n), rng.randrange(-3, 10))
                for _ in range(rng.randrange(12))
            ]
            dist, nxt = floyd_warshall(n, edges)
            expected = [bellman_ford_row(n, edges, s) for s in range(n)]
            self.assertEqual(dist, expected)
            self.assertEqual(
                negative_cycle_vertices(dist),
                [v for v in range(n) if expected[v][v] == -inf],
            )
            weight = {}
            for u, v, w in edges:
                weight[u, v] = min(w, weight.get((u, v), inf))
            for s in range(n):
                for t in range(n):
                    path = reconstruct_path(dist, nxt, s, t)
                    if dist[s][t] in (inf, -inf):
                        self.assertIsNone(path)
                        continue
                    assert path is not None
                    self.assertEqual((path[0], path[-1]), (s, t))
                    total = sum(
                        weight[a, b] for a, b in zip(path, path[1:], strict=False)
                    )
                    self.assertEqual(total, dist[s][t])

    def test_examples(self):
        edges = [(0, 1, 3), (1, 2, 1), (0, 2, 5), (2, 3, 2), (3, 0, 2)]
        dist, nxt = floyd_warshall(4, edges)
        self.assertEqual(dist[0], [0, 3, 4, 6])
        self.assertEqual(reconstruct_path(dist, nxt, 0, 3), [0, 1, 2, 3])
        dist, nxt = floyd_warshall(3, [(0, 1, 1), (1, 1, -1), (2, 0, 1)])
        self.assertEqual(dist[0], [0, -inf, inf])
        self.assertEqual(dist[2], [1, -inf, 0])
        self.assertEqual(negative_cycle_vertices(dist), [1])
        self.assertIsNone(reconstruct_path(dist, nxt, 0, 1))
        self.assertIsNone(reconstruct_path(dist, nxt, 0, 2))
        self.assertEqual(floyd_warshall(0, []), ([], []))


if __name__ == "__main__":
    unittest.main()
