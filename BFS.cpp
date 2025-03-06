#include <bits/stdc++.h>

using namespace std;

const int N = 1e6, NT = N + 2;

vector<int> V[NT];
bitset<NT> Vis;
queue<int> Q;

void bfs(int v) {
  Q.push(v);
  while (!Q.empty()) {
    v = Q.front();
    Q.pop();
    Vis[v] = true;
    for (const auto &u : V[v]) {
      if (!Vis[u]) {
        Q.push(u);
      }
    }
  }
}
