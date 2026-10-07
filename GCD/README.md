# GCD and extended Euclid

Compute a nonnegative greatest common divisor and coefficients satisfying the Bézout identity.

## My solution

Euclid repeatedly replaces a pair by the divisor and remainder. Extended Euclid carries the same transformations into two coefficient pairs, then restores the original input signs.

## Complexity

O(log(max(|a|, |b|) + 1)) arithmetic steps and O(1) auxiliary storage in the fixed-width model. Python big-integer arithmetic has additional bit costs.

## Usage and assumptions

`gcd(a, b)` returns a nonnegative integer. Python `extended_gcd(a, b)` returns `(g, x, y)` such that `a*x + b*y == g`; C++ returns `ExtendedGCD` with fields `gcd`, `x`, and `y`. Signed and zero inputs are supported, with `gcd(0, 0) == 0`. C++ accepts signed 64-bit inputs except `LLONG_MIN`, whose absolute value does not fit; that input raises `std::out_of_range`. C++ uses GCC/Clang `__int128` for intermediate coefficients. For modulus `m > 1`, if `extended_gcd(a, m)` returns gcd 1, its x coefficient modulo m is the modular inverse.

```python
from GCD.GCD import gcd, extended_gcd

assert gcd(-30, 18) == 6
g, x, y = extended_gcd(-30, 18)
assert g == 6 and -30 * x + 18 * y == g
g, inverse, _ = extended_gcd(5, 12)
assert g == 1 and inverse % 12 == 5
```

Run the example from the repository root. C++ implementations are reusable C++17 snippets with dynamic storage and no demo `main`; include the file in one translation unit.

## Tests

Tests compare against standard-library GCD and verify the Bézout identity for signed/zero inputs and large random numbers. C++ checks 64-bit boundaries with wide reference arithmetic; Python includes 100-digit inputs. [`test_GCD.py`](test_GCD.py) and [`test_GCD.cpp`](test_GCD.cpp) run with:

```sh
python3 -m unittest discover -s GCD -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
