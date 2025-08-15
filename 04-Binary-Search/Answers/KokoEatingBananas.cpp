/*
 * Problem: Koko Eating Bananas (LeetCode #875)
 * Link: https://leetcode.com/problems/koko-eating-bananas/description/
 *
 * Approach: This is a classic "Binary Search on Answer" problem. The answer,
 *           the minimum eating speed `k`, must lie within a specific range.
 *           1.  **Search Space:** The minimum possible speed is 1, and the
 *               maximum necessary speed is the size of the largest pile. So,
 *               our search space is `[1, max(piles)]`.
 *           2.  **Binary Search:** We binary search within this range. For each
 *               `mid` value (a potential speed `k`), we check if it's possible
 *               to eat all bananas within `h` hours.
 *           3.  **Check Feasibility:** If a speed `k` is possible, it's a
 *               potential answer, so we try to find an even smaller speed by
 *               searching in the left half (`high = mid - 1`). If it's not
 *               possible, we need a higher speed, so we search in the right
 *               half (`low = mid + 1`).
 *
 * Time Complexity: O(N * log(max(piles)))
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int minEatingSpeed(vector<int>& piles, int h);
bool isPossible(vector<int>& piles, int h, int k);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, h;
    cin >> n >> h;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Array: [ ";
    for (auto i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Minimum Eating Speed: " << minEatingSpeed(nums, h) << endl;

    cout << endl;
  }

  return 0;
}

int minEatingSpeed(vector<int>& piles, int h) {
  int low = 1;
  int high = *(max_element(piles.begin(), piles.end()));

  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (isPossible(piles, h, mid)) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }

  return low;
}

bool isPossible(vector<int>& piles, int h, int k) {
  long long totalHours = 0;
  for (auto pile : piles) {
    // Calculate hours for the current pile: ceil(pile / k).
    // The integer arithmetic for ceil(a/b) is (a + b - 1) / b.
    totalHours += (long long)(pile + k - 1) / k;
  }
  return totalHours <= h;
}
