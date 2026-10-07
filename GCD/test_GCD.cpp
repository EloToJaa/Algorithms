#include "GCD.cpp"
#include <cassert>

void check(long long a, long long b) {
  auto result = extended_gcd(a, b);
  assert(result.gcd == std::gcd(a, b));
  assert(gcd(a, b) == result.gcd);
  assert(static_cast<__int128>(a) * result.x +
             static_cast<__int128>(b) * result.y ==
         result.gcd);
}
int main() {
  for (int a = -15; a <= 15; ++a)
    for (int b = -15; b <= 15; ++b)
      check(a, b);
  std::mt19937_64 rng(21);
  for (int i = 0; i < 1000; ++i) {
    long long a = rng() >> 1, b = rng() >> 1;
    check(i % 2 ? -a : a, i % 3 ? -b : b);
  }
  check(LLONG_MAX, LLONG_MAX - 1);
  check(-LLONG_MAX, 0);
  for (auto values : std::vector<std::pair<long long, long long>>{
           {LLONG_MIN, 0}, {0, LLONG_MIN}}) {
    bool rejected = false;
    try {
      extended_gcd(values.first, values.second);
    } catch (const std::out_of_range &) {
      rejected = true;
    }
    assert(rejected);
  }
}
