# Sparse table for static range minimum

Answer range-minimum queries over an immutable array in constant time.

## My solution

Precompute minima for all valid power-of-two blocks. Answer each query using two overlapping blocks of the largest power of two fitting in the interval. Overlap is safe because minimum is idempotent; this technique cannot be used unchanged for sums.

## Complexity

O(n log n) preprocessing time/space and O(1) per query.

## Usage and assumptions

`SparseTable(values).query(left, right)` returns the minimum in the zero-based inclusive interval `[left, right]`. Construction copies the input; later changes to the original array do not affect queries. Empty construction is allowed, but no query is valid on an empty table. Invalid ranges raise `ValueError` in Python and `std::out_of_range` in C++. C++ stores `long long` values. This implementation supports minimum queries; it does not provide updates.

```python
from SparseTable.SparseTable import SparseTable

table = SparseTable([4, -2, 7, 1, -5])
assert table.query(1, 3) == -2
assert table.query(0, 4) == -5
```

Run the example from the repository root. C++ implementations are reusable C++17 snippets with dynamic storage and no demo `main`; include the file in one translation unit.

## Tests

Every interval in random arrays is compared with a direct minimum. Regressions cover singletons, non-power-of-two sizes, negative values, input copying, invalid ranges, and extreme integers. [`test_SparseTable.py`](test_SparseTable.py) and [`test_SparseTable.cpp`](test_SparseTable.cpp) run with:

```sh
python3 -m unittest discover -s SparseTable -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
