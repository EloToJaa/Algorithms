#include <bits/stdc++.h>
#include <cassert>
#define main algorithm_main
#include "MonoQueue.cpp"
#undef main

using namespace std;

int main() {

  MonoQueue<int> queue;
  deque<int> reference;
  mt19937 generator(5);
  for (int i = 0; i < 500; ++i) {
    if (reference.empty() || generator() % 3) {
      int value = static_cast<int>(generator() % 20) - 10;
      queue.push(value);
      reference.push_back(value);
    } else {
      queue.pop();
      reference.pop_front();
    }
    int expected = reference.empty()
                       ? INT_MIN
                       : *max_element(reference.begin(), reference.end());
    assert(queue.max() == expected);
  }
}
