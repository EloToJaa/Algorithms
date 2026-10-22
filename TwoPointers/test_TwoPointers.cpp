#include "TwoPointers.cpp"
#include <cassert>

int main() {
  std::mt19937 rng(5);
  for (int iteration = 0; iteration < 300; ++iteration) {
    int n = rng() % 10, m = rng() % 10;
    std::vector<long long> a(n), h(m);
    for (auto &x : a)
      x = (long long)(rng() % 13) - 6;
    for (auto &x : h)
      x = rng() % 8;
    long long target = (long long)(rng() % 17) - 8;
    std::sort(a.begin(), a.end());

    bool hasPair = false;
    std::set<std::array<long long, 3>> triplets;
    for (int i = 0; i < n; ++i)
      for (int j = i + 1; j < n; ++j) {
        hasPair |= a[i] + a[j] == target;
        for (int k = j + 1; k < n; ++k)
          if (a[i] + a[j] + a[k] == target)
            triplets.insert({a[i], a[j], a[k]});
      }
    auto [i, j] = pairWithSum(a, target);
    if (hasPair)
      assert(i >= 0 && i < j && a[i] + a[j] == target);
    else
      assert(i == -1 && j == -1);
    auto found = threeSum(a, target);
    assert(std::vector<std::array<long long, 3>>(triplets.begin(),
                                                 triplets.end()) == found);

    long long area = 0, water = 0;
    for (int x = 0; x < m; ++x) {
      for (int y = x + 1; y < m; ++y)
        area = std::max(area, (y - x) * std::min(h[x], h[y]));
      long long leftMax = *std::max_element(h.begin(), h.begin() + x + 1);
      long long rightMax = *std::max_element(h.begin() + x, h.end());
      water += std::min(leftMax, rightMax) - h[x];
    }
    assert(maxArea(h) == area);
    assert(trap(h) == water);
  }
  assert(pairWithSum({2, 7, 11, 15}, 9) == std::make_pair(0, 1));
  assert(threeSum({-1, 0, 1, 2, -1, -4}).size() == 2);
  assert(maxArea({1, 8, 6, 2, 5, 4, 8, 3, 7}) == 49);
  assert(trap({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}) == 6);
}
