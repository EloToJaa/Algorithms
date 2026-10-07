import random
import unittest

from Bridges.Bridges import bridges_and_articulation_points


def component_count(size, edges, removed_edge=None, removed_vertex=None):
    graph = [[] for _ in range(size)]
    for identifier, (a, b) in enumerate(edges):
        if identifier == removed_edge or removed_vertex in (a, b):
            continue
        graph[a].append(b)
        graph[b].append(a)
    seen, count = {removed_vertex}, 0
    for start in range(size):
        if start in seen:
            continue
        count += 1
        stack = [start]
        seen.add(start)
        while stack:
            for u in graph[stack.pop()]:
                if u not in seen:
                    seen.add(u)
                    stack.append(u)
    return count


class TestBridges(unittest.TestCase):
    def test_against_removal(self):
        rng = random.Random(26)
        for size in range(10):
            for _ in range(30):
                edges = (
                    [
                        (rng.randrange(size), rng.randrange(size))
                        for _ in range(rng.randrange(20))
                    ]
                    if size
                    else []
                )
                baseline = component_count(size, edges)
                bridges = [
                    i
                    for i in range(len(edges))
                    if component_count(size, edges, removed_edge=i) > baseline
                ]
                points = [
                    v
                    for v in range(size)
                    if component_count(size, edges, removed_vertex=v) > baseline
                ]
                self.assertEqual(
                    bridges_and_articulation_points(size, edges), (bridges, points)
                )

    def test_parallel_edges_roots_and_deep_chain(self):
        self.assertEqual(
            bridges_and_articulation_points(3, [(0, 1), (0, 1), (1, 2), (1, 1)]),
            ([2], [1]),
        )
        self.assertEqual(
            bridges_and_articulation_points(3, [(0, 1), (0, 2)]), ([0, 1], [0])
        )
        size = 5000
        self.assertEqual(
            bridges_and_articulation_points(
                size, [(v, v + 1) for v in range(size - 1)]
            ),
            (list(range(size - 1)), list(range(1, size - 1))),
        )


if __name__ == "__main__":
    unittest.main()
