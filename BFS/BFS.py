"""Breadth-first traversal using a FIFO queue."""

from collections import deque
from collections.abc import Sequence


def bfs(graph: Sequence[Sequence[int]], start: int) -> list[int]:
    """Return reachable vertices in BFS order; graph is an adjacency sequence."""
    seen = {start}
    queue = deque([start])
    order: list[int] = []
    while queue:
        vertex = queue.popleft()
        order.append(vertex)
        for neighbor in graph[vertex]:
            if neighbor in seen:
                continue
            seen.add(neighbor)
            queue.append(neighbor)
    return order
