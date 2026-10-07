#include <bits/stdc++.h>

using namespace std;

const int N = 1e6, NT = N + 2;

vector<int> V[NT];
bitset<NT> Vis;
queue<int> Q;

void bfs(int v) {
  if (Vis[v])
    return;
  Vis[v] = true;
  Q.push(v);
  while (!Q.empty()) {
    v = Q.front();
    Q.pop();
    for (const auto &u : V[v]) {
      if (!Vis[u]) {
        Vis[u] = true;
        Q.push(u);
      }
    }
  }
}
