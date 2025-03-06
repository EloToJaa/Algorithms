#include <bits/stdc++.h>

using namespace std;

struct ModuloStruct {
  long long MOD;

  ModuloStruct(long long mod) { MOD = mod; }

  long long Modulo(const long long &a) {
    if (a < MOD)
      return a;
    return a % MOD;
  }

  long long Power(long long a, long long b) {
    if (b == 0)
      return 1;
    long long ans = Power(a, b / 2);
    ans = Modulo(ans * ans);
    if (b & 1)
      return Modulo(ans * a);
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
    return Modulo(a * Power(b, MOD - 2));
  }
} Mod(1e9 + 7);

struct Hash {
  vector<pair<long long, long long>> Hashes, Powers;
  int n, m;
  string s;
  void Build() {
    const pair<int, int> P = {29, 31};
    const int S = 'a';
    Hashes.resize(n + 1, {0, 0});
    Powers.resize(m + 1, {0, 0});
    Powers[0] = {1, 1};

    for (int i = 1; i <= m; i++)
      Powers[i] = {Mod.Multiply(Powers[i - 1].first, P.first),
                   Mod.Multiply(Powers[i - 1].second, P.second)};

    for (int i = 1; i <= n; i++)
      Hashes[i] = {
          Mod.Add(Mod.Multiply(Hashes[i - 1].first, P.first), (s[i] - S + 1)),
          Mod.Add(Mod.Multiply(Hashes[i - 1].second, P.second),
                  (s[i] - S + 1))};
  }

  void Init(string inputString, int maxSize = -1) {
    s = "#" + inputString;
    n = s.size() - 1;
    if (maxSize == -1)
      m = n;
    else
      m = maxSize;
    Build();
  }
  pair<long long, long long> GetHash(int l = 1, int r = -1) {
    if (r == -1)
      r = n;
    return {Mod.Multiply(Mod.Subtract(Hashes[r].first, Hashes[l - 1].first),
                         Powers[m - r].first),
            Mod.Multiply(Mod.Subtract(Hashes[r].second, Hashes[l - 1].second),
                         Powers[m - r].second)};
  }
  int size() { return n; }
};

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  return 0;
}
