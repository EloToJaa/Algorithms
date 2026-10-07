#include <bits/stdc++.h>

template <typename T> class MonoQueue {
private:
  int pops = 0, pushes = 0;
  std::deque<std::pair<T, int>> queue;

public:
  void push(const T &val) {
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

  T max() {
    if (queue.empty())
      return std::numeric_limits<T>::lowest();
    return queue.front().first;
  }
};
