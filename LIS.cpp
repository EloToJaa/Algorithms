#include <bits/stdc++.h>

using namespace std;

const int N = 1e6, NT = N + 2;

struct StackStruct {
  shared_ptr<StackStruct> prev;
  int head, size;
  StackStruct() { prev = nullptr; }
  StackStruct(shared_ptr<StackStruct> s, int e) {
    prev = s;
    head = e;
  }
};

shared_ptr<StackStruct> historia[NT];
int t = 1;

void push(int k, int e) {
  historia[t++] = make_shared<StackStruct>(historia[k], e);
}

void printStack(int k) {
  auto s = historia[k];
  vector<int> stos;
  while (s) {
    stos.push_back(s->head);
    s = s->prev;
  }
  reverse(stos.begin(), stos.end());
  for (const int &e : stos) {
    cout << e << " ";
  }
  cout << "\n";
}

int A[NT];
pair<int, int> B[NT];

int find(int l, int r, int val) {
  while (l < r) {
    int mid = (l + (r - l)) >> 1;
    if (val < B[mid].first)
      r = mid;
    else
      l = mid + 1;
  }
  return l;
}

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, ans = 1, idx = 0;

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
  }
  for (int i = 1; i <= n; i++) {
    B[i].first = LONG_LONG_MAX;
  }
  for (int i = 1; i <= n; i++) {
    int x = find(1, n, A[i]);    // szukamy 1szego miejsca ze A[i] < B[x].first
    push(B[x - 1].second, A[i]); // dodajemy element do poprzedniego stosu
    if (x >= ans) {
      ans = x;
      idx = i;
    }
    B[x] = {A[i], i};
  }
  cout << ans << "\n";
  printStack(idx);
  return 0;
}
