# Prefix sums

Constant-time range sums in 1D and 2D, counting subarrays with a given sum, and batching range additions with a difference array.

## My solution

- `prefix_sums`: `prefix[i]` is the sum of the first `i` values, with `prefix[0] = 0`, so the half-open range `[left, right)` sums to `prefix[right] - prefix[left]` (`range_sum`) with no special case for `left = 0`.
- `PrefixSum2D`: `table[i][j]` sums the top-left `i x j` block, built by inclusion-exclusion: `value + up + left - upLeft`. `sum_region` answers an inclusive rectangle with the same four corners: whole block minus the strip above minus the strip to the left plus the doubly removed corner.
- `count_subarrays_with_sum`: a subarray `(j, i]` sums to `k` exactly when `prefix[i] - prefix[j] == k`, so while scanning keep a counter of earlier prefix values and add `seen[prefix - k]`. Seeding `seen[0] = 1` counts subarrays starting at index 0. Works with negative values, where a sliding window would not.
- `apply_range_additions`: the difference array is the inverse of prefix sums. Adding `delta` to inclusive `[left, right]` becomes `diff[left] += delta` and `diff[right + 1] -= delta`; one prefix-sum pass at the end materializes all updates.

## Complexity

`prefix_sums` and building `PrefixSum2D` are O(n) and O(rows * columns) time and space; `range_sum` and `sum_region` are O(1). `count_subarrays_with_sum` is O(n) expected time and O(n) space. `apply_range_additions` is O(size + updates) time and O(size) space.

## Usage and assumptions

Conventions: `range_sum(prefix, left, right)` is half-open `[left, right)`; `PrefixSum2D.sum_region(row1, col1, row2, col2)` and the `(left, right, delta)` updates of `apply_range_additions(size, updates)` are inclusive. `PrefixSum2D` expects a rectangular matrix. `count_subarrays_with_sum(values, k)` counts nonempty subarrays. C++ `prefixSums`, `rangeSum`, `PrefixSum2D::sumRegion`, `countSubarraysWithSum`, and `applyRangeAdditions` (updates as `std::tuple<int, int, long long>`) use `long long`.

```python
from PrefixSum.PrefixSum import (
    PrefixSum2D,
    apply_range_additions,
    count_subarrays_with_sum,
    prefix_sums,
    range_sum,
)

range_sum(prefix_sums([-2, 0, 3, -5, 2, -1]), 0, 3) == 1
PrefixSum2D([[3, 0, 1], [5, 6, 3]]).sum_region(0, 1, 1, 2) == 10
count_subarrays_with_sum([1, 1, 1], 2) == 2
apply_range_additions(5, [(1, 3, 2), (2, 4, 3), (0, 2, -2)]) == [-2, 0, 3, 5, 3]
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

New snippet.

## LeetCode problems

- [303. Range Sum Query - Immutable](https://leetcode.com/problems/range-sum-query-immutable/)
- [304. Range Sum Query 2D - Immutable](https://leetcode.com/problems/range-sum-query-2d-immutable/)
- [560. Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/)
- [974. Subarray Sums Divisible by K](https://leetcode.com/problems/subarray-sums-divisible-by-k/) — count prefix sums modulo k
- [525. Contiguous Array](https://leetcode.com/problems/contiguous-array/) — map 0 to -1 and store the first index of each prefix
- [370. Range Addition](https://leetcode.com/problems/range-addition/)
- [1094. Car Pooling](https://leetcode.com/problems/car-pooling/) — trips are half-open, so use `to - 1`
- [1109. Corporate Flight Bookings](https://leetcode.com/problems/corporate-flight-bookings/) — one-based inclusive ranges

## Tests

[`test_PrefixSum.py`](test_PrefixSum.py) checks the Python implementation; [`test_PrefixSum.cpp`](test_PrefixSum.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s PrefixSum -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
