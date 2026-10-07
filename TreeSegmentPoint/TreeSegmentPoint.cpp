#include <bits/stdc++.h>

using namespace std;

const int N = 3e5, NT = N + 2;
const int NTREE = 524288 * 2 + 2;
long long T[NTREE], A[NT];
int ntree = 1;

void build(int n) {
  ntree = 1;
  while (ntree < n)
    ntree <<= 1;
  fill(T, T + 2 * ntree, 0);
  for (int i = 1; i <= n; ++i)
    T[ntree + i - 1] = A[i];
}

long long query(int v) {
  long long answer = 0;
  for (v += ntree - 1; v > 0; v >>= 1)
    answer += T[v];
  return answer;
}

// Add val to every position in the inclusive interval [l, r].
void update(int l, int r, long long val) {
  l += ntree - 1;
  r += ntree - 1;
  while (l <= r) {
    if (l & 1)
      T[l++] += val;
    if (!(r & 1))
      T[r--] += val;
    l >>= 1;
    r >>= 1;
  }
}

int main() { return 0; }
