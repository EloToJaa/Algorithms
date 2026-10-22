#include "Palindromes.cpp"
#include <cassert>

bool isPalindrome(const std::string &s) {
  return std::equal(s.begin(), s.end(), s.rbegin());
}

int main() {
  std::mt19937 rng(6);
  for (int iteration = 0; iteration < 200; ++iteration) {
    int n = rng() % 10;
    std::string s(n, 'a');
    for (char &c : s)
      c = 'a' + rng() % 2;

    auto table = palindromeTable(s);
    for (int i = 0; i < n; ++i)
      for (int j = i; j < n; ++j)
        assert(table[i][j] == isPalindrome(s.substr(i, j - i + 1)));

    int longest = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
      std::string chosen;
      for (int i = 0; i < n; ++i)
        if (mask >> i & 1)
          chosen.push_back(s[i]);
      if (isPalindrome(chosen))
        longest = std::max(longest, int(chosen.size()));
    }
    assert(longestPalindromicSubsequence(s) == longest);

    // Every subset of the n - 1 gaps is a candidate set of cuts.
    int fewest = n ? n - 1 : 0;
    for (int mask = 0; n && mask < (1 << (n - 1)); ++mask) {
      bool valid = true;
      for (int start = 0, end = 0; end < n; ++end)
        if (end == n - 1 || mask >> end & 1) {
          valid = valid && isPalindrome(s.substr(start, end - start + 1));
          start = end + 1;
        }
      if (valid)
        fewest = std::min(fewest, __builtin_popcount(mask));
    }
    assert(minPalindromeCuts(s) == fewest);
  }
  assert(longestPalindromicSubsequence("bbbab") == 4);
  assert(minPalindromeCuts("aab") == 1);
  assert(minPalindromeCuts("racecar") == 0);
}
