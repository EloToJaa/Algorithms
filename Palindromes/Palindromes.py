"""Quadratic palindrome DPs: substring table, longest subsequence, minimum cuts."""

from collections.abc import Sequence


def palindrome_table(text: Sequence[object]) -> list[list[bool]]:
    """table[i][j] tells whether text[i..j] (inclusive) is a palindrome."""
    n = len(text)
    table = [[False] * n for _ in range(n)]
    for i in range(n - 1, -1, -1):
        for j in range(i, n):
            table[i][j] = text[i] == text[j] and (j - i < 2 or table[i + 1][j - 1])
    return table


def longest_palindromic_subsequence(text: Sequence[object]) -> int:
    n = len(text)
    # best[i][j] is the answer for text[i..j]; empty intervals stay 0.
    best = [[0] * n for _ in range(n)]
    for i in range(n - 1, -1, -1):
        best[i][i] = 1
        for j in range(i + 1, n):
            if text[i] == text[j]:
                best[i][j] = best[i + 1][j - 1] + 2
            else:
                best[i][j] = max(best[i + 1][j], best[i][j - 1])
    return best[0][n - 1] if n else 0


def min_palindrome_cuts(text: Sequence[object]) -> int:
    """Fewest cuts splitting text into palindromic pieces; 0 for empty text."""
    if not text:
        return 0
    table = palindrome_table(text)
    # cuts[j] is the answer for text[:j]; cuts[0] = -1 cancels the first cut.
    cuts = [-1] + [len(text)] * len(text)
    for j in range(1, len(text) + 1):
        for i in range(j):
            if table[i][j - 1]:
                cuts[j] = min(cuts[j], cuts[i] + 1)
    return cuts[len(text)]
