#include "Sieve.cpp"
#include <cassert>

int main() {
  for (int limit : {0, 1, 2, 20, 1000}) {
    Sieve sieve(limit);
    std::vector<int> primes;
    for (int value = 2; value <= limit; ++value) {
      int smallest = 2;
      while (value % smallest != 0)
        ++smallest;
      assert(sieve.spf[value] == smallest);
      if (smallest == value)
        primes.push_back(value);
      int remainder = value;
      std::vector<std::pair<int, int>> expected;
      for (int d = 2; d <= value; ++d) {
        int exponent = 0;
        while (remainder % d == 0) {
          remainder /= d;
          ++exponent;
        }
        if (exponent)
          expected.push_back({d, exponent});
      }
      assert(sieve.factorize(value) == expected);
    }
    assert(sieve.primes == primes);
  }
  assert(Sieve(1).factorize(1).empty());
  bool rejected = false;
  try {
    Sieve(-1);
  } catch (const std::invalid_argument &) {
    rejected = true;
  }
  assert(rejected);
  for (int value : {-1, 0, 11}) {
    rejected = false;
    try {
      Sieve(10).factorize(value);
    } catch (const std::out_of_range &) {
      rejected = true;
    }
    assert(rejected);
  }
}
