import random
import unittest

from SCC.SCC import strongly_connected_components


class TestSCC(unittest.TestCase):
    def test_against_reachability(self):
        rng = random.Random(22)
        for size in range(15):
            for _ in range(12):
                graph = [
                    [u for u in range(size) if rng.random() < 0.2] for _ in range(size)
                ]
                reachable = []
                for start in range(size):
                    seen, stack = {start}, [start]
                    while stack:
                        for u in graph[stack.pop()]:
                            if u not in seen:
                                seen.add(u)
                                stack.append(u)
                    reachable.append(seen)
                ids, groups = strongly_connected_components(graph)
                self.assertEqual(
                    sorted(v for group in groups for v in group), list(range(size))
                )
                for identifier, group in enumerate(groups):
                    self.assertTrue(all(ids[v] == identifier for v in group))
                for v in range(size):
                    for u in range(size):
                        self.assertEqual(
                            ids[v] == ids[u], u in reachable[v] and v in reachable[u]
                        )
                    self.assertTrue(all(ids[v] <= ids[u] for u in graph[v]))

    def test_deep_graph(self):
        graph = [[v + 1] for v in range(4999)] + [[]]
        ids, groups = strongly_connected_components(graph)
        self.assertEqual(ids, list(range(5000)))
        graph[-1] = [0]
        self.assertEqual(len(strongly_connected_components(graph)[1]), 1)


if __name__ == "__main__":
    unittest.main()
