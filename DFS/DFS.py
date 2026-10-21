"""Depth-first traversal without Python recursion limits."""

from collections.abc import Sequence


def dfs(graph: Sequence[Sequence[int]], start: int) -> list[int]:
    """Return recursive-style DFS order for an adjacency sequence."""
    seen = {start}
    order = [start]
    stack = [iter(graph[start])]
    while stack:
        neighbor = next(stack[-1], None)
        if neighbor is None:
            stack.pop()
            continue
        if neighbor in seen:
            continue
        seen.add(neighbor)
        order.append(neighbor)
        stack.append(iter(graph[neighbor]))
    return order
