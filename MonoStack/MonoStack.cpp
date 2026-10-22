#include <bits/stdc++.h>

// Index of the nearest strictly greater value to the right, or -1.
std::vector<int> nextGreater(const std::vector<long long> &a) {
  std::vector<int> result(a.size(), -1), stack;
  for (int i = 0; i < (int)a.size(); ++i) {
    while (!stack.empty() && a[stack.back()] < a[i]) {
      result[stack.back()] = i;
      stack.pop_back();
    }
    stack.push_back(i);
  }
  return result;
}

// Index of the nearest strictly smaller value to the left, or -1.
std::vector<int> previousSmaller(const std::vector<long long> &a) {
  std::vector<int> result(a.size(), -1), stack;
  for (int i = 0; i < (int)a.size(); ++i) {
    while (!stack.empty() && a[stack.back()] >= a[i])
      stack.pop_back();
    if (!stack.empty())
      result[i] = stack.back();
    stack.push_back(i);
  }
  return result;
}

// Largest axis-aligned rectangle in a histogram of non-negative bars.
long long largestRectangle(const std::vector<long long> &h) {
  long long best = 0;
  std::vector<int> stack;
  int n = h.size();
  for (int i = 0; i <= n; ++i) {
    long long height = i < n ? h[i] : -1;
    while (!stack.empty() && h[stack.back()] >= height) {
      long long top = h[stack.back()];
      stack.pop_back();
      int left = stack.empty() ? -1 : stack.back();
      best = std::max(best, top * (i - left - 1));
    }
    stack.push_back(i);
  }
  return best;
}

// Sum of min(a[l..r]) over all subarrays, modulo mod.
long long sumSubarrayMins(const std::vector<long long> &a,
                          long long mod = 1'000'000'007) {
  long long total = 0;
  std::vector<int> stack;
  int n = a.size();
  for (int i = 0; i <= n; ++i) {
    while (!stack.empty() && (i == n || a[stack.back()] >= a[i])) {
      int j = stack.back();
      stack.pop_back();
      int left = stack.empty() ? -1 : stack.back(); // previous strictly smaller
      long long value = (a[j] % mod + mod) % mod;   // i: next smaller or equal
      total = (total + value * (j - left) % mod * (i - j)) % mod;
    }
    stack.push_back(i);
  }
  return total;
}
