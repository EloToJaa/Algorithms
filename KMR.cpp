#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 2;
const int R = 23;

pair<int, pair<int, int>> A[N];
int KMR[N][R];

void kmr(string s) {
  int n = s.size() - 1;
  int r = log2(n) + 1, pot = 1;

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
  int r = log2(n) + 1; // ostatnia warstwa KMR
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

void lcp(string s) { // longest common prefix
  int n = s.size() - 1;
  for (int i = 1; i <= n; i++) {
    if (RANK[i] == 1)
      LCP[1] = -1; // jezeli jest pierwszy leksykograficznie to -1 bo nie ma dla
                   // niego pary
    else
      LCP[RANK[i]] = commonPart(s, i, SA[RANK[i] - 1]);
  }
  cout << "LCP:\n";
  for (int i = 1; i <= n; i++)
    cout << LCP[i] << " ";
  cout << "\n";
}

int compare(
    int a, int b, int c,
    int d) { // 0 - s(a,b) < s(c,d), 1 - s(a,b) == s(c,d), 2 - s(a,b) > s(c,d)
  int n = b - a + 1, m = d - c + 1, pot = 1, pota = -1, potb = -1, qa, qb;
  bool oa = 0, ob = 0;
  for (int i = 2; i <= 20; i++) {
    pot *= 2;
    if (pot > n && !oa) {
      pota = pot / 2;
      qa = i - 2; // nie jestem pewny dlaczego i - 2, a nie i - 1
      oa = 1;
    }
    if (pot > m && !ob) {
      potb = pot / 2;
      qb = i - 2; // ^^^ (same here lulz)
      ob = 1;
    }
    if (pot > n && pot > m)
      break;
  }
  pair<int, int> x, y;
  x = {KMR[a][qa], KMR[b - pota + 1][qa]};
  y = {KMR[c][qb], KMR[d - potb + 1][qb]};
  if (x < y)
    return 0;
  else if (x == y)
    return 1;
  else
    return 2;
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
