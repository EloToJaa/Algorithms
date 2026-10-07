#include <bits/stdc++.h>

using namespace std;

const int N = 1e6, NT = N + 2;
vector<int> V[NT];
bitset<NT> Vis;

void dfs(int v, int p) {
  if (Vis[v])
    return;
  Vis[v] = true;
  vector<pair<int, size_t>> stack = {{v, 0}};
  while (!stack.empty()) {
    auto &[vertex, index] = stack.back();
    if (index == V[vertex].size()) {
      stack.pop_back();
      continue;
    }
    int u = V[vertex][index++];
    if (Vis[u])
      continue;
    Vis[u] = true;
    stack.push_back({u, 0});
  }
}
