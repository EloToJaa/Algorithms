# Bellman–Ford

Compute shortest paths with negative edge weights and identify vertices affected by reachable negative cycles.

## My solution

Relax all edges for up to V passes, stopping early if no distance changes. Improvements on the V-th pass seed a graph traversal marking every downstream vertex as affected by a negative cycle.

## Complexity

O(VE + V) worst-case time and O(V + E) auxiliary space.

## Usage and assumptions

`bellman_ford(size, edges, start)` takes directed `(from, to, weight)` edges and a valid source in a nonempty graph. Python accepts integer weights and returns `(distance, parent)`: unreachable distances are `math.inf`, affected distances are `-math.inf`, and their predecessors are `None`. C++ takes `std::vector<BellmanFordEdge>` with signed 64-bit weights and returns `BellmanFordResult` containing `distance` (`std::optional<long long>`), `parent`, and `negative`. Missing distance with `negative[v] == false` means unreachable; `negative[v] == true` means no finite shortest distance. These vertices have parent -1. Finite predecessors reconstruct shortest paths. Unreachable negative cycles do not affect results. C++ uses GCC/Clang `__int128` intermediate distances and throws `std::overflow_error` if a final finite distance cannot fit in `long long`.

Vertices and edge endpoints must be valid zero-based indices. Vertex counts are nonnegative, C++ counts/indices must fit in int, and inputs must fit in memory. Graph adjacency and edge endpoints are assumed valid.

```python
from BellmanFord.BellmanFord import bellman_ford
from math import inf

assert bellman_ford(3, [(0, 1, 4), (1, 2, -6)], 0)[0] == [0, 4, -2]
assert bellman_ford(3, [(0, 1, 0), (1, 1, -1), (1, 2, 2)], 0)[0] == [0, -inf, -inf]
```

Run the example from the repository root. C++ implementations are reusable C++17 snippets with dynamic storage and no demo `main`; include the file in one translation unit.

## Tests

Random signed-weight graphs are checked against Floyd–Warshall, including negative-cycle reachability and predecessor paths. Regressions cover downstream propagation, unreachable cycles, self-loops, empty edge lists, invalid sources, and C++ distance boundaries/overflow. [`test_BellmanFord.py`](test_BellmanFord.py) and [`test_BellmanFord.cpp`](test_BellmanFord.cpp) run with:

```sh
python3 -m unittest discover -s BellmanFord -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
