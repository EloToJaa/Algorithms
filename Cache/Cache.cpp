#include <bits/stdc++.h>

// List runs from most to least recently used; the map stores list iterators,
// which stay valid across splice.
class LRUCache {
  int capacity;
  std::list<std::pair<int, int>> items;
  std::unordered_map<int, std::list<std::pair<int, int>>::iterator> where;

public:
  explicit LRUCache(int capacity) : capacity(capacity) {}

  // Value of key, or -1 if missing; marks key most recently used.
  int get(int key) {
    auto found = where.find(key);
    if (found == where.end())
      return -1;
    items.splice(items.begin(), items, found->second);
    return found->second->second;
  }

  void put(int key, int value) {
    if (capacity <= 0)
      return;
    auto found = where.find(key);
    if (found != where.end()) {
      found->second->second = value;
      items.splice(items.begin(), items, found->second);
      return;
    }
    if (int(items.size()) == capacity) {
      where.erase(items.back().first);
      items.pop_back();
    }
    items.emplace_front(key, value);
    where[key] = items.begin();
  }
};

// Evicts the least frequently used key, least recently used among ties.
// Each frequency bucket lists keys from oldest to newest use.
class LFUCache {
  struct Entry {
    int value, freq;
    std::list<int>::iterator position;
  };
  int capacity, minFreq = 0;
  std::unordered_map<int, Entry> entries;
  std::unordered_map<int, std::list<int>> buckets;

  void touch(Entry &entry) {
    auto &bucket = buckets[entry.freq];
    int key = *entry.position;
    bucket.erase(entry.position);
    if (bucket.empty()) {
      buckets.erase(entry.freq);
      if (minFreq == entry.freq)
        ++minFreq;
    }
    auto &next = buckets[++entry.freq];
    entry.position = next.insert(next.end(), key);
  }

public:
  explicit LFUCache(int capacity) : capacity(capacity) {}

  // Value of key, or -1 if missing; bumps the key's frequency.
  int get(int key) {
    auto found = entries.find(key);
    if (found == entries.end())
      return -1;
    touch(found->second);
    return found->second.value;
  }

  void put(int key, int value) {
    if (capacity <= 0)
      return;
    auto found = entries.find(key);
    if (found != entries.end()) {
      found->second.value = value;
      touch(found->second);
      return;
    }
    if (int(entries.size()) == capacity) {
      auto &bucket = buckets[minFreq];
      entries.erase(bucket.front());
      bucket.pop_front();
      if (bucket.empty())
        buckets.erase(minFreq);
    }
    auto &ones = buckets[1];
    entries[key] = {value, 1, ones.insert(ones.end(), key)};
    minFreq = 1;
  }
};
