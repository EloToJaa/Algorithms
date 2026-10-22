#include "Intervals.cpp"
#include <cassert>

// Doubled coordinates: the gap between x and x + 1 is the odd point 2x + 1.
std::vector<Interval> bruteMerge(const std::vector<Interval> &intervals) {
  std::vector<bool> covered(64);
  for (auto [start, end] : intervals)
    for (int p = 2 * start; p <= 2 * end; ++p)
      covered[p] = true;
  std::vector<Interval> result;
  for (int p = 0; p < 64; ++p) {
    if (!covered[p])
      continue;
    if (p > 0 && covered[p - 1])
      result.back().second = p / 2;
    else
      result.push_back({p / 2, p / 2});
  }
  return result;
}

int main() {
  std::mt19937 rng(3);
  for (int iteration = 0; iteration < 300; ++iteration) {
    int n = rng() % 8;
    std::vector<Interval> closed(n), open(n);
    for (auto &[s, e] : closed) {
      s = rng() % 15;
      e = s + rng() % 4;
    }
    for (auto &[s, e] : open) {
      s = rng() % 15;
      e = s + 1 + rng() % 5;
    }
    assert(mergeIntervals(closed) == bruteMerge(closed));
    auto disjoint = bruteMerge(closed);
    int start = rng() % 18;
    Interval added{start, start + int(rng() % 5)};
    auto withAdded = disjoint;
    withAdded.push_back(added);
    assert(insertInterval(disjoint, added) == bruteMerge(withAdded));

    int kept = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
      bool ok = true;
      for (int a = 0; a < n; ++a)
        for (int b = a + 1; b < n; ++b)
          if ((mask >> a & 1) && (mask >> b & 1) &&
              open[a].first < open[b].second && open[b].first < open[a].second)
            ok = false;
      if (ok)
        kept = std::max(kept, __builtin_popcount(mask));
    }
    assert(eraseOverlapIntervals(open) == n - kept);

    int rooms = 0;
    for (int t = 0; t < 25; ++t) {
      int active = 0;
      for (auto [s, e] : open)
        active += s <= t && t < e;
      rooms = std::max(rooms, active);
    }
    assert(minMeetingRooms(open) == rooms);
  }
  assert(mergeIntervals({{1, 3}, {2, 6}, {8, 10}, {15, 18}}) ==
         std::vector<Interval>({{1, 6}, {8, 10}, {15, 18}}));
  assert(insertInterval({{1, 3}, {6, 9}}, {2, 5}) ==
         std::vector<Interval>({{1, 5}, {6, 9}}));
  assert(eraseOverlapIntervals({{1, 2}, {2, 3}, {3, 4}, {1, 3}}) == 1);
  assert(minMeetingRooms({{0, 30}, {5, 10}, {15, 20}}) == 2);
}
