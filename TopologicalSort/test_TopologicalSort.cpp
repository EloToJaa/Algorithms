#include "TopologicalSort.cpp"
#include <cassert>

int main() {
  std::mt19937 rng(20);
  for (int n = 0; n < 40; ++n) {
    std::vector<int> permutation(n);
    std::iota(permutation.begin(), permutation.end(), 0);
    std::shuffle(permutation.begin(), permutation.end(), rng);
    std::vector<std::vector<int>> graph(n);
    for (int i = 0; i < n; ++i)
      for (int j = i + 1; j < n; ++j)
        if (rng() % 5 == 0)
          graph[permutation[i]].push_back(permutation[j]);
    auto order = topological_sort(graph);
    assert(order.size() == graph.size());
    auto sorted = order;
    std::sort(sorted.begin(), sorted.end());
    std::vector<int> position(n);
    for (int i = 0; i < n; ++i) {
      assert(sorted[i] == i);
      position[order[i]] = i;
    }
    for (int v = 0; v < n; ++v)
      for (int u : graph[v])
        assert(position[v] < position[u]);
  }
  assert((topological_sort({{1, 1}, {}}) == std::vector<int>{0, 1}));
  for (auto graph : std::vector<std::vector<std::vector<int>>>{
           {{0}}, {{1}, {0}}, {{}, {2}, {1}}}) {
    bool rejected = false;
    try {
      topological_sort(graph);
    } catch (const std::domain_error &) {
      rejected = true;
    }
    assert(rejected);
  }
  std::vector<std::vector<int>> chain(5000);
  for (int i = 0; i < 4999; ++i)
    chain[i].push_back(i + 1);
  auto order = topological_sort(chain);
  for (int i = 0; i < 5000; ++i)
    assert(order[i] == i);
}
