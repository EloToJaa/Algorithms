#include <bits/stdc++.h>
#include <cassert>
#define main algorithm_main
#include "TreeSegmentSegment.cpp"
#undef main

using namespace std;

int main() {

  mt19937 generator(7);
  for (int size : {1, 3, 8, 15}) {
    vector<long long> reference(size);
    for (int i = 0; i < size; ++i)
      A[i + 1] = reference[i] = static_cast<int>(generator() % 20) - 30;
    build(size);
    for (int step = 0; step < 200; ++step) {
      int left = generator() % size, right = left + generator() % (size - left);
      long long value = static_cast<int>(generator() % 40) - 20;

      if (generator() % 2) {
        update(1, 1, ntree, left + 1, right + 1, value);
        for (int i = left; i <= right; ++i)
          reference[i] += value;
      } else
        assert(query(1, 1, ntree, left + 1, right + 1) ==
               accumulate(reference.begin() + left,
                          reference.begin() + right + 1, 0LL));
    }
  }
}
