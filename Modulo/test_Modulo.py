import random
import unittest

from Modulo.Modulo import Modulo


class TestModulo(unittest.TestCase):
    def test_against_integer_arithmetic(self):
        rng = random.Random(10)
        for modulus in (2, 7, 1_000_000_007):
            arithmetic = Modulo(modulus)
            for _ in range(50):
                a, b = rng.randrange(-10000, 10000), rng.randrange(1, modulus)
                exponent = rng.randrange(40)
                self.assertEqual(arithmetic.add(a, b), (a + b) % modulus)
                self.assertEqual(arithmetic.subtract(a, b), (a - b) % modulus)
                self.assertEqual(arithmetic.multiply(a, b), a * b % modulus)
                self.assertEqual(
                    arithmetic.power(a, exponent), pow(a, exponent, modulus)
                )
                self.assertEqual(
                    arithmetic.multiply(arithmetic.divide(a, b), b), a % modulus
                )


if __name__ == "__main__":
    unittest.main()
