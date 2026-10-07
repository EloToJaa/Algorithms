#include <bits/stdc++.h>
#include <cassert>
#define main algorithm_main
#include "Knapsack.cpp"
#undef main

using namespace std;

int main() {

  ios_base::sync_with_stdio(false);
  istringstream input("4 5\n2 4\n3 5\n0 2\n4 8\n");
  ostringstream output;
  auto oldInput = cin.rdbuf(input.rdbuf());
  auto oldOutput = cout.rdbuf(output.rdbuf());
  algorithm_main();
  cin.rdbuf(oldInput);
  cout.rdbuf(oldOutput);
  assert(output.str() == "11\n");
}
