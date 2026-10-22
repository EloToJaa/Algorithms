"""Tree DPs on edge lists: diameter, max path sum, independent set, rerooting."""

from collections.abc import Iterable, Sequence


def _order(n: int, edges: Iterable[tuple[int, int]]) -> tuple[list[int], list[int]]:
    """Iterative DFS preorder from 0 and parents (-1 for the root)."""
    graph: list[list[int]] = [[] for _ in range(n)]
    for a, b in edges:
        graph[a].append(b)
        graph[b].append(a)
    parent = [-1] * n
    order: list[int] = []
    stack = [0]
    while stack:
        vertex = stack.pop()
        order.append(vertex)
        for neighbor in graph[vertex]:
            if neighbor == parent[vertex]:
                continue
            parent[neighbor] = vertex
            stack.append(neighbor)
    return order, parent


def tree_diameter(n: int, edges: Iterable[tuple[int, int]]) -> int:
    """Edges on the longest path of a tree with n >= 1 vertices."""
    order, parent = _order(n, edges)
    down = [0] * n  # longest downward chain in edges
    best = 0
    for vertex in reversed(order):
        up = parent[vertex]
        if up < 0:
            continue
        best = max(best, down[up] + down[vertex] + 1)
        down[up] = max(down[up], down[vertex] + 1)
    return best


def max_path_sum(values: Sequence[int], edges: Iterable[tuple[int, int]]) -> int:
    """Largest vertex-value sum over nonempty simple paths; values may be negative."""
    n = len(values)
    order, parent = _order(n, edges)
    gain = [0] * n  # best nonnegative chain hanging below vertex, excluding it
    second = [0] * n
    best = max(values)
    for vertex in reversed(order):
        down = values[vertex] + gain[vertex]
        best = max(best, down + second[vertex])
        up = parent[vertex]
        if up < 0 or down <= second[up]:
            continue
        if down > gain[up]:
            gain[up], second[up] = down, gain[up]
        else:
            second[up] = down
    return best


def max_independent_set(values: Sequence[int], edges: Iterable[tuple[int, int]]) -> int:
    """Max value sum of pairwise nonadjacent vertices (empty set allowed)."""
    n = len(values)
    order, parent = _order(n, edges)
    take = list(values)
    skip = [0] * n
    for vertex in reversed(order):
        up = parent[vertex]
        if up < 0:
            continue
        take[up] += skip[vertex]
        skip[up] += max(take[vertex], skip[vertex])
    return max(take[0], skip[0])


def sum_of_distances(n: int, edges: Iterable[tuple[int, int]]) -> list[int]:
    """answer[v] is the sum of edge distances from v to every vertex."""
    order, parent = _order(n, edges)
    size = [1] * n
    depth = [0] * n
    for vertex in order[1:]:
        depth[vertex] = depth[parent[vertex]] + 1
    for vertex in reversed(order[1:]):
        size[parent[vertex]] += size[vertex]
    answer = [0] * n
    answer[0] = sum(depth)
    for vertex in order[1:]:
        # size[vertex] vertices get 1 closer, the other n - size[vertex] get 1 farther.
        answer[vertex] = answer[parent[vertex]] - size[vertex] + (n - size[vertex])
    return answer
