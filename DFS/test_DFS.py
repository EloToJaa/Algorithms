import unittest

from DFS.DFS import dfs


class TestDFS(unittest.TestCase):
    def test_recursive_order_and_deep_chain(self):
        self.assertEqual(dfs([[1, 2], [2, 3], [], []], 0), [0, 1, 2, 3])
        graph = [[i + 1] for i in range(2999)] + [[]]
        self.assertEqual(dfs(graph, 0), list(range(3000)))
        self.assertEqual(dfs([[1, 1], [0], []], 0), [0, 1])


if __name__ == "__main__":
    unittest.main()
