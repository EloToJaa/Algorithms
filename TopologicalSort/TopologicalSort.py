"""Kahn's topological ordering for directed graphs."""

from collections import deque


def topological_sort(graph):
    """Return a vertex ordering; raise ValueError if any directed cycle exists."""
    indegree = [0] * len(graph)
    for edges in graph:
        for neighbor in edges:
            indegree[neighbor] += 1
    queue = deque(v for v, degree in enumerate(indegree) if degree == 0)
    order = []
    while queue:
        vertex = queue.popleft()
        order.append(vertex)
        for neighbor in graph[vertex]:
            indegree[neighbor] -= 1
            if indegree[neighbor] == 0:
                queue.append(neighbor)
    if len(order) != len(graph):
        raise ValueError("directed cycle")
    return order
