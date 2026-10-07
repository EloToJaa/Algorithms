import random
import unittest

from BigNumbers.BigNumbers import BigNumber


class TestBigNumbers(unittest.TestCase):
    def test_against_python_integers(self):
        rng = random.Random(13)
        samples = [(0, 0), (10**9 - 1, 1), (10**50, 1)]
        samples += [(rng.randrange(10**70), rng.randrange(10**40)) for _ in range(80)]
        for a, b in samples:
            x, y = BigNumber(a), BigNumber(b)
            self.assertEqual(str(x + y), str(a + b))
            self.assertEqual(str(x * y), str(a * b))
            self.assertEqual(str(x * 0), "0")
            self.assertEqual(x < y, a < b)
            self.assertEqual(x == y, a == b)
            if a >= b:
                self.assertEqual(str(x - y), str(a - b))
            divisor = rng.randrange(1, 10**9)
            self.assertEqual(str(x // divisor), str(a // divisor))
            self.assertEqual(x % divisor, a % divisor)
        self.assertEqual(str(BigNumber("0000000000")), "0")


if __name__ == "__main__":
    unittest.main()
