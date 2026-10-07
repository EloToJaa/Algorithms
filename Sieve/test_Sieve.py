import unittest

from Sieve.Sieve import Sieve


class TestSieve(unittest.TestCase):
    def test_trial_division(self):
        for limit in (0, 1, 2, 20, 1000):
            sieve = Sieve(limit)
            expected_primes = []
            for value in range(2, limit + 1):
                smallest = next((d for d in range(2, value + 1) if value % d == 0))
                self.assertEqual(sieve.spf[value], smallest)
                if smallest == value:
                    expected_primes.append(value)
                remainder, expected = value, []
                for divisor in range(2, value + 1):
                    exponent = 0
                    while remainder % divisor == 0:
                        remainder //= divisor
                        exponent += 1
                    if exponent:
                        expected.append((divisor, exponent))
                self.assertEqual(sieve.factorize(value), expected)
            self.assertEqual(sieve.primes, expected_primes)
        self.assertEqual(Sieve(1).factorize(1), [])

    def test_invalid_inputs(self):
        with self.assertRaises(ValueError):
            Sieve(-1)
        for value in (-1, 0, 11):
            with self.assertRaises(ValueError):
                Sieve(10).factorize(value)


if __name__ == "__main__":
    unittest.main()
