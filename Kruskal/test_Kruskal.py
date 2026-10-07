import random
import unittest

from Kruskal.Kruskal import kruskal


class TestKruskal(unittest.TestCase):
    def test_against_exhaustive_spanning_trees(self):
        import itertools

        rng = random.Random(7)
        for _ in range(20):
            edges = [
                (a, b, rng.randrange(-5, 10)) for a in range(4) for b in range(a + 1, 4)
            ]
            candidates = []
            for subset in itertools.combinations(edges, 3):
                reached = {0}
                for _ in range(4):
                    for a, b, _ in subset:
                        if a in reached or b in reached:
                            reached.update((a, b))
                if len(reached) == 4:
                    candidates.append(sum(edge[2] for edge in subset))
            total, selected = kruskal(4, edges)
            self.assertEqual(total, min(candidates))
            self.assertEqual(len(selected), 3)
        self.assertEqual(kruskal(4, [(0, 1, 2), (2, 3, -1), (0, 0, -10)])[0], 1)
        self.assertEqual(kruskal(0, []), (0, []))


if __name__ == "__main__":
    unittest.main()
