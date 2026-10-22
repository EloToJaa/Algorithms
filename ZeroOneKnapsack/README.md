# Zero-one knapsack

Choose each item at most once to maximize value without exceeding a capacity.

## My solution

Keep one DP entry per capacity and update capacities in descending order for every item; this prevents reusing that item. Ascending order gives the [unbounded knapsack](../UnboundedKnapsack/README.md). Empty selection is allowed.

## Complexity

O(nW) time and O(W) space.

## Usage and assumptions

`zero_one_knapsack(items, capacity)` takes `(weight, value)` pairs and returns the maximum value. Capacity and weights must be nonnegative integers; zero-weight items are allowed. C++ reads `n W`, then n lines of `weight value`, and prints the answer. C++ requires n < N and W <= MAXW.

```python
from ZeroOneKnapsack.ZeroOneKnapsack import zero_one_knapsack

zero_one_knapsack([(2, 4), (3, 5), (4, 8)], 5) == 9
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

C++ now reads the item weights/values and prints the result with 64-bit values; previously it only read n and W.

## LeetCode problems

- [416. Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/)
- [494. Target Sum](https://leetcode.com/problems/target-sum/)
- [474. Ones and Zeroes](https://leetcode.com/problems/ones-and-zeroes/) — two-dimensional capacity
- [1049. Last Stone Weight II](https://leetcode.com/problems/last-stone-weight-ii/)

## Tests

[`test_ZeroOneKnapsack.py`](test_ZeroOneKnapsack.py) checks the Python implementation; [`test_ZeroOneKnapsack.cpp`](test_ZeroOneKnapsack.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s ZeroOneKnapsack -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
