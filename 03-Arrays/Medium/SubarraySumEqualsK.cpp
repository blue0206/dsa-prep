/*
 * Problem: Subarray Sum Equals K (LeetCode #560)
 * Link: https://leetcode.com/problems/subarray-sum-equals-k/description/
 *
 * Approach: This solution uses a hash map and the concept of prefix sums.
 *           The key insight is that if the cumulative sum up to the current
 *           index `i` is `pSum`, and there was a previous index where the
 *           cumulative sum was `pSum - k`, then the subarray between that
 *           previous index and the current index `i` must sum to `k`.
 *
 *           We use a hash map to store the frequencies of all prefix sums
 *           encountered so far. As we iterate through the array, we calculate
 *           the current `pSum` and check if `pSum - k` exists in our map. If
 *           it does, we add its stored frequency to our total count. Finally,
 *           we update the map with the frequency of the current `pSum`.
 *
 * Time Complexity: O(N) on average.
 * Space Complexity: O(N)
 */

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int subarraySum(vector<int>& nums, int k) {
  unordered_map<int, int> fq;

  int count = 0;
  int pSum = 0;
  for (int i = 0; i < nums.size(); i++) {
    pSum += nums[i];
    if (pSum == k) {
      count++;
    }
    if (fq.find(pSum - k) != fq.end()) {
      count += fq[pSum - k];
    }
    fq[pSum]++;
  }

  return count;
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Total subarrays with sum equal to k: " << subarraySum(nums, k)
         << endl;

    cout << endl;
  }

  return 0;
}
