#include <bits/stdc++.h>

struct ZeroOneBFSResult {
  std::vector<int> distance, parent;
};
ZeroOneBFSResult
zero_one_bfs(const std::vector<std::vector<std::pair<int, int>>> &graph,
             int start) {
  int n = graph.size();
  if (start < 0 || start >= n)
    throw std::out_of_range("invalid source");
  for (const auto &edges : graph)
    for (auto [u, weight] : edges)
      if (weight != 0 && weight != 1)
        throw std::invalid_argument("weights must be zero or one");
  ZeroOneBFSResult result{std::vector<int>(n, INT_MAX),
                          std::vector<int>(n, -1)};
  result.distance[start] = 0;
  std::deque<std::pair<int, int>> queue = {{0, start}};
  while (!queue.empty()) {
    auto [cost, v] = queue.front();
    queue.pop_front();
    if (cost != result.distance[v])
      continue;
    for (auto [u, weight] : graph[v]) {
      int candidate = cost + weight;
      if (candidate >= result.distance[u])
        continue;
      result.distance[u] = candidate;
      result.parent[u] = v;
      if (weight)
        queue.push_back({candidate, u});
      else
        queue.push_front({candidate, u});
    }
  }
  return result;
}
