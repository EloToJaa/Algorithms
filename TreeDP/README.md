# Tree DP

Linear-time DPs on general trees given as undirected edge lists: diameter, maximum path sum, maximum-weight independent set, and sum of distances by rerooting.

## My solution

All functions root the tree at 0, record an iterative DFS preorder with parents, and scan it backwards so every child is finished before its parent (no recursion, so deep trees are safe).

- Path pattern (`tree_diameter`, `max_path_sum`): each vertex returns its best *downward chain* to the parent, while the global answer is updated with the path that *bends* at the vertex — its value plus the two best child chains. For the diameter chains count edges, so `best = max(best, down[parent] + down[child] + 1)` before extending `down[parent]`. For path sums a child chain is only worth attaching when positive, so clamp at 0: `down = value + max(0, best child)` and `best = max(best, value + top1 + top2)`; starting from `max(values)` keeps the path nonempty when everything is negative.
- `max_independent_set`: two states per vertex — `take[v] = value[v] + Σ skip[child]` and `skip[v] = Σ max(take[child], skip[child])`; answer `max(take[root], skip[root])`.
- `sum_of_distances` (rerooting): one bottom-up pass computes subtree sizes and the root answer `ans[0] = Σ depth`. Moving the root from a parent to its child brings the child's `size[child]` vertices one step closer and pushes the other `n - size[child]` one step farther, so top-down `ans[child] = ans[parent] - size[child] + (n - size[child])`.

## Complexity

O(n) time and O(n) space for each function.

## Usage and assumptions

The tree has n ≥ 1 vertices and n - 1 valid zero-based edges `(a, b)` in any direction. `tree_diameter(n, edges)` returns an edge count. `max_path_sum(values, edges)` and `max_independent_set(values, edges)` take `n = len(values)`; values may be negative, the path is nonempty, and the independent set may be empty (so the result is ≥ 0). `sum_of_distances(n, edges)` returns a list of per-vertex sums. C++ equivalents are `treeDiameter`, `maxPathSum`, `maxIndependentSet` (with `std::vector<long long>` values), and `sumOfDistances`, taking `std::vector<std::pair<int, int>>` edges; `treeOrder` is the shared traversal helper.

```python
from TreeDP.TreeDP import (
    max_independent_set,
    max_path_sum,
    sum_of_distances,
    tree_diameter,
)

tree_diameter(6, [(0, 1), (1, 2), (2, 3), (1, 4), (4, 5)]) == 4
max_path_sum([-10, 9, 20, 15, 7], [(0, 1), (0, 2), (2, 3), (2, 4)]) == 42
max_independent_set([3, 2, 3, 3, 1], [(0, 1), (0, 2), (1, 3), (2, 4)]) == 7
sum_of_distances(6, [(0, 1), (0, 2), (2, 3), (2, 4), (2, 5)]) == [8, 12, 6, 10, 10, 10]
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

New snippet.

## LeetCode problems

- [1245. Tree Diameter](https://leetcode.com/problems/tree-diameter/)
- [124. Binary Tree Maximum Path Sum](https://leetcode.com/problems/binary-tree-maximum-path-sum/)
- [337. House Robber III](https://leetcode.com/problems/house-robber-iii/)
- [834. Sum of Distances in Tree](https://leetcode.com/problems/sum-of-distances-in-tree/)
- [543. Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/)
- [310. Minimum Height Trees](https://leetcode.com/problems/minimum-height-trees/) — rerooting the height, or peel leaves
- [2246. Longest Path With Different Adjacent Characters](https://leetcode.com/problems/longest-path-with-different-adjacent-characters/) — diameter skipping equal-character children
- [968. Binary Tree Cameras](https://leetcode.com/problems/binary-tree-cameras/) — three states per vertex

## Tests

[`test_TreeDP.py`](test_TreeDP.py) checks the Python implementation; [`test_TreeDP.cpp`](test_TreeDP.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s TreeDP -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
