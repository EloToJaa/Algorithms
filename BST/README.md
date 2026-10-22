# Binary search tree

Store distinct keys in order, supporting insertion, deletion, membership, minimum/maximum, lower bound, and sorted iteration.

## My solution

Keep every left subtree smaller and every right subtree larger than its node. Searches walk down from the root. Removal splices out a node with at most one child; a node with two children takes its in-order successor's key, and the successor is spliced out instead. All operations, including in-order traversal, are iterative, so degenerate trees do not overflow the call stack.

The tree is unbalanced. For guaranteed O(log n) operations use a balanced tree (C++ `std::set`), or [Heap](../Heap/README.md) when only the minimum or maximum is needed.

## Complexity

O(h) insert/remove/contains/min/max/lower bound, where h is the height: O(log n) expected for random insertion order, O(n) worst case (for example, sorted insertion). O(n) traversal and O(n) space.

## Usage and assumptions

`BST(keys)` provides `insert`, `remove` (both return whether the tree changed), `key in tree`, `min`, `max`, `lower_bound` (smallest key >= x, or None), `len(tree)`, and in-order iteration. Duplicate keys are ignored. `min`/`max` on an empty tree raise ValueError in Python and out_of_range in C++. C++ `BST` stores `int` keys and provides `insert`, `remove`, `contains`, `min`, `max`, `lowerBound` (returning `optional<int>`), `inorder`, `size`, and `empty`. C++ nodes live in a vector and link by index; removed nodes are not reclaimed.

```python
from BST.BST import BST

tree = BST([5, 2, 8, 1])
tree.remove(5)
assert list(tree) == [1, 2, 8] and tree.lower_bound(3) == 8
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

New snippet, written iteratively like the [DFS](../DFS/README.md) and [LCA](../LCA/README.md) fixes, to avoid unbounded call-stack depth.

## LeetCode problems

- [701. Insert into a Binary Search Tree](https://leetcode.com/problems/insert-into-a-binary-search-tree/)
- [450. Delete Node in a BST](https://leetcode.com/problems/delete-node-in-a-bst/)
- [700. Search in a Binary Search Tree](https://leetcode.com/problems/search-in-a-binary-search-tree/)
- [98. Validate Binary Search Tree](https://leetcode.com/problems/validate-binary-search-tree/)
- [230. Kth Smallest Element in a BST](https://leetcode.com/problems/kth-smallest-element-in-a-bst/) — iterative in-order walk

## Tests

[`test_BST.py`](test_BST.py) checks the Python implementation; [`test_BST.cpp`](test_BST.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s BST -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
