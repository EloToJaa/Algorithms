#include <bits/stdc++.h>
#include <cassert>
#define main algorithm_main
#include "KMP.cpp"
#undef main

using namespace std;

int main() {

  for (string text : {"ababa", "aaaaa", "abcabca", "a", ""}) {
    Kmp(text);
    for (int i = 0; i < static_cast<int>(text.size()); ++i) {
      int expected = 0;
      for (int k = 1; k <= i; ++k)
        if (text.substr(0, k) == text.substr(i - k + 1, k))
          expected = k;
      assert(Pi[i + 1] == expected);
    }
  }
}
