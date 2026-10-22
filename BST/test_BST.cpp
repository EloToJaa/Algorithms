#include "BST.cpp"
#include <cassert>

int main() {
  mt19937 rng(9);
  BST tree;
  set<int> reference;
  for (int iteration = 0; iteration < 5000; ++iteration) {
    int key = int(rng() % 60) - 30, operation = rng() % 3;
    if (operation == 0)
      assert(tree.insert(key) == reference.insert(key).second);
    else if (operation == 1)
      assert(tree.remove(key) == (reference.erase(key) == 1));
    else {
      auto it = reference.lower_bound(key);
      optional<int> expected;
      if (it != reference.end())
        expected = *it;
      assert(tree.lowerBound(key) == expected);
    }
    assert(tree.contains(key) == reference.count(key));
    assert(tree.inorder() == vector<int>(reference.begin(), reference.end()));
    assert(tree.size() == int(reference.size()));
    if (!reference.empty()) {
      assert(tree.min() == *reference.begin());
      assert(tree.max() == *reference.rbegin());
    }
  }

  BST chain;
  for (int key = 0; key < 5000; ++key)
    chain.insert(key);
  assert(chain.inorder().size() == 5000);
  for (int key = 0; key < 5000; ++key)
    assert(chain.remove(key));
  assert(chain.empty() && !chain.lowerBound(0));
  bool threw = false;
  try {
    chain.min();
  } catch (const out_of_range &) {
    threw = true;
  }
  assert(threw);
}
