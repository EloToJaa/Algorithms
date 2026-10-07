# Sieve and smallest prime factors

Precompute primes and the smallest prime factor of every integer up to an inclusive limit.

## My solution

A linear sieve visits composites through their smallest prime factor, marking each composite once. Factorization repeatedly divides by the stored smallest prime factor.

## Complexity

O(n) preprocessing time and space; O(log x) worst-case factorization time and O(log x) output space.

## Usage and assumptions

`Sieve(limit)` exposes `primes` and `spf`. The limit is a nonnegative integer; `spf[0]` and `spf[1]` (when present) are zero. `factorize(x)` returns ascending `(prime, exponent)` pairs for `1 <= x <= limit`; factorizing 1 returns an empty list. Invalid limits or factorization arguments raise exceptions. C++ uses integer limits below `INT_MAX` and `std::vector<std::pair<int, int>>` output.

```python
from Sieve.Sieve import Sieve

sieve = Sieve(100)
assert sieve.primes[:4] == [2, 3, 5, 7]
assert sieve.spf[91] == 7
assert sieve.factorize(72) == [(2, 3), (3, 2)]
```

Run the example from the repository root. C++ implementations are reusable C++17 snippets with dynamic storage and no demo `main`; include the file in one translation unit.

## Tests

Prime lists, smallest factors, and factorizations are checked against trial division through 1,000. Regressions cover limits 0 and 1, prime powers, factorizing 1, and invalid inputs. [`test_Sieve.py`](test_Sieve.py) and [`test_Sieve.cpp`](test_Sieve.cpp) run with:

```sh
python3 -m unittest discover -s Sieve -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
