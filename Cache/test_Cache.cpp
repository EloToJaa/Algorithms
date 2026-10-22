#include "Cache.cpp"
#include <cassert>

// Brute force: key -> {value, frequency, last use}; evict by linear scan.
struct ReferenceCache {
  int capacity;
  bool byFrequency;
  int clock = 0;
  std::map<int, std::array<int, 3>> entries;

  void use(int key) {
    entries[key][1]++;
    entries[key][2] = ++clock;
  }

  int get(int key) {
    if (!entries.count(key))
      return -1;
    use(key);
    return entries[key][0];
  }

  void put(int key, int value) {
    if (capacity <= 0)
      return;
    if (!entries.count(key) && int(entries.size()) == capacity) {
      auto victim = entries.begin();
      for (auto it = entries.begin(); it != entries.end(); ++it) {
        auto rank = [&](auto entry) {
          return std::make_pair(byFrequency ? entry->second[1] : 0,
                                entry->second[2]);
        };
        if (rank(it) < rank(victim))
          victim = it;
      }
      entries.erase(victim);
    }
    if (!entries.count(key))
      entries[key] = {value, 0, 0};
    entries[key][0] = value;
    use(key);
  }
};

template <typename Cache> void check(bool byFrequency, unsigned seed) {
  std::mt19937 rng(seed);
  for (int iteration = 0; iteration < 200; ++iteration) {
    int capacity = int(rng() % 4);
    Cache cache(capacity);
    ReferenceCache reference{capacity, byFrequency};
    for (int step = 0; step < 60; ++step) {
      int key = int(rng() % 6);
      if (rng() % 2) {
        assert(cache.get(key) == reference.get(key));
      } else {
        int value = int(rng() % 100);
        cache.put(key, value);
        reference.put(key, value);
      }
    }
  }
}

int main() {
  check<LRUCache>(false, 1);
  check<LFUCache>(true, 2);

  LRUCache lru(2);
  lru.put(1, 1);
  lru.put(2, 2);
  assert(lru.get(1) == 1);
  lru.put(3, 3);
  assert(lru.get(2) == -1);
  lru.put(4, 4);
  assert(lru.get(1) == -1 && lru.get(3) == 3 && lru.get(4) == 4);

  LFUCache lfu(2);
  lfu.put(1, 1);
  lfu.put(2, 2);
  assert(lfu.get(1) == 1);
  lfu.put(3, 3);
  assert(lfu.get(2) == -1 && lfu.get(3) == 3);
  lfu.put(4, 4);
  assert(lfu.get(1) == -1 && lfu.get(3) == 3 && lfu.get(4) == 4);
}
