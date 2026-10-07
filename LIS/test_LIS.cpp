#include <bits/stdc++.h>
#include <cassert>
#define main algorithm_main
#include "LIS.cpp"
#undef main

using namespace std;

int main() {

  mt19937 generator(3);
  LIS algorithm;
  for (int size = 0; size < 100; ++size) {
    vector<int> values(size), dp(size, 1);
    for (int &value : values)
      value = static_cast<int>(generator() % 20) - 10;
    int expected = 0;
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < i; ++j)
        if (values[j] < values[i])
          dp[i] = max(dp[i], dp[j] + 1);
      expected = max(expected, dp[i]);
    }
    assert(algorithm.lengthOfLIS(values) == expected);
  }
}
