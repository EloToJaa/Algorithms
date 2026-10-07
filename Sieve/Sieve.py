"""Linear sieve with smallest prime factors and repeated factorization."""


class Sieve:
    def __init__(self, limit):
        if limit < 0:
            raise ValueError("negative limit")
        self.spf = [0] * (limit + 1)
        self.primes = []
        for value in range(2, limit + 1):
            if self.spf[value] == 0:
                self.spf[value] = value
                self.primes.append(value)
            for prime in self.primes:
                if prime > self.spf[value] or prime * value > limit:
                    break
                self.spf[prime * value] = prime

    def factorize(self, value):
        """Return sorted (prime, exponent) pairs for 1 <= value <= limit."""
        if not 1 <= value < len(self.spf):
            raise ValueError("value outside sieve")
        factors = []
        while value > 1:
            prime, exponent = self.spf[value], 0
            while value % prime == 0:
                value //= prime
                exponent += 1
            factors.append((prime, exponent))
        return factors
