"""Shortest paths in graphs with nonnegative edge weights."""

from collections.abc import Sequence
from heapq import heappop, heappush
from math import inf


def dijkstra(
    graph: Sequence[Sequence[tuple[int, float]]], start: int
) -> tuple[list[float], list[int | None]]:
    """Return (distances, predecessors); adjacency entries are (vertex, weight)."""
    distance: list[float] = [inf] * len(graph)
    parent: list[int | None] = [None] * len(graph)
    distance[start] = 0
    queue: list[tuple[float, int]] = [(0, start)]
    while queue:
        cost, vertex = heappop(queue)
        if cost != distance[vertex]:
            continue
        for neighbor, weight in graph[vertex]:
            candidate = cost + weight
            if candidate >= distance[neighbor]:
                continue
            distance[neighbor] = candidate
            parent[neighbor] = vertex
            heappush(queue, (candidate, neighbor))
    return distance, parent
