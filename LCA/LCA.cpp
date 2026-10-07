#include <bits/stdc++.h>

using namespace std;

const int N = 1e6, NT = N + 2;
const int LOG = 20;
vector<int> V[NT];
int anc[NT][LOG + 1], pre[NT], post[NT], idx;

// Call ancestors(root, root) on a connected undirected tree.
void ancestors(int v, int p) {
  idx = 0;
  vector<tuple<int, int, bool>> stack = {{v, p, false}};
  while (!stack.empty()) {
    auto [vertex, parentVertex, exiting] = stack.back();
    stack.pop_back();
    if (exiting) {
      post[vertex] = idx;
      continue;
    }
    anc[vertex][0] = parentVertex;
    for (int k = 1; k <= LOG; ++k)
      anc[vertex][k] = anc[anc[vertex][k - 1]][k - 1];
    pre[vertex] = ++idx;
    stack.push_back({vertex, parentVertex, true});
    for (auto it = V[vertex].rbegin(); it != V[vertex].rend(); ++it) {
      if (*it != parentVertex)
        stack.push_back({*it, vertex, false});
    }
  }
}

bool parent(int a, int b) { return pre[a] <= pre[b] && pre[b] <= post[a]; }

int LCA(int a, int b) {
  if (parent(a, b))
    return a;
  if (parent(b, a))
    return b;
  for (int k = LOG; k >= 0; --k) {
    if (!parent(anc[a][k], b))
      a = anc[a][k];
  }
  return anc[a][0];
}
