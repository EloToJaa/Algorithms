#include <bits/stdc++.h>

using namespace std;

const int N = 1e6, NT = N + 2;
const int LOG = 20; // log n

vector<int> V[NT];
int anc[NT][LOG + 1], pre[NT], post[NT], idx;

void ancestors(int v, int p) {
  anc[v][0] = p;
  for (int k = 1; k <= LOG; k++) {
    anc[v][k] = anc[anc[v][k - 1]][k - 1];
  }
  idx++;
  pre[v] = idx;
  for (const int &u : V[v]) {
    if (u != v)
      ancestors(u, v);
  }
  post[v] = idx;
}

bool parent(int a, int b) { // czy a jest przodkiem b
  return pre[a] <= pre[b] and pre[b] <= post[a];
}

int LCA(int a, int b) {
  if (parent(a, b))
    return a;
  if (parent(b, a))
    return b;
  for (int k = LOG; k >= 0; k--) {
    if (!parent(anc[a][k], b))
      a = anc[a][k];
  }
  return anc[a][0];
}
