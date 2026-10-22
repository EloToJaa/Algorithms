#include <bits/stdc++.h>

// All 2^n subsets in DFS order.
std::vector<std::vector<int>> subsets(const std::vector<int> &nums) {
  std::vector<std::vector<int>> result;
  std::vector<int> path;
  std::function<void(int)> go = [&](int start) {
    result.push_back(path);
    for (int i = start; i < (int)nums.size(); ++i) {
      path.push_back(nums[i]);
      go(i + 1);
      path.pop_back();
    }
  };
  go(0);
  return result;
}

// Distinct subsets of a multiset; each subset is sorted.
std::vector<std::vector<int>> subsetsWithDup(std::vector<int> nums) {
  std::sort(nums.begin(), nums.end());
  std::vector<std::vector<int>> result;
  std::vector<int> path;
  std::function<void(int)> go = [&](int start) {
    result.push_back(path);
    for (int i = start; i < (int)nums.size(); ++i) {
      if (i > start && nums[i] == nums[i - 1])
        continue;
      path.push_back(nums[i]);
      go(i + 1);
      path.pop_back();
    }
  };
  go(0);
  return result;
}

std::vector<std::vector<int>> permutations(const std::vector<int> &nums) {
  std::vector<std::vector<int>> result;
  std::vector<int> path;
  std::vector<bool> used(nums.size());
  std::function<void()> go = [&]() {
    if (path.size() == nums.size()) {
      result.push_back(path);
      return;
    }
    for (size_t i = 0; i < nums.size(); ++i) {
      if (used[i])
        continue;
      used[i] = true;
      path.push_back(nums[i]);
      go();
      path.pop_back();
      used[i] = false;
    }
  };
  go();
  return result;
}

// k-element increasing vectors drawn from 1..n.
std::vector<std::vector<int>> combinations(int n, int k) {
  std::vector<std::vector<int>> result;
  std::vector<int> path;
  std::function<void(int)> go = [&](int start) {
    if ((int)path.size() == k) {
      result.push_back(path);
      return;
    }
    for (int value = start; value <= n - (k - (int)path.size()) + 1; ++value) {
      path.push_back(value);
      go(value + 1);
      path.pop_back();
    }
  };
  go(1);
  return result;
}

// Multisets of distinct positive candidates summing to target.
std::vector<std::vector<int>> combinationSum(std::vector<int> candidates,
                                             int target) {
  std::sort(candidates.begin(), candidates.end());
  std::vector<std::vector<int>> result;
  std::vector<int> path;
  std::function<void(int, int)> go = [&](int start, int remaining) {
    if (remaining == 0) {
      result.push_back(path);
      return;
    }
    for (int i = start; i < (int)candidates.size(); ++i) {
      if (candidates[i] > remaining)
        break;
      path.push_back(candidates[i]);
      go(i, remaining - candidates[i]);
      path.pop_back();
    }
  };
  go(0, target);
  return result;
}

std::vector<std::vector<std::string>> solveNQueens(int n) {
  std::vector<std::vector<std::string>> result;
  std::vector<std::string> board(n, std::string(n, '.'));
  std::vector<bool> cols(n), diagonals(2 * n), antiDiagonals(2 * n);
  std::function<void(int)> go = [&](int row) {
    if (row == n) {
      result.push_back(board);
      return;
    }
    for (int col = 0; col < n; ++col) {
      int d = row - col + n, a = row + col;
      if (cols[col] || diagonals[d] || antiDiagonals[a])
        continue;
      cols[col] = diagonals[d] = antiDiagonals[a] = true;
      board[row][col] = 'Q';
      go(row + 1);
      board[row][col] = '.';
      cols[col] = diagonals[d] = antiDiagonals[a] = false;
    }
  };
  go(0);
  return result;
}

// Bitmask N-Queens count; n <= 30.
int totalNQueens(int n) {
  int full = (1 << n) - 1;
  std::function<int(int, int, int)> go = [&](int cols, int left, int right) {
    if (cols == full)
      return 1;
    int count = 0;
    for (int free = full & ~(cols | left | right); free; free &= free - 1) {
      int bit = free & -free;
      count += go(cols | bit, (left | bit) << 1 & full, (right | bit) >> 1);
    }
    return count;
  };
  return go(0, 0, 0);
}
