import random
import unittest

from TopologicalSort.TopologicalSort import topological_sort


class TestTopologicalSort(unittest.TestCase):
    def test_random_dags(self):
        rng = random.Random(20)
        for size in range(40):
            permutation = list(range(size))
            rng.shuffle(permutation)
            graph = [[] for _ in range(size)]
            for i, vertex in enumerate(permutation):
                graph[vertex] = [u for u in permutation[i + 1 :] if rng.random() < 0.2]
            order = topological_sort(graph)
            self.assertEqual(sorted(order), list(range(size)))
            position = {v: i for i, v in enumerate(order)}
            self.assertTrue(
                all(position[v] < position[u] for v in range(size) for u in graph[v])
            )
        self.assertEqual(topological_sort([[1, 1], []]), [0, 1])

    def test_cycles_and_deep_chain(self):
        for graph in ([[0]], [[1], [0]], [[], [2], [1]]):
            with self.assertRaises(ValueError):
                topological_sort(graph)
        graph = [[v + 1] for v in range(4999)] + [[]]
        self.assertEqual(topological_sort(graph), list(range(5000)))


if __name__ == "__main__":
    unittest.main()
