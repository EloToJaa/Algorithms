#include "../Kruskal/Kruskal.cpp"
#include "Prim.cpp"
#include <cassert>

int main() {
  std::mt19937 rng(11);
  for (int iteration = 0; iteration < 200; ++iteration) {
    int n = rng() % 12, m = n ? rng() % 30 : 0;
    std::vector<std::vector<std::pair<int, long long>>> graph(n);
    for (int i = 1; i <= m; ++i) {
      int a = rng() % n, b = rng() % n, w = int(rng() % 15) - 5;
      graph[a].push_back({b, w});
      graph[b].push_back({a, w});
      K[i] = {a + 1, b + 1, w};
    }
    auto result = prim(graph);
    Kruskal(n, m);
    assert(result.totalWeight == totalWeight);
    assert(result.selected.size() == selected.size());
    long long sum = 0;
    for (auto [a, b, w] : result.selected) {
      sum += w;
      bool found = false;
      for (auto [u, cost] : graph[a])
        if (u == b && cost == w)
          found = true;
      assert(found);
    }
    assert(sum == result.totalWeight);
  }
  auto empty = prim({});
  assert(empty.totalWeight == 0 && empty.selected.empty());
  auto forest = prim({{{1, 2}, {2, 8}, {0, -20}},
                      {{0, 2}, {2, -1}},
                      {{1, -1}, {0, 8}},
                      {}});
  assert(forest.totalWeight == 1 && forest.selected.size() == 2);
}
