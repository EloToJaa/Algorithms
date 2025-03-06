#include <bits/stdc++.h>

using namespace std;

const int N = 1e6, NT = N + 2, MAXW = 1e6;

int DP[MAXW + 2], m[N], w[N];

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, W;
  cin >> n >> W;

  for (int i = 0; i <= W; ++i)
    DP[i] = 0;
  for (int j = 1; j <= n; ++j)
    for (int i = W - m[j]; i >= 0; --i)
      DP[i + m[j]] = max(DP[i + m[j]], DP[i] + w[j]);
  return 0;
}
