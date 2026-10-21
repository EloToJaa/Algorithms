"""Iterative Kosaraju decomposition of directed graphs."""

from collections.abc import Sequence


def strongly_connected_components(
    graph: Sequence[Sequence[int]],
) -> tuple[list[int], list[list[int]]]:
    """Return (component IDs, vertex groups); IDs follow condensation order."""
    size = len(graph)
    reverse: list[list[int]] = [[] for _ in graph]
    for vertex, edges in enumerate(graph):
        for neighbor in edges:
            reverse[neighbor].append(vertex)
    seen = [False] * size
    order: list[int] = []
    for start in range(size):
        if seen[start]:
            continue
        seen[start] = True
        stack = [(start, iter(graph[start]))]
        while stack:
            vertex, edges = stack[-1]
            neighbor = next(edges, None)
            if neighbor is None:
                order.append(vertex)
                stack.pop()
                continue
            if not seen[neighbor]:
                seen[neighbor] = True
                stack.append((neighbor, iter(graph[neighbor])))
    component = [-1] * size
    groups: list[list[int]] = []
    for start in reversed(order):
        if component[start] != -1:
            continue
        identifier = len(groups)
        component[start] = identifier
        stack = [start]
        group: list[int] = []
        while stack:
            vertex = stack.pop()
            group.append(vertex)
            for neighbor in reverse[vertex]:
                if component[neighbor] == -1:
                    component[neighbor] = identifier
                    stack.append(neighbor)
        groups.append(group)
    return component, groups
