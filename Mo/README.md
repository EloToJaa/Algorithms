# Mo's algorithm for distinct counts

Answer offline range queries asking how many distinct values appear in each interval.

## My solution

Sort queries by the block of their left endpoint, then their right endpoint. Move a shared interval and maintain value frequencies and the number of nonzero frequencies.

## Complexity

O((n + q) sqrt(n) + q log q) typical time; O(n + q) space for frequencies, sorted queries, and answers.

## Usage and assumptions

`distinct_counts(values, queries)` takes zero-based inclusive ranges and returns counts in the original order. Empty values require no queries. C++ reads `n m`, n values, then m one-based inclusive queries; values must be in 0..N because ILE is an array. Python uses a dictionary and supports negative values.

```python
from Mo.Mo import distinct_counts

distinct_counts([1, 2, 1, 3], [(0, 3), (0, 2), (2, 2)]) == [3, 2, 1]
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

C++ now reads m queries (rather than n), uses a nonzero block size, and expands before shrinking the interval to keep frequencies valid.

## Tests

[`test_Mo.py`](test_Mo.py) checks the Python implementation; [`test_Mo.cpp`](test_Mo.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s Mo -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
