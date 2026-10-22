#include "BitmaskDP.cpp"
#include <cassert>

long long bruteCycle(const std::vector<std::vector<long long>> &cost) {
  int n = cost.size();
  if (n <= 1)
    return 0;
  std::vector<int> order(n - 1);
  std::iota(order.begin(), order.end(), 1);
  long long best = heldKarpInf;
  do {
    long long total = 0;
    int previous = 0;
    order.push_back(0);
    for (int v : order) {
      total = cost[previous][v] >= heldKarpInf ? heldKarpInf
                                               : total + cost[previous][v];
      if (total >= heldKarpInf)
        break;
      previous = v;
    }
    order.pop_back();
    best = std::min(best, total);
  } while (std::next_permutation(order.begin(), order.end()));
  return best;
}

bool brutePartition(const std::vector<int> &nums, int k) {
  int n = nums.size(), states = 1;
  for (int i = 0; i < n; ++i)
    states *= k;
  for (int code = 0; code < states; ++code) {
    std::vector<int> sums(k);
    for (int i = 0, c = code; i < n; ++i, c /= k)
      sums[c % k] += nums[i];
    if (std::count(sums.begin(), sums.end(), sums[0]) == k)
      return true;
  }
  return false;
}

int bruteWalk(const std::vector<std::vector<int>> &graph) {
  int n = graph.size();
  const int inf = 1e9;
  std::vector<std::vector<int>> distance(n, std::vector<int>(n, inf));
  for (int s = 0; s < n; ++s) {
    std::queue<int> queue;
    distance[s][s] = 0;
    queue.push(s);
    while (!queue.empty()) {
      int v = queue.front();
      queue.pop();
      for (int u : graph[v])
        if (distance[s][u] == inf)
          distance[s][u] = distance[s][v] + 1, queue.push(u);
    }
  }
  std::vector<int> order(n);
  std::iota(order.begin(), order.end(), 0);
  int best = inf;
  do {
    int total = 0;
    for (int i = 0; i + 1 < n && total < inf; ++i)
      total = distance[order[i]][order[i + 1]] == inf
                  ? inf
                  : total + distance[order[i]][order[i + 1]];
    best = std::min(best, total);
  } while (std::next_permutation(order.begin(), order.end()));
  return best == inf ? -1 : best;
}

int main() {
  std::mt19937 rng(8);
  for (int iteration = 0; iteration < 150; ++iteration) {
    int n = 1 + rng() % 6;
    std::vector<std::vector<long long>> cost(n, std::vector<long long>(n));
    for (auto &row : cost)
      for (auto &c : row)
        c = rng() % 10 < 3 ? heldKarpInf : 1 + rng() % 19;
    assert(heldKarp(cost) == bruteCycle(cost));

    std::vector<int> nums(1 + rng() % 7);
    for (int &value : nums)
      value = 1 + rng() % 5;
    int k = 1 + rng() % std::min<int>(nums.size(), 4);
    assert(canPartitionKSubsets(nums, k) == brutePartition(nums, k));

    std::vector<std::vector<int>> graph(n);
    for (int a = 0; a < n; ++a)
      for (int b = a + 1; b < n; ++b)
        if (rng() % 10 < 4)
          graph[a].push_back(b), graph[b].push_back(a);
    assert(shortestPathVisitingAllNodes(graph) == bruteWalk(graph));
  }
  assert(heldKarp({{0, 10, 15, 20},
                   {10, 0, 35, 25},
                   {15, 35, 0, 30},
                   {20, 25, 30, 0}}) == 80);
  assert(canPartitionKSubsets({4, 3, 2, 3, 5, 2, 1}, 4));
  assert(!canPartitionKSubsets({1, 2, 3, 4}, 3));
  assert(shortestPathVisitingAllNodes({{1, 2, 3}, {0}, {0}, {0}}) == 4);
  assert(shortestPathVisitingAllNodes(
             {{1}, {0, 2, 4}, {1, 3, 4}, {2}, {1, 2}}) == 4);
}
