# Topological sort

Order the vertices of a directed acyclic graph so every edge points forward.

## My solution

Kahn's algorithm tracks indegrees and processes zero-indegree vertices through a FIFO queue. If fewer than all vertices are processed, the graph has a directed cycle.

## Complexity

O(V + E) time and O(V) auxiliary space.

## Usage and assumptions

`topological_sort(graph)` takes a directed adjacency sequence and returns every vertex exactly once. Python raises `ValueError` and C++ raises `std::domain_error` on a cycle, including a cycle in a disconnected component. Empty graphs return an empty order. Parallel edges and self-loops are supported; a self-loop is a cycle. The order is deterministic for a given adjacency order, but is not necessarily lexicographically smallest.

Vertices and edge endpoints must be valid zero-based indices. Vertex counts are nonnegative, C++ counts/indices must fit in int, and inputs must fit in memory. Graph adjacency and edge endpoints are assumed valid.

```python
from TopologicalSort.TopologicalSort import topological_sort

assert topological_sort([[1, 2], [2], []]) == [0, 1, 2]
```

Run the example from the repository root. C++ implementations are reusable C++17 snippets with dynamic storage and no demo `main`; include the file in one translation unit.

## Tests

Random DAGs check that every edge points forward and every vertex occurs once. Regressions cover disconnected cycles, self-loops, parallel edges, empty graphs, and a 5,000-vertex chain. [`test_TopologicalSort.py`](test_TopologicalSort.py) and [`test_TopologicalSort.cpp`](test_TopologicalSort.cpp) run with:

```sh
python3 -m unittest discover -s TopologicalSort -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
