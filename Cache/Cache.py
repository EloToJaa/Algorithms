"""LRU and LFU caches with O(1) get and put."""

from __future__ import annotations


class _Node:
    __slots__ = ("key", "value", "prev", "next")

    def __init__(self, key: int = 0, value: int = 0) -> None:
        self.key = key
        self.value = value
        self.prev: _Node = self
        self.next: _Node = self


class LRUCache:
    """Hash map to list nodes; the list runs from least to most recently used.

    Sentinel head/tail nodes mean unlink and append never special-case an
    empty list or an end node.
    """

    def __init__(self, capacity: int) -> None:
        self.capacity = capacity
        self.nodes: dict[int, _Node] = {}
        self.head, self.tail = _Node(), _Node()
        self.head.next, self.tail.prev = self.tail, self.head

    def _unlink(self, node: _Node) -> None:
        node.prev.next, node.next.prev = node.next, node.prev

    def _append(self, node: _Node) -> None:
        node.prev, node.next = self.tail.prev, self.tail
        self.tail.prev.next = node
        self.tail.prev = node

    def get(self, key: int) -> int:
        """Return the value and mark it most recent, or -1 if missing."""
        node = self.nodes.get(key)
        if node is None:
            return -1
        self._unlink(node)
        self._append(node)
        return node.value

    def put(self, key: int, value: int) -> None:
        """Insert or update; evict the least recently used key when full."""
        if self.capacity <= 0:
            return
        node = self.nodes.get(key)
        if node is not None:
            node.value = value
            self._unlink(node)
            self._append(node)
            return
        if len(self.nodes) == self.capacity:
            oldest = self.head.next
            self._unlink(oldest)
            del self.nodes[oldest.key]
        node = _Node(key, value)
        self.nodes[key] = node
        self._append(node)


class LFUCache:
    """Evict the least frequently used key, least recently used among ties.

    keys maps key -> [value, frequency]; buckets maps frequency -> keys in
    use order (dicts keep insertion order, so the first key is the oldest).
    """

    def __init__(self, capacity: int) -> None:
        self.capacity = capacity
        self.keys: dict[int, list[int]] = {}
        self.buckets: dict[int, dict[int, None]] = {}
        self.min_freq = 0

    def _touch(self, key: int) -> None:
        entry = self.keys[key]
        bucket = self.buckets[entry[1]]
        del bucket[key]
        if not bucket:
            del self.buckets[entry[1]]
            if self.min_freq == entry[1]:
                self.min_freq += 1
        entry[1] += 1
        self.buckets.setdefault(entry[1], {})[key] = None

    def get(self, key: int) -> int:
        """Return the value and bump its frequency, or -1 if missing."""
        if key not in self.keys:
            return -1
        self._touch(key)
        return self.keys[key][0]

    def put(self, key: int, value: int) -> None:
        """Insert or update (counts as a use); evict when full."""
        if self.capacity <= 0:
            return
        if key in self.keys:
            self.keys[key][0] = value
            self._touch(key)
            return
        if len(self.keys) == self.capacity:
            bucket = self.buckets[self.min_freq]
            victim = next(iter(bucket))
            del bucket[victim]
            if not bucket:
                del self.buckets[self.min_freq]
            del self.keys[victim]
        self.keys[key] = [value, 1]
        self.buckets.setdefault(1, {})[key] = None
        self.min_freq = 1
