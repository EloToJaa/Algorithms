# Kruskal's minimum spanning forest

Select minimum-weight edges connecting each component of an undirected weighted graph without cycles.

## My solution

Sort edges by weight and use path-compressed, size-weighted disjoint sets to accept exactly those edges joining different components.

## Complexity

O(E log E + V) time and O(V + E) space including copied/sorted edges and output.

## Usage and assumptions

`kruskal(n, edges)` returns `(total_weight, selected_edges)`; edges are `(a, b, weight)`. Disconnected input produces a minimum spanning forest. Parallel edges, self-loops, and negative weights are allowed. C++ fills `K[1..m]`, calls `Kruskal(n, m)`, and reads `selected` and `totalWeight`.

```python
from Kruskal.Kruskal import kruskal

kruskal(3, [(0, 1, 2), (1, 2, 1), (0, 2, 9)])[0] == 3
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

C++ now exposes the accepted edges and a 64-bit total weight, resetting both on each run.

## Tests

[`test_Kruskal.py`](test_Kruskal.py) checks the Python implementation; [`test_Kruskal.cpp`](test_Kruskal.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s Kruskal -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
