#include <bits/stdc++.h>
#include <cassert>
#define main algorithm_main
#include "DFS.cpp"
#undef main

using namespace std;

int main() {

  for (int i = 1; i < 100000; ++i)
    V[i] = {i + 1};
  V[100000] = {1};
  dfs(1, 1);
  for (int i = 1; i <= 100000; ++i)
    assert(Vis[i]);
  assert(!Vis[100001]);
}
