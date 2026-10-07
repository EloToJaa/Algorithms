#include <bits/stdc++.h>
#include <cassert>
#define main algorithm_main
#include "BigNumbers.cpp"
#undef main

using namespace std;

int main() {

  auto fromInteger = [](unsigned long long value) {
    liczba result{};
    do {
      result.t[result.l++] = value % BASE;
      value /= BASE;
    } while (value);
    return result;
  };
  auto toInteger = [](liczba value) {
    unsigned long long result = 0;
    for (int i = value.l - 1; i >= 0; --i)
      result = result * BASE + value.t[i];
    return result;
  };
  mt19937 generator(8);
  for (int i = 0; i < 200; ++i) {
    unsigned long long a = generator() % 1000000000ULL,
                       b = generator() % 1000000000ULL;
    liczba x = fromInteger(a), y = fromInteger(b);
    assert(toInteger(x + y) == a + b && toInteger(x * y) == a * b);
    assert((x < y) == (a < b));
    if (a >= b)
      assert(toInteger(x - y) == a - b);
    int divisor = 1 + generator() % 1000000;
    assert(toInteger(x / divisor) == a / divisor && x % divisor == a % divisor);
  }
  auto zero = fromInteger(1000000001ULL) * 0;
  assert(zero.l == 1 && zero.t[0] == 0);
  auto carry = fromInteger(999999999ULL) + fromInteger(1);
  assert(carry.l == 2 && carry.t[0] == 0 && carry.t[1] == 1);
}
