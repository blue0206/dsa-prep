/*
 * Problem: Subarrays with K Different Integers (LeetCode #992)
 * Link:
 * https://leetcode.com/problems/subarrays-with-k-different-integers/description/
 *
 * Approach:
 * This is a challenging problem because a standard sliding window cannot
 * directly count subarrays with *exactly* `k` distinct elements. The trick is
 * to rephrase the problem using the principle of inclusion-exclusion:
 * `count(exactly k) = count(at most k) - count(at most k-1)`.
 *
 * We create a helper function, `subarrayCount`, that uses a sliding window to
 * solve the easier problem of counting subarrays with *at most* `k` distinct
 * elements.
 *
 * For each position of the `high` pointer, the window `[low, high]` is a valid
 * window with at most `k` distinct elements. All subarrays ending at `high`
 * (i.e., `[low, high]`, `[low+1, high]`, etc.) are also valid. There are
 * `high - low + 1` such subarrays, which we add to our total count.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
using ll = long long;

int subarraysWithKDistinct(const vector<int>& nums, int k);
ll subarrayCount(const vector<int>& nums, int k);

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

    cout << "Good Subarrays: " << subarraysWithKDistinct(nums, k) << endl;
  }

  return 0;
}

int subarraysWithKDistinct(const vector<int>& nums, int k) {
  ll atMostK = subarrayCount(nums, k);
  ll lessThanK = subarrayCount(nums, k - 1);

  return atMostK - lessThanK;
}

ll subarrayCount(const vector<int>& nums, int k) {
  if (k < 0) return 0;

  unordered_map<int, int> intHash;
  ll count = 0;
  int low = 0;
  int high = 0;
  while (high < nums.size()) {
    // Expand the window.
    intHash[nums[high]]++;

    // If the window is invalid, shrink it from the left.
    while (intHash.size() > k) {
      intHash[nums[low]]--;
      if (intHash[nums[low]] == 0) {
        intHash.erase(nums[low]);
      }
      low++;
    }

    // The window [low, high] is valid. All subarrays ending at `high`
    // are also valid. There are `high - low + 1` such subarrays.
    count += (high - low + 1);
    high++;
  }

  return count;
}
