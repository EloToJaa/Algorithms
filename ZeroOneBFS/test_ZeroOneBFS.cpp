#include "ZeroOneBFS.cpp"
#include <cassert>

int main() {
  std::mt19937 rng(24);
  for (int n = 1; n < 30; ++n) {
    std::vector<std::vector<std::pair<int, int>>> graph(n);
    for (int v = 0; v < n; ++v)
      for (int u = 0; u < n; ++u)
        if (rng() % 7 == 0)
          graph[v].push_back({u, rng() % 2});
    graph[0].push_back({0, 0});
    graph[0].push_back({0, 1});
    for (int start : {0, n - 1}) {
      std::vector<int> expected(n, INT_MAX);
      expected[start] = 0;
      for (int pass = 1; pass < n; ++pass)
        for (int v = 0; v < n; ++v)
          for (auto [u, weight] : graph[v])
            if (expected[v] != INT_MAX)
              expected[u] = std::min(expected[u], expected[v] + weight);
      auto result = zero_one_bfs(graph, start);
      assert(result.distance == expected);
      for (int v = 0; v < n; ++v) {
        if (v == start || expected[v] == INT_MAX) {
          assert(result.parent[v] == -1);
          continue;
        }
        int p = result.parent[v];
        bool found = false;
        for (auto [u, w] : graph[p])
          if (u == v && expected[p] + w == expected[v])
            found = true;
        assert(found);
        int current = v, steps = 0;
        while (current != start) {
          assert(current >= 0 && ++steps <= n);
          current = result.parent[current];
        }
      }
    }
  }
  bool rejected = false;
  try {
    zero_one_bfs({}, 0);
  } catch (const std::out_of_range &) {
    rejected = true;
  }
  assert(rejected);
  rejected = false;
  try {
    zero_one_bfs({{}, {{0, 2}}}, 0);
  } catch (const std::invalid_argument &) {
    rejected = true;
  }
  assert(rejected);
  rejected = false;
  try {
    zero_one_bfs({{{0, -1}}}, 0);
  } catch (const std::invalid_argument &) {
    rejected = true;
  }
  assert(rejected);
}
