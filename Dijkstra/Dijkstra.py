"""Shortest paths in graphs with nonnegative edge weights."""

from heapq import heappop, heappush
from math import inf


def dijkstra(graph, start):
    """Return (distances, predecessors); adjacency entries are (vertex, weight)."""
    distance = [inf] * len(graph)
    parent = [None] * len(graph)
    distance[start] = 0
    queue = [(0, start)]
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
