# Dijkstra's shortest paths

Find minimum weighted distances from one vertex in a graph whose edge weights are nonnegative.

## My solution

Use a priority queue of tentative distances. Relax outgoing edges and skip obsolete queue entries. Record each successful relaxation in a predecessor array.

## Complexity

O((V + E) log(V + E)) time with the duplicate-entry heap, O(V + E) auxiliary space.

## Usage and assumptions

`dijkstra(graph, start)` returns `(distances, predecessors)`. Adjacency entries are `(neighbor, weight)`; unreachable vertices have `math.inf` and `None`. C++ calls `dijkstra(start, n)` with vertices 1..n and returns data through `D` and `path`; unreachable entries are `LLONG_MAX` and -1. Nonnegative weights and representable C++ distances are required.

```python
from Dijkstra.Dijkstra import dijkstra

dijkstra([[(1, 4), (2, 1)], [], [(1, 2)]], 0)[0] == [0, 3, 1]
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

C++ heap keys now use `long long`, predecessors and the queue reset between runs, and overflowing relaxations are skipped.

## Tests

[`test_Dijkstra.py`](test_Dijkstra.py) checks the Python implementation; [`test_Dijkstra.cpp`](test_Dijkstra.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s Dijkstra -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
