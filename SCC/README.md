# Strongly connected components

Partition a directed graph into maximal groups of mutually reachable vertices.

## My solution

Kosaraju's algorithm first records DFS finishing order, then traverses the reversed graph in reverse finishing order. Both passes use explicit stacks.

## Complexity

O(V + E) time and O(V + E) auxiliary space, including the reversed graph.

## Usage and assumptions

Python `strongly_connected_components(graph)` returns `(component, groups)`. C++ returns `SCCResult` with the same field names. `component[v]` indexes the vertex list in `groups`. Component IDs follow topological order of the condensation graph: an edge between different components goes from a smaller ID to a larger ID. IDs and group member order depend on traversal order. Disconnected graphs, parallel edges, self-loops, and empty graphs are supported.

Vertices and edge endpoints must be valid zero-based indices. Vertex counts are nonnegative, C++ counts/indices must fit in int, and inputs must fit in memory. Graph adjacency and edge endpoints are assumed valid.

```python
from SCC.SCC import strongly_connected_components

component, groups = strongly_connected_components([[1], [0, 2], [3], [2]])
assert component == [0, 0, 1, 1]
assert [sorted(group) for group in groups] == [[0, 1], [2, 3]]
```

Run the example from the repository root. C++ implementations are reusable C++17 snippets with dynamic storage and no demo `main`; include the file in one translation unit.

## Tests

Random graphs are checked against mutual reachability, including the complete partition and condensation ordering. A 5,000-vertex chain and cycle verify deep iterative traversals. [`test_SCC.py`](test_SCC.py) and [`test_SCC.cpp`](test_SCC.cpp) run with:

```sh
python3 -m unittest discover -s SCC -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
