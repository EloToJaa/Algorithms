#include "LCS.cpp"
#include <cassert>

bool isSubsequence(const std::string &candidate, const std::string &text) {
  size_t i = 0;
  for (char c : text)
    if (i < candidate.size() && candidate[i] == c)
      ++i;
  return i == candidate.size();
}

int main() {
  std::mt19937 rng(5);
  for (int iteration = 0; iteration < 200; ++iteration) {
    std::string a(rng() % 8, 'a'), b(rng() % 8, 'a');
    for (char &c : a)
      c = 'a' + rng() % 3;
    for (char &c : b)
      c = 'a' + rng() % 3;
    int expected = 0;
    for (int mask = 0; mask < (1 << a.size()); ++mask) {
      std::string chosen;
      for (size_t i = 0; i < a.size(); ++i)
        if (mask >> i & 1)
          chosen.push_back(a[i]);
      if (isSubsequence(chosen, b))
        expected = std::max(expected, int(chosen.size()));
    }
    std::string common = lcs(a, b);
    assert(lcsLength(a, b) == expected);
    assert(int(common.size()) == expected);
    assert(isSubsequence(common, a) && isSubsequence(common, b));
  }
  assert(lcs("abcde", "ace") == "ace");
  assert(lcsLength("abc", "def") == 0);
}
