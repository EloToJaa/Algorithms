import random
import unittest

from Dijkstra.Dijkstra import dijkstra
from ZeroOneBFS.ZeroOneBFS import zero_one_bfs


class TestZeroOneBFS(unittest.TestCase):
    def test_against_dijkstra(self):
        rng = random.Random(24)
        for size in range(1, 30):
            graph = [
                [(u, rng.randrange(2)) for u in range(size) if rng.random() < 0.15]
                for _ in range(size)
            ]
            graph[0].extend([(0, 0), (0, 1)])
            for start in (0, size - 1):
                distances, parent = zero_one_bfs(graph, start)
                self.assertEqual(distances, dijkstra(graph, start)[0])
                for vertex, predecessor in enumerate(parent):
                    if predecessor is None:
                        continue
                    self.assertTrue(
                        any(
                            u == vertex
                            and distances[predecessor] + w == distances[vertex]
                            for u, w in graph[predecessor]
                        )
                    )
                    seen = set()
                    current = vertex
                    while current != start:
                        self.assertNotIn(current, seen)
                        seen.add(current)
                        current = parent[current]
                    self.assertEqual(current, start)
        self.assertEqual(zero_one_bfs([[], []], 0), ([0, float("inf")], [None, None]))

    def test_invalid_inputs(self):
        for graph, start in (
            ([], 0),
            ([[]], -1),
            ([[]], 1),
            ([[], [(0, 2)]], 0),
            ([[(0, -1)]], 0),
        ):
            with self.assertRaises(ValueError):
                zero_one_bfs(graph, start)


if __name__ == "__main__":
    unittest.main()
