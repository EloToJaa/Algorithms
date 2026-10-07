#include "Bridges.cpp"
#include <cassert>

int component_count(int n, const std::vector<std::pair<int, int>> &edges,
                    int removed_edge = -1, int removed_vertex = -1) {
  std::vector<std::vector<int>> graph(n);
  for (int id = 0; id < static_cast<int>(edges.size()); ++id) {
    auto [a, b] = edges[id];
    if (id == removed_edge || a == removed_vertex || b == removed_vertex)
      continue;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }
  std::vector<bool> seen(n);
  if (removed_vertex != -1)
    seen[removed_vertex] = true;
  int count = 0;
  for (int start = 0; start < n; ++start) {
    if (seen[start])
      continue;
    ++count;
    seen[start] = true;
    std::vector<int> stack = {start};
    while (!stack.empty()) {
      int v = stack.back();
      stack.pop_back();
      for (int u : graph[v])
        if (!seen[u]) {
          seen[u] = true;
          stack.push_back(u);
        }
    }
  }
  return count;
}
int main() {
  std::mt19937 rng(26);
  for (int n = 0; n < 10; ++n)
    for (int trial = 0; trial < 30; ++trial) {
      std::vector<std::pair<int, int>> edges;
      if (n)
        for (int m = rng() % 20; m > 0; --m)
          edges.push_back({rng() % n, rng() % n});
      int baseline = component_count(n, edges);
      std::vector<int> bridges, points;
      for (int id = 0; id < static_cast<int>(edges.size()); ++id)
        if (component_count(n, edges, id) > baseline)
          bridges.push_back(id);
      for (int v = 0; v < n; ++v)
        if (component_count(n, edges, -1, v) > baseline)
          points.push_back(v);
      auto result = bridges_and_articulation_points(n, edges);
      assert(result.bridges == bridges && result.articulation == points);
    }
  auto result =
      bridges_and_articulation_points(3, {{0, 1}, {0, 1}, {1, 2}, {1, 1}});
  assert((result.bridges == std::vector<int>{2} &&
          result.articulation == std::vector<int>{1}));
  result = bridges_and_articulation_points(3, {{0, 1}, {0, 2}});
  assert((result.articulation == std::vector<int>{0}));
  std::vector<std::pair<int, int>> chain;
  for (int v = 0; v < 4999; ++v)
    chain.push_back({v, v + 1});
  result = bridges_and_articulation_points(5000, chain);
  assert(result.bridges.size() == 4999 && result.articulation.size() == 4998);
  for (int i = 0; i < 4999; ++i)
    assert(result.bridges[i] == i);
  for (int i = 0; i < 4998; ++i)
    assert(result.articulation[i] == i + 1);
}
