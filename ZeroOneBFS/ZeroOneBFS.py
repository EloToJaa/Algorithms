"""Shortest paths for graphs with edge weights zero or one."""

from collections import deque
from math import inf


def zero_one_bfs(graph, start):
    """Return (distances, predecessors); unreachable entries are inf/None."""
    if not 0 <= start < len(graph):
        raise ValueError("invalid source")
    if any(weight not in (0, 1) for edges in graph for _, weight in edges):
        raise ValueError("weights must be zero or one")
    distance, parent = [inf] * len(graph), [None] * len(graph)
    distance[start] = 0
    queue = deque([(0, start)])
    while queue:
        cost, vertex = queue.popleft()
        if cost != distance[vertex]:
            continue
        for neighbor, weight in graph[vertex]:
            candidate = cost + weight
            if candidate >= distance[neighbor]:
                continue
            distance[neighbor], parent[neighbor] = candidate, vertex
            if weight:
                queue.append((candidate, neighbor))
            else:
                queue.appendleft((candidate, neighbor))
    return distance, parent
