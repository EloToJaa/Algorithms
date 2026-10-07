import unittest

from Trie.Trie import Trie


class TestTrie(unittest.TestCase):
    def test_words_prefixes_and_empty_word(self):
        trie = Trie()
        for word in ("apple", "app", "banana", "apple"):
            trie.insert(word)
        self.assertTrue(trie.search("app"))
        self.assertFalse(trie.search("ap"))
        self.assertTrue(trie.starts_with("ap"))
        self.assertFalse(trie.starts_with("cat"))
        self.assertFalse(trie.search(""))
        self.assertTrue(trie.starts_with(""))
        trie.insert("")
        self.assertTrue(trie.search(""))


if __name__ == "__main__":
    unittest.main()
