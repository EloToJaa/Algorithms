"""All-pairs shortest paths with negative-cycle marking and path reconstruction."""

from collections.abc import Iterable, Sequence
from math import inf


def floyd_warshall(
    n: int, edges: Iterable[tuple[int, int, float]]
) -> tuple[list[list[float]], list[list[int | None]]]:
    """Directed (from, to, weight) edges; return (dist, nxt).

    dist[i][j] is inf if j is unreachable from i and -inf if some walk from i to j
    passes through a negative cycle; nxt[i][j] is the vertex after i on a
    shortest path (None if unreachable).
    """
    dist = [[inf] * n for _ in range(n)]
    nxt: list[list[int | None]] = [[None] * n for _ in range(n)]
    for v in range(n):
        dist[v][v], nxt[v][v] = 0, v
    for u, v, w in edges:
        if w < dist[u][v]:
            dist[u][v], nxt[u][v] = w, v
    for k in range(n):
        for i in range(n):
            if dist[i][k] == inf:
                continue
            for j in range(n):
                if dist[i][k] + dist[k][j] < dist[i][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]
                    nxt[i][j] = nxt[i][k]
    # i -> k -> j with a negative closed walk through k makes i -> j unbounded.
    cycle = [k for k in range(n) if dist[k][k] < 0]
    for i in range(n):
        for j in range(n):
            if any(dist[i][k] < inf and dist[k][j] < inf for k in cycle):
                dist[i][j] = -inf
    return dist, nxt


def negative_cycle_vertices(dist: Sequence[Sequence[float]]) -> list[int]:
    """Vertices lying on a negative closed walk (dist[v][v] == -inf)."""
    return [v for v in range(len(dist)) if dist[v][v] == -inf]


def reconstruct_path(
    dist: Sequence[Sequence[float]],
    nxt: Sequence[Sequence[int | None]],
    start: int,
    end: int,
) -> list[int] | None:
    """Vertices of a shortest start -> end path; None if unreachable or unbounded."""
    if dist[start][end] in (inf, -inf):
        return None
    path = [start]
    while start != end:
        start = nxt[start][end]
        assert start is not None
        path.append(start)
    return path
