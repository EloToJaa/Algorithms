# Double polynomial hashing

Compare substring fingerprints in constant time after a linear prefix build.

## My solution

Build prefix polynomials and powers for bases 29 and 31 modulo 1,000,000,007. Remove a prefix using H[r] - H[l]*base^(r-l), giving a position-independent hash.

## Complexity

O(n) preprocessing time/space and O(1) substring queries.

## Usage and assumptions

`Hash(text).get_hash(left, right)` uses half-open zero-based bounds, defaulting to the whole string. C++ `Hash.Init(text, maxSize)` and `GetHash(l, r)` use one-based inclusive bounds; maxSize is clamped to at least text length. Both map lowercase a..z to 1..26. Hash equality is probabilistic: verify actual strings when collisions are unacceptable.

```python
from Hashing.Hashing import Hash

Hash("abacaba").get_hash(0, 3) == Hash("aba").get_hash()
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

C++ substring extraction now subtracts the correctly weighted prefix. Reinitialization clears old state, and powers cannot be undersized.

## Tests

[`test_Hashing.py`](test_Hashing.py) checks the Python implementation; [`test_Hashing.cpp`](test_Hashing.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s Hashing -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
