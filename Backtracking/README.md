# Backtracking

Choose / recurse / un-choose templates for subsets, permutations, combinations, combination sums, and N-Queens.

## My solution

Every function grows one shared `path`: append a choice, recurse, then pop it so the next sibling starts from the same state. What changes between problems is only which choices a level may try.

- `subsets`: every node of the recursion tree is an answer; a level tries indices from `start` on and recurses with `i + 1`, so each set is built in increasing index order exactly once.
- `subsets_with_dup`: sort first, then skip `i > start and nums[i] == nums[i - 1]`. Equal values may be picked at the same level only once (the first copy), yet deeper levels may still take the next copy, so `[2, 2]` survives while a second `[2]` branch is pruned.
- `permutations`: order matters, so every level scans all indices and a `used` array blocks reusing a position; leaves at depth n are answers.
- `combinations`: like `subsets` but only depth-k leaves count; the loop stops at `n - (k - len(path)) + 1` because later starts cannot fill the path.
- `combination_sum`: recurse with `i` instead of `i + 1` so a candidate may repeat, and break once a sorted candidate exceeds the remainder.
- `n_queens` / `total_n_queens`: place one queen per row; a column is free unless its column, `row - col` diagonal, or `row + col` anti-diagonal is taken. The counting version keeps the three sets as bitmasks and shifts the diagonal masks by one column per row, so `free & -free` enumerates open squares directly.

## Complexity

`subsets` and `subsets_with_dup` are O(n 2^n); `permutations` O(n n!); `combinations` O(k C(n, k)); `combination_sum` is output-sensitive (exponential in the worst case); N-Queens is O(n!) with heavy pruning. Recursion depth is O(n) (O(target / min candidate) for `combination_sum`).

## Usage and assumptions

`subsets(nums)`, `subsets_with_dup(nums)`, and `permutations(nums)` return lists of lists in DFS order; `subsets_with_dup` returns each subset sorted. `combinations(n, k)` draws values from 1..n as in LeetCode. `combination_sum(candidates, target)` assumes distinct positive candidates and returns sorted lists. `n_queens(n)` returns boards of `'.'`/`'Q'` strings; `total_n_queens(n)` returns the count. C++ `subsets`, `subsetsWithDup`, `permutations`, `combinations`, `combinationSum`, `solveNQueens`, and `totalNQueens` mirror them (bitmask count for n <= 30).

```python
from Backtracking.Backtracking import combination_sum, subsets_with_dup, total_n_queens

subsets_with_dup([1, 2, 2]) == [[], [1], [1, 2], [1, 2, 2], [2], [2, 2]]
combination_sum([2, 3, 6, 7], 7) == [[2, 2, 3], [7]]
total_n_queens(8) == 92
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

New snippet.

## LeetCode problems

- [78. Subsets](https://leetcode.com/problems/subsets/)
- [90. Subsets II](https://leetcode.com/problems/subsets-ii/) — sort + skip duplicates
- [46. Permutations](https://leetcode.com/problems/permutations/)
- [77. Combinations](https://leetcode.com/problems/combinations/)
- [39. Combination Sum](https://leetcode.com/problems/combination-sum/)
- [40. Combination Sum II](https://leetcode.com/problems/combination-sum-ii/) — recurse with `i + 1` plus the duplicate skip
- [51. N-Queens](https://leetcode.com/problems/n-queens/)
- [52. N-Queens II](https://leetcode.com/problems/n-queens-ii/)

## Tests

[`test_Backtracking.py`](test_Backtracking.py) checks the Python implementation; [`test_Backtracking.cpp`](test_Backtracking.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s Backtracking -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
