#include <bits/stdc++.h>

// Iterative DFS preorder from 0; parent[0] = -1.
std::vector<int> treeOrder(int n, const std::vector<std::pair<int, int>> &edges,
                           std::vector<int> &parent) {
  std::vector<std::vector<int>> graph(n);
  for (auto [a, b] : edges)
    graph[a].push_back(b), graph[b].push_back(a);
  parent.assign(n, -1);
  std::vector<int> order, stack = {0};
  while (!stack.empty()) {
    int v = stack.back();
    stack.pop_back();
    order.push_back(v);
    for (int u : graph[v]) {
      if (u == parent[v])
        continue;
      parent[u] = v;
      stack.push_back(u);
    }
  }
  return order;
}

// Edges on the longest path of a tree with n >= 1 vertices.
int treeDiameter(int n, const std::vector<std::pair<int, int>> &edges) {
  std::vector<int> parent, down(n, 0);
  auto order = treeOrder(n, edges, parent);
  int best = 0;
  for (int i = n - 1; i > 0; --i) {
    int v = order[i], up = parent[v];
    best = std::max(best, down[up] + down[v] + 1);
    down[up] = std::max(down[up], down[v] + 1);
  }
  return best;
}

// Largest vertex-value sum over nonempty simple paths; values may be negative.
long long maxPathSum(const std::vector<long long> &values,
                     const std::vector<std::pair<int, int>> &edges) {
  int n = values.size();
  std::vector<int> parent;
  auto order = treeOrder(n, edges, parent);
  // Two best nonnegative chains hanging below each vertex, excluding it.
  std::vector<long long> gain(n, 0), second(n, 0);
  long long best = *std::max_element(values.begin(), values.end());
  for (int i = n - 1; i >= 0; --i) {
    int v = order[i], up = parent[v];
    long long down = values[v] + gain[v];
    best = std::max(best, down + second[v]);
    if (up < 0 || down <= second[up])
      continue;
    if (down > gain[up])
      second[up] = gain[up], gain[up] = down;
    else
      second[up] = down;
  }
  return best;
}

// Max value sum of pairwise nonadjacent vertices (empty set allowed).
long long maxIndependentSet(const std::vector<long long> &values,
                            const std::vector<std::pair<int, int>> &edges) {
  int n = values.size();
  std::vector<int> parent;
  auto order = treeOrder(n, edges, parent);
  std::vector<long long> take = values, skip(n, 0);
  for (int i = n - 1; i > 0; --i) {
    int v = order[i], up = parent[v];
    take[up] += skip[v];
    skip[up] += std::max(take[v], skip[v]);
  }
  return std::max(take[0], skip[0]);
}

// answer[v] is the sum of edge distances from v to every vertex.
std::vector<long long>
sumOfDistances(int n, const std::vector<std::pair<int, int>> &edges) {
  std::vector<int> parent;
  auto order = treeOrder(n, edges, parent);
  std::vector<long long> size(n, 1), depth(n, 0), answer(n, 0);
  for (int i = 1; i < n; ++i)
    depth[order[i]] = depth[parent[order[i]]] + 1;
  for (int i = n - 1; i > 0; --i)
    size[parent[order[i]]] += size[order[i]];
  answer[0] = std::accumulate(depth.begin(), depth.end(), 0LL);
  for (int i = 1; i < n; ++i) {
    int v = order[i];
    answer[v] = answer[parent[v]] - size[v] + (n - size[v]);
  }
  return answer;
}
