#include <bits/stdc++.h>

const long long heldKarpInf = LLONG_MAX / 4;

// Minimum Hamiltonian cycle through 0; cost entries >= heldKarpInf mean no
// edge. Returns heldKarpInf if no cycle exists and 0 for n <= 1.
long long heldKarp(const std::vector<std::vector<long long>> &cost) {
  int n = cost.size();
  if (n <= 1)
    return 0;
  int full = (1 << n) - 1;
  // best[mask][last]: cheapest path 0 -> ... -> last visiting exactly mask.
  std::vector<std::vector<long long>> best(
      1 << n, std::vector<long long>(n, heldKarpInf));
  best[1][0] = 0;
  for (int mask = 1; mask <= full; mask += 2)
    for (int last = 0; last < n; ++last) {
      long long here = best[mask][last];
      if (here >= heldKarpInf)
        continue;
      for (int next = 0; next < n; ++next) {
        if (mask >> next & 1 || cost[last][next] >= heldKarpInf)
          continue;
        long long &target = best[mask | 1 << next][next];
        target = std::min(target, here + cost[last][next]);
      }
    }
  long long answer = heldKarpInf;
  for (int last = 1; last < n; ++last)
    if (best[full][last] < heldKarpInf && cost[last][0] < heldKarpInf)
      answer = std::min(answer, best[full][last] + cost[last][0]);
  return answer;
}

// Split positive nums into k >= 1 groups of equal sum.
bool canPartitionKSubsets(const std::vector<int> &nums, int k) {
  long long total = std::accumulate(nums.begin(), nums.end(), 0LL);
  if (total % k)
    return false;
  long long target = total / k;
  for (int value : nums)
    if (value > target)
      return false;
  int n = nums.size();
  // filled[mask]: sum of the open bucket after placing mask, -1 if unreachable.
  std::vector<long long> filled(1 << n, -1);
  filled[0] = 0;
  for (int mask = 0; mask < (1 << n); ++mask) {
    if (filled[mask] < 0)
      continue;
    for (int i = 0; i < n; ++i) {
      int next = mask | 1 << i;
      if (next == mask || filled[next] >= 0 || filled[mask] + nums[i] > target)
        continue;
      filled[next] = (filled[mask] + nums[i]) % target;
    }
  }
  return filled[(1 << n) - 1] == 0;
}

// Fewest edges of a walk visiting every vertex; -1 if impossible, 0 if n <= 1.
int shortestPathVisitingAllNodes(const std::vector<std::vector<int>> &graph) {
  int n = graph.size();
  if (n <= 1)
    return 0;
  int full = (1 << n) - 1;
  std::vector<std::vector<int>> distance(n, std::vector<int>(1 << n, -1));
  std::queue<std::pair<int, int>> queue;
  for (int start = 0; start < n; ++start) {
    distance[start][1 << start] = 0;
    queue.push({start, 1 << start});
  }
  while (!queue.empty()) {
    auto [vertex, mask] = queue.front();
    queue.pop();
    for (int neighbor : graph[vertex]) {
      int next = mask | 1 << neighbor;
      if (next == full)
        return distance[vertex][mask] + 1;
      if (distance[neighbor][next] >= 0)
        continue;
      distance[neighbor][next] = distance[vertex][mask] + 1;
      queue.push({neighbor, next});
    }
  }
  return -1;
}
