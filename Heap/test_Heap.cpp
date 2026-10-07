#include <bits/stdc++.h>
#include <cassert>
#define main algorithm_main
#include "Heap.cpp"
#undef main

using namespace std;

int main() {

  mt19937 generator(1);
  vector<int> values;
  for (int i = 0; i < 100; ++i)
    values.push_back(static_cast<int>(generator() % 100) - 50);
  MinHeap minimum(values);
  MaxHeap maximum(values);
  sort(values.begin(), values.end());
  for (int x : values) {
    assert(minimum.top() == x);
    minimum.remove();
  }
  for (auto it = values.rbegin(); it != values.rend(); ++it) {
    assert(maximum.top() == *it);
    maximum.remove();
  }
  assert(minimum.empty() && maximum.empty());
  minimum.heapify({5, 10});
  minimum.heapify({2, 7});
  assert(minimum.size() == 2);
  minimum.replace(9);
  assert(minimum.top() == 7);
  bool caught = false;
  try {
    maximum.remove();
  } catch (const out_of_range &) {
    caught = true;
  }
  assert(caught);
}
