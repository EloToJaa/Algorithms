import random
import unittest
from itertools import combinations

from Intervals.Intervals import (
    erase_overlap_intervals,
    insert_interval,
    merge_intervals,
    min_meeting_rooms,
)


def brute_merge(intervals: list[list[int]]) -> list[list[int]]:
    # Doubled coordinates: a gap between integers x and x + 1 is the odd point 2x + 1.
    covered = {p for start, end in intervals for p in range(2 * start, 2 * end + 1)}
    result: list[list[int]] = []
    for p in sorted(covered):
        if result and p - 1 in covered:
            result[-1][1] = p // 2
        else:
            result.append([p // 2, p // 2])
    return result


def overlaps(a: list[int], b: list[int]) -> bool:
    return a[0] < b[1] and b[0] < a[1]


def random_intervals(rng: random.Random, count: int) -> list[list[int]]:
    result = []
    for _ in range(count):
        start = rng.randrange(15)
        result.append([start, start + rng.randrange(1, 6)])
    return result


class TestIntervals(unittest.TestCase):
    def test_merge_and_insert(self):
        rng = random.Random(3)
        for _ in range(300):
            intervals = [
                [s, s + rng.randrange(4)]
                for s in (rng.randrange(15) for _ in range(rng.randrange(7)))
            ]
            self.assertEqual(merge_intervals(intervals), brute_merge(intervals))
            start = rng.randrange(18)
            new = [start, start + rng.randrange(5)]
            disjoint = brute_merge(intervals)
            self.assertEqual(
                insert_interval(disjoint, new), brute_merge(disjoint + [new])
            )

    def test_removals_and_rooms(self):
        rng = random.Random(4)
        for _ in range(300):
            intervals = random_intervals(rng, rng.randrange(8))
            kept = max(
                size
                for size in range(len(intervals) + 1)
                for chosen in combinations(intervals, size)
                if not any(overlaps(a, b) for a, b in combinations(chosen, 2))
            )
            self.assertEqual(erase_overlap_intervals(intervals), len(intervals) - kept)
            rooms = max(
                (sum(s <= t < e for s, e in intervals) for t in range(25)), default=0
            )
            self.assertEqual(min_meeting_rooms(intervals), rooms)

    def test_examples(self):
        self.assertEqual(
            merge_intervals([[1, 3], [2, 6], [8, 10], [15, 18]]),
            [[1, 6], [8, 10], [15, 18]],
        )
        self.assertEqual(merge_intervals([[1, 4], [4, 5]]), [[1, 5]])
        self.assertEqual(insert_interval([[1, 3], [6, 9]], [2, 5]), [[1, 5], [6, 9]])
        self.assertEqual(
            insert_interval([[1, 2], [3, 5], [6, 7], [8, 10], [12, 16]], [4, 8]),
            [[1, 2], [3, 10], [12, 16]],
        )
        self.assertEqual(insert_interval([], [5, 7]), [[5, 7]])
        self.assertEqual(erase_overlap_intervals([[1, 2], [2, 3], [3, 4], [1, 3]]), 1)
        self.assertEqual(erase_overlap_intervals([[1, 2], [1, 2], [1, 2]]), 2)
        self.assertEqual(min_meeting_rooms([[0, 30], [5, 10], [15, 20]]), 2)
        self.assertEqual(min_meeting_rooms([[7, 10], [2, 4]]), 1)


if __name__ == "__main__":
    unittest.main()
