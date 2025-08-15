/*
 * Problem: Minimum Number of Days to Make m Bouquets (LeetCode #1482)
 * Link:
 * https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/description/
 *
 * Approach: This is a classic "Binary Search on Answer" problem. The answer,
 *           the minimum number of days, must lie within a specific range.
 *           1.  **Search Space:** The minimum possible day is the earliest
 *               bloom day in the array, and the maximum is the latest bloom
 *               day. So, our search space is `[min(bloomDay), max(bloomDay)]`.
 *           2.  **Binary Search:** We binary search within this range. For each
 *               `mid` value (a potential day), we check if it's possible to
 *               make `m` bouquets.
 *           3.  **Check Feasibility:** The `possible` function iterates through
 *               the `bloomDay` array, counting consecutive flowers that have
 *               bloomed by the given day (`mid`) to see if `m` bouquets can be
 *               formed.
 *           4.  **Narrowing Down:** If it's possible, we store that day as a
 *               potential answer and search for an earlier day
 *               (`high = mid - 1`). If not, we need to wait longer
 *               (`low = mid + 1`).
 *
 * Time Complexity: O(N * log(max(bloomDay)))
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int minDays(vector<int>& bloomDay, int m, int k);
bool possible(vector<int>& bloomDay, int m, int k, int mid);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Array: [ ";
    for (auto i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Minimum Days to make Bouquets: " << minDays(nums, m, k) << endl;

    cout << endl;
  }

  return 0;
}

int minDays(vector<int>& bloomDay, int m, int k) {
  if (bloomDay.size() < (long long)m * k) {
    return -1;
  }

  int low = *(min_element(bloomDay.begin(), bloomDay.end()));
  int high = *(max_element(bloomDay.begin(), bloomDay.end()));

  int ans = -1;
  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (possible(bloomDay, m, k, mid)) {
      ans = mid;
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }

  return ans;
}

bool possible(vector<int>& bloomDay, int m, int k, int mid) {
  int bouquets = 0;
  int flowers = 0;
  for (int i = 0; i < bloomDay.size(); i++) {
    if (bloomDay[i] <= mid) {
      flowers++;
    } else {
      bouquets += (flowers / k);
      flowers = 0;
    }
  }
  bouquets += (flowers / k);

  return bouquets >= m;
}
