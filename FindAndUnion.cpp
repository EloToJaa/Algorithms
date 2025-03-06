#include <bits/stdc++.h>

using namespace std;

const int N = 1e6, NT = N + 2;

int Rep[NT], Ile[NT];

int Find(int a) {
  if (Rep[a] != a)
    Rep[a] = Find(Rep[a]);
  return Rep[a];
}

void Union(int a, int b) {
  a = Find(a);
  b = Find(b);
  if (Ile[a] > Ile[b])
    swap(a, b);
  Rep[a] = b;
  Ile[b] += Ile[a];
}

void Init(int n) {
  for (int i = 1; i <= n; i++) {
    Rep[i] = i;
    Ile[i] = 1;
  }
}
