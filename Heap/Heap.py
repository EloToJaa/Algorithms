"""One-based binary min and max heaps with sift-up and sift-down."""


class MinHeap:
    def __init__(self, values=()):
        self.heap = [None]
        for value in values:
            self.insert(value)

    def _before(self, first, second):
        return first < second

    def insert(self, value):
        self.heap.append(value)
        index = len(self.heap) - 1
        while index > 1 and self._before(self.heap[index], self.heap[index // 2]):
            self.heap[index], self.heap[index // 2] = (
                self.heap[index // 2],
                self.heap[index],
            )
            index //= 2

    def _sift_down(self):
        index = 1
        while 2 * index < len(self.heap):
            child = 2 * index
            if child + 1 < len(self.heap) and self._before(
                self.heap[child + 1], self.heap[child]
            ):
                child += 1
            if not self._before(self.heap[child], self.heap[index]):
                return
            self.heap[index], self.heap[child] = self.heap[child], self.heap[index]
            index = child

    def top(self):
        return self.heap[1]

    def remove(self):
        """Remove and return the root; requires a nonempty heap."""
        value = self.top()
        last = self.heap.pop()
        if not self.empty():
            self.heap[1] = last
            self._sift_down()
        return value

    def replace(self, value):
        """Replace the root; requires a nonempty heap."""
        previous = self.top()
        self.heap[1] = value
        self._sift_down()
        return previous

    def size(self):
        return len(self.heap) - 1

    def empty(self):
        return self.size() == 0


class MaxHeap(MinHeap):
    def _before(self, first, second):
        return first > second
