import random
import unittest
from collections import deque
from itertools import permutations, product
from math import inf

from BitmaskDP.BitmaskDP import (
    can_partition_k_subsets,
    held_karp,
    shortest_path_visiting_all_nodes,
)


def brute_cycle(cost: list[list[float]]) -> float:
    n = len(cost)
    if n <= 1:
        return 0
    return min(
        sum(cost[a][b] for a, b in zip((0, *order), (*order, 0), strict=True))
        for order in permutations(range(1, n))
    )


def brute_partition(nums: list[int], k: int) -> bool:
    for labels in product(range(k), repeat=len(nums)):
        sums = [0] * k
        for value, label in zip(nums, labels, strict=True):
            sums[label] += value
        if len(set(sums)) == 1:
            return True
    return False


def brute_walk(graph: list[list[int]]) -> int:
    n = len(graph)
    distance = []
    for source in range(n):
        row = [inf] * n
        row[source] = 0
        queue = deque([source])
        while queue:
            vertex = queue.popleft()
            for neighbor in graph[vertex]:
                if row[neighbor] == inf:
                    row[neighbor] = row[vertex] + 1
                    queue.append(neighbor)
        distance.append(row)
    best = min(
        sum(distance[a][b] for a, b in zip(order, order[1:], strict=False))
        for order in permutations(range(n))
    )
    return -1 if best == inf else best


class TestBitmaskDP(unittest.TestCase):
    def test_against_brute_force(self):
        rng = random.Random(8)
        for _ in range(150):
            n = rng.randrange(1, 7)
            cost = [
                [inf if rng.random() < 0.3 else rng.randrange(1, 20) for _ in range(n)]
                for _ in range(n)
            ]
            self.assertEqual(held_karp(cost), brute_cycle(cost))

            nums = [rng.randrange(1, 6) for _ in range(rng.randrange(1, 8))]
            k = rng.randrange(1, min(len(nums), 4) + 1)
            self.assertEqual(can_partition_k_subsets(nums, k), brute_partition(nums, k))

            graph: list[list[int]] = [[] for _ in range(n)]
            for a in range(n):
                for b in range(a + 1, n):
                    if rng.random() < 0.4:
                        graph[a].append(b)
                        graph[b].append(a)
            self.assertEqual(shortest_path_visiting_all_nodes(graph), brute_walk(graph))

    def test_examples(self):
        square = [[0, 10, 15, 20], [10, 0, 35, 25], [15, 35, 0, 30], [20, 25, 30, 0]]
        self.assertEqual(held_karp(square), 80)
        self.assertEqual(held_karp([[0, inf], [1, 0]]), inf)
        self.assertTrue(can_partition_k_subsets([4, 3, 2, 3, 5, 2, 1], 4))
        self.assertFalse(can_partition_k_subsets([1, 2, 3, 4], 3))
        self.assertEqual(
            shortest_path_visiting_all_nodes([[1, 2, 3], [0], [0], [0]]), 4
        )
        graph = [[1], [0, 2, 4], [1, 3, 4], [2], [1, 2]]
        self.assertEqual(shortest_path_visiting_all_nodes(graph), 4)
        self.assertEqual(shortest_path_visiting_all_nodes([[]]), 0)


if __name__ == "__main__":
    unittest.main()
