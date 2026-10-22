#include <bits/stdc++.h>

using namespace std;

// Unbalanced BST of distinct keys. Nodes live in a pool and link by index
// (-1 is null), so there is no manual memory management or recursion.
class BST {
private:
  struct Node {
    int key, left = -1, right = -1;
  };
  vector<Node> nodes;
  int root = -1, count = 0;

public:
  bool insert(int key) {
    int parent = -1, v = root;
    while (v != -1) {
      if (key == nodes[v].key)
        return false;
      parent = v;
      v = key < nodes[v].key ? nodes[v].left : nodes[v].right;
    }
    nodes.push_back({key});
    int created = nodes.size() - 1;
    count++;
    if (parent == -1)
      root = created;
    else if (key < nodes[parent].key)
      nodes[parent].left = created;
    else
      nodes[parent].right = created;
    return true;
  }

  bool contains(int key) const {
    int v = root;
    while (v != -1 && nodes[v].key != key)
      v = key < nodes[v].key ? nodes[v].left : nodes[v].right;
    return v != -1;
  }

  bool remove(int key) {
    int parent = -1, v = root;
    while (v != -1 && nodes[v].key != key) {
      parent = v;
      v = key < nodes[v].key ? nodes[v].left : nodes[v].right;
    }
    if (v == -1)
      return false;
    count--;
    if (nodes[v].left != -1 && nodes[v].right != -1) {
      // Replace the key with its successor, then unlink the successor.
      parent = v;
      int successor = nodes[v].right;
      while (nodes[successor].left != -1) {
        parent = successor;
        successor = nodes[successor].left;
      }
      nodes[v].key = nodes[successor].key;
      v = successor;
    }
    int child = nodes[v].left != -1 ? nodes[v].left : nodes[v].right;
    if (parent == -1)
      root = child;
    else if (nodes[parent].left == v)
      nodes[parent].left = child;
    else
      nodes[parent].right = child;
    return true;
  }

  int min() const {
    if (root == -1)
      throw out_of_range("empty tree");
    int v = root;
    while (nodes[v].left != -1)
      v = nodes[v].left;
    return nodes[v].key;
  }

  int max() const {
    if (root == -1)
      throw out_of_range("empty tree");
    int v = root;
    while (nodes[v].right != -1)
      v = nodes[v].right;
    return nodes[v].key;
  }

  // Smallest stored key >= key, if any.
  optional<int> lowerBound(int key) const {
    optional<int> best;
    int v = root;
    while (v != -1) {
      if (nodes[v].key < key) {
        v = nodes[v].right;
      } else {
        best = nodes[v].key;
        v = nodes[v].left;
      }
    }
    return best;
  }

  vector<int> inorder() const {
    vector<int> keys, stack;
    int v = root;
    while (!stack.empty() || v != -1) {
      while (v != -1) {
        stack.push_back(v);
        v = nodes[v].left;
      }
      v = stack.back();
      stack.pop_back();
      keys.push_back(nodes[v].key);
      v = nodes[v].right;
    }
    return keys;
  }

  int size() const { return count; }

  bool empty() const { return count == 0; }
};
