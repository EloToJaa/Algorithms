import random
import unittest

from SparseTable.SparseTable import SparseTable


class TestSparseTable(unittest.TestCase):
    def test_all_ranges(self):
        rng = random.Random(23)
        for size in range(1, 50):
            values = [rng.randrange(-100, 101) for _ in range(size)]
            table = SparseTable(values)
            values_copy = values.copy()
            values[0] = 999
            for left in range(size):
                for right in range(left, size):
                    self.assertEqual(
                        table.query(left, right), min(values_copy[left : right + 1])
                    )
        self.assertEqual(SparseTable([10**100, -(10**100)]).query(0, 1), -(10**100))

    def test_invalid_ranges(self):
        for values, interval in (
            ([], (0, 0)),
            ([1], (-1, 0)),
            ([1], (0, 1)),
            ([1, 2], (1, 0)),
        ):
            with self.assertRaises(ValueError):
                SparseTable(values).query(*interval)


if __name__ == "__main__":
    unittest.main()
