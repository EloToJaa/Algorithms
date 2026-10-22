#include <bits/stdc++.h>

using Interval = std::pair<int, int>;

// Closed [first, second] intervals; touching ones merge.
std::vector<Interval> mergeIntervals(std::vector<Interval> intervals) {
  std::sort(intervals.begin(), intervals.end());
  std::vector<Interval> merged;
  for (auto [start, end] : intervals) {
    if (!merged.empty() && start <= merged.back().second) {
      merged.back().second = std::max(merged.back().second, end);
      continue;
    }
    merged.push_back({start, end});
  }
  return merged;
}

// Insert into sorted disjoint closed intervals; touching ones merge.
std::vector<Interval> insertInterval(const std::vector<Interval> &intervals,
                                     Interval added) {
  std::vector<Interval> result;
  size_t i = 0, n = intervals.size();
  while (i < n && intervals[i].second < added.first)
    result.push_back(intervals[i++]);
  for (; i < n && intervals[i].first <= added.second; ++i) {
    added.first = std::min(added.first, intervals[i].first);
    added.second = std::max(added.second, intervals[i].second);
  }
  result.push_back(added);
  result.insert(result.end(), intervals.begin() + i, intervals.end());
  return result;
}

// Fewest removals leaving half-open [first, second) intervals disjoint.
int eraseOverlapIntervals(std::vector<Interval> intervals) {
  std::sort(
      intervals.begin(), intervals.end(),
      [](const Interval &a, const Interval &b) { return a.second < b.second; });
  int kept = 0;
  long long lastEnd = LLONG_MIN;
  for (auto [start, end] : intervals) {
    if (start < lastEnd)
      continue;
    ++kept;
    lastEnd = end;
  }
  return intervals.size() - kept;
}

// Rooms needed for half-open [first, second) meetings.
int minMeetingRooms(std::vector<Interval> intervals) {
  std::sort(intervals.begin(), intervals.end());
  std::priority_queue<int, std::vector<int>, std::greater<int>> ends;
  for (auto [start, end] : intervals) {
    if (!ends.empty() && ends.top() <= start)
      ends.pop();
    ends.push(end);
  }
  return ends.size();
}
