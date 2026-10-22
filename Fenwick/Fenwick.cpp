#include <bits/stdc++.h>

// Zero-based API over a one-based tree; tree[i] sums (i - (i & -i), i].
struct Fenwick {
  int n;
  std::vector<long long> tree;

  explicit Fenwick(int size) : n(size), tree(size + 1, 0) {}

  // O(n) build: push each node's partial sum into its parent once.
  explicit Fenwick(const std::vector<long long> &values)
      : n(int(values.size())), tree(values.size() + 1, 0) {
    for (int i = 1; i <= n; ++i) {
      tree[i] += values[i - 1];
      int parent = i + (i & -i);
      if (parent <= n)
        tree[parent] += tree[i];
    }
  }

  // values[index] += delta.
  void add(int index, long long delta) {
    for (int i = index + 1; i <= n; i += i & -i)
      tree[i] += delta;
  }

  // Sum of the first count elements.
  long long prefixSum(int count) const {
    long long total = 0;
    for (; count > 0; count -= count & -count)
      total += tree[count];
    return total;
  }

  // Sum of values[left, right) (half-open).
  long long rangeSum(int left, int right) const {
    return prefixSum(right) - prefixSum(left);
  }

  // Smallest count with prefixSum(count) >= target, or n + 1 if none.
  // Requires nonnegative values.
  int lowerBound(long long target) const {
    if (target <= 0)
      return 0;
    int position = 0;
    int step = 1;
    while (step * 2 <= n)
      step *= 2;
    for (; step > 0; step /= 2) {
      if (position + step <= n && tree[position + step] < target) {
        position += step;
        target -= tree[position];
      }
    }
    return position + 1;
  }
};

// result[i] is the number of j > i with nums[j] < nums[i].
std::vector<int> countSmallerAfterSelf(const std::vector<int> &nums) {
  std::vector<int> ranks(nums);
  std::sort(ranks.begin(), ranks.end());
  ranks.erase(std::unique(ranks.begin(), ranks.end()), ranks.end());
  Fenwick counts(int(ranks.size()));
  std::vector<int> result(nums.size());
  for (int i = int(nums.size()) - 1; i >= 0; --i) {
    int rank = int(std::lower_bound(ranks.begin(), ranks.end(), nums[i]) -
                   ranks.begin());
    result[i] = int(counts.prefixSum(rank));
    counts.add(rank, 1);
  }
  return result;
}
