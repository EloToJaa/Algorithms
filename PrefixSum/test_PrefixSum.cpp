#include "PrefixSum.cpp"
#include <cassert>

int main() {
  std::mt19937 rng(5);
  for (int iteration = 0; iteration < 200; ++iteration) {
    int n = rng() % 10;
    std::vector<long long> a(n);
    for (auto &x : a)
      x = (long long)(rng() % 9) - 4;
    auto prefix = prefixSums(a);
    long long k = (long long)(rng() % 9) - 4, expectedCount = 0;
    for (int l = 0; l <= n; ++l)
      for (int r = l; r <= n; ++r) {
        long long sum = std::accumulate(a.begin() + l, a.begin() + r, 0LL);
        assert(rangeSum(prefix, l, r) == sum);
        expectedCount += r > l && sum == k;
      }
    assert(countSubarraysWithSum(a, k) == expectedCount);

    std::vector<std::tuple<int, int, long long>> updates;
    std::vector<long long> expected(n, 0);
    for (int u = 0; n && u < (int)(rng() % 5); ++u) {
      int l = rng() % n, r = l + rng() % (n - l);
      long long delta = (long long)(rng() % 11) - 5;
      updates.push_back({l, r, delta});
      for (int i = l; i <= r; ++i)
        expected[i] += delta;
    }
    assert(applyRangeAdditions(n, updates) == expected);

    int rows = 1 + rng() % 5, columns = 1 + rng() % 5;
    std::vector<std::vector<long long>> matrix(rows,
                                               std::vector<long long>(columns));
    for (auto &row : matrix)
      for (auto &x : row)
        x = (long long)(rng() % 11) - 5;
    PrefixSum2D table(matrix);
    for (int r1 = 0; r1 < rows; ++r1)
      for (int r2 = r1; r2 < rows; ++r2)
        for (int c1 = 0; c1 < columns; ++c1)
          for (int c2 = c1; c2 < columns; ++c2) {
            long long sum = 0;
            for (int r = r1; r <= r2; ++r)
              for (int c = c1; c <= c2; ++c)
                sum += matrix[r][c];
            assert(table.sumRegion(r1, c1, r2, c2) == sum);
          }
  }
  assert(countSubarraysWithSum({1, 1, 1}, 2) == 2);
  assert(applyRangeAdditions(5, {{1, 3, 2}, {2, 4, 3}, {0, 2, -2}}) ==
         std::vector<long long>({-2, 0, 3, 5, 3}));
}
