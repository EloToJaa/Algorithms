#include <bits/stdc++.h>

// Indices i < j with a[i] + a[j] == target in a sorted array, or {-1, -1}.
std::pair<int, int> pairWithSum(const std::vector<long long> &a,
                                long long target) {
  int left = 0, right = (int)a.size() - 1;
  while (left < right) {
    long long total = a[left] + a[right];
    if (total == target)
      return {left, right};
    if (total < target)
      left++;
    else
      right--;
  }
  return {-1, -1};
}

// Unique value triplets a <= b <= c with a + b + c == target, sorted.
std::vector<std::array<long long, 3>> threeSum(std::vector<long long> a,
                                               long long target = 0) {
  std::sort(a.begin(), a.end());
  std::vector<std::array<long long, 3>> result;
  int n = a.size();
  for (int i = 0; i + 2 < n; ++i) {
    if (i && a[i] == a[i - 1])
      continue;
    int left = i + 1, right = n - 1;
    while (left < right) {
      long long total = a[i] + a[left] + a[right];
      if (total < target) {
        left++;
      } else if (total > target) {
        right--;
      } else {
        result.push_back({a[i], a[left], a[right]});
        for (left++; left < right && a[left] == a[left - 1];)
          left++;
      }
    }
  }
  return result;
}

// Largest (j - i) * min(h[i], h[j]) over pairs i < j.
long long maxArea(const std::vector<long long> &h) {
  long long best = 0;
  int left = 0, right = (int)h.size() - 1;
  while (left < right) {
    best = std::max(best, (right - left) * std::min(h[left], h[right]));
    if (h[left] < h[right])
      left++;
    else
      right--;
  }
  return best;
}

// Water trapped between non-negative bars of width one.
long long trap(const std::vector<long long> &h) {
  long long water = 0, leftMax = 0, rightMax = 0;
  int left = 0, right = (int)h.size() - 1;
  while (left < right) {
    if (h[left] < h[right]) {
      leftMax = std::max(leftMax, h[left]);
      water += leftMax - h[left++];
    } else {
      rightMax = std::max(rightMax, h[right]);
      water += rightMax - h[right--];
    }
  }
  return water;
}
