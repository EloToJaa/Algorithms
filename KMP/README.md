# Knuth-Morris-Pratt prefix function

Compute longest proper prefix/suffix lengths and use them for linear-time pattern matching.

## My solution

On a mismatch, follow previously computed prefix links instead of restarting the comparison. Python additionally scans a text using the pattern prefix table.

## Complexity

O(n) for the prefix table; O(text_length + pattern_length) matching time plus output. O(pattern_length) matching auxiliary space.

## Usage and assumptions

`prefix_function(text)` returns zero-based prefix lengths. `find_matches(text, pattern)` returns all zero-based starts, including overlaps. An empty pattern matches every boundary. C++ `Kmp(s)` fills `Pi[1..len(s)]`.

```python
from KMP.KMP import find_matches, prefix_function

find_matches("ababa", "aba") == [0, 2]
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

C++ explicitly resets the base prefix entries for repeated calls.

## Tests

[`test_KMP.py`](test_KMP.py) checks the Python implementation; [`test_KMP.cpp`](test_KMP.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s KMP -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
