"""Arithmetic modulo a prime, including binary exponentiation."""


class Modulo:
    def __init__(self, modulus=1_000_000_007):
        self.modulus = modulus

    def add(self, first, second):
        return (first + second) % self.modulus

    def subtract(self, first, second):
        return (first - second) % self.modulus

    def multiply(self, first, second):
        return first * second % self.modulus

    def power(self, base, exponent):
        """Exponent must be nonnegative."""
        result = 1 % self.modulus
        base %= self.modulus
        while exponent:
            if exponent & 1:
                result = self.multiply(result, base)
            base = self.multiply(base, base)
            exponent //= 2
        return result

    def divide(self, first, second):
        """Requires a prime modulus and a divisor nonzero modulo it."""
        return self.multiply(first, self.power(second, self.modulus - 2))
