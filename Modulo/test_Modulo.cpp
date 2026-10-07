#include <bits/stdc++.h>
#include <cassert>
#define main algorithm_main
#include "Modulo.cpp"
#undef main

using namespace std;

int main() {

  ModuloStruct arithmetic(7);
  assert(arithmetic.Modulo(-8) == 6);
  assert(arithmetic.Add(-8, 3) == 2);
  assert(arithmetic.Subtract(1, 3) == 5);
  assert(arithmetic.Multiply(-8, 3) == 4);
  assert(arithmetic.Power(-2, 3) == 6);
  assert(arithmetic.Divide(6, 3) == 2);
  bool caught = false;
  try {
    arithmetic.Divide(1, 7);
  } catch (const domain_error &) {
    caught = true;
  }
  assert(caught);
}
