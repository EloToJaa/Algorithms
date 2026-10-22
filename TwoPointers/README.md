# Two pointers

Opposite-end pointers on arrays: pair with a target sum in a sorted array, unique 3Sum triplets, container with most water, and trapping rain water.

## My solution

Start with `left = 0`, `right = n - 1` and move exactly one pointer inward per step. Each move discards every pair involving the abandoned index, so the argument for correctness is always "that index can no longer be part of a better answer".

- `pair_with_sum`: in sorted order, if `a[left] + a[right] < target` then `a[left]` plus anything left of `right` is even smaller, so `left` is useless; symmetrically for `right`. O(n) instead of O(n^2).
- `three_sum`: sort, fix the smallest element `a[i]`, and run `pair_with_sum` on the suffix for `target - a[i]`. Skip equal `a[i]` and, after a hit, equal `a[left]` to keep triplets unique without a set.
- `max_area`: the area is bounded by the shorter wall. If `h[left] <= h[right]`, every other partner of `left` is closer and still capped by `h[left]`, so `left` has already achieved its best; moving the smaller side is safe and moving the taller side can never help.
- `trap`: water above `i` is `min(maxLeft(i), maxRight(i)) - h[i]`. Only the shorter side moves, so the opposite pointer always stands on a bar at least as tall as everything the moving side has passed: when `h[left] < h[right]`, `left_max <= h[right] <= maxRight(left)`. The limiting wall for `left` is therefore `left_max`, so its water is final without knowing the exact right maximum; symmetrically for `right`.

## Complexity

O(n) time and O(1) extra space for `pair_with_sum`, `max_area`, and `trap`; `three_sum` is O(n^2) time after an O(n log n) sort and O(n) space for the sorted copy.

## Usage and assumptions

`pair_with_sum(values, target)` requires sorted `values` and returns indices `(i, j)` with `i < j`, or `None`. `three_sum(values, target=0)` returns sorted unique value triplets as tuples. `max_area(heights)` returns 0 for fewer than two walls; `trap(heights)` expects non-negative heights. C++ `pairWithSum` (returns `{-1, -1}` if none), `threeSum` (returns `std::array<long long, 3>` triplets), `maxArea`, and `trap` use `long long` values.

```python
from TwoPointers.TwoPointers import max_area, pair_with_sum, three_sum, trap

pair_with_sum([2, 7, 11, 15], 9) == (0, 1)
three_sum([-1, 0, 1, 2, -1, -4]) == [(-1, -1, 2), (-1, 0, 1)]
max_area([1, 8, 6, 2, 5, 4, 8, 3, 7]) == 49
trap([0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]) == 6
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

New snippet.

## LeetCode problems

- [167. Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/) — answer is one-based
- [15. 3Sum](https://leetcode.com/problems/3sum/)
- [16. 3Sum Closest](https://leetcode.com/problems/3sum-closest/) — track the closest total instead
- [18. 4Sum](https://leetcode.com/problems/4sum/) — one more fixed outer loop
- [11. Container With Most Water](https://leetcode.com/problems/container-with-most-water/)
- [42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)
- [125. Valid Palindrome](https://leetcode.com/problems/valid-palindrome/)

## Tests

[`test_TwoPointers.py`](test_TwoPointers.py) checks the Python implementation; [`test_TwoPointers.cpp`](test_TwoPointers.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s TwoPointers -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
