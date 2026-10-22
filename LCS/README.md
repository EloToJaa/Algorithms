# Longest common subsequence

Find the longest sequence appearing, not necessarily contiguously, in both inputs.

## My solution

Fill `table[i][j]`, the LCS length of the first i and j elements: extend the diagonal on a match, otherwise take the better of dropping either last element. Reconstruct one subsequence by walking back from the bottom-right corner.

## Complexity

O(nm) time and O(nm) space; only the length needs two rows if memory matters.

## Usage and assumptions

`lcs_length(first, second)` returns the length; `lcs(first, second)` returns one longest common subsequence as a list; `lcs_table` exposes the full table. Python accepts any sequences with comparable-by-equality elements. C++ `lcsLength`, `lcs`, and `lcsTable` work on strings.

```python
from LCS.LCS import lcs, lcs_length

lcs_length("abcde", "ace") == 3
"".join(lcs("abcde", "ace")) == "ace"
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

New snippet.

## LeetCode problems

- [1143. Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/)
- [583. Delete Operation for Two Strings](https://leetcode.com/problems/delete-operation-for-two-strings/)
- [1092. Shortest Common Supersequence](https://leetcode.com/problems/shortest-common-supersequence/) — walk the table back
- [72. Edit Distance](https://leetcode.com/problems/edit-distance/) — same table shape

## Tests

[`test_LCS.py`](test_LCS.py) checks the Python implementation; [`test_LCS.cpp`](test_LCS.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s LCS -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
