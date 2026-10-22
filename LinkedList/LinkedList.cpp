#include <bits/stdc++.h>

struct ListNode {
  int val;
  ListNode *next;
  explicit ListNode(int val = 0, ListNode *next = nullptr)
      : val(val), next(next) {}
};

// Nodes live in the caller's arena (deque keeps addresses stable).
ListNode *fromList(const std::vector<int> &values,
                   std::deque<ListNode> &arena) {
  ListNode dummy;
  ListNode *tail = &dummy;
  for (int value : values) {
    arena.emplace_back(value);
    tail = tail->next = &arena.back();
  }
  return dummy.next;
}

// Values of an acyclic list.
std::vector<int> toList(const ListNode *head) {
  std::vector<int> values;
  for (; head; head = head->next)
    values.push_back(head->val);
  return values;
}

ListNode *reverseList(ListNode *head) {
  ListNode *prev = nullptr;
  while (head) {
    ListNode *next = head->next;
    head->next = prev;
    prev = head;
    head = next;
  }
  return prev;
}

// Reverses each full group of k nodes; a shorter tail stays as is.
ListNode *reverseKGroup(ListNode *head, int k) {
  if (k <= 1)
    return head;
  ListNode dummy(0, head);
  ListNode *groupPrev = &dummy;
  while (true) {
    ListNode *kth = groupPrev;
    for (int i = 0; i < k && kth; ++i)
      kth = kth->next;
    if (!kth)
      return dummy.next;
    ListNode *groupNext = kth->next, *first = groupPrev->next;
    ListNode *prev = groupNext, *node = first;
    while (node != groupNext) {
      ListNode *next = node->next;
      node->next = prev;
      prev = node;
      node = next;
    }
    groupPrev->next = kth;
    groupPrev = first;
  }
}

// Second of the two middles for even length.
ListNode *middleNode(ListNode *head) {
  ListNode *slow = head, *fast = head;
  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow;
}

// Node where the cycle begins, or nullptr if acyclic.
ListNode *detectCycle(ListNode *head) {
  ListNode *slow = head, *fast = head;
  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow != fast)
      continue;
    for (slow = head; slow != fast; fast = fast->next)
      slow = slow->next;
    return slow;
  }
  return nullptr;
}

bool hasCycle(ListNode *head) { return detectCycle(head) != nullptr; }

ListNode *mergeTwoLists(ListNode *first, ListNode *second) {
  ListNode dummy;
  ListNode *tail = &dummy;
  while (first && second) {
    ListNode *&smaller = second->val < first->val ? second : first;
    tail = tail->next = smaller;
    smaller = smaller->next;
  }
  tail->next = first ? first : second;
  return dummy.next;
}

// n + 1 values in [1, n]: Floyd on the graph i -> nums[i] from index 0.
int findDuplicate(const std::vector<int> &nums) {
  int slow = 0, fast = 0;
  do {
    slow = nums[slow];
    fast = nums[nums[fast]];
  } while (slow != fast);
  for (slow = 0; slow != fast; fast = nums[fast])
    slow = nums[slow];
  return slow;
}
