#include <bits/stdc++.h>

struct BridgesResult {
  std::vector<int> bridges, articulation;
};
BridgesResult
bridges_and_articulation_points(int n,
                                const std::vector<std::pair<int, int>> &edges) {
  std::vector<std::vector<std::pair<int, int>>> graph(n);
  for (int id = 0; id < static_cast<int>(edges.size()); ++id) {
    auto [a, b] = edges[id];
    graph[a].push_back({b, id});
    graph[b].push_back({a, id});
  }
  std::vector<int> entered(n, -1), low(n), parent(n, -1), parent_edge(n, -1),
      children(n);
  std::vector<bool> articulation(n), bridges(edges.size());
  BridgesResult result;
  int timer = 0;
  for (int root = 0; root < n; ++root) {
    if (entered[root] != -1)
      continue;
    entered[root] = low[root] = timer++;
    std::vector<std::pair<int, size_t>> stack = {{root, 0}};
    while (!stack.empty()) {
      int v = stack.back().first;
      size_t index = stack.back().second;
      if (index < graph[v].size()) {
        ++stack.back().second;
        auto [u, id] = graph[v][index];
        if (id == parent_edge[v])
          continue;
        if (entered[u] != -1) {
          low[v] = std::min(low[v], entered[u]);
          continue;
        }
        parent[u] = v;
        parent_edge[u] = id;
        ++children[v];
        entered[u] = low[u] = timer++;
        stack.push_back({u, 0});
        continue;
      }
      stack.pop_back();
      int p = parent[v];
      if (p == -1) {
        articulation[v] = children[v] > 1;
        continue;
      }
      low[p] = std::min(low[p], low[v]);
      if (low[v] > entered[p])
        bridges[parent_edge[v]] = true;
      if (parent[p] != -1 && low[v] >= entered[p])
        articulation[p] = true;
    }
  }
  for (int id = 0; id < static_cast<int>(edges.size()); ++id)
    if (bridges[id])
      result.bridges.push_back(id);
  for (int v = 0; v < n; ++v)
    if (articulation[v])
      result.articulation.push_back(v);
  return result;
}
