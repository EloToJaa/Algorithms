#include <bits/stdc++.h>

using namespace std;

const int N = 1e6, NT = N + 2;

vector<int> V[NT];
bitset<NT> Vis;
void dfs(int v, int p) {
  Vis[v] = true;
  for (const int &u : V[v]) {
    if (!Vis[u]) {
      dfs(u, v);
    }
  }
}
