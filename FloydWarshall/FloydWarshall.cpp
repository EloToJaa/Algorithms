#include <bits/stdc++.h>

// Unreachable is floydInf; unbounded (through a negative cycle) is -floydInf.
const long long floydInf = LLONG_MAX / 4;

struct FloydWarshallEdge {
  int from, to;
  long long weight;
};
struct FloydWarshallResult {
  std::vector<std::vector<long long>> dist;
  std::vector<std::vector<int>> next; // vertex after i on a path, -1 if none
};

FloydWarshallResult floydWarshall(int n,
                                  const std::vector<FloydWarshallEdge> &edges) {
  FloydWarshallResult result{
      std::vector<std::vector<long long>>(n,
                                          std::vector<long long>(n, floydInf)),
      std::vector<std::vector<int>>(n, std::vector<int>(n, -1))};
  auto &dist = result.dist;
  auto &next = result.next;
  for (int v = 0; v < n; ++v)
    dist[v][v] = 0, next[v][v] = v;
  for (auto [u, v, w] : edges)
    if (w < dist[u][v])
      dist[u][v] = w, next[u][v] = v;
  for (int k = 0; k < n; ++k)
    for (int i = 0; i < n; ++i) {
      if (dist[i][k] == floydInf)
        continue;
      for (int j = 0; j < n; ++j) {
        if (dist[k][j] == floydInf)
          continue;
        // Both terms lie in [-floydInf, floydInf), so the sum cannot overflow;
        // clamping keeps values bounded when negative cycles compound.
        long long candidate = std::max(-floydInf, dist[i][k] + dist[k][j]);
        if (candidate < dist[i][j])
          dist[i][j] = candidate, next[i][j] = next[i][k];
      }
    }
  std::vector<int> cycle;
  for (int k = 0; k < n; ++k)
    if (dist[k][k] < 0)
      cycle.push_back(k);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      for (int k : cycle)
        if (dist[i][k] < floydInf && dist[k][j] < floydInf) {
          dist[i][j] = -floydInf;
          break;
        }
  return result;
}

// Vertices lying on a negative closed walk (dist[v][v] == -floydInf).
std::vector<int>
negativeCycleVertices(const std::vector<std::vector<long long>> &dist) {
  std::vector<int> vertices;
  for (int v = 0; v < int(dist.size()); ++v)
    if (dist[v][v] == -floydInf)
      vertices.push_back(v);
  return vertices;
}

// Shortest start -> end path; empty if unreachable or unbounded.
std::vector<int> reconstructPath(const FloydWarshallResult &result, int start,
                                 int end) {
  long long d = result.dist[start][end];
  if (d == floydInf || d == -floydInf)
    return {};
  std::vector<int> path = {start};
  while (start != end) {
    start = result.next[start][end];
    path.push_back(start);
  }
  return path;
}
