import unittest

from BinSearch.BinSearch import search_first, search_last


class TestBinSearch(unittest.TestCase):
    def test_monotone_boundaries(self):
        for boundary in range(-1, 12):
            first = next((x for x in range(10) if x >= boundary), 10)
            last = next((x for x in reversed(range(10)) if x <= boundary), -1)
            self.assertEqual(
                search_first(0, 9, lambda x, boundary=boundary: x >= boundary), first
            )
            self.assertEqual(
                search_last(0, 9, lambda x, boundary=boundary: x <= boundary), last
            )
        self.assertEqual(search_first(3, 2, lambda _: True), 3)
        self.assertEqual(search_last(3, 2, lambda _: True), 2)


if __name__ == "__main__":
    unittest.main()
