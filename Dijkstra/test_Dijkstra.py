import random
import unittest

from Dijkstra.Dijkstra import dijkstra


class TestDijkstra(unittest.TestCase):
    def test_against_bellman_ford(self):
        rng = random.Random(5)
        for size in range(1, 12):
            graph = [
                [(j, rng.randrange(10)) for j in range(size) if rng.random() < 0.2]
                for _ in range(size)
            ]
            expected = [float("inf")] * size
            expected[0] = 0
            for _ in range(size - 1):
                for vertex, edges in enumerate(graph):
                    for neighbor, weight in edges:
                        expected[neighbor] = min(
                            expected[neighbor], expected[vertex] + weight
                        )
            actual, parent = dijkstra(graph, 0)
            self.assertEqual(actual, expected)
            for vertex in range(1, size):
                if parent[vertex] is None:
                    self.assertEqual(actual[vertex], float("inf"))
                    continue
                self.assertTrue(
                    any(
                        neighbor == vertex
                        and actual[parent[vertex]] + weight == actual[vertex]
                        for neighbor, weight in graph[parent[vertex]]
                    )
                )


if __name__ == "__main__":
    unittest.main()
