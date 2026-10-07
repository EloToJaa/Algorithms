#include "SparseTable.cpp"
#include <cassert>

int main() {
  std::mt19937 rng(23);
  for (int n = 1; n < 50; ++n) {
    std::vector<long long> values(n);
    for (auto &value : values)
      value = static_cast<int>(rng() % 201) - 100;
    SparseTable table(values);
    auto original = values;
    values[0] = 999;
    for (int left = 0; left < n; ++left)
      for (int right = left; right < n; ++right)
        assert(table.query(left, right) ==
               *std::min_element(original.begin() + left,
                                 original.begin() + right + 1));
  }
  assert(SparseTable({LLONG_MAX, LLONG_MIN}).query(0, 1) == LLONG_MIN);
  for (auto interval :
       std::vector<std::pair<int, int>>{{-1, 0}, {0, 2}, {1, 0}}) {
    bool rejected = false;
    try {
      SparseTable({1, 2}).query(interval.first, interval.second);
    } catch (const std::out_of_range &) {
      rejected = true;
    }
    assert(rejected);
  }
  bool rejected = false;
  try {
    SparseTable({}).query(0, 0);
  } catch (const std::out_of_range &) {
    rejected = true;
  }
  assert(rejected);
}
