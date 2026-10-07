#include <bits/stdc++.h>

class Sieve {
public:
  std::vector<int> spf, primes;
  explicit Sieve(int limit) {
    if (limit < 0)
      throw std::invalid_argument("negative limit");
    spf.resize(static_cast<size_t>(limit) + 1);
    for (int value = 2; value <= limit; ++value) {
      if (spf[value] == 0) {
        spf[value] = value;
        primes.push_back(value);
      }
      for (int prime : primes) {
        if (prime > spf[value] || prime > limit / value)
          break;
        spf[prime * value] = prime;
      }
    }
  }
  std::vector<std::pair<int, int>> factorize(int value) const {
    if (value < 1 || static_cast<size_t>(value) >= spf.size())
      throw std::out_of_range("value outside sieve");
    std::vector<std::pair<int, int>> factors;
    while (value > 1) {
      int prime = spf[value], exponent = 0;
      while (value % prime == 0) {
        value /= prime;
        ++exponent;
      }
      factors.push_back({prime, exponent});
    }
    return factors;
  }
};
