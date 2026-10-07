#include <bits/stdc++.h>
#include <cassert>
#define main algorithm_main
#include "BFS.cpp"
#undef main

using namespace std;

int main() {

  V[1] = {2, 2, 3};
  V[2] = {1, 4};
  V[3] = {4};
  bfs(1);
  for (int i = 1; i <= 4; ++i)
    assert(Vis[i]);
  assert(!Vis[5]);
  assert(Q.empty());
  bfs(1);
  assert(Q.empty());
}
