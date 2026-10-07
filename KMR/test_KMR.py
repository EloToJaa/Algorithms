import random
import unittest

from KMR.KMR import KMR


class TestKMR(unittest.TestCase):
    def test_suffixes_lcp_and_substring_comparison(self):
        rng = random.Random(14)
        for text in ["", "banana", "aaaaa"] + [
            "".join(rng.choices("abc", k=rng.randrange(1, 30))) for _ in range(40)
        ]:
            table = KMR(text)
            suffixes = sorted(range(len(text)), key=lambda i: text[i:])
            self.assertEqual(table.suffix_array, suffixes)
            for position in range(1, len(text)):
                a, b = text[suffixes[position - 1] :], text[suffixes[position] :]
                common = 0
                while common < min(len(a), len(b)) and a[common] == b[common]:
                    common += 1
                self.assertEqual(table.lcp[position], common)
            for _ in range(50):
                a, b = sorted(rng.choices(range(len(text) + 1), k=2))
                c, d = sorted(rng.choices(range(len(text) + 1), k=2))
                x, y = text[a:b], text[c:d]
                expected = 0 if x < y else 2 if x > y else 1
                self.assertEqual(table.compare(a, b, c, d), expected)


if __name__ == "__main__":
    unittest.main()
