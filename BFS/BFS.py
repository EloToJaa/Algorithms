"""Breadth-first traversal using a FIFO queue."""

from collections import deque


def bfs(graph, start):
    """Return reachable vertices in BFS order; graph is an adjacency sequence."""
    seen = {start}
    queue = deque([start])
    order = []
    while queue:
        vertex = queue.popleft()
        order.append(vertex)
        for neighbor in graph[vertex]:
            if neighbor in seen:
                continue
            seen.add(neighbor)
            queue.append(neighbor)
    return order
