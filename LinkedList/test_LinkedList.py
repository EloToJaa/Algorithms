import random
import unittest

from LinkedList.LinkedList import (
    ListNode,
    detect_cycle,
    find_duplicate,
    from_list,
    has_cycle,
    merge_two_lists,
    middle_node,
    reverse_k_group,
    reverse_list,
    to_list,
)


def random_values(rng: random.Random) -> list[int]:
    return [rng.randrange(10) for _ in range(rng.randrange(12))]


def nodes_of(head: ListNode | None) -> list[ListNode]:
    nodes = []
    while head:
        nodes.append(head)
        head = head.next
    return nodes


class TestLinkedList(unittest.TestCase):
    def test_reverse_and_middle(self):
        rng = random.Random(1)
        for _ in range(200):
            values = random_values(rng)
            self.assertEqual(to_list(from_list(values)), values)
            self.assertEqual(to_list(reverse_list(from_list(values))), values[::-1])
            middle = middle_node(from_list(values))
            self.assertEqual(to_list(middle), values[len(values) // 2 :])

    def test_reverse_k_group(self):
        rng = random.Random(2)
        for _ in range(300):
            values = random_values(rng)
            k = rng.randrange(1, 6)
            expected: list[int] = []
            for start in range(0, len(values), k):
                chunk = values[start : start + k]
                expected += chunk[::-1] if len(chunk) == k else chunk
            self.assertEqual(to_list(reverse_k_group(from_list(values), k)), expected)

    def test_merge(self):
        rng = random.Random(3)
        for _ in range(200):
            first, second = sorted(random_values(rng)), sorted(random_values(rng))
            merged = merge_two_lists(from_list(first), from_list(second))
            self.assertEqual(to_list(merged), sorted(first + second))

    def test_cycle(self):
        rng = random.Random(4)
        for _ in range(300):
            nodes = nodes_of(from_list(range(rng.randrange(1, 12))))
            entry = rng.randrange(-1, len(nodes))
            if entry >= 0:
                nodes[-1].next = nodes[entry]
            expected = nodes[entry] if entry >= 0 else None
            self.assertIs(detect_cycle(nodes[0]), expected)
            self.assertEqual(has_cycle(nodes[0]), entry >= 0)
        self.assertIsNone(detect_cycle(None))

    def test_find_duplicate(self):
        rng = random.Random(5)
        for _ in range(300):
            n = rng.randrange(1, 12)
            duplicate = rng.randrange(1, n + 1)
            others = rng.sample(range(1, n + 1), rng.randrange(n))
            others = [v for v in others if v != duplicate]
            nums = [duplicate] * (n + 1 - len(others)) + others
            rng.shuffle(nums)
            self.assertEqual(find_duplicate(nums), duplicate)

    def test_examples(self):
        self.assertEqual(
            to_list(reverse_k_group(from_list([1, 2, 3, 4, 5]), 2)), [2, 1, 4, 3, 5]
        )
        self.assertEqual(to_list(middle_node(from_list([1, 2, 3, 4, 5, 6]))), [4, 5, 6])
        self.assertEqual(
            to_list(merge_two_lists(from_list([1, 2, 4]), from_list([1, 3, 4]))),
            [1, 1, 2, 3, 4, 4],
        )
        self.assertEqual(find_duplicate([1, 3, 4, 2, 2]), 2)
        self.assertEqual(find_duplicate([3, 3, 3, 3, 3]), 3)


if __name__ == "__main__":
    unittest.main()
