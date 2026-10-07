import random
import unittest
from math import gcd as reference_gcd

from GCD.GCD import extended_gcd, gcd


class TestGCD(unittest.TestCase):
    def test_bezout_and_signs(self):
        rng = random.Random(21)
        samples = [(a, b) for a in range(-15, 16) for b in range(-15, 16)]
        samples += [
            (rng.randrange(-(10**100), 10**100), rng.randrange(-(10**100), 10**100))
            for _ in range(100)
        ]
        for a, b in samples:
            expected = reference_gcd(a, b)
            result, x, y = extended_gcd(a, b)
            self.assertEqual(result, expected)
            self.assertEqual(gcd(a, b), expected)
            self.assertEqual(a * x + b * y, result)


if __name__ == "__main__":
    unittest.main()
