#include "FloydWarshall.cpp"
#include <cassert>

std::vector<long long>
bellmanFordRow(int n, const std::vector<FloydWarshallEdge> &edges, int source) {
  std::vector<long long> dist(n, floydInf);
  dist[source] = 0;
  for (int round = 0; round < n - 1; ++round)
    for (auto [u, v, w] : edges)
      if (dist[u] < floydInf && dist[u] + w < dist[v])
        dist[v] = dist[u] + w;
  for (int round = 0; round < n; ++round)
    for (auto [u, v, w] : edges)
      if (dist[u] < floydInf && (dist[u] == -floydInf || dist[u] + w < dist[v]))
        dist[v] = -floydInf;
  return dist;
}

int main() {
  std::mt19937 rng(12);
  for (int iteration = 0; iteration < 300; ++iteration) {
    int n = 1 + rng() % 6;
    std::vector<FloydWarshallEdge> edges(rng() % 12);
    std::map<std::pair<int, int>, long long> weight;
    for (auto &edge : edges) {
      edge = {int(rng() % n), int(rng() % n), (long long)(rng() % 13) - 3};
      auto key = std::make_pair(edge.from, edge.to);
      weight[key] =
          weight.count(key) ? std::min(weight[key], edge.weight) : edge.weight;
    }
    auto result = floydWarshall(n, edges);
    std::vector<int> negative;
    for (int s = 0; s < n; ++s) {
      assert(result.dist[s] == bellmanFordRow(n, edges, s));
      if (result.dist[s][s] == -floydInf)
        negative.push_back(s);
    }
    assert(negativeCycleVertices(result.dist) == negative);
    for (int s = 0; s < n; ++s)
      for (int t = 0; t < n; ++t) {
        auto path = reconstructPath(result, s, t);
        long long d = result.dist[s][t];
        if (d == floydInf || d == -floydInf) {
          assert(path.empty());
          continue;
        }
        assert(path.front() == s && path.back() == t);
        long long total = 0;
        for (size_t i = 0; i + 1 < path.size(); ++i)
          total += weight.at({path[i], path[i + 1]});
        assert(total == d);
      }
  }
  auto result =
      floydWarshall(4, {{0, 1, 3}, {1, 2, 1}, {0, 2, 5}, {2, 3, 2}, {3, 0, 2}});
  assert(result.dist[0] == std::vector<long long>({0, 3, 4, 6}));
  assert(reconstructPath(result, 0, 3) == std::vector<int>({0, 1, 2, 3}));
  result = floydWarshall(3, {{0, 1, 1}, {1, 1, -1}, {2, 0, 1}});
  assert(result.dist[0][1] == -floydInf && result.dist[0][2] == floydInf);
  assert(negativeCycleVertices(result.dist) == std::vector<int>({1}));
  assert(reconstructPath(result, 0, 1).empty());
  // Compounding negative cycles stay clamped instead of overflowing.
  std::vector<FloydWarshallEdge> big;
  for (int v = 0; v < 60; ++v)
    big.push_back({v, (v + 1) % 60, -(1LL << 40)});
  result = floydWarshall(60, big);
  assert(negativeCycleVertices(result.dist).size() == 60);
}
