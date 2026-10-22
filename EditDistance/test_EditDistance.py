import random
import unittest
from functools import cache

from EditDistance.EditDistance import (
    edit_distance,
    edit_distance_table,
    edit_operations,
)


def brute_distance(first: str, second: str) -> int:
    @cache
    def go(i: int, j: int) -> int:
        if i == len(first) or j == len(second):
            return len(first) - i + len(second) - j
        if first[i] == second[j]:
            return go(i + 1, j + 1)
        return 1 + min(go(i + 1, j + 1), go(i + 1, j), go(i, j + 1))

    return go(0, 0)


def apply(ops: list[tuple[object, ...]]) -> tuple[list[object], list[object]]:
    """Return (consumed source, produced target) of an operation list."""
    consumed: list[object] = []
    produced: list[object] = []
    for op in ops:
        kind = op[0]
        if kind == "keep":
            consumed.append(op[1])
            produced.append(op[1])
        elif kind == "replace":
            assert op[1] != op[2]
            consumed.append(op[1])
            produced.append(op[2])
        elif kind == "delete":
            consumed.append(op[1])
        elif kind == "insert":
            produced.append(op[1])
        else:
            raise AssertionError(kind)
    return consumed, produced


class TestEditDistance(unittest.TestCase):
    def test_against_recursion(self):
        rng = random.Random(9)
        for _ in range(400):
            first = "".join(rng.choice("abc") for _ in range(rng.randrange(8)))
            second = "".join(rng.choice("abc") for _ in range(rng.randrange(8)))
            expected = brute_distance(first, second)
            self.assertEqual(edit_distance(first, second), expected)
            table = edit_distance_table(first, second)
            self.assertEqual(table[len(first)][len(second)], expected)
            ops = edit_operations(first, second)
            consumed, produced = apply(ops)
            self.assertEqual("".join(map(str, consumed)), first)
            self.assertEqual("".join(map(str, produced)), second)
            self.assertEqual(sum(op[0] != "keep" for op in ops), expected)

    def test_examples(self):
        self.assertEqual(edit_distance("horse", "ros"), 3)
        self.assertEqual(edit_distance("intention", "execution"), 5)
        self.assertEqual(edit_distance("", "abc"), 3)
        self.assertEqual(edit_operations("ab", "b"), [("delete", "a"), ("keep", "b")])
        self.assertEqual(edit_distance([1, 2, 3], [1, 3]), 1)


if __name__ == "__main__":
    unittest.main()
