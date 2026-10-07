#include <bits/stdc++.h>
#include <cassert>
#define main algorithm_main
#include "Mo.cpp"
#undef main

using namespace std;

int main() {

  ios_base::sync_with_stdio(false);
  istringstream input("5 3\n1 2 1 3 2\n1 5\n2 4\n3 3\n");
  ostringstream output;
  auto oldInput = cin.rdbuf(input.rdbuf());
  auto oldOutput = cout.rdbuf(output.rdbuf());
  algorithm_main();
  cin.rdbuf(oldInput);
  cout.rdbuf(oldOutput);
  assert(output.str() == "3 3 1 \n");
}
