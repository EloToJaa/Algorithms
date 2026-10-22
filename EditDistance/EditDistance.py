"""Levenshtein edit distance with operation reconstruction and a linear-space variant."""

from collections.abc import Sequence
from typing import TypeVar

T = TypeVar("T")

# ("keep", x), ("replace", x, y), ("delete", x), or ("insert", y), left to right.
Operation = tuple[object, ...]


def edit_distance_table(first: Sequence[T], second: Sequence[T]) -> list[list[int]]:
    """table[i][j] is the edit distance between first[:i] and second[:j]."""
    n, m = len(first), len(second)
    table = [
        [i + j if i == 0 or j == 0 else 0 for j in range(m + 1)] for i in range(n + 1)
    ]
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            if first[i - 1] == second[j - 1]:
                table[i][j] = table[i - 1][j - 1]
                continue
            table[i][j] = 1 + min(
                table[i - 1][j - 1],  # replace
                table[i - 1][j],  # delete first[i - 1]
                table[i][j - 1],  # insert second[j - 1]
            )
    return table


def edit_operations(first: Sequence[T], second: Sequence[T]) -> list[Operation]:
    """One optimal alignment as ops consuming first and producing second in order."""
    table = edit_distance_table(first, second)
    ops: list[Operation] = []
    i, j = len(first), len(second)
    while i > 0 or j > 0:
        diagonal = table[i - 1][j - 1] if i > 0 and j > 0 else None
        if diagonal is not None and first[i - 1] == second[j - 1]:
            ops.append(("keep", first[i - 1]))
            i, j = i - 1, j - 1
        elif diagonal is not None and table[i][j] == diagonal + 1:
            ops.append(("replace", first[i - 1], second[j - 1]))
            i, j = i - 1, j - 1
        elif i > 0 and table[i][j] == table[i - 1][j] + 1:
            ops.append(("delete", first[i - 1]))
            i -= 1
        else:
            ops.append(("insert", second[j - 1]))
            j -= 1
    ops.reverse()
    return ops


def edit_distance(first: Sequence[T], second: Sequence[T]) -> int:
    """Distance only, keeping one row of length min(n, m) + 1."""
    if len(first) < len(second):
        first, second = second, first
    row = list(range(len(second) + 1))
    for i, a in enumerate(first, 1):
        diagonal, row[0] = row[0], i  # diagonal holds the old row[j - 1]
        for j, b in enumerate(second, 1):
            above = row[j]
            row[j] = diagonal if a == b else 1 + min(diagonal, above, row[j - 1])
            diagonal = above
    return row[-1]
