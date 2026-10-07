# Unsigned big integers

Represent nonnegative integers larger than native C++ integer types and perform arithmetic on their digits.

## My solution

Store little-endian limbs in base 10^9. Addition/subtraction propagate carry/borrow; multiplication combines shifted limb products; integer division scans from most significant to least significant limb.

## Complexity

O(L) addition/subtraction/comparison/integer division; O(L*M) multiplication; O(L+M) output space. L and M count base-10^9 limbs.

## Usage and assumptions

`BigNumber(decimal_text_or_int)` supports +, -, *, //positive_int, %positive_int, equality, ordering, and string conversion. Subtraction requires left >= right and all inputs/multipliers must be nonnegative. Python grows dynamically and deliberately uses limb arithmetic rather than delegating to built-in big integers. C++ `liczba` has LEN=1000 limbs; all inputs, outputs, and intermediate shifted products must fit. C++ integer divisors/multipliers must also fit in int.

```python
from BigNumbers.BigNumbers import BigNumber

str(BigNumber("999999999") + BigNumber(1)) == "1000000000"
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

C++ bounds decimal input reads, trims leading zero limbs and zero multiplication results, rejects negative subtraction/multipliers and nonpositive divisors, checks arithmetic capacity before writing extra limbs, and uses consistent stdio output.

## Tests

[`test_BigNumbers.py`](test_BigNumbers.py) checks the Python implementation; [`test_BigNumbers.cpp`](test_BigNumbers.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s BigNumbers -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
