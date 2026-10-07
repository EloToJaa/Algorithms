#include "BellmanFord.cpp"
#include <cassert>

int main() {
  std::mt19937 rng(25);
  const long long inf = 1000000000000LL;
  for (int n = 1; n < 10; ++n)
    for (int trial = 0; trial < 20; ++trial) {
      std::vector<BellmanFordEdge> edges;
      std::vector<std::vector<long long>> matrix(
          n, std::vector<long long>(n, inf));
      for (int v = 0; v < n; ++v)
        matrix[v][v] = 0;
      for (int v = 0; v < n; ++v)
        for (int u = 0; u < n; ++u)
          if (rng() % 5 == 0) {
            long long w = static_cast<int>(rng() % 13) - 5;
            edges.push_back({v, u, w});
            matrix[v][u] = std::min(matrix[v][u], w);
          }
      for (int k = 0; k < n; ++k)
        for (int v = 0; v < n; ++v)
          for (int u = 0; u < n; ++u)
            if (matrix[v][k] != inf && matrix[k][u] != inf)
              matrix[v][u] =
                  std::min(matrix[v][u], matrix[v][k] + matrix[k][u]);
      for (int start : {0, n - 1}) {
        auto result = bellman_ford(n, edges, start);
        for (int v = 0; v < n; ++v) {
          bool negative = false;
          for (int k = 0; k < n; ++k)
            if (matrix[start][k] != inf && matrix[k][k] < 0 &&
                matrix[k][v] != inf)
              negative = true;
          assert(result.negative[v] == negative);
          if (negative || matrix[start][v] == inf) {
            assert(!result.distance[v]);
            assert(result.parent[v] == -1);
            continue;
          }
          assert(result.distance[v] && *result.distance[v] == matrix[start][v]);
          if (v == start)
            continue;
          bool found = false;
          for (auto edge : edges)
            if (edge.to == v && edge.from == result.parent[v] &&
                result.distance[edge.from] &&
                *result.distance[edge.from] + edge.weight ==
                    *result.distance[v])
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
  auto result = bellman_ford(
      5, {{0, 1, 2}, {1, 2, -2}, {2, 1, 1}, {2, 3, 5}, {4, 4, -1}}, 0);
  assert(
      (result.negative == std::vector<bool>{false, true, true, true, false}));
  assert(result.distance[0] == 0 && !result.distance[4]);
  // Intermediate path sums may exceed long long; affected vertices have no
  // finite distance.
  result = bellman_ford(2, {{0, 1, LLONG_MIN}, {1, 1, -1}}, 0);
  assert(result.negative[1]);
  result = bellman_ford(2, {{0, 1, LLONG_MAX}}, 0);
  assert(result.distance[1] == LLONG_MAX);
  result = bellman_ford(2, {{0, 1, LLONG_MIN}}, 0);
  assert(result.distance[1] == LLONG_MIN);
  bool rejected = false;
  try {
    bellman_ford(3, {{0, 1, LLONG_MAX}, {1, 2, 1}}, 0);
  } catch (const std::overflow_error &) {
    rejected = true;
  }
  assert(rejected);
  rejected = false;
  try {
    bellman_ford(0, {}, 0);
  } catch (const std::out_of_range &) {
    rejected = true;
  }
  assert(rejected);
}
