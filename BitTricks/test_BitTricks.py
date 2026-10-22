import random
import unittest

from BitTricks.BitTricks import (
    add32,
    clear_lowest_bit,
    counting_bits,
    is_power_of_two,
    lowest_bit,
    popcount,
    single_number,
    submasks,
)


def wrap32(value: int) -> int:
    value &= 0xFFFFFFFF
    return value - (1 << 32) if value >= 1 << 31 else value


class TestBitTricks(unittest.TestCase):
    def test_against_brute_force(self):
        rng = random.Random(21)
        for _ in range(500):
            x = rng.randrange(1 << rng.randrange(1, 64))
            self.assertEqual(popcount(x), bin(x).count("1"))
            low = next((1 << i for i in range(64) if x >> i & 1), 0)
            self.assertEqual(lowest_bit(x), low)
            self.assertEqual(clear_lowest_bit(x), x - low)
            self.assertEqual(is_power_of_two(x), bin(x).count("1") == 1)

            a = rng.randrange(-(1 << 31), 1 << 31)
            b = rng.randrange(-(1 << 31), 1 << 31)
            self.assertEqual(add32(a, b), wrap32(a + b))

            mask = rng.randrange(1 << 10)
            expected = [s for s in range(mask, -1, -1) if s & mask == s]
            self.assertEqual(list(submasks(mask)), expected)

            pairs = [rng.randrange(-50, 50) for _ in range(rng.randrange(6))]
            lone = rng.randrange(-50, 50)
            nums = pairs + pairs + [lone]
            rng.shuffle(nums)
            self.assertEqual(single_number(nums), lone)

        self.assertEqual(counting_bits(300), [bin(i).count("1") for i in range(301)])

    def test_examples(self):
        self.assertEqual(single_number([4, 1, 2, 1, 2]), 4)
        self.assertEqual(counting_bits(5), [0, 1, 1, 2, 1, 2])
        self.assertEqual(counting_bits(0), [0])
        self.assertEqual(add32(1, 2), 3)
        self.assertEqual(add32(-1, 1), 0)
        self.assertEqual(add32(2**31 - 1, 1), -(2**31))
        self.assertEqual(list(submasks(0b101)), [5, 4, 1, 0])
        self.assertEqual(list(submasks(0)), [0])
        self.assertFalse(is_power_of_two(0))
        self.assertEqual(lowest_bit(12), 4)


if __name__ == "__main__":
    unittest.main()
