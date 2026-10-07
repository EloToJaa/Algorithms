#include <bits/stdc++.h>
#include <cassert>
#define main algorithm_main
#include "FindAndUnion.cpp"
#undef main

using namespace std;

int main() {

  Init(5);
  Union(1, 2);
  Union(2, 1);
  Union(1, 1);
  assert(Ile[Find(1)] == 2);
  Union(3, 4);
  Union(2, 3);
  assert(Ile[Find(4)] == 4 && Find(5) != Find(1));
}
