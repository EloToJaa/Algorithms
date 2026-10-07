"""Offline distinct-element range queries with Mo's ordering."""

from collections import defaultdict
from math import isqrt


def distinct_counts(values, queries):
    """Queries are zero-based inclusive (left, right); answers retain input order."""
    block = max(1, isqrt(len(values)))
    ordered = sorted(
        enumerate(queries), key=lambda item: (item[1][0] // block, item[1][1])
    )
    counts = defaultdict(int)
    answers = [0] * len(queries)
    left, right, distinct = 0, -1, 0

    def add(index):
        nonlocal distinct
        value = values[index]
        if counts[value] == 0:
            distinct += 1
        counts[value] += 1

    def remove(index):
        nonlocal distinct
        value = values[index]
        counts[value] -= 1
        if counts[value] == 0:
            distinct -= 1

    for index, (start, end) in ordered:
        while left > start:
            left -= 1
            add(left)
        while right < end:
            right += 1
            add(right)
        while left < start:
            remove(left)
            left += 1
        while right > end:
            remove(right)
            right -= 1
        answers[index] = distinct
    return answers
