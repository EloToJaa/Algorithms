# Lowest common ancestor

Find the deepest vertex that is an ancestor of both query vertices in a rooted tree.

## My solution

Precompute 2^k-th ancestors. Python equalizes depths, then lifts both vertices; C++ uses DFS entry/exit intervals to test ancestry while lifting. Both preprocess with explicit stacks.

## Complexity

O(n log n) preprocessing/space and O(log n) per query.

## Usage and assumptions

`LCA(graph, root=0).query(a, b)` requires a nonempty connected undirected tree. C++ uses global `V`; call `ancestors(root, root)` before `LCA(a, b)`. The root is its own ancestor. C++ supports up to the fixed N and LOG limits.

```python
from LCA.LCA import LCA

tree = LCA([[1, 2], [0, 3], [0], [1]])
assert tree.query(3, 2) == 0
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

C++ now skips the parent, fixing infinite recursion on undirected trees, and avoids recursion depth limits.

## Tests

[`test_LCA.py`](test_LCA.py) checks the Python implementation; [`test_LCA.cpp`](test_LCA.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s LCA -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
