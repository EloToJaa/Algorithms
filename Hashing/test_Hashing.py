import unittest

from Hashing.Hashing import Hash


class TestHashing(unittest.TestCase):
    def test_substrings_against_direct_polynomial(self):
        text = "abacabadabacaba"
        hashes = Hash(text)
        for left in range(len(text) + 1):
            for right in range(left, len(text) + 1):
                expected = []
                for base in (29, 31):
                    value = 0
                    for char in text[left:right]:
                        value = (
                            value * base + ord(char) - ord("a") + 1
                        ) % 1_000_000_007
                    expected.append(value)
                self.assertEqual(hashes.get_hash(left, right), tuple(expected))
        self.assertEqual(hashes.get_hash(0, 3), hashes.get_hash(4, 7))
        self.assertEqual(hashes.get_hash(0, 3), Hash("aba").get_hash())


if __name__ == "__main__":
    unittest.main()
