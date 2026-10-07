# Range addition / range sum

Add a value over an interval and find the sum over another interval.

## My solution

Use a lazy segment tree. Each node stores a segment sum and a pending addition. A full-cover update adds value times segment length; partial operations push the pending addition to children before descending.

## Complexity

O(n) build time and space; O(log n) per update or query.

## Usage and assumptions

Python `RangeAddSum(values)` uses zero-based positions and inclusive range bounds. Operate only on valid positions/ranges in a nonempty array. Python integers are unbounded; C++ values, additions, and sums must fit in signed 64-bit integers. C++ retains the original fixed capacity of N=300000 array elements.

```python
from TreeSegmentSegment.TreeSegmentSegment import RangeAddSum

tree = RangeAddSum([1, 2, 3])
tree.update(0, 1, 5)
assert tree.query(0, 2) == 16
```

Run this example from the repository root.

## C++ review

C++ `build(n)` reads A[1..n] and establishes the power-of-two base `ntree`. Call `update(1, 1, ntree, l, r, value)` and `query(1, 1, ntree, l, r)` with one-based inclusive bounds. Build now aggregates sums rather than maxima, matching the existing lazy updates/queries, and clears all old values and tags.

## Tests

[`test_TreeSegmentSegment.py`](test_TreeSegmentSegment.py) and [`test_TreeSegmentSegment.cpp`](test_TreeSegmentSegment.cpp) compare randomized operations with a plain array, including negative values, overlapping updates, one-element ranges, and non-power-of-two sizes. From the repository root:

```sh
python3 -m unittest discover -s TreeSegmentSegment -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
