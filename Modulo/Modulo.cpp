#include <bits/stdc++.h>

using namespace std;

struct ModuloStruct {
  long long MOD;

  ModuloStruct(long long mod) { MOD = mod; }

  long long Modulo(const long long &a) {
    long long value = a % MOD;
    return value < 0 ? value + MOD : value;
  }

  long long Power(long long a, long long b) {
    if (b == 0)
      return 1 % MOD;
    long long ans = Power(a, b / 2);
    ans = Modulo(ans * ans);
    if (b & 1)
      return Modulo(ans * Modulo(a));
    return ans;
  }

  long long Add(long long a, long long b) {
    a = Modulo(a), b = Modulo(b);
    if (a + b >= MOD)
      return a + b - MOD;
    else
      return a + b;
  }

  long long Subtract(long long a, long long b) {
    a = Modulo(a), b = Modulo(b);
    if (a - b < 0)
      return a - b + MOD;
    else
      return a - b;
  }

  long long Multiply(long long a, long long b) {
    a = Modulo(a), b = Modulo(b);
    return Modulo(a * b);
  }

  long long Divide(long long a, long long b) {
    a = Modulo(a), b = Modulo(b);
    if (b == 0)
      throw domain_error("division by zero modulo MOD");
    return Modulo(a * Power(b, MOD - 2));
  }
} Mod(1e9 + 7);
