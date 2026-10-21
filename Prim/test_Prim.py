import random
import unittest

from Kruskal.Kruskal import kruskal
from Prim.Prim import prim


def adjacency(size, edges):
    graph = [[] for _ in range(size)]
    for a, b, weight in edges:
        graph[a].append((b, weight))
        graph[b].append((a, weight))
    return graph


class TestPrim(unittest.TestCase):
    def test_matches_kruskal(self):
        rng = random.Random(11)
        for _ in range(200):
            size = rng.randrange(0, 12)
            edges = [
                (rng.randrange(size), rng.randrange(size), rng.randrange(-5, 10))
                for _ in range(rng.randrange(0, 30) if size else 0)
            ]
            total, selected = prim(adjacency(size, edges))
            expected_total, expected_selected = kruskal(size, edges)
            self.assertEqual(total, expected_total)
            self.assertEqual(len(selected), len(expected_selected))
            self.assertEqual(sum(edge[2] for edge in selected), total)
            available = adjacency(size, edges)
            for parent, vertex, weight in selected:
                self.assertIn((vertex, weight), available[parent])

    def test_small_cases(self):
        graph = adjacency(4, [(0, 1, 2), (1, 2, -1), (0, 2, 8), (0, 0, -20)])
        self.assertEqual(prim(graph), (1, [(0, 1, 2), (1, 2, -1)]))
        self.assertEqual(prim([]), (0, []))


if __name__ == "__main__":
    unittest.main()
