#include <bits/stdc++.h>

using namespace std;

// Replace this placeholder for the two-argument convenience overloads.
bool check(int x) { return true; }

// Inclusive bounds; returns original r + 1 when no value is true.
// The bounds and the sentinel must fit in int.
template <typename Predicate>
int search_first(long long l, long long r, Predicate predicate) {
  r++;  // r + 1 stands for "none"
  while (l < r) {
    long long mid = l + (r - l) / 2;
    if (predicate(static_cast<int>(mid))) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  return static_cast<int>(l);
}

// Inclusive bounds; returns original l - 1 when no value is true.
template <typename Predicate>
int search_last(long long l, long long r, Predicate predicate) {
  l--;  // l - 1 stands for "none"
  while (l < r) {
    long long mid = l + (r - l + 1) / 2;  // round up, or l = mid can get stuck
    if (predicate(static_cast<int>(mid))) {
      l = mid;
    } else {
      r = mid - 1;
    }
  }
  return static_cast<int>(l);
}

int search_first(int l, int r) { return search_first(l, r, check); }
int search_last(int l, int r) { return search_last(l, r, check); }

int main() { return 0; }
