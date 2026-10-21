"""Arithmetic modulo a prime, including binary exponentiation."""


class Modulo:
    def __init__(self, modulus: int = 1_000_000_007) -> None:
        self.modulus = modulus

    def add(self, first: int, second: int) -> int:
        return (first + second) % self.modulus

    def subtract(self, first: int, second: int) -> int:
        return (first - second) % self.modulus

    def multiply(self, first: int, second: int) -> int:
        return first * second % self.modulus

    def power(self, base: int, exponent: int) -> int:
        """Exponent must be nonnegative."""
        result = 1 % self.modulus
        base %= self.modulus
        while exponent:
            if exponent & 1:
                result = self.multiply(result, base)
            base = self.multiply(base, base)
            exponent //= 2
        return result

    def divide(self, first: int, second: int) -> int:
        """Requires a prime modulus and a divisor nonzero modulo it."""
        return self.multiply(first, self.power(second, self.modulus - 2))
