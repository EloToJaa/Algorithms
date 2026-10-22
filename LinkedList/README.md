# Singly linked list toolkit

Reverse, split, merge, and detect cycles in LeetCode-style singly linked lists with O(1) extra space.

## My solution

- A dummy node before the head removes the special case of building or relinking the first node (`from_list`, `merge_two_lists`, `reverse_k_group`).
- Reversal keeps three pointers: save `next`, point the current node back to `prev`, advance both.
- `reverse_k_group` first walks k nodes to check a full group exists, then reverses it with `prev` starting at the node after the group, so the reversed group is already attached to the rest. The old first node becomes the `group_prev` of the next group.
- Middle node: fast moves two steps per slow step; when fast runs out, slow is halfway (the second middle for even length).
- Floyd phase 1: inside a cycle, fast gains one node per step on slow, so they must meet.
- Floyd phase 2: let the tail before the cycle have length a, the cycle length c, and the meeting point be b steps into the cycle. Fast walked twice as far: 2(a + b) = a + b + kc, so a = kc - b. From the meeting point, a more steps land at the cycle entry (b + a = kc, a full number of laps). Reset one pointer to the head and step both by one: they meet exactly at the entry after a steps.
- `find_duplicate` treats the array as a function graph i -> nums[i]. Values lie in [1, n], so index 0 has no incoming edge and starts a tail; the duplicate value has two incoming edges, which is exactly the cycle entry. Floyd finds it in O(n) time and O(1) space without modifying the array.

## Complexity

O(n) time and O(1) extra space for every operation except `from_list`/`to_list`, which allocate O(n). Merge is O(n + m).

## Usage and assumptions

`ListNode(val, next)` matches LeetCode. `from_list(values)` and `to_list(head)` convert from and to Python lists (`to_list` requires an acyclic list). `reverse_list(head)`, `reverse_k_group(head, k)`, `middle_node(head)`, and `merge_two_lists(first, second)` relink nodes in place and return the new head. `detect_cycle(head)` returns the cycle entry node or `None`; `has_cycle(head)` returns a bool. `find_duplicate(nums)` requires n + 1 values in [1, n]. C++ `ListNode`, `fromList(values, arena)` (nodes are owned by a caller-provided `std::deque<ListNode>`), `toList`, `reverseList`, `reverseKGroup`, `middleNode`, `detectCycle`, `hasCycle`, `mergeTwoLists`, and `findDuplicate` mirror the Python API with raw non-owning pointers.

```python
from LinkedList.LinkedList import (
    detect_cycle,
    find_duplicate,
    from_list,
    reverse_k_group,
    to_list,
)

to_list(reverse_k_group(from_list([1, 2, 3, 4, 5]), 2)) == [2, 1, 4, 3, 5]
find_duplicate([1, 3, 4, 2, 2]) == 2
detect_cycle(from_list([1, 2, 3])) is None
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

New snippet.

## LeetCode problems

- [206. Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/)
- [25. Reverse Nodes in k-Group](https://leetcode.com/problems/reverse-nodes-in-k-group/)
- [876. Middle of the Linked List](https://leetcode.com/problems/middle-of-the-linked-list/)
- [141. Linked List Cycle](https://leetcode.com/problems/linked-list-cycle/)
- [142. Linked List Cycle II](https://leetcode.com/problems/linked-list-cycle-ii/) — Floyd phase 2
- [21. Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/)
- [287. Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/) — Floyd on i -> nums[i]
- [234. Palindrome Linked List](https://leetcode.com/problems/palindrome-linked-list/) — middle, reverse the second half, compare

## Tests

[`test_LinkedList.py`](test_LinkedList.py) checks the Python implementation; [`test_LinkedList.cpp`](test_LinkedList.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s LinkedList -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
