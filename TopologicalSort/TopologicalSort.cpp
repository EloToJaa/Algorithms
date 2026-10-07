#include <bits/stdc++.h>

std::vector<int> topological_sort(const std::vector<std::vector<int>> &graph) {
  std::vector<int> indegree(graph.size()), order;
  for (const auto &edges : graph)
    for (int u : edges)
      ++indegree[u];
  std::queue<int> queue;
  for (int v = 0; v < static_cast<int>(graph.size()); ++v)
    if (indegree[v] == 0)
      queue.push(v);
  while (!queue.empty()) {
    int v = queue.front();
    queue.pop();
    order.push_back(v);
    for (int u : graph[v])
      if (--indegree[u] == 0)
        queue.push(u);
  }
  if (order.size() != graph.size())
    throw std::domain_error("directed cycle");
  return order;
}
