#include "BitTricks.cpp"
#include <cassert>

int main() {
  std::mt19937_64 rng(21);
  for (int iteration = 0; iteration < 500; ++iteration) {
    unsigned long long x = rng() >> (rng() % 64);
    int bits = 0;
    unsigned long long low = 0;
    for (int i = 63; i >= 0; --i)
      if (x >> i & 1)
        ++bits, low = 1ULL << i;
    assert(popcount(x) == bits);
    assert(lowestBit(x) == low);
    assert(clearLowestBit(x) == x - low);
    assert(isPowerOfTwo((long long)(x >> 1)) == (popcount(x >> 1) == 1));

    int a = static_cast<int32_t>(rng()), b = static_cast<int32_t>(rng());
    assert(add32(a, b) == static_cast<int32_t>((long long)a + b));

    unsigned mask = rng() % 1024;
    std::vector<unsigned> expected;
    for (int s = mask; s >= 0; --s)
      if ((s & mask) == unsigned(s))
        expected.push_back(s);
    assert(submasks(mask) == expected);

    std::vector<int> nums;
    int pairs = rng() % 6, lone = int(rng() % 100) - 50;
    for (int i = 0; i < pairs; ++i) {
      int value = int(rng() % 100) - 50;
      nums.push_back(value), nums.push_back(value);
    }
    nums.push_back(lone);
    std::shuffle(nums.begin(), nums.end(), rng);
    assert(singleNumber(nums) == lone);
  }
  auto table = countingBits(300);
  for (int i = 0; i <= 300; ++i)
    assert(table[i] == popcount(i));
  assert(singleNumber({4, 1, 2, 1, 2}) == 4);
  assert(countingBits(5) == std::vector<int>({0, 1, 1, 2, 1, 2}));
  assert(add32(1, 2) == 3 && add32(-1, 1) == 0);
  assert(add32(INT_MAX, 1) == INT_MIN);
  assert(submasks(5) == std::vector<unsigned>({5, 4, 1, 0}));
  assert(!isPowerOfTwo(0) && isPowerOfTwo(1LL << 40));
}
