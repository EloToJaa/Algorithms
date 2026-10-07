# Quicksort

Sort an array by partitioning values around a pivot and sorting the resulting intervals.

## My solution

Move the middle pivot to the right endpoint, use Lomuto partitioning, and process the remaining intervals. Python uses an explicit stack; C++ recurses only on the smaller side and iterates on the larger side.

## Complexity

O(n log n) typical time, O(n^2) worst-case time (including equal-value arrays), and O(log n) stack space.

## Usage and assumptions

`quick_sort(values)` returns a sorted copy. C++ calls `QuickSort(values).sort()` and reads `getSortedArray()`. This sort is not stable.

```python
from QuickSort.QuickSort import quick_sort

quick_sort([3, 1, 2]) == [1, 2, 3]
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

C++ now moves the selected pivot into the slot used by partitioning, fixing incorrect output, and bounds recursive stack depth.

## Tests

[`test_QuickSort.py`](test_QuickSort.py) checks the Python implementation; [`test_QuickSort.cpp`](test_QuickSort.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s QuickSort -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
