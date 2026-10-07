# Modular arithmetic

Perform addition, subtraction, multiplication, exponentiation, and prime-modulus division.

## My solution

Normalize residues, use binary exponentiation, and compute a divisor inverse by Fermat's little theorem: b^(p-2) modulo a prime p.

## Complexity

O(1) arithmetic (fixed-width model), O(log exponent) power, O(log modulus) division; Python uses O(1) auxiliary space and C++ power uses O(log exponent) recursion.

## Usage and assumptions

`Modulo(prime)` provides `add`, `subtract`, `multiply`, `power`, and `divide`. Modulus must be prime and >=2 for division; divisor must be nonzero modulo the prime. Exponents are nonnegative. C++ uses `ModuloStruct` and capitalized method names. C++ products must fit in signed 64-bit integers; the default modulus 1,000,000,007 is safe.

```python
from Modulo.Modulo import Modulo

Modulo(7).divide(6, 3) == 2
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

C++ now normalizes negative operands, reduces the base before odd-power multiplication, and rejects division by zero modulo the prime.

## Tests

[`test_Modulo.py`](test_Modulo.py) checks the Python implementation; [`test_Modulo.cpp`](test_Modulo.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s Modulo -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
