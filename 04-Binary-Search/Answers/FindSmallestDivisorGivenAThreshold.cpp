/*
 * Problem: Find the Smallest Divisor Given a Threshold (LeetCode #1283)
 * Link:
 * https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/description/
 *
 * Approach: This is a "Binary Search on Answer" problem. The answer, the
 *           smallest divisor, must lie within a specific range.
 *           1.  **Search Space:** The smallest possible divisor is 1, and the
 *               largest possible divisor we'd ever need to check is the
 *               maximum element in the array. So, our search space is
 *               `[1, max(nums)]`.
 *           2.  **Binary Search:** We binary search within this range. For each
 *               `mid` value (a potential divisor), we check if the sum of
 *               divisions is less than or equal to the `threshold`.
 *           3.  **Check Feasibility:** The `possible` function calculates the
 *               sum of `ceil(num / divisor)` for all numbers.
 *           4.  **Narrowing Down:** If the sum is within the threshold, it's a
 *               possible answer, so we try to find a smaller divisor
 *               (`high = mid - 1`). If not, we need a larger divisor
 *               (`low = mid + 1`).
 *
 * Time Complexity: O(N * log(max(nums)))
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int smallestDivisor(vector<int>& nums, int threshold);
bool possible(vector<int>& nums, int threshold, int k);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, threshold;
    cin >> n >> threshold;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Array: [ ";
    for (auto i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Smallest Divisor: " << smallestDivisor(nums, threshold) << endl;

    cout << endl;
  }

  return 0;
}

int smallestDivisor(vector<int>& nums, int threshold) {
  int low = 1;
  int high = *(max_element(nums.begin(), nums.end()));
  int ans = high;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (possible(nums, threshold, mid)) {
      ans = mid;
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }

  return ans;
}

bool possible(vector<int>& nums, int threshold, int k) {
  long long sum = 0;
  for (int num : nums) {
    sum += (num + k - 1) / k;
    if (sum > threshold) return false;
  }
  return true;
}
