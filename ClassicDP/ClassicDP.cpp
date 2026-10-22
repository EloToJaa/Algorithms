#include <bits/stdc++.h>

// Max sum of non-adjacent nonnegative values in a line.
long long rob(const std::vector<int> &nums) {
  long long take = 0, skip = 0;
  for (int value : nums) {
    long long nextTake = skip + value;
    skip = std::max(take, skip);
    take = nextTake;
  }
  return std::max(take, skip);
}

// First and last houses are adjacent.
long long robCircular(const std::vector<int> &nums) {
  if (nums.size() == 1)
    return nums[0];
  if (nums.empty())
    return 0;
  return std::max(rob(std::vector<int>(nums.begin() + 1, nums.end())),
                  rob(std::vector<int>(nums.begin(), nums.end() - 1)));
}

// Fewest positive coins summing to amount, or -1.
int coinChange(const std::vector<int> &coins, int amount) {
  std::vector<int> best(amount + 1, amount + 1);
  best[0] = 0;
  for (int total = 1; total <= amount; ++total)
    for (int coin : coins)
      if (coin <= total)
        best[total] = std::min(best[total], best[total - coin] + 1);
  return best[amount] > amount ? -1 : best[amount];
}

// Coin multisets (order ignored): coins in the outer loop.
long long coinChangeWays(const std::vector<int> &coins, int amount) {
  std::vector<long long> ways(amount + 1);
  ways[0] = 1;
  for (int coin : coins)
    for (int total = coin; total <= amount; ++total)
      ways[total] += ways[total - coin];
  return ways[amount];
}

// Coin sequences (order matters): totals in the outer loop.
long long coinChangeOrderedWays(const std::vector<int> &coins, int amount) {
  std::vector<long long> ways(amount + 1);
  ways[0] = 1;
  for (int total = 1; total <= amount; ++total)
    for (int coin : coins)
      if (coin <= total)
        ways[total] += ways[total - coin];
  return ways[amount];
}

// Right/down paths avoiding cells equal to 1.
long long uniquePathsWithObstacles(const std::vector<std::vector<int>> &grid) {
  if (grid.empty() || grid[0].empty())
    return 0;
  std::vector<long long> paths(grid[0].size());
  paths[0] = 1;
  for (const auto &row : grid)
    for (size_t j = 0; j < row.size(); ++j) {
      if (row[j] == 1)
        paths[j] = 0;
      else if (j > 0)
        paths[j] += paths[j - 1];
    }
  return paths.back();
}

// Minimum right/down path sum of a nonempty grid.
long long minPathSum(const std::vector<std::vector<int>> &grid) {
  const long long inf = LLONG_MAX / 2;
  std::vector<long long> best(grid[0].size(), inf);
  best[0] = 0;
  for (const auto &row : grid)
    for (size_t j = 0; j < row.size(); ++j)
      best[j] = std::min(best[j], j > 0 ? best[j - 1] : inf) + row[j];
  return best.back();
}

bool wordBreak(const std::string &text, const std::vector<std::string> &words) {
  std::unordered_set<std::string> dictionary(words.begin(), words.end());
  std::set<size_t> lengths;
  for (const auto &word : words)
    lengths.insert(word.size());
  std::vector<bool> ok(text.size() + 1);
  ok[0] = true;
  for (size_t i = 1; i <= text.size(); ++i)
    for (size_t size : lengths)
      if (size <= i && ok[i - size] &&
          dictionary.count(text.substr(i - size, size))) {
        ok[i] = true;
        break;
      }
  return ok[text.size()];
}
