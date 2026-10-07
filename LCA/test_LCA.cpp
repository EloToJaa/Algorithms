#include <bits/stdc++.h>
#include <cassert>
#define main algorithm_main
#include "LCA.cpp"
#undef main

using namespace std;

int main() {

  mt19937 generator(6);
  vector<int> parents(81, 1);
  for (int i = 2; i <= 80; ++i) {
    parents[i] = 1 + generator() % (i - 1);
    V[i].push_back(parents[i]);
    V[parents[i]].push_back(i);
  }
  ancestors(1, 1);
  for (int a = 1; a <= 80; ++a) {
    set<int> chain;
    int vertex = a;
    while (vertex != 1) {
      chain.insert(vertex);
      vertex = parents[vertex];
    }
    chain.insert(1);
    for (int b = 1; b <= 80; ++b) {
      int expected = b;
      while (!chain.count(expected))
        expected = parents[expected];
      assert(LCA(a, b) == expected);
    }
  }
}
