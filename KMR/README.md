# Karp-Miller-Rosenberg ranks and suffix arrays

Assign lexicographic ranks to doubled substrings, derive a suffix array, and compare substrings without hash collisions.

## My solution

Start with character ranks, sort pairs of adjacent half-block ranks at each doubling level, and store the new ranks. Final ranks order suffixes. Kasai's scan builds adjacent suffix LCP values; binary lifting over ranks compares arbitrary-length substrings.

## Complexity

O(n log^2 n) rank construction time using comparison sorting, O(n log n) storage, O(n) LCP construction, and O(log n) substring comparison. The C++ demo prints every suffix, which can add O(n^2) output time.

## Usage and assumptions

`KMR(text)` exposes `levels`, `suffix_array`, `rank`, `lcp`, and `compare(a,b,c,d)` with half-open ranges. Comparison returns 0 (less), 1 (equal), or 2 (greater). Python uses lcp[0]=0. C++ prepends a dummy character before `kmr(s)`, `sa(s)`, and `lcp(s)`; arrays/ranges are one-based inclusive and LCP[1]=-1. C++ character ranks assume lowercase a..z.

```python
from KMR.KMR import KMR

table = KMR("banana")
assert table.suffix_array == [5, 3, 1, 0, 4, 2]
assert table.compare(1, 4, 3, 6) == 1
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

C++ substring comparison now correctly handles unequal lengths and powers of two, empty construction avoids log2(0), and LCP uses linear-time Kasai scanning.

## Tests

[`test_KMR.py`](test_KMR.py) checks the Python implementation; [`test_KMR.cpp`](test_KMR.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s KMR -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
