#include <bits/stdc++.h>

// Rearranges values so values[k] is the k-th smallest (zero-based) and
// values[0, k) holds no larger elements. Requires 0 <= k < values.size().
template <typename T> T selectInPlace(std::vector<T> &values, int k) {
  static std::mt19937 rng(std::random_device{}());
  int low = 0, high = int(values.size());
  while (true) {
    T pivot = values[low + int(rng() % unsigned(high - low))];
    // Dutch flag: [low, lt) < pivot, [lt, i) == pivot, (gt, high) > pivot.
    int lt = low, i = low, gt = high - 1;
    while (i <= gt) {
      if (values[i] < pivot)
        std::swap(values[lt++], values[i++]);
      else if (pivot < values[i])
        std::swap(values[gt--], values[i]);
      else
        ++i;
    }
    if (k < lt)
      high = lt;
    else if (k > gt)
      low = gt + 1;
    else
      return pivot;
  }
}

// Takes a copy, so the caller's vector is untouched. The standard library
// equivalent is std::nth_element(v.begin(), v.begin() + k, v.end()).
template <typename T> T quickSelect(std::vector<T> values, int k) {
  return selectInPlace(values, k);
}

// The k smallest elements in no particular order.
template <typename T> std::vector<T> kSmallest(std::vector<T> values, int k) {
  if (k <= 0)
    return {};
  if (k >= int(values.size()))
    return values;
  selectInPlace(values, k - 1);
  values.resize(k);
  return values;
}

// k most frequent distinct values via bucket sort; ties broken arbitrarily.
std::vector<int> topKFrequent(const std::vector<int> &nums, int k) {
  std::unordered_map<int, int> counts;
  for (int num : nums)
    ++counts[num];
  std::vector<std::vector<int>> buckets(nums.size() + 1);
  for (const auto &[value, count] : counts)
    buckets[count].push_back(value);
  std::vector<int> result;
  for (int count = int(nums.size()); count > 0; --count)
    for (int value : buckets[count]) {
      if (int(result.size()) == k)
        return result;
      result.push_back(value);
    }
  return result;
}
