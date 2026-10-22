import random
import unittest
from itertools import combinations

from LCS.LCS import lcs, lcs_length


def is_subsequence(candidate: str, text: str) -> bool:
    remaining = iter(text)
    return all(character in remaining for character in candidate)


class TestLCS(unittest.TestCase):
    def test_against_subsets(self):
        rng = random.Random(5)
        for _ in range(200):
            first = "".join(rng.choice("abc") for _ in range(rng.randrange(8)))
            second = "".join(rng.choice("abc") for _ in range(rng.randrange(8)))
            expected = max(
                (
                    size
                    for size in range(len(first) + 1)
                    for chosen in combinations(first, size)
                    if is_subsequence("".join(chosen), second)
                ),
                default=0,
            )
            common = "".join(lcs(first, second))
            self.assertEqual(lcs_length(first, second), expected)
            self.assertEqual(len(common), expected)
            self.assertTrue(is_subsequence(common, first))
            self.assertTrue(is_subsequence(common, second))

    def test_examples(self):
        self.assertEqual("".join(lcs("abcde", "ace")), "ace")
        self.assertEqual(lcs_length("abc", "def"), 0)
        self.assertEqual(lcs([1, 3, 4, 1], [3, 4, 1, 2, 1]), [3, 4, 1])


if __name__ == "__main__":
    unittest.main()
