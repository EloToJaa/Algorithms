#include <bits/stdc++.h>

// Items are (positive weight, value) pairs; each item may be taken any number
// of times.
long long unboundedKnapsack(const std::vector<std::pair<int, long long>> &items,
                            int capacity) {
  std::vector<long long> best(capacity + 1, 0);
  for (auto [weight, value] : items)
    for (int available = weight; available <= capacity; ++available)
      best[available] =
          std::max(best[available], best[available - weight] + value);
  return best[capacity];
}
