"""DP over subsets: Held-Karp TSP, k equal-sum partition, BFS over (node, mask)."""

from collections import deque
from collections.abc import Sequence
from math import inf


def held_karp(cost: Sequence[Sequence[float]]) -> float:
    """Minimum Hamiltonian cycle through 0 in a dense matrix (inf = no edge).

    Returns inf if no cycle exists and 0 for n <= 1.
    """
    n = len(cost)
    if n <= 1:
        return 0
    full = (1 << n) - 1
    # best[mask][last]: cheapest path 0 -> ... -> last visiting exactly mask.
    best = [[inf] * n for _ in range(1 << n)]
    best[1][0] = 0
    for mask in range(1, 1 << n, 2):
        for last in range(n):
            here = best[mask][last]
            if here == inf:
                continue
            for nxt in range(n):
                if mask >> nxt & 1:
                    continue
                candidate = here + cost[last][nxt]
                if candidate < best[mask | 1 << nxt][nxt]:
                    best[mask | 1 << nxt][nxt] = candidate
    return min(best[full][last] + cost[last][0] for last in range(1, n))


def can_partition_k_subsets(nums: Sequence[int], k: int) -> bool:
    """Split positive nums into k groups of equal sum (1 <= k)."""
    total = sum(nums)
    if total % k:
        return False
    target = total // k
    if max(nums, default=0) > target:
        return False
    n = len(nums)
    # filled[mask]: sum of the open bucket after placing mask, -1 if unreachable.
    filled = [-1] * (1 << n)
    filled[0] = 0
    for mask in range(1 << n):
        if filled[mask] < 0:
            continue
        for i in range(n):
            nxt = mask | 1 << i
            if nxt == mask or filled[nxt] >= 0:
                continue
            if filled[mask] + nums[i] <= target:
                filled[nxt] = (filled[mask] + nums[i]) % target
    return filled[(1 << n) - 1] == 0


def shortest_path_visiting_all_nodes(graph: Sequence[Sequence[int]]) -> int:
    """Fewest edges of a walk visiting every vertex; -1 if impossible, 0 if n <= 1."""
    n = len(graph)
    if n <= 1:
        return 0
    full = (1 << n) - 1
    seen = [[False] * (1 << n) for _ in range(n)]
    queue: deque[tuple[int, int, int]] = deque()
    for start in range(n):
        seen[start][1 << start] = True
        queue.append((start, 1 << start, 0))
    while queue:
        vertex, mask, steps = queue.popleft()
        for neighbor in graph[vertex]:
            nxt = mask | 1 << neighbor
            if nxt == full:
                return steps + 1
            if seen[neighbor][nxt]:
                continue
            seen[neighbor][nxt] = True
            queue.append((neighbor, nxt, steps + 1))
    return -1
