# Quickselect

Find the k-th smallest element, the k smallest elements, or the k most frequent values without fully sorting.

## My solution

- Same partition step as [quicksort](../QuickSort/README.md), but only continue into the side containing index k, so the expected work is n + n/2 + n/4 + ... = O(n).
- A random pivot makes the O(n^2) worst case depend on luck rather than on the input order (sorted or adversarial inputs are fine).
- Three-way (Dutch flag) partition splits the window into `< pivot`, `== pivot`, `> pivot`. If k lands in the middle block, the pivot is the answer; otherwise the equal block is dropped. With many duplicates, a two-way partition would keep recursing on equal values and degrade to O(n^2); here an all-equal array finishes in one pass.
- The loop is iterative: just shrink `[low, high)`; there is no recursion to unwind.
- After selecting index k - 1, everything left of it is no larger, so `k_smallest` returns that prefix (unordered).
- `top_k_frequent` does not need selection at all: a frequency is at most n, so bucket values by count and read buckets from high to low for O(n).
- Compared with a heap of size k (O(n log k), streaming-friendly, stable worst case), quickselect is O(n) expected but needs all data in memory and rearranges it.

## Complexity

O(n) expected time, O(n^2) worst case with vanishing probability, and O(n) space for the copy (O(1) extra in place). `top_k_frequent` is O(n) time and space.

## Usage and assumptions

`quick_select(nums, k)` returns the k-th smallest element with zero-based k and raises `IndexError` if k is out of range; `k_smallest(nums, k)` returns the k smallest in arbitrary order (empty for k <= 0, everything for k >= n); `top_k_frequent(nums, k)` returns k distinct values with the highest counts, ties broken arbitrarily. Python copies the input and never mutates the caller's list. C++ `quickSelect` and `kSmallest` take the vector by value; `selectInPlace` rearranges in place like `std::nth_element(v.begin(), v.begin() + k, v.end())`, the standard alternative. C++ `topKFrequent` works on `std::vector<int>`.

```python
from QuickSelect.QuickSelect import k_smallest, quick_select, top_k_frequent

quick_select([3, 2, 1, 5, 6, 4], 4) == 5
sorted(k_smallest([5, 1, 4, 1, 3], 3)) == [1, 1, 3]
sorted(top_k_frequent([1, 1, 1, 2, 2, 3], 2)) == [1, 2]
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

New snippet.

## LeetCode problems

- [215. Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/) — k-th largest is index n - k
- [347. Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/) — bucket sort
- [973. K Closest Points to Origin](https://leetcode.com/problems/k-closest-points-to-origin/) — `k_smallest` by squared distance
- [692. Top K Frequent Words](https://leetcode.com/problems/top-k-frequent-words/) — ordered ties, so sort or use a heap
- [462. Minimum Moves to Equal Array Elements II](https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/) — move to the median
- [324. Wiggle Sort II](https://leetcode.com/problems/wiggle-sort-ii/) — median plus three-way partition

## Tests

[`test_QuickSelect.py`](test_QuickSelect.py) checks the Python implementation; [`test_QuickSelect.cpp`](test_QuickSelect.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s QuickSelect -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
