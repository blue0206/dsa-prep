/*
 * Problem: Maximum Subarray (LeetCode #53)
 * Link: https://leetcode.com/problems/maximum-subarray/description/
 *
 * Approach:------------------------Kadane's Algorithm--------------------------
 *          In this algorithm, we initialize a sum and maxSum to track current
 *          and maximum sum.
 *          We simply iterate through the array and update the sum.
 *          Each time sum crosses maxSum, we update maxSum.
 *          If sum goes negative, we reset it to 0 as it would not help us
 *          determine the maximum possible sum if it is already negative.
 *          In this way, at the end of iteration, the maxSum holds the sum of
 *          the subarray having greater sum than all other subarrays.
 *
 *          This can also be seen from the perspective of start and end indices
 *          of subarray where the start pointer/index is moved forward each
 *          time sum is reset to 0 and the end is incremented each time maxSum
 *          is updated.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int maxSubArray(vector<int>& nums, int& subarrayStart, int& subarrayEnd) {
  int maxSum = INT_MIN;
  int sum = 0;
  int currentStart = 0;

  for (int i = 0; i < nums.size(); i++) {
    sum += nums[i];

    if (sum > maxSum) {
      maxSum = sum;
      subarrayStart = currentStart;
      subarrayEnd = i;
    }

    if (sum < 0) {
      sum = 0;
      currentStart = i + 1;
    }
  }

  return maxSum;
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

    int start = 0, end = 0;
    int maxSum = maxSubArray(nums, start, end);

    cout << "Max Sum: " << maxSum << endl;

    cout << "Max Sum Subarray: [ ";
    for (int i = start; i <= end; i++) {
      cout << nums[i] << " ";
    }
    cout << "]" << endl;
    cout << endl;
  }

  return 0;
}
