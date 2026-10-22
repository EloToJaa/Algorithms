# Bit tricks

Constant-size bit identities plus a few classic XOR, table, and submask patterns.

## My solution

- `popcount`: `x & (x - 1)` clears the lowest set bit, so loop until zero; the step count is the popcount (Kernighan).
- `lowest_bit`: in two's complement `-x = ~x + 1` flips everything above the lowest set bit, so `x & -x` isolates it.
- `clear_lowest_bit` / `is_power_of_two`: a power of two has exactly one set bit, so clearing it leaves 0.
- `single_number`: XOR is associative, commutative, and `v ^ v = 0`, so paired values cancel and the odd one out survives.
- `counting_bits`: `i >> 1` drops the last bit and is already computed, giving `bits[i] = bits[i >> 1] + (i & 1)`.
- `submasks`: `(sub - 1) & mask` borrows from the lowest set bit of `sub` and keeps only mask bits, which is the next smaller submask; stop after yielding 0. Over all masks this enumerates 3^n pairs.
- `add32`: `a ^ b` is the sum without carries and `(a & b) << 1` the carries; repeat until no carry. Python ints are unbounded, so keep 32 bits with a mask and map values ≥ 2^31 back to negatives; C++ works on `uint32_t` so wrapping is defined.

Cheat sheet:

| Identity | Meaning |
| --- | --- |
| `x & -x` | lowest set bit |
| `x & (x - 1)` | clear lowest set bit |
| `x \| (x + 1)` | set lowest clear bit |
| `x ^ (x >> 1)` | Gray code of x |
| `x >> i & 1` | bit i |
| `x \| 1 << i`, `x & ~(1 << i)`, `x ^ 1 << i` | set, clear, toggle bit i |
| `(1 << n) - 1` | n low ones (full mask) |
| `(a & b) == a` | a is a submask of b |
| `a ^ b ^ b` | equals a: XOR is its own inverse |
| `a + b == (a ^ b) + 2 * (a & b)` | sum splits into carry-free part and carries |

## Complexity

`popcount` O(set bits); `lowest_bit`, `clear_lowest_bit`, `is_power_of_two` O(1); `single_number` O(n); `counting_bits` O(n) time and space; `submasks` O(2^popcount(mask)); `add32` O(32).

## Usage and assumptions

`popcount`, `lowest_bit`, `clear_lowest_bit`, and `submasks` expect nonnegative inputs; `submasks(mask)` yields in decreasing order and includes 0. `single_number(nums)` assumes exactly one value appears an odd number of times. `add32(a, b)` returns the signed 32-bit wrapped sum. C++ equivalents are `popcount`, `lowestBit`, `clearLowestBit` (unsigned 64-bit), `isPowerOfTwo`, `singleNumber`, `countingBits`, `submasks` (returns a `std::vector<unsigned>`), and `add32`.

```python
from BitTricks.BitTricks import add32, counting_bits, single_number, submasks

single_number([4, 1, 2, 1, 2]) == 4
counting_bits(5) == [0, 1, 1, 2, 1, 2]
list(submasks(0b101)) == [5, 4, 1, 0]
add32(-1, 1) == 0
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

New snippet.

## LeetCode problems

- [136. Single Number](https://leetcode.com/problems/single-number/)
- [338. Counting Bits](https://leetcode.com/problems/counting-bits/)
- [371. Sum of Two Integers](https://leetcode.com/problems/sum-of-two-integers/)
- [191. Number of 1 Bits](https://leetcode.com/problems/number-of-1-bits/)
- [231. Power of Two](https://leetcode.com/problems/power-of-two/)
- [260. Single Number III](https://leetcode.com/problems/single-number-iii/) — split by the lowest set bit of the total XOR
- [78. Subsets](https://leetcode.com/problems/subsets/) — enumerate submasks of the full mask
- [268. Missing Number](https://leetcode.com/problems/missing-number/) — XOR indices with values

## Tests

[`test_BitTricks.py`](test_BitTricks.py) checks the Python implementation; [`test_BitTricks.cpp`](test_BitTricks.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s BitTricks -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
