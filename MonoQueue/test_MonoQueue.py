import random
import unittest

from MonoQueue.MonoQueue import MonoQueue


class TestMonoQueue(unittest.TestCase):
    def test_against_fifo_maximum(self):
        from collections import deque

        queue, reference = MonoQueue(), deque()
        rng = random.Random(11)
        for _ in range(500):
            if not reference or rng.random() < 0.6:
                value = rng.randrange(-10, 11)
                queue.push(value)
                reference.append(value)
            else:
                queue.pop()
                reference.popleft()
            self.assertEqual(queue.max(), max(reference, default=float("-inf")))


if __name__ == "__main__":
    unittest.main()
