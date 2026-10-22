# Monotonic stack

Nearest greater/smaller neighbours for every index, the largest rectangle in a histogram, and the sum of subarray minimums.

## My solution

Scan left to right keeping a stack of indices whose values are monotone. Before pushing `i`, pop every index that `values[i]` "beats"; at that moment `i` is the popped index's next greater/smaller element, and whatever remains below on the stack is its previous one. Each index is pushed once and popped at most once, so a full scan is O(n) even though a single step may pop many entries.

Picking the comparison: pop with `<` to find the next *strictly* greater (equal values wait on the stack), pop with `>=` to keep the stack strictly increasing, so the element below is the previous *strictly* smaller. Flip strict/non-strict to get the "or equal" variants.

- `next_greater`: stack of non-increasing values; popping on `values[top] < value` assigns the answer to each popped index. Unpopped indices keep -1.
- `previous_smaller`: stack of strictly increasing values; after popping everything `>= value`, the top is the answer for `i`.
- `largest_rectangle`: when bar `j` is popped by a lower bar at `i`, `i` is its next smaller and the new top its previous smaller, so `j` is the minimum of the open interval `(left, i)` with width `i - left - 1`. A sentinel height -1 after the end flushes the stack.
- `sum_subarray_mins`: each subarray's minimum is charged to one index `j`, contributing `values[j] * (j - left) * (right - j)` with `left` the previous strictly smaller and `right` the next smaller-or-equal. Mixing strict and non-strict sides means that among equal minimums only the rightmost owns the subarray, so duplicates are counted exactly once; using strict (or non-strict) on both sides would double count (or miss) them. Popping on `>=` provides both boundaries in one pass.

For the maximum of a sliding window, see [MonoQueue](../MonoQueue/README.md).

## Complexity

O(n) time and O(n) space for every function.

## Usage and assumptions

`next_greater(values)` and `previous_smaller(values)` return zero-based indices with -1 for none. `largest_rectangle(heights)` expects non-negative heights and returns 0 for an empty histogram. `sum_subarray_mins(values, mod=MOD)` returns the sum modulo `MOD = 10**9 + 7` (also for negative values). C++ `nextGreater`, `previousSmaller`, `largestRectangle`, and `sumSubarrayMins` take `std::vector<long long>`.

```python
from MonoStack.MonoStack import (
    largest_rectangle,
    next_greater,
    previous_smaller,
    sum_subarray_mins,
)

next_greater([2, 1, 2, 4, 3]) == [3, 2, 3, -1, -1]
previous_smaller([3, 1, 2, 2, 0]) == [-1, -1, 1, 1, -1]
largest_rectangle([2, 1, 5, 6, 2, 3]) == 10
sum_subarray_mins([3, 1, 2, 4]) == 17
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

New snippet.

## LeetCode problems

- [496. Next Greater Element I](https://leetcode.com/problems/next-greater-element-i/)
- [503. Next Greater Element II](https://leetcode.com/problems/next-greater-element-ii/) — scan the array twice for circularity
- [739. Daily Temperatures](https://leetcode.com/problems/daily-temperatures/) — distance to the next greater
- [84. Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)
- [85. Maximal Rectangle](https://leetcode.com/problems/maximal-rectangle/) — histogram per row
- [907. Sum of Subarray Minimums](https://leetcode.com/problems/sum-of-subarray-minimums/)
- [2104. Sum of Subarray Ranges](https://leetcode.com/problems/sum-of-subarray-ranges/) — sum of maximums minus sum of minimums
- [402. Remove K Digits](https://leetcode.com/problems/remove-k-digits/)

## Tests

[`test_MonoStack.py`](test_MonoStack.py) checks the Python implementation; [`test_MonoStack.cpp`](test_MonoStack.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s MonoStack -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
