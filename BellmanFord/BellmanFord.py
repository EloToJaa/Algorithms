"""Shortest paths and vertices affected by reachable negative cycles."""

from collections import deque
from math import inf


def bellman_ford(size, edges, start):
    """Edges are (from, to, weight); return distances and predecessors.

    Unreachable distances are inf; negative-cycle-affected distances are -inf.
    """
    if not 0 <= start < size:
        raise ValueError("invalid source")
    edges = list(edges)
    graph = [[] for _ in range(size)]
    for vertex, neighbor, _ in edges:
        graph[vertex].append(neighbor)
    distance, parent = [inf] * size, [None] * size
    distance[start] = 0
    affected = set()
    for iteration in range(size):
        changed = False
        for vertex, neighbor, weight in edges:
            if (
                distance[vertex] == inf
                or distance[vertex] + weight >= distance[neighbor]
            ):
                continue
            distance[neighbor] = distance[vertex] + weight
            parent[neighbor] = vertex
            changed = True
            if iteration == size - 1:
                affected.add(neighbor)
        if not changed:
            break
    queue = deque(affected)
    while queue:
        for neighbor in graph[queue.popleft()]:
            if neighbor not in affected:
                affected.add(neighbor)
                queue.append(neighbor)
    for vertex in affected:
        distance[vertex], parent[vertex] = -inf, None
    return distance, parent
