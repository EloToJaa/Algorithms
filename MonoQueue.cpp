#include <bits/stdc++.h>

using namespace std;

class MonoQueue {
private:
  int pops = 0, pushes = 0;
  deque<pair<long long, int>> queue;

public:
  void push(const long long &val) {
    while (!queue.empty() and queue.back().first <= val)
      queue.pop_back();
    pushes++;
    queue.push_back({val, pushes});
  }

  void pop() {
    pops++;
    if (!queue.empty() and pops == queue.front().second)
      queue.pop_front();
  }

  long long max() {
    if (queue.empty())
      return -LONG_LONG_MAX;
    return queue.front().first;
  }
};
