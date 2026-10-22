import random
import unittest
from itertools import combinations

from Palindromes.Palindromes import (
    longest_palindromic_subsequence,
    min_palindrome_cuts,
    palindrome_table,
)


def fewest_pieces(text: str) -> int:
    """pieces[start] is the fewest palindromes covering text[start:]."""
    n = len(text)
    pieces = [0] * (n + 1)
    for start in range(n - 1, -1, -1):
        pieces[start] = min(
            1 + pieces[end]
            for end in range(start + 1, n + 1)
            if text[start:end] == text[start:end][::-1]
        )
    return pieces[0]


class TestPalindromes(unittest.TestCase):
    def test_against_brute_force(self):
        rng = random.Random(6)
        for _ in range(200):
            text = "".join(rng.choice("ab") for _ in range(rng.randrange(10)))
            n = len(text)
            table = palindrome_table(text)
            for i in range(n):
                for j in range(i, n):
                    piece = text[i : j + 1]
                    self.assertEqual(table[i][j], piece == piece[::-1])

            longest = max(
                (
                    size
                    for size in range(n + 1)
                    for chosen in combinations(text, size)
                    if chosen == chosen[::-1]
                ),
                default=0,
            )
            self.assertEqual(longest_palindromic_subsequence(text), longest)
            self.assertEqual(min_palindrome_cuts(text), max(fewest_pieces(text) - 1, 0))

    def test_examples(self):
        self.assertEqual(longest_palindromic_subsequence("bbbab"), 4)
        self.assertEqual(min_palindrome_cuts("aab"), 1)
        self.assertEqual(min_palindrome_cuts("racecar"), 0)
        self.assertEqual(min_palindrome_cuts(""), 0)


if __name__ == "__main__":
    unittest.main()
