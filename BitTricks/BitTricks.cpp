#include <bits/stdc++.h>

// Number of set bits (Kernighan: each step clears the lowest set bit).
int popcount(unsigned long long x) {
  int count = 0;
  for (; x; x &= x - 1)
    ++count;
  return count;
}

// Value of the lowest set bit; 0 for x = 0. Unsigned negation avoids UB.
unsigned long long lowestBit(unsigned long long x) { return x & (0 - x); }

unsigned long long clearLowestBit(unsigned long long x) { return x & (x - 1); }

bool isPowerOfTwo(long long x) { return x > 0 && (x & (x - 1)) == 0; }

// XOR of all values: the element appearing an odd number of times.
int singleNumber(const std::vector<int> &nums) {
  int result = 0;
  for (int value : nums)
    result ^= value;
  return result;
}

// bits[i] is popcount(i) for 0 <= i <= n.
std::vector<int> countingBits(int n) {
  std::vector<int> bits(n + 1, 0);
  for (int i = 1; i <= n; ++i)
    bits[i] = bits[i >> 1] + (i & 1);
  return bits;
}

// Every submask of mask in decreasing order, ending with 0.
std::vector<unsigned> submasks(unsigned mask) {
  std::vector<unsigned> result;
  for (unsigned sub = mask;; sub = (sub - 1) & mask) {
    result.push_back(sub);
    if (sub == 0)
      break;
  }
  return result;
}

// Wrapping 32-bit a + b without +: XOR sums bits, AND-shift carries them.
int add32(int a, int b) {
  uint32_t x = a, y = b;
  while (y) {
    uint32_t carry = (x & y) << 1;
    x ^= y;
    y = carry;
  }
  return static_cast<int32_t>(x);
}
