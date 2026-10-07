#include <bits/stdc++.h>
#include <cassert>
#define main algorithm_main
#include "Trie.cpp"
#undef main

using namespace std;

int main() {

  Trie trie;
  trie.insert("apple");
  trie.insert("app");
  trie.insert("apple");
  assert(trie.search("app") && !trie.search("ap") && trie.startsWith("ap"));
  assert(!trie.startsWith("cat") && !trie.search("") && trie.startsWith(""));
  trie.insert("");
  assert(trie.search(""));
}
