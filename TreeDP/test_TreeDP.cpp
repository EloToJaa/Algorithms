#include "TreeDP.cpp"
#include <cassert>

int main() {
  std::mt19937 rng(9);
  for (int iteration = 0; iteration < 200; ++iteration) {
    int n = 1 + rng() % 9;
    std::vector<int> labels(n);
    std::iota(labels.begin(), labels.end(), 0);
    std::shuffle(labels.begin(), labels.end(), rng);
    std::vector<std::pair<int, int>> edges;
    std::vector<std::vector<int>> graph(n);
    for (int i = 1; i < n; ++i) {
      int a = labels[i], b = labels[rng() % i];
      edges.push_back(rng() % 2 ? std::make_pair(a, b) : std::make_pair(b, a));
      graph[a].push_back(b), graph[b].push_back(a);
    }
    std::vector<long long> values(n);
    for (auto &value : values)
      value = int(rng() % 21) - 10;

    int diameter = 0;
    long long pathSum = LLONG_MIN;
    std::vector<long long> distances(n, 0);
    for (int s = 0; s < n; ++s) {
      std::vector<int> parent(n, -2), depth(n, 0);
      std::queue<int> queue;
      parent[s] = -1, queue.push(s);
      while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        for (int u : graph[v])
          if (parent[u] == -2)
            parent[u] = v, depth[u] = depth[v] + 1, queue.push(u);
      }
      for (int t = 0; t < n; ++t) {
        diameter = std::max(diameter, depth[t]);
        distances[s] += depth[t];
        long long sum = 0;
        for (int v = t; v >= 0; v = parent[v])
          sum += values[v];
        pathSum = std::max(pathSum, sum);
      }
    }
    long long independent = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
      bool valid = true;
      for (auto [a, b] : edges)
        valid &= !((mask >> a & 1) && (mask >> b & 1));
      if (!valid)
        continue;
      long long sum = 0;
      for (int v = 0; v < n; ++v)
        if (mask >> v & 1)
          sum += values[v];
      independent = std::max(independent, sum);
    }
    assert(treeDiameter(n, edges) == diameter);
    assert(maxPathSum(values, edges) == pathSum);
    assert(sumOfDistances(n, edges) == distances);
    assert(maxIndependentSet(values, edges) == independent);
  }
  assert(maxPathSum({-10, 9, 20, 15, 7}, {{0, 1}, {0, 2}, {2, 3}, {2, 4}}) ==
         42);
  assert(maxIndependentSet({3, 2, 3, 3, 1}, {{0, 1}, {0, 2}, {1, 3}, {2, 4}}) ==
         7);
  assert(sumOfDistances(6, {{0, 1}, {0, 2}, {2, 3}, {2, 4}, {2, 5}}) ==
         std::vector<long long>({8, 12, 6, 10, 10, 10}));
  assert(treeDiameter(1, {}) == 0 && maxPathSum({-3}, {}) == -3);
  int n = 200000;
  std::vector<std::pair<int, int>> line;
  for (int i = 0; i + 1 < n; ++i)
    line.push_back({i, i + 1});
  assert(treeDiameter(n, line) == n - 1);
}
