#include "Fenwick.cpp"
#include <cassert>

int main() {
  std::mt19937 rng(7);
  for (int iteration = 0; iteration < 100; ++iteration) {
    int n = int(rng() % 20);
    std::vector<long long> values(n);
    for (long long &value : values)
      value = int(rng() % 21) - 10;
    Fenwick tree(values);
    for (int step = 0; step < 50; ++step) {
      if (n > 0 && rng() % 2) {
        int index = int(rng() % n);
        long long delta = int(rng() % 21) - 10;
        tree.add(index, delta);
        values[index] += delta;
      }
      int left = int(rng() % (n + 1));
      int right = left + int(rng() % (n - left + 1));
      long long prefix =
          std::accumulate(values.begin(), values.begin() + right, 0LL);
      long long range =
          std::accumulate(values.begin() + left, values.begin() + right, 0LL);
      assert(tree.prefixSum(right) == prefix);
      assert(tree.rangeSum(left, right) == range);
    }
  }
  for (int iteration = 0; iteration < 200; ++iteration) {
    int n = int(rng() % 20);
    std::vector<long long> values(n);
    for (long long &value : values)
      value = rng() % 4;
    Fenwick tree(values);
    long long total = std::accumulate(values.begin(), values.end(), 0LL);
    for (long long target = -1; target <= total + 2; ++target) {
      int expected = n + 1;
      long long prefix = 0;
      for (int count = 0; count <= n; ++count) {
        if (count > 0)
          prefix += values[count - 1];
        if (prefix >= target) {
          expected = count;
          break;
        }
      }
      assert(tree.lowerBound(target) == expected);
    }
  }
  for (int iteration = 0; iteration < 200; ++iteration) {
    std::vector<int> nums(rng() % 15);
    for (int &num : nums)
      num = int(rng() % 11) - 5;
    std::vector<int> expected(nums.size());
    for (size_t i = 0; i < nums.size(); ++i)
      for (size_t j = i + 1; j < nums.size(); ++j)
        expected[i] += nums[j] < nums[i];
    assert(countSmallerAfterSelf(nums) == expected);
  }
  assert(countSmallerAfterSelf({5, 2, 6, 1}) == std::vector<int>({2, 1, 1, 0}));
  Fenwick tree(std::vector<long long>{1, 0, 2, 3});
  assert(tree.lowerBound(2) - 1 == 2);
  assert(tree.rangeSum(1, 3) == 2);
}
