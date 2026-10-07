#include <bits/stdc++.h>
#include <cassert>
#define main algorithm_main
#include "Manacher.cpp"
#undef main

using namespace std;

int main() {

  mt19937 generator(4);
  for (int size = 0; size < 60; ++size) {
    string text;
    for (int i = 0; i < size; ++i)
      text += 'a' + generator() % 3;
    Manacher(text);
    for (int i = 0; i < size; ++i) {
      int odd = 1, even = 0;
      while (i - odd >= 0 && i + odd < size && text[i - odd] == text[i + odd])
        ++odd;
      while (i - even - 1 >= 0 && i + even < size &&
             text[i - even - 1] == text[i + even])
        ++even;
      assert(Odd[i + 1] == odd && Even[i + 1] == even);
    }
  }
}
