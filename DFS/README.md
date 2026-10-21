# Depth-first search

Explore one graph branch fully before returning to explore other neighbors.

## My solution

Keep an explicit stack of neighbor iterators (C++: vertex/index pairs). Mark a vertex on discovery; this reproduces recursive DFS order without using the call stack.

## Complexity

O(V + E) time and O(V) auxiliary space.

## Usage and assumptions

`dfs(graph, start)` returns visitation order. C++ uses global `V` and `Vis`; `dfs(v, p)` retains the original signature, but the parent argument is unnecessary for visited-based traversal. Reset `Vis` before a fresh traversal.

```python
from DFS.DFS import dfs

dfs([[1, 2], [2, 3], [], []], 0) == [0, 1, 2, 3]
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

C++ recursion was replaced with an explicit stack so long chains do not overflow the call stack.

## LeetCode problems

- [200. Number of Islands](https://leetcode.com/problems/number-of-islands/)
- [547. Number of Provinces](https://leetcode.com/problems/number-of-provinces/)
- [133. Clone Graph](https://leetcode.com/problems/clone-graph/)
- [797. All Paths From Source to Target](https://leetcode.com/problems/all-paths-from-source-to-target/)

## Tests

[`test_DFS.py`](test_DFS.py) checks the Python implementation; [`test_DFS.cpp`](test_DFS.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s DFS -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
