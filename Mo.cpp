#include <bits/stdc++.h>

using namespace std;

const int N = 1e6;

int A[N + 2], ILE[N + 2], ANS[N + 2];
struct zap {
  int x, y, id;
} Q[N + 2];

int BL, ans = 0;
int blok(int x) { return x / BL; }

void add(int x) {
  if (ILE[x] == 0)
    ++ans;
  ILE[x]++;
}

void remove(int x) {
  ILE[x]--;
  if (ILE[x] == 0)
    --ans;
}

int L = 0, R = 0;
int query(int l, int r) {
  while (R < r) {
    ++R;
    add(A[R]);
  }
  while (R > r) {
    remove(A[R]);
    --R;
  }
  while (L < l - 1) {
    ++L;
    remove(A[L]);
  }
  while (L >= l) {
    add(A[L]);
    --L;
  }
  return ans;
}

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  // wprowadzanie danych
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    cin >> A[i];
  for (int i = 1; i <= n; i++) {
    cin >> Q[i].x >> Q[i].y;
    Q[i].id = i;
  }

  // wyliczenie pierwiastka
  BL = sqrt(n);

  // sortowanie zapytan po blokach
  sort(Q + 1, Q + (m + 1), [](zap a, zap b) {
    if (blok(a.x) != blok(b.x))
      return a.x < b.x;
    return a.y < b.y;
  });

  for (int i = 1; i <= m; i++)
    ANS[Q[i].id] = query(Q[i].x, Q[i].y);
  for (int i = 1; i <= m; i++)
    cout << ANS[i] << " ";
  cout << "\n";
  return 0;
}
