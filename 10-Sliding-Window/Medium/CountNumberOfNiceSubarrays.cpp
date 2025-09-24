/*
 * Problem: Count Number of Nice Subarrays (LeetCode #1248)
 * Link:
 * https://leetcode.com/problems/count-number-of-nice-subarrays/description/
 *
 * Approach: This problem asks for the number of subarrays with *exactly* `k`
 *           odd numbers. This can be solved using the principle that
 *           `count(exactly k) = count(at most k) - count(at most k-1)`.
 *
 *           A helper function, `subarrayCount`, is created to count the number
 *           of subarrays with at most `k` odd numbers. This function uses a
 *           standard sliding window. For each valid window `[low, high]`, all
 *           subarrays ending at `high` (i.e., `[low, high]`, `[low+1, high]`,
 *           etc.) are also valid. There are `high - low + 1` such subarrays,
 *           which we add to our running total.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int numberOfSubarrays(const vector<int>& nums, int k);
int subarrayCount(const vector<int>& nums, int k);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "k: " << k << endl;
    cout << "Input Array: [ ";
    for (int i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Number of Nice Subarrays: " << numberOfSubarrays(nums, k) << endl;
  }

  return 0;
}

int numberOfSubarrays(const vector<int>& nums, int k) {
  int atMostKCount = subarrayCount(nums, k);
  int lessThanKCount = subarrayCount(nums, k - 1);

  return (atMostKCount - lessThanKCount);
}

int subarrayCount(const vector<int>& nums, int k) {
  if (k < 0) return 0;

  int low = 0;
  int high = 0;

  int oddCount = 0;
  int ans = 0;
  while (high < nums.size()) {
    // Expand the window.
    if (nums[high] & 1) oddCount++;

    // If the window is invalid, shrink it from the left.
    while (oddCount > k) {
      if (nums[low] & 1) oddCount--;
      low++;
    }

    // The window [low, high] is valid. All subarrays ending at `high`
    // are also valid. There are `high - low + 1` such subarrays.
    ans += (high - low + 1);
    high++;
  }

  return ans;
}
