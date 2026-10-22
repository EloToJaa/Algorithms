#include <bits/stdc++.h>

// Length of the longest substring with no repeated character.
int longestUniqueSubstring(const std::string &s) {
  std::vector<int> last(256, -1);
  int best = 0, left = 0;
  for (int right = 0; right < (int)s.size(); ++right) {
    unsigned char c = s[right];
    left = std::max(left, last[c] + 1);
    last[c] = right;
    best = std::max(best, right - left + 1);
  }
  return best;
}

// Shortest substring of text containing pattern with multiplicity, or "".
std::string minWindow(const std::string &text, const std::string &pattern) {
  if (pattern.empty())
    return "";
  std::vector<int> need(256, 0);
  for (unsigned char c : pattern)
    need[c]++;
  int missing = pattern.size(), start = 0, len = -1, left = 0;
  for (int right = 0; right < (int)text.size(); ++right) {
    if (need[(unsigned char)text[right]]-- > 0)
      missing--;
    if (missing)
      continue;
    while (need[(unsigned char)text[left]] < 0)
      need[(unsigned char)text[left++]]++;
    if (len < 0 || right - left + 1 < len)
      start = left, len = right - left + 1;
    need[(unsigned char)text[left++]]++;
    missing++;
  }
  return len < 0 ? "" : text.substr(start, len);
}

// Shared template: for each right, the smallest left with <= k distinct.
template <typename F>
void atMostKDistinctWindows(const std::vector<int> &a, int k, F onWindow) {
  std::unordered_map<int, int> counts;
  int left = 0;
  for (int right = 0; right < (int)a.size(); ++right) {
    counts[a[right]]++;
    for (; (int)counts.size() > k; ++left)
      if (--counts[a[left]] == 0)
        counts.erase(a[left]);
    onWindow(left, right);
  }
}

// Length of the longest subarray with at most k distinct values.
int longestAtMostKDistinct(const std::vector<int> &a, int k) {
  int best = 0;
  atMostKDistinctWindows(
      a, k, [&](int l, int r) { best = std::max(best, r - l + 1); });
  return best;
}

// Number of subarrays with at most k distinct values.
long long countAtMostKDistinct(const std::vector<int> &a, int k) {
  long long total = 0;
  atMostKDistinctWindows(a, k, [&](int l, int r) { total += r - l + 1; });
  return total;
}

// Number of subarrays with exactly k distinct values.
long long countExactlyKDistinct(const std::vector<int> &a, int k) {
  if (k <= 0)
    return 0;
  return countAtMostKDistinct(a, k) - countAtMostKDistinct(a, k - 1);
}
