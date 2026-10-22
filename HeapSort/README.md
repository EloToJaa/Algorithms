# Heap sort

Sort an array by building a max heap in place and repeatedly moving its root to the end.

## My solution

Use a zero-based max heap (children `2i+1`, `2i+2`). Heapify bottom-up by sifting down every internal node, then swap the root behind the shrinking heap and sift the new root down.

## Complexity

O(n log n) worst-case time, O(n) heapify, and O(1) auxiliary space beyond the copy.

## Usage and assumptions

`heap_sort(values)` returns a sorted copy without changing the input. C++ calls `HeapSort(values).sort()` and reads `getSortedArray()`. This sort is not stable.

```python
from HeapSort.HeapSort import heap_sort

heap_sort([3, 1, 2, 1]) == [1, 1, 2, 3]
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

New snippet; it follows the [QuickSort](../QuickSort/README.md) and [MergeSort](../MergeSort/README.md) interface. The one-based [Heap](../Heap/README.md) classes build by repeated insertion instead.

## LeetCode problems

- [912. Sort an Array](https://leetcode.com/problems/sort-an-array/)
- [215. Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/) — stop after k extractions
- [1985. Find the Kth Largest Integer in the Array](https://leetcode.com/problems/find-the-kth-largest-integer-in-the-array/)

## Tests

[`test_HeapSort.py`](test_HeapSort.py) checks the Python implementation; [`test_HeapSort.cpp`](test_HeapSort.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s HeapSort -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
