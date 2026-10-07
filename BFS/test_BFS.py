import unittest

from BFS.BFS import bfs


class TestBFS(unittest.TestCase):
    def test_cycles_and_duplicate_edges(self):
        graph = [[1, 1, 2], [0, 3], [3], [1], []]
        self.assertEqual(bfs(graph, 0), [0, 1, 2, 3])
        self.assertEqual(bfs(graph, 4), [4])


if __name__ == "__main__":
    unittest.main()
