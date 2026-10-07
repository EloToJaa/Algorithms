#include <bits/stdc++.h>
#include <cassert>
#define main algorithm_main
#include "KMR.cpp"
#undef main

using namespace std;

int main() {

  ostringstream ignored;
  auto previous = cout.rdbuf(ignored.rdbuf());
  for (string text : {"banana", "aaaaa", "abacaba", "z"}) {
    string padded = "#" + text;
    kmr(padded);
    sa(padded);
    lcp(padded);
    int size = text.size();
    vector<int> suffixes(size);
    iota(suffixes.begin(), suffixes.end(), 1);
    sort(suffixes.begin(), suffixes.end(),
         [&](int a, int b) { return padded.substr(a) < padded.substr(b); });
    for (int i = 1; i <= size; ++i) {
      assert(SA[i] == suffixes[i - 1]);
      assert(RANK[SA[i]] == i);
      assert(LCP[i] == (i == 1 ? -1 : commonPart(padded, SA[i], SA[i - 1])));
    }
    for (int a = 1; a <= size; ++a)
      for (int b = a; b <= size; ++b)
        for (int c = 1; c <= size; ++c)
          for (int d = c; d <= size; ++d) {
            string x = padded.substr(a, b - a + 1),
                   y = padded.substr(c, d - c + 1);
            assert(compare(a, b, c, d) == (x < y ? 0 : x > y ? 2 : 1));
          }
  }
  kmr("#");
  sa("#");
  lcp("#");
  cout.rdbuf(previous);
}
