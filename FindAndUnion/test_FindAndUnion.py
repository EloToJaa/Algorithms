import unittest

from FindAndUnion.FindAndUnion import DisjointSet


class TestFindAndUnion(unittest.TestCase):
    def test_repeated_union_and_sizes(self):
        sets = DisjointSet(5)
        self.assertTrue(sets.union(0, 1))
        self.assertFalse(sets.union(1, 0))
        self.assertFalse(sets.union(0, 0))
        self.assertEqual(sets.size[sets.find(0)], 2)
        sets.union(2, 3)
        sets.union(1, 2)
        self.assertEqual(sets.size[sets.find(3)], 4)
        self.assertNotEqual(sets.find(4), sets.find(0))


if __name__ == "__main__":
    unittest.main()
