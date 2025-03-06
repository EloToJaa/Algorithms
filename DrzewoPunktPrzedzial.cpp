#include <bits/stdc++.h>

using namespace std;

#define lc (v << 1)
#define rc (v << 1 | 1)

const int N = 3e5, NT = N + 2;
const int NTREE = 524288 * 2 + 2;

long long T[NTREE], A[NT];
int ntree = 1;

void build(int n) {
  while (ntree < n)
    ntree <<= 1;
  for (int i = 1; i <= n; i++)
    T[i + ntree - 1] = A[i];
  for (int v = ntree - 1; v >= 1; v--)
    T[v] = max(T[lc], T[rc]);
}

void update(int v, int val) {
  v += ntree - 1;
  T[v] = val;
  v /= 2;
  while (v > 0) {
    T[v] = max(T[lc], T[rc]);
    v >>= 1;
  }
}

long long query(int l, int r) {
  l += ntree - 1;
  r += ntree - 1;
  long long ans = T[l];
  if (r > l)
    ans = max(ans, T[r]);
  while (r - l > 1) {
    if (!(l & 1))
      ans = max(ans, T[l + 1]);
    if (r & 1)
      ans = max(ans, T[r - 1]);
    l >>= 1;
    r >>= 1;
  }
  return ans;
}

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  return 0;
}
