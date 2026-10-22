#include "LinkedList.cpp"
#include <cassert>

std::vector<int> randomValues(std::mt19937 &rng) {
  std::vector<int> values(rng() % 12);
  for (int &value : values)
    value = int(rng() % 10);
  return values;
}

int main() {
  std::mt19937 rng(1);
  for (int iteration = 0; iteration < 300; ++iteration) {
    std::deque<ListNode> arena;
    std::vector<int> values = randomValues(rng);
    assert(toList(fromList(values, arena)) == values);
    std::vector<int> reversed(values.rbegin(), values.rend());
    assert(toList(reverseList(fromList(values, arena))) == reversed);
    std::vector<int> second(values.begin() + values.size() / 2, values.end());
    assert(toList(middleNode(fromList(values, arena))) == second);

    int k = 1 + int(rng() % 5);
    std::vector<int> expected;
    for (size_t start = 0; start < values.size(); start += k) {
      std::vector<int> chunk(values.begin() + start,
                             values.begin() +
                                 std::min(values.size(), start + k));
      if (int(chunk.size()) == k)
        std::reverse(chunk.begin(), chunk.end());
      expected.insert(expected.end(), chunk.begin(), chunk.end());
    }
    assert(toList(reverseKGroup(fromList(values, arena), k)) == expected);

    std::vector<int> a = randomValues(rng), b = randomValues(rng);
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    std::vector<int> merged(a);
    merged.insert(merged.end(), b.begin(), b.end());
    std::sort(merged.begin(), merged.end());
    assert(toList(mergeTwoLists(fromList(a, arena), fromList(b, arena))) ==
           merged);

    int n = 1 + int(rng() % 11);
    std::deque<ListNode> cycleArena;
    ListNode *head = fromList(std::vector<int>(n), cycleArena);
    int entry = int(rng() % (n + 1)) - 1;
    if (entry >= 0)
      cycleArena.back().next = &cycleArena[entry];
    assert(detectCycle(head) == (entry >= 0 ? &cycleArena[entry] : nullptr));
    assert(hasCycle(head) == (entry >= 0));

    int duplicate = 1 + int(rng() % n);
    std::vector<int> nums(n + 1, duplicate);
    for (int value = 1, i = 0; value <= n; ++value)
      if (value != duplicate && rng() % 2)
        nums[i++] = value;
    std::shuffle(nums.begin(), nums.end(), rng);
    assert(findDuplicate(nums) == duplicate);
  }
  std::deque<ListNode> arena;
  assert(toList(reverseKGroup(fromList({1, 2, 3, 4, 5}, arena), 2)) ==
         std::vector<int>({2, 1, 4, 3, 5}));
  assert(findDuplicate({1, 3, 4, 2, 2}) == 2);
  assert(findDuplicate({3, 3, 3, 3, 3}) == 3);
  assert(detectCycle(nullptr) == nullptr);
}
