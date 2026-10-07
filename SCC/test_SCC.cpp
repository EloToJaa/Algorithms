#include "SCC.cpp"
#include <cassert>

int main() {
  std::mt19937 rng(22);
  for (int n = 0; n < 15; ++n)
    for (int trial = 0; trial < 12; ++trial) {
      std::vector<std::vector<int>> graph(n);
      std::vector<std::vector<bool>> reach(n, std::vector<bool>(n));
      for (int v = 0; v < n; ++v) {
        reach[v][v] = true;
        for (int u = 0; u < n; ++u)
          if (rng() % 5 == 0) {
            graph[v].push_back(u);
            reach[v][u] = true;
          }
      }
      for (int k = 0; k < n; ++k)
        for (int v = 0; v < n; ++v)
          for (int u = 0; u < n; ++u)
            reach[v][u] = reach[v][u] || (reach[v][k] && reach[k][u]);
      auto result = strongly_connected_components(graph);
      std::vector<int> members;
      for (int id = 0; id < static_cast<int>(result.groups.size()); ++id)
        for (int v : result.groups[id]) {
          assert(result.component[v] == id);
          members.push_back(v);
        }
      std::sort(members.begin(), members.end());
      assert(members.size() == graph.size());
      for (int v = 0; v < n; ++v) {
        assert(members[v] == v);
        for (int u = 0; u < n; ++u)
          assert((result.component[v] == result.component[u]) ==
                 (reach[v][u] && reach[u][v]));
        for (int u : graph[v])
          assert(result.component[v] <= result.component[u]);
      }
    }
  std::vector<std::vector<int>> graph(5000);
  for (int v = 0; v < 4999; ++v)
    graph[v].push_back(v + 1);
  auto result = strongly_connected_components(graph);
  for (int v = 0; v < 5000; ++v)
    assert(result.component[v] == v);
  graph.back().push_back(0);
  assert(strongly_connected_components(graph).groups.size() == 1);
}
