"""Minimum spanning forest by sorting edges and joining disjoint sets."""


def kruskal(size, edges):
    """Return (total_weight, selected_edges); edges are (a, b, weight)."""
    parent = list(range(size))
    counts = [1] * size

    def find(vertex):
        while parent[vertex] != vertex:
            parent[vertex] = parent[parent[vertex]]
            vertex = parent[vertex]
        return vertex

    total = 0
    selected = []
    for first, second, weight in sorted(edges, key=lambda edge: edge[2]):
        a, b = find(first), find(second)
        if a == b:
            continue
        if counts[a] > counts[b]:
            a, b = b, a
        parent[a] = b
        counts[b] += counts[a]
        selected.append((first, second, weight))
        total += weight
    return total, selected
