# Fenwick tree

Maintain prefix sums of an array under point updates with a tiny, cache-friendly array.

## My solution

- Internally one-based: `tree[i]` stores the sum of the `i & -i` values ending at position `i`, i.e. the range `(i - (i & -i), i]`.
- `i & -i` isolates the lowest set bit (two's complement flips every bit above it). It is the length of the block owned by `i`.
- Prefix sum walks down with `i -= i & -i`: each step strips the lowest bit, so it visits at most log n disjoint blocks that tile `[1, i]`.
- Point add walks up with `i += i & -i`: each step reaches the next block that also covers position `i`.
- O(n) build: copy the values, then add each `tree[i]` into its parent `i + (i & -i)` once, in increasing order.
- `lower_bound` uses binary lifting instead of binary search over `prefix_sum`: try steps of decreasing powers of two, and jump whenever the block sum is still below the target. That is O(log n) instead of O(log^2 n) and only valid for nonnegative values.
- `count_smaller_after_self` compresses values to ranks, scans from the right, and asks how many already-seen ranks are smaller.
- Compared with [`TreePointSegment`](../TreePointSegment/README.md) and [`TreeSegmentSegment`](../TreeSegmentSegment/README.md): a segment tree handles any associative operation (max, min, lazy range updates); a Fenwick tree needs an invertible operation (sums, xor) for range queries but uses n + 1 cells and a few lines of code.

## Complexity

O(n) build, O(log n) per `add`, `prefix_sum`, `range_sum`, and `lower_bound`, and O(n) space. `count_smaller_after_self` is O(n log n).

## Usage and assumptions

`Fenwick(values)` uses zero-based positions: `add(index, delta)`, `prefix_sum(count)` sums the first `count` values, `range_sum(left, right)` sums the half-open range `[left, right)`, and `lower_bound(target)` returns the smallest count whose prefix sum reaches `target` (`0` for nonpositive targets, `n + 1` if none). `lower_bound` requires nonnegative values; the element holding the k-th unit (k >= 1) is `lower_bound(k) - 1`. Start empty with `Fenwick([0] * n)`. C++ `Fenwick(n)` / `Fenwick(values)` with `add`, `prefixSum`, `rangeSum`, `lowerBound` uses `long long`; `countSmallerAfterSelf` returns `std::vector<int>`.

```python
from Fenwick.Fenwick import Fenwick, count_smaller_after_self

tree = Fenwick([1, 0, 2, 3])
tree.add(1, 4)
tree.range_sum(1, 3) == 6
tree.lower_bound(6) == 3
count_smaller_after_self([5, 2, 6, 1]) == [2, 1, 1, 0]
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

New snippet.

## LeetCode problems

- [307. Range Sum Query - Mutable](https://leetcode.com/problems/range-sum-query-mutable/)
- [315. Count of Smaller Numbers After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/) — `count_smaller_after_self`
- [493. Reverse Pairs](https://leetcode.com/problems/reverse-pairs/) — compress values and 2 * values
- [327. Count of Range Sum](https://leetcode.com/problems/count-of-range-sum/) — Fenwick over compressed prefix sums
- [1649. Create Sorted Array through Instructions](https://leetcode.com/problems/create-sorted-array-through-instructions/)
- [1395. Count Number of Teams](https://leetcode.com/problems/count-number-of-teams/) — smaller-before and greater-after counts

## Tests

[`test_Fenwick.py`](test_Fenwick.py) checks the Python implementation; [`test_Fenwick.cpp`](test_Fenwick.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s Fenwick -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
