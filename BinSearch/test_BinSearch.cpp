#include <bits/stdc++.h>
#include <cassert>
#define main algorithm_main
#include "BinSearch.cpp"
#undef main

using namespace std;

int main() {

  for (int threshold = -1; threshold <= 11; ++threshold) {
    assert(search_first(0, 9, [=](int x) { return x >= threshold; }) ==
           clamp(threshold, 0, 10));
    assert(search_last(0, 9, [=](int x) { return x <= threshold; }) ==
           clamp(threshold, -1, 9));
  }
  assert(search_first(-2000000000, 2000000000, [](int x) { return x >= 17; }) ==
         17);
  assert(search_first(INT_MIN, 0, [](int) { return true; }) == INT_MIN);
  assert(search_last(0, INT_MAX, [](int) { return true; }) == INT_MAX);
}
