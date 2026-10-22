#include "SlidingWindow.cpp"
#include <cassert>

bool covers(const std::string &window, const std::string &pattern) {
  std::map<char, int> need;
  for (char c : pattern)
    need[c]++;
  for (char c : window)
    need[c]--;
  for (auto &[c, count] : need)
    if (count > 0)
      return false;
  return true;
}

int main() {
  std::mt19937 rng(5);
  for (int iteration = 0; iteration < 300; ++iteration) {
    int n = rng() % 12;
    std::string text(n, 'a'), pattern(1 + rng() % 3, 'a');
    for (char &c : text)
      c = 'a' + rng() % 4;
    for (char &c : pattern)
      c = 'a' + rng() % 4;
    std::vector<int> a(text.begin(), text.end());
    int k = rng() % 5;
    int unique = 0, longestK = 0, shortest = -1;
    long long atMost = 0, exactly = 0;
    for (int i = 0; i < n; ++i)
      for (int j = i + 1; j <= n; ++j) {
        std::string window = text.substr(i, j - i);
        int distinct = std::set<char>(window.begin(), window.end()).size();
        if (distinct == j - i)
          unique = std::max(unique, j - i);
        if (distinct <= k)
          longestK = std::max(longestK, j - i), atMost++;
        if (distinct == k)
          exactly++;
        if (covers(window, pattern) && (shortest < 0 || j - i < shortest))
          shortest = j - i;
      }
    std::string result = minWindow(text, pattern);
    assert(longestUniqueSubstring(text) == unique);
    assert((int)result.size() == std::max(shortest, 0));
    assert(result.empty() || covers(result, pattern));
    assert(text.find(result) != std::string::npos);
    assert(longestAtMostKDistinct(a, k) == longestK);
    assert(countAtMostKDistinct(a, k) == atMost);
    assert(countExactlyKDistinct(a, k) == exactly);
  }
  assert(longestUniqueSubstring("abcabcbb") == 3);
  assert(minWindow("ADOBECODEBANC", "ABC") == "BANC");
  assert(minWindow("a", "aa") == "");
  assert(longestAtMostKDistinct({1, 2, 3, 2, 2}, 2) == 4);
  assert(countExactlyKDistinct({1, 2, 1, 2, 3}, 2) == 7);
}
