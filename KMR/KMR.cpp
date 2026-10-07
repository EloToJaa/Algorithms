#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 2;
const int R = 23;

pair<int, pair<int, int>> A[N];
int KMR[N][R];

void kmr(string s) {
  int n = s.size() - 1;
  if (n == 0)
    return;
  int r = static_cast<int>(log2(n)) + 1, pot = 1;

  for (int i = 1; i <= n; i++) {
    KMR[i][0] = s[i] - 'a' + 1;
  }

  for (int k = 1; k <= r; k++) {
    for (int i = 1; i <= n; i++) {
      if (i + pot > n)
        A[i] = {KMR[i][k - 1], {-1, i}};
      else
        A[i] = {KMR[i][k - 1], {KMR[i + pot][k - 1], i}};
    }
    sort(A + 1, A + (n + 1));
    int kl = 0;
    pair<int, int> p = {-1, -1}, a; // previous element
    for (int i = 1; i <= n; i++) {
      a = {A[i].first, A[i].second.first};
      if (p != a) {
        p = a;
        ++kl;
      }
      KMR[A[i].second.second][k] = kl;
    }
    pot *= 2;
  }
  cout << "KMR:\n";
  for (int k = 0; k <= r; k++) {
    for (int i = 1; i <= n; i++)
      cout << KMR[i][k] << " ";
    cout << "\n";
  }
}

int SA[N], RANK[N]; // SA - przechowuje informacje o kolejnosci w SA, RANK -
                    // informuje ktory leksykograficznie jest ity sufiks
void sa(string s) { // suffix array
  int n = s.size() - 1;
  if (n == 0)
    return;
  int r = static_cast<int>(log2(n)) + 1; // ostatnia warstwa KMR
  for (int i = 1; i <= n; i++) {
    SA[KMR[i][r]] = i;
    RANK[i] =
        KMR[i][r]; // RANK pomaga przy nawigacji po SA, jest to odwrotnosc SA
  }
  cout << "SA:\n";
  for (int i = 1; i <= n; i++) {
    cout << SA[i] << ": ";
    for (int j = SA[i]; j <= n; j++)
      cout << s[j];
    cout << "\n";
  }
  cout << "RANK:\n";
  for (int i = 1; i <= n; i++)
    cout << RANK[i] << " ";
  cout << "\n";
}

int LCP[N];

int commonPart(string s, int a, int b) {
  int n = s.size() - 1, i = 0;
  while (a + i <= n && b + i <= n) {
    if (s[a + i] != s[b + i])
      break;
    ++i;
  }
  return i;
}

void lcp(string s) {
  int n = s.size() - 1, common = 0;
  if (n == 0)
    return;
  LCP[1] = -1;
  for (int i = 1; i <= n; ++i) {
    if (RANK[i] == 1) {
      common = 0;
      continue;
    }
    int previous = SA[RANK[i] - 1];
    while (i + common <= n && previous + common <= n &&
           s[i + common] == s[previous + common])
      ++common;
    LCP[RANK[i]] = common;
    common = max(0, common - 1);
  }
  cout << "LCP:\n";
  for (int i = 1; i <= n; ++i)
    cout << LCP[i] << " ";
  cout << "\n";
}

// Inclusive substrings: 0 = less, 1 = equal, 2 = greater.
int compare(int a, int b, int c, int d) {
  int firstLength = b - a + 1, secondLength = d - c + 1;
  int remaining = min(firstLength, secondLength);
  for (int level = R - 1; level >= 0; --level) {
    int width = 1 << level;
    if (width > remaining || KMR[a][level] != KMR[c][level])
      continue;
    a += width;
    c += width;
    remaining -= width;
  }
  if (remaining > 0)
    return KMR[a][0] < KMR[c][0] ? 0 : 2;
  if (firstLength == secondLength)
    return 1;
  return firstLength < secondLength ? 0 : 2;
}

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  string s;
  cin >> s;
  s = "#" + s;
  kmr(s);
  sa(s);
  lcp(s);
  return 0;
}
