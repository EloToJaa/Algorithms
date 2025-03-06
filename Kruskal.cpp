#include <bits/stdc++.h>

using namespace std;

const int N = 1e6, NT = N + 2;

int REP[NT], ILE[NT];

void Init(int n) {
  for (int i = 1; i <= n; i++) {
    REP[i] = i;
    ILE[i] = 1;
  }
}

void Union(int a, int b) { // O(1)
  if (ILE[a] > ILE[b])
    swap(a, b);
  REP[a] = b;
  ILE[b] += ILE[a];
}

int Find(int a) { // O(stala ackermana)
  if (REP[a] != a)
    REP[a] = Find(REP[a]);
  return REP[a];
}

struct Edge {
  int a, b, w;
} K[NT];

void Kruskal(int n, int m) {
  Init(n);
  sort(K + 1, K + (m + 1),
       [](const Edge &a, const Edge &b) { return a.w < b.w; });
  int a, b;
  for (int i = 1; i <= m; i++) {
    a = Find(K[i].a);
    b = Find(K[i].b);
    if (a != b) {
      Union(a, b);
    }
  }
}
