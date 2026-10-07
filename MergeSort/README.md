# Merge sort

Sort an array by recursively sorting halves and merging their ordered elements.

## My solution

Copy the current interval to one reusable auxiliary buffer, then merge from the two halves. Prefer the left value on equality, preserving stability.

## Complexity

O(n log n) time and O(n) auxiliary space.

## Usage and assumptions

`merge_sort(values)` returns a sorted copy without changing the input. C++ `MergeSort(values)` owns a copy; call `sort()` then `getSortedArray()`. The original inclusive `mergeSort(left, right)` method remains available.

```python
from MergeSort.MergeSort import merge_sort

merge_sort([3, 1, 2, 1]) == [1, 1, 2, 3]
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

C++ now exposes a whole-array sort method and a getter for the sorted result.

## Tests

[`test_MergeSort.py`](test_MergeSort.py) checks the Python implementation; [`test_MergeSort.cpp`](test_MergeSort.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s MergeSort -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
