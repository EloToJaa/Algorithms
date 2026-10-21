"""Minimum spanning forest by growing trees from a priority queue of edges."""

from heapq import heappop, heappush


def prim(graph):
    """Return (total_weight, selected_edges); adjacency entries are (vertex, weight).

    Selected edges are (parent, vertex, weight) in the order vertices join.
    """
    visited = [False] * len(graph)
    total = 0
    selected = []
    for root in range(len(graph)):
        if visited[root]:
            continue
        queue = [(0, root, -1)]
        while queue:
            weight, vertex, parent = heappop(queue)
            if visited[vertex]:
                continue
            visited[vertex] = True
            if parent != -1:
                selected.append((parent, vertex, weight))
                total += weight
            for neighbor, cost in graph[vertex]:
                if not visited[neighbor]:
                    heappush(queue, (cost, neighbor, vertex))
    return total, selected
