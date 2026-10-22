"""Longest common subsequence with a two-dimensional DP and backtracking."""

from collections.abc import Sequence
from typing import TypeVar

T = TypeVar("T")


def lcs_table(first: Sequence[T], second: Sequence[T]) -> list[list[int]]:
    """table[i][j] is the LCS length of first[:i] and second[:j]."""
    table = [[0] * (len(second) + 1) for _ in range(len(first) + 1)]
    for i, a in enumerate(first, 1):
        for j, b in enumerate(second, 1):
            if a == b:
                table[i][j] = table[i - 1][j - 1] + 1
            else:
                table[i][j] = max(table[i - 1][j], table[i][j - 1])
    return table


def lcs_length(first: Sequence[T], second: Sequence[T]) -> int:
    return lcs_table(first, second)[len(first)][len(second)]


def lcs(first: Sequence[T], second: Sequence[T]) -> list[T]:
    """Return one longest common subsequence."""
    table = lcs_table(first, second)
    result: list[T] = []
    i, j = len(first), len(second)
    while i > 0 and j > 0:
        if first[i - 1] == second[j - 1]:
            result.append(first[i - 1])
            i -= 1
            j -= 1
        elif table[i - 1][j] >= table[i][j - 1]:
            i -= 1
        else:
            j -= 1
    result.reverse()
    return result
