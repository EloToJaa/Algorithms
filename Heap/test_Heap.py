import random
import unittest

from Heap.Heap import MaxHeap, MinHeap


class TestHeap(unittest.TestCase):
    def test_order_replacement_and_reuse(self):
        rng = random.Random(12)
        values = [rng.randrange(-30, 31) for _ in range(100)]
        for heap_type, descending in ((MinHeap, False), (MaxHeap, True)):
            heap = heap_type(values)
            self.assertEqual(heap.size(), len(values))
            self.assertEqual(
                [heap.remove() for _ in values], sorted(values, reverse=descending)
            )
            self.assertTrue(heap.empty())
            heap.insert(5)
            heap.insert(10)
            previous = heap.replace(7)
            self.assertEqual(previous, 10 if descending else 5)
            self.assertEqual(
                [heap.remove(), heap.remove()], [7, 5] if descending else [7, 10]
            )
            with self.assertRaises(IndexError):
                heap.top()


if __name__ == "__main__":
    unittest.main()
