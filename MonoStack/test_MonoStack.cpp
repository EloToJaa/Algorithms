#include "MonoStack.cpp"
#include <cassert>

int main() {
  const long long mod = 1'000'000'007;
  std::mt19937 rng(5);
  for (int iteration = 0; iteration < 300; ++iteration) {
    int n = rng() % 12;
    std::vector<long long> a(n), h(n);
    for (auto &x : a)
      x = (long long)(rng() % 7) - 3;
    for (auto &x : h)
      x = rng() % 5;
    std::vector<int> greater(n, -1), smaller(n, -1);
    long long area = 0, mins = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n && greater[i] < 0; ++j)
        if (a[j] > a[i])
          greater[i] = j;
      for (int j = i - 1; j >= 0 && smaller[i] < 0; --j)
        if (a[j] < a[i])
          smaller[i] = j;
      long long lowA = a[i], lowH = h[i];
      for (int j = i; j < n; ++j) {
        lowA = std::min(lowA, a[j]), lowH = std::min(lowH, h[j]);
        mins += lowA;
        area = std::max(area, lowH * (j - i + 1));
      }
    }
    assert(nextGreater(a) == greater);
    assert(previousSmaller(a) == smaller);
    assert(largestRectangle(h) == area);
    assert(sumSubarrayMins(a) == ((mins % mod) + mod) % mod);
  }
  assert(nextGreater({2, 1, 2, 4, 3}) == std::vector<int>({3, 2, 3, -1, -1}));
  assert(largestRectangle({2, 1, 5, 6, 2, 3}) == 10);
  assert(sumSubarrayMins({3, 1, 2, 4}) == 17);
  assert(sumSubarrayMins({11, 81, 94, 43, 3}) == 444);
}
