#include <bits/stdc++.h>

using namespace std;

class MergeSort {
private:
  vector<int> nums;
  vector<int> aux;

  void merge(int left, int mid, int right) {
    for (int i = left; i <= right; i++)
      aux[i] = nums[i];

    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
      if (aux[i] <= aux[j])
        nums[k++] = aux[i++];
      else
        nums[k++] = aux[j++];
    }

    while (i <= mid)
      nums[k++] = aux[i++];

    while (j <= right)
      nums[k++] = aux[j++];
  }

public:
  MergeSort(const vector<int> &nums) : nums(nums) { aux.resize(nums.size()); }

  void mergeSort(int left, int right) {
    if (left >= right)
      return;

    int mid = left + ((right - left) >> 1);

    mergeSort(left, mid);
    mergeSort(mid + 1, right);

    merge(left, mid, right);
  }
};
