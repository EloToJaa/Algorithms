import random
import unittest

from Cache.Cache import LFUCache, LRUCache


class ReferenceCache:
    """Brute force: entries key -> [value, frequency, last use]; evict by scan."""

    def __init__(self, capacity: int, by_frequency: bool) -> None:
        self.capacity = capacity
        self.by_frequency = by_frequency
        self.entries: dict[int, list[int]] = {}
        self.clock = 0

    def _use(self, key: int) -> None:
        self.clock += 1
        self.entries[key][1] += 1
        self.entries[key][2] = self.clock

    def get(self, key: int) -> int:
        if key not in self.entries:
            return -1
        self._use(key)
        return self.entries[key][0]

    def put(self, key: int, value: int) -> None:
        if self.capacity <= 0:
            return
        if key not in self.entries and len(self.entries) == self.capacity:
            if self.by_frequency:
                victim = min(self.entries, key=lambda k: self.entries[k][1:])
            else:
                victim = min(self.entries, key=lambda k: self.entries[k][2])
            del self.entries[victim]
        if key not in self.entries:
            self.entries[key] = [value, 0, 0]
        self.entries[key][0] = value
        self._use(key)


class TestCache(unittest.TestCase):
    def check(self, cache_type: type, by_frequency: bool, seed: int) -> None:
        rng = random.Random(seed)
        for _ in range(200):
            capacity = rng.randrange(4)
            cache, reference = (
                cache_type(capacity),
                ReferenceCache(capacity, by_frequency),
            )
            for _ in range(60):
                key = rng.randrange(6)
                if rng.random() < 0.5:
                    self.assertEqual(cache.get(key), reference.get(key))
                else:
                    value = rng.randrange(100)
                    cache.put(key, value)
                    reference.put(key, value)

    def test_lru_against_reference(self):
        self.check(LRUCache, False, 1)

    def test_lfu_against_reference(self):
        self.check(LFUCache, True, 2)

    def test_examples(self):
        lru = LRUCache(2)
        lru.put(1, 1)
        lru.put(2, 2)
        self.assertEqual(lru.get(1), 1)
        lru.put(3, 3)
        self.assertEqual(lru.get(2), -1)
        lru.put(4, 4)
        self.assertEqual([lru.get(1), lru.get(3), lru.get(4)], [-1, 3, 4])

        lfu = LFUCache(2)
        lfu.put(1, 1)
        lfu.put(2, 2)
        self.assertEqual(lfu.get(1), 1)
        lfu.put(3, 3)
        self.assertEqual([lfu.get(2), lfu.get(3)], [-1, 3])
        lfu.put(4, 4)
        self.assertEqual([lfu.get(1), lfu.get(3), lfu.get(4)], [-1, 3, 4])


if __name__ == "__main__":
    unittest.main()
