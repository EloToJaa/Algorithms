# Binary search on a predicate

Find the boundary of a monotone true/false predicate over an integer interval.

## My solution

Repeatedly inspect the midpoint and discard the half that cannot contain the requested boundary. First-true expects false...true; last-true expects true...false.

## Complexity

O(log interval_length) predicate evaluations and O(1) space.

## Usage and assumptions

`search_first(left, right, check)` and `search_last(left, right, check)` use inclusive bounds. If no value is true, return `right + 1` and `left - 1`, respectively. C++ accepts a callable as the third argument; its two-argument overloads use the editable `check` placeholder. C++ bounds and result sentinel must fit in `int`.

```python
from BinSearch.BinSearch import search_first, search_last

search_first(0, 9, lambda x: x >= 4) == 4
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

C++ now accepts callable predicates, uses overflow-safe midpoint arithmetic, and explicitly handles missing boundaries.

## LeetCode problems

- [278. First Bad Version](https://leetcode.com/problems/first-bad-version/)
- [875. Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/)
- [1011. Capacity To Ship Packages Within D Days](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/)
- [410. Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/)

## Tests

[`test_BinSearch.py`](test_BinSearch.py) checks the Python implementation; [`test_BinSearch.cpp`](test_BinSearch.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s BinSearch -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
