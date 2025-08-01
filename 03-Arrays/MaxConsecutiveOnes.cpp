/*
 * Problem: Max Consecutive Ones (LeetCode #485)
 * Link: https://leetcode.com/problems/max-consecutive-ones/description/
 *
 * Approach: Create a counter variable and a variable to store max. Iterate
 *           through the array and count ones. Upon encountering 0, update
 *           max if count greater, then reset count and proceed.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int findMaxConsecutiveOnes(vector<int>& nums) {
  int count = 0;
  int maxCount = 0;
  for (auto i : nums) {
    if (i == 1) {
      count++;
    } else {
      maxCount = max(count, maxCount);
      count = 0;
    }
  }
  return max(count, maxCount);
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Array: [ ";
    for (auto i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Max consecutive ones: " << findMaxConsecutiveOnes(nums) << endl;

    cout << endl;
  }

  return 0;
}
