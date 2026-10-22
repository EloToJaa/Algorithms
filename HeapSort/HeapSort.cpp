#include <bits/stdc++.h>

using namespace std;

class HeapSort {
private:
  vector<int> nums;

  void siftDown(int i, int size) {
    while (2 * i + 1 < size) {
      int child = 2 * i + 1;
      if (child + 1 < size && nums[child] < nums[child + 1])
        child++;
      if (nums[i] >= nums[child])
        return;
      swap(nums[i], nums[child]);
      i = child;
    }
  }

public:
  HeapSort(const vector<int> &nums) : nums(nums) {}

  void sort() {
    int n = nums.size();
    for (int i = n / 2 - 1; i >= 0; i--)
      siftDown(i, n);
    // Move the current maximum behind the shrinking heap.
    for (int end = n - 1; end > 0; end--) {
      swap(nums[0], nums[end]);
      siftDown(0, end);
    }
  }

  vector<int> getSortedArray() const { return nums; }
};
