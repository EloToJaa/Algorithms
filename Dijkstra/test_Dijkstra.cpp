#include <bits/stdc++.h>
#include <cassert>
#define main algorithm_main
#include "Dijkstra.cpp"
#undef main

using namespace std;

int main() {

  V[1] = {{2, 10}, {3, 1}};
  V[3] = {{2, 2}};
  V[2] = {{4, 0}};
  dijkstra(1, 5);
  assert(D[2] == 3 && D[4] == 3 && D[5] == LLONG_MAX);
  assert(path[2] == 3 && path[4] == 2 && path[5] == -1);
  dijkstra(2, 5);
  assert(D[1] == LLONG_MAX && path[1] == -1 && D[4] == 0);
}
