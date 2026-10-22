#include "QuickSelect.cpp"
#include <cassert>

int main() {
  std::mt19937 rng(3);
  for (int iteration = 0; iteration < 300; ++iteration) {
    std::vector<int> nums(1 + rng() % 30);
    for (int &num : nums)
      num = int(rng() % 11) - 5;
    std::vector<int> sorted(nums), original(nums);
    std::sort(sorted.begin(), sorted.end());
    int k = int(rng() % nums.size());
    assert(quickSelect(nums, k) == sorted[k]);
    assert(nums == original);
    int count = int(rng() % (nums.size() + 2)) - 1;
    std::vector<int> smallest = kSmallest(nums, count);
    std::sort(smallest.begin(), smallest.end());
    std::vector<int> expected(sorted.begin(),
                              sorted.begin() +
                                  std::clamp(count, 0, int(nums.size())));
    assert(smallest == expected);
  }
  for (int iteration = 0; iteration < 300; ++iteration) {
    std::vector<int> nums(1 + rng() % 30);
    std::map<int, int> counts;
    for (int &num : nums)
      ++counts[num = int(rng() % 8)];
    int k = 1 + int(rng() % counts.size());
    std::vector<int> result = topKFrequent(nums, k);
    std::set<int> distinct(result.begin(), result.end());
    assert(int(distinct.size()) == k && int(result.size()) == k);
    std::vector<int> got, expected;
    for (int value : result)
      got.push_back(counts[value]);
    for (const auto &[value, count] : counts)
      expected.push_back(count);
    std::sort(got.rbegin(), got.rend());
    std::sort(expected.rbegin(), expected.rend());
    expected.resize(k);
    assert(got == expected);
  }
  assert(quickSelect(std::vector<int>{3, 2, 1, 5, 6, 4}, 6 - 2) == 5);
  assert(quickSelect(std::vector<int>(1000, 7), 500) == 7);
  std::vector<int> top = topKFrequent({1, 1, 1, 2, 2, 3}, 2);
  std::sort(top.begin(), top.end());
  assert(top == std::vector<int>({1, 2}));
}
