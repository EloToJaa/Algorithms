#include <bits/stdc++.h>

using namespace std;

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, W;
  cin >> n >> W;

  // One DP row; each item is applied as it is read, so memory is O(W).
  vector<long long> DP(W + 1, 0);
  for (int j = 0; j < n; ++j) {
    int m;
    long long w;
    cin >> m >> w;
    for (int i = W - m; i >= 0; --i)
      DP[i + m] = max(DP[i + m], DP[i] + w);
  }
  cout << DP[W] << "\n";
  return 0;
}
