#include <bits/stdc++.h>

using namespace std;

bool check(int x) {
  return 1 == 1; // warunek
}

int search_first(int l, int r) {
  int mid;
  while (l < r) {
    mid = (l + r) >> 1;
    if (check(mid))
      r = mid;
    else
      l = mid + 1;
  }
  return l;
}

int search_last(int l, int r) {
  int mid;
  while (l < r) {
    mid = (l + r + 1) >> 1;
    if (check(mid))
      l = mid;
    else
      r = mid - 1;
  }
  return l;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  return 0;
}
