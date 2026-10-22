#include "EditDistance.cpp"
#include <cassert>

int bruteDistance(const std::string &a, const std::string &b) {
  if (a.empty() || b.empty())
    return a.size() + b.size();
  std::string restA = a.substr(1), restB = b.substr(1);
  if (a[0] == b[0])
    return bruteDistance(restA, restB);
  return 1 + std::min({bruteDistance(restA, restB), bruteDistance(restA, b),
                       bruteDistance(a, restB)});
}

int main() {
  std::mt19937 rng(9);
  for (int iteration = 0; iteration < 300; ++iteration) {
    std::string a(rng() % 7, 'a'), b(rng() % 7, 'a');
    for (char &c : a)
      c = 'a' + rng() % 3;
    for (char &c : b)
      c = 'a' + rng() % 3;
    int expected = bruteDistance(a, b);
    assert(editDistance(a, b) == expected);
    assert(editDistanceTable(a, b)[a.size()][b.size()] == expected);

    std::string consumed, produced;
    int edits = 0;
    for (auto [type, from, to] : editOperations(a, b)) {
      edits += type != 'K';
      if (type == 'K')
        assert(from == to);
      if (type == 'R')
        assert(from != to);
      if (type != 'I')
        consumed.push_back(from);
      if (type != 'D')
        produced.push_back(to);
    }
    assert(consumed == a && produced == b && edits == expected);
  }
  assert(editDistance("horse", "ros") == 3);
  assert(editDistance("intention", "execution") == 5);
  assert(editDistance("", "abc") == 3);
}
