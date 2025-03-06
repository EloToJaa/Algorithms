#include <bits/stdc++.h>

using namespace std;

const int N = 1e6, NT = N + 2;

int Odd[NT], Even[NT];

void Manacher(string s) {
  int n = s.size(), k, l = 0, r = -1;
  for (int i = 0; i <= n - 1; i++) {
    k = (i > r) ? 1 : min(Odd[l + r - i + 1], r - i + 1);
    while (0 <= i - k and i + k < n and s[i - k] == s[i + k])
      k++;
    Odd[i + 1] = k--;
    if (i + k > r) {
      l = i - k;
      r = i + k;
    }
  }
  l = 0, r = -1;
  for (int i = 0; i <= n - 1; i++) {
    k = (i > r) ? 0 : min(Even[l + r - i + 2], r - i + 1);
    while (0 <= i - k - 1 and i + k < n and s[i - k - 1] == s[i + k])
      k++;
    Even[i + 1] = k--;
    if (i + k > r) {
      l = i - k - 1;
      r = i + k;
    }
  }
}
