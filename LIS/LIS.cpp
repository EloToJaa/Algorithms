#include <bits/stdc++.h>

using namespace std;

class LIS {
public:
  int findNewPosition(const vector<int> &lis, int num) {
    return lower_bound(lis.begin(), lis.end(), num) - lis.begin();
  }

  int lengthOfLIS(const vector<int> &nums) {
    vector<int> tails;
    for (int num : nums) {
      auto position = lower_bound(tails.begin(), tails.end(), num);
      if (position == tails.end())
        tails.push_back(num);
      else
        *position = num;
    }
    return tails.size();
  }
};
