#include <bits/stdc++.h>

struct SCCResult {
  std::vector<int> component;
  std::vector<std::vector<int>> groups;
};
SCCResult
strongly_connected_components(const std::vector<std::vector<int>> &graph) {
  int n = graph.size();
  std::vector<std::vector<int>> reverse(n);
  for (int v = 0; v < n; ++v)
    for (int u : graph[v])
      reverse[u].push_back(v);
  std::vector<bool> seen(n);
  std::vector<int> order;
  for (int start = 0; start < n; ++start) {
    if (seen[start])
      continue;
    seen[start] = true;
    std::vector<std::pair<int, size_t>> stack = {{start, 0}};
    while (!stack.empty()) {
      int v = stack.back().first;
      size_t index = stack.back().second;
      if (index == graph[v].size()) {
        order.push_back(v);
        stack.pop_back();
        continue;
      }
      ++stack.back().second;
      int u = graph[v][index];
      if (seen[u])
        continue;
      seen[u] = true;
      stack.push_back({u, 0});
    }
  }
  SCCResult result;
  result.component.assign(n, -1);
  for (auto it = order.rbegin(); it != order.rend(); ++it) {
    int start = *it;
    if (result.component[start] != -1)
      continue;
    int id = result.groups.size();
    result.groups.push_back({});
    result.component[start] = id;
    std::vector<int> stack = {start};
    while (!stack.empty()) {
      int v = stack.back();
      stack.pop_back();
      result.groups[id].push_back(v);
      for (int u : reverse[v]) {
        if (result.component[u] != -1)
          continue;
        result.component[u] = id;
        stack.push_back(u);
      }
    }
  }
  return result;
}
