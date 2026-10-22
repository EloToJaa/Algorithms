#include <bits/stdc++.h>

// prefix[i] is the sum of a[0, i); size is a.size() + 1.
std::vector<long long> prefixSums(const std::vector<long long> &a) {
  std::vector<long long> prefix(a.size() + 1, 0);
  for (size_t i = 0; i < a.size(); ++i)
    prefix[i + 1] = prefix[i] + a[i];
  return prefix;
}

// Sum of the half-open range a[left, right).
long long rangeSum(const std::vector<long long> &prefix, int left, int right) {
  return prefix[right] - prefix[left];
}

struct PrefixSum2D {
  // table[i][j] is the sum of the top-left i x j block.
  std::vector<std::vector<long long>> table;

  PrefixSum2D(const std::vector<std::vector<long long>> &matrix) {
    int n = matrix.size(), m = n ? matrix[0].size() : 0;
    table.assign(n + 1, std::vector<long long>(m + 1, 0));
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        table[i + 1][j + 1] =
            matrix[i][j] + table[i][j + 1] + table[i + 1][j] - table[i][j];
  }

  // Sum of the inclusive rectangle [row1, row2] x [col1, col2].
  long long sumRegion(int row1, int col1, int row2, int col2) const {
    return table[row2 + 1][col2 + 1] - table[row1][col2 + 1] -
           table[row2 + 1][col1] + table[row1][col1];
  }
};

// Number of nonempty contiguous subarrays summing to k.
long long countSubarraysWithSum(const std::vector<long long> &a, long long k) {
  std::unordered_map<long long, long long> seen{{0, 1}};
  long long total = 0, count = 0;
  for (long long x : a) {
    total += x;
    auto it = seen.find(total - k);
    if (it != seen.end())
      count += it->second;
    seen[total]++;
  }
  return count;
}

// Start from zeros and add delta to every index in each inclusive
// [left, right].
std::vector<long long> applyRangeAdditions(
    int size, const std::vector<std::tuple<int, int, long long>> &updates) {
  std::vector<long long> diff(size + 1, 0);
  for (auto [left, right, delta] : updates) {
    diff[left] += delta;
    diff[right + 1] -= delta;
  }
  diff.pop_back();
  std::partial_sum(diff.begin(), diff.end(), diff.begin());
  return diff;
}
