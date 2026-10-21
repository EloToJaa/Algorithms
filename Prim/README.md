# Prim's minimum spanning forest

Select minimum-weight edges connecting each component of an undirected weighted graph without cycles.

## My solution

Grow a tree from each unvisited root. A min-priority queue holds candidate edges `(weight, vertex, parent)` leaving the tree; the cheapest edge reaching an unvisited vertex is accepted and its neighbors' edges are queued. Stale entries for already-visited vertices are skipped.

## Complexity

O(E log E + V) time and O(V + E) auxiliary space for the queue and output.

## Usage and assumptions

`prim(graph)` takes adjacency entries `(neighbor, weight)`; add both directions for each undirected edge. Python returns `(total_weight, selected_edges)` with edges `(parent, vertex, weight)` in the order vertices join. C++ returns `PrimResult` with `totalWeight` and `selected` (`PrimEdge{a, b, w}`). Disconnected input produces a minimum spanning forest. Parallel edges, self-loops, and negative weights are allowed. Vertices are zero-based and adjacency entries are assumed valid.

```python
from Prim.Prim import prim

graph = [[(1, 2), (2, 9)], [(0, 2), (2, 1)], [(1, 1), (0, 9)]]
assert prim(graph) == (3, [(0, 1, 2), (1, 2, 1)])
```

Run the example from the repository root. The C++ implementation is a reusable C++17 snippet with dynamic storage and no demo `main`. Prefer Prim over [Kruskal](../Kruskal/README.md) when the graph is dense or already stored as adjacency lists.

## LeetCode problems

- [1584. Min Cost to Connect All Points](https://leetcode.com/problems/min-cost-to-connect-all-points/) — dense graph
- [1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/)
- [1631. Path With Minimum Effort](https://leetcode.com/problems/path-with-minimum-effort/) — grow the tree until it reaches the target

## Tests

Both suites compare random multigraphs (including disconnected graphs, self-loops, and negative weights) against Kruskal and check that every selected edge exists. [`test_Prim.py`](test_Prim.py) and [`test_Prim.cpp`](test_Prim.cpp) run with:

```sh
python3 -m unittest discover -s Prim -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
