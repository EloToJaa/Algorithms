#include <bits/stdc++.h>
#include <cassert>
#define main algorithm_main
#include "Hashing.cpp"
#undef main

using namespace std;

int main() {

  string text = "abacabadabacaba";
  Hash hashes;
  hashes.Init(text, 2);
  for (int left = 1; left <= static_cast<int>(text.size()); ++left) {
    for (int right = left; right <= static_cast<int>(text.size()); ++right) {
      long long first = 0, second = 0;
      for (int i = left - 1; i < right; ++i) {
        first = (first * 29 + text[i] - 'a' + 1) % 1000000007;
        second = (second * 31 + text[i] - 'a' + 1) % 1000000007;
      }
      assert(hashes.GetHash(left, right) == make_pair(first, second));
    }
  }
  assert(hashes.GetHash(1, 3) == hashes.GetHash(5, 7));
  hashes.Init("aba");
  Hash other;
  other.Init("aba");
  assert(hashes.GetHash() == other.GetHash());
}
