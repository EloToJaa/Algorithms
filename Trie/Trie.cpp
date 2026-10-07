#include <bits/stdc++.h>

using namespace std;

class TrieNode {
public:
  int nextNode[26];
  bool isEnd;
  TrieNode() : isEnd(false) { memset(nextNode, -1, sizeof(nextNode)); }
};

class Trie {
public:
  vector<TrieNode> trie;

  Trie() { trie.push_back(TrieNode()); }

  void insert(string word) {
    int node = 0;
    for (const char &c : word) {
      if (trie[node].nextNode[c - 'a'] == -1) {
        trie[node].nextNode[c - 'a'] = trie.size();
        trie.push_back(TrieNode());
      }
      node = trie[node].nextNode[c - 'a'];
    }
    trie[node].isEnd = true;
  }

  bool search(string word) {
    int node = 0;
    for (const char &c : word) {
      if (trie[node].nextNode[c - 'a'] == -1) {
        return false;
      }
      node = trie[node].nextNode[c - 'a'];
    }
    return trie[node].isEnd;
  }

  bool startsWith(string prefix) {
    int node = 0;
    for (const char &c : prefix) {
      if (trie[node].nextNode[c - 'a'] == -1) {
        return false;
      }
      node = trie[node].nextNode[c - 'a'];
    }
    return true;
  }
};
