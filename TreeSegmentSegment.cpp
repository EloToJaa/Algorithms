#include <bits/stdc++.h>

using namespace std;

#define lc (v << 1)
#define rc (v << 1 | 1)

const int N = 3e5, NT = N + 2;
const int NTREE = 524288 * 2 + 2;

long long T[NTREE], lazy[NTREE], A[NT];

int ntree = 1;
void build(int n) {
  while (ntree < n)
    ntree <<= 1;
  for (int i = 1; i <= n; i++)
    T[i + ntree - 1] = A[i];
  for (int v = ntree - 1; v >= 1; v--)
    T[v] = max(T[lc], T[rc]);
}

void push(int v, long long len) {
  T[lc] += lazy[v] * len / 2;
  T[rc] += lazy[v] * len / 2;
  lazy[lc] += lazy[v];
  lazy[rc] += lazy[v];
  lazy[v] = 0;
}

long long query(int v, int tl, int tr, int l, int r) {
  if (l <= tl and tr <= r)
    return T[v];
  int tm = (tl + tr) >> 1;
  push(v, tr - tl + 1);
  long long a = 0, b = 0;
  if (l <= tm)
    a = query(lc, tl, tm, l, r);
  if (r > tm)
    b = query(rc, tm + 1, tr, l, r);
  T[v] = T[lc] + T[rc] + lazy[v] * (tr - tl + 1);
  return a + b;
}

void update(int v, int tl, int tr, int l, int r, long long val) {
  if (l <= tl and tr <= r) {
    T[v] += val * (tr - tl + 1);
    lazy[v] += val;
    return;
  }
  int tm = (tl + tr) >> 1;
  push(v, tr - tl + 1);
  if (l <= tm)
    update(lc, tl, tm, l, r, val);
  if (r > tm)
    update(rc, tm + 1, tr, l, r, val);
  T[v] = T[lc] + T[rc] + lazy[v] * (tr - tl + 1);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  return 0;
}
