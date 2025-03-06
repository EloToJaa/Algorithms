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

long long query(int v) {
  v += ntree - 1;
  long long ans = 0;
  while (v > 0) {
    ans = max(ans, T[v]);
    v >>= 1;
  }
  return ans;
}

void update(int l, int r, int val) {
  l += ntree - 1;
  r += ntree - 1;
  if (l == r) {
    T[l] = val;
    return;
  }
  T[l] = val;
  T[r] = val;
  while (r - l > 1) {
    if (!(l & 1))
      T[l + 1]++;
    if (r & 1)
      T[r - 1]++;
    l >>= 1;
    r >>= 1;
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  return 0;
}
