import random
import unittest

from KMP.KMP import find_matches, prefix_function


class TestKMP(unittest.TestCase):
    def test_matches_and_prefixes(self):
        rng = random.Random(4)
        for _ in range(100):
            text = "".join(rng.choices("ab#", k=rng.randrange(30)))
            pattern = "".join(rng.choices("ab#", k=rng.randrange(6)))
            expected = [i for i in range(len(text) + 1) if text.startswith(pattern, i)]
            self.assertEqual(find_matches(text, pattern), expected)
            expected_prefix = [
                max(
                    (k for k in range(1, i + 1) if text[:k] == text[i - k + 1 : i + 1]),
                    default=0,
                )
                for i in range(len(text))
            ]
            self.assertEqual(prefix_function(text), expected_prefix)


if __name__ == "__main__":
    unittest.main()
