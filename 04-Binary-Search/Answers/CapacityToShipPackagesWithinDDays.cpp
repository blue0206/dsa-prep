/*
 * Problem: Capacity To Ship Packages Within D Days (LeetCode #1011)
 * Link:
 * https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/description/
 *
 * Approach: This is a classic "Binary Search on Answer" problem. The answer,
 *           the minimum required capacity, must lie within a specific range.
 *           1.  **Search Space:** The minimum possible capacity is the weight
 *               of the heaviest single package (`max(weights)`), as we must be
 *               able to ship it. The maximum possible capacity is the sum of
 *               all weights, which would ship everything in one day. So, our
 *               search space is `[max(weights), sum(weights)]`.
 *           2.  **Binary Search:** We binary search within this range. For each
 *               `mid` value (a potential capacity), we check if it's possible
 *               to ship all packages within `days`.
 *           3.  **Check Feasibility:** The `possible` function simulates the
 *               shipping process greedily.
 *           4.  **Narrowing Down:** If a capacity is possible, it's a potential
 *               answer, so we try for a smaller one (`high = mid - 1`). If not,
 *               we need a larger one (`low = mid + 1`).
 *
 * Time Complexity: O(N * log(S)), where S is the sum of all weights.
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int shipWithinDays(vector<int>& weights, int days);
bool possible(vector<int>& weights, int days, int k);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, days;
    cin >> n >> days;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Array: [ ";
    for (auto i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Minimum Capacity: " << shipWithinDays(nums, days) << endl;

    cout << endl;
  }

  return 0;
}

int shipWithinDays(vector<int>& weights, int days) {
  int low = INT_MIN;
  int high = 0;
  for (auto i : weights) {
    high += i;
    if (i > low) low = i;
  }

  int ans = high;
  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (possible(weights, days, mid)) {
      ans = mid;
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }

  return ans;
}

bool possible(vector<int>& weights, int days, int k) {
  int day = 1;
  int weight = 0;

  for (auto i : weights) {
    if (weight + i <= k) {
      weight += i;
    } else {
      day++;
      if (day > days) return false;
      weight = i;
    }
  }

  return day <= days;
}
