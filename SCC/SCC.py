"""Iterative Kosaraju decomposition of directed graphs."""


def strongly_connected_components(graph):
    """Return (component IDs, vertex groups); IDs follow condensation order."""
    size = len(graph)
    reverse = [[] for _ in graph]
    for vertex, edges in enumerate(graph):
        for neighbor in edges:
            reverse[neighbor].append(vertex)
    seen, order = [False] * size, []
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
    component, groups = [-1] * size, []
    for start in reversed(order):
        if component[start] != -1:
            continue
        identifier = len(groups)
        component[start] = identifier
        stack, group = [start], []
        while stack:
            vertex = stack.pop()
            group.append(vertex)
            for neighbor in reverse[vertex]:
                if component[neighbor] == -1:
                    component[neighbor] = identifier
                    stack.append(neighbor)
        groups.append(group)
    return component, groups
