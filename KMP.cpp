#include <bits/stdc++.h>

using namespace std;

const int NT = 1e6 + 2;

int Pi[NT];

void Kmp(string s) {
  int n = s.size();
  s = "#" + s;
  for (int i = 2; i <= n; i++) {
    int pref = Pi[i - 1];
    while (pref > 0 and s[pref + 1] != s[i])
      pref = Pi[pref];
    if (s[pref + 1] == s[i])
      pref++;
    Pi[i] = pref;
  }
}
