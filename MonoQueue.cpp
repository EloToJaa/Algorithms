#include <bits/stdc++.h>

using namespace std;

struct MonoQueue {
  int pops = 0, pushes = 0;
  deque<pair<long long, int>> Q;
  void push(const long long &val) {
    while (!Q.empty() and Q.back().first <= val)
      Q.pop_back();
    pushes++;
    Q.push_back({val, pushes});
  }
  void pop() {
    pops++;
    if (!Q.empty() and pops == Q.front().second)
      Q.pop_front();
  }
  long long max() {
    if (Q.empty())
      return -LONG_LONG_MAX;
    return Q.front().first;
  }
};
