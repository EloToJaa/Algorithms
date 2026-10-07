"""Monotone queue supporting FIFO removal and maximum queries."""

from collections import deque
from math import inf


class MonoQueue:
    def __init__(self):
        self.queue = deque()
        self.pushes = 0
        self.pops = 0

    def push(self, value):
        while self.queue and self.queue[-1][0] <= value:
            self.queue.pop()
        self.pushes += 1
        self.queue.append((value, self.pushes))

    def pop(self):
        """Discard the oldest input; caller must ensure the logical queue is nonempty."""
        self.pops += 1
        if self.queue and self.queue[0][1] == self.pops:
            self.queue.popleft()

    def max(self):
        return self.queue[0][0] if self.queue else -inf
