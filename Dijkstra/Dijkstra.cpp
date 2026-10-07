#include <bits/stdc++.h>

using namespace std;

const int N = 1e6, NT = N + 2;

long long path[2 * NT], D[NT];
vector<pair<int, int>> V[NT];
priority_queue<pair<long long, int>> Q;

void dijkstra(int v, int n) {
  Q = {};
  for (int i = 1; i <= n; i++) {
    D[i] = LLONG_MAX;
    path[i] = -1;
  }
  D[v] = 0;
  Q.push({0, v});
  while (!Q.empty()) {
    v = Q.top().second;
    long long dist = -Q.top().first;
    Q.pop();
    if (dist > D[v])
      continue;
    for (const auto &x : V[v]) {
      int u = x.first, c = x.second;
      if (c <= LLONG_MAX - D[v] && D[v] + c < D[u]) {
        D[u] = D[v] + c;
        path[u] = v;
        Q.push({-D[u], u});
      }
    }
  }
}
