#include <bits/stdc++.h>

// table[i][j] tells whether s[i..j] (inclusive) is a palindrome.
std::vector<std::vector<bool>> palindromeTable(const std::string &s) {
  int n = s.size();
  std::vector<std::vector<bool>> table(n, std::vector<bool>(n, false));
  for (int i = n - 1; i >= 0; --i)
    for (int j = i; j < n; ++j)
      table[i][j] = s[i] == s[j] && (j - i < 2 || table[i + 1][j - 1]);
  return table;
}

int longestPalindromicSubsequence(const std::string &s) {
  int n = s.size();
  if (n == 0)
    return 0;
  std::vector<std::vector<int>> best(n, std::vector<int>(n, 0));
  for (int i = n - 1; i >= 0; --i) {
    best[i][i] = 1;
    for (int j = i + 1; j < n; ++j)
      best[i][j] = s[i] == s[j] ? best[i + 1][j - 1] + 2
                                : std::max(best[i + 1][j], best[i][j - 1]);
  }
  return best[0][n - 1];
}

int minPalindromeCuts(const std::string &s) {
  int n = s.size();
  if (n == 0)
    return 0;
  auto table = palindromeTable(s);
  // cuts[j] is the answer for s[0, j); cuts[0] = -1 cancels the first cut.
  std::vector<int> cuts(n + 1, n);
  cuts[0] = -1;
  for (int j = 1; j <= n; ++j)
    for (int i = 0; i < j; ++i)
      if (table[i][j - 1])
        cuts[j] = std::min(cuts[j], cuts[i] + 1);
  return cuts[n];
}
