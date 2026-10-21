"""Length of a strictly increasing subsequence using minimal tails."""

from bisect import bisect_left
from collections.abc import Iterable


def lis_length(values: Iterable[float]) -> int:
    tails: list[float] = []
    for value in values:
        position = bisect_left(tails, value)
        if position == len(tails):
            tails.append(value)
        else:
            tails[position] = value
    return len(tails)
