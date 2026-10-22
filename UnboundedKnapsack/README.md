# Unbounded knapsack

Choose items any number of times to maximize value without exceeding a capacity.

## My solution

Keep one DP entry per capacity and update capacities in ascending order for every item; `best[available - weight]` may already include the same item, which allows reuse. Empty selection is allowed.

## Complexity

O(nW) time and O(W) space.

## Usage and assumptions

`unbounded_knapsack(items, capacity)` takes `(weight, value)` pairs and returns the maximum value. Capacity must be a nonnegative integer and weights positive integers; values may be negative. C++ `unboundedKnapsack(items, capacity)` takes `vector<pair<int, long long>>` and returns a 64-bit value.

```python
from UnboundedKnapsack.UnboundedKnapsack import unbounded_knapsack

unbounded_knapsack([(3, 4), (4, 5), (2, 3)], 7) == 10
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

New snippet; it differs from [ZeroOneKnapsack](../ZeroOneKnapsack/README.md) only in the capacity loop direction.

## LeetCode problems

- [322. Coin Change](https://leetcode.com/problems/coin-change/) — minimize count instead of maximizing value
- [518. Coin Change II](https://leetcode.com/problems/coin-change-ii/) — count combinations
- [279. Perfect Squares](https://leetcode.com/problems/perfect-squares/)
- [1449. Form Largest Integer With Digits That Add up to Target](https://leetcode.com/problems/form-largest-integer-with-digits-that-add-up-to-target/)

## Tests

[`test_UnboundedKnapsack.py`](test_UnboundedKnapsack.py) checks the Python implementation; [`test_UnboundedKnapsack.cpp`](test_UnboundedKnapsack.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s UnboundedKnapsack -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
