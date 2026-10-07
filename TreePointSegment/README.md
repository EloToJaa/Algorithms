# Point assignment / range maximum

Assign a value at a single array position and find the maximum over an interval.

## My solution

Store values at leaves of a power-of-two segment tree and maxima at internal nodes. A point assignment recomputes ancestors; a query collects disjoint nodes covering its interval. Padding uses negative infinity, so all-negative arrays work.

## Complexity

O(n) build time and space; O(log n) per update or query.

## Usage and assumptions

Python `PointRangeMax(values)` uses zero-based positions and inclusive range bounds. Operate only on valid positions/ranges in a nonempty array. Python integers are unbounded; C++ values, additions, and sums must fit in signed 64-bit integers. C++ retains the original fixed capacity of N=300000 array elements.

```python
from TreePointSegment.TreePointSegment import PointRangeMax

tree = PointRangeMax([-5, -2, -8])
tree.update(1, -9)
assert tree.query(0, 2) == -5
```

Run this example from the repository root.

## C++ review

C++ `build(n)` reads A[1..n]; `update(position, value)` assigns a value; `query(l, r)` returns an inclusive range maximum. C++ uses LLONG_MIN padding, resets the tree on rebuild, and accepts 64-bit updates.

## Tests

[`test_TreePointSegment.py`](test_TreePointSegment.py) and [`test_TreePointSegment.cpp`](test_TreePointSegment.cpp) compare randomized operations with a plain array, including negative values, overlapping updates, one-element ranges, and non-power-of-two sizes. From the repository root:

```sh
python3 -m unittest discover -s TreePointSegment -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
