# Floyd–Warshall

All-pairs shortest paths on a dense directed graph with negative weights, marking pairs made unbounded by negative cycles and reconstructing paths.

## My solution

`dist[k][i][j]` is the shortest i → j path whose intermediate vertices all lie in `{0, …, k-1}`. Allowing vertex k either leaves the path alone or splits it at k into two halves that only use smaller vertices, so `dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])`, updated in place (while `dist[k][k] = 0`, row and column k do not change during round k).

- Why k is the outer loop: the recurrence is a DP over k; both halves must already be optimal for *all* pairs over the vertex set `{0, …, k-1}` before k is used as a split. Putting i or j outside would combine values that have not yet seen every intermediate vertex and miss paths.
- Negative cycles: after the main loop `dist[k][k] < 0` certifies a negative closed walk through k (every stored value is the weight of a real walk), and every negative cycle contains at least one such k (its highest-numbered vertex). A pair is unbounded iff i reaches such a k and k reaches j, so those pairs are set to `-inf`; afterwards `dist[v][v] == -inf` precisely for vertices on a negative closed walk (equivalently, in a strongly connected component containing a negative cycle).
- Path reconstruction: `nxt[i][j]` is the first step of the current best path; initialise it to j for direct edges and copy `nxt[i][k]` whenever k improves the pair, then follow `nxt[·][end]` from start.

Single-source alternatives: [Dijkstra](../Dijkstra/README.md) for nonnegative weights and [Bellman–Ford](../BellmanFord/README.md) for negative weights.

## Complexity

O(V^3 + E) time and O(V^2) space; negative-cycle marking adds O(V^3), path reconstruction O(V) per query.

## Usage and assumptions

`floyd_warshall(n, edges)` takes zero-based directed `(from, to, weight)` edges (parallel edges keep the minimum, `dist[v][v]` starts at 0 so only negative self-loops matter) and returns `(dist, nxt)`: `dist[i][j]` is `math.inf` when unreachable and `-math.inf` when a walk from i to j can pass through a negative cycle. `negative_cycle_vertices(dist)` lists vertices with `dist[v][v] == -inf`. `reconstruct_path(dist, nxt, start, end)` returns the vertex list or `None` for unreachable or unbounded pairs. C++ equivalents are `floydWarshall(n, edges)` returning `FloydWarshallResult` with `dist` (`long long`, `floydInf` = `LLONG_MAX / 4` for unreachable and `-floydInf` for unbounded) and `next` (-1 if none), `negativeCycleVertices(dist)`, and `reconstructPath(result, start, end)` returning an empty vector instead of `None`. C++ skips infinite terms before adding and clamps sums at `-floydInf`, so finite shortest distances must have magnitude below `floydInf`.

```python
from FloydWarshall.FloydWarshall import (
    floyd_warshall,
    negative_cycle_vertices,
    reconstruct_path,
)
from math import inf

dist, nxt = floyd_warshall(4, [(0, 1, 3), (1, 2, 1), (0, 2, 5), (2, 3, 2), (3, 0, 2)])
dist[0] == [0, 3, 4, 6]
reconstruct_path(dist, nxt, 0, 3) == [0, 1, 2, 3]
dist, nxt = floyd_warshall(3, [(0, 1, 1), (1, 1, -1), (2, 0, 1)])
dist[0] == [0, -inf, inf]
negative_cycle_vertices(dist) == [1]
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

New snippet.

## LeetCode problems

- [1334. Find the City With the Smallest Number of Neighbors at a Threshold Distance](https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/)
- [1462. Course Schedule IV](https://leetcode.com/problems/course-schedule-iv/) — boolean transitive closure
- [399. Evaluate Division](https://leetcode.com/problems/evaluate-division/) — multiply ratios instead of adding
- [2976. Minimum Cost to Convert String I](https://leetcode.com/problems/minimum-cost-to-convert-string-i/) — 26-letter APSP
- [743. Network Delay Time](https://leetcode.com/problems/network-delay-time/)
- [1617. Count Subtrees With Max Distance Between Cities](https://leetcode.com/problems/count-subtrees-with-max-distance-between-cities/) — APSP plus subset enumeration

## Tests

[`test_FloydWarshall.py`](test_FloydWarshall.py) checks the Python implementation; [`test_FloydWarshall.cpp`](test_FloydWarshall.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s FloydWarshall -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
