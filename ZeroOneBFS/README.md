# 0–1 BFS

Compute shortest paths from one source when all edge weights are zero or one.

## My solution

Relax outgoing edges using a deque: zero-cost improvements go to the front and unit-cost improvements go to the back. Each entry stores its tentative distance so stale entries can be skipped.

## Complexity

O(V + E) time and O(V + E) auxiliary space, including queued entries and weight validation.

## Usage and assumptions

`zero_one_bfs(graph, start)` takes directed adjacency entries `(neighbor, weight)`. Add both directions for undirected edges. Python returns `(distance, parent)` with `math.inf` and `None` for unreachable vertices. C++ returns `ZeroOneBFSResult` with `distance` and `parent`, using `INT_MAX` and -1 for unreachable entries. The source predecessor is unset. All weights, including edges unreachable from the source, must be 0 or 1; invalid weights or sources raise exceptions. Parallel edges, self-loops, and zero-weight cycles are supported.

Vertices and edge endpoints must be valid zero-based indices. Vertex counts are nonnegative, C++ counts/indices must fit in int, and inputs must fit in memory. Graph adjacency and edge endpoints are assumed valid.

```python
from ZeroOneBFS.ZeroOneBFS import zero_one_bfs

distance, parent = zero_one_bfs([[(1, 1), (2, 0)], [], [(1, 0)]], 0)
assert distance == [0, 0, 0]
assert parent == [None, 2, 0]
```

Run the example from the repository root. C++ implementations are reusable C++17 snippets with dynamic storage and no demo `main`; include the file in one translation unit.

## Tests

Python compares random graphs against Dijkstra; C++ uses repeated relaxation as a reference. Tests verify predecessor paths terminate at the source, and cover unreachable vertices, self-loops, zero-cost cycles, and invalid weights/sources. [`test_ZeroOneBFS.py`](test_ZeroOneBFS.py) and [`test_ZeroOneBFS.cpp`](test_ZeroOneBFS.cpp) run with:

```sh
python3 -m unittest discover -s ZeroOneBFS -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
