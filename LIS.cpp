#include <bits/stdc++.h>

using namespace std;

class LIS {
public:
  int findNewPosition(const vector<int> &lis, int num) {
    int l = 0, r = lis.size() - 1, mid;

    while (l < r) {
      mid = (l + r) >> 1;
      if (num < lis[mid])
        r = mid;
      else
        l = mid + 1;
    }
    return l;
  }

  int lengthOfLIS(const vector<int> &nums) {
    int n = nums.size();
    if (n <= 1)
      return n;

    vector<int> lis;
    lis.push_back(nums[0]);
    for (const int &num : nums) {
      if (num > lis[lis.size() - 1]) {
        lis.push_back(num);
        continue;
      }
      if (num == lis[lis.size() - 1])
        continue;
      int pos = findNewPosition(lis, num);
      if (pos > 0 && lis[pos - 1] == num)
        continue;
      lis[pos] = num;
    }

    return lis.size();
  }
};
