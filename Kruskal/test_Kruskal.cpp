#include <bits/stdc++.h>
#include <cassert>
#define main algorithm_main
#include "Kruskal.cpp"
#undef main

using namespace std;

int main() {

  K[1] = {1, 2, 2};
  K[2] = {2, 3, -1};
  K[3] = {1, 3, 8};
  K[4] = {1, 1, -20};
  Kruskal(4, 4);
  assert(totalWeight == 1 && selected.size() == 2);
  assert(Find(1) == Find(3) && Find(4) != Find(1));
  Kruskal(4, 0);
  assert(totalWeight == 0 && selected.empty());
}
