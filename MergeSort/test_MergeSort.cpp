#include <bits/stdc++.h>
#include <cassert>
#define main algorithm_main
#include "MergeSort.cpp"
#undef main

using namespace std;

int main() {

  mt19937 generator(2);
  for (int size = 0; size < 100; ++size) {
    vector<int> values(size);
    for (int &value : values)
      value = static_cast<int>(generator() % 20) - 10;
    MergeSort algorithm(values);
    algorithm.sort();
    sort(values.begin(), values.end());
    assert(algorithm.getSortedArray() == values);
  }
  MergeSort regression({3, 1, 2});
  regression.sort();
  assert(regression.getSortedArray() == vector<int>({1, 2, 3}));
}
