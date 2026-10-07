# Manacher's palindrome radii

Find the maximum odd and even palindrome radii at every center in linear time.

## My solution

Reuse the mirrored radius inside the current rightmost palindrome, then expand only beyond the known boundary. Process odd and even centers separately.

## Complexity

O(n) time and O(n) output space.

## Usage and assumptions

`manacher(text)` returns `(odd, even)`. `odd[i]` includes its center, so length is `2*odd[i]-1`; `even[i]` centers just before i, so length is `2*even[i]`. C++ `Manacher(s)` stores these at `Odd[i+1]` and `Even[i+1]`.

```python
from Manacher.Manacher import manacher

manacher("abba") == ([1, 1, 1, 1], [0, 0, 2, 0])
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

The original C++ recurrence was retained and checked against direct center expansion.

## Tests

[`test_Manacher.py`](test_Manacher.py) checks the Python implementation; [`test_Manacher.cpp`](test_Manacher.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s Manacher -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
