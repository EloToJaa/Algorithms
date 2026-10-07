#include <bits/stdc++.h>

struct BellmanFordEdge {
  int from, to;
  long long weight;
};
struct BellmanFordResult {
  std::vector<std::optional<long long>> distance;
  std::vector<int> parent;
  std::vector<bool> negative;
};
BellmanFordResult bellman_ford(int n, const std::vector<BellmanFordEdge> &edges,
                               int start) {
  if (start < 0 || start >= n)
    throw std::out_of_range("invalid source");
  std::vector<std::vector<int>> graph(n);
  for (const auto &edge : edges)
    graph[edge.from].push_back(edge.to);
  std::vector<std::optional<__int128>> distance(n);
  BellmanFordResult result{std::vector<std::optional<long long>>(n),
                           std::vector<int>(n, -1), std::vector<bool>(n)};
  distance[start] = 0;
  std::queue<int> queue;
  for (int iteration = 0; iteration < n; ++iteration) {
    bool changed = false;
    for (auto edge : edges) {
      if (!distance[edge.from])
        continue;
      __int128 candidate = *distance[edge.from] + edge.weight;
      if (distance[edge.to] && candidate >= *distance[edge.to])
        continue;
      distance[edge.to] = candidate;
      result.parent[edge.to] = edge.from;
      changed = true;
      if (iteration == n - 1 && !result.negative[edge.to]) {
        result.negative[edge.to] = true;
        queue.push(edge.to);
      }
    }
    if (!changed)
      break;
  }
  while (!queue.empty()) {
    int v = queue.front();
    queue.pop();
    for (int u : graph[v]) {
      if (result.negative[u])
        continue;
      result.negative[u] = true;
      queue.push(u);
    }
  }
  for (int v = 0; v < n; ++v) {
    if (result.negative[v]) {
      result.parent[v] = -1;
      continue;
    }
    if (!distance[v])
      continue;
    if (*distance[v] < LLONG_MIN || *distance[v] > LLONG_MAX)
      throw std::overflow_error("finite distance outside long long");
    result.distance[v] = static_cast<long long>(*distance[v]);
  }
  return result;
}
