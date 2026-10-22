# LRU and LFU caches

Bounded key-value caches with O(1) `get` and `put` that evict the least recently or least frequently used key.

## My solution

- LRU = hash map + doubly linked list ordered by recency. The map finds a key's node in O(1); the list moves that node to the "most recent" end and drops the "least recent" end in O(1). Neither structure alone does both.
- The list must be doubly linked so a node can unlink itself without searching for its predecessor, and each node stores its key so eviction can also delete the map entry.
- Sentinel `head` and `tail` nodes are never removed, so unlink and append have no `None` checks for empty lists or end nodes.
- Python shortcut: `collections.OrderedDict` is exactly this structure; `move_to_end(key)` on access and `popitem(last=False)` on eviction give a few-line LRU.
- C++ uses `std::list` plus `unordered_map` of list iterators; `splice` moves a node to the front without invalidating any iterator.
- LFU adds a frequency dimension: `key -> (value, freq)` and `freq -> keys in use order`. A use moves the key from bucket f to the end of bucket f + 1.
- `min_freq` makes eviction O(1): it only rises by one when a touched key empties the minimum bucket, and resets to 1 on every insertion of a new key. Evict the oldest key in bucket `min_freq`, which breaks frequency ties by recency.

## Complexity

O(1) average time per `get` and `put` (hash map operations) and O(capacity) space for both caches.

## Usage and assumptions

`LRUCache(capacity)` and `LFUCache(capacity)` provide `get(key)`, returning -1 when missing, and `put(key, value)`. Both `get` and updating `put` count as a use. A capacity of zero or less stores nothing. Keys and values are integers as in LeetCode. C++ classes `LRUCache` and `LFUCache` have the same `get`/`put` interface.

```python
from Cache.Cache import LFUCache, LRUCache

lru = LRUCache(2)
lru.put(1, 1)
lru.put(2, 2)
lru.get(1)
lru.put(3, 3)
assert lru.get(2) == -1

lfu = LFUCache(2)
lfu.put(1, 1)
lfu.put(2, 2)
lfu.get(1)
lfu.put(3, 3)
assert lfu.get(2) == -1 and lfu.get(1) == 1
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

New snippet.

## LeetCode problems

- [146. LRU Cache](https://leetcode.com/problems/lru-cache/)
- [460. LFU Cache](https://leetcode.com/problems/lfu-cache/)
- [432. All O\`one Data Structure](https://leetcode.com/problems/all-oone-data-structure/) — count buckets in a linked list, like LFU
- [1472. Design Browser History](https://leetcode.com/problems/design-browser-history/) — doubly linked list navigation
- [707. Design Linked List](https://leetcode.com/problems/design-linked-list/) — sentinel nodes

## Tests

[`test_Cache.py`](test_Cache.py) checks the Python implementation; [`test_Cache.cpp`](test_Cache.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s Cache -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
