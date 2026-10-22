#include <bits/stdc++.h>

// table[i][j] is the LCS length of a[0, i) and b[0, j).
std::vector<std::vector<int>> lcsTable(const std::string &a,
                                       const std::string &b) {
  int n = a.size(), m = b.size();
  std::vector<std::vector<int>> table(n + 1, std::vector<int>(m + 1, 0));
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      table[i][j] = a[i - 1] == b[j - 1]
                        ? table[i - 1][j - 1] + 1
                        : std::max(table[i - 1][j], table[i][j - 1]);
  return table;
}

int lcsLength(const std::string &a, const std::string &b) {
  return lcsTable(a, b)[a.size()][b.size()];
}

std::string lcs(const std::string &a, const std::string &b) {
  auto table = lcsTable(a, b);
  std::string result;
  int i = a.size(), j = b.size();
  while (i > 0 && j > 0) {
    if (a[i - 1] == b[j - 1]) {
      result.push_back(a[i - 1]);
      --i, --j;
    } else if (table[i - 1][j] >= table[i][j - 1]) {
      --i;
    } else {
      --j;
    }
  }
  std::reverse(result.begin(), result.end());
  return result;
}
