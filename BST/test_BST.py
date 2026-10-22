import random
import unittest
from bisect import bisect_left

from BST.BST import BST


class TestBST(unittest.TestCase):
    def test_against_sorted_list(self):
        rng = random.Random(9)
        tree: BST[int] = BST()
        reference: list[int] = []
        for _ in range(3000):
            key = rng.randrange(-30, 30)
            operation = rng.randrange(3)
            if operation == 0:
                self.assertEqual(tree.insert(key), key not in reference)
                if key not in reference:
                    reference.insert(bisect_left(reference, key), key)
            elif operation == 1:
                self.assertEqual(tree.remove(key), key in reference)
                if key in reference:
                    reference.remove(key)
            else:
                position = bisect_left(reference, key)
                expected = reference[position] if position < len(reference) else None
                self.assertEqual(tree.lower_bound(key), expected)
            self.assertEqual(key in tree, key in reference)
            self.assertEqual(list(tree), reference)
            self.assertEqual(len(tree), len(reference))
            if reference:
                self.assertEqual(tree.min(), reference[0])
                self.assertEqual(tree.max(), reference[-1])

    def test_deep_chain_and_empty(self):
        tree = BST(range(5000))
        self.assertEqual(list(tree), list(range(5000)))
        for key in range(5000):
            self.assertTrue(tree.remove(key))
        self.assertEqual(len(tree), 0)
        self.assertIsNone(tree.lower_bound(0))
        with self.assertRaises(ValueError):
            tree.min()


if __name__ == "__main__":
    unittest.main()
