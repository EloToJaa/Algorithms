# Edit distance

Levenshtein distance: the fewest single-element inserts, deletes, and replacements turning one sequence into another.

## My solution

Fill `table[i][j]`, the distance between the first i elements of `first` and the first j of `second`; the borders are `i` (delete everything) and `j` (insert everything). Each cell takes one of three moves:

- diagonal `table[i-1][j-1]`: keep for free when the last elements match, otherwise replace (+1);
- up `table[i-1][j]`: delete `first[i-1]` (+1);
- left `table[i][j-1]`: insert `second[j-1]` (+1).

On a match keeping is always optimal, since neighbouring cells differ by at most 1. `edit_operations` walks back from the bottom-right corner, choosing any move whose cell explains the current value, then reverses the path into left-to-right operations. `edit_distance` only needs the previous row: scan the longer input in the outer loop, keep a row over the shorter one, and carry the old `row[j-1]` as `diagonal` before it is overwritten.

The table has the same shape as [LCS](../LCS/README.md): with only inserts and deletes allowed, the distance is `n + m - 2 * lcs_length`.

## Complexity

O(nm) time for every function; O(nm) space for the table and reconstruction, O(min(n, m)) for `edit_distance`.

## Usage and assumptions

`edit_distance(first, second)` returns the distance; `edit_distance_table` returns the full `(n + 1) x (m + 1)` table; `edit_operations(first, second)` returns one optimal alignment as tuples `("keep", x)`, `("replace", x, y)`, `("delete", x)`, `("insert", y)` that consume `first` and produce `second` in order, with exactly `distance` non-keep operations. Python accepts any sequences compared by equality. C++ `editDistance`, `editDistanceTable`, and `editOperations` work on strings; operations are `EditOp{type, from, to}` with type `'K'`, `'R'`, `'D'`, or `'I'`.

```python
from EditDistance.EditDistance import edit_distance, edit_operations

edit_distance("horse", "ros") == 3
edit_operations("ab", "b") == [("delete", "a"), ("keep", "b")]
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

New snippet.

## LeetCode problems

- [72. Edit Distance](https://leetcode.com/problems/edit-distance/)
- [583. Delete Operation for Two Strings](https://leetcode.com/problems/delete-operation-for-two-strings/) — no replace move
- [712. Minimum ASCII Delete Sum for Two Strings](https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/) — weighted deletes
- [161. One Edit Distance](https://leetcode.com/problems/one-edit-distance/) — premium; linear check suffices
- [1143. Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/) — same table shape

## Tests

[`test_EditDistance.py`](test_EditDistance.py) checks the Python implementation; [`test_EditDistance.cpp`](test_EditDistance.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s EditDistance -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
