# Bitmask DP

Dynamic programming and BFS over subsets of up to about 16–20 items: Held–Karp travelling salesman, k equal-sum partition, and shortest walk visiting every node.

## My solution

- `held_karp`: the state is `(mask, last)` — which vertices the path from 0 has visited and where it currently ends; the order inside `mask` no longer matters, which collapses n! orders into 2^n·n states. `best[mask | 1 << next][next] = min(best[mask][last] + cost[last][next])`, iterating masks in increasing order (supersets are numerically larger) and only odd masks since vertex 0 is always visited. Close the cycle with `min(best[full][last] + cost[last][0])`.
- `can_partition_k_subsets`: fill buckets one at a time in any order. `filled[mask]` is the amount in the open bucket after placing exactly `mask`; it is determined by `sum(mask) % target`, so one value per mask suffices. Add an unplaced number only if it fits, and wrap to 0 when the bucket becomes full; the answer is `filled[full] == 0`.
- `shortest_path_visiting_all_nodes`: unweighted edges, so BFS over states `(node, visited mask)` started from every `(v, 1 << v)` simultaneously; the first state reaching the full mask gives the answer. Revisiting vertices is allowed because the mask, not the vertex, is what must grow.

## Complexity

`held_karp` O(2^n·n^2) time and O(2^n·n) space; `can_partition_k_subsets` O(2^n·n) time and O(2^n) space; `shortest_path_visiting_all_nodes` O(2^n·(n + E)) time and O(2^n·n) space.

## Usage and assumptions

`held_karp(cost)` takes a dense n×n matrix with `math.inf` for missing edges and returns the cheapest cycle through vertex 0, `inf` if none, or 0 when n ≤ 1. `can_partition_k_subsets(nums, k)` assumes positive integers and k ≥ 1. `shortest_path_visiting_all_nodes(graph)` takes zero-based undirected adjacency lists and returns the edge count, 0 when n ≤ 1, or -1 if the graph is disconnected. C++ equivalents are `heldKarp` (signed 64-bit costs, entries ≥ `heldKarpInf` mean no edge and `heldKarpInf` means no cycle), `canPartitionKSubsets`, and `shortestPathVisitingAllNodes`.

```python
from BitmaskDP.BitmaskDP import (
    can_partition_k_subsets,
    held_karp,
    shortest_path_visiting_all_nodes,
)

held_karp([[0, 10, 15, 20], [10, 0, 35, 25], [15, 35, 0, 30], [20, 25, 30, 0]]) == 80
can_partition_k_subsets([4, 3, 2, 3, 5, 2, 1], 4)
shortest_path_visiting_all_nodes([[1, 2, 3], [0], [0], [0]]) == 4
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

New snippet.

## LeetCode problems

- [698. Partition to K Equal Sum Subsets](https://leetcode.com/problems/partition-to-k-equal-sum-subsets/)
- [847. Shortest Path Visiting All Nodes](https://leetcode.com/problems/shortest-path-visiting-all-nodes/)
- [943. Find the Shortest Superstring](https://leetcode.com/problems/find-the-shortest-superstring/) — Held–Karp path with overlap costs
- [473. Matchsticks to Square](https://leetcode.com/problems/matchsticks-to-square/) — k = 4 partition
- [1986. Minimum Number of Work Sessions to Finish the Tasks](https://leetcode.com/problems/minimum-number-of-work-sessions-to-finish-the-tasks/) — (buckets, filled) per mask
- [526. Beautiful Arrangement](https://leetcode.com/problems/beautiful-arrangement/) — count over masks of used numbers
- [1125. Smallest Sufficient Team](https://leetcode.com/problems/smallest-sufficient-team/) — DP over skill masks

## Tests

[`test_BitmaskDP.py`](test_BitmaskDP.py) checks the Python implementation; [`test_BitmaskDP.cpp`](test_BitmaskDP.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s BitmaskDP -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
