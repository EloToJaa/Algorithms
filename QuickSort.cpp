#include <bits/stdc++.h>

using namespace std;

class QuickSort {
private:
  vector<int> nums;

  int partition(int left, int right) {
    int mid = left + ((right - left) >> 1);
    int pivot = nums[mid];
    int i = left - 1;

    for (int j = left; j < right; j++) {
      if (nums[j] < pivot)
        swap(nums[++i], nums[j]);
    }

    swap(nums[i + 1], nums[right]);
    return i + 1;
  }

  void quickSort(int left, int right) {
    if (left >= right)
      return;

    int pivot = partition(left, right);

    quickSort(left, pivot - 1);
    quickSort(pivot + 1, right);
  }

public:
  QuickSort(const vector<int> &nums) : nums(nums) {}

  void sort() { quickSort(0, nums.size() - 1); }

  vector<int> getSortedArray() { return nums; }
};
