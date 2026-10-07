#include <bits/stdc++.h>

class SparseTable {
  std::vector<std::vector<long long>> levels;
  std::vector<int> logs;
  int size;

public:
  explicit SparseTable(const std::vector<long long> &values)
      : levels{values}, size(values.size()) {
    logs.resize(size + 1);
    for (int i = 2; i <= size; ++i)
      logs[i] = logs[i / 2] + 1;
    for (long long width = 2; width <= size; width *= 2) {
      const auto &previous = levels.back();
      std::vector<long long> next(size - width + 1);
      for (int i = 0; i < static_cast<int>(next.size()); ++i)
        next[i] = std::min(previous[i], previous[i + width / 2]);
      levels.push_back(std::move(next));
    }
  }
  long long query(int left, int right) const {
    if (left < 0 || left > right || right >= size)
      throw std::out_of_range("invalid range");
    int level = logs[right - left + 1];
    return std::min(levels[level][left],
                    levels[level][right - (1 << level) + 1]);
  }
};
