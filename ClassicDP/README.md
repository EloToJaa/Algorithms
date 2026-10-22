# Classic DPs

Common one- and two-dimensional DPs: house robber, coin change, grid paths, and word break.

## My solution

- `rob`: track `take` (best using the current house) and `skip` (best without it); `take' = skip + value`, `skip' = max(take, skip)`. O(1) memory.
- `rob_circular`: the first and last houses cannot both be taken, so the answer is the better of the line without the first house and the line without the last.
- `coin_change`: `best[t] = 1 + min(best[t - coin])`; unreachable totals keep the sentinel `amount + 1`, which becomes -1.
- `coin_change_ways`: `ways[t] += ways[t - coin]` with coins in the outer loop. After processing coins `c1..ci`, `ways[t]` counts multisets using only those coins, so every combination is built in one canonical coin order and counted once.
- `coin_change_ordered_ways` (LC 377 contrast): swap the loops. With totals outer, `ways[t]` sums over every possible last coin, so `1+2` and `2+1` are different sequences. Loop order alone decides combinations vs permutations.
- `unique_paths_with_obstacles`: one row of counts; `paths[j]` already holds the count from above, so adding `paths[j - 1]` (from the left) finishes the cell, and an obstacle resets it to 0.
- `min_path_sum`: same rolling row with `min(above, left) + cell`.
- `word_break`: `ok[i]` is true when some dictionary word ends at i and `ok[i - len(word)]` holds; only distinct word lengths are tried.

Related: [ZeroOneKnapsack](../ZeroOneKnapsack/README.md) and [UnboundedKnapsack](../UnboundedKnapsack/README.md) generalize coin change; [LIS](../LIS/README.md), [LCS](../LCS/README.md), and [Palindromes](../Palindromes/README.md) cover sequence DPs.

## Complexity

Robbers O(n) time, O(1) extra space (`rob_circular` copies slices). Coin change variants O(amount * coins) time, O(amount) space. Grids O(rows * cols) time, O(cols) space. Word break O(n * L * w) time for L distinct word lengths and slices of length up to w, O(n) space.

## Usage and assumptions

`rob(nums)` and `rob_circular(nums)` take nonnegative values and return 0 for no houses. `coin_change(coins, amount)` returns the fewest coins or -1; `coin_change_ways` and `coin_change_ordered_ways` count multisets and sequences (both 1 for amount 0); coins are positive with unlimited supply. `unique_paths_with_obstacles(grid)` treats cells equal to 1 as blocked; `min_path_sum(grid)` needs a nonempty grid; both move only right or down. `word_break(text, words)` allows reusing words. C++ `rob`, `robCircular`, `coinChange`, `coinChangeWays`, `coinChangeOrderedWays`, `uniquePathsWithObstacles`, `minPathSum`, and `wordBreak` mirror them, returning `long long` where counts or sums can grow.

```python
from ClassicDP.ClassicDP import (
    coin_change,
    coin_change_ordered_ways,
    coin_change_ways,
    rob_circular,
    word_break,
)

rob_circular([2, 3, 2]) == 3
coin_change([1, 2, 5], 11) == 3
coin_change_ways([1, 2, 5], 5) == 4
coin_change_ordered_ways([1, 2, 3], 4) == 7
word_break("leetcode", ["leet", "code"])
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

New snippet.

## LeetCode problems

- [198. House Robber](https://leetcode.com/problems/house-robber/)
- [213. House Robber II](https://leetcode.com/problems/house-robber-ii/)
- [322. Coin Change](https://leetcode.com/problems/coin-change/)
- [518. Coin Change II](https://leetcode.com/problems/coin-change-ii/) — coins outer loop
- [377. Combination Sum IV](https://leetcode.com/problems/combination-sum-iv/) — totals outer loop
- [63. Unique Paths II](https://leetcode.com/problems/unique-paths-ii/)
- [64. Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/)
- [139. Word Break](https://leetcode.com/problems/word-break/)

## Tests

[`test_ClassicDP.py`](test_ClassicDP.py) checks the Python implementation; [`test_ClassicDP.cpp`](test_ClassicDP.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s ClassicDP -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
