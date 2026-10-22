#include "UnboundedKnapsack.cpp"
#include <cassert>

long long bruteForce(const std::vector<std::pair<int, long long>> &items,
                     int capacity) {
  long long best = 0;
  for (auto [weight, value] : items)
    if (weight <= capacity)
      best = std::max(best, value + bruteForce(items, capacity - weight));
  return best;
}

int main() {
  std::mt19937 rng(4);
  for (int iteration = 0; iteration < 200; ++iteration) {
    std::vector<std::pair<int, long long>> items(rng() % 5);
    for (auto &[weight, value] : items)
      weight = 1 + rng() % 6, value = int(rng() % 12) - 2;
    int capacity = rng() % 16;
    assert(unboundedKnapsack(items, capacity) == bruteForce(items, capacity));
  }
  assert(unboundedKnapsack({{2, 3}}, 7) == 9);
  assert(unboundedKnapsack({{3, 4}, {4, 5}, {2, 3}}, 7) == 10);
  assert(unboundedKnapsack({}, 5) == 0);
}
