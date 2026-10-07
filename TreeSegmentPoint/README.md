# Range addition / point lookup

Add a value to every element of an interval and look up a single element.

## My solution

Store initial values only at leaves and range-add tags on canonical interval nodes. A point query sums its leaf and every tag on the path to the root. No lazy push is needed for point lookups.

## Complexity

O(n) build time and space; O(log n) per update or query.

## Usage and assumptions

Python `RangeAddPoint(values)` uses zero-based positions and inclusive range bounds. Operate only on valid positions/ranges in a nonempty array. Python integers are unbounded; C++ values, additions, and sums must fit in signed 64-bit integers. C++ retains the original fixed capacity of N=300000 array elements.

```python
from TreeSegmentPoint.TreeSegmentPoint import RangeAddPoint

tree = RangeAddPoint([1, 2, 3])
tree.update(0, 1, 5)
tree.update(1, 2, -2)
assert [tree.query(i) for i in range(3)] == [6, 5, 1]
```

Run this example from the repository root.

## C++ review

C++ `build(n)` reads A[1..n]; `update(l, r, value)` adds value; `query(position)` returns the resulting point value. The original mixed assignment, increment, and maximum operations were replaced with consistent range addition and path summation. Rebuild clears old tags.

## Tests

[`test_TreeSegmentPoint.py`](test_TreeSegmentPoint.py) and [`test_TreeSegmentPoint.cpp`](test_TreeSegmentPoint.cpp) compare randomized operations with a plain array, including negative values, overlapping updates, one-element ranges, and non-power-of-two sizes. From the repository root:

```sh
python3 -m unittest discover -s TreeSegmentPoint -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
