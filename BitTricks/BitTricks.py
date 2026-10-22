"""Bit-manipulation toolkit: popcount, lowest bit, XOR tricks, submasks, add."""

from collections.abc import Iterable, Iterator

MASK32 = 0xFFFFFFFF


def popcount(x: int) -> int:
    """Number of set bits of a nonnegative x (Kernighan: clear lowest bit)."""
    count = 0
    while x:
        x &= x - 1
        count += 1
    return count


def lowest_bit(x: int) -> int:
    """Value of the lowest set bit (x & -x); 0 for x = 0."""
    return x & -x


def clear_lowest_bit(x: int) -> int:
    return x & (x - 1)


def is_power_of_two(x: int) -> bool:
    return x > 0 and x & (x - 1) == 0


def single_number(nums: Iterable[int]) -> int:
    """XOR of all values: the element appearing an odd number of times."""
    result = 0
    for value in nums:
        result ^= value
    return result


def counting_bits(n: int) -> list[int]:
    """bits[i] is popcount(i) for 0 <= i <= n."""
    bits = [0] * (n + 1)
    for i in range(1, n + 1):
        bits[i] = bits[i >> 1] + (i & 1)
    return bits


def submasks(mask: int) -> Iterator[int]:
    """Yield every submask of a nonnegative mask in decreasing order, ending with 0."""
    sub = mask
    while True:
        yield sub
        if sub == 0:
            return
        sub = (sub - 1) & mask


def add32(a: int, b: int) -> int:
    """Signed 32-bit a + b (wrapping) without +: XOR sums, AND-shift carries."""
    a, b = a & MASK32, b & MASK32
    while b:
        a, b = a ^ b, ((a & b) << 1) & MASK32
    return a if a < 1 << 31 else a - (1 << 32)
