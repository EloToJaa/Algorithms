#include <bits/stdc++.h>

using namespace std;

class QuickSort {
private:
  vector<int> nums;

  int partition(int left, int right) {
    int mid = left + ((right - left) >> 1);
    swap(nums[mid], nums[right]);
    int pivot = nums[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
      if (nums[j] < pivot)
        swap(nums[++i], nums[j]);
    }

    swap(nums[i + 1], nums[right]);
    return i + 1;
  }

  void quickSort(int left, int right) {
    while (left < right) {
      int pivot = partition(left, right);
      // Recurse on the smaller part to bound stack depth by O(log n).
      if (pivot - left < right - pivot) {
        quickSort(left, pivot - 1);
        left = pivot + 1;
      } else {
        quickSort(pivot + 1, right);
        right = pivot - 1;
      }
    }
  }

public:
  QuickSort(const vector<int> &nums) : nums(nums) {}

  void sort() { quickSort(0, static_cast<int>(nums.size()) - 1); }

  vector<int> getSortedArray() { return nums; }
};
