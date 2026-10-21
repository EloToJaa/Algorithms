#include <bits/stdc++.h>

struct PrimEdge {
  int a, b;
  long long w;
};
struct PrimResult {
  long long totalWeight = 0;
  std::vector<PrimEdge> selected;
};
PrimResult
prim(const std::vector<std::vector<std::pair<int, long long>>> &graph) {
  int n = graph.size();
  PrimResult result;
  std::vector<bool> visited(n, false);
  using Entry = std::tuple<long long, int, int>;
  std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>> queue;
  for (int root = 0; root < n; ++root) {
    if (visited[root])
      continue;
    queue.push({0, root, -1});
    while (!queue.empty()) {
      auto [weight, v, parent] = queue.top();
      queue.pop();
      if (visited[v])
        continue;
      visited[v] = true;
      if (parent != -1) {
        result.selected.push_back({parent, v, weight});
        result.totalWeight += weight;
      }
      for (auto [u, cost] : graph[v])
        if (!visited[u])
          queue.push({cost, u, v});
    }
  }
  return result;
}
