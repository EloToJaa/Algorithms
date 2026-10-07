#include <bits/stdc++.h>

using namespace std;

// Replace this placeholder for the two-argument convenience overloads.
bool check(int x) { return true; }

// Inclusive bounds; returns original r + 1 when no value is true.
// The bounds and the sentinel must fit in int.
template <typename Predicate>
int search_first(int l, int r, Predicate predicate) {
  long long low = l, high = r;
  int answer = r + 1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (predicate(mid)) {
      answer = mid;
      high = static_cast<long long>(mid) - 1;
    } else {
      low = static_cast<long long>(mid) + 1;
    }
  }
  return answer;
}

// Inclusive bounds; returns original l - 1 when no value is true.
template <typename Predicate>
int search_last(int l, int r, Predicate predicate) {
  long long low = l, high = r;
  int answer = l - 1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (predicate(mid)) {
      answer = mid;
      low = static_cast<long long>(mid) + 1;
    } else {
      high = static_cast<long long>(mid) - 1;
    }
  }
  return answer;
}

int search_first(int l, int r) { return search_first(l, r, check); }
int search_last(int l, int r) { return search_last(l, r, check); }

int main() { return 0; }
