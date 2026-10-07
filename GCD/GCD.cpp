#include <bits/stdc++.h>

struct ExtendedGCD {
  long long gcd, x, y;
};

ExtendedGCD extended_gcd(long long first, long long second) {
  if (first == LLONG_MIN || second == LLONG_MIN)
    throw std::out_of_range("absolute inputs must fit in long long");
  __int128 old_r = std::abs(first), r = std::abs(second);
  __int128 old_x = 1, x = 0, old_y = 0, y = 1;
  while (r != 0) {
    __int128 quotient = old_r / r;
    auto next_r = old_r - quotient * r;
    old_r = r;
    r = next_r;
    auto next_x = old_x - quotient * x;
    old_x = x;
    x = next_x;
    auto next_y = old_y - quotient * y;
    old_y = y;
    y = next_y;
  }
  return {static_cast<long long>(old_r),
          static_cast<long long>(first < 0 ? -old_x : old_x),
          static_cast<long long>(second < 0 ? -old_y : old_y)};
}
long long gcd(long long first, long long second) {
  return extended_gcd(first, second).gcd;
}
