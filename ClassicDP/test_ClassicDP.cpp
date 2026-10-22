#include "ClassicDP.cpp"
#include <cassert>

using Grid = std::vector<std::vector<int>>;

long long bruteRob(const std::vector<int> &nums, bool circular) {
  int n = nums.size();
  long long best = 0;
  for (int mask = 0; mask < (1 << n); ++mask) {
    if (mask & mask >> 1)
      continue;
    if (circular && n > 1 && (mask & 1) && (mask >> (n - 1) & 1))
      continue;
    long long sum = 0;
    for (int i = 0; i < n; ++i)
      if (mask >> i & 1)
        sum += nums[i];
    best = std::max(best, sum);
  }
  return best;
}

// Multisets with coins used in nondecreasing index order from `from`.
void countMultisets(const std::vector<int> &coins, int from, int amount,
                    int used, long long &ways, int &fewest) {
  if (amount == 0) {
    ++ways;
    fewest = fewest < 0 ? used : std::min(fewest, used);
    return;
  }
  for (int i = from; i < (int)coins.size(); ++i)
    if (coins[i] <= amount)
      countMultisets(coins, i, amount - coins[i], used + 1, ways, fewest);
}

long long sequences(const std::vector<int> &coins, int amount) {
  if (amount == 0)
    return 1;
  long long ways = 0;
  for (int coin : coins)
    if (coin <= amount)
      ways += sequences(coins, amount - coin);
  return ways;
}

// Collects the sum and obstacle flag of every right/down path.
void walk(const Grid &grid, int i, int j, long long sum, bool blocked,
          std::vector<std::pair<long long, bool>> &paths) {
  sum += grid[i][j];
  blocked = blocked || grid[i][j] == 1;
  int rows = grid.size(), cols = grid[0].size();
  if (i == rows - 1 && j == cols - 1) {
    paths.push_back({sum, blocked});
    return;
  }
  if (i + 1 < rows)
    walk(grid, i + 1, j, sum, blocked, paths);
  if (j + 1 < cols)
    walk(grid, i, j + 1, sum, blocked, paths);
}

bool bruteWordBreak(const std::string &text,
                    const std::vector<std::string> &words) {
  if (text.empty())
    return true;
  for (const auto &word : words)
    if (!word.empty() && text.compare(0, word.size(), word) == 0 &&
        bruteWordBreak(text.substr(word.size()), words))
      return true;
  return false;
}

int main() {
  std::mt19937 rng(1);
  for (int iteration = 0; iteration < 300; ++iteration) {
    std::vector<int> nums(rng() % 9);
    for (int &x : nums)
      x = rng() % 10;
    assert(rob(nums) == bruteRob(nums, false));
    assert(robCircular(nums) == bruteRob(nums, true));

    std::vector<int> coins;
    for (int c = 1; c <= 7; ++c)
      if (rng() % 3 == 0)
        coins.push_back(c);
    if (coins.empty())
      coins.push_back(1 + rng() % 7);
    int amount = rng() % 13;
    long long ways = 0;
    int fewest = -1;
    countMultisets(coins, 0, amount, 0, ways, fewest);
    assert(coinChange(coins, amount) == fewest);
    assert(coinChangeWays(coins, amount) == ways);
    assert(coinChangeOrderedWays(coins, amount) == sequences(coins, amount));

    int rows = 1 + rng() % 4, cols = 1 + rng() % 4;
    Grid values(rows, std::vector<int>(cols)), obstacles = values;
    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < cols; ++j) {
        values[i][j] = rng() % 10;
        obstacles[i][j] = rng() % 4 == 0;
      }
    std::vector<std::pair<long long, bool>> paths;
    walk(values, 0, 0, 0, false, paths);
    long long best = LLONG_MAX;
    for (auto [sum, blocked] : paths)
      best = std::min(best, sum);
    assert(minPathSum(values) == best);
    paths.clear();
    walk(obstacles, 0, 0, 0, false, paths);
    long long free = 0;
    for (auto [sum, blocked] : paths)
      free += !blocked;
    assert(uniquePathsWithObstacles(obstacles) == free);

    std::vector<std::string> words(rng() % 4);
    for (auto &word : words) {
      word.resize(1 + rng() % 3);
      for (char &c : word)
        c = 'a' + rng() % 2;
    }
    std::string text(rng() % 9, 'a');
    for (char &c : text)
      c = 'a' + rng() % 2;
    assert(wordBreak(text, words) == bruteWordBreak(text, words));
  }
  assert(rob({2, 7, 9, 3, 1}) == 12);
  assert(robCircular({2, 3, 2}) == 3);
  assert(coinChange({1, 2, 5}, 11) == 3);
  assert(coinChange({2}, 3) == -1);
  assert(coinChangeWays({1, 2, 5}, 5) == 4);
  assert(coinChangeOrderedWays({1, 2, 3}, 4) == 7);
  assert(uniquePathsWithObstacles({{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}) == 2);
  assert(minPathSum({{1, 3, 1}, {1, 5, 1}, {4, 2, 1}}) == 7);
  assert(wordBreak("leetcode", {"leet", "code"}));
  assert(!wordBreak("catsandog", {"cats", "dog", "sand", "and", "cat"}));
}
