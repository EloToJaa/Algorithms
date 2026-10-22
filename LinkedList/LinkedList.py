"""LeetCode-style singly linked list toolkit with Floyd cycle detection."""

from __future__ import annotations

from collections.abc import Iterable, Sequence


class ListNode:
    def __init__(self, val: int = 0, next: ListNode | None = None) -> None:
        self.val = val
        self.next = next


def from_list(values: Iterable[int]) -> ListNode | None:
    dummy = tail = ListNode()
    for value in values:
        tail.next = ListNode(value)
        tail = tail.next
    return dummy.next


def to_list(head: ListNode | None) -> list[int]:
    """Values of an acyclic list."""
    values = []
    while head:
        values.append(head.val)
        head = head.next
    return values


def reverse_list(head: ListNode | None) -> ListNode | None:
    """Reverse in place and return the new head."""
    prev = None
    while head:
        head.next, prev, head = prev, head, head.next
    return prev


def reverse_k_group(head: ListNode | None, k: int) -> ListNode | None:
    """Reverse each full group of k nodes; a shorter tail stays as is."""
    if k <= 1:
        return head
    dummy = ListNode(0, head)
    group_prev = dummy
    while True:
        kth: ListNode | None = group_prev
        for _ in range(k):
            kth = kth.next if kth else None
        if kth is None:
            return dummy.next
        group_next = kth.next
        first = group_prev.next
        prev, node = group_next, first
        while node is not group_next:
            assert node is not None
            node.next, prev, node = prev, node, node.next
        group_prev.next = kth
        assert first is not None
        group_prev = first


def middle_node(head: ListNode | None) -> ListNode | None:
    """Middle node; the second of the two middles for even length."""
    slow = fast = head
    while fast and fast.next:
        slow = slow.next  # type: ignore[union-attr]
        fast = fast.next.next
    return slow


def detect_cycle(head: ListNode | None) -> ListNode | None:
    """Return the node where the cycle begins, or None if acyclic."""
    slow = fast = head
    while fast and fast.next:
        slow = slow.next  # type: ignore[union-attr]
        fast = fast.next.next
        if slow is fast:
            slow = head
            while slow is not fast:
                slow = slow.next  # type: ignore[union-attr]
                fast = fast.next  # type: ignore[union-attr]
            return slow
    return None


def has_cycle(head: ListNode | None) -> bool:
    return detect_cycle(head) is not None


def merge_two_lists(first: ListNode | None, second: ListNode | None) -> ListNode | None:
    """Splice two sorted lists into one sorted list (stable: first wins ties)."""
    dummy = tail = ListNode()
    while first and second:
        if second.val < first.val:
            tail.next, second = second, second.next
        else:
            tail.next, first = first, first.next
        tail = tail.next
    tail.next = first or second
    return dummy.next


def find_duplicate(nums: Sequence[int]) -> int:
    """n + 1 values in [1, n]: Floyd on the graph i -> nums[i] from index 0.

    Index 0 has no incoming edge, so it lies on the tail; the cycle entry is a
    value pointed to by two indices, i.e. the duplicate.
    """
    slow = fast = 0
    while True:
        slow = nums[slow]
        fast = nums[nums[fast]]
        if slow == fast:
            break
    slow = 0
    while slow != fast:
        slow = nums[slow]
        fast = nums[fast]
    return slow
