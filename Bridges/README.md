# Bridges and articulation points

Find edges and vertices whose removal increases the number of connected components of an undirected graph.

## My solution

An iterative DFS records entry times and low-link values. A child subtree with no back edge above its parent exposes a bridge or articulation point. DFS roots are articulation points only when they have multiple DFS children. Parent edges are skipped by edge ID, preserving parallel-edge correctness.

## Complexity

O(V + E) time and auxiliary space. Scanning edge and vertex flags returns sorted results without a sorting step.

## Usage and assumptions

`bridges_and_articulation_points(size, edges)` takes a nonnegative vertex count and undirected `(a, b)` edge pairs, each listed once. Its Python result is `(bridges, articulation)`; C++ returns `BridgesResult` with these fields. Both outputs are sorted integer lists. Bridges are zero-based indices into the input edge list, not endpoint pairs. Articulation points are vertex IDs. Empty/disconnected graphs, isolated vertices, self-loops, and parallel edges are supported.

Vertices and edge endpoints must be valid zero-based indices. Vertex counts are nonnegative, C++ counts/indices must fit in int, and inputs must fit in memory. Graph adjacency and edge endpoints are assumed valid.

```python
from Bridges.Bridges import bridges_and_articulation_points

# Parallel edges between 0 and 1 prevent either from being a bridge.
assert bridges_and_articulation_points(3, [(0, 1), (0, 1), (1, 2)]) == ([2], [1])
```

Run the example from the repository root. C++ implementations are reusable C++17 snippets with dynamic storage and no demo `main`; include the file in one translation unit.

## Tests

Random multigraphs are checked by removing each edge or vertex and recounting connected components. Regressions cover parallel edges, self-loops, root articulation rules, empty graphs, and a 5,000-vertex chain. [`test_Bridges.py`](test_Bridges.py) and [`test_Bridges.cpp`](test_Bridges.cpp) run with:

```sh
python3 -m unittest discover -s Bridges -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
