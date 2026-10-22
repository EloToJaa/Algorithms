#include "Backtracking.cpp"
#include <cassert>

using Lists = std::vector<std::vector<int>>;

Lists sorted(Lists lists) {
  std::sort(lists.begin(), lists.end());
  return lists;
}

bool validBoard(const std::vector<std::string> &board) {
  int n = board.size();
  std::vector<int> queen(n);
  for (int r = 0; r < n; ++r) {
    if (std::count(board[r].begin(), board[r].end(), 'Q') != 1)
      return false;
    queen[r] = board[r].find('Q');
  }
  for (int a = 0; a < n; ++a)
    for (int b = a + 1; b < n; ++b)
      if (queen[a] == queen[b] || std::abs(queen[a] - queen[b]) == b - a)
        return false;
  return true;
}

int main() {
  std::mt19937 rng(7);
  for (int iteration = 0; iteration < 200; ++iteration) {
    int n = rng() % 7;
    std::vector<int> nums(n);
    for (int &x : nums)
      x = int(rng() % 5) - 2;

    Lists all, distinct;
    for (int mask = 0; mask < (1 << n); ++mask) {
      std::vector<int> chosen;
      for (int i = 0; i < n; ++i)
        if (mask >> i & 1)
          chosen.push_back(nums[i]);
      all.push_back(chosen);
      std::sort(chosen.begin(), chosen.end());
      distinct.push_back(chosen);
    }
    std::sort(distinct.begin(), distinct.end());
    distinct.erase(std::unique(distinct.begin(), distinct.end()),
                   distinct.end());
    assert(sorted(subsets(nums)) == sorted(all));
    assert(sorted(subsetsWithDup(nums)) == distinct);

    Lists perms;
    std::vector<int> index(n);
    std::iota(index.begin(), index.end(), 0);
    do {
      std::vector<int> perm;
      for (int i : index)
        perm.push_back(nums[i]);
      perms.push_back(perm);
    } while (std::next_permutation(index.begin(), index.end()));
    assert(sorted(permutations(nums)) == sorted(perms));

    std::vector<int> candidates;
    for (int c = 1; c <= 8; ++c)
      if (rng() % 3 == 0)
        candidates.push_back(c);
    int target = 1 + rng() % 12;
    // Count multisets by a coin-change DP over the candidates.
    std::vector<long long> ways(target + 1);
    ways[0] = 1;
    for (int c : candidates)
      for (int s = c; s <= target; ++s)
        ways[s] += ways[s - c];
    Lists found = combinationSum(candidates, target);
    assert((long long)found.size() == ways[target]);
    for (auto &combo : found) {
      assert(std::is_sorted(combo.begin(), combo.end()));
      assert(std::accumulate(combo.begin(), combo.end(), 0) == target);
    }
    assert(std::set<std::vector<int>>(found.begin(), found.end()).size() ==
           found.size());
  }

  for (int n = 0; n <= 7; ++n)
    for (int k = 0; k <= n + 1; ++k) {
      Lists expected;
      for (int mask = 0; mask < (1 << n); ++mask) {
        if (__builtin_popcount(mask) != k)
          continue;
        std::vector<int> chosen;
        for (int i = 0; i < n; ++i)
          if (mask >> i & 1)
            chosen.push_back(i + 1);
        expected.push_back(chosen);
      }
      assert(combinations(n, k) == sorted(expected));
    }

  int known[] = {1, 1, 0, 0, 2, 10, 4, 40, 92};
  for (int n = 1; n <= 8; ++n) {
    auto boards = solveNQueens(n);
    assert((int)boards.size() == known[n]);
    for (auto &board : boards)
      assert(validBoard(board));
    assert(totalNQueens(n) == known[n]);
  }

  assert(subsetsWithDup({1, 2, 2}) ==
         Lists({{}, {1}, {1, 2}, {1, 2, 2}, {2}, {2, 2}}));
  assert(combinationSum({2, 3, 6, 7}, 7) == Lists({{2, 2, 3}, {7}}));
  assert(solveNQueens(4)[0] ==
         std::vector<std::string>({".Q..", "...Q", "Q...", "..Q."}));
}
