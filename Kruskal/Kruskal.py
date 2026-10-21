"""Minimum spanning forest by sorting edges and joining disjoint sets."""

from collections.abc import Iterable


def kruskal(
    size: int, edges: Iterable[tuple[int, int, float]]
) -> tuple[float, list[tuple[int, int, float]]]:
    """Return (total_weight, selected_edges); edges are (a, b, weight)."""
    parent = list(range(size))
    counts = [1] * size

    def find(vertex: int) -> int:
        while parent[vertex] != vertex:
            parent[vertex] = parent[parent[vertex]]
            vertex = parent[vertex]
        return vertex

    def union(first: int, second: int) -> bool:
        first, second = find(first), find(second)
        if first == second:
            return False
        if counts[first] > counts[second]:
            first, second = second, first
        parent[first] = second
        counts[second] += counts[first]
        return True

    total: float = 0
    selected: list[tuple[int, int, float]] = []
    for first, second, weight in sorted(edges, key=lambda edge: edge[2]):
        if not union(first, second):
            continue
        selected.append((first, second, weight))
        total += weight
    return total, selected
