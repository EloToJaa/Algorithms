import random
import unittest

from LCA.LCA import LCA


class TestLCA(unittest.TestCase):
    def test_against_parent_walk(self):
        rng = random.Random(1)
        parent = [0] + [rng.randrange(i) for i in range(1, 80)]
        graph = [[] for _ in parent]
        for vertex in range(1, len(parent)):
            graph[vertex].append(parent[vertex])
            graph[parent[vertex]].append(vertex)
        tree = LCA(graph)
        for first in range(len(parent)):
            ancestors = {first}
            vertex = first
            while vertex:
                vertex = parent[vertex]
                ancestors.add(vertex)
            for second in range(len(parent)):
                expected = second
                while expected not in ancestors:
                    expected = parent[expected]
                self.assertEqual(tree.query(first, second), expected)
        self.assertEqual(LCA([[1], [0, 2], [1]], root=2).query(0, 1), 1)


if __name__ == "__main__":
    unittest.main()
