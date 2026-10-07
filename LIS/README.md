# Longest increasing subsequence

Find the length of the longest strictly increasing subsequence, without requiring adjacent elements.

## My solution

Maintain the smallest possible tail of each subsequence length. A lower-bound search replaces the first tail at least as large as each value or extends the tails list.

## Complexity

O(n log n) time and O(n) space.

## Usage and assumptions

`lis_length(values)` returns a length, with 0 for empty input. Equal values do not extend a strictly increasing subsequence. C++ provides `LIS().lengthOfLIS(values)`.

```python
from LIS.LIS import lis_length

lis_length([10, 9, 2, 5, 3, 7, 101, 18]) == 4
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

C++ now uses standard `lower_bound`, simplifying duplicate handling and the tails invariant.

## Tests

[`test_LIS.py`](test_LIS.py) checks the Python implementation; [`test_LIS.cpp`](test_LIS.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s LIS -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
